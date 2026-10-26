// ==== 0 FUN_00000000 ====

/* WARNING: Control flow encountered bad instruction data */

void FUN_00000000(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 + (uint)(*(uint *)(param_1 + 0x80) < *(uint *)(param_1 + 0xa0)) * 0x20 + 0x80;
  if (*(int *)(iVar1 + 4) != 0) {
    FUN_00004030(*(undefined2 *)(param_1 + 0x1ac),*(undefined2 *)(param_1 + 0x1ae),iVar1 + 0xc);
    *(undefined4 *)(iVar1 + 4) = 0;
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ==== 6c FUN_0000006c ====

/* WARNING: Control flow encountered bad instruction data */

void FUN_0000006c(undefined8 param_1,ulonglong param_2)

{
  undefined1 auStack_60 [72];
  uint auStack_18 [6];
  
  FUN_0000799c(param_1,param_2 | 0x1000,1,auStack_18);
  if ((auStack_18[0] & 0x1000) != 0) {
    FUN_00007948(0,auStack_60);
                    /* WARNING: Subroutine does not return */
    FUN_00007984(param_1,0x1000);
  }
  FUN_00007994(param_1,~param_2);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ==== 1a8 FUN_000001a8 ====

/* WARNING: Control flow encountered bad instruction data */

void FUN_000001a8(int param_1)

{
  undefined1 auStack_58 [88];
  
  FUN_00007948(*(undefined4 *)(param_1 + 0x18c),auStack_58);
  FUN_00007948(*(undefined4 *)(param_1 + 400),auStack_58);
  FUN_00007948(*(undefined4 *)(param_1 + 0x198),auStack_58);
  FUN_00007948(*(undefined4 *)(param_1 + 0x19c),auStack_58);
  FUN_00007948(*(undefined4 *)(param_1 + 0x1a0),auStack_58);
  FUN_00007948(*(undefined4 *)(param_1 + 0x1a4),auStack_58);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ==== 3e0c FUN_00003e0c ====

/* WARNING: Control flow encountered bad instruction data */

void FUN_00003e0c(int param_1,int param_2,longlong param_3,longlong param_4)

{
  int iVar1;
  
  iVar1 = param_1 * 0x710 + param_2 * 0x1c4 + 0x7e60;
  if (*(short *)(iVar1 + 0x1b0) != 1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  if (1 < *(byte *)(iVar1 + 0xc0)) {
    if (param_3 == -1) {
      halt_baddata();
    }
    if (param_3 < (longlong)(ulonglong)*(byte *)(iVar1 + 0xc6)) {
      if (param_4 == -1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      if (param_4 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      if (param_4 == 1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      if (param_4 == 2) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
    }
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ==== 4690 FUN_00004690 ====

/* WARNING: Control flow encountered bad instruction data */

void FUN_00004690(int param_1,uint param_2,int param_3)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  if (0 < *(int *)(param_3 * 0x68 + param_2 * 0x1a0 + 0x8cd0)) {
    do {
      puVar1 = (undefined1 *)(DAT_00009074 + DAT_0000906c);
      DAT_0000906c = DAT_0000906c + 1;
      *puVar1 = *(undefined1 *)(iVar2 + param_3 * 0x68 + param_2 * 0x1a0 + 0x8cd8);
      iVar2 = iVar2 + 1;
    } while (iVar2 < *(int *)(param_3 * 0x68 + param_2 * 0x1a0 + 0x8cd0));
  }
  iVar2 = param_3 * 0x68 + param_2 * 0x1a0;
  DAT_00009070 = DAT_00009070 + *(int *)(iVar2 + 0x8cd4);
  *(undefined4 *)(param_2 * 4 + 0x9004) = *(undefined4 *)(iVar2 + 0x8d18);
  *(undefined4 *)(param_2 * 4 + 0x9014) = *(undefined4 *)(iVar2 + 0x8d1c);
  *(uint *)(param_1 * 4 + 0x9028) = *(uint *)(iVar2 + 0x8d20) & 0xfffffffc | param_2 & 3;
  *(undefined4 *)((param_1 + 1) * 4 + 0x9028) = 0;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ==== 4824 FUN_00004824 ====

/* WARNING: Control flow encountered bad instruction data */

void FUN_00004824(undefined8 param_1,int param_2,int param_3)

{
  int iVar1;
  longlong lVar2;
  undefined1 *puVar3;
  int iVar4;
  
  if ((DAT_00009000 >> 0xd & 1) == 1) {
    *(undefined4 *)(param_3 * 0x68 + param_2 * 0x1a0 + 0x8d24) = 1;
  }
  else {
    lVar2 = FUN_000044f0(param_1,&DAT_00009000);
    if (lVar2 == 1) {
      *(undefined4 *)(param_3 * 0x68 + param_2 * 0x1a0 + 0x8d24) = 1;
    }
    else {
      iVar1 = param_3 * 0x68 + param_2 * 0x1a0;
      *(undefined4 *)(iVar1 + 0x8d24) = 0;
      iVar4 = 0;
      if (0 < *(int *)(iVar1 + 0x8cd4)) {
        do {
          puVar3 = (undefined1 *)(DAT_00009078 + DAT_00009070);
          DAT_00009070 = DAT_00009070 + 1;
          *(undefined1 *)(iVar4 + param_3 * 0x68 + param_2 * 0x1a0 + 0x8cf8) = *puVar3;
          iVar4 = iVar4 + 1;
        } while (iVar4 < *(int *)(param_3 * 0x68 + param_2 * 0x1a0 + 0x8cd4));
      }
    }
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ==== 49d0 FUN_000049d0 ====

/* WARNING: Control flow encountered bad instruction data */

void FUN_000049d0(undefined8 param_1)

{
  bool bVar1;
  bool bVar2;
  uint uVar3;
  longlong lVar4;
  int iVar5;
  longlong lVar6;
  longlong lVar7;
  
  bVar2 = false;
  bVar1 = false;
  lVar6 = 0;
  DAT_0000906c = 0;
  DAT_00009070 = 0;
  DAT_00009088 = 0;
  DAT_0000907c = 0;
  uVar3 = FUN_000078cc();
  FUN_00004604(0,param_1,uVar3 >> 4 & 1);
  FUN_00004604(1,param_1,uVar3 >> 5 & 1);
  iVar5 = (int)param_1;
  if ((*(int *)(iVar5 * 0x68 + 0x8cc0) == 1) && (DAT_000090a8 == 1)) {
    bVar1 = true;
    lVar6 = FUN_00004690(0,0,param_1);
  }
  lVar4 = lVar6;
  lVar7 = 0;
  if ((*(int *)(iVar5 * 0x68 + 0x8e60) == 1) && (DAT_000090ac == 1)) {
    bVar2 = true;
    lVar4 = FUN_00004690(lVar6,1,param_1);
    lVar7 = lVar6;
  }
  if ((*(int *)(iVar5 * 0x68 + 0x8cc0) == 1) && (DAT_000090a8 != 1)) {
    *(undefined4 *)(iVar5 * 0x68 + 0x8d24) = 10;
  }
  if ((*(int *)(iVar5 * 0x68 + 0x8e60) == 1) && (DAT_000090ac != 1)) {
    *(undefined4 *)(iVar5 * 0x68 + 0x8ec4) = 10;
  }
  if (lVar4 != 0) {
    FUN_000078dc(&DAT_00009000);
    DAT_00009070 = 0;
    if (bVar1) {
      FUN_00004824(0,0,param_1);
      DAT_00009070 = *(undefined4 *)(iVar5 * 0x68 + 0x8cd4);
    }
    if (bVar2) {
      FUN_00004824(lVar7,1,param_1);
      DAT_00009070 = *(undefined4 *)(iVar5 * 0x68 + 0x8e74);
    }
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ==== 4c6c FUN_00004c6c ====

/* WARNING: Control flow encountered bad instruction data */

void FUN_00004c6c(int param_1)

{
  DAT_00009098 = -1;
  DAT_0000909c = -1;
  DAT_000090a0 = 0xffffffff;
  DAT_000090a4 = 0xffffffff;
  if ((*(int *)(param_1 * 0x68 + 0x8cc0) != 0) || (*(int *)(param_1 * 0x68 + 0x8e60) != 0)) {
    if (*(int *)(param_1 * 0x68 + 0x8cc0) == 1) {
      DAT_00009098 = param_1;
    }
    if (*(int *)(param_1 * 0x68 + 0x8e60) == 1) {
      DAT_0000909c = param_1;
    }
    FUN_000078ec(&DAT_00009098);
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ==== 5154 FUN_00005154 ====

/* WARNING: Control flow encountered bad instruction data */

void FUN_00005154(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  undefined8 uVar1;
  undefined1 auStack_30 [48];
  
  uVar1 = FUN_000057a8(0,param_3,0);
  FUN_00004e04(param_1,param_2,uVar1);
  uVar1 = FUN_00005840(0,param_3);
  FUN_00004e54(param_1,param_2,uVar1);
  uVar1 = FUN_00005914(0);
  FUN_00004ea4(param_1,param_2,uVar1);
  uVar1 = FUN_000058d4(0);
  FUN_00004f44(param_1,param_2,uVar1);
  uVar1 = FUN_000058f4(0);
  FUN_0000504c(param_1,param_2,uVar1);
  FUN_00005718(0,auStack_30);
  FUN_00004f94(param_1,param_2,0,auStack_30);
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ==== 5234 FUN_00005234 ====

/* WARNING: Control flow encountered bad instruction data */

void FUN_00005234(longlong param_1,undefined8 param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = (int)param_1;
  DAT_0000906c = 0;
  DAT_00009070 = 0;
  DAT_00009088 = 0;
  DAT_0000907c = 0;
  if ((&DAT_000090a8)[iVar3] == 1) {
    uVar1 = FUN_000078cc();
    if (param_1 == 0) {
      FUN_00004604(0,param_2,uVar1 >> 4 & 1);
    }
    if (param_1 == 1) {
      FUN_00004604(1,param_2,uVar1 >> 5 & 1);
    }
    FUN_00004690(0,param_1,param_2);
    FUN_000078dc(&DAT_00009000);
    DAT_00009070 = 0;
    FUN_00004824(0,param_1,param_2);
    iVar2 = (int)param_2 * 0x68 + iVar3 * 0x1a0;
    DAT_00009070 = *(undefined4 *)(iVar2 + 0x8cd4);
    if ((&DAT_000090a8)[iVar3] != 1) {
      *(undefined4 *)(iVar2 + 0x8d24) = 10;
    }
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ==== 5388 FUN_00005388 ====

/* WARNING: Control flow encountered bad instruction data */

void FUN_00005388(undefined8 param_1,undefined8 param_2)

{
  undefined8 uVar1;
  
  FUN_000078d4();
  DAT_000090a0 = 0xffffffff;
  DAT_000090a4 = 0xffffffff;
  DAT_00009098 = (undefined4)param_2;
  DAT_0000909c = DAT_00009098;
  FUN_000078ec(&DAT_00009098);
  uVar1 = FUN_00004650(0,param_2);
  FUN_00005154(0,param_2,uVar1);
  uVar1 = FUN_00004650(1,param_2);
  FUN_00005154(1,param_2,uVar1);
  FUN_00005234(param_1,param_2);
  DAT_000090a0 = 0xffffffff;
  DAT_000090a4 = 0xffffffff;
  DAT_00009098 = 0;
  DAT_0000909c = 0;
  FUN_000078ec();
  FUN_000078e4();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ==== 54f0 FUN_000054f0 ====

/* WARNING: Control flow encountered bad instruction data */

void FUN_000054f0(char *param_1)

{
  int iVar1;
  int iVar2;
  
  if ((DAT_00009740 + 1 < 0x10) && (param_1 != (char *)0x0)) {
    iVar1 = 0;
    if (0 < DAT_00009740) {
      iVar2 = 0;
      do {
        iVar1 = iVar1 + 1;
        if (*param_1 == *(char *)(iVar2 + 0x92c0)) {
          halt_baddata();
        }
        iVar2 = iVar2 + 0x48;
      } while (iVar1 < DAT_00009740);
    }
    *(char *)(DAT_00009740 * 0x48 + 0x92c0) = *param_1;
    iVar1 = DAT_00009740 * 0x48;
    *(undefined4 *)(iVar1 + 0x92c4) = *(undefined4 *)(param_1 + 4);
    *(undefined4 *)(iVar1 + 0x92c8) = *(undefined4 *)(param_1 + 8);
    *(undefined4 *)(iVar1 + 0x92cc) = *(undefined4 *)(param_1 + 0xc);
    *(undefined4 *)(iVar1 + 0x92d0) = *(undefined4 *)(param_1 + 0x10);
    *(undefined4 *)(iVar1 + 0x92d4) = *(undefined4 *)(param_1 + 0x14);
    *(undefined4 *)(iVar1 + 0x92d8) = *(undefined4 *)(param_1 + 0x18);
    *(undefined4 *)(iVar1 + 0x92dc) = *(undefined4 *)(param_1 + 0x1c);
    *(undefined4 *)(iVar1 + 0x92e0) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(iVar1 + 0x92e4) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(iVar1 + 0x92e8) = *(undefined4 *)(param_1 + 0x28);
    *(undefined4 *)(iVar1 + 0x92ec) = *(undefined4 *)(param_1 + 0x2c);
    *(undefined4 *)(iVar1 + 0x92f0) = *(undefined4 *)(param_1 + 0x30);
    *(undefined4 *)(iVar1 + 0x92f4) = *(undefined4 *)(param_1 + 0x34);
    *(undefined4 *)(iVar1 + 0x92f8) = *(undefined4 *)(param_1 + 0x38);
    *(undefined4 *)(iVar1 + 0x92fc) = *(undefined4 *)(param_1 + 0x3c);
    *(undefined4 *)(iVar1 + 0x9300) = *(undefined4 *)(param_1 + 0x40);
    DAT_00009740 = DAT_00009740 + 1;
    *(undefined4 *)(iVar1 + 0x9304) = *(undefined4 *)(param_1 + 0x44);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


// ==== 6f70 FUN_00006f70 ====

void FUN_00006f70(void)

{
  undefined1 auStack_50 [4];
  undefined *puStack_4c;
  undefined *puStack_48;
  undefined *puStack_44;
  undefined *puStack_40;
  undefined *puStack_3c;
  undefined *puStack_38;
  undefined4 uStack_34;
  undefined *puStack_30;
  undefined *puStack_2c;
  undefined *puStack_28;
  undefined *puStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  undefined *puStack_14;
  undefined *puStack_10;
  undefined *puStack_c;
  
  auStack_50[0] = 0xf;
  puStack_4c = &UNK_00006cc0;
  puStack_48 = &UNK_00006cf4;
  puStack_44 = &UNK_00006d14;
  puStack_40 = &UNK_00006d34;
  puStack_3c = &UNK_00006d40;
  puStack_38 = &UNK_00006d48;
  puStack_30 = &UNK_00006d50;
  puStack_2c = &UNK_00006d88;
  puStack_28 = &UNK_00006dc0;
  puStack_24 = &UNK_00006df8;
  puStack_20 = &UNK_00006e30;
  puStack_1c = &UNK_00006e68;
  puStack_18 = &UNK_00006ea0;
  puStack_14 = &UNK_00006ed4;
  puStack_10 = &UNK_00006f08;
  uStack_34 = 0;
                    /* WARNING: Subroutine does not return */
  puStack_c = &UNK_00006f3c;
  FUN_000054f0(auStack_50);
}


