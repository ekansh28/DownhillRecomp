#!/usr/bin/env bash
# Instala dependências, extrai o ELF da ISO e compila o PS2Recomp.
set -euo pipefail
cd "$(dirname "$0")"

ISO="Downhill Domination (USA)/Downhill Domination (USA).iso"
ELF=SCUS_971.77

sudo pacman -S --needed base-devel git cmake ninja clang python 7zip ghidra sdl2 vulkan-headers glslang

[ -f "game/$ELF" ] || 7z e -y -ogame "$ISO" "$ELF" SYSTEM.CNF

[ -d PS2Recomp ] || git clone --recurse-submodules https://github.com/ran-j/PS2Recomp
cmake -S PS2Recomp -B PS2Recomp/out/build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS=-march=native
cmake --build PS2Recomp/out/build
