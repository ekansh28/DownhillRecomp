// ===== FUN_00201e90 @ 00201e90 =====
// callers: FUN_00201180, FUN_002024d0, FUN_002025d8, FUN_00202738, FUN_00201980, FUN_00202a30, FUN_00202a70, FUN_00202aa8, FUN_00202ad0, FUN_00202b08, FUN_00201b00
// callees: sceSifCallRpc, FUN_002016e8, FUN_002013f8, FUN_00254d08, FlushCache, FUN_0025d178, FUN_00201640, FUN_00202388
// strings: "989snd.c: RPC collision!\n"

undefined4 FUN_00201e90(undefined8 param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  long lVar3;
  undefined *puVar4;
  int iVar5;
  
  iVar5 = 0;
  if (0 < param_2) {
    do {
      puVar2 = (undefined1 *)(param_3 + iVar5);
      puVar4 = &DAT_004c89c0 + iVar5;
      iVar5 = iVar5 + 1;
      *puVar4 = *puVar2;
    } while (iVar5 < param_2);
  }
  while (DAT_00279428 != 0) {
    FUN_002013f8(0x4c8980);
    FlushCache(0);
  }
  FUN_002016e8(0x4c8980,1);
  while (lVar3 = FUN_0025d178(0x4c8940), lVar3 != 0) {
    if (DAT_002794a0 == 0) {
      FUN_00254d08(0x297860);
    }
    FUN_002013f8();
    FlushCache(0);
  }
  if (param_2 == 0) {
    sceSifCallRpc(0x4c8940,param_1,1,0,0,0x4c8980,0xc,0);
  }
  else {
    sceSifCallRpc(0x4c8940,param_1,1,0x4c89c0,param_2,0x4c8980,0xc,0);
  }
  do {
    lVar3 = FUN_00201640();
    uVar1 = DAT_004c8984;
  } while (lVar3 == 0);
  if ((*(int *)(&PTR_DAT_00279448)[DAT_00279468] != 0) && (DAT_0027946c == 0)) {
    FUN_00202388();
  }
  return uVar1;
}


