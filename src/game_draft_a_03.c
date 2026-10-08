extern void nullsub_2(void);
#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"
#include <stdint.h>
#include <stdlib.h>

/* Unverified draft; integration deferred */
/* TODO: Missing SDK and external adapters require fail-fast during integration */
extern uint32 sub_80022B24();
extern uint32 sub_80022CC0();
extern uint32 sub_80023500();
extern uint32 sub_80029DD4();
extern uint32 sub_8002AFE8();
extern uint32 sub_80031224();
extern uint32 sub_80031308();
extern uint32 sub_8003133C();
extern uint32 sub_80032FD0();



extern uint32 sub_80040D64();
extern uint32 sub_800410B8();
extern uint32 sub_800449A0();
extern uint32 sub_80044F58();
extern uint32 sub_800467A0();
extern uint32 sub_8004EB88();
extern uint32 sub_80050A08();
extern uint32 sub_80051550();
extern uint32 sub_800516E8();
extern uint32 sub_80052078();
extern uint32 sub_80052228();
extern uint32 sub_800522D0();
extern uint32 sub_800524AC();
extern uint32 sub_80053774();
extern uint32 sub_80053A28();
extern uint32 sub_800540C0();
extern uint32 sub_80054184();
extern uint32 sub_80054414();
extern uint32 sub_8005B278();
extern uint32 sub_8005CC48();
extern uint32 sub_8005CDA8();
extern uint32 sub_8005CDD8();
extern void sub_8005CF98();
extern uint32 sub_8005D138();
extern uint32 sub_8005D3C8();
extern uint32 sub_8005D658(uint32 rotation, uint32 matrix);
extern uint32 sub_8005DFE4();
extern uint32 sub_8005E290();
extern uint32 sub_8005E814();
extern uint32 sub_8005EEB8();
extern uint32 sub_80060DB8();
extern uint32 sub_80063C94();
extern uint32 sub_80065768();
extern uint32 sub_80067A6C();
extern uint32 sub_80067AE8();

uint32 sub_80019648(uint32 a1, uint32 a2, uint32 a3, uint32 a4)
{
    FUNCTION_MARKER(0x80019648u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

  sint32 v4; 
  sint32 v5; 
  sint32 v6; 
  sint32 v7; 
  uint16 v8; 
  sint32 v9; 
  sint32 result; 
  uint8 v11; 
  sint32 v12; 
  sint32 v13; 
  sint32 v14; 
  sint32 v15; 
  sint32 v16; 
  sint32 v17; 
  sint32 v18; 
  sint32 v19; 
  sint32 v20; 
  uint32 v21; 
  sint32 v22; 
  sint32 v23; 
  sint32 v24; 
  sint32 v25; 
  sint32 v26; 
  sint32 v27; 
  sint32 v28; 
  sint32 v29; 
  sint32 v30; 
  sint32 v31; 
  sint32 v32; 
  uint32 v33; 
  sint32 v34; 
  sint32 v35; 
  sint32 v36; 
  sint32 v37; 
  sint32 v38; 
  sint32 v39; 
  sint32 v40; 
  sint32 v41; 
  sint32 v42; 
  sint32 v43; 
  uint32 v44; 
  sint32 v45; 
  sint32 v46; 
  sint32 v47; 
  uint32 frame[36];

  sint32 v49; 
  sint32 v50; 
  sint32 v51; 
  sint32 v52; 
  sint32 v53; 
  sint32 v54; 
  sint32 v55; 

  v4 = 56 * a1 - 2146762464;
  sub_80019498((uint32)v4, draft_local_address(frame, sizeof(frame)), a2, a3, a4);
  v49 = frame[0]; v50 = frame[1]; v51 = frame[2];
  v52 = frame[6]; v53 = frame[8]; v54 = frame[12]; v55 = frame[17];
  v5 = v53 - v49;
  if ( v53 - v49 < 0 )
    v5 = v49 - v53;
  v6 = v55 - v50;
  if ( v55 - v50 < 0 )
    v6 = v50 - v55;
  v7 = v52 - v51;
  if ( v52 - v51 < 0 )
    v7 = v51 - v52;
  v8 = 0;
  if ( v6 >= v5 )
    v8 = v6 >= v7;
  v9 = v8;
  if ( v7 >= v5 && v7 >= v6 )
    v9 = 2;
  result = v9 < 2;
  if ( v9 == 1 )
  {
    v25 = v7;
    if ( v5 >= v7 )
      v25 = v5;
    if ( !v25 )
      v25 = 1;
    if ( v25 == -1 && v6 == 0x80000000 )
      abort(); /* TODO: Original BREAK exception requires an integration boundary */
    v27 = v6 / v25;
    v26 = v6 / v25;
    v28 = v6 / v25 < 5;
    if ( v25 / 2 < v6 % v25 )
    {
      v27 = v26 + 1;
      v28 = v26 + 1 < 5;
    }
    if ( !v28 )
      v27 = 4;
    v29 = 90 * v25 / 100;
    w_u16((uint32)((v4 + 52)), v27);
    if ( !v29 )
      v29 = 1;
    w_u16((uint32)((v4 + 54)), v29 / 2);
    result = v55 - v50;
    if ( v55 - v50 < 0 )
      result = v50 - v55;
    if ( !v27 )
      abort(); /* TODO: Original BREAK exception requires an integration boundary */
    if ( v27 == -1 && result == 0x80000000 )
      abort(); /* TODO: Original BREAK exception requires an integration boundary */
    v30 = result / v27;
    v31 = 0;
    if ( v27 > 0 )
    {
      v32 = v50;
      v33 = (uint32)v4;
      do
      {
        v34 = v32 + v30 / 2;
        v32 += v30;
        w_u16((uint32)(v33 + 2u * (10)), (v49 + v54) / 2);
        v35 = v51;
        v36 = v52;
        ++v31;
        w_u16((uint32)(v33 + 2u * (11)), v34);
        w_u16((uint32)(v33 + 2u * (12)), (v35 + v36) / 2);
        result = v31 < v27;
        v33 += 2u * (4);
      }
      while ( v31 < v27 );
    }
  }
  else if ( v9 >= 2 )
  {
    result = 2;
    v11 = v9 == 2;
    v13 = v6;
    if ( v11 )
    {
      if ( v5 >= v6 )
        v13 = v5;
      if ( !v13 )
        v13 = 1;
      v37 = v7 / v13;
      if ( v13 == -1 && v7 == 0x80000000 )
        abort(); /* TODO: Original BREAK exception requires an integration boundary */
      v38 = v7 / v13;
      v39 = v37 < 5;
      if ( v13 / 2 < v7 % v13 )
      {
        v38 = v37 + 1;
        v39 = v37 + 1 < 5;
      }
      if ( !v39 )
        v38 = 4;
      v40 = 90 * v13 / 100;
      w_u16((uint32)((v4 + 52)), v38);
      if ( !v40 )
        v40 = 1;
      w_u16((uint32)((v4 + 54)), v40 / 2);
      result = v52 - v51;
      if ( v52 - v51 < 0 )
        result = v51 - v52;
      if ( !v38 )
        abort(); /* TODO: Original BREAK exception requires an integration boundary */
      if ( v38 == -1 && result == 0x80000000 )
        abort(); /* TODO: Original BREAK exception requires an integration boundary */
      v41 = result / v38;
      v42 = 0;
      if ( v38 > 0 )
      {
        v43 = v51;
        v44 = (uint32)v4;
        do
        {
          v45 = v43 + v41 / 2;
          v43 += v41;
          w_u16((uint32)(v44 + 2u * (10)), (v49 + v54) / 2);
          v46 = v50;
          v47 = v55;
          ++v42;
          w_u16((uint32)(v44 + 2u * (12)), v45);
          w_u16((uint32)(v44 + 2u * (11)), (v46 + v47) / 2);
          result = v42 < v38;
          v44 += 2u * (4);
        }
        while ( v42 < v38 );
      }
    }
  }
  else
  {
    v11 = v9 == 0;
    v12 = v7;
    if ( v11 )
    {
      if ( v6 >= v7 )
        v12 = v6;
      if ( !v12 )
        v12 = 1;
      if ( v12 == -1 && v5 == 0x80000000 )
        abort(); /* TODO: Original BREAK exception requires an integration boundary */
      v15 = v5 / v12;
      v14 = v5 / v12;
      v16 = v5 / v12 < 5;
      if ( v12 / 2 < v5 % v12 )
      {
        v15 = v14 + 1;
        v16 = v14 + 1 < 5;
      }
      if ( !v16 )
        v15 = 4;
      v17 = 90 * v12 / 100;
      w_u16((uint32)((v4 + 52)), v15);
      if ( !v17 )
        v17 = 1;
      w_u16((uint32)((v4 + 54)), v17 / 2);
      result = v54 - v49;
      if ( v54 - v49 < 0 )
        result = v49 - v54;
      if ( !v15 )
        abort(); /* TODO: Original BREAK exception requires an integration boundary */
      if ( v15 == -1 && result == 0x80000000 )
        abort(); /* TODO: Original BREAK exception requires an integration boundary */
      v18 = result / v15;
      v19 = 0;
      if ( v15 > 0 )
      {
        v20 = v49;
        v21 = (uint32)v4;
        do
        {
          v22 = v20 + v18 / 2;
          v20 += v18;
          w_u16((uint32)(v21 + 2u * (11)), (v50 + v55) / 2);
          v23 = v51;
          v24 = v52;
          ++v19;
          w_u16((uint32)(v21 + 2u * (10)), v22);
          w_u16((uint32)(v21 + 2u * (12)), (v23 + v24) / 2);
          result = v19 < v15;
          v21 += 2u * (4);
        }
        while ( v19 < v15 );
      }
    }
  }
  return result;
}

uint32 sub_80019000(uint32 a1)
{
    FUNCTION_MARKER(0x80019000u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

  uint32 v1; 
  uint32 v2; 
  sint32 v3; 
  uint32 v4; 
  uint32 v5; 
  uint32 v6; 
  sint32 v7; 
  uint32 v8; 
  uint32 v9; 
  uint32 v10; 
  sint32 v11; 
  uint8 v12; 
  uint32 v13; 
  uint32 v14; 
  uint32 v15; 
  uint16 v16; 
  uint16 v17; 
  uint16 v18; 
  uint16 v19; 
  uint32 v20; 
  uint32 v21; 
  sint32 v22; 
  sint32 v23; 
  sint32 v24; 
  sint32 v25; 
  sint32 v26; 
  sint32 v27; 
  sint32 v28; 
  uint32 v29; 
  uint32 v30; 
  uint32 v31; 
  uint32 v32; 
  uint32 v33; 
  sint16 v34; 
  sint32 result; 

  v1 = 0;
  v2 = (uint32)(56u * (uint16)a1 + 0x800B0120u);
  v3 = r_u32((uint32)(v2 + 4u * (1)));
  v4 = r_u32((uint32)(v2 + 4u * (2)));
  v5 = (uint32)r_u32((uint32)(v2 + 4u * (3)));
  v6 = sub_80011A98(16 * v4);
  v7 = (sint32)v6;
  if ( v4 )
  {
    v8 = v6;
    do
    {
      w_u32((uint32)(v8), 0);
      w_u32((uint32)(v8 + 4u * (1)), 0);
      w_u32((uint32)(v8 + 4u * (2)), 0);
      w_u32((uint32)(v8 + 4u * (3)), 0);
      ++v1;
      v8 += 4u * (4);
    }
    while ( v1 < v4 );
  }
  while ( r_u32((uint32)(v5)) != 8 )
  {
    v9 = r_u32((uint32)((v5 += 4u, v5 - 4u)));
    v10 = (uint16)((uint32)(v9) >> 16);
    v11 = v9 & 7;
    v12 = v10 == 0;
    v13 = v10 - 1;
    if ( !v12 )
    {
      v14 = (uint32)v5 + 2;
      do
      {
        v15 = v13;
        switch ( v11 )
        {
          case 0:
            v5 += 4u * (3);
            sub_80018FA0(r_u16((uint32)((v14 + 2u * (1)))), r_u16((uint32)((v14 + 2u * (4)))), v7, v3);
            sub_80018FA0(r_u16((uint32)((v14 + 2u * (2)))), r_u16((uint32)((v14 + 2u * (4)))), v7, v3);
            sub_80018FA0(r_u16((uint32)((v14 + 2u * (3)))), r_u16((uint32)((v14 + 2u * (4)))), v7, v3);
            w_u8((uint32)(v14 + 1u * (1)), 48);
            v14 += 1u * (12);
            goto LABEL_14;
          case 1:
            v5 += 4u * (4);
            sub_80018FA0(r_u16((uint32)((v14 + 2u * (1)))), r_u16((uint32)((v14 + 2u * (5)))), v7, v3);
            sub_80018FA0(r_u16((uint32)((v14 + 2u * (2)))), r_u16((uint32)((v14 + 2u * (5)))), v7, v3);
            sub_80018FA0(r_u16((uint32)((v14 + 2u * (3)))), r_u16((uint32)((v14 + 2u * (5)))), v7, v3);
            sub_80018FA0(r_u16((uint32)((v14 + 2u * (4)))), r_u16((uint32)((v14 + 2u * (5)))), v7, v3);
            w_u8((uint32)(v14 + 1u * (1)), 56);
            v14 += 1u * (16);
            goto LABEL_14;
          case 2:
            v5 += 4u * (5);
            sub_80018FA0(r_u16((uint32)((v14 + 2u * (5)))), r_u16((uint32)((v14 + 2u * (8)))), v7, v3);
            sub_80018FA0(r_u16((uint32)((v14 + 2u * (6)))), r_u16((uint32)((v14 + 2u * (8)))), v7, v3);
            v16 = r_u16((uint32)((v14 + 2u * (7))));
            v17 = r_u16((uint32)((v14 + 2u * (8))));
            v14 += 1u * (20);
            sub_80018FA0(v16, v17, v7, v3);
            v15 = v13;
            break;
          case 3:
            v5 += 4u * (7);
            sub_80018FA0(r_u16((uint32)((v14 + 2u * (7)))), r_u16((uint32)((v14 + 2u * (11)))), v7, v3);
            sub_80018FA0(r_u16((uint32)((v14 + 2u * (8)))), r_u16((uint32)((v14 + 2u * (11)))), v7, v3);
            sub_80018FA0(r_u16((uint32)((v14 + 2u * (9)))), r_u16((uint32)((v14 + 2u * (11)))), v7, v3);
            v18 = r_u16((uint32)((v14 + 2u * (10))));
            v19 = r_u16((uint32)((v14 + 2u * (11))));
            v14 += 1u * (28);
            sub_80018FA0(v18, v19, v7, v3);
            v15 = v13;
            break;
          case 4:
          case 6:
            sub_80018FA0(r_u16((uint32)((v14 + 2u * (7)))), r_u16((uint32)((v14 + 2u * (10)))), v7, v3);
            sub_80018FA0(r_u16((uint32)((v14 + 2u * (8)))), r_u16((uint32)((v14 + 2u * (10)))), v7, v3);
            sub_80018FA0(r_u16((uint32)((v14 + 2u * (9)))), r_u16((uint32)((v14 + 2u * (10)))), v7, v3);
            w_u8((uint32)(v14 + 1u * (1)), 52);
            w_u8((uint32)(v5), -106);
            w_u8((uint32)(v14 - 1u * (1)), -106);
            w_u8((uint32)(v14), -106);
            v14 += 1u * (24);
            v5 += 4u * (6);
            goto LABEL_14;
          case 5:
          case 7:
            sub_80018FA0(r_u16((uint32)((v14 + 2u * (7)))), r_u16((uint32)((v14 + 2u * (11)))), v7, v3);
            sub_80018FA0(r_u16((uint32)((v14 + 2u * (8)))), r_u16((uint32)((v14 + 2u * (11)))), v7, v3);
            sub_80018FA0(r_u16((uint32)((v14 + 2u * (9)))), r_u16((uint32)((v14 + 2u * (11)))), v7, v3);
            sub_80018FA0(r_u16((uint32)((v14 + 2u * (10)))), r_u16((uint32)((v14 + 2u * (11)))), v7, v3);
            w_u8((uint32)(v14 + 1u * (1)), 60);
            w_u8((uint32)(v5), -106);
            w_u8((uint32)(v14 - 1u * (1)), -106);
            w_u8((uint32)(v14), -106);
            v14 += 1u * (28);
            v5 += 4u * (7);
LABEL_14:
            v15 = v13;
            break;
          default:
            break;
        }
        --v13;
      }
      while ( v15 );
    }
  }
  v20 = 0;
  if ( v4 )
  {
    v21 = (uint32)v7;
    do
    {
      v22 = r_u32((uint32)(v21 + 4u * (3)));
      ++v20;
      if ( v22 )
      {
        if ( v22 == -1 && r_u32((uint32)(v21)) == 0x80000000 )
          abort(); /* TODO: Original BREAK exception requires an integration boundary */
        v23 = (sint32)r_u32(v21) / v22;
        v24 = r_u32((uint32)(v21 + 4u * (1)));
        v25 = r_u32((uint32)(v21 + 4u * (3)));
        if ( !v25 )
          abort(); /* TODO: Original BREAK exception requires an integration boundary */
        if ( v25 == -1 && v24 == 0x80000000 )
          abort(); /* TODO: Original BREAK exception requires an integration boundary */
        v26 = v24 / v25;
        v27 = r_u32((uint32)(v21 + 4u * (2)));
        v28 = r_u32((uint32)(v21 + 4u * (3)));
        if ( v28 == -1 && v27 == 0x80000000 )
          abort(); /* TODO: Original BREAK exception requires an integration boundary */
        w_u32((uint32)(v21), v23);
        w_u32((uint32)(v21 + 4u * (1)), v26);
        w_u32((uint32)(v21 + 4u * (2)), v27 / v28);
      }
      v21 += 4u * (4);
    }
    while ( v20 < v4 );
  }
  sub_80011AF8(v3);
  v29 = sub_80011A98(8 * v4);
  v30 = v29;
  v31 = 0;
  if ( v4 )
  {
    v32 = v29;
    v33 = (uint32)v7;
    do
    {
      w_u16((uint32)(v32), r_u16((uint32)(v33)));
      ++v31;
      w_u16((uint32)(v32 + 2u * (1)), r_u16((uint32)(v33 + 2u * (2))));
      v34 = r_u16((uint32)(v33 + 2u * (4)));
      v33 += 2u * (8);
      w_u16((uint32)(v32 + 2u * (2)), v34);
      v32 += 2u * (4);
    }
    while ( v31 < v4 );
  }
  result = sub_80011AF8(v7);
  w_u32((uint32)(v2 + 4u * (1)), v30);
  return result;
}

uint32 sub_80016738(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a9, uint32 a10)
{
    FUNCTION_MARKER(0x80016738u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */
    uint32 gte_t1, gte_t4, gte_t5, gte_t6;

  sint32 result; 
  sint32 v14; 
  sint32 v20; 
  uint32 v21; 
  uint32 v22; 
  sint8 v24; 
  sint16 v26; 
  uint32 v29; 

  a9 = (uint16)a9;
  a10 = (uint16)a10;
  w_u32((uint32)(0x1F800030u), r_u32((uint32)(a1 + 4u * (2))) - r_u32((uint32)(0x800BBFCCu)));
  w_u32((uint32)(0x1F800028u), r_u32((uint32)(a1)) - r_u32((uint32)(0x800BBFC4u)));
  w_u32((uint32)(0x1F80002Cu), r_u32((uint32)(a1 + 4u * (1))) - r_u32((uint32)(0x800BBFC8u)));
  sub_8005CC48(-2146713636, 528482344, 528482344);
  result = 0;
  if ( r_u32((uint32)(0x1F800030u)) <= 0x9C3Fu )
  {
    result = 0;
    if ( (uint32)(r_u32((uint32)(0x1F800028u)) + 20000) <= 0x9C40 )
    {
      result = 0;
      if ( (uint32)(r_u32((uint32)(0x1F80002Cu)) + 20000) <= 0x9C40 )
      {
        if ( r_u32((uint32)(0x1F800030u)) < 32 )
          w_u32((uint32)(0x1F800030u), 32);
        v14 = 16 * (uint16)a2 - 2146695836;
        gte_t4 = 0;
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
draft_gte_control(1u, gte_t4);
draft_gte_control(3u, gte_t4);
        gte_t4 = 4096;
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
draft_gte_control(0u, gte_t4);
draft_gte_control(2u, gte_t4);
draft_gte_control(4u, gte_t4);
        gte_t4 = r_u32((uint32)(0x1F800028u));
        gte_t5 = r_u32((uint32)(0x1F80002Cu));
        gte_t6 = r_u32((uint32)(0x1F800030u));
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
draft_gte_control(5u, gte_t4);
draft_gte_control(6u, gte_t5);
draft_gte_control(7u, gte_t6);
        v20 = -(sint16)r_u16((uint32)((v14 + 12))) * a3;
        v21 = (uint32)r_u32((uint32)(0x80071680u));
        w_u32((uint32)(0x80071680u), r_u32((uint32)(0x80071680u)) + (40));
        v22 = (uint32)v21;
        w_u16((uint32)(0x1F800020u), v20 / 2048);
        gte_t1 = 528482336;
        w_u16((uint32)(0x1F800022u), (sint32)((uint32)(-(sint32)(sint16)r_u16((uint32)((v14 + 14)))) * a4) / 2048);
        w_u16((uint32)(0x1F800024u), 0);
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
draft_gte_data(0u, r_u32(gte_t1 + 0u));
draft_gte_data(1u, r_u32(gte_t1 + 4u));
draft_gte_command(0x180001u);
        w_u8((uint32)(v21 + 1u * (3)), 9);
        v24 = 44;
        w_u8((uint32)(v21 + 1u * (7)), 44);
        if ( a9 )
          v24 = 46;
        w_u8((uint32)(v21 + 1u * (7)), v24);
        w_u8((uint32)(v21 + 1u * (4)), a10);
        w_u8((uint32)(v21 + 1u * (5)), a10);
        w_u8((uint32)(v21 + 1u * (6)), a10);
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
w_u32(v21 + 8u, draft_gte_read(14u));
        gte_t1 = 528482336;
        w_u16((uint32)(0x1F800020u), r_u16((uint32)(0x1F800020u)) + ((sint32)((uint32)(sint32)(sint16)r_u16((uint32)((v14 + 8))) * a3) / 2048));
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
draft_gte_data(0u, r_u32(gte_t1 + 0u));
draft_gte_data(1u, r_u32(gte_t1 + 4u));
draft_gte_command(0x180001u);
        v26 = r_u16((uint32)(v14));
        w_u16((uint32)((v22 + 22)), r_u16((uint32)(v14)));
        if ( (uint16)a9 )
          w_u16((uint32)((v22 + 22)), v26 | r_u16((uint32)(0x8007177Eu + 2u * (a9))));
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
w_u32(v21 + 16u, draft_gte_read(14u));
        gte_t1 = 528482336;
        w_u16((uint32)(0x1F800022u), r_u16((uint32)(0x1F800022u)) + ((sint32)((uint32)(sint32)(sint16)r_u16((uint32)((v14 + 10))) * a4) / 2048));
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
draft_gte_data(0u, r_u32(gte_t1 + 0u));
draft_gte_data(1u, r_u32(gte_t1 + 4u));
draft_gte_command(0x180001u);
        w_u16((uint32)((v22 + 14)), r_u16((uint32)((v14 + 2))));
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
w_u32(v21 + 32u, draft_gte_read(14u));
        gte_t1 = 528482336;
        w_u16((uint32)(0x1F800020u), r_u16((uint32)(0x1F800020u)) - ((sint32)((uint32)(sint32)(sint16)r_u16((uint32)((v14 + 8))) * a3) / 2048));
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
draft_gte_data(0u, r_u32(gte_t1 + 0u));
draft_gte_data(1u, r_u32(gte_t1 + 4u));
draft_gte_command(0x180001u);
        w_u8((uint32)((v22 + 12)), r_u8((uint32)((v14 + 4))));
        w_u8((uint32)((v22 + 13)), r_u8((uint32)((v14 + 6))));
        w_u8((uint32)((v22 + 20)), r_u8((uint32)((v14 + 4))) + r_u8((uint32)((v14 + 8))) - 1);
        w_u8((uint32)((v22 + 21)), r_u8((uint32)((v14 + 6))));
        w_u8((uint32)((v22 + 28)), r_u8((uint32)((v14 + 4))));
        w_u8((uint32)((v22 + 29)), r_u8((uint32)((v14 + 6))) + r_u8((uint32)((v14 + 10))) - 1);
        w_u8((uint32)((v22 + 36)), r_u8((uint32)((v14 + 4))) + r_u8((uint32)((v14 + 8))) - 1);
        w_u8((uint32)((v22 + 37)), r_u8((uint32)((v14 + 6))) + r_u8((uint32)((v14 + 10))) - 1);
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
w_u32(v21 + 24u, draft_gte_read(14u));
        if ( (uint32)(((sint32)r_u32((uint32)(0x1F800030u)) >> 4) - 1) < 0x9C3 )
        {
          v29 = (uint32)(4 * ((sint32)r_u32((uint32)(0x1F800030u)) >> 4) + r_u32((uint32)(0x8007184Cu)));
          w_u32((uint32)(v22), r_u32((uint32)(v22)) & 0xFF000000 | r_u32((uint32)(v29)) & 0xFFFFFF);
          w_u32((uint32)(v29), r_u32((uint32)(v29)) & 0xFF000000 | v22 & 0xFFFFFF);
        }
        return 1;
      }
    }
  }
  return result;
}

uint32 sub_80016358(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a9, uint32 a10)
{
    FUNCTION_MARKER(0x80016358u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */
    uint32 gte_t1, gte_t4, gte_t5, gte_t6;

  sint32 result; 
  sint32 v14; 
  sint32 v21; 
  sint32 v22; 
  sint8 v23; 
  sint16 v25; 
  uint32 v27; 

  w_u32((uint32)(0x1F800030u), r_u32((uint32)(a1 + 4u * (2))) - r_u32((uint32)(0x800BBFCCu)));
  w_u32((uint32)(0x1F800028u), r_u32((uint32)(a1)) - r_u32((uint32)(0x800BBFC4u)));
  w_u32((uint32)(0x1F80002Cu), r_u32((uint32)(a1 + 4u * (1))) - r_u32((uint32)(0x800BBFC8u)));
  sub_8005CC48(-2146713636, 528482344, 528482344);
  result = 0;
  if ( r_u32((uint32)(0x1F800030u)) <= 0x9C3Fu )
  {
    result = 0;
    if ( (uint32)(r_u32((uint32)(0x1F800028u)) + 20000) <= 0x9C40 )
    {
      result = 0;
      if ( (uint32)(r_u32((uint32)(0x1F80002Cu)) + 20000) <= 0x9C40 )
      {
        if ( r_u32((uint32)(0x1F800030u)) < 32 )
          w_u32((uint32)(0x1F800030u), 32);
        v14 = 16 * a2 - 2146695836;
        gte_t4 = 0;
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
draft_gte_control(1u, gte_t4);
draft_gte_control(3u, gte_t4);
        gte_t4 = 4096;
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
draft_gte_control(0u, gte_t4);
draft_gte_control(2u, gte_t4);
draft_gte_control(4u, gte_t4);
        gte_t4 = r_u32((uint32)(0x1F800028u));
        gte_t5 = r_u32((uint32)(0x1F80002Cu));
        gte_t6 = r_u32((uint32)(0x1F800030u));
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
draft_gte_control(5u, gte_t4);
draft_gte_control(6u, gte_t5);
draft_gte_control(7u, gte_t6);
        gte_t1 = 528482336;
        w_u16((uint32)(0x1F800020u), -(sint16)r_u16((uint32)((v14 + 12))) << a3);
        v21 = (sint16)r_u16((uint32)((v14 + 14)));
        v22 = r_u32((uint32)(0x80071680u));
        w_u32((uint32)(0x80071680u), r_u32((uint32)(0x80071680u)) + (40));
        w_u16((uint32)(0x1F800024u), 0);
        w_u16((uint32)(0x1F800022u), -v21 << a4);
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
draft_gte_data(0u, r_u32(gte_t1 + 0u));
draft_gte_data(1u, r_u32(gte_t1 + 4u));
draft_gte_command(0x180001u);
        w_u8((uint32)((v22 + 3)), 9);
        v23 = 44;
        w_u8((uint32)((v22 + 7)), 44);
        if ( a9 )
          v23 = 46;
        w_u8((uint32)((v22 + 7)), v23);
        w_u8((uint32)((v22 + 4)), a10);
        w_u8((uint32)((v22 + 5)), a10);
        w_u8((uint32)((v22 + 6)), a10);
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
w_u32(v22 + 8u, draft_gte_read(14u));
        gte_t1 = 528482336;
        w_u16((uint32)(0x1F800020u), r_u16((uint32)(0x1F800020u)) + ((sint16)r_u16((uint32)((v14 + 8))) << a3));
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
draft_gte_data(0u, r_u32(gte_t1 + 0u));
draft_gte_data(1u, r_u32(gte_t1 + 4u));
draft_gte_command(0x180001u);
        v25 = r_u16((uint32)(v14));
        w_u16((uint32)((v22 + 22)), r_u16((uint32)(v14)));
        if ( a9 )
          w_u16((uint32)((v22 + 22)), v25 | r_u16((uint32)(0x8007177Eu + 2u * (a9))));
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
w_u32(v22 + 16u, draft_gte_read(14u));
        gte_t1 = 528482336;
        w_u16((uint32)(0x1F800022u), r_u16((uint32)(0x1F800022u)) + ((sint16)r_u16((uint32)((v14 + 10))) << a4));
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
draft_gte_data(0u, r_u32(gte_t1 + 0u));
draft_gte_data(1u, r_u32(gte_t1 + 4u));
draft_gte_command(0x180001u);
        w_u16((uint32)((v22 + 14)), r_u16((uint32)((v14 + 2))));
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
w_u32(v22 + 32u, draft_gte_read(14u));
        w_u16((uint32)(0x1F800020u), r_u16((uint32)(0x1F800020u)) - ((sint16)r_u16((uint32)((v14 + 8))) << a3));
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
draft_gte_data(0u, r_u32(gte_t1 + 0u));
draft_gte_data(1u, r_u32(gte_t1 + 4u));
draft_gte_command(0x180001u);
        w_u8((uint32)((v22 + 12)), r_u8((uint32)((v14 + 4))));
        w_u8((uint32)((v22 + 13)), r_u8((uint32)((v14 + 6))));
        w_u8((uint32)((v22 + 20)), r_u8((uint32)((v14 + 4))) + r_u8((uint32)((v14 + 8))) - 1);
        w_u8((uint32)((v22 + 21)), r_u8((uint32)((v14 + 6))));
        w_u8((uint32)((v22 + 28)), r_u8((uint32)((v14 + 4))));
        w_u8((uint32)((v22 + 29)), r_u8((uint32)((v14 + 6))) + r_u8((uint32)((v14 + 10))) - 1);
        w_u8((uint32)((v22 + 36)), r_u8((uint32)((v14 + 4))) + r_u8((uint32)((v14 + 8))) - 1);
        w_u8((uint32)((v22 + 37)), r_u8((uint32)((v14 + 6))) + r_u8((uint32)((v14 + 10))) - 1);
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
w_u32(v22 + 24u, draft_gte_read(14u));
        if ( (uint32)(((sint32)r_u32((uint32)(0x1F800030u)) >> 4) - 1) < 0x9C3 )
        {
          v27 = (uint32)(4 * ((sint32)r_u32((uint32)(0x1F800030u)) >> 4) + r_u32((uint32)(0x8007184Cu)));
          w_u32((uint32)(v22), r_u32((uint32)(v22)) & 0xFF000000 | r_u32((uint32)(v27)) & 0xFFFFFF);
          w_u32((uint32)(v27), r_u32((uint32)(v27)) & 0xFF000000 | v22 & 0xFFFFFF);
        }
        return 1;
      }
    }
  }
  return result;
}

uint32 sub_80058100(uint32 a1)
{
    FUNCTION_MARKER(0x80058100u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

  uint32 v2; 
  sint32 v3; 
  sint32 v4; 
  uint32 v5; 
  sint32 v6; 
  sint32 result; 
  uint32 v8; 
  uint32 v9; 
  uint16 v10; 
  uint16 v11; 
  sint32 v12; 
  uint16 v13; 
  uint32 v14; 
  sint32 v15; 
  sint32 v16; 
  sint32 v17; 
  sint32 v18; 
  uint32 v19; 
  uint16 v20; 
  uint16 v21; 





  v2 = (uint32)(40 * r_u16((uint32)(a1)) - 2146697976);
  v3 = r_u16((uint32)(a1 + 2u * (1)));
  v4 = r_u32((uint32)(v2 + 4u * (8)));
  v5 = (uint32)(r_u32((uint32)(v2 + 4u * (6))) + v3);
  v6 = (uint8)r_u8((uint32)(v5));
  result = 12 * r_u16((uint32)((2 * v3 + r_u32(v2 + 28u))));
  v8 = (uint32)(v4 + result);
  if ( r_u8((uint32)(v5)) )
  {
    /* Event payload follows the frame halfword and type/parameter bytes */
    v9 = v8 + 4u;
    do
    {
      if ( r_u16((uint32)(v8)) == r_u16((uint32)(a1 + 2u * (8))) )
      {
        switch ( r_u8((uint32)(v9 - 1u * (2))) )
        {
          case 0u:
            w_u8((uint32)((a1 + 1u * (30))), r_u8((uint32)(v9 - 1u * (1))));
            w_u8((uint32)((a1 + 1u * (31))), r_u8((uint32)(v9)));
            w_u8((uint32)((a1 + 1u * (32))), r_u8((uint32)(v9 + 1u * (1))));
            w_u8((uint32)((a1 + 1u * (33))), r_u8((uint32)(v9 + 1u * (2))));
            v10 = r_u8((uint32)(v9 + 1u * (3)));
            w_u16((uint32)(a1 + 2u * (17)), v10);
            if ( (r_u8((uint32)(v9 + 1u * (4))) & 1) != 0 )
              w_u16((uint32)(a1 + 2u * (17)), v10 | 0x8000);
            w_u16((uint32)(a1 + 2u * (18)), r_u8((uint32)(v9 + 1u * (5))) & 3);
            v11 = r_u8((uint32)(v9 + 1u * (6)));
            w_u16((uint32)(a1 + 2u * (29)), 1);
            w_u16((uint32)(a1 + 2u * (19)), v11);
            goto LABEL_24;
          case 1u:
            w_u16((uint32)(a1 + 2u * (17)), 0);
            goto LABEL_24;
          case 2u:
            w_u16((uint32)(a1 + 2u * (20)), r_u8((uint32)(v9 - 1u * (1))));
            goto LABEL_24;
          case 3u:
            if ( r_u8((uint32)(v9 + 1u * (1))) < 9u )
            {
              v12 = r_u16((uint32)(a1 + 2u * (11)));
              if ( v12 != 0xFFFF )
              {
                sub_80031308(v12);
                w_u16((uint32)(a1 + 2u * (11)), -1);
              }
              w_u16((uint32)(a1 + 2u * (11)), sub_80031224(r_u8((uint32)(v9 - 1u * (1))), r_u8((uint32)(v9))));
              w_u16((uint32)(a1 + 2u * (12)), r_u8((uint32)(v9 + 1u * (1))));
              w_u16((uint32)(a1 + 2u * (13)), r_u8((uint32)(v9 + 1u * (2))));
            }
            goto LABEL_24;
          case 4u:
            v9 += 1u * (12);
            sub_80031308(r_u16((uint32)(a1 + 2u * (11))));
            w_u16((uint32)(a1 + 2u * (11)), -1);
            break;
          case 5u:
            w_u8((uint32)((a1 + 1u * (21))), 1);
            goto LABEL_24;
          case 6u:
            w_u16((uint32)(a1 + 2u * (14)), r_u16((uint32)(a1 + 2u * (8))));
            goto LABEL_24;
          case 7u:
            w_u16((uint32)(a1 + 2u * (21)), 1);
            w_u16((uint32)(a1 + 2u * (22)), r_u8((uint32)(v9 - 1u * (1))));
            w_u16((uint32)(a1 + 2u * (23)), r_u8((uint32)(v9)));
            w_u16((uint32)(a1 + 2u * (24)), r_u8((uint32)(v9 + 1u * (1))));
            w_u16((uint32)(a1 + 2u * (24)), r_u16((uint32)(a1 + 2u * (24))) * (16));
            w_u16((uint32)(a1 + 2u * (25)), r_u8((uint32)(v9 + 1u * (2))) - 1);
            v13 = r_u8((uint32)(v9 + 1u * (3)));
            w_u16((uint32)(a1 + 2u * (26)), v13);
            if ( (r_u8((uint32)(v9 + 1u * (4))) & 1) != 0 )
              w_u16((uint32)(a1 + 2u * (26)), v13 | 0x8000);
            w_u16((uint32)(a1 + 2u * (27)), r_u8((uint32)(v9 + 1u * (5))) & 3);
            goto LABEL_24;
          case 8u:
            v14 = r_u8((uint32)(v9 - 1u * (1)));
            if ( v14 >= 0x10 )
              goto LABEL_24;
            v15 = r_u16((uint32)((2 * v14 + 32 * r_u16(a1) - 2146768276)));
            if ( v15 == 0xFFFF )
              goto LABEL_24;
            v16 = 16 * r_u8((uint32)(v9 + 1u * (1)));
            v17 = 16 * r_u8((uint32)(v9 + 1u * (2))) - v16;
            v18 = r_u8((uint32)(v9)) << 8;
            v19 = v16 + ((v17 * (uint32)(uint8)sub_80011B8C()) >> 8);
            v17 = (uint16)(sub_800448F4());
            v20 = sub_80044F58(v18);
            sub_8004486C(1, v17, v15, (uint16)v19, v20, r_u16((uint32)(0x80071A20u)));
            v9 += 1u * (12);
            break;
          case 9u:
            v21 = r_u8((uint32)(v9 - 1u * (1)));
            w_u16((uint32)(a1 + 2u * (28)), v21);
            w_u16((uint32)(a1 + 2u * (28)), v21 | (16 * r_u8((uint32)(v9))));
            goto LABEL_24;
          default:
            goto LABEL_24;
        }
      }
      else
      {
LABEL_24:
        v9 += 1u * (12);
      }
      v6 += 0xFFFF;
      result = (uint16)v6;
      v8 += 2u * (6);
    }
    while ( (uint16)v6 );
  }
  return result;
}

uint32 sub_80021288(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a5)
{
    FUNCTION_MARKER(0x80021288u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

  sint32 result; 

  if ( !r_u32((uint32)(0x80071A08u)) )
  {
    w_u32((uint32)(0x800BF7E0u), 0);
    w_u32((uint32)(0x800BF7E4u), 0);
    w_u32((uint32)(0x800BF7E8u), 0);
    w_u32((uint32)(0x800AF01Cu), 0);
    w_u32((uint32)(0x80071550u), 1000000);
    w_u32((uint32)(0x80071A40u), 1000000);
    w_u32((uint32)(0x800716B0u), -1000000);
    w_u32((uint32)(0x80071554u), -1000000);
    w_u16((uint32)(0x800715A8u), 0);
    w_u32((uint32)(0x80071738u), 0);
  }
  w_u32((uint32)(0x800BF7E0u), r_u32((uint32)(0x800BF7E0u)) + (a1));
  w_u32((uint32)(0x800BF7E4u), r_u32((uint32)(0x800BF7E4u)) + (a3));
  w_u32((uint32)(0x800BF7E8u), r_u32((uint32)(0x800BF7E8u)) + (a2));
  w_u32((uint32)(0x800AF01Cu), r_u32((uint32)(0x800AF01Cu)) + (a4));
  (w_u32((uint32)(0x80071A08u), r_u32((uint32)(0x80071A08u)) + 1u), r_u32((uint32)(0x80071A08u)));
  (w_u32((uint32)(0x80071738u), r_u32((uint32)(0x80071738u)) + 1u), r_u32((uint32)(0x80071738u)));
  w_u32((uint32)(0x1F800028u), a1 - r_u32((uint32)(0x800BBFC4u)));
  w_u32((uint32)(0x1F800030u), a2 - r_u32((uint32)(0x800BBFCCu)));
  w_u32((uint32)(0x1F80002Cu), a3 - r_u32((uint32)(0x800BBFC8u)));
  sub_8005CC48(-2146763136, 528482344, 528482344);
  if ( (a5 & 2) == 0 )
    (w_u16((uint32)(0x800715A8u), r_u16((uint32)(0x800715A8u)) + 1u), r_u16((uint32)(0x800715A8u)));
  if ( (sint32)r_u32((uint32)(0x1F800028u)) < (sint32)r_u32((uint32)(0x80071A40u)) )
  {
    w_u32((uint32)(0x800AF674u), r_u32((uint32)(0x1F800028u)));
    w_u32((uint32)(0x800AF678u), r_u32((uint32)(0x1F80002Cu)));
    w_u32((uint32)(0x800AF67Cu), r_u32((uint32)(0x1F800030u)));
    w_u32((uint32)(0x800AF680u), r_u32((uint32)(0x1F800034u)));
    w_u32((uint32)(0x80071A40u), r_u32((uint32)(0x1F800028u)));
    if ( (a5 & 2) == 0 )
    {
      w_u32((uint32)(0x800C9E40u), a1);
      w_u32((uint32)(0x800C9E44u), a3);
      w_u32((uint32)(0x800C9E48u), a2);
    }
  }
  if ( (sint32)r_u32((uint32)(0x80071554u)) < (sint32)r_u32((uint32)(0x1F800028u)) )
  {
    w_u32((uint32)(0x800AF6E0u), r_u32((uint32)(0x1F800028u)));
    w_u32((uint32)(0x800AF6E4u), r_u32((uint32)(0x1F80002Cu)));
    w_u32((uint32)(0x800AF6E8u), r_u32((uint32)(0x1F800030u)));
    w_u32((uint32)(0x800AF6ECu), r_u32((uint32)(0x1F800034u)));
    w_u32((uint32)(0x80071554u), r_u32((uint32)(0x1F800028u)));
    if ( (a5 & 2) == 0 )
    {
      w_u32((uint32)(0x800AEEA0u), a1);
      w_u32((uint32)(0x800AEEA4u), a3);
      w_u32((uint32)(0x800AEEA8u), a2);
    }
  }
  if ( (sint32)r_u32((uint32)(0x1F800030u)) < (sint32)r_u32((uint32)(0x80071550u)) )
  {
    w_u32((uint32)(0x800AF6B0u), r_u32((uint32)(0x1F800028u)));
    w_u32((uint32)(0x800AF6B4u), r_u32((uint32)(0x1F80002Cu)));
    w_u32((uint32)(0x800AF6B8u), r_u32((uint32)(0x1F800030u)));
    w_u32((uint32)(0x800AF6BCu), r_u32((uint32)(0x1F800034u)));
    w_u32((uint32)(0x80071550u), r_u32((uint32)(0x1F800030u)));
  }
  result = (sint32)r_u32((uint32)(0x800716B0u)) < (sint32)r_u32((uint32)(0x1F800030u));
  if ( (sint32)r_u32((uint32)(0x800716B0u)) < (sint32)r_u32((uint32)(0x1F800030u)) )
  {
    result = r_u32((uint32)(0x1F800030u));
    w_u32((uint32)(0x800BD1D8u), r_u32((uint32)(0x1F800028u)));
    w_u32((uint32)(0x800BD1DCu), r_u32((uint32)(0x1F80002Cu)));
    w_u32((uint32)(0x800BD1E0u), r_u32((uint32)(0x1F800030u)));
    w_u32((uint32)(0x800BD1E4u), r_u32((uint32)(0x1F800034u)));
    w_u32((uint32)(0x800716B0u), r_u32((uint32)(0x1F800030u)));
  }
  return result;
}

uint32 sub_80015364(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a9, uint32 a10)
{
    FUNCTION_MARKER(0x80015364u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

  sint32 v13; 
  sint32 v14; 
  sint32 v15; 
  uint32 v16; 
  sint8 v17; 
  sint32 v18; 
  sint32 result; 
  sint32 v20; 
  sint8 v21; 
  sint16 v22; 
  sint16 v23; 
  uint32 v24; 
  sint16 v25[4]; 
  sint32 transformed[3];
  sint32 v26; 
  sint32 v27; 

  v13 = r_u32((uint32)(0x80071680u));
  v14 = 16 * a4 - 2146695836;
  v15 = r_u16((uint32)((v14 + 8)));
  v16 = r_u16((uint32)((v14 + 10)));
  w_u16((uint32)(0x1F800020u), 0);
  w_u16((uint32)(0x1F800024u), 0);
  v25[1] = 0;
  v25[2] = 0;
  w_u32((uint32)(0x80071680u), r_u32((uint32)(0x80071680u)) + (80));
  v17 = v15 - 1;
  v18 = v16 - 1;
  w_u16((uint32)(0x1F800022u), a9);
  v25[0] = (sint16)((sint32)((uint32)(v15 - 1) << 16) >> 12);
  sub_8005D138(528482336, 528482304);
  sub_8005CDD8(528482304, draft_local_address(v25, sizeof(v25)), draft_local_address(transformed, sizeof(transformed)));
  v26 = transformed[0]; v27 = transformed[2];
  v26 /= 32;
  v27 /= 32;
  result = (sint32)((uint32)(sint32)(sint16)a10 * (uint32)v26);
  v20 = a2 - v18;
  if ( result >= 0 )
  {
    w_u16((uint32)((v13 + 8)), a1 - v26);
    w_u16((uint32)((v13 + 10)), v20 + (v27 >> 3));
    w_u16((uint32)((v13 + 20)), a1 + v26);
    w_u16((uint32)((v13 + 22)), v20 - (v27 >> 3));
    w_u16((uint32)((v13 + 32)), a1 - v26);
    w_u16((uint32)((v13 + 34)), a2 - (v27 >> 3));
    w_u16((uint32)((v13 + 44)), a1 + v26);
    w_u16((uint32)((v13 + 46)), a2 + (v27 >> 3));
    w_u8((uint32)((v13 + 12)), r_u8((uint32)((v14 + 4))));
    w_u8((uint32)((v13 + 13)), r_u8((uint32)((v14 + 6))));
    w_u8((uint32)((v13 + 24)), r_u8((uint32)((v14 + 4))) + v17);
    w_u8((uint32)((v13 + 25)), r_u8((uint32)((v14 + 6))));
    w_u8((uint32)((v13 + 36)), r_u8((uint32)((v14 + 4))));
    w_u8((uint32)((v13 + 37)), r_u8((uint32)((v14 + 6))) + v18);
    w_u8((uint32)((v13 + 48)), r_u8((uint32)((v14 + 4))) + v17);
    w_u8((uint32)((v13 + 49)), r_u8((uint32)((v14 + 6))) + v18);
    v21 = 0x80 - 4 * v27;
    if ( ((128 - 4 * (uint16)v27) & 0x8000) != 0 )
      v21 = 0;
    w_u8((uint32)((v13 + 4)), v21);
    w_u8((uint32)((v13 + 5)), v21);
    w_u8((uint32)((v13 + 6)), v21);
    w_u8((uint32)((v13 + 28)), v21);
    w_u8((uint32)((v13 + 29)), v21);
    w_u8((uint32)((v13 + 30)), v21);
    v22 = 4 * v27 + 128;
    if ( v22 >= 256 )
      v22 = (uint8)(-1);
    w_u8((uint32)((v13 + 3)), 12);
    w_u8((uint32)((v13 + 16)), v22);
    w_u8((uint32)((v13 + 17)), v22);
    w_u8((uint32)((v13 + 18)), v22);
    w_u8((uint32)((v13 + 40)), v22);
    w_u8((uint32)((v13 + 41)), v22);
    w_u8((uint32)((v13 + 42)), v22);
    w_u8((uint32)((v13 + 7)), 60);
    w_u16((uint32)((v13 + 26)), r_u16((uint32)(v14)));
    v23 = r_u16((uint32)((v14 + 2)));
    w_u8((uint32)((v13 + 7)), r_u8((uint32)((v13 + 7))) & (0xFCu));
    w_u16((uint32)((v13 + 14)), v23);
    if ( (sint32)a3 >= 2500 )
      a3 = 2499;
    v24 = (uint32)(4 * a3 + r_u32((uint32)(0x8007184Cu)));
    w_u32((uint32)(v13), r_u32((uint32)(v13)) & 0xFF000000 | r_u32((uint32)(v24)) & 0xFFFFFF);
    result = r_u32((uint32)(v24)) & 0xFF000000 | v13 & 0xFFFFFF;
    w_u32((uint32)(v24), result);
  }
  return result;
}

uint32 sub_80032A20(uint32 a1)
{
    FUNCTION_MARKER(0x80032A20u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */
    uint32 gte_t4, gte_t5, gte_t6, gte_v0, gte_v1;

  sint32 v1; 
  uint32 v2; 
  sint32 v3; 
  sint32 v4; 
  uint8 v5; 
  sint32 result; 
  uint32 v7; 
  sint32 v8; 
  sint32 v17; 
  sint8 v18; 
  sint16 v21; 
  sint16 v22; 
  uint32 v23; 
  sint32 v24; 
  uint32 v25; 
  sint32 v26; 
  sint8 v28; 
  sint8 v29; 
  sint8 v30; 
  sint32 v31; 

  v1 = 0;
  v2 = a1 + 2;
  while ( 1 )
  {
    v3 = r_u32((uint32)(a1)) - r_u32((uint32)(0x800BBFC4u));
    v4 = v3;
    if ( v3 < 0 )
      v4 = r_u32((uint32)(0x800BBFC4u)) - r_u32((uint32)(a1));
    v5 = v4 >= 16001;
    result = (uint16)v1;
    if ( v5 )
      break;
    v7 = draft_local_address(&v26, sizeof(v26)) + 2 * (uint16)v1;
    w_u16((uint32)(v7), v3);
    w_u16((uint32)((v7 + 2u * (1))), r_u16((uint32)((v2 - 2u * (2)))) - r_u32((uint32)(0x800BBFC8u)));
    v8 = r_u32((uint32)(v2)) - r_u32((uint32)(0x800BBFCCu));
    result = v8 < 128;
    if ( v8 < 128 )
      break;
    result = r_u32((uint32)(v2)) - r_u32((uint32)(0x800BBFCCu)) < 16001;
    v2 += 4u * (4);
    if ( !result )
      break;
    w_u16((uint32)((v7 + 2u * (2))), v8);
    ++v1;
    a1 += 4u * (4);
    if ( (uint16)v1 >= 4u )
    {
      gte_t4 = r_u32((uint32)(0x800BBFDCu));
      gte_t5 = r_u32((uint32)(0x800BBFE0u));
      /* TODO: GTE adapters and reconstructed operand addresses await integration */
draft_gte_control(0u, gte_t4);
draft_gte_control(1u, gte_t5);
      gte_t4 = r_u32((uint32)(0x800BBFE4u));
      gte_t5 = r_u32((uint32)(0x800BBFE8u));
      gte_t6 = r_u32((uint32)(0x800BBFECu));
      /* TODO: GTE adapters and reconstructed operand addresses await integration */
draft_gte_control(2u, gte_t4);
draft_gte_control(3u, gte_t5);
draft_gte_control(4u, gte_t6);
      gte_t4 = 0;
      /* TODO: GTE adapters and reconstructed operand addresses await integration */
draft_gte_control(5u, gte_t4);
draft_gte_control(6u, gte_t4);
draft_gte_control(7u, gte_t4);
      gte_v1 = draft_local_address(&v28, sizeof(v28));
      gte_v0 = draft_local_address(&v30, sizeof(v30));
      /* TODO: GTE adapters and reconstructed operand addresses await integration */
/* TODO: Recover GTE local operand lwc2    $0, 0x28+var_28($sp) */
/* TODO: Recover GTE local operand lwc2    $1, 0x28+var_24($sp) */
draft_gte_data(2u, r_u32(gte_v1 + 0u));
draft_gte_data(3u, r_u32(gte_v1 + 4u));
draft_gte_data(4u, r_u32(gte_v0 + 0u));
draft_gte_data(5u, r_u32(gte_v0 + 4u));
draft_gte_command(0x280030u);
      v17 = r_u32((uint32)(0x80071680u));
      w_u8((uint32)((r_u32((uint32)(0x80071680u)) + 3)), 9);
      w_u8((uint32)((v17 + 7)), 44);
      w_u8((uint32)((v17 + 12)), r_u32((uint32)(0x800C0F08u)));
      w_u8((uint32)((v17 + 13)), r_u8((uint32)(0x800C0F0Au)));
      w_u8((uint32)((v17 + 20)), r_u32((uint32)(0x800C0F08u)) + r_u8((uint32)(0x800C0F0Cu)) - 1);
      w_u8((uint32)((v17 + 21)), r_u8((uint32)(0x800C0F0Au)));
      w_u8((uint32)((v17 + 28)), r_u32((uint32)(0x800C0F08u)));
      w_u8((uint32)((v17 + 29)), r_u8((uint32)(0x800C0F0Au)) + r_u8((uint32)(0x800C0F0Eu)) - 1);
      v18 = r_u8((uint32)((v17 + 7))) | 2;
      w_u8((uint32)((v17 + 36)), r_u32((uint32)(0x800C0F08u)) + r_u8((uint32)(0x800C0F0Cu)) - 1);
      gte_v0 = (uint8)(r_u8((uint32)(0x800C0F0Eu)));
      gte_v1 = (uint8)(r_u8((uint32)(0x800C0F0Au)));
      w_u8((uint32)((v17 + 7)), v18 & 0xFE);
      w_u8((uint32)((v17 + 37)), (uint8)gte_v1 + (uint8)gte_v0 - 1);
      /* TODO: GTE adapters and reconstructed operand addresses await integration */
draft_gte_command(0x158002Du);
gte_t4 = draft_gte_read(7u);
      v31 = gte_t4 >> 2;
      result = (uint32)((gte_t4 >> 2) - 16) < 0x9B4;
      if ( (uint32)((gte_t4 >> 2) - 16) < 0x9B4 )
      {
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
w_u32(v17 + 8u, draft_gte_read(12u));
w_u32(v17 + 0x10u, draft_gte_read(13u));
w_u32(v17 + 0x18u, draft_gte_read(14u));
        gte_v0 = draft_local_address(&v29, sizeof(v29));
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
draft_gte_data(0u, r_u32(gte_v0 + 0u));
draft_gte_data(1u, r_u32(gte_v0 + 4u));
draft_gte_command(0x180001u);
        w_u16((uint32)((v17 + 14)), r_u16((uint32)(0x800C0F06u)));
        v21 = r_u16((uint32)(0x800C0F04u));
        v22 = r_u16((uint32)(0x80071784u));
        w_u8((uint32)((v17 + 4)), 64);
        w_u8((uint32)((v17 + 5)), 64);
        w_u8((uint32)((v17 + 6)), 64);
        w_u16((uint32)((v17 + 22)), v21 | v22);
        /* TODO: GTE adapters and reconstructed operand addresses await integration */
w_u32(gte_v0 + 0u, draft_gte_read(14u));
        v23 = (uint32)(4 * v31 + r_u32((uint32)(0x8007184Cu)));
        v24 = r_u32((uint32)(0x80071680u));
        w_u32((uint32)(v17), r_u32((uint32)(v17)) & 0xFF000000 | r_u32((uint32)(v23)) & 0xFFFFFF);
        result = v24 + 40;
        v25 = r_u32((uint32)(v23)) & 0xFF000000 | v17 & 0xFFFFFF;
        w_u32((uint32)(0x80071680u), result);
        w_u32((uint32)(v23), v25);
      }
      return result;
    }
  }
  return result;
}

uint32 sub_800184C0(uint32 a, uint32 b, uint32 c, uint32 d)
{
  uint32 a1 = a, a2 = b, a3 = c, a4 = d;
    FUNCTION_MARKER(0x800184C0u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

  sint32 v6; 
  sint32 v7; 
  sint32 v8; 
  uint32 v9; 
  sint32 v10; 
  sint32 v11; 
  uint32 v12; 
  sint32 v13; 
  sint32 v14; 
  uint32 v15; 
  uint32 v16; 
  sint32 v17; 
  sint32 v18; 
  uint32 v19; 
  sint32 v20; 
  uint32 v21; 
  uint32 result; 

  v6 = 2 * a4;
  v7 = 4 * a3;
  v8 = r_u32((uint32)(0x80071680u));
  w_u32((uint32)(0x80071680u), r_u32((uint32)(0x80071680u)) + (40));
  w_u8((uint32)((v8 + 3)), 4);
  w_u8((uint32)((v8 + 7)), 101);
  v9 = (uint32)(2 * a4 - 2146695920);
  w_u16((uint32)((v8 + 8)), a1);
  w_u16((uint32)((v8 + 10)), a2);
  w_u8((uint32)((v8 + 12)), 0);
  w_u8((uint32)((v8 + 13)), 0);
  w_u16((uint32)((v8 + 16)), 256);
  w_u16((uint32)((v8 + 18)), 256);
  v10 = r_u32((uint32)(0x80071680u));
  v11 = r_u32((uint32)(v8));
  v12 = (uint32)(4 * a3 + r_u32((uint32)(0x8007184Cu)));
  w_u16((uint32)((v8 + 14)), r_u16((uint32)((2 * r_u8((uint32)((40 * r_u16(v9) - 2146764952))) - 2146696668))));
  w_u32((uint32)(v8), v11 & 0xFF000000 | r_u32((uint32)(v12)) & 0xFFFFFF);
  w_u32((uint32)(v12), r_u32((uint32)(v12)) & 0xFF000000 | v8 & 0xFFFFFF);
  v13 = r_u16((uint32)((2 * r_u16(v9) - 2146767244)));
  w_u32((uint32)(0x80071680u), v10 + 40);
  sub_8005EEB8(v10, 1, 1, v13, 0u);
  v14 = r_u32((uint32)(0x80071680u));
  v15 = (uint32)(v7 + r_u32((uint32)(0x8007184Cu)));
  w_u32((uint32)(v10), r_u32((uint32)(v10)) & 0xFF000000 | r_u32((uint32)((v7 + r_u32((uint32)(0x8007184Cu))))) & 0xFFFFFF);
  v16 = r_u32((uint32)(v15));
  w_u32((uint32)(0x80071680u), v14 + 40);
  w_u32((uint32)(v15), v16 & 0xFF000000 | v10 & 0xFFFFFF);
  w_u8((uint32)((v14 + 3)), 4);
  w_u8((uint32)((v14 + 7)), 101);
  w_u16((uint32)((v14 + 8)), a1 + 256);
  w_u16((uint32)((v14 + 10)), a2);
  w_u8((uint32)((v14 + 12)), 0);
  w_u8((uint32)((v14 + 13)), 0);
  w_u16((uint32)((v14 + 16)), 64);
  w_u16((uint32)((v14 + 18)), 256);
  v17 = r_u32((uint32)(0x80071680u));
  v18 = r_u32((uint32)(v14));
  v19 = (uint32)(v7 + r_u32((uint32)(0x8007184Cu)));
  w_u16((uint32)((v14 + 14)), r_u16((uint32)((2 * r_u8((uint32)((40 * r_u16(v9) - 2146764952))) - 2146696668))));
  w_u32((uint32)(v14), v18 & 0xFF000000 | r_u32((uint32)(v19)) & 0xFFFFFF);
  w_u32((uint32)(v19), r_u32((uint32)(v19)) & 0xFF000000 | v14 & 0xFFFFFF);
  v20 = r_u16((uint32)((2 * r_u16((uint32)((v6 - 2146695920 + 32))) - 2146767244)));
  w_u32((uint32)(0x80071680u), v17 + 40);
  sub_8005EEB8(v17, 1, 1, v20, 0u);
  v21 = (uint32)(v7 + r_u32((uint32)(0x8007184Cu)));
  w_u32((uint32)(v17), r_u32((uint32)(v17)) & 0xFF000000 | r_u32((uint32)(v21)) & 0xFFFFFF);
  result = r_u32((uint32)(v21)) & 0xFF000000 | v17 & 0xFFFFFF;
  w_u32((uint32)(v21), result);
  return result;
}

uint32 sub_80048EB8(void)
{
    FUNCTION_MARKER(0x80048EB8u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */
    uint32 gte_t4, gte_t5, gte_t6;

  sint32 v0; 
  sint32 v1; 
  sint32 v2; 
  sint16 v3; 
  sint16 v4; 
  sint16 v5; 
  sint8 v6; 
  sint16 v7; 
  sint32 v8; 
  sint16 v9; 
  uint16 v10; 
  sint16 v11; 
  sint32 v12; 
  sint16 v13; 
  uint16 v14; 
  sint16 v15; 
  sint32 v16; 
  sint16 v17; 
  uint16 v18; 
  sint16 v19; 
  sint32 v20; 
  sint32 v21; 
  sint32 v22; 
  sint32 v23; 
  sint32 result; 

  v0 = 0;
  v1 = 0;
  do
  {
    v2 = 8 * (uint16)v1++;
    v3 = sub_8001F8E0(r_u16((uint32)((v2 - 2146673330))), r_u16((uint32)((v2 - 2146701382))), r_u16((uint32)(0x800717F0u)));
    v4 = r_u16((uint32)((v2 - 2146673332)));
    v5 = r_u16((uint32)((v2 - 2146701384)));
    v6 = (sint8)r_u16((uint32)(0x800717F0u));
    w_u16((uint32)((v2 - 2146673330)), v3 & 0xFFF);
    v7 = sub_8001F8E0(v4, v5, v6);
    v8 = (sint16)r_u16((uint32)((v2 - 2146673412)));
    v9 = r_u16((uint32)((v2 - 2146701712)));
    v10 = r_u16((uint32)(0x800719C4u));
    w_u16((uint32)((v2 - 2146673332)), v7 & 0xFFF);
    v11 = sub_8001F950(v8, v9, v10);
    v12 = (sint16)r_u16((uint32)((v2 - 2146673410)));
    v13 = r_u16((uint32)((v2 - 2146701710)));
    v14 = r_u16((uint32)(0x800719C4u));
    w_u16((uint32)((v2 - 2146673412)), v11);
    v15 = sub_8001F950(v12, v13, v14);
    v16 = (sint16)r_u16((uint32)((v2 - 2146673408)));
    v17 = r_u16((uint32)((v2 - 2146701708)));
    v18 = r_u16((uint32)(0x800719C4u));
    w_u16((uint32)((v2 - 2146673410)), v15);
    v19 = sub_8001F950(v16, v17, v18);
    w_u16((uint32)((v2 - 2146673408)), v19);
    v20 = r_u32((uint32)((v2 - 2146673412)));
    v21 = r_u32((uint32)((v2 - 2146673408)));
    w_u32((uint32)((v2 - 2146699040)), v20);
    w_u32((uint32)((v2 - 2146699040)), v20);
    w_u32((uint32)((v2 - 2146699036)), v21);
    w_u32((uint32)((v2 - 2146699036)), v21);
    v0 += (sint16)r_u16((uint32)((v2 - 2146673412))) + (sint16)r_u16((uint32)((v2 - 2146673410))) + v19;
  }
  while ( (uint16)v1 < 3u );
  if ( r_u32((uint32)(0x800C0550u)) != 0xFFFF )
    sub_80048BA8((uint32)0x800C0550);
  w_u32((uint32)(0x800718F4u), sub_8001F950(r_u32((uint32)(0x800718F4u)), r_u32((uint32)(0x800717D8u)), r_u16((uint32)(0x800719C4u))));
  sub_8001F338();
  w_u32((uint32)(0x800719B0u), 128);
  w_u32((uint32)(0x80071988u), 128);
  w_u32((uint32)(0x80071980u), 128);
  v22 = v0 / 9 / 3;
  v23 = (uint64_t)(1431655766LL * v22) >> 32;
  if ( v22 < 24 )
  {
    v22 = 24;
    v23 = 8;
  }
  result = v23 - (v22 >> 31);
  gte_t4 = 16 * v22;
  gte_t5 = 16 * (v22 / 2);
  gte_t6 = 16 * result;
  /* TODO: GTE adapters and reconstructed operand addresses await integration */
draft_gte_control(13u, gte_t4);
draft_gte_control(14u, gte_t5);
draft_gte_control(15u, gte_t6);
  return result;
}

uint32 sub_80059C50(uint32 a1)
{
    extern sint32 legend_skip_movies(void);
    /* User-selected native playback policy skips before decoder allocation */
    if (legend_skip_movies()) return 1u;
    FUNCTION_MARKER(0x80059C50u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

  sint16 v2; 
  sint32 v3; 
  uint8 v4; 
  sint32 result; 
  sint32 v6; 
  sint16 v7; 
  sint16 v8; 
  uint16 v9; 
  sint32 v10; 
  sint32 v11; 
  sint16 v12; 
  sint8 v13[24]; 

  v2 = 0;
  v3 = 0;
  v4 = sub_80065768(draft_local_address(v13, sizeof(v13)), r_u32((uint32)(a1))) == 0;
  result = 3;
  if ( !v4 )
  {
    sub_8005A044(a1);
    if ( sub_8005A47C(draft_local_address(v13, sizeof(v13))) << 16 )
    {
      while ( 1 )
      {
        v6 = sub_8005A530();
        v7 = v2 + 1;
        if ( v6 )
          break;
        ++v2;
        if ( v7 == 5 )
          goto LABEL_5;
      }
      sub_800451B8(256, 0, 0, 16);
      sub_8005A614(v6);
      v8 = 0;
      if ( !r_u32((uint32)(0x80071A88u)) )
      {
        do
        {
          v9 = sub_8005A7D8();
          sub_80067A6C(r_u32((uint32)(((r_u32((uint32)(0x80071A8Eu)) << 16 >> 14) - 2147018098 + 6))), v9);
          v10 = sub_8005A730();
          sub_80067AE8(r_u32((uint32)(((r_u32((uint32)(0x80071A90u)) << 16 >> 14) - 2147018084))), v10);
          v11 = sub_8005A530();
          v12 = v8 + 1;
          if ( v11 )
          {
            v8 = 0;
          }
          else
          {
            ++v8;
            if ( v12 == 5 )
              v3 = 3;
          }
          sub_8005A614(v11);
          sub_80011BB8();
          sub_80045048(0);
          if ( !r_u32((uint32)(0x800718C8u)) )
            goto LABEL_16;
          if ( !r_u16((uint32)(0x800716D8u)) && r_u16((uint32)(0x80071790u + 2u * (0))) )
            w_u16((uint32)(0x800716D8u), -8);
          if ( !r_u32((uint32)(0x800718C8u)) )
          {
LABEL_16:
            if ( !r_u16((uint32)(0x800716D8u)) )
              v3 = 1;
          }
          sub_8005A67C();
          sub_8005DFE4(0);
          sub_8005B278(2);
          sub_8005E814(20 * r_u32((uint32)(0x80071A8Cu)) - 2147018076);
        }
        while ( !r_u32((uint32)(0x80071A88u)) && !v3 );
      }
      sub_8005A3C8();
      result = v3;
      if ( r_u32((uint32)(0x80071A88u)) )
        return 1;
    }
    else
    {
LABEL_5:
      sub_8005A3C8();
      return 3;
    }
  }
  return result;
}

uint32 sub_8002F0F8(void)
{
    FUNCTION_MARKER(0x8002F0F8u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

  uint32 result; 
  sint32 v1; 
  sint32 v2; 
  uint32 v3; 
  sint32 v4; 
  uint32 v5; 

  if ( r_u16((uint32)(0x80071A50u)) >= (uint32)(uint16)r_u16((uint32)(0x8007158Cu)) )
    w_u16((uint32)(0x8007158Cu), 0);
  else
    w_u16((uint32)(0x8007158Cu), r_u16((uint32)(0x8007158Cu)) - (r_u16((uint32)(0x80071A50u))));
  if ( r_u16((uint32)(0x80071A50u)) >= (uint32)(uint16)r_u16((uint32)(0x8007156Cu)) )
    w_u16((uint32)(0x8007156Cu), 0);
  else
    w_u16((uint32)(0x8007156Cu), r_u16((uint32)(0x8007156Cu)) - (r_u16((uint32)(0x80071A50u))));
  if ( r_u16((uint32)(0x80071A50u)) >= (uint32)(uint16)r_u16((uint32)(0x8007155Cu)) )
    w_u16((uint32)(0x8007155Cu), 0);
  else
    w_u16((uint32)(0x8007155Cu), r_u16((uint32)(0x8007155Cu)) - (r_u16((uint32)(0x80071A50u))));
  result = (uint16)r_u16((uint32)(0x8007158Cu)) | (uint16)r_u16((uint32)(0x8007155Cu));
  if ( (uint16)r_u16((uint32)(0x8007156Cu)) | result )
  {
    v1 = r_u32((uint32)(0x80071680u));
    w_u32((uint32)(0x80071680u), r_u32((uint32)(0x80071680u)) + (40));
    w_u8((uint32)((v1 + 3)), 3);
    w_u8((uint32)((v1 + 7)), 98);
    v2 = r_u16((uint32)(0x800719D0u));
    w_u16((uint32)((v1 + 12)), 384);
    w_u16((uint32)((v1 + 8)), 0);
    w_u16((uint32)((v1 + 10)), 0);
    w_u16((uint32)((v1 + 14)), 251);
    if ( v2 )
    {
      w_u8((uint32)((v1 + 4)), r_u16((uint32)(0x8007158Cu)));
      w_u8((uint32)((v1 + 5)), r_u16((uint32)(0x8007156Cu)));
      w_u8((uint32)((v1 + 6)), r_u16((uint32)(0x8007155Cu)));
    }
    else
    {
      w_u8((uint32)((v1 + 4)), r_u16((uint32)(0x8007158Cu)) - ((uint16)r_u16((uint32)(0x8007158Cu)) >> 3));
      w_u8((uint32)((v1 + 5)), r_u16((uint32)(0x8007156Cu)) - ((uint16)r_u16((uint32)(0x8007156Cu)) >> 3));
      w_u8((uint32)((v1 + 6)), r_u16((uint32)(0x8007155Cu)) - ((uint16)r_u16((uint32)(0x8007155Cu)) >> 3));
    }
    v3 = (uint32)r_u32((uint32)(0x8007184Cu));
    v4 = r_u32((uint32)(0x80071680u));
    w_u32((uint32)(v1), r_u32((uint32)(v1)) & 0xFF000000 | r_u32((uint32)(r_u32((uint32)(0x8007184Cu)))) & 0xFFFFFF);
    w_u32((uint32)(0x80071680u), v4 + 40);
    w_u32((uint32)(v3), r_u32((uint32)(v3)) & 0xFF000000 | v1 & 0xFFFFFF);
    sub_8005EEB8(v4, 1, 1, (uint16)r_u16((uint32)(0x80071782u)), 0u);
    v5 = (uint32)r_u32((uint32)(0x8007184Cu));
    w_u32((uint32)(v4), r_u32((uint32)(v4)) & 0xFF000000 | r_u32((uint32)(r_u32((uint32)(0x8007184Cu)))) & 0xFFFFFF);
    result = r_u32((uint32)(v5)) & 0xFF000000 | v4 & 0xFFFFFF;
    w_u32((uint32)(v5), result);
  }
  return result;
}

uint32 sub_80046324(uint32 a1, uint32 a2, uint32 a3)
{
    FUNCTION_MARKER(0x80046324u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

  sint32 v3; 
  sint32 v5; 
  sint32 v6; 
  sint32 v7; 
  sint32 result; 
  sint32 v9; 
  sint32 v10; 
  sint32 v11; 
  sint32 v12; 
  sint32 v13; 
  sint32 v14; 
  sint32 v15; 
  uint32 v16; 
  sint32 v17; 

  v3 = a1;
  v5 = (uint16)r_u16((uint32)(a3));
  v6 = a2;
  if ( v5 == 0xFFFF
    || (v7 = sub_80045EF4((uint32)(14 * v5 + r_u32((uint32)(0x80071704u))), a1, a2), result = -v7, v7 == -1000000) )
  {
    v9 = v3;
    v10 = v6;
    if ( v3 < (sint32)r_u32((uint32)(0x80071874u)) )
      v3 = (sint32)r_u32((uint32)(0x80071874u));
    if ( (sint32)r_u32((uint32)(0x8007187Cu)) < v3 )
      v3 = (sint32)r_u32((uint32)(0x8007187Cu));
    if ( v6 < (sint32)r_u32((uint32)(0x80071878u)) )
      v6 = (sint32)r_u32((uint32)(0x80071878u));
    v11 = v3 - (sint32)r_u32((uint32)(0x80071874u));
    if ( (sint32)r_u32((uint32)(0x80071880u)) < v6 )
      v6 = (sint32)r_u32((uint32)(0x80071880u));
    if ( !r_u32((uint32)(0x80071864u)) )
      abort(); /* TODO: Original BREAK exception requires an integration boundary */
    if ( r_u32((uint32)(0x80071864u)) == -1 && v11 == 0x80000000 )
      abort(); /* TODO: Original BREAK exception requires an integration boundary */
    v12 = v6 - (sint32)r_u32((uint32)(0x80071878u));
    if ( !r_u32((uint32)(0x80071884u)) )
      abort(); /* TODO: Original BREAK exception requires an integration boundary */
    if ( r_u32((uint32)(0x80071884u)) == -1 && v12 == 0x80000000 )
      abort(); /* TODO: Original BREAK exception requires an integration boundary */
    v13 = r_u32((uint32)((4 * (v12 / r_u32((uint32)(0x80071884u)) * r_u32((uint32)(0x80071598u)) + v11 / r_u32((uint32)(0x80071864u))) + r_u32((uint32)(0x800718D0u)))));
    v14 = 2 * v13;
    if ( v13 == -1
      || (v15 = r_u16((uint32)((v14 + r_u32((uint32)(0x80071714u))))),
          v16 = (uint32)(v14 + r_u32((uint32)(0x80071714u)) + 2),
          v15 == 0xFFFF) )
    {
LABEL_27:
      w_u16((uint32)(a3), -1);
      return -3000;
    }
    else
    {
      while ( 1 )
      {
        v17 = sub_80045EF4((uint32)(14 * v15 + r_u32((uint32)(0x80071704u))), v9, v10);
        if ( v17 != -1000000 )
          break;
        v15 = r_u16((uint32)((v16 += 2u, v16 - 2u)));
        if ( v15 == 0xFFFF )
          goto LABEL_27;
      }
      w_u16((uint32)(a3), v15);
      return -v17;
    }
  }
  return result;
}

uint32 sub_80057BC0(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a9)
{
    FUNCTION_MARKER(0x80057BC0u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

  sint16 v13; 
  sint32 v14; 
  sint32 v15; 
  sint32 v16; 
  sint32 result; 

  w_u32((uint32)(0x1F800028u), (sint16)sub_80046D0C(r_u16((uint32)(a2)) - r_u16((uint32)(a1))));
  w_u16((uint32)(0x1F80002Cu), (sint16)sub_80046D0C(r_u16((uint32)(a2 + 2u * (1))) - r_u16((uint32)(a1 + 2u * (1)))));
  v13 = sub_80046D0C(r_u16((uint32)(a2 + 2u * (2))) - r_u16((uint32)(a1 + 2u * (2))));
  v14 = a4 * r_u32((uint32)(0x1F800028u));
  v15 = a4 * r_u16((uint32)(0x1F80002Cu));
  v16 = a4 * v13;
  if ( !a3 )
    abort(); /* TODO: Original BREAK exception requires an integration boundary */
  if ( a3 == -1 && v14 == 0x80000000 )
    abort(); /* TODO: Original BREAK exception requires an integration boundary */
  if ( a3 == -1 && v15 == 0x80000000 )
    abort(); /* TODO: Original BREAK exception requires an integration boundary */
  if ( a3 == -1 && v16 == 0x80000000 )
    abort(); /* TODO: Original BREAK exception requires an integration boundary */
  w_u32((uint32)(0x1F800028u), v14 / a3);
  w_u16((uint32)(0x1F80002Cu), v15 / a3);
  w_u16((uint32)(0x1F800030u), v16 / a3);
  w_u16((uint32)(a9 + 2u * (12)), -(sint16)(r_u16((uint32)(a1)) + v14 / a3) & 0xFFF);
  w_u16((uint32)(a9 + 2u * (13)), (r_u16((uint32)(a1 + 2u * (1))) + r_u16((uint32)(0x1F80002Cu)) - 4096) & 0xFFF);
  result = -((uint16)r_u16((uint32)(a1 + 2u * (2))) + r_u16((uint32)(0x1F800030u))) & 0xFFF;
  w_u16((uint32)(a9 + 2u * (14)), result);
  return result;
}

uint32 sub_80014F0C(uint32 file,uint32 slot,uint32 maximum)
{
    uint16 count,lookup[32],record[8];
    uint32 destination,index,variant,i,result;
    file=(uint16)file;slot=(uint16)slot;maximum=(uint16)maximum;
    FUNCTION_MARKER(0x80014F0Cu,"SLES_007.30");
    result=sub_8004E0A0(file);if((sint32)result<0)return result;
    sub_8004DD18(draft_local_address(&count,2),2);
    sub_8004DD18(draft_local_address(lookup,sizeof(lookup)),64);
    if(count>=maximum)count=(uint16)maximum;
    if((sint32)(350u-slot)<count)count=(uint16)(350u-slot);
    result=count;
    destination=0x800C0564u+16*slot;
    if(count) {
        --count;
        do {
            sub_8004DD18(draft_local_address(record,sizeof(record)),16);
            index=(uint16)sub_800127C8(lookup[record[0]],0xFFFFu);
            variant=r_u8(0x800C020Cu+index)==2?0:r_u8(0x800AF768u+40*index+record[1]);
            w_u16(destination,r_u16(0x800AEE74u+2*index));
            w_u16(destination+2,r_u16(0x800C0224u+2*variant));
            for(i=2;i<8;++i)w_u16(destination+2*i,record[i]);
            result=(uint32)count-1u;
            destination+=16;
            if(!count){count=0xFFFFu;break;}
            --count;
        }while(1);
    }
    nullsub_2();return result;
}

uint32 sub_8003681C(uint32 a1)
{
    FUNCTION_MARKER(0x8003681Cu, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

  sint32 v2; 
  sint32 result; 
  sint32 v4; 
  sint32 v5; 
  sint32 v6; 
  sint32 v7; 
  sint32 v8; 
  sint32 v9; 
  uint8 v10; 
  sint32 v11; 

  v2 = a1 + 12;
  result = 0xFFFF;
  if ( r_u16((uint32)(0x800BC0CCu)) != 0xFFFF )
  {
    v4 = r_u8((uint32)((14 * r_u16((uint32)(0x800BC0CCu)) + r_u32((uint32)(0x80071704u)) + 9)));
    v5 = (sint16)r_u16((uint32)((a1 + 12)));
    v6 = 8;
    if ( v4 < v5 )
    {
      v7 = (v5 - v4) << 16;
      if ( (sint16)((uint32)(v7) >> 16) >= 9 )
        v7 = 0x80000;
      v6 = 8 - (v7 >> 16);
    }
    v8 = r_u8((uint32)((v2 + 2)));
    v9 = v4 - v8;
    if ( v8 < v4 )
    {
      v10 = v9 < 9;
      v11 = v9 << 16;
      if ( !v10 )
        v11 = 0x80000;
      v6 = 8 - (v11 >> 16);
    }
    result = 1;
    if ( r_u16((uint32)((v2 + 4))) )
    {
      if ( r_u16((uint32)((v2 + 4))) == 1 )
      {
        if ( v6 )
        {
          return sub_8004486C(2, r_u16((uint32)((v2 + 6))), 0, 0, draft_unknown_argument("sub_8004486C", 5u), draft_unknown_argument("sub_8004486C", 6u));
        }
        else
        {
          sub_800449A0(r_u16((uint32)((v2 + 6))));
          sub_8004486C(4, r_u16((uint32)((v2 + 6))), 0, 0, draft_unknown_argument("sub_8004486C", 5u), draft_unknown_argument("sub_8004486C", 6u));
          result = r_u16((uint32)((v2 + 2))) & 0x400;
          w_u16((uint32)((v2 + 4)), 0);
          if ( result )
            return sub_80032FD0((uint32)a1);
        }
      }
    }
    else if ( v6 )
    {
      w_u16((uint32)((v2 + 6)), sub_8004496C());
      sub_8004486C(1, r_u16((uint32)((v2 + 6))), r_u16((uint32)((v2 + 8))), r_u16((uint32)((v2 + 10))), draft_unknown_argument("sub_8004486C", 5u), draft_unknown_argument("sub_8004486C", 6u));
      result = 1;
      w_u16((uint32)((v2 + 4)), 1);
    }
  }
  return result;
}

uint32 sub_8002F36C(void)
{
    uint32 packet, mode_packet, ordering, result;
    sint16 fade;
    FUNCTION_MARKER(0x8002F36Cu, "SLES_007.30");
    fade=(sint16)(r_u16(0x8007194Cu)+r_u16(0x800717A4u));
    w_u16(0x8007194Cu,(uint16)fade);
    if(fade<0){w_u16(0x8007194Cu,0);w_u16(0x800717A4u,0);}
    if((sint16)r_u16(0x8007194Cu)>=256){w_u16(0x8007194Cu,255);w_u16(0x800717A4u,0);}
    result=(uint32)(sint32)(sint16)r_u16(0x8007194Cu);
    if(!result)return result;
    packet=r_u32(0x80071680u);w_u32(0x80071680u,packet+40);
    w_u8(packet+3,3);w_u8(packet+7,98);
    w_u16(packet+10,0);w_u16(packet+8,0);
    w_u8(packet+4,r_u8(0x8007194Cu));
    w_u16(packet+12,384);w_u8(packet+5,r_u8(0x8007194Cu));
    w_u16(packet+14,251);w_u8(packet+6,r_u8(0x8007194Cu));
    ordering=r_u32(0x8007184Cu);mode_packet=r_u32(0x80071680u);
    w_u32(packet,(r_u32(packet)&0xFF000000u)|(r_u32(ordering)&0xFFFFFFu));
    w_u32(ordering,(r_u32(ordering)&0xFF000000u)|(packet&0xFFFFFFu));
    w_u32(0x80071680u,mode_packet+40);
    sub_8005EEB8(mode_packet,1,1,r_u16(0x80071780u+2*r_u16(0x800716FCu)),0);
    ordering=r_u32(0x8007184Cu);
    w_u32(mode_packet,(r_u32(mode_packet)&0xFF000000u)|(r_u32(ordering)&0xFFFFFFu));
    result=(r_u32(ordering)&0xFF000000u)|(mode_packet&0xFFFFFFu);
    w_u32(ordering,result);
    return result;
}

void sub_80050E48(void)
{
    FUNCTION_MARKER(0x80050E48u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

  sint32 v0; 









  if ( r_u8((uint32)(0x800715E4u)) )
  {
    if ( r_u16((uint32)(0x80071930u)) )
    {
      sub_80050A08();
    }
    else
    {
      sub_80050414();
      sub_8004E73C();
      if ( r_u8((uint32)(0x800AFFB0u)) )
      {
        sub_8004F220(-2146763072, 30);
        sub_8004F1F8(-2146763072, 30);
      }
      if ( r_u8((uint32)(0x800B00D0u)) )
      {
        sub_8004F220(-2146762784, 218);
        sub_8004F1F8(-2146762784, 346);
      }
      if ( r_u8((uint32)(0x80071760u)) )
        sub_8004EB88((uint8)r_u8((uint32)(0x800716CCu)), r_u16((uint32)(0x800715E0u)), r_u16((uint32)(0x800716B8u)), 128);
      sub_8004F8BC();
      if ( !r_u16((uint32)(0x800715BCu)) )
      {
        v0 = (sint16)r_u16((uint32)(0x80071558u));
        if ( r_u16((uint32)(0x80071558u)) == 2 )
        {
          sub_80050134();
          v0 = (sint16)r_u16((uint32)(0x80071558u));
        }
        if ( v0 == 1 )
          sub_8004FC14();
      }
    }
  }
  else
  {
    sub_8004EDD8(228, 239, 0x80010BE4u);
    sub_80018A9C(0, 0, 384, 16, 0, 0, 0, 1);
    sub_80018A9C(0, 235, 384, 16, 0, 0, 0, 1);
  }
}

uint32 sub_8005764C(uint32 a1, uint32 a2)
{
    FUNCTION_MARKER(0x8005764Cu, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

  uint16 v3; 
  uint32 v4; 
  uint32 v5; 
  sint32 v6; 
  sint32 v7; 
  sint32 v8; 
  uint16 v9; 
  sint32 v10; 
  uint32 v11; 
  sint32 v12; 
  uint16 v13; 
  sint32 result; 
  uint16 v15[4]; 

  sub_8004E0A0((uint16)a1);
  sub_8004DD18(draft_local_address(v15, sizeof(v15)), 2);
  v3 = 0;
  v4 = sub_80011A98(v15[0]);
  v5 = sub_80011A98(2 * v15[0]);
  sub_8004DD18(v4, v15[0]);
  v6 = 0;
  if ( v15[0] )
  {
    v7 = 0;
    do
    {
      ++v6;
      v3 += (uint8)r_u8((uint32)(v4 + 1u * (v7)));
      v7 = (uint16)v6;
    }
    while ( (uint16)v6 < (uint32)v15[0] );
  }
  v8 = v3;
  v9 = 0;
  if ( !v3 )
    v8 = 1;
  v10 = 0;
  v11 = sub_80011A98(12 * v8);
  if ( v15[0] )
  {
    v12 = 0;
    do
    {
      v13 = (uint8)r_u8((uint32)(v4 + 1u * (v12)));
      w_u16((uint32)((v5 + 2u * (v12))), v9);
      if ( v13 )
      {
        sub_8004DD18((v11 + 4u * (3 * v9)), 12 * v13);
        v9 += v13;
      }
      v12 = (uint16)++v10;
    }
    while ( (uint16)v10 < (uint32)v15[0] );
  }
  nullsub_2();
  result = 40 * (uint16)a2;
  w_u32((uint32)((result - 2146697952)), v4);
  w_u32((uint32)((result - 2146697948)), v5);
  w_u32((uint32)((result - 2146697944)), v11);
  return result;
}

