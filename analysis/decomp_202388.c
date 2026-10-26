// ===== FUN_00202388 @ 00202388 =====
// callers: FUN_002013f8, FUN_00201e90
// callees: FUN_0025d178, FUN_00254d08, FlushCache, FUN_002016e8, sceSifCallRpc
// strings: "989snd.c: RPC collision!\n"

void FUN_00202388(void)

{
  long lVar1;
  undefined4 *puVar2;
  
  FUN_002016e8((&PTR_DAT_00279460)[DAT_00279468],*(undefined4 *)(&PTR_DAT_00279448)[DAT_00279468]);
  while (lVar1 = FUN_0025d178(0x4c8940), lVar1 != 0) {
    if (DAT_002794a0 == 0) {
      FUN_00254d08(0x297860);
    }
    FlushCache(0);
  }
  sceSifCallRpc(0x4c8940,0x4d,1,(&PTR_DAT_00279448)[DAT_00279468],
                0x1000 - (&DAT_00279450)[DAT_00279468],(&PTR_DAT_00279460)[DAT_00279468],
                *(int *)(&PTR_DAT_00279448)[DAT_00279468] * 4 + 8,0);
  DAT_00279468 = (uint)(DAT_00279468 != 1);
  puVar2 = &DAT_00279450 + DAT_00279468;
  *(undefined4 *)(&PTR_DAT_00279448)[DAT_00279468] = 0;
  *puVar2 = 0xffc;
  return;
}


