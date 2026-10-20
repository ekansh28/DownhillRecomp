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
