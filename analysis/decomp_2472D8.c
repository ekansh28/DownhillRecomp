// ===== FUN_002472d8 @ 002472d8 =====
// callers: FUN_00247d28, FUN_00247448, FUN_00248390
// callees: FUN_0025c078, SignalSema, PollSema, sceSifBindRpc, FUN_00246d88, ReferThreadStatus, FUN_002474e0, FUN_0025c7d0
// strings: "Ncmd fail sema cur_cmd:%d keep_cmd:%d\n", "Libcdvd bind err N CMD\n"

undefined4 FUN_002472d8(undefined8 param_1)

{
  int iVar1;
  long lVar2;
  
  FUN_00246d88();
  iVar1 = PollSema(DAT_0027f828);
  if (DAT_0027f828 == iVar1) {
    DAT_0027f81c = (undefined4)param_1;
    ReferThreadStatus(DAT_007607d0,0x7607d8);
    lVar2 = FUN_002474e0(1);
    if (lVar2 == 0) {
      FUN_0025c7d0(0);
      if (-1 < DAT_0027f83c) {
        return 1;
      }
      while( true ) {
        while (lVar2 = sceSifBindRpc(0x2809d0,0xffffffff80000595,0), lVar2 < 0) {
          if (0 < DAT_0027f810) {
            FUN_0025c078(0x29a4f8);
          }
          iVar1 = 0x100000;
          do {
            iVar1 = iVar1 + -1;
          } while (iVar1 != -1);
        }
        if (DAT_002809f4 != 0) break;
        iVar1 = 0x100000;
        do {
          iVar1 = iVar1 + -1;
        } while (iVar1 != -1);
      }
      DAT_0027f83c = 0;
      return 1;
    }
    SignalSema(DAT_0027f828);
  }
  else if (0 < DAT_0027f810) {
    FUN_0025c078(0x29a4d0,param_1,DAT_0027f81c);
    return 0;
  }
  return 0;
}


