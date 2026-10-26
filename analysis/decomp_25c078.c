// ===== FUN_0025c078 @ 0025c078 =====
// callers: FUN_00243680, FUN_00243d80, FUN_002440a8, FUN_00244228, FUN_00244d88, FUN_00244f68, FUN_00244c70, FUN_00245ae8, FUN_00245e78, FUN_00246fa0, FUN_002474e0, FUN_00247760, FUN_00247580, FUN_00247a40, FUN_002475f0, FUN_00247d28, FUN_002472d8, FUN_00248058, FUN_00248200, FUN_00248390, FUN_0025ed48, FUN_0024da50
// callees: FUN_0025ba50
// strings: 

void FUN_0025c078(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined *puVar1;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined8 uStack_18;
  undefined8 uStack_10;
  undefined8 uStack_8;
  
  puVar1 = PTR_FUN_00282158;
  PTR_FUN_00282158 = FUN_0025b770;
  uStack_38 = param_2;
  uStack_30 = param_3;
  uStack_28 = param_4;
  uStack_20 = param_5;
  uStack_18 = param_6;
  uStack_10 = param_7;
  uStack_8 = param_8;
  FUN_0025ba50(param_1,&uStack_38);
  PTR_FUN_00282158 = puVar1;
  return;
}


