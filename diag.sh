#!/usr/bin/env bash
# Resume a última execução (run.log + ps2_log.txt): onde parou e por quê. Uso: ./diag.sh
cd "$(dirname "$0")"
python3 -I - <<'PY'
import re,collections,os
fns=[]
if os.path.exists('ps2_log.txt'):
    for l in open('ps2_log.txt',errors='replace'):
        m=re.match(r'\s*>> (\S+) enter',l)
        if m: fns.append(m.group(1))
run=open('run.log',errors='replace').read().splitlines()
print(f'== chamadas registradas: {len(fns)}')
c=collections.Counter(fns)
print('== mais chamadas:',', '.join(f'{k}x{v}' for k,v in c.most_common(4)))
print('== últimas funções:',' > '.join(dict.fromkeys(fns[-12:])))
# bind RPC em laço: último SID usado por um BindRpc recompilado
hot=[f for f,_ in c.most_common(6)]
for f in hot:
    m=re.search(r'_0x([0-9a-f]+)$',f)
    if not m: continue
    path=[p for p in os.listdir('config/output') if p.endswith(f'_0x{m.group(1)}.cpp')]
    if path:
        s=open('config/output/'+path[0]).read()
        if 'func_25CDB8' in s:
            sid=re.search(r'ori\s+\$a1, \$a1, (0x[0-9A-Fa-f]+)',s)
            print(f'== laço de BindRpc em {f}: SID 0x8000{int(sid.group(1),16):04x}' if sid else f'== laço de BindRpc em {f}')
            break
pat=re.compile(r'missing-target|unresolved|TODO|not implemented|unimplemented|Unhandled|SearchFile\]|abort|SIGSEGV|exception',re.I)
seen=set()
print('== avisos do runtime:')
for l in run:
    if pat.search(l) and 'frame:upload' not in l:
        k=re.sub(r'0x[0-9a-f]+','N',l)[:80]
        if k not in seen:
            seen.add(k); print('  ',l[:200])
        if len(seen)>=12: break
ticks=[l for l in run if l.startswith('[run:tick]')]
if ticks: print('== último tick:',ticks[-1][:160])
PY
