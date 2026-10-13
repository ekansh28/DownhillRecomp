# Downhill Domination Recomp

Static recompilation of *Downhill Domination* (PS2, USA, SCUS-971.77) to native
Linux x86, built on [PS2Recomp](https://github.com/ran-j/PS2Recomp).

**Status:** early work in progress. Nothing is playable yet.

## Legal

This repository contains no game assets, ELF, or BIOS. You must supply your
own legally obtained dump of the game.

## Setup

    ./setup.sh

Put your ISO at `Downhill Domination (USA)/Downhill Domination (USA).iso`.
The script installs dependencies (Arch/pacman), extracts the ELF to `game/`
and builds PS2Recomp.

## Workflow

The ELF is retail and has no symbols, so game-side SDK functions (libsif,
libcdvd, fio) must be bound to the runtime's HLE stubs by address.

1. Analyse `game/SCUS_971.77` in Ghidra (Emotion Engine extension) and export
   `config/config.toml` + `config/functions.csv` with
   `PS2Recomp/ps2xRecomp/tools/ghidra/ExportPS2Functions.java`.
2. `ps2_recomp config/config.toml`, copy the output into
   `PS2Recomp/ps2xRuntime/src/runner` and `include`, and build.
3. Iterate: add `handler@0xADDR` lines to `config/binds.txt` and run
   `./run.sh`. No regeneration or rebuild is needed (runtime patch
   `patches/ps2recomp-runtime-env.patch`, env `PS2X_BINDS`). `./diag.sh`
   summarises where the last run stopped; `BUILD=fast ./run.sh` uses the build
   without function tracing.

`bind.sh` is the slow path (edits `config.toml` stubs, regenerates, rebuilds).
`rpc_table.py` lists the game functions that use IOP RPC (SID and function
number) to help identify SDK functions.

## License

GPL-3.0, matching PS2Recomp (the generated code links against its runtime).
