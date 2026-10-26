// ===== FUN_0025e7c0 @ 0025e7c0 =====
// callers: FUN_0025e960
// callees: sceSifCallRpc, sceSifBindRpc
// strings: 

undefined4 FUN_0025e7c0(void)

{
  undefined4 uVar1;
  int iVar2;
  long lVar3;
  
  if (DAT_00282208 < 0) {
    while (lVar3 = sceSifBindRpc(0x765100,0xffffffff80000006,0), -1 < lVar3) {
      if (DAT_00765124 != 0) {
        DAT_00282208 = 0;
        lVar3 = sceSifCallRpc(0x765100,0xff,0,0,0,0x764f00,4,0);
        if (lVar3 < 0) {
          return 0xfffeffff;
        }
        DAT_00765128 = DAT_00764f00;
        return 0;
      }
      iVar2 = 0x100000;
      do {
        iVar2 = iVar2 + -1;
      } while (iVar2 != -1);
    }
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}


