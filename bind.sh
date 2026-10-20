#!/usr/bin/env bash
# Uso: ./bind.sh nome@0xADDR ...  -> adiciona stubs ao config, regenera, copia e recompila (build rápido).
set -euo pipefail
cd "$(dirname "$0")"
# Prefere "python" (no Windows o "python3" e o stub da Microsoft Store); so usa python3 se nao houver python.
if command -v python >/dev/null 2>&1; then PY=python; else PY=python3; fi
"$PY" - "$@" <<'PY'
import re,sys
p='config/config.toml'; s=open(p).read()
for b in sys.argv[1:]:
    if f'"{b}"' not in s:
        s,n=re.subn(r'^stubs = \[\n',f'stubs = [\n  "{b}",\n',s,count=1,flags=re.M); assert n==1
open(p,'w').write(s)
PY
PS2Recomp/out/build/ps2xRecomp/ps2_recomp config/config.toml 2>&1 | tail -1
R=PS2Recomp/ps2xRuntime
# Copia so os ficheiros que mudaram (hash), preservando mtimes dos iguais; substitui o rsync -rc.
"$PY" -I tools/syncgen.py config/output "$R/src/runner" .cpp
"$PY" -I tools/syncgen.py config/output "$R/include" .h
cmake --build PS2Recomp/out/dev --target ps2EntryRunner -j4 > build-dev.log 2>&1 || { grep -E ' error |FAILED' build-dev.log | head -5; exit 1; }
