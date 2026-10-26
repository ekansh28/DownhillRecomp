// ===== FUN_00201718 @ 00201718 =====
// callers: FUN_00208900
// callees: FlushCache, sceSifCallRpc, FUN_00202820, FUN_00254d08, FUN_002013f8, FUN_0025d178
// strings: "snd_BankLoadByLoc: Load already in progress!\n", "snd_BankLoadByLoc: CD BUSY!\n", "989snd.c: RPC collision!\n", "989snd.c: RPC call has failed inside snd_BankLoadByLoc\n"

int FUN_00201718(undefined4 param_1,undefined4 param_2)

{
  long lVar1;
  char *pcVar2;
  
  DAT_00279430 = 0;
  if (DAT_00279470 == 0) {
    lVar1 = FUN_00202820(1);
    if (lVar1 != 1) {
      DAT_004cd400 = -1;
      DAT_004cd440 = param_1;
      DAT_004cd444 = param_2;
      while (lVar1 = FUN_0025d178(0x4cd3c0), lVar1 != 0) {
        if (DAT_002794a0 == 0) {
          FUN_00254d08(0x297860);
        }
        FUN_002013f8();
        FlushCache(0);
      }
      lVar1 = sceSifCallRpc(0x4cd3c0,3,1,0x4cd440,8,0x4cd400,4,0);
      if (lVar1 < 0) {
        if (DAT_002794a0 == 0) {
          FUN_00254d08(0x297938);
        }
        DAT_00279430 = 0x106;
        return 0;
      }
      while (DAT_004cd400 == -1) {
        FlushCache(0);
      }
      return DAT_004cd400;
    }
    if (DAT_002794a0 != 0) {
      return 0;
    }
    pcVar2 = "snd_BankLoadByLoc: CD BUSY!\n";
  }
  else {
    if (DAT_002794a0 != 0) {
      DAT_00279430 = 0;
      return 0;
    }
    pcVar2 = "snd_BankLoadByLoc: Load already in progress!\n";
  }
  FUN_00254d08(pcVar2);
  return 0;
}


