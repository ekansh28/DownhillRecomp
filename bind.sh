#!/usr/bin/env bash
# Uso: ./bind.sh nome@0xADDR ...  -> adiciona stubs ao config, regenera, copia e recompila (build rápido).
set -euo pipefail
cd "$(dirname "$0")"
python3 - "$@" <<'PY'
import re,sys
p='config/config.toml'; s=open(p).read()
for b in sys.argv[1:]:
    if f'"{b}"' not in s:
        s,n=re.subn(r'^stubs = \[\n',f'stubs = [\n  "{b}",\n',s,count=1,flags=re.M); assert n==1
open(p,'w').write(s)
PY
PS2Recomp/out/build/ps2xRecomp/ps2_recomp config/config.toml 2>&1 | tail -1
R=PS2Recomp/ps2xRuntime
rsync -rc config/output/ $R/src/runner/ --include='*.cpp' --exclude='*'
rsync -rc config/output/ $R/include/ --include='*.h' --exclude='*'
cmake --build PS2Recomp/out/dev --target ps2EntryRunner -j4 > build-dev.log 2>&1 || { grep -E ' error |FAILED' build-dev.log | head -5; exit 1; }
