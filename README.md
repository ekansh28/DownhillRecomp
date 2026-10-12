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

## Next steps

1. Open `game/SCUS_971.77` in Ghidra and run
   `PS2Recomp/ps2xRecomp/tools/ghidra/ExportPS2Functions.java`.
2. Run `ps2_recomp` with the exported TOML/CSV.
3. Build the generated code against `ps2xRuntime`.

## License

GPL-3.0, matching PS2Recomp (the generated code links against its runtime).
