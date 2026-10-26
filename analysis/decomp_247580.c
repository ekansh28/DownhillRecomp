// ===== FUN_00247580 @ 00247580 =====
// callers: FUN_00247760, FUN_002475f0
// callees: FUN_0025d178, FUN_00246bb0, FUN_0025c078
// strings: "S cmd wait\n"

undefined8 FUN_00247580(long param_1)

{
  long lVar1;
  undefined8 uVar2;
  
  if (param_1 == 0) {
    if (0 < DAT_0027f810) {
      FUN_0025c078(0x29a520);
    }
    while( true ) {
      lVar1 = FUN_0025d178(0x281380);
      uVar2 = 0;
      if (lVar1 == 0) break;
      FUN_00246bb0(0x3c);
    }
  }
  else {
    uVar2 = FUN_0025d178(0x281380);
  }
  return uVar2;
}


