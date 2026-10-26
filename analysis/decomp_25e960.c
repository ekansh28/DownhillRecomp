// ===== FUN_0025e960 @ 0025e960 =====
// callers: FUN_0025eb88
// callees: FUN_0025e8c0, sceSifCallRpc, FUN_00254b30, FUN_0025e7c0, FUN_00254050
// strings: 

undefined4
FUN_0025e960(undefined8 param_1,long param_2,undefined8 *param_3,undefined4 *param_4,
            undefined8 param_5)

{
  undefined4 uVar1;
  undefined8 *puVar2;
  long lVar3;
  undefined8 *puVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  
  lVar3 = FUN_0025e7c0();
  uVar1 = 0xffff0000;
  if (-1 < lVar3) {
    lVar3 = FUN_0025e8c0();
    if (lVar3 == 0) {
      FUN_00254b30(0x764f08,param_1,0xfc);
      DAT_00765003 = 0;
      if (param_3 == (undefined8 *)0x0) {
        DAT_00765004 = 0;
        DAT_00764f00 = 0;
      }
      else if (param_2 < 0xfd) {
        FUN_00254050(0x765004,param_3,param_2);
        DAT_00764f00 = (undefined4)param_2;
      }
      else {
        puVar4 = (undefined8 *)&DAT_00765004;
        if ((((uint)param_3 | 0x765004) & 7) == 0) {
          puVar2 = param_3 + 0x1c;
          do {
            uVar5 = param_3[1];
            uVar6 = param_3[2];
            uVar7 = param_3[3];
            *puVar4 = *param_3;
            puVar4[1] = uVar5;
            puVar4[2] = uVar6;
            puVar4[3] = uVar7;
            param_3 = param_3 + 4;
            puVar4 = puVar4 + 4;
          } while (param_3 != puVar2);
        }
        else {
          puVar2 = param_3 + 0x1c;
          do {
            uVar5 = param_3[1];
            uVar6 = param_3[2];
            uVar7 = param_3[3];
            *puVar4 = *param_3;
            puVar4[1] = uVar5;
            puVar4[2] = uVar6;
            puVar4[3] = uVar7;
            param_3 = param_3 + 4;
            puVar4 = puVar4 + 4;
          } while (param_3 != puVar2);
        }
        uVar5 = param_3[1];
        uVar6 = param_3[2];
        uVar1 = *(undefined4 *)(param_3 + 3);
        *puVar4 = *param_3;
        puVar4[1] = uVar5;
        puVar4[2] = uVar6;
        *(undefined4 *)(puVar4 + 3) = uVar1;
        DAT_00764f00 = 0xfc;
      }
      lVar3 = sceSifCallRpc(0x765100,param_5,0,0x764f00,0x200,0x764f00,8,0);
      uVar1 = DAT_00764f00;
      if (lVar3 < 0) {
        uVar1 = 0xfffeffff;
      }
      else {
        *param_4 = DAT_00764f04;
      }
    }
    else {
      uVar1 = 0xfffefffc;
    }
  }
  return uVar1;
}


