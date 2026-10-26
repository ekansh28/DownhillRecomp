// ===== FUN_002474e0 @ 002474e0 =====
// callers: FUN_00202820, FUN_0020e4d0, FUN_00231230, FUN_00246fa0, FUN_002472d8
// callees: FUN_0025c078, FUN_00246bb0, FUN_0025d178
// strings: "N cmd wait\n"

undefined4 FUN_002474e0(long param_1)

{
  undefined4 uVar1;
  long lVar2;
  
  if (param_1 == 0) {
    if (0 < DAT_0027f810) {
      FUN_0025c078(0x29a510);
    }
    while ((DAT_0027f834 != 0 || (lVar2 = FUN_0025d178(0x2809d0), lVar2 != 0))) {
      FUN_00246bb0(0x3c);
    }
    return 0;
  }
  uVar1 = 1;
  if (DAT_0027f834 == 0) {
    lVar2 = FUN_0025d178(0x2809d0);
    uVar1 = 1;
    if (lVar2 == 0) {
      uVar1 = 0;
    }
  }
  return uVar1;
}


