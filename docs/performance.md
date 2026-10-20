# Performance notes

What was measured, what helped, and what was noise. Numbers come from the `out/fast`
build (`-O2`, `-march=native`) on one machine (12 threads, one used by the guest).

## How to measure

Sampling a few dozen stacks with gdb is **not** reliable here: the same build showed
"75% VU1" in one run and "60% GS" in another, because the game moves through different
scenes. Use the built-in counters instead:

    PS2X_PROF=1 PS2X_AUTOX=20 BUILD=fast ./run.sh 110

- `PS2X_PROF=1` prints one line per 10 s window to stderr (`[prof]` in `run.log`):
  `vu1_core` (share of wall time in the VU1 interpreter, GS time excluded),
  `gs_in_vu1` / `gs_total` (software rasteriser), `cycles` (VU1 cycles executed in the
  window, a proxy for guest progress because the game thread is always at 100%) and
  `core_ns/cycle` (interpreter cost per VU1 cycle, independent of the scene).
- `PS2X_AUTOX=<s>` pulses X on the pad from second `<s>`, so the run goes past the title
  without a keyboard. The timeline is then reproducible: title (steady, GS-bound) →
  loading (VU1-bound) → 3D scene (GS-bound).
- Compare **steady windows of the same phase**. Window-to-window noise in steady phases
  is about ±0.5%; the first window includes start-up and is useless.
- `cycles` is cumulative in the VU1 (`m_cycle` is reset only by `reset()`), so use the
  difference before/after a call. A first version that assumed the opposite undercounted.

## Result (same conditions, `PS2X_AUTOX=20`, 10 windows each)

| Phase | Base | Now | Change |
| --- | --- | --- | --- |
| Title (steady), VU1 cycles/window | 2.87 M | 4.80 M | +67% |
| Loading (VU1-bound), cycles/window | 26.6 M | 38.0 M | +43% |
| Loading, `core_ns/cycle` | 309 | 217 | -30% |
| 3D scene (GS-bound), cycles/window | 6.9 M | 9.8 M | +42% |

Still slow: the VU1 interpreter costs ~215 ns per cycle (the real unit runs at ~3 ns), and
the rasteriser is ~70% of the 3D scene.

## Real gains (kept)

1. **Solid sprite fills at block granularity** (`GSMem::FillRect`). In the title 81% of
   all pixels were untextured, unblended sprites (screen/Z clears, ~146 M pixels per
   10 s). A fully covered 8x8 (32-bit) or 16x8 (16-bit) block is 256 contiguous bytes,
   so it is one `memcpy` instead of 64 address calculations and two indirect calls. Fill
   time went from ~2 s to ~0.2 s per window. Falls back to the per-pixel path whenever
   fog, blending, a frame mask, a destination alpha test or a depth test is active.
   Checked byte for byte against the per-pixel path: 2700 random rectangles over all
   32/16-bit formats, plus a run-time comparison of the whole 4 MB VRAM after every fill
   in the real game (0 differences).
2. **VU1: skip `commitReadyPipelines` when nothing is ready.** It ran twice per cycle and
   scanned every pipeline array (25% of the samples). A conservative "earliest ready
   cycle" (`m_nextReady`, lowered at the 10 creation sites, recomputed after a scan)
   removes the scan. Verified with a temporary check that no ready entry was ever
   skipped over ~190 M cycles. `core_ns/cycle` -15%.
3. **CLUT memo and no `std::lround`** in texture sampling. Palette lookups are memoised
   per index while the CLUT and TEXA do not change (invalidated on CLUT load);
   `lround` was a libm call per channel in the bilinear filter and is replaced by the
   exact equivalent for non-negative values. +9% in both title and 3D scene.
4. **`-O3` for `ps2_vu1_core.cpp`** (`#pragma GCC optimize`): `core_ns/cycle` about -10%,
   reproduced in two phases.

## Small or noise (do not spend more time here)

- `-O3` for `gs_cpu_backend.cpp`: about +4%, one comparison, close to the noise. Kept
  because it costs nothing.
- Fill at page granularity (first attempt) versus block granularity: throughput was
  within noise; block is kept because it also covers partial pages.
- Returning the decoded VU1 instruction pair by reference: the struct is ~80 bytes, so
  the copy is cheap. Not done.
- Counting pixels per primitive type, timing `FillRect`, bisecting with gdb: useful once
  to find the target, removed afterwards (a per-pixel counter costs ~1 ns on a ~36 ns
  pixel). Only the `PS2X_PROF` timers remain, and the GS timer is off unless the variable
  is set.

## Not tried yet

- A VU1 mode without the pipeline model: large, and the timing may matter for correctness.
  The loading phase is the only place where it dominates.
- Triangle rasteriser: per-pixel barycentrics over the whole bounding box, and texture
  sampling (`SampleTexture`, `ReadTexture`) is ~half of the 3D scene. This is the next
  biggest lever.
- Running the GS on its own thread: at most ~1.4x and adds races.

## Found while measuring: crash when X arrives late on the title screen

Pressing X on the title after it has been idle for a while ends in
`[guest-branch:missing-target]` (an indirect call through garbage). It is **not** caused
by the optimisations above: with them disabled, X from second 60 crashed 4 of 4 runs,
while X from second 20 to 25 passed 10 of 10 with them enabled. A faster build only gets
to the bad state sooner in wall-clock time. Likely related to the skipped intro movie
(the attract sequence the title would start); not investigated yet.

---

# Windows baseline (2026-10-20, branch `phase-a2-build`, commit `4c6b7f6`)

**Machine:** Windows 11, i7-11800H (16 cores), 33 GB RAM, RTX 3060 Laptop GPU,
clang-cl 23.1.3, CMake 4.5.0-rc1, Ninja 1.13.2.

**Toolchain flags:** Debug build type + explicit
`/O2 /Ob2 /Oi /GF /Gy /DNDEBUG /Z7 -msse4.1` (no AVX2, no `/fp:fast`, no LTO).
Release build type fails on clang-cl (`/Qspectre-` rejected) and forces AVX2
and `/fp:fast` (audit items 15–17).

**Build outcome:** `ps2_recomp.exe` + `ps2EntryRunner.exe` both build (exit 0).
No generated code was edited; the SSE4.1 floor was added to our CMake preset
(`-msse4.1`; `/arch:SSE4.1` is ignored by clang-cl on x86-64).

**First run (30 s, `PS2X_PROF=1`):**

| Metric | Value |
| --- | --- |
| Window opened | Yes (raylib 5.5, GLFW, OpenGL 3.3) |
| Render size | 640 × 448 (PS2 native) → upscaled |
| ELF load | ✅ at 0x10a008 (matches header) |
| Execution | ✅ started at entry point |
| IOP RPC syscalls | Active (`sceSifGetReg`, `SetReg`, `SetDma`) |
| Textures | 640×512 RGBA, 512×128 RGBA loaded |
| `ps2_log.txt` size | 272 MB (aggressive logs on) |
| Exit code | 124 (timeout after 30 s), **no crash** |
| Visible frame | **Purple screen** — game did not reach a drawn frame in 30 s |

**Performance measurements (PS2X_PROF):** **N/A, not yet measurable.** The 30 s
run captured start-up and initial IOP bring-up only; no steady 10 s window
completed, no VU1/GS timers emitted, no `PS2X_AUTOX` pad pulses applied.
The "purple screen" is the attract/intro state before the title screen; the
game has not yet reached the measurable phases (title, loading, 3D scene)
documented in the Linux notes above.

**Next steps to get measurable data:** extend the run past the intro (e.g.
`PS2X_AUTOX=20` for 110 s), disable aggressive logs for speed, capture the
first steady `PS2X_PROF` windows. Do not copy Linux numbers here.
