// ===== FUN_0025b528 @ 0025b528 =====
// callers: FUN_0025aca8
// callees: FUN_0025eea0, FUN_0025f458, FUN_0025ee58, FUN_0025f488
// strings: 

int FUN_0025b528(char *param_1,int param_2)

{
  long lVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = 0;
  iVar5 = -1;
  if (DAT_0076175c == 0) {
    FUN_0025ee58();
    DAT_0076175c = 1;
    DAT_00761760 = &DAT_20761780;
    pcVar3 = &DAT_2076178c;
    iVar5 = 0;
    do {
      param_2 = param_2 + -1;
      if (param_2 == -1) break;
      cVar2 = *param_1;
      if (*param_1 == '\n') {
        *pcVar3 = '\r';
        iVar4 = iVar4 + 1;
        pcVar3 = pcVar3 + 1;
        if (0xff < iVar4) break;
        cVar2 = *param_1;
      }
      *pcVar3 = cVar2;
      iVar4 = iVar4 + 1;
      param_1 = param_1 + 1;
      pcVar3 = pcVar3 + 1;
      iVar5 = iVar5 + 1;
    } while (iVar4 < 0x100);
    DAT_00761754 = iVar4 + 0xc;
    DAT_20761780 = (undefined2)DAT_00761754;
    lVar1 = FUN_0025f458(DAT_00761750,DAT_20761787);
    if (lVar1 < 0) {
      DAT_0076175c = 0;
      FUN_0025eea0();
      iVar5 = -1;
    }
    else {
      while (DAT_0076175c != 0) {
        FUN_0025f488(DAT_00761750);
      }
      FUN_0025eea0();
    }
  }
  return iVar5;
}


