// ===== FUN_00248390 @ 00248390 =====
// callers: FUN_00248150, FUN_00248180, FUN_002481c8, FUN_00248200
// callees: FUN_0025c078, FUN_002472d8, sceSifCallRpc, SignalSema, FUN_0025c720
// strings: "call cdreadstm call\n", "call cdreadstm cmd\n", "cdread end\n"

undefined4
FUN_00248390(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            long param_5)

{
  undefined4 uVar1;
  long lVar2;
  undefined1 *puVar3;
  
  lVar2 = FUN_002472d8(0xf);
  if (lVar2 == 0) {
    uVar1 = 0;
  }
  else {
    if (0 < DAT_0027f810) {
      FUN_0025c078(0x29a738);
    }
    if (param_5 != 0) {
      puVar3 = (undefined1 *)param_5;
      DAT_0027f910 = *puVar3;
      DAT_0027f911 = puVar3[1];
      DAT_0027f912 = puVar3[2];
    }
    DAT_0027f900 = param_1;
    DAT_0027f904 = param_2;
    DAT_0027f908 = param_3;
    DAT_0027f90c = param_4;
    if (0 < DAT_0027f810) {
      FUN_0025c078(0x29a750);
    }
    FUN_0025c720(0x27f900,0x14);
    lVar2 = sceSifCallRpc(0x2809d0,9,0,0x27f900,0x14,0x27f880,4,0);
    if (lVar2 < 0) {
      SignalSema(DAT_0027f828);
      uVar1 = 0;
    }
    else {
      if (0 < DAT_0027f810) {
        FUN_0025c078(0x29a768);
      }
      uVar1 = DAT_2027f880;
      SignalSema(DAT_0027f828);
    }
  }
  return uVar1;
}


