// ===== sceSifCallRpc @ 0025cf88 =====
// callers: FUN_00201e90, FUN_00202048, FUN_00202388, FUN_00201718, FUN_00244ec8, FUN_00244f68, FUN_00245a58, FUN_00245d28, FUN_00245da0, FUN_00245e10, FUN_00245e78, FUN_00246030, FUN_00246fa0, FUN_00247760, FUN_00247a40, FUN_00247c28, FUN_00247d28, FUN_00247448, FUN_00247f08, FUN_00248058, FUN_00248390, FUN_0025da60, FUN_0025d790, FUN_0025dce8, FUN_0025de68, FUN_0025e0a0, FUN_0025e300, FUN_0025e6a8, FUN_0025e718, FUN_0025e960, FUN_0025e7c0, FUN_002455d0, FUN_00245748, FUN_002458d8, FUN_002460f8, FUN_00246258, FUN_002463a0, FUN_002464b8, FUN_00246960, FUN_002467d8, FUN_00246ab0, FUN_00247fa0
// callees: FUN_0025c998, FUN_0025ca40, DeleteSema, WaitSema, FUN_0025c578, CreateSema, FUN_0025c720
// strings: 

undefined4
sceSifCallRpc(int *param_1,undefined4 param_2,ulong param_3,long param_4,long param_5,long param_6,
             long param_7,long param_8,int param_9)

{
  int iVar1;
  long lVar2;
  long lVar3;
  int iVar4;
  undefined1 auStack_c0 [4];
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  
  lVar2 = FUN_0025c998(0x763500);
  if (lVar2 == 0) {
    return 0xffffffff;
  }
  iVar4 = (int)lVar2;
  iVar1 = *(int *)(iVar4 + 0x18);
  param_1[8] = param_9;
  *param_1 = iVar4;
  param_1[1] = iVar1;
  param_1[7] = (int)param_8;
  *(undefined4 *)(iVar4 + 0x20) = param_2;
  *(int *)(iVar4 + 0x24) = (int)param_5;
  *(int *)(iVar4 + 0x28) = (int)param_6;
  *(int *)(iVar4 + 0x2c) = (int)param_7;
  *(int *)(iVar4 + 0x14) = iVar4;
  iVar1 = param_1[9];
  *(int **)(iVar4 + 0x1c) = param_1;
  *(int *)(iVar4 + 0x34) = iVar1;
  if ((param_3 & 2) == 0) {
    if (param_4 == param_6) {
      if (param_7 <= param_5) {
        param_7 = param_5;
      }
      FUN_0025c720(param_4,param_7);
    }
    else {
      if (0 < param_5) {
        FUN_0025c720(param_4,param_5);
      }
      if (0 < param_7) {
        FUN_0025c720(param_6,param_7);
      }
    }
  }
  if ((param_3 & 1) == 0) {
    uStack_b8 = 0;
    uStack_bc = 1;
    lVar3 = CreateSema(auStack_c0);
    param_1[2] = (int)lVar3;
    if (lVar3 < 0) {
      FUN_0025ca40(lVar2);
      return 0xfffffffd;
    }
    *(undefined4 *)(iVar4 + 0x30) = 1;
    lVar3 = FUN_0025c578(0xffffffff8000000a,lVar2,0x40,param_4,param_1[5],param_5);
    if (lVar3 != 0) {
      WaitSema(param_1[2]);
      DeleteSema(param_1[2]);
      return 0;
    }
    DeleteSema(param_1[2]);
  }
  else {
    if (param_8 == 0) {
      *(undefined4 *)(iVar4 + 0x30) = 0;
    }
    else {
      *(undefined4 *)(iVar4 + 0x30) = 1;
    }
    param_1[2] = -1;
    lVar3 = FUN_0025c578(0xffffffff8000000a,lVar2,0x40,param_4,param_1[5],param_5);
    if (lVar3 != 0) {
      return 0;
    }
  }
  FUN_0025ca40(lVar2);
  return 0xfffffffe;
}


