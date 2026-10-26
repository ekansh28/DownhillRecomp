// ===== FUN_00245230 @ 00245230 =====
// callers: FUN_0021fad0
// callees: FUN_00245150
// strings: 

char FUN_00245230(undefined8 param_1,int param_2)

{
  char cVar1;
  int iVar2;
  
  cVar1 = 'c';
  if ((&DAT_0075ede0)[(int)param_1 * 0x1c + param_2 * 7] != 0) {
    iVar2 = FUN_00245150(param_1);
    cVar1 = *(char *)(iVar2 + 0x70);
    if (cVar1 == '\x06') {
      if (*(char *)(iVar2 + 0x71) == '\x02') {
        cVar1 = '\x05';
      }
      else {
        cVar1 = *(char *)(iVar2 + 0x70);
      }
    }
  }
  return cVar1;
}


