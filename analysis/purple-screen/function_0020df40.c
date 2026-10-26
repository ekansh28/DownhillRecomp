// ===== FUN_0020df40 @ 0020df40 =====
// callers: FUN_001b6f80
// callees: FUN_00247760, FUN_0025ed10, FUN_0020e018, FUN_00247a40, FUN_0025ed48, FUN_0025da28, FUN_0025c7d0, FUN_00247c28
// strings: "cdrom0:\\IOPRP270.IMG;1"

void FUN_0020df40(void)

{
  long lVar1;
  
  FUN_0025c7d0(0);
  FUN_00247760(0);
  do {
    lVar1 = FUN_0025ed48(0x298140);
  } while (lVar1 == 0);
  do {
    lVar1 = FUN_0025ed10();
  } while (lVar1 == 0);
  FUN_0025c7d0(0);
  FUN_00247760(0);
  FUN_00247c28(2);
  FUN_0025da28();
  do {
    lVar1 = FUN_00247a40(0);
  } while (lVar1 != 2);
  FUN_0020e018();
  DAT_0029da18 = 1;
  do {
    lVar1 = FUN_00247a40(0);
  } while (lVar1 != 2);
  return;
}


