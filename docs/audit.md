# Audit: Windows port, Phase A.0

Date: 2026-10-20. Branch `phase-a0-audit`, base `2131704`. Host: Windows 11, Git Bash
(MSYS2 ucrt64). Read-only audit apart from extracting the ELF into the ignored `game/`.
Nothing was built or run. This document lists no game function addresses.

Priority: **P0** blocks safe work or could leak game data, **P1** blocks the Windows build,
**P2** wrong/misleading but has a workaround, **P3** cleanup.

## Inputs checked

| Item | Result | Evidence |
| --- | --- | --- |
| ISO `Downhill Domination.iso` (repo root) | Valid. 2,530,869,248 bytes = 1,235,776 sectors of 2048; ISO9660 PVD at sector 16 (`\x01CD001`, system id `PLAYSTATION`); `7z t` read all 14 folders / 2338 files, "Everything is Ok" | `stat`, `dd \| od`, `7z t` |
| ISO SHA-1 | `a2739ce3b632c1513d2a96cf3982b5effcca5a3c` (computed locally, **not** compared against a Redump entry) | `sha1sum` |
| `SYSTEM.CNF` | `BOOT2 = cdrom0:\SCUS_971.77;1`, `VER = 1.00`, `VMODE = NTSC` | `7z e -so` |
| Game ELF | `SCUS_971.77` (USA, not SLES/SLUS), 1,691,684 bytes, extracted to `game/SCUS_971.77` (git-ignored by `/game/`). Header: ELF32, little-endian, `e_type`=2 (EXEC), `e_machine`=8 (MIPS). SHA-1 `4e25a222ad8a475b5d26c2e928e90b5f2b7075eb` | `od -t x1 -N 64` |
| REA, provider `ghidra` on the ELF | **Rejected**: `target_format_unsupported`, "Windows Ghidra P0 accepts native PE and explicitly selected raw 6502 targets only." Hopper/IDA/Kuna are also unavailable or have no MIPS support | `open_binary` error |
| Ghidra | `C:\Tools\ghidra_12.1.4_PUBLIC`, `support\analyzeHeadless.bat` present; Emotion Engine extension at `%APPDATA%\ghidra\ghidra_12.1.4_PUBLIC\Extensions\ghidra-emotionengine-reloaded`. Not run yet | `ls` |

## Toolchain on this machine

| Tool | Status |
| --- | --- |
| CMake | 4.5.0-rc1 (`C:\Program Files\CMake`) — a release candidate |
| Ninja | 1.13.2 (winget) |
| C/C++ compiler | **Not on PATH.** MSVC 14.51.36231 (VS 18 Community) is installed with `vcvars64.bat`; it needs a Developer shell. No gcc, clang or clang-cl |
| Windows SDK | 10.0.26100.0 |
| Python | `python` = 3.12.10 works; **`python3` is the Microsoft Store stub** ("Python was not found") |
| Java | Temurin 21.0.12 (Ghidra) |
| 7-Zip | 26.04 installed, **not on PATH** (`C:\Program Files\7-Zip\7z.exe`) |
| rsync | **Missing** |
| SDL2 | **Not found** (no `sdl2-config`, no SDL2 dir under `C:\` depth 3) |
| Vulkan SDK / glslang | **Missing** (`VULKAN_SDK` unset, no `C:\VulkanSDK`, no `glslangValidator`/`glslc`) |
| git | MSYS2 git, `core.autocrlf=true`, `core.symlinks=false`, `core.ignorecase=true` |

Whether PS2Recomp actually needs SDL2/Vulkan/glslang on Windows, or fetches them itself, is
**unknown**: `PS2Recomp/` is not cloned yet. `setup.sh:8` installs them on Arch.

## Issues

### P0

1. **The ISO in the repo root is not ignored.** `git status` lists `?? "Downhill Domination.iso"`.
   `.gitignore:2-8` only ignores fixed folders (`/game/`, `/PS2 BIOS/`,
   `/Downhill Domination (USA)/`, ...); there is no rule for `*.iso`, `*.bin`, `*.cue`, `*.img`,
   the ELF by name, BIOS files outside `/PS2 BIOS/`, or RAM dumps. A single `git add -A` would
   commit 2.4 GB of game data. Proposed fix below (not applied).
2. **No Windows RE path through REA.** See the table above. Function identification has to use
   Ghidra headless exports (`analyzeHeadless.bat` + `tools/ghidra/DecompileFunctions.java`).
   There is also no local Ghidra project (`ghidra/DownhillDom`) and no `config/`, so
   `functions.csv`, `config.toml`, `binds.txt` and the generated code all have to be made
   again on this machine.

### P1 (blocks a Windows build)

3. **`setup.sh` is Arch-only.** `setup.sh:8` uses `sudo pacman -S ...`; `setup.sh:12` calls
   `7z` (not on PATH); `setup.sh:6` expects `Downhill Domination (USA)/Downhill Domination (USA).iso`,
   but the ISO is at `./Downhill Domination.iso` (also `README.md:22`, `run.sh:5`).
4. **GCC-only compiler flags.** `setup.sh:19` and `AGENTS.md:15` use `-DCMAKE_CXX_FLAGS=-march=native`,
   which MSVC does not accept (it needs something like `/arch:AVX2`; the runtime needs at least SSE4.1 according to
   `AGENTS.md:15`). The patch uses `#pragma GCC optimize("O3")` (`patches/ps2recomp-runtime-env.patch:824`
   in `gs_cpu_backend.cpp`, `:1361` in `ps2_vu1_core.cpp`). MSVC ignores it (C4068), so the
   ~10% VU1 gain reported in `docs/performance.md` ("Real gains" item 4) would be lost.
5. **No compiler on PATH.** CMake/Ninja need a VS Developer shell (`vcvars64.bat`), or clang
   has to be installed. Choosing the toolchain is up to the user.
6. **Scripts need tools that are missing on Windows.** `bind.sh:15-16` uses `rsync` (missing);
   the regenerate workflow in `AGENTS.md:26` depends on `rsync -rc` for 26k files.
   `bind.sh:5`, `diag.sh:4` call `python3` (Store stub here); `rpc_table.py:1` has the shebang
   `#!/usr/bin/env python3 -I` (passing an argument through `env` like this does not work on Linux either without `-S`).
7. **The runtime patch has never been applied on Windows.** It is pinned to PS2Recomp `2c5fbb9`
   (`setup.sh:16`, `AGENTS.md:10`) and was checked out with CRLF line endings (see 9). Whether
   `git apply` works on a Windows clone, and whether the patched code compiles with MSVC, is NOT TESTED.

### P2

8. **`CLAUDE.md` is a broken symlink on Windows.** It is mode `120000` in git (`git ls-files -s`)
   but `core.symlinks=false`, so the file in the working tree is the 9-byte text `AGENTS.md`.
   Any tool that reads `CLAUDE.md` gets only that word unless it follows the reference.
9. **No `.gitattributes`; everything was checked out with CRLF line endings** (`core.autocrlf=true`): `setup.sh`,
   `run.sh`, `bind.sh`, `diag.sh`, `rpc_table.py`, `.gitignore`, the patch and the Java script
   (`file` says "with CRLF line terminators"). Git Bash here ignores the `\r`; a test CRLF script
   with `set -euo pipefail` ran (exit 0). WSL/Linux bash would fail on `pipefail\r`. Suggested:
   `*.sh text eol=lf`, `*.py text eol=lf`, `*.patch -text`.
10. **AGENTS.md describes the Linux machine.** `/opt/ghidra/support/analyzeHeadless` and
    `~/.config/ghidra/ghidra_12.1.2_DEV/Extensions` (`AGENTS.md:52-54`); here they are
    `C:\Tools\ghidra_12.1.4_PUBLIC\support\analyzeHeadless.bat` and
    `%APPDATA%\ghidra\ghidra_12.1.4_PUBLIC\Extensions`. Also `grim` (`AGENTS.md:63`), "~7 GB RAM,
    -j4" (`AGENTS.md:15`), "native Linux x86" (`AGENTS.md:3`, `README.md:4`). The Ghidra project
    was made with 12.1.2_DEV; a project made with 12.1.4 is a new project, not a copy.
11. **No Windows baseline.** `docs/performance.md` numbers come from the Linux `out/fast` build on another
    machine. No build exists here, so there is no frame, speed or crash measurement for
    Windows yet. None was made up.

### P3

12. **Game addresses in versioned scripts.** `rpc_table.py:2` names the BindRpc/CallRpc
    addresses in its docstring and `rpc_table.py:17,22,26` and `diag.sh:24` match on them.
    `AGENTS.md:9` says never to commit address lists. The README itself lists no game addresses (`README.md` "Legal").
    These are two SDK entry points, not a list, but the user should decide.
13. **`overrides/` is an empty folder** in the working tree (git does not track empty folders); nothing
    refers to it.
14. **CMake 4.5.0-rc1** is a release candidate; older `cmake_minimum_required` values
    in PS2Recomp's dependencies may fail on CMake 4.x. NOT TESTED.

### P2 (Windows baseline flags, found in A.2)

15. **`ReleaseMode.cmake` uses `/arch:AVX2`, breaking the portable baseline.**
    `ps2xRuntime/cmake/ReleaseMode.cmake:20` adds `/arch:AVX2` (and `/GL`, `/Qspectre-`)
    for every `MSVC` build — and clang-cl also sets `MSVC=true`, so this applies to both
    Windows compilers. AVX2 excludes CPUs without it (pre-2013 Intel, pre-2015 AMD); the
    baseline build must not assume it. Do not edit upstream: configure the first baseline
    as `Debug` with explicit `/O2` flags (below), which bypasses `EnableFastReleaseMode`
    (it is Release/RelWithDebInfo-only).
16. **`ReleaseMode.cmake` uses `/fp:fast`, which may change PS2 float semantics.**
    `ps2xRuntime/cmake/ReleaseMode.cmake:18`. `/fp:fast` allows contraction, reordering
    and flushing of denormals; the Emotion Engine FPU/COP1 has its own rounding and
    denormal behaviour, so `fast` math on the GS/VU1/float paths can diverge from the
    Linux `out/fast` reference. The baseline uses `/fp:precise` (the MSVC/clang-cl
    default) by simply not adding `/fp:fast`.
17. **clang-cl rejects upstream's `/Qspectre-`.** First build error:
    `clang-cl: error: no such file or directory: '/Qspectre-'; did you mean '/Qspectre'?`
    (`ReleaseMode.cmake:22`). MSVC accepts `/Qspectre-`; clang-cl 23.1.3 does not. This is
    a second reason (besides AVX2/`/fp:fast`) the baseline cannot use
    `EnableFastReleaseMode` unmodified.

**A.2 baseline flags actually used** (Debug build type so `EnableFastReleaseMode` does
not run, then explicit optimization): `CMAKE_BUILD_TYPE=Debug`,
`CMAKE_C_FLAGS_DEBUG = CMAKE_CXX_FLAGS_DEBUG = /O2 /Ob2 /Oi /GF /Gy /DNDEBUG /Z7 -msse4.1`.
`/O2 /Ob2 /Oi` = speed, aggressive inlining, intrinsics; `/GF /Gy` = string pooling and
function-level linking; `/DNDEBUG` = no asserts; `/Z7` = debug info in the .obj;
`-msse4.1` = the runtime's documented floor (AGENTS.md:15 "the runtime needs at least
SSE4.1"; the generated code uses `_mm_blendv_ps`). No `/arch:AVX2` (SSE4.1 is the floor,
not AVX2), no `/fp:fast` (so `/fp:precise`), no `/GL`/LTO.

**SSE4.1 spelling.** MSVC `cl` takes `/arch:SSE4.1`, but **clang-cl ignores it**
(`warning: ignoring invalid /arch: argument 'SSE4.1'; for 64-bit expected one of AVX,
AVX2, ...`) — verified: a `_mm_blendv_ps` compile fails under clang-cl `/arch:SSE4.1`.
clang-cl needs **`-msse4.1`** (verified accepted). So the baseline uses `-msse4.1`,
which clang-cl accepts and MSVC-cl also tolerates; do not write `/arch:SSE4.1` for this
toolchain.
The two hot translation units (`gs_cpu_backend.cpp`, `ps2_vu1_core.cpp`) get
`/O2;/Ob2;/Oi` via a per-file `set_source_files_properties` in `ps2xRuntime/CMakeLists.txt`
(our patched file, not upstream's ReleaseMode), replacing the ignored
`#pragma GCC optimize("O3")`.

---

# Phase A.2 results (2026-10-20, branch `phase-a2-build`)

- **A.2.1 Dependencies.** Every `CMakeLists.txt` read. On `WIN32` the runtime and
  recompiler need **no system packages**: raylib/imgui/rlImGui via FetchContent, FFmpeg
  via a prebuilt-MSVC-DLL ExternalProject (`ps2xRuntime/CMakeLists.txt:256-340`), and
  elfio/toml11/fmt/libdwarf/rabbitizer via FetchContent in `ps2xRecomp`. SDL2, Vulkan,
  glslang and pkg-config are **not** referenced on the Windows path (they are Arch-only
  in `setup.sh`). Nothing was installed; no sccache.
- **A.2.2 Scripts.** `tools/syncgen.py` replaces `rsync -rc` (SHA-256 compare, preserves
  mtimes of identical files); `tools/test_syncgen.py` passes 6/6. `bind.sh`/`diag.sh`/
  `rpc_table.py` prefer `python`, fall back to `python3` (Linux-safe).
- **A.2.3 Patch.** `ps2recomp-runtime-env.patch` applies cleanly to a clean `2c5fbb9`.
  Both `#pragma GCC optimize("O3")` lines removed; per-file `/O2;/Ob2;/Oi` added under
  `if(MSVC)` in the patched `ps2xRuntime/CMakeLists.txt`.
- **A.2.4 Build.** Toolchain: clang-cl 23.1.3, CMake 4.5.0-rc1, Ninja 1.13.2, MSVC env
  from vcvars64. Two real failures then success:
  1. clang-cl without the MSVC env: link step fails, `rc` not found (needs vcvars64).
  2. Release build type: `clang-cl: error: no such file or directory: '/Qspectre-'`
     from upstream `ReleaseMode.cmake:22` (item 17) — plus AVX2/`/fp:fast` (items 15-16).
  Fixed by configuring `Debug` + explicit `/O2 /Ob2 /Oi /GF /Gy /DNDEBUG /Z7` (bypasses
  `EnableFastReleaseMode`; no upstream edit). `ps2_recomp.exe` built:
  `PS2Recomp/out/build/ps2xRecomp/ps2_recomp.exe`, 3,453,440 bytes, prints usage.
  libdwarf warns ZLIB/zstd not found — optional decompression, non-fatal.
- **A.2.5 Generation determinism.** `config/` produced by `ExportPS2Functions.java`
  against the DDGhidraProj project: **5091 functions + 21084 executable labels = 26175
  CSV records** (`functions.csv` starts at `entry,0x0010A008`, the ELF entry). Ran
  `ps2_recomp` twice into `config/genA` and `config/genB` (two configs differing only in
  the `output` key): **26,178 files each, identical name sets, all SHA-256 hashes
  identical → generation is deterministic/reproducible.** (26175 functions + 3
  runner/registry files.) The game runner was **not** built or run.

`config.toml` as exported uses absolute paths with backslashes for `input`/`output`/
`ghidra_output`; making them relative/portable is a pending cleanup (not required for
the build to work).


## Proposed `.gitignore` change (not applied, waiting for approval)

```diff
 # Game data and anything derived from it: never commit.
 /game/
 /PS2 BIOS/
 /Downhill Domination (USA)/
 /config/
 /ghidra/
 /mc0/
 /mc1/
+# Disc images, ELF and BIOS anywhere in the tree (any name or case on Windows).
+*.iso
+*.bin
+*.cue
+*.img
+*.chd
+*.cso
+*.elf
+SCUS_*
+SLUS_*
+SCES_*
+SLES_*
+*.rom
+*.rom0
+*.erom
+*.nvm
+*.mec
+# Ghidra projects, RAM dumps and generated code anywhere.
+*.gpr
+*.rep/
+*.ram
+/out/
+/build/
```

The extension rules have no leading `/` on purpose (they are file patterns, not folders, so
they cannot hide `tools/ghidra/` the way the old unanchored folder rule did, `AGENTS.md:11`).
`core.ignorecase=true` makes them case-insensitive on this machine; on Linux, `*.ISO`
would need its own line.

---

# Phase A.1 results (2026-10-20, same branch, commit `f0d6ade`)

## A.1.1 Compiler toolchain

Installed compilers on this machine, and whether each honors `#pragma GCC optimize`
(the patch uses it at `ps2recomp-runtime-env.patch:824` and `:1361`):

| Compiler | Present | `#pragma GCC optimize` |
| --- | --- | --- |
| MSYS2 ucrt64 GCC | **No** (`C:\msys64` absent, no `pacman`) | Would honor it (it is GCC) |
| clang-cl 23.1.3 (`C:\Program Files\LLVM\bin`) | Yes | **Ignored**: `warning: unknown pragma ignored [-Wunknown-pragmas]` |
| MSVC cl 19.51.36260 (VS 18, via vcvars64) | Yes | **Ignored**: `warning C4068: unknown pragma 'GCC'` |

Evidence (compiled `pragma_test.cpp`, temp dir, since deleted): a float
multiply-accumulate loop marked `#pragma GCC optimize("O3")` compiles to a scalar,
unvectorized loop at `/Od` on **both** clang-cl and MSVC (1 `mulss`, no SIMD),
identical to plain `/Od`; at `/O2` the same function unrolls to 5 multiplies. So the
pragma is a no-op on both Windows compilers and the ~10% VU1 gain from
`docs/performance.md` ("Real gains" item 4) would be lost. The patch contains no other
GCC-isms (`grep -cE '__attribute__|#pragma GCC|__builtin_'` = the 2 pragmas only).

**Chosen for A.2: clang-cl** (installed, MSVC ABI). The two pragmas must be replaced by a
compiler-agnostic per-file CMake compile option regardless of compiler choice.

## A.1.2 PS2Recomp clone and patch check

- Cloned `github.com/ran-j/PS2Recomp` into ignored `/PS2Recomp/`, checked out `2c5fbb9`
  ("Dispatch syscalls 0x79/0x7A… (#274)").
- `git -C PS2Recomp apply --check ../patches/ps2recomp-runtime-env.patch` → **exit 0**,
  applies cleanly: 19 files, +550/−63. Clean **despite `core.autocrlf=true`** on the
  clone, so P1.7's "does `git apply` work on a Windows clone" is answered: yes.

## A.1.3 Ghidra headless import and export

- Extension `ghidra-emotionengine-reloaded` `extension.properties` says `version=12.1.4`,
  an exact match for Ghidra 12.1.4 (no conflict). `data/languages/emotionengine.ldefs`
  provides `r5900:LE:32:default` (processor `MIPS-R5900`, variant `PS2`).
- Imported `game/SCUS_971.77` into a project **outside the repo**
  (`%TEMP%\DDGhidraProj\DownhillDom`) with `analyzeHeadless.bat … -import … -processor
  r5900:LE:32:default`. Exit 0 in ~76 s. Log: `REPORT: Analysis succeeded`, `Import
  succeeded`. Only benign warnings: DVP overlay blocks skipped, one `rom0` language
  memory-block conflict.
- Ran `tools/ghidra/DecompileFunctions.java` headless (`-process SCUS_971.77 -noanalysis
  -readOnly`). The ELF header gives `e_entry = 0x0010a008` (`od -j 24`, bytes `08 a0 10
  00`); decompiling that address produced real output (`ghidra/entry_decompile.c`,
  ignored): `void entry(void)` with a BSS-clear loop, `syscall(0x3c/0x3d)`, `FlushCache`,
  `EI()`, callers `Entry Point`/`_elfHeader::00000018`, callees `FUN_0025f0a0`,
  `FUN_0025f298`, `FUN_001b6708`, `FlushCache`. (An initial guess of `0x100000`
  correctly returned `// no function`; only header-derived addresses were used.)

Nothing was built or run in A.1.

## Runtime progress update (2026-10-21)

The latest rebuild completed successfully and produced
`PS2Recomp/out/build/ps2xRuntime/ps2EntryRunner.exe` (the build log ends at the
final link step in `analysis/build-cd-completion.log`). The current executable
has been smoke-tested far enough to establish the following runtime evidence:

- The game boots and consistently renders title/menu content at 640x448.
- PADMAN and the physical PAD RPC clients initialize, pad areas register, and
  the runtime observes stable button transitions (`0xffff` released and
  `0xbff7` for the automated Cross+Start press).
- CD search locates `SKAT/DHSKAT.SKX`, reporting size `101288144` and LBN
  `1048576`; the guest also reaches the associated resource/audio setup.
- No fatal loader or unhandled-RPC error has been observed in this path.

The current blocker is a guest initialization wait at PC `0x201f08`, the
return point after `FlushCache`. The guest repeatedly polls its asynchronous
state and does not progress to the menu/input flow far enough to exercise the
memory-card requests or a race. The CD read path is observable: SID
`0x80000595`, RPC function `0x01`, invokes callback `0x246cd0` with parameter
`0x280900` and a read request ending at callback address `0x246cd0`.

A narrowly scoped runtime patch attempted to update the completion record for
that SID/function. The rebuilt regression still stayed at `0x201f08`, and no
write to the intended completion state was observed. Therefore that patch is
not considered proven; the correct callback record/layout and completion
protocol must be established from the guest call sites before any further
completion write is added. Memory-card `GetInfo`/`GetDir` support remains
implemented but has not yet been runtime-verified because execution has not
reached those requests.

### CD completion follow-up

Further bounded tracing established why the first completion attempt failed:
the HLE callback ran before the guest published its async record. The deferred
completion now waits until the guest initializes the table at `0x279428`
(`0x4ccb00`), then completes the matching slot and active record. The guest
poll subsequently sees the matching object and ready bit. A focused rebuild
and regression verified that execution now leaves `0x201f08` and reaches the
next loop at `0x201f00`/`0x201f14`.

The remaining blocker has therefore moved forward to the state checked after
the CD poll; no memory-card request has appeared in this run yet. The exact
state field at that new wait is being traced before making another change.

### Resource-loading regression update (2026-10-22)

The follow-up executable was rebuilt successfully with Ninja and regression
tested. The completed CD record now allows the guest to pass the original
`0x201f08` wait and reach `0x201fc8`. The run performs 82 CD sector reads,
including the `DHSKAT.SKX` resource and its subsequent chunks, with no fatal
loader or unhandled-RPC error observed.

The game has not yet reached memory-card traffic, menu activation, or a race.
The current blocker is a later asynchronous resource-processing loop at
`0x201fc8`; the first CD completion is verified, but the second resource-state
protocol is not yet resolved. PAD registration and button-state transitions
remain observed at the transport level only.

The latest 35-second regression (`analysis/branchfix-regression.*`) confirms
that this is a stable loop, not a crash: the executable remains alive, keeps
rendering the 640x448 frame, and has already issued the expected resource CD
reads. No `[MC] GetInfo`/`GetDir` request or menu activation was observed in
that run. The remaining work is to identify the second resource completion
record and retire it through the guest's real state machine before testing
memory-card flow and physical menu control.

### MCSERV handshake and input-area regression (2026-10-22)

Retail decompilation of `FUN_00245E78` established the exact version checks in
the shipped game: `0x760784 < 0x20A` reports the MCSERV error and
`0x760788 < 0x20E` reports the MCMAN error. The public PS2SDK checks use lower
minimums (`0x205`/`0x206`), but those values are rejected by this retail
client. The HLE response was changed to `0x020A`/`0x020E`.

The rebuilt executable passed the regression: the MCSERV init trace shows
`(0, 0x20A, 0x20E)`, the old-release message is absent, and the real guest
path invokes `[MC] GetInfo` twice with `port=0`, `type=2`, `free=8192`,
`format=1`, and result `0`. No `[MC] GetDir` request has occurred yet.

The same run confirms that the PAD DMA areas are refreshed with guest-visible
active-low transitions (`0xFFFF`, `0xFFF7`, `0xBFFF`, `0xBFF7`), including the
bounded automated Cross/Start pulses. This proves transport and area updates,
but menu selection and new-game activation are not yet verified. The current
runtime remains in the title/resource presentation path after the CD loader
completion; no race has started.

### Digital PAD protocol regression (2026-10-22)

The live IOP DMA path was found to report controller ID `0x73` even though the
retail `padPortOpen` path opens controllers in digital mode. The runtime HLE
already documented the corresponding digital ID as `0x41`; the mismatch could
make the retail guest report the controller as disconnected despite valid
active-low button bytes. `PS2Recomp/ps2xRuntime/src/lib/ps2_pad.cpp` now emits
the protocol-correct digital marker `0x41` for the shared PAD backend.

The affected target rebuilt successfully with Ninja after restoring the Windows
SDK `rc.exe` directory to `PATH`:
`analysis/build-digital-pad-20261022.log` and
`analysis/build-digital-pad-20261022.exit` (`BUILD_EXIT=0`). The fresh
`PS2Recomp/out/build/ps2xRuntime/ps2EntryRunner.exe` was run from the project
directory. The regression still shows active Cross transitions (`0xBFFF`) and
stable rendering, but it produced no `[MC] GetDir` request and no evidence of
menu selection or new-game activation. Thus the digital-ID fix is implemented,
built, and transport-verified, but the title-to-menu transition remains
unverified and the game is not playable yet.

### PAD DMA metadata regression (2026-10-22)

The PS2SDK `pad_data_new` definition was checked against the live HLE layout.
The existing offsets are correct: `frame=88`, `length=96`,
`buttonDataReady=103`, `state=112`, and `reqState=113`. The missing protocol
field was `currentTask` at offset `114`; PS2SDK's `padInfoMode()` and
`padInfoAct()` reject a stable new-format packet unless this field is `1`.
The IOP refresh now also publishes `modeCurId=0x41` and digital model `4`, and
uses `0x41` for the fallback packet ID.

The resulting executable was rebuilt with Ninja successfully:
`analysis/build-pad-metadata-20261022.exit` (`BUILD_EXIT=0`). The focused
20-second run is `analysis/pad-metadata-run-20261022.err/.out`. It confirms
the MCSERV handshake, both `GetInfo` calls, CD search/stream reads, and active
Start/Cross transitions, but still produces no `GetDir` request or menu
activation. The process remains alive and renders 640x448 frames. The trace
also establishes that the guest's actual pad open requests use SID `0` with
the `{command=1, port, slot, 1, padArea}` shape for eight areas; no later PAD
RPC is observed. The next blocker is therefore the guest-side direct DMA
consumer or the presentation-state transition, not an unimplemented PAD RPC.

### Full-build visual regression follow-up (2026-10-22)

The configured full Ninja target `PS2Recomp/out/build` was used. An initial
link attempt failed only because Windows `rc.exe` was absent from `PATH`; after
adding the Windows SDK resource compiler directory, the target linked
successfully. The fresh executable is
`PS2Recomp/out/build/ps2xRuntime/ps2EntryRunner.exe`.

The current executable reproduces the reported visual regression: it remains
alive, uploads 640x448 frames, and reaches the shell loop at PCs `0x1EC2A8`
and `0x223EBC`, but no `GetDir`, menu activation, or race occurs. The frame
source is consistently reported as `displayFbp=70`, `sourceFbp=70`, with
`preferred=0`; this is not evidence of CRT2 selection. Bounded frame statistics
show 143,360 non-black pixels, top-left `(0,0,0)`, and center/bottom samples
`(28,28,28)`, confirming a uniform gray shell frame rather than the magenta
fallback.

An A/B run with `PS2X_BINDS` empty stalls earlier at the SIF startup loop, so
the normal binds are still required to reach this shell state. Automated
Cross/Start pulses continue to update PAD areas, but tracing the known writers
of guest flag `0x29DFB4` has not shown a transition into the writer paths;
input transport is implemented but menu consumption remains unverified. The
next investigation is the guest shell state/input consumer and the GIF/GS path
that produces the gray framebuffer, without changing the presenter
speculatively.

