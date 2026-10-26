// ===== FUN_00245e78 @ 00245e78 =====
// callers: FUN_0021f400
// callees: WaitSema, FUN_002466a0, sceSifBindRpc, SignalSema, CreateSema, FUN_0025c078, FUN_0025c7d0, sceSifCallRpc
// strings: "bind error libmc \n", "libmc: too old release of mcserv.irx\n", "libmc: too old release of mcman.irx\n"

int FUN_00245e78(void)

{
  int iVar1;
  long lVar2;
  undefined1 auStack_a0 [4];
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_8c;
  
  if (DAT_0027f7cc < 0) {
    uStack_8c = 0;
    uStack_9c = 1;
    uStack_98 = 1;
    DAT_0027f7cc = CreateSema(auStack_a0);
  }
  FUN_002466a0(0,0,0);
  WaitSema(DAT_0027f7cc);
  FUN_0025c7d0(0);
  while( true ) {
    lVar2 = sceSifBindRpc(0x75f1c0,0xffffffff80000400,0);
    if (lVar2 < 0) {
      FUN_0025c078(0x29a3b0);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if (DAT_0075f1e4 != 0) break;
    iVar1 = 0x100000;
    do {
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  lVar2 = sceSifCallRpc(0x75f1c0,0xfe,0,0x75f240,0x30,0x760780,0xc,0);
  SignalSema(DAT_0027f7cc);
  if (lVar2 < 0) {
    DAT_0075f1e4 = 0;
    iVar1 = (int)lVar2 + -100;
  }
  else if (DAT_00760784 < 0x20a) {
    FUN_0025c078(0x29a3c8);
    DAT_0075f1e4 = 0;
    iVar1 = -0x78;
  }
  else {
    iVar1 = DAT_00760780;
    if (DAT_00760788 < 0x20e) {
      FUN_0025c078(0x29a3f0);
      DAT_0075f1e4 = 0;
      iVar1 = -0x79;
    }
  }
  return iVar1;
}


