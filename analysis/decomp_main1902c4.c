// ===== FUN_001901c0 @ 001901c0 =====
// callers: FUN_00190108, FUN_00190188
// callees: FUN_001c51c0, FUN_00190358, FUN_001b5a38, FUN_001b5b70, FUN_00139bf0, FUN_001b5ac8, FUN_001b4dd0, FUN_001c54a0, FUN_0018dd80, FUN_00190320, FUN_001b5130
// strings: 

void FUN_001901c0(undefined8 param_1)

{
  char cVar1;
  long lVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = (int)param_1;
  *(undefined1 *)(iVar4 + 0x12d) = 0;
  *(undefined1 *)(iVar4 + 300) = 0;
  FUN_001b5a38();
  FUN_001b5b70(param_1,0);
  cVar1 = *(char *)(iVar4 + 0x12d);
  while (cVar1 == '\0') {
    FUN_001b4dd0(param_1);
    iVar3 = *(int *)(iVar4 + 0x150);
    if (*(char *)(iVar3 + 0x4b9) == '\0') {
      (**(code **)(*(int *)(iVar3 + 0x4f8) + 0xc))(iVar3 + *(short *)(*(int *)(iVar3 + 0x4f8) + 8));
      *(undefined1 *)(iVar3 + 0x4b9) = 1;
    }
    lVar2 = FUN_00139bf0();
    if (lVar2 == 0) {
      if (DAT_004b26b8 == 2) {
        if (*(char *)(iVar4 + 4) == '\0') {
          FUN_001c54a0(0x4b2a90);
          iVar3 = *(int *)(iVar4 + 0x150);
        }
        else {
          iVar3 = *(int *)(iVar4 + 0x150);
        }
      }
      else {
        iVar3 = *(int *)(iVar4 + 0x150);
      }
    }
    else {
      FUN_001c51c0(0x4b2a90);
      iVar3 = *(int *)(iVar4 + 0x150);
    }
    if (iVar3 != 0) {
      lVar2 = FUN_0018dd80(iVar3,DAT_004b2828,1);
      if (lVar2 == 0) {
        iVar3 = *(int *)(*(int *)(iVar4 + 0x150) + 0x4f8);
        (**(code **)(iVar3 + 0x2c))(*(int *)(iVar4 + 0x150) + (int)*(short *)(iVar3 + 0x28));
      }
      else {
        FUN_00190358(param_1);
      }
    }
    FUN_001b5130(param_1);
    cVar1 = *(char *)(iVar4 + 0x12d);
  }
  FUN_001b5ac8(param_1);
  FUN_00190320(param_1);
  return;
}


