// ===== FUN_0025c440 @ 0025c440 =====
// callers: FUN_0025c578, FUN_0025c5b8
// callees: sceSifSetDma, isceSifSetDma, FUN_0025c720
// strings: 

undefined8
FUN_0025c440(uint param_1,ulong param_2,undefined8 param_3,undefined8 param_4,uint param_5,
            uint param_6,long param_7)

{
  undefined8 uVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  uint auStack_80 [8];
  
  if (0x60 < (int)param_4 - 0x10U) {
    return 0;
  }
  iVar4 = 0;
  puVar3 = (uint *)param_3;
  if (param_7 < 1) {
    puVar3[1] = 0;
    *puVar3 = (uint)(byte)*puVar3;
  }
  else {
    auStack_80[2] = (uint)param_7;
    puVar3[1] = param_6;
    iVar4 = 1;
    *puVar3 = (uint)(byte)*puVar3 | auStack_80[2] << 8;
    auStack_80[3] = 0;
    auStack_80[0] = param_5;
    auStack_80[1] = param_6;
    if ((param_2 & 4) != 0) {
      FUN_0025c720();
      iVar2 = 0x10;
      goto LAB_0025c4e0;
    }
  }
  iVar2 = iVar4 << 4;
LAB_0025c4e0:
  *(uint **)((int)auStack_80 + iVar2) = puVar3;
  *(undefined4 *)((int)auStack_80 + iVar2 + 4) = DAT_00761b60;
  *(int *)((int)auStack_80 + iVar2 + 8) = (int)param_4;
  puVar3[2] = param_1;
  *(byte *)puVar3 = (byte)param_4;
  *(undefined4 *)((int)auStack_80 + iVar2 + 0xc) = 0x44;
  FUN_0025c720(param_3,param_4);
  if ((param_2 & 1) == 0) {
    uVar1 = sceSifSetDma(auStack_80,iVar4 + 1);
  }
  else {
    uVar1 = isceSifSetDma(auStack_80);
  }
  return uVar1;
}


