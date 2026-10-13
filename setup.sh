#!/usr/bin/env bash
# Instala dependências, extrai o ELF da ISO e compila o PS2Recomp.
set -euo pipefail
cd "$(dirname "$0")"

ISO="Downhill Domination (USA)/Downhill Domination (USA).iso"
ELF=SCUS_971.77

sudo pacman -S --needed base-devel git cmake ninja clang python 7zip ghidra sdl2 vulkan-headers glslang

# o runtime lê módulos IRX e dados do disco a partir desta pasta
[ -f "game/$ELF" ] || 7z x -y -ogame "$ISO"

if [ ! -d PS2Recomp ]; then
  git clone --recurse-submodules https://github.com/ran-j/PS2Recomp
  git -C PS2Recomp checkout -q 2c5fbb9   # commit em que patches/ aplica limpo
  git -C PS2Recomp apply ../patches/ps2recomp-runtime-env.patch  # PS2X_CD_IMAGE e PS2X_BINDS
fi
cmake -S PS2Recomp -B PS2Recomp/out/build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS=-march=native
cmake --build PS2Recomp/out/build
