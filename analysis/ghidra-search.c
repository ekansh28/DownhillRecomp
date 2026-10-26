// ===== FUN_00246fa0 @ 00246fa0 =====
// callers: FUN_002472b8
// callees: sceSifBindRpc, PollSema, FUN_00246d88, FUN_002474e0, FUN_0025c078, ReferThreadStatus, sceSifCallRpc, FUN_0025c7d0, FUN_0025c720, SignalSema
// strings: "Libcdvd bind err CdSearchFile\n", "ee call cmd search %s\n", "search name %s\n", "search size %d\n", "search loc lbn %d\n"

undefined4 FUN_00246fa0(undefined4 *param_1,char *param_2,undefined4 param_3)

{
  char cVar1;
  uint uVar2;
  ulong *puVar3;
  uint *puVar4;
  ulong uVar5;
  ulong uVar6;
  ulong uVar7;
  ulong uVar8;
  uint uVar9;
  undefined4 uVar10;
  int iVar11;
  long lVar12;
  
  FUN_00246d88();
  iVar11 = PollSema(DAT_0027f828);
  if (DAT_0027f828 == iVar11) {
    DAT_0027f81c = 1;
    ReferThreadStatus(DAT_007607d0,0x7607d8);
    lVar12 = FUN_002474e0(1);
    if (lVar12 == 0) {
      FUN_0025c7d0(0);
      if (DAT_0027f844 < 0) {
        while( true ) {
          while (lVar12 = sceSifBindRpc(0x7609c0,0xffffffff80000597,0), lVar12 < 0) {
            if (0 < DAT_0027f810) {
              FUN_0025c078(0x29a460);
            }
            iVar11 = 0x100000;
            do {
              iVar11 = iVar11 + -1;
            } while (iVar11 != -1);
          }
          iVar11 = 0x100000;
          if (DAT_007609e4 != 0) break;
          do {
            iVar11 = iVar11 + -1;
          } while (iVar11 != -1);
        }
        DAT_0027f844 = 0;
      }
      DAT_00760864 = *param_2;
      iVar11 = 0;
      if (DAT_00760864 != '\0') {
        for (iVar11 = 1;
            (iVar11 < 0x100 &&
            (cVar1 = param_2[iVar11], (&DAT_00760864)[iVar11] = cVar1, cVar1 != '\0'));
            iVar11 = iVar11 + 1) {
        }
      }
      if (iVar11 == 0x100) {
        DAT_00760963 = 0;
      }
      if (0 < DAT_0027f810) {
        FUN_0025c078(0x29a480,0x760864);
      }
      DAT_00760964 = &DAT_00760840;
      DAT_00760968 = param_3;
      FUN_0025c720(0x760840,300);
      lVar12 = sceSifCallRpc(0x7609c0,0,0,0x760840,300,0x760980,4,0);
      uVar8 = DAT_20760858;
      uVar7 = DAT_20760850;
      uVar6 = DAT_20760848;
      uVar5 = DAT_20760840;
      if (-1 < lVar12) {
        uVar2 = (int)param_1 + 7U & 7;
        puVar3 = (ulong *)(((int)param_1 + 7U) - uVar2);
        *puVar3 = *puVar3 & -1L << (uVar2 + 1) * 8 | DAT_20760840 >> (7 - uVar2) * 8;
        uVar2 = (uint)param_1 & 7;
        *(ulong *)((int)param_1 - uVar2) =
             uVar5 << uVar2 * 8 |
             *(ulong *)((int)param_1 - uVar2) & 0xffffffffffffffffU >> (8 - uVar2) * 8;
        uVar2 = (int)param_1 + 0xfU & 7;
        puVar3 = (ulong *)(((int)param_1 + 0xfU) - uVar2);
        *puVar3 = *puVar3 & -1L << (uVar2 + 1) * 8 | uVar6 >> (7 - uVar2) * 8;
        uVar2 = (uint)(param_1 + 2) & 7;
        puVar3 = (ulong *)((int)(param_1 + 2) - uVar2);
        *puVar3 = uVar6 << uVar2 * 8 | *puVar3 & 0xffffffffffffffffU >> (8 - uVar2) * 8;
        uVar2 = (int)param_1 + 0x17U & 7;
        puVar3 = (ulong *)(((int)param_1 + 0x17U) - uVar2);
        *puVar3 = *puVar3 & -1L << (uVar2 + 1) * 8 | uVar7 >> (7 - uVar2) * 8;
        uVar2 = (uint)(param_1 + 4) & 7;
        puVar3 = (ulong *)((int)(param_1 + 4) - uVar2);
        *puVar3 = uVar7 << uVar2 * 8 | *puVar3 & 0xffffffffffffffffU >> (8 - uVar2) * 8;
        uVar2 = (int)param_1 + 0x1fU & 7;
        puVar3 = (ulong *)(((int)param_1 + 0x1fU) - uVar2);
        *puVar3 = *puVar3 & -1L << (uVar2 + 1) * 8 | uVar8 >> (7 - uVar2) * 8;
        uVar2 = (uint)(param_1 + 6) & 7;
        puVar3 = (ulong *)((int)(param_1 + 6) - uVar2);
        *puVar3 = uVar8 << uVar2 * 8 | *puVar3 & 0xffffffffffffffffU >> (8 - uVar2) * 8;
        uVar9 = DAT_20760860;
        uVar2 = (int)param_1 + 0x23U & 3;
        puVar4 = (uint *)(((int)param_1 + 0x23U) - uVar2);
        *puVar4 = *puVar4 & -1 << (uVar2 + 1) * 8 | DAT_20760860 >> (3 - uVar2) * 8;
        uVar2 = (uint)(param_1 + 8) & 3;
        puVar4 = (uint *)((int)(param_1 + 8) - uVar2);
        *puVar4 = *puVar4 & 0xffffffffU >> (4 - uVar2) * 8 | uVar9 << uVar2 * 8;
        if (((0 < DAT_0027f810) && (FUN_0025c078(0x29a498,param_1 + 2), 0 < DAT_0027f810)) &&
           (FUN_0025c078(0x29a4a8,param_1[1]), 0 < DAT_0027f810)) {
          FUN_0025c078(0x29a4b8,*param_1);
        }
        uVar10 = DAT_20760980;
        SignalSema(DAT_0027f828);
        return uVar10;
      }
    }
    SignalSema(DAT_0027f828);
  }
  return 0;
}


