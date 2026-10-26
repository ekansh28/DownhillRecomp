// ===== FUN_0025b770 @ 0025b770 =====
// callers: FUN_0025c078
// callees: FUN_0025f530
// strings: 

void FUN_0025b770(int param_1)

{
  int iVar1;
  
  iVar1 = DAT_00282154;
  if (0x7d < DAT_00282154) {
    DAT_00282154 = 0;
    DAT_00761a7f = 0;
    FUN_0025f530(0x761a00);
    iVar1 = DAT_00282154;
  }
  if (param_1 != 10) {
    DAT_00282154 = iVar1 + 1;
    (&DAT_00761a00)[iVar1] = (char)param_1;
    return;
  }
  DAT_00282154 = 0;
  (&DAT_00761a00)[iVar1] = 10;
  *(undefined1 *)(iVar1 + 0x761a01) = 0;
  FUN_0025f530();
  return;
}


