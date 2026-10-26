// ===== FUN_0025c7d0 @ 0025c7d0 =====
// callers: FUN_00201180, FUN_0020df40, FUN_00223bb0, FUN_00245ae8, FUN_00245e78, FUN_00246fa0, FUN_00247760, FUN_00247a40, FUN_002475f0, FUN_002472d8, FUN_0025d790, FUN_0025ed48
// callees: sceSifGetReg, FUN_0025eea0, FUN_0025c3e8, FUN_0025c578, FUN_0025ee58, FUN_0025c130, FUN_0025c108, sceSifSetReg
// strings: 

void FUN_0025c7d0(void)

{
  long lVar1;
  
  FUN_0025ee58();
  if (DAT_00282160 != 0) {
    FUN_0025eea0();
    return;
  }
  DAT_00282160 = 1;
  FUN_0025eea0();
  FUN_0025c130();
  FUN_0025ee58();
  DAT_00763520 = 0x20;
  DAT_00763500 = 1;
  DAT_00763514 = &DAT_20762500;
  DAT_00763504 = &DAT_20761d00;
  DAT_0076351c = &DAT_20762d00;
  DAT_00763508 = 0x20;
  DAT_0076350c = 0;
  DAT_00763510 = 0;
  DAT_00763518 = 0x20;
  DAT_00763524 = 0;
  FUN_0025c3e8(0xffffffff80000008,0x25cad0,0x763500);
  FUN_0025c3e8(0xffffffff80000009,0x25cd08,0x763500);
  FUN_0025c3e8(0xffffffff8000000a,0x25cef8,0x763500);
  FUN_0025c3e8(0xffffffff8000000c,0x25cbe8,0x763500);
  FUN_0025eea0();
  lVar1 = sceSifGetReg(0xffffffff80000002);
  if (lVar1 == 0) {
    DAT_00761d4c = 1;
    FUN_0025c578(0xffffffff80000002,0x761d40,0x10,0,0,0);
    do {
      lVar1 = FUN_0025c108(0);
    } while (lVar1 == 0);
    sceSifSetReg(0xffffffff80000002,1);
    return;
  }
  return;
}


