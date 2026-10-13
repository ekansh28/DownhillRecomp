#!/usr/bin/env python3 -I
"""Tabela de funções do jogo que usam RPC do IOP (BindRpc 0x25CDB8 / CallRpc 0x25CF88).
Uso: python3 -I rpc_table.py > config/rpc_table.txt"""
import re,csv,glob,bisect,collections
rows=sorted((int(r[1],16),int(r[2],16),r[0]) for r in csv.reader(open('config/functions.csv')) if r and r[1].startswith('0x'))
starts=[r[0] for r in rows]
def owner(a):  # função "pai": última não-fragmento que começa em/antes de a
    i=bisect.bisect_right(starts,a)-1
    while i>0 and re.match(r'(entry_|caseD_)',rows[i][2]): i-=1
    return rows[i][0],rows[i][2]
bound=set(int(x,16) for x in re.findall(r'@(0x[0-9A-Fa-f]+)',open('config/config.toml').read()+open('config/binds.txt').read()))
info=collections.defaultdict(lambda:{'sid':set(),'fno':set(),'size':0,'frags':0})
for f in glob.glob('config/output/*_0x*.cpp'):
    m=re.search(r'_0x([0-9a-f]+)\.cpp$',f)
    if not m or 'register' in f: continue
    a=int(m.group(1),16); s=open(f).read()
    if 'func_25CDB8' not in s and 'func_25CF88' not in s: continue
    o,name=owner(a); d=info[o]; d['name']=name; d['frags']+=1
    sz=re.search(r'Address: 0x([0-9a-f]+) - 0x([0-9a-f]+)',s); d['size']+=int(sz.group(2),16)-int(sz.group(1),16)
    ins=re.findall(r'// 0x[0-9a-f]+: 0x[0-9a-f]+\s+(\S+)\s+(.*?)(?: \(Delay Slot\))?$',s,re.M)
    for i,(op,arg) in enumerate(ins):
        if op=='jal' and arg=='func_25CDB8':
            for op2,a2 in ins[max(0,i-6):i+1]:
                m2=re.match(r'\$a1, \$a1, (0x[0-9A-Fa-f]+)',a2)
                if op2=='ori' and m2: d['sid'].add(0x80000000|int(m2.group(1),16))
        if op=='jal' and arg=='func_25CF88':
            for op2,a2 in ins[max(0,i-8):i+1]:
                m2=re.match(r'\$a1, \$zero, (-?0x[0-9A-Fa-f]+|\d+)',a2)
                if op2=='addiu' and m2: d['fno'].add(int(m2.group(1),16 if 'x' in m2.group(1) else 10))
SIDS={0x80000001:'FILEIO',0x80000006:'LOADFILE',0x80000592:'CDVD-init',0x80000593:'CDVD-?',0x80000595:'CDVD-ncmd',0x80000597:'CDVD-scmd'}
print('%-10s %-6s %-5s %-14s %-12s %s'%('endereço','bytes','frag','SID','fno RPC','ligada?'))
for a in sorted(info):
    d=info[a]
    sid=','.join(f"{SIDS.get(x,'?')}:{x:#x}" for x in sorted(d['sid'])) or '-'
    print('%-10s %-6d %-5d %-14s %-12s %s'%(hex(a),d['size'],d['frags'],sid,','.join(map(str,sorted(d['fno']))) or '-', 'sim' if a in bound else ''))
