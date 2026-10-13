# Downhill Domination Recomp

Static recompilation of *Downhill Domination* (PS2, USA, SCUS-971.77) to native
Linux x86, built on [PS2Recomp](https://github.com/ran-j/PS2Recomp).

**Status:** work in progress, not playable. The recompiled game boots, loads
its data from the disc and reaches the front-end menu, but the picture is still
wrong (see [Progress](#progress)).

## Legal

This repository contains no game assets, ELF, BIOS or anything derived from
them (the Ghidra project, function lists and generated code stay local and are
git-ignored). You must supply your own legally obtained dump of the game.

## Setup

    ./setup.sh

Put your ISO at `Downhill Domination (USA)/Downhill Domination (USA).iso`.
The script installs dependencies (Arch/pacman), extracts the disc to `game/`,
clones PS2Recomp at a pinned commit, applies `patches/ps2recomp-runtime-env.patch`
and builds it.

## Progress

Done (the game runs on the PS2Recomp runtime):

- Boot, SIF commands and RPC, CD initialisation, IOP reset and module loading
  from the disc.
- Disc reads and file I/O, CD streaming, memory card (host folder), pad
  initialisation.
- Front-end menu reached; the per-frame render thread draws through VU1 and the
  GS.

Not working yet:

- **Picture:** polygons come out untextured and with wrong geometry, at about 1
  frame per second (software rasteriser).
- **Intro movie:** skipped. The game feeds the IPU by DMA, which the runtime does
  not emulate.
- **Sound:** disabled at the EE level. The game's sound IOP module cannot read
  the disc inside the emulated IOP.
- Input is not verified past the boot screens.

## Workflow

The ELF is retail and has no symbols, so the game's SDK functions (libsif,
libcdvd, fio, memory card, pad, mpeg) run as ordinary recompiled code waiting
for a real IOP. Each one is bound to a runtime HLE stub by address.

1. Analyse `game/SCUS_971.77` in Ghidra (Emotion Engine extension) and export
   `config/config.toml` + `config/functions.csv` with
   `PS2Recomp/ps2xRecomp/tools/ghidra/ExportPS2Functions.java`.
2. `ps2_recomp config/config.toml`, copy the output into
   `PS2Recomp/ps2xRuntime/src/runner` and `include`, and build.
3. Iterate with `config/binds.txt`: add `handler@0xADDR` lines (a runtime stub
   name, `ret0` or `ret1`) and run `./run.sh`. No regeneration or rebuild is
   needed.

Scripts:

- `run.sh [secs]` runs the game (`BUILD=fast` selects the build without function tracing).
- `diag.sh` summarises where the last run stopped.
- `bind.sh` is the slow path (edits `config.toml`, regenerates, rebuilds).
- `rpc_table.py` lists game functions that use IOP RPC (SID and function number).
- `tools/ghidra/DecompileFunctions.java` exports C for a list of addresses, much
  easier to read than MIPS:
  `analyzeHeadless ghidra DownhillDom -process SCUS_971.77 -noanalysis -scriptPath tools/ghidra -postScript DecompileFunctions.java 0xADDR,0xADDR out.c`

Runtime patch (`patches/ps2recomp-runtime-env.patch`) adds these environment
variables:

| Variable | Effect |
| --- | --- |
| `PS2X_CD_IMAGE` | ISO used for raw sector reads |
| `PS2X_BINDS` | file of `handler@0xADDR` lines applied at ELF load |
| `PS2X_DUMP_RAM="secs:path"` | writes the 32 MB EE RAM once after that many seconds |
| `PS2X_TRACE_CALLS=0xA,0xB` | logs the first calls to those guest addresses with arguments |
| `PS2X_TRACE_SYSCALLS=1` | logs thread, semaphore and interrupt syscalls |

It also makes the scheduler match the real kernel (main thread at priority 1,
priority 0 accepted by `CreateThread`), makes the simulated `sceCdRead` take one
frame, and batches IOP cycles (the IOP scheduler dominated the profile).
PCSX2 is a useful ground truth: its debugger shows the real thread table and can
break on memory writes.

## Roadmap

1. **Find why the picture is wrong:** compare the first menu frame against PCSX2
   to tell bad VU1 geometry from missing textures.
2. **Fix the GS/VU1 path** (vertices, textures) and its speed.
3. **Replace the temporary shortcuts:** bring back the sound IOP module and the
   intro movie (IPU DMA path).
4. **Make it playable:** confirm input, then run a race end to end.

## License

GPL-3.0, matching PS2Recomp (the generated code links against its runtime).
