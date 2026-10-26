// ===== FUN_00202048 @ 00202048 =====
// callers: FUN_002018e8, FUN_00201948, FUN_002019a8, FUN_00201a30, FUN_00201a78, FUN_00201ab8, FUN_00201b68, FUN_00201bd0, FUN_00201c58, FUN_00201cb8, FUN_00201cf0, FUN_00201d20, FUN_00201d50, FUN_00201d80, FUN_00201e08, FUN_002025a0, FUN_00202688, FUN_00202960, FUN_00202998, FUN_00201918, FUN_00202760, FUN_00202708, FUN_002028c8
// callees: sceSifCallRpc, FUN_00202348, FUN_002016e8, FUN_00254d08, FUN_0025d178, FlushCache, FUN_002013f8
// strings: "989snd.c: RPC collision!\n", "snd_SendIOPCommandNoWait: BUFFER %d FULL(%d)! Sound stalled waiting for IOP comands to finish!\n", "snd_SendIOPCommandNoWait: continuing (%d).\n"

void FUN_00202048(undefined4 param_1,int param_2,int param_3,long param_4,undefined8 param_5)

{
  bool bVar1;
  uint uVar2;
  undefined1 *puVar3;
  long lVar4;
  int iVar5;
  undefined **ppuVar6;
  undefined2 *puVar7;
  int iVar8;
  undefined **ppuVar9;
  int iVar10;
  
  bVar1 = false;
  if ((DAT_0027946c == 0) && (DAT_00279428 == 0)) {
    uVar2 = param_2 + 4U & 3;
    if ((param_2 == 0) && (param_4 == 0)) {
      FUN_002016e8(0x4c8980,1);
      while (lVar4 = FUN_0025d178(0x4c8940), lVar4 != 0) {
        if (DAT_002794a0 == 0) {
          FUN_00254d08(0x297860);
        }
        FUN_002013f8();
        FlushCache(0);
      }
      sceSifCallRpc(0x4c8940,param_1,1,0,0,0x4c8980,0xc,0);
      return;
    }
  }
  else {
    uVar2 = param_2 + 4U & 3;
  }
  iVar10 = param_2 + 4;
  iVar8 = 0;
  if (uVar2 != 0) {
    iVar5 = param_2 + 7;
    if (-1 < iVar10) {
      iVar5 = iVar10;
    }
    iVar10 = (param_2 + 8) - (iVar10 + (iVar5 >> 2) * -4);
  }
  while ((*(int *)(&PTR_DAT_00279448)[DAT_00279468] == 0x100 ||
         ((int)(&DAT_00279450)[DAT_00279468] < iVar10))) {
    if (DAT_0027946c != 0) {
      DAT_0027946c = 0;
      bVar1 = true;
    }
    FUN_002013f8();
    if (iVar8 == 1) {
      if (DAT_002794a0 == 0) {
        FUN_00254d08(0x297bb8,DAT_00279468,*(undefined4 *)(&PTR_DAT_00279448)[DAT_00279468]);
        iVar8 = 2;
      }
      else {
        iVar8 = 2;
      }
    }
    else {
      iVar8 = iVar8 + 1;
    }
  }
  if ((iVar8 != 0) && (DAT_002794a0 == 0)) {
    FUN_00254d08(0x297c18,iVar8);
  }
  if (bVar1) {
    DAT_0027946c = 1;
  }
  iVar8 = 0;
  puVar7 = (undefined2 *)
           ((&PTR_DAT_00279448)[DAT_00279468] + -((&DAT_00279450)[DAT_00279468] + -0x1000));
  *puVar7 = (short)param_1;
  puVar7[1] = (short)param_2;
  if (0 < param_2) {
    do {
      puVar3 = (undefined1 *)(param_3 + iVar8);
      iVar5 = iVar8 + 4;
      iVar8 = iVar8 + 1;
      *(undefined1 *)((int)puVar7 + iVar5) = *puVar3;
    } while (iVar8 < param_2);
  }
  ppuVar9 = &PTR_DAT_00279448 + DAT_00279468;
  ppuVar6 = &PTR_DAT_00279458 + DAT_00279468;
  (&DAT_00279450)[DAT_00279468] = (&DAT_00279450)[DAT_00279468] - iVar10;
  *(int *)(*ppuVar6 + *(int *)*ppuVar9 * 0x10) = (int)param_4;
  *(undefined8 *)(*ppuVar6 + *(int *)*ppuVar9 * 0x10 + 8) = param_5;
  FUN_00202348();
  return;
}


