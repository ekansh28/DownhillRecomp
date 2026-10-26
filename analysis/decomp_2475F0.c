// ===== FUN_002475f0 @ 002475f0 =====
// callers: FUN_00247c28, FUN_00247f08, FUN_00248058, FUN_00247fa0
// callees: FUN_0025c078, SignalSema, PollSema, sceSifBindRpc, FUN_00246d88, ReferThreadStatus, FUN_00247580, FUN_0025c7d0
// strings: "Scmd fail sema cur_cmd:%d keep_cmd:%d\n", "Libcdvd bind err S cmd\n"

undefined4 FUN_002475f0(undefined8 param_1)

{
  int iVar1;
  long lVar2;
  
  FUN_00246d88();
  iVar1 = PollSema(DAT_0027f82c);
  if (DAT_0027f82c == iVar1) {
    DAT_0027f818 = (undefined4)param_1;
    ReferThreadStatus(DAT_007607d0,0x7607d8);
    lVar2 = FUN_00247580(1);
    if (lVar2 == 0) {
      FUN_0025c7d0(0);
      if (-1 < DAT_0027f84c) {
        return 1;
      }
      while( true ) {
        while (lVar2 = sceSifBindRpc(0x281380,0xffffffff80000593,0), lVar2 < 0) {
          if (0 < DAT_0027f810) {
            FUN_0025c078(0x29a558);
          }
          iVar1 = 0x100000;
          do {
            iVar1 = iVar1 + -1;
          } while (iVar1 != -1);
        }
        if (DAT_002813a4 != 0) break;
        iVar1 = 0x100000;
        do {
          iVar1 = iVar1 + -1;
        } while (iVar1 != -1);
      }
      DAT_0027f84c = 0;
      return 1;
    }
    SignalSema(DAT_0027f82c);
  }
  else if (0 < DAT_0027f810) {
    FUN_0025c078(0x29a530,param_1,DAT_0027f818);
    return 0;
  }
  return 0;
}


