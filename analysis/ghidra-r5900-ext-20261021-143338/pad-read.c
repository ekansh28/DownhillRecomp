// ===== FUN_00245370 @ 00245370 =====
// callers: FUN_0021fad0
// callees: FUN_00245150
// strings: 

ulong FUN_00245370(undefined8 param_1,int param_2,long param_3,long param_4)

{
  int iVar1;
  int iVar2;
  
  if ((&DAT_0075ede0)[(int)param_1 * 0x1c + param_2 * 7] != 0) {
    iVar1 = FUN_00245150(param_1);
    if (*(char *)(iVar1 + 0x72) != '\x01') {
      return 0;
    }
    if (*(byte *)(iVar1 + 100) < 2) {
      return 0;
    }
    if (param_3 < (long)(ulong)*(byte *)(iVar1 + 0x6a)) {
      if (param_3 == -1) {
        return (ulong)*(byte *)(iVar1 + 0x6a);
      }
      iVar2 = (int)param_3;
      if (param_4 == 2) {
        return (ulong)*(byte *)(iVar1 + iVar2 * 4 + 0x31);
      }
      if (param_4 < 3) {
        if (param_4 != 1) {
          return 0;
        }
        return (ulong)*(byte *)(iVar1 + iVar2 * 4 + 0x30);
      }
      if (param_4 == 3) {
        return (ulong)*(byte *)(iVar1 + iVar2 * 4 + 0x32);
      }
      if (param_4 != 4) {
        return 0;
      }
      return (ulong)*(byte *)(iVar1 + iVar2 * 4 + 0x33);
    }
  }
  return 0;
}


