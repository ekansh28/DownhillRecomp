This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

Static recompilation of *Downhill Domination* (PS2, USA, `SCUS_971.77`) to native Linux x86 on top of [PS2Recomp](https://github.com/ran-j/PS2Recomp). Progress and roadmap live in `README.md`; do not duplicate them here. The user writes in Portuguese; scripts are commented in Portuguese, the README in English.

## What is and is not in this repo

Only our own work is versioned: `setup.sh`, `run.sh`, `bind.sh`, `diag.sh`, `rpc_table.py`, `tools/ghidra/`, `patches/`, docs. Everything else is local and git-ignored by root-anchored rules: `PS2Recomp/` (third-party clone), `game/` (extracted ISO), `config/` (Ghidra export, generated code, `binds.txt`), `ghidra/` (Ghidra project), BIOS, ISO, logs.

- **Never commit anything derived from the game**: decompiled C, `functions.csv`, generated `.cpp`, address lists. The README deliberately lists no game addresses.
- **Edits inside `PS2Recomp/` are lost unless exported** to `patches/ps2recomp-runtime-env.patch`. The patch is pinned to PS2Recomp commit `2c5fbb9` and `setup.sh` applies it. Regenerate it with `git -C PS2Recomp diff -- <only the source files you changed> > patches/ps2recomp-runtime-env.patch`, then check it applies to a clean checkout of that commit (`git apply --check` in a scratch dir). Never include `ps2xRuntime/src/runner/*` (that is generated output; `register_functions.cpp` shows as modified for that reason).
- Keep `.gitignore` rules anchored with a leading `/`. An unanchored `ghidra/` once silently ignored `tools/ghidra/`.

## Builds

Three CMake build dirs under `PS2Recomp/out/`, all Ninja, all configured with `-march=native` (the runtime needs SSE4; gcc does not enable it by default). The machine has ~7 GB RAM, so use `-j4`; the game is ~26k generated functions built as unity batches.

| Dir | Purpose | Notes |
| --- | --- | --- |
| `out/build` | Release; builds the `ps2_recomp` tool | LTO makes a full build ~14 min; only needed for the tool |
| `out/dev` | `-O1`, no LTO, aggressive logging on | incremental ~5 s when only runtime sources change; a generated-code change recompiles unity batches (~7 min). Writes `ps2_log.txt` at ~100 MB/min. |
| `out/fast` | `-O2`, `PS2X_ENABLE_AGRESSIVE_LOGS=OFF` | what to use to actually run/look at the game |

    cmake --build PS2Recomp/out/dev --target ps2EntryRunner -j4     # or out/fast
    ./run.sh [secs]            # runs out/dev; BUILD=fast ./run.sh uses out/fast
    ./diag.sh                  # summarises the last run (hot functions, failing RPC bind, warnings)
    ./bind.sh name@0xADDR ...  # slow path: edit config.toml stubs, regenerate, rsync, rebuild dev

Regenerating code: `PS2Recomp/out/build/ps2xRecomp/ps2_recomp config/config.toml` writes `config/output/`; copy it into `PS2Recomp/ps2xRuntime/src/runner` (`.cpp`) and `include` (`.h`) with **`rsync -rc`** (not `cp`: 26k files exceed the argument limit, and checksum copy avoids touching mtimes and rebuilding everything). Unit tests exist (`PS2Recomp/ps2xTest`, `ps2xIOP/tests` with `-DPS2X_IOP_BUILD_TESTS=ON`) but are not part of the daily loop.

## How the pieces fit

The ELF is retail with no symbols. Ghidra's `ExportPS2Functions.java` finds only the syscall wrappers and function boundaries; the **SDK libraries (libsif, libcdvd, fio, libmc, libpad, libmpeg, the sound lib) are ordinary game code** that talks RPC to an IOP the runtime does not fully have. Each such function must be rebound to a runtime HLE stub (`ps2_stubs::sceXxx`, listed in `ps2xRuntime/include/ps2_call_list.h`) or to `ret0`/`ret1`.

Two ways to bind, and they differ:
- `config/config.toml` `stubs = ["name@0xADDR"]`: baked into generated code (needs regenerate + rebuild).
- `config/binds.txt` (`handler@0xADDR`, `#` comments), read at ELF load through `PS2X_BINDS` and applied with `replaceFunction`: takes effect on the next run with no rebuild. Prefer this. It works for every caller because generated code calls through `runtime->dispatchGuestBranch` and the function table, never directly.

Other things that need several files to see:
- Generated naming: `FUN_<addr>_0x<addr>` is a Ghidra function; `entry_*`/`caseD_*` are fragments of the function that precedes them. `config/functions.csv` is `name,start,end,size`; to find a fragment's owner, walk back to the nearest non-`entry_`/`caseD_` row.
- `ps2_log.txt` only records functions that run as recompiled code. **A function bound by address is not logged**, so a count of 0 for it means nothing. Use `PS2X_TRACE_CALLS` for those.
- A stub that blocks the thread (`waitVSync`, `waitExternal`) must set `ctx->pc = $ra` first. Generated wrappers do it; a stub entered through `replaceFunction` has `pc` = its own address and would resume in the wrong place.
- Runtime layout (all under `PS2Recomp/ps2xRuntime/src/lib`): `Kernel/EeScheduler.cpp` (guest threads, alarms, VBlank; interrupt handlers run as "invocations" in the priority-0 queue), `Kernel/Syscalls` (kernel syscalls), `Kernel/Stubs` (HLE of SDK calls: CD, MC, pad, MPEG, FileIO), `gs/` (software GS rasteriser), VU1 interpreter, `ps2_runtime.cpp` (loader, IOP glue, game-override hook). `PS2Recomp/ps2xIOP` emulates the IOP: it loads the game's real `.IRX` files on an R3000 interpreter; HLE only exists for MCSERV, LIBSD and DBCMAN, and a physical IRX that registers an RPC SID wins over HLE.
- The IOP `cdrom0:` root is the folder of the ELF (`game/`), so the whole ISO must be extracted there, and raw sector reads need `PS2X_CD_IMAGE`.
- Threads/priority follow the real BIOS: main thread priority 1, `CreateThread` accepts priority 0. Do not "fix" priority 0 back to invalid.

## Debug environment variables

All come from our runtime patch: `PS2X_BINDS`, `PS2X_CD_IMAGE`, `PS2X_TRACE_CALLS=0xA,0xB` (args of calls to those guest addresses, first 400), `PS2X_TRACE_SYSCALLS=1` (thread/semaphore/interrupt syscalls, first 3000), `PS2X_DUMP_RAM="secs:path"` (32 MB EE RAM; compare strings/state offline). `run.sh` already exports the first two.

## Identifying game functions

Do not read raw MIPS when you can avoid it. Export C with the headless decompile script (the Ghidra project is `ghidra/DownhillDom`, language `r5900:LE:32:default`, needs the Emotion Engine extension from `~/.config/ghidra/ghidra_12.1.2_DEV/Extensions`):

    /opt/ghidra/support/analyzeHeadless ghidra DownhillDom -process SCUS_971.77 -noanalysis -readOnly \
      -scriptPath tools/ghidra -postScript DecompileFunctions.java 0xADDR,0xADDR out.c

Run it from the repo root. `ExportPS2Functions.java` in headless mode reads its two output paths from a `.properties` file named after the script whose keys are `<dialog title> Save` with unescaped spaces.

Useful identification signals: the RPC SID a function binds and the function number it sends (`rpc_table.py`; e.g. the FILEIO functions send 1/2/3/4 for close/read/write/lseek, CD stream commands are 1 start, 2 read, 3 stop, 5 init), argument shape, and string references. State your confidence in the `binds.txt` comment. The installed PCSX2 (BIOS in `PS2 BIOS/`, use a USA 1.90) is the ground truth: its debugger Threads tab and memory-write breakpoints settle behaviour questions that guessing would not.

## Working with the user

- Screen captures: `grim` captures the *composited* screen, so another window can be included. Ask the user for screenshots instead of capturing their desktop; if a capture is ever taken, delete it.
- Long builds/runs: run them in the background and check; the game window is titled `PS2-Recomp | SCUS_971.77`.
- Commits are grouped by logical change; the runtime patch, scripts and docs are committed separately.
