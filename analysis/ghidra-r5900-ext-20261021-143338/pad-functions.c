// ===== FUN_00245318 @ 00245318 =====
// callers: FUN_0021fad0
// callees: FUN_00245150
// strings: 

undefined1 FUN_00245318(undefined8 param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  
  uVar1 = 0;
  if ((&DAT_0075ede0)[(int)param_1 * 0x1c + param_2 * 7] != 0) {
    iVar2 = FUN_00245150(param_1);
    uVar1 = *(undefined1 *)(iVar2 + 0x71);
  }
  return uVar1;
}


