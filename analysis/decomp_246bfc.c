// ===== FUN_00246bb0 @ 00246bb0 =====
// callers: FUN_002474e0, FUN_00247580, FUN_00248200
// callees: WaitSema, CreateSema, SetAlarm, DeleteSema
// strings: 

void FUN_00246bb0(undefined2 param_1)

{
  undefined8 uVar1;
  undefined1 auStack_50 [4];
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_3c;
  
  uStack_4c = 1;
  uStack_48 = 0;
  uStack_3c = 0;
  uVar1 = CreateSema(auStack_50);
  SetAlarm(param_1,0x246b88,uVar1);
  WaitSema(uVar1);
  DeleteSema(uVar1);
  return;
}


