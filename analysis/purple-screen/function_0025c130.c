// ===== FUN_0025c130 @ 0025c130 =====
// callers: FUN_0025c7d0
// callees: FUN_0025eea0, FUN_0025b068, sceSifGetReg, AddDmacHandler, FUN_0025ee58, sceSifSetDChain, FlushCache, FUN_0025c578, sceSifSetReg
// strings: 

void FUN_0025c130(void)

{
  uint uVar1;
  undefined4 *puVar2;
  long lVar3;
  ulong uVar4;
  undefined8 uVar5;
  int iVar6;
  
  FUN_0025ee58();
  if (DAT_0028215c != 0) {
    FUN_0025eea0();
    return;
  }
  DAT_0028215c = 1;
  puVar2 = &DAT_00761b80;
  DAT_00761b58 = &DAT_20761a80;
  DAT_00761b74 = &DAT_00761c80;
  DAT_00761b5c = &DAT_20761b00;
  DAT_00761b68 = 0x20;
  DAT_00761b60 = 0;
  iVar6 = 0x1f;
  DAT_00761b64 = &DAT_00761b80;
  DAT_00761b6c = 0;
  DAT_00761b70 = 0;
  do {
    *puVar2 = 0;
    iVar6 = iVar6 + -1;
    puVar2[1] = 0;
    puVar2 = puVar2 + 2;
  } while (-1 < iVar6);
  iVar6 = 0x1f;
  puVar2 = &DAT_00761cfc;
  do {
    *puVar2 = 0;
    iVar6 = iVar6 + -1;
    puVar2 = puVar2 + -1;
  } while (-1 < iVar6);
  DAT_00761b80 = &LAB_0025c0f8;
  DAT_00761b88 = &LAB_0025c0d8;
  DAT_00761b8c = &DAT_00761b58;
  DAT_00761b84 = &DAT_00761b58;
  FUN_0025eea0();
  FlushCache(0);
  uVar1 = REG_DMAC_STAT;
  if ((uVar1 & 0x20) != 0) {
    REG_DMAC_STAT = 0x20;
  }
  uVar1 = REG_DMAC_5_SIF0_CHCR;
  if ((uVar1 & 0x100) == 0) {
    sceSifSetDChain();
  }
  DAT_00761b54 = AddDmacHandler(5,0x25c5f8,0);
  FUN_0025b068(5);
  lVar3 = sceSifGetReg(0xffffffff80000000);
  DAT_00761b60 = (undefined4)lVar3;
  if (lVar3 != 0) {
    DAT_00761b50 = &DAT_00761a80;
    FUN_0025c578(0xffffffff80000000,0x761b40,0x14,0,0,0);
    return;
  }
  DAT_00761b60 = 0;
  do {
    uVar4 = sceSifGetReg(4);
  } while ((uVar4 & 0x20000) == 0);
  uVar5 = sceSifGetReg(2);
  DAT_00761b60 = (undefined4)uVar5;
  sceSifSetReg(0xffffffff80000000,uVar5);
  sceSifSetReg(0xffffffff80000001,0x761b58);
  DAT_00761b50 = &DAT_00761a80;
  DAT_00761b4c = 0;
  FUN_0025c578(0xffffffff80000002,0x761b40,0x14,0,0,0);
  return;
}


