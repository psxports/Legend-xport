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
extern uint32 sub_80031224();
extern uint32 sub_80031308();
extern uint32 sub_8003133C();
extern uint32 sub_80032FD0();

extern uint32 sub_800449A0();
extern uint32 sub_80044F58();
extern uint32 sub_800467A0();
extern uint32 sub_8004EB88();
extern uint32 sub_80051550();
extern uint32 sub_800516E8();
extern uint32 sub_80052078();
extern uint32 sub_80052228();
extern uint32 sub_800522D0();
extern uint32 sub_800524AC();
extern uint32 sub_80053774();
extern uint32 sub_80053A28(uint32 position, uint32 effect);
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

uint32 sub_80054454(uint32 a1, uint32 a2)
{
    FUNCTION_MARKER(0x80054454u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

    sint16 v4;
    sint32 result;

    sint32 v9;
    sint32 v10;
    sint32 v11;
    sint32 v12;
    sint32 v13;
    sint32 v14;
    sint32 v15;
    sint32 v16;
    sint16 v17;
    uint32 v18;
    sint32 v19;
    sint32 v20;
    sint32 v21;
    uint8 v22;
    sint32 v23;
    sint32 v24;
    sint32 v25;
    sint32 v26;
    uint32 v27;
    sint16 v28;
    sint32 v29;
    sint32 v30;
    uint32 v31;
    uint32 v32;
    sint16 v33;
    sint16 v34;
    sint32 v35;
    sint32 v36;
    sint32 v37;
    sint16 v38;
    sint32 v39;
    sint32 v40;
    sint32 v41;
    sint32 v42;
    sint32 v43;

    sint32 v46;
    uint32 v47;
    sint16 v48;
    uint32 v49;
    sint16 v50;
    sint32 v51;
    sint32 v52;
    sint16 v53;
    sint16 v54;
    sint16 v55;
    uint32 v56;
    sint16 v57;
    sint16 v58;
    sint16 v59;
    sint16 v60;
    sint32 v61;
    sint32 v62;
    sint16 v63;
    sint16 v64;
    sint16 v65;
    sint16 v66;
    sint16 v67;
    sint32 v68;
    sint16 v69;
    sint32 v70;
    sint32 v71;
    sint32 v72;
    sint32 v73;
    uint16 v74;
    sint16 v75;
    sint32 v76;
    sint16 v77;
    uint16 v78;
    sint16 v79;
    sint32 v80;
    sint16 v81;
    sint16 v82;
    sint16 v83;
    sint16 v84;
    sint32 v85;
    sint32 v86;
    sint16 v87;
    sint32 v88;
    sint16 v89;
    sint32 v90;
    sint32 v91;
    sint16 v92;
    uint16 v93;
    uint16 v94;
    sint32 v95;
    sint32 v96;
    sint32 v97;
    sint32 v98;
    sint32 v99;
    sint32 v100;
    sint32 v101;
    sint32 v102;
    sint16 v103;
    sint32 v104;
    sint32 v105;
    sint32 v106;
    sint32 v107;
    sint32 v108;
    sint32 v109;
    sint16 v110;
    sint32 v111;
    sint32 v112;
    sint32 v113;
    sint32 v114;
    sint32 v115;
    sint32 v116;
    sint16 v117;
    sint32 v118;
    sint32 v119;
    sint32 v120;
    sint32 v121;
    sint32 v122;
    sint32 v123;
    sint32 v124;
    sint32 v125;
    sint32 v126;
    sint32 v127;
    uint32 v128;
    sint32 v129;
    sint32 v130;
    sint32 v131;
    sint32 v132;
    sint32 v133;
    sint32 v134;
    sint32 v135;
    uint32 v136;
    sint32 v137;
    sint32 v138;
    sint32 v139;
    uint32 v140;
    sint32 v141;
    sint32 v142;
    sint32 v143;
    sint32 v144;
    sint32 v145;

    sint32 v148;

    sint32 v150;
    uint32 position[3];
    uint32 v151;

    sint32 v153;

    v4 = 1;
    result = r_u8((uint32)((a1 + 240)));
    if (!r_u8((uint32)((a1 + 240))))
        return result;
    if (r_u16((uint32)((a1 + 246))))
        w_u16((uint32)(0x800715C8u), 0);
    sub_80044CC0(r_u32((uint32)(a1)), r_u32((uint32)((a1 + 8))));
    sub_80044DC8(r_u32((uint32)(a1)), r_u32((uint32)((a1 + 8))));
    if (!r_u16((uint32)(0x80071940u)) && r_u8((uint32)((a1 + 244))))
    {
        if (r_u16((uint32)((a1 + 214))) != 15)
        {
            v9 = r_u32((uint32)((a1 + 48)));
            w_u32((uint32)((a1 + 68)), 0);
            w_u32((uint32)((a1 + 4)), v9);
            legend_player_reset(a1);
            sub_800513CC((uint32)a1, 15);
            sub_8003F928(r_u16((uint32)((a1 + 76))));
            if (!r_u8((uint32)((288 * (a2 ^ 1) - 2146762832))))
                sub_80054414(r_u32((uint32)(r_u32((uint32)((288 * a2 - 2146763020))))) + 344, r_u32((uint32)(r_u32((uint32)((288 * a2 - 2146763020))))) + 8);
        }
        v10 = r_u32((uint32)((a1 + 60)));
        w_u16((uint32)((a1 + 208)), 0);
        w_u32((uint32)((v10 + 128)), 0);
    }
    v11 = r_u32((uint32)((a1 + 56)));
    if (r_u16((uint32)((v11 + 28))))
    {
        v12 = r_u32((uint32)((v11 + 4)));
        v13 = r_u32((uint32)((v11 + 8)));
        v14 = r_u32((uint32)((v11 + 12)));
        w_u32((uint32)(a1), r_u32((uint32)(v11)));
        w_u32((uint32)((a1 + 4)), v12);
        w_u32((uint32)((a1 + 8)), v13);
        w_u32((uint32)((a1 + 12)), v14);
    }
    v15 = r_u32((uint32)((a1 + 60)));
    w_u16((uint32)((a1 + 272)), 0);
    if (!r_u32((uint32)((v15 + 128))))
        goto LABEL_51;
    v16 = r_u32((uint32)((a1 + 60)));
    w_u16((uint32)((a1 + 272)), 0x7FFF);
    v17 = sub_80046D0C(r_u16((uint32)((v16 + 136))) - r_u16((uint32)((a1 + 18))));
    v18 = r_u8((uint32)((r_u32((uint32)((a1 + 60))) + 132)));
    v19 = v18;
    if (r_u16((uint32)((2 * a2 - 2147018172))))
    {
        v19 = v18 >> 1;
        if (!(v18 >> 1))
            v19 = 1;
    }
    v20 = r_u16((uint32)((a1 + 214)));
    w_u16((uint32)((a1 + 282)), r_u16((uint32)((r_u32((uint32)((a1 + 60))) + 148))));
    if ((uint16)(v20 - 17) >= 2u && (uint32)(v20 - 45) >= 2)
        goto LABEL_23;
    v21 = v17;
    if (v17 < 0)
        v21 = -v17;
    if (v21 < 1025)
    {
    LABEL_23:
        if (v19 < r_u16((uint32)((a1 + 210))))
            w_u16((uint32)((a1 + 210)), r_u16((uint32)((a1 + 210))) - (v19));
        else
            w_u16((uint32)((a1 + 210)), 0);
        v23 = r_u16((uint32)((a1 + 210)));
        w_u32((uint32)((a1 + 200)), 0);
        if (v23)
        {
            if ((r_u32((uint32)((r_u32((uint32)((a1 + 60))) + 132))) & 0x8000) == 0 && r_u16((uint32)((a1 + 74))))
            {
                sub_8003F8D0(r_u16((uint32)((a1 + 76))));
                v30 = v17;
                if (v17 < 0)
                    v30 = -v17;
                v27 = (uint32)a1;
                if (v30 < 1024)
                {
                    v28 = 10;
                    w_u16((uint32)((a1 + 18)), r_u16((uint32)((r_u32((uint32)((a1 + 60))) + 136))) & 0xFFF);
                }
                else
                {
                    w_u16((uint32)((a1 + 18)), (r_u16((uint32)((r_u32((uint32)((a1 + 60))) + 136))) + 2048) & 0xFFF);
                    v31 = sub_80011B8C() & 0x7F;
                    if (v31 < 0x2B)
                        sub_800513CC((uint32)a1, 7);
                    if (v31 - 43 < 0x2B)
                        sub_800513CC((uint32)a1, 8);
                    v27 = (uint32)a1;
                    if (v31 < 0x56)
                        goto LABEL_51;
                    v28 = 9;
                }
            }
            else
            {
                sub_800527C8(a1, v19, 65519);
                v25 = v17;
                if (v17 < 0)
                    v25 = -v17;
                if (v25 >= 1024)
                {
                    v29 = r_u32((uint32)((a1 + 60)));
                    w_u16((uint32)((a1 + 18)), (r_u16((uint32)((v29 + 136))) - 2048) & 0xFFF);
                    if ((r_u32((uint32)((v29 + 132))) & 0x4000) != 0)
                        w_u16((uint32)((a1 + 274)), 60);
                    sub_8003F8D0(r_u16((uint32)((a1 + 76))));
                    v27 = (uint32)a1;
                    v28 = 12;
                }
                else
                {
                    v26 = r_u32((uint32)((a1 + 60)));
                    w_u16((uint32)((a1 + 18)), r_u16((uint32)((v26 + 136))));
                    if ((r_u32((uint32)((v26 + 132))) & 0x4000) != 0)
                        w_u16((uint32)((a1 + 274)), 60);
                    sub_8003F8D0(r_u16((uint32)((a1 + 76))));
                    v27 = (uint32)a1;
                    v28 = 11;
                }
            }
            sub_800513CC(v27, v28);
        }
        else
        {
            v24 = r_u32((uint32)((a1 + 48)));
            w_u32((uint32)((a1 + 68)), 0);
            w_u32((uint32)((a1 + 4)), v24);
            sub_800527C8(a1, v19, 65519);
            sub_800513CC((uint32)a1, 15);
            sub_8003F928(r_u16((uint32)((a1 + 76))));
            if (!r_u8((uint32)((288 * (a2 ^ 1) - 2146762832))))
                sub_80054414(r_u32((uint32)(r_u32((uint32)((288 * a2 - 2146763020))))) + 344, r_u32((uint32)(r_u32((uint32)((288 * a2 - 2146763020))))) + 8);
        }
    }
    else
    {
        v22 = (uint16)(r_u16((uint32)((a1 + 214))) - 17) >= 2u;
        w_u16((uint32)((a1 + 18)), (r_u16((uint32)((r_u32((uint32)((a1 + 60))) + 136))) + 2048) & 0xFFF);
        if (!v22)
        {
            sub_800513CC((uint32)a1, 18);
            sub_8003F9F0();
        }
    }
LABEL_51:
    w_u32((uint32)(0x800BF8F8u), r_u32((uint32)(a1)));
    w_u32((uint32)(0x800BF900u), r_u32((uint32)((a1 + 8))));
    v32 = (0x80071790u + 2u * a2);
    v22 = r_u16((uint32)(0x80071810u)) != 0;
    w_u16((uint32)((a1 + 226)), r_u16((uint32)(v32)));
    if (!v22)
        w_u16((uint32)((a1 + 226)), 0);
    v33 = r_u16((uint32)((a1 + 228)));
    w_u16((uint32)((a1 + 226)), r_u16((uint32)((a1 + 226))) & (~v33));
    v34 = v33 & r_u16((uint32)(v32));
    v35 = (sint16)r_u16((uint32)((a1 + 204)));
    w_u16((uint32)((a1 + 242)), 0);
    w_u8((uint32)((a1 + 213)), 0);
    w_u16((uint32)((a1 + 228)), v34);
    if (v35 != -1)
    {
        if (r_u16((uint32)((a1 + 214))) == 2)
            sub_800513CC((uint32)a1, 0);
        v36 = r_u16((uint32)((a1 + 264)));
        w_u16((uint32)((a1 + 226)), 0x2000);
        w_u16((uint32)((a1 + 236)), 0);
        w_u8((uint32)((a1 + 244)), 0);
        if (v36 == 5 && r_u16((uint32)((a1 + 214))) != 4)
            sub_800513CC((uint32)a1, 4);
    }
    v37 = r_u16((uint32)((a1 + 278)));
    w_u8((uint32)((a1 + 244)), 1);
    if (v37)
    {
        v38 = r_u16((uint32)((a1 + 278)));
        w_u8((uint32)((a1 + 244)), 0);
        w_u16((uint32)((a1 + 278)), v38 - 1);
    }
    if (r_u16((uint32)((a1 + 74))))
    {
        v39 = r_u32((uint32)((a1 + 44)));
        if (v39 < 8)
            w_u32((uint32)((a1 + 44)), 0);
        else
            w_u32((uint32)((a1 + 44)), v39 - 8);
    }
    v40 = (sint16)r_u16((uint32)((a1 + 268)));
    w_u8((uint32)((a1 + 245)), 0);
    v41 = r_u32((uint32)(0x800716D0u));
    w_u32((uint32)((a1 + 32)), 0);
    v40 = (uint16)(r_u16((uint32)((2 * v40 + v41))));
    v42 = r_u16((uint32)((a1 + 236)));
    w_u16((uint32)((a1 + 270)), v40);
    if (v42)
        (w_u16((uint32)((a1 + 236)), r_u16((uint32)((a1 + 236))) - 1u), r_u16((uint32)((a1 + 236))));
    v43 = r_u16((uint32)((a1 + 214)));
    if ((uint32)(v43 - 32) >= 2 && (uint32)(v43 - 34) >= 2 && (r_u16((uint32)(0x800719D0u)) & 0xF) == 0 && r_u8((uint32)((a1 + 241))) < 0x40u)
    {
        (w_u8((uint32)((a1 + 241)), r_u8((uint32)((a1 + 241))) + 1u), r_u8((uint32)((a1 + 241))));
    }
    w_u16((uint32)((r_u32((uint32)((a1 + 60))) + 144)), 0);
    sub_80053B00(a1);
    v46 = a2;
    if (r_u16((uint32)(0x80071930u)))
    {
        v46 = a2;
        if (r_u16((uint32)(0x80071A0Cu)) >= 3u)
        {
            if (r_u16((uint32)((a1 + 214))) != 36)
                sub_800513CC((uint32)a1, 36);
            v46 = a2;
        }
    }
    v47 = (uint32)(2 * v46 - 2147018172);
    if (r_u16((uint32)(v47)))
        (w_u16((uint32)(v47), r_u16((uint32)(v47)) - 1u), r_u16((uint32)(v47)));
    switch (r_u16((uint32)((a1 + 216))))
    {
        case 0:
            if (r_u16((uint32)((a1 + 246))) && !r_u16((uint32)((a1 + 248))))
            {
                legend_player_reset(a1);
                sub_800513CC((uint32)a1, 0);
            }
            if (r_u16((uint32)((a1 + 214))) == 6 && r_u8((uint32)((a1 + 96))))
                sub_800513CC((uint32)a1, 0);
            if (!r_u16((uint32)((a1 + 74))))
                goto LABEL_342;
            v48 = r_u16((uint32)((a1 + 226)));
            if ((v48 & 0xF000) != 0)
            {
                v49 = (uint32)a1;
                if (r_u16((uint32)((a1 + 236))))
                {
                    v50 = 2;
                    w_u16((uint32)((a1 + 236)), 0);
                    w_u16((uint32)((a1 + 238)), 0);
                }
                else
                {
                    w_u16((uint32)((a1 + 236)), 16);
                    v50 = 1;
                }
                goto LABEL_341;
            }
            v51 = v48 & 0xF0;
            if ((v48 & 0xA) == 10)
            {
                if ((v48 & 0xF0) != 0 && r_u8((uint32)((a1 + 218))) < 7u)
                {
                    v52 = r_u8((uint32)((a1 + 218)));
                    w_u8((uint32)((a1 + 218)), v52 + 1);
                    w_u8((uint32)((v52 + a1 + 219)), v51);
                    w_u16((uint32)((a1 + 228)), r_u16((uint32)((a1 + 228))) | (v51));
                }
                sub_80053774(a1, v51);
                goto LABEL_342;
            }
            v53 = r_u16((uint32)((a1 + 226)));
            w_u8((uint32)((a1 + 218)), 0);
            if ((v53 & 0x40) != 0)
            {
                v49 = (uint32)a1;
                v54 = r_u16((uint32)((a1 + 228)));
                v50 = 4;
                w_u16((uint32)((a1 + 236)), 0);
                w_u16((uint32)((a1 + 228)), v54 | 0x40);
                goto LABEL_341;
            }
            if ((v53 & 0x20) == 0)
                goto LABEL_109;
            v55 = r_u16((uint32)((a1 + 232)));
            v56 = (uint32)a1;
            if ((v55 & 2) != 0)
            {
                v57 = r_u16((uint32)((a1 + 228)));
                v58 = 3;
            }
            else
            {
                if ((v55 & 4) == 0)
                {
                    if ((v55 & 0x18) != 0)
                    {
                        legend_player_reset(a1);
                        v59 = r_u16((uint32)((a1 + 228)));
                        v60 = r_u16((uint32)((a1 + 232)));
                        w_u16((uint32)((a1 + 236)), 0);
                        v60 |= 1u;
                        w_u16((uint32)((a1 + 232)), v60);
                        w_u16((uint32)((a1 + 228)), v59 | 0x20);
                        if ((v60 & 0x10) != 0 && (v49 = (uint32)a1, r_u32((uint32)((4 * a2 + 28 * a2 - 2146673372))) >= r_u32((uint32)((4 * a2 + 28 * a2 - 2146690220)))))
                        {
                            v50 = 44;
                        }
                        else
                        {
                            v49 = (uint32)a1;
                            v50 = 43;
                        }
                        goto LABEL_341;
                    }
                LABEL_109:
                    if ((r_u16((uint32)((a1 + 226))) & 8) == 0)
                        goto LABEL_119;
                    w_u16((uint32)((a1 + 228)), r_u16((uint32)((a1 + 228))) | (8u));
                    sub_80052078(a1, 768, 6000);
                    v49 = (uint32)a1;
                    v50 = 17;
                    goto LABEL_341;
                }
                legend_player_reset(a1);
                v56 = (uint32)a1;
                v57 = r_u16((uint32)((a1 + 228)));
                v58 = 41;
            }
            w_u16((uint32)((a1 + 236)), 0);
            w_u16((uint32)((a1 + 228)), v57 | 0x20);
            sub_800513CC(v56, v58);
            w_u16((uint32)((a1 + 232)), r_u16((uint32)((a1 + 232))) | (1u));
        LABEL_342:
            if (!r_u8((uint32)((a1 + 213))) && r_u16((uint32)((a1 + 110))))
                w_u8((uint32)((a1 + 213)), 2);
            v126 = r_u32((uint32)((a1 + 32)));
            if (v126)
            {
                sub_80051550((uint32)a1, v126, a1 + 24);
                w_u8((uint32)((a1 + 245)), 1);
            }
            v127 = r_u32((uint32)((a1 + 44)));
            if (v127)
            {
                sub_80051550((uint32)a1, v127, a1 + 36);
                if (r_u16((uint32)((a1 + 74))) && (r_u16((uint32)(0x800719D0u)) & 3) == 0)
                {
                    w_u32((uint32)(0x1F800028u), 0);
                    w_u32((uint32)(0x1F80002Cu), 5);
                    w_u32((uint32)(0x1F800030u), 0);
                    sub_80022CC0((uint32)a1, (uint32)0x1F800028, 2, 5);
                }
                w_u8((uint32)((a1 + 245)), 1);
            }
            sub_80058484(a1 + 76, r_u32((uint32)((a1 + 52))));
            v128 = (uint32)a1;
            if (r_u16((uint32)(0x80071804u)))
            {
                sub_800516E8((uint32)a1, r_u16((uint32)((a1 + 266))));
                v128 = (uint32)a1;
            }
            if (sub_80051614(v128, a1 + 76, r_u16((uint32)((a1 + 18)))))
                w_u8((uint32)((a1 + 245)), 1);
            sub_80051D38((uint32)a1, a2);
            sub_80046324(r_u32((uint32)(a1)), r_u32((uint32)((a1 + 8))), (uint32)(a1 + 266));
            v129 = r_u16((uint32)((a1 + 266)));
            if (v129 != 0xFFFF)
                sub_80046A28(14 * v129 + r_u32((uint32)(0x80071704u)), v129, (uint32)a1);
            v148 = r_u32(a1 + 16u);
            v150 = r_u32(a1 + 20u);
            v130 = sub_8005178C((uint32)a1, 1000, (uint32)(a1 + 16), r_u16((uint32)((a1 + 266))), a1 + 136);
            v131 = (sint16)r_u16((uint32)((a1 + 74)));
            w_u32((uint32)((a1 + 48)), v130);
            if (!v131)
            {
                if ((sint32)r_u32((uint32)((a1 + 68))) >= 0)
                {
                    w_u32((uint32)((a1 + 16)), v148);
                    w_u32((uint32)((a1 + 20)), v150);
                }
                else
                {
                    w_u16((uint32)((a1 + 16)), sub_80051EB8(v148, 0));
                    w_u16((uint32)((a1 + 20)), sub_80051EB8(v150, 0));
                }
            }
            sub_800519E4(a1 + 68, (uint32)a1, r_u32((uint32)((a1 + 48))), v4);
            v132 = r_u16((uint32)((a1 + 266)));
            if (v132 == 0xFFFF)
            {
                w_u16((uint32)((a1 + 268)), 0);
            }
            else
            {
                v133 = 14 * v132;
                v134 = r_u32((uint32)(0x80071704u));
                v135 = r_u16((uint32)((a1 + 266)));
                w_u16((uint32)((a1 + 268)), r_u8((uint32)((v133 + r_u32((uint32)(0x80071704u)) + 9))));
                w_u16((uint32)((a1 + 264)), r_u8((uint32)((14 * v135 + v134 + 8))));
            }
            v136 = r_u32((uint32)((a1 + 56)));
            v137 = r_u32((uint32)((a1 + 4)));
            v138 = r_u32((uint32)((a1 + 8)));
            v139 = r_u32((uint32)((a1 + 12)));
            w_u32((uint32)(v136), r_u32((uint32)(a1)));
            w_u32((uint32)(v136 + 4u * (1)), v137);
            w_u32((uint32)(v136 + 4u * (2)), v138);
            w_u32((uint32)(v136 + 4u * (3)), v139);
            w_u16((uint32)((r_u32((uint32)((a1 + 56))) + 24)), r_u16((uint32)((a1 + 18))));
            sub_800471E8(r_u32((uint32)((a1 + 56))));
            if (r_u8((uint32)((a1 + 244))))
                sub_800475F4(r_u32((uint32)((a1 + 60))));
            else
                w_u32((uint32)((r_u32((uint32)((a1 + 60))) + 128)), 0);
            v140 = r_u32((uint32)(r_u32((uint32)((a1 + 52)))));
            v141 = r_u32((uint32)((a1 + 4)));
            v142 = r_u32((uint32)((a1 + 8)));
            v143 = r_u32((uint32)((a1 + 12)));
            w_u32((uint32)(v140 + 4u * (2)), r_u32((uint32)(a1)));
            w_u32((uint32)(v140 + 4u * (3)), v141);
            w_u32((uint32)(v140 + 4u * (4)), v142);
            w_u32((uint32)(v140 + 4u * (5)), v143);
            v144 = r_u32((uint32)(r_u32((uint32)((a1 + 52)))));
            v145 = r_u32((uint32)((a1 + 20)));
            w_u32((uint32)((v144 + 24)), r_u32((uint32)((a1 + 16))));
            w_u32((uint32)((v144 + 28)), v145);
            sub_800585D8(a1 + 76);
            sub_80052EE8(a1);
            if (r_u16((uint32)((a1 + 276))))
                w_u16((uint32)((a1 + 276)), r_u16((uint32)((a1 + 276))) - (128));
            result = 1;
            if (r_u8((uint32)((a1 + 212))) == 1)
                return sub_800542D4(a1);
            return result;
        case 1:
            v61 = (sint16)r_u16((uint32)((a1 + 204)));
            if (v61 != -1)
            {
                if ((sint16)r_u16((uint32)((a1 + 268))) == v61)
                    goto LABEL_168;
                goto LABEL_113;
            }
            v49 = (uint32)a1;
            if ((r_u16((uint32)((a1 + 226))) & 0x40) != 0)
            {
                v66 = r_u16((uint32)((a1 + 228)));
                v50 = 4;
                w_u16((uint32)((a1 + 236)), 0);
                w_u16((uint32)((a1 + 228)), v66 | 0x40);
                goto LABEL_341;
            }
            v67 = sub_800524AC(a1);
            if (v67 == 1)
                sub_800513CC((uint32)a1, 0);
            else
                w_u16((uint32)((a1 + 18)), sub_80051EB8(r_u16((uint32)((a1 + 18))), (v67 + r_u16((uint32)((a1 + 270)))) & 0xFFF));
        LABEL_119:
            sub_80054184((uint32)a1);
            goto LABEL_342;
        case 2:
            w_u16((uint32)((a1 + 276)), 1024);
            v68 = (sint16)r_u16((uint32)((a1 + 74)));
            (w_u16((uint32)((a1 + 238)), r_u16((uint32)((a1 + 238))) + 1u), r_u16((uint32)((a1 + 238))));
            if (v68)
            {
                v49 = (uint32)a1;
                if ((r_u16((uint32)((a1 + 226))) & 0x40) != 0)
                {
                    v50 = 5;
                    w_u16((uint32)((a1 + 228)), r_u16((uint32)((a1 + 228))) | (0x40u));
                    goto LABEL_341;
                }
            }
            v69 = sub_800524AC(a1);
            if (v69 != 1)
                goto LABEL_202;
            v49 = (uint32)a1;
            if (r_u16((uint32)((a1 + 238))) < 0x1Fu)
                v50 = 0;
            else
                v50 = 6;
            goto LABEL_341;
        case 3:
            v70 = r_u8((uint32)((a1 + 96)));
            w_u8((uint32)((a1 + 244)), 0);
            if (!v70)
                goto LABEL_342;
            v49 = (uint32)a1;
            v50 = 0;
            goto LABEL_341;
        case 4:
            v71 = r_u16((uint32)((a1 + 92)));
            v72 = v71 << 16;
            if ((uint32)(v71 - 26) >= 9)
                goto LABEL_136;
            if ((r_u16((uint32)((a1 + 226))) & 0x80) != 0)
            {
                w_u16((uint32)((a1 + 228)), r_u16((uint32)((a1 + 228))) | (0x80u));
                sub_80052078(a1, 768, 10000);
                v49 = (uint32)a1;
                v50 = 19;
                goto LABEL_341;
            }
            v72 = v71 << 16;
        LABEL_136:
            v73 = v72 >> 16;
            v22 = v72 >> 16 >= 19;
            v74 = v71 - 18;
            if (!v22)
            {
                v75 = sub_800524AC(a1);
                if (v75 != 1)
                    w_u16((uint32)((a1 + 18)), sub_80051EB8(r_u16((uint32)((a1 + 18))), (v75 + r_u16((uint32)((a1 + 270)))) & 0xFFF));
                v74 = v71 - 18;
                if (v73 == 18)
                {
                    v76 = -2700;
                    if (r_u16((uint32)((a1 + 264))) == 5)
                        v76 = -3200;
                    w_u32((uint32)((a1 + 68)), v76);
                    v74 = v71 - 18;
                }
            }
            if (v74 >= 0xBu)
                goto LABEL_150;
            if ((sint16)v71 == 28 && (sint32)r_u32((uint32)((a1 + 68))) < 0)
                w_u16((uint32)((a1 + 92)), 27);
            v77 = sub_800524AC(a1);
            v78 = v71 - 29;
            if (v77 != 1)
            {
                w_u16((uint32)((a1 + 18)), sub_80051EB8(r_u16((uint32)((a1 + 18))), (v77 + r_u16((uint32)((a1 + 270)))) & 0xFFF));
                v79 = r_u16((uint32)((a1 + 270)));
                w_u32((uint32)((a1 + 32)), 100);
                v80 = r_u16((uint32)((a1 + 264)));
                w_u16((uint32)((a1 + 24)), 0);
                w_u16((uint32)((a1 + 28)), 0);
                w_u16((uint32)((a1 + 26)), (v77 + v79) & 0xFFF);
                v78 = v71 - 29;
                if (v80 == 5)
                {
                    w_u32((uint32)((a1 + 32)), 150);
                LABEL_150:
                    v78 = v71 - 29;
                }
            }
            if (v78 < 0xBu)
            {
                if ((sint16)v71 == 34 && !r_u16((uint32)((a1 + 74))))
                    w_u16((uint32)((a1 + 92)), 33);
                v81 = sub_800524AC(a1);
                if (v81 != 1)
                {
                    w_u16((uint32)((a1 + 18)), sub_80051EB8(r_u16((uint32)((a1 + 18))), (v81 + r_u16((uint32)((a1 + 270)))) & 0xFFF));
                    v82 = r_u16((uint32)((a1 + 270)));
                    w_u16((uint32)((a1 + 36)), 0);
                    w_u16((uint32)((a1 + 24)), 0);
                    w_u16((uint32)((a1 + 40)), 0);
                    w_u16((uint32)((a1 + 28)), 0);
                    v83 = (v81 + v82) & 0xFFF;
                    w_u16((uint32)((a1 + 38)), v83);
                    w_u16((uint32)((a1 + 26)), v83);
                    if ((sint16)v71 == 39)
                        w_u32((uint32)((a1 + 44)), 100);
                    else
                        w_u32((uint32)((a1 + 32)), 100);
                }
            }
            v49 = (uint32)a1;
            if (!r_u8((uint32)((a1 + 96))))
                goto LABEL_342;
            v50 = 0;
            goto LABEL_341;
        case 5:
            v91 = r_u16((uint32)((a1 + 92)));
            if ((uint32)(v91 - 8) < 9 && (r_u16((uint32)((a1 + 226))) & 0x80) != 0)
            {
                w_u16((uint32)((a1 + 228)), r_u16((uint32)((a1 + 228))) | (0x80u));
                sub_80052078(a1, 768, 10000);
                v49 = (uint32)a1;
                v50 = 20;
                goto LABEL_341;
            }
            v92 = r_u16((uint32)((a1 + 18)));
            w_u32((uint32)((a1 + 32)), 200);
            w_u16((uint32)((a1 + 36)), 0);
            w_u16((uint32)((a1 + 24)), 0);
            w_u16((uint32)((a1 + 40)), 0);
            w_u16((uint32)((a1 + 28)), 0);
            w_u16((uint32)((a1 + 38)), v92);
            w_u16((uint32)((a1 + 26)), v92);
            v93 = v91 - 2;
            if ((sint16)v91 == 1)
            {
                w_u32((uint32)((a1 + 68)), -2200);
                v93 = v91 - 2;
            }
            if (v93 >= 7u)
                goto LABEL_216;
            v94 = v91 - 9;
            if ((sint16)v91 == 8)
            {
                v94 = v91 - 9;
                if ((sint32)r_u32((uint32)((a1 + 68))) < 0)
                {
                    w_u16((uint32)((a1 + 92)), 7);
                LABEL_216:
                    v94 = v91 - 9;
                }
            }
            if (v94 >= 0xCu)
                goto LABEL_221;
            v95 = v91 << 16;
            if ((sint16)v91 == 20)
            {
                v95 = v91 << 16;
                if (!r_u16((uint32)((a1 + 74))))
                {
                    w_u16((uint32)((a1 + 92)), 19);
                LABEL_221:
                    v95 = v91 << 16;
                }
            }
            if (v95 >> 16 >= 21)
            {
                w_u32((uint32)((a1 + 32)), 0);
                w_u32((uint32)((a1 + 44)), 50);
            }
            v49 = (uint32)a1;
            if (!r_u8((uint32)((a1 + 96))))
                goto LABEL_342;
            v50 = 0;
            goto LABEL_341;
        case 6:
            if (r_u16((uint32)((a1 + 214))) == 18)
                w_u16((uint32)((r_u32((uint32)((a1 + 60))) + 144)), 1);
            v115 = (sint16)r_u16((uint32)((a1 + 92)));
            if (v115 < 8)
            {
                w_u8((uint32)((a1 + 244)), 0);
                w_u8((uint32)((a1 + 213)), 1);
            }
            if (v115 == 2)
            {
                v116 = r_u16((uint32)((a1 + 214)));
                w_u16((uint32)((a1 + 36)), 0);
                w_u16((uint32)((a1 + 40)), 0);
                if (v116 == 10)
                    v117 = r_u16((uint32)((a1 + 18))) & 0xFFF;
                else
                    v117 = (r_u16((uint32)((a1 + 18))) + 2048) & 0xFFF;
                w_u16((uint32)((a1 + 38)), v117);
                w_u32((uint32)((a1 + 44)), r_u16((uint32)((a1 + 282))));
            }
            v49 = (uint32)a1;
            if (!r_u8((uint32)((a1 + 96))))
                goto LABEL_342;
            v50 = 0;
            goto LABEL_341;
        case 7:
            v108 = (sint16)r_u16((uint32)((a1 + 92)));
            v4 = 0;
            w_u8((uint32)((a1 + 244)), 0);
            if (v108 < 8)
                w_u8((uint32)((a1 + 213)), 1);
            v109 = v108 << 16;
            if (v108 >= 7)
            {
                if (v108 < 43)
                {
                    v110 = r_u16((uint32)((a1 + 18)));
                    w_u16((uint32)((a1 + 24)), 0);
                    w_u16((uint32)((a1 + 28)), 0);
                    w_u32((uint32)((a1 + 32)), 150);
                    w_u16((uint32)((a1 + 26)), v110 & 0xFFF);
                }
                v109 = v108 << 16;
                if (v108 == 43)
                {
                    v111 = r_u32((uint32)((a1 + 28)));
                    w_u32((uint32)((a1 + 36)), r_u32((uint32)((a1 + 24))));
                    w_u32((uint32)((a1 + 40)), v111);
                    w_u32((uint32)((a1 + 44)), 100);
                    v109 = 2818048;
                }
            }
            v22 = v109 >> 16 != 22;
            v112 = v108 << 16;
            if (!v22)
            {
                v112 = v108 << 16;
                if (!r_u16((uint32)((a1 + 74))))
                {
                    w_u16((uint32)((a1 + 92)), 21);
                    v112 = 1376256;
                }
            }
            if (v112 >> 16 == 28 || v112 >> 16 == 40)
                sub_80053A28((uint32)a1, 0x40u);
            if (!r_u8((uint32)((a1 + 96))))
                goto LABEL_273;
            if ((uint16)(w_u16((uint32)((a1 + 238)), r_u16((uint32)((a1 + 238))) + 1u), r_u16((uint32)((a1 + 238)))) < 0xBu)
                goto LABEL_342;
            v113 = r_u16((uint32)((a1 + 210)));
            w_u16((uint32)((a1 + 238)), 0);
            if (!v113)
                goto LABEL_272;
            v49 = (uint32)a1;
            v50 = 13;
            goto LABEL_341;
        case 8:
            v101 = (sint16)r_u16((uint32)((a1 + 92)));
            v4 = 0;
            w_u8((uint32)((a1 + 244)), 0);
            if (v101 < 8)
                w_u8((uint32)((a1 + 213)), 1);
            v102 = v101 << 16;
            if (v101 >= 7)
            {
                if (v101 < 43)
                {
                    v103 = r_u16((uint32)((a1 + 18)));
                    w_u16((uint32)((a1 + 24)), 0);
                    w_u16((uint32)((a1 + 28)), 0);
                    w_u32((uint32)((a1 + 32)), 150);
                    w_u16((uint32)((a1 + 26)), (v103 - 2048) & 0xFFF);
                }
                v102 = v101 << 16;
                if (v101 == 43)
                {
                    v104 = r_u32((uint32)((a1 + 28)));
                    w_u32((uint32)((a1 + 36)), r_u32((uint32)((a1 + 24))));
                    w_u32((uint32)((a1 + 40)), v104);
                    w_u32((uint32)((a1 + 44)), 80);
                    v102 = 2818048;
                }
            }
            v22 = v102 >> 16 != 17;
            v105 = v101 << 16;
            if (!v22)
            {
                v105 = v101 << 16;
                if (!r_u16((uint32)((a1 + 74))))
                {
                    w_u16((uint32)((a1 + 92)), 16);
                    v105 = 0x100000;
                }
            }
            if (v105 >> 16 == 33 || v105 >> 16 == 42)
                sub_80053A28((uint32)a1, 0x40u);
            if (!r_u8((uint32)((a1 + 96))))
                goto LABEL_273;
            if ((uint16)(w_u16((uint32)((a1 + 238)), r_u16((uint32)((a1 + 238))) + 1u), r_u16((uint32)((a1 + 238)))) < 0xBu)
                goto LABEL_342;
            v106 = r_u16((uint32)((a1 + 210)));
            w_u16((uint32)((a1 + 238)), 0);
            if (v106)
            {
                v49 = (uint32)a1;
                v50 = 14;
                goto LABEL_341;
            }
        LABEL_272:
            w_u16((uint32)((a1 + 214)), 15);
            w_u16((uint32)((a1 + 216)), 11);
            goto LABEL_342;
        case 9:
            v114 = r_u8((uint32)((a1 + 96)));
            w_u8((uint32)((a1 + 244)), 0);
            if (!v114)
                goto LABEL_342;
            if (r_u16((uint32)((a1 + 210))) < 0xCu && (sub_80011B8C() & 0x7Fu) >= 0x40)
            {
                sub_800513CC((uint32)a1, 16);
                w_u16((uint32)((a1 + 238)), 120);
                goto LABEL_342;
            }
            v49 = (uint32)a1;
            if (r_u16((uint32)(0x80071558u)) == 2)
                w_u16((uint32)(0x800718D4u), 0);
            v50 = 0;
            goto LABEL_341;
        case 0xA:
            v107 = r_u8((uint32)((a1 + 96)));
            w_u8((uint32)((a1 + 244)), 0);
            if (!v107)
                goto LABEL_342;
            v49 = (uint32)a1;
            if (r_u16((uint32)(0x80071558u)) == 2)
                w_u16((uint32)(0x800718D4u), 0);
            v50 = 0;
            goto LABEL_341;
        case 0xB:
            v96 = r_u8((uint32)((a1 + 96)));
            w_u8((uint32)((a1 + 244)), 0);
            if (v96)
            {
                sub_80022B24(r_u32((uint32)(r_u32((uint32)((288 * a2 - 2146763020))))) + 344);
                if ((uint16)(w_u16((uint32)((a1 + 238)), r_u16((uint32)((a1 + 238))) + 1u), r_u16((uint32)((a1 + 238)))) >= 0x3Du)
                {
                    v97 = r_u16((uint32)((a1 + 208)));
                    w_u16((uint32)((a1 + 210)), 72);
                    if (v97)
                    {
                        v98 = r_u32((uint32)((a1 + 4))) - 8000;
                        (w_u16((uint32)((a1 + 208)), r_u16((uint32)((a1 + 208))) - 1u), r_u16((uint32)((a1 + 208))));
                        w_u32((uint32)((a1 + 4)), v98);
                        sub_800513CC((uint32)a1, 0);
                        sub_800234BC(r_u8((uint32)((a1 + 240))) - 1);
                        sub_8002AFE8((uint32)a1, r_u32((uint32)((a1 + 64))), r_u32((uint32)((a1 + 60))));
                        v99 = r_u8((uint32)((a1 + 240)));
                        w_u16((uint32)((a1 + 278)), 90);
                        w_u16((uint32)((2 * v99 - 2147018174)), 0);
                    }
                    else
                    {
                        v100 = r_u8((uint32)((a1 + 240)));
                        w_u8((uint32)((a1 + 231)), 1);
                        if (!r_u8((uint32)(0x80071767u + 1u * (v100))))
                            w_u8((uint32)(0x80071767u + 1u * (v100)), 1);
                        if (r_u8((uint32)((288 * ((r_u8((uint32)((a1 + 240))) - 1) ^ 1) - 2146762832))))
                            w_u8((uint32)((a1 + 240)), 0);
                    }
                }
            }
            else
            {
            LABEL_273:
                w_u16((uint32)((a1 + 238)), 0);
            }
            goto LABEL_342;
        case 0xC:
            if (r_u16((uint32)((a1 + 238))))
                (w_u16((uint32)((a1 + 238)), r_u16((uint32)((a1 + 238))) - 1u), r_u16((uint32)((a1 + 238))));
            if ((r_u16((uint32)((a1 + 226))) & 0x8000) != 0)
            {
                v22 = r_u16((uint32)((a1 + 238))) < 0x11u;
                w_u16((uint32)((a1 + 228)), r_u16((uint32)((a1 + 228))) | (0x8000u));
                if (v22)
                    w_u16((uint32)((a1 + 238)), 0);
                else
                    w_u16((uint32)((a1 + 238)), r_u16((uint32)((a1 + 238))) - (16));
            }
            if ((r_u16((uint32)((a1 + 226))) & 0x2000) != 0)
            {
                v22 = r_u16((uint32)((a1 + 238))) < 0x11u;
                w_u16((uint32)((a1 + 228)), r_u16((uint32)((a1 + 228))) | (0x2000u));
                if (v22)
                    w_u16((uint32)((a1 + 238)), 0);
                else
                    w_u16((uint32)((a1 + 238)), r_u16((uint32)((a1 + 238))) - (16));
            }
            if (!r_u16((uint32)((a1 + 238))))
            {
                sub_800513CC((uint32)a1, 0);
                if (r_u16((uint32)(0x80071558u)) == 2)
                    w_u16((uint32)(0x800718D4u), 0);
            }
            goto LABEL_342;
        case 0xD:
            if (r_u16((uint32)((a1 + 214))) == 36 && r_u16((uint32)((a1 + 92))) == 12)
                sub_8003F994(r_u16((uint32)((a1 + 76))));
            v49 = (uint32)a1;
            if (!r_u8((uint32)((a1 + 96))))
                goto LABEL_342;
            v50 = 0;
            goto LABEL_341;
        case 0xE:
            if ((sint16)r_u16((uint32)((a1 + 268))) != (sint16)r_u16((uint32)((a1 + 204))))
                goto LABEL_113;
            w_u16((uint32)((a1 + 204)), -1);
            v49 = (uint32)a1;
            v50 = 36;
            goto LABEL_341;
        case 0xF:
            w_u16((uint32)((a1 + 242)), 1);
            sub_80052078(a1, 768, 10000);
            sub_8005302C(a1);
            v49 = (uint32)a1;
            if (!r_u8((uint32)((a1 + 96))))
                goto LABEL_342;
            v50 = 0;
            goto LABEL_341;
        case 0x10:
            w_u8((uint32)(0x80071690u), r_u8((uint32)(0x80071690u)) | (1u));
            w_u8((uint32)((a1 + 244)), 0);
            sub_80052078(a1, 768, 10000);
            v49 = (uint32)a1;
            if (!r_u8((uint32)((a1 + 96))))
                goto LABEL_342;
            v50 = 0;
            goto LABEL_341;
        case 0x11:
            v49 = (uint32)a1;
            if (!r_u8((uint32)((a1 + 96))) && !r_u16((uint32)((a1 + 226))))
                goto LABEL_342;
            v50 = 0;
            goto LABEL_341;
        case 0x12:
            w_u16((uint32)((a1 + 242)), 1);
            v118 = r_u32((uint32)((a1 + 20)));
            w_u32((uint32)((a1 + 24)), r_u32((uint32)((a1 + 16))));
            w_u32((uint32)((a1 + 28)), v118);
            v119 = 200;
            if (r_u16((uint32)((a1 + 214))) == 19)
                v119 = 64;
            w_u32((uint32)((a1 + 32)), v119);
            if (!r_u16((uint32)((a1 + 74))))
                goto LABEL_342;
            v49 = (uint32)a1;
            if (!r_u8((uint32)((a1 + 96))))
                goto LABEL_342;
            v50 = 0;
            goto LABEL_341;
        case 0x13:
            w_u16((uint32)((r_u32((uint32)((a1 + 60))) + 144)), 1);
            v49 = (uint32)a1;
            if (!r_u8((uint32)((a1 + 96))))
                goto LABEL_342;
            v50 = 0;
            goto LABEL_341;
        case 0x14:
            v49 = (uint32)a1;
            if (!r_u32((uint32)((a1 + 200))))
            {
                v50 = 0;
                goto LABEL_341;
            }
            v84 = r_u16((uint32)((a1 + 226)));
            v50 = 40;
            if ((v84 & 0xF000) != 0)
                goto LABEL_341;
            v49 = (uint32)a1;
            if ((v84 & 0x80) == 0)
                goto LABEL_342;
            v50 = 42;
            w_u16((uint32)((a1 + 228)), r_u16((uint32)((a1 + 228))) | (0x80u));
            goto LABEL_341;
        case 0x15:
            v85 = (sint16)r_u16((uint32)((a1 + 204)));
            if (v85 != -1)
            {
                if ((sint16)r_u16((uint32)((a1 + 268))) != v85)
                {
                LABEL_113:
                    sub_8005135C(r_u16((uint32)((a1 + 204))), r_u16((uint32)((a1 + 206))), draft_local_address(position, sizeof(position)));
                    v151 = position[0];
                    v153 = position[2];
                    v151 = (uint32)((uint32)v151 - r_u32((uint32)(a1)));
                    v153 -= r_u32((uint32)((a1 + 8)));
                    v62 = sub_8001F8A8((sint32)v151, v153);
                    v63 = sub_80046B84((sint32)v151, v153, v62);
                    v64 = r_u16((uint32)((a1 + 18)));
                    v65 = v63 & 0xFFF;
                    goto LABEL_203;
                }
            LABEL_168:
                w_u16((uint32)((a1 + 204)), -1);
                goto LABEL_342;
            }
            v49 = (uint32)a1;
            if (!r_u32((uint32)((a1 + 200))))
            {
                v50 = 0;
                goto LABEL_341;
            }
            v69 = sub_800524AC(a1);
            v49 = (uint32)a1;
            if (v69 == 1)
            {
                v50 = 39;
                goto LABEL_341;
            }
            goto LABEL_202;
        case 0x16:
            v86 = r_u16((uint32)((a1 + 92)));
            w_u8((uint32)((a1 + 244)), 0);
            if (v86 == 50)
            {
                v49 = (uint32)a1;
                if (!r_u32((uint32)((a1 + 200))))
                {
                    v50 = 0;
                    goto LABEL_341;
                }
            }
            v49 = (uint32)a1;
            if (!r_u8((uint32)((a1 + 96))))
                goto LABEL_342;
            v50 = 39;
            goto LABEL_341;
        case 0x17:
            v87 = r_u16((uint32)((a1 + 92)));
            w_u16((uint32)((a1 + 242)), 1);
            sub_80052078(a1, 768, 10000);
            if (v87 == 19)
                w_u32((uint32)((a1 + 200)), 0);
            v49 = (uint32)a1;
            if (!r_u8((uint32)((a1 + 96))))
                goto LABEL_342;
            v50 = 0;
            goto LABEL_341;
        case 0x18:
            w_u8((uint32)((a1 + 244)), 0);
            sub_80052228(a1);
            if (r_u16((uint32)((a1 + 92))) == 11)
                sub_80040D64(a1);
            if (!r_u8((uint32)((a1 + 96))))
                goto LABEL_342;
            v49 = (uint32)a1;
            if (r_u32((uint32)((a1 + 200))))
                v50 = 39;
            else
                v50 = 0;
            goto LABEL_341;
        case 0x19:
            v88 = r_u32((uint32)((a1 + 200)));
            w_u8((uint32)((a1 + 244)), 0);
            if (!v88)
            {
                sub_800522D0(a1);
                if (r_u16((uint32)((a1 + 92))) >= 0xBu)
                    sub_800410B8(a1);
            }
            v49 = (uint32)a1;
            if (!r_u8((uint32)((a1 + 96))))
                goto LABEL_342;
            v50 = 45;
            goto LABEL_341;
        case 0x1A:
            w_u16((uint32)((r_u32((uint32)((a1 + 60))) + 144)), 1);
            v49 = (uint32)a1;
            if (!r_u32((uint32)((a1 + 200))))
            {
                v50 = 0;
                goto LABEL_341;
            }
            v89 = r_u16((uint32)((a1 + 226)));
            v50 = 46;
            if ((v89 & 0xF000) != 0)
                goto LABEL_341;
            v49 = (uint32)a1;
            if ((v89 & 0x80) == 0)
                goto LABEL_342;
            v50 = 47;
            w_u16((uint32)((a1 + 228)), r_u16((uint32)((a1 + 228))) | (0x80u));
            goto LABEL_341;
        case 0x1B:
            w_u16((uint32)((r_u32((uint32)((a1 + 60))) + 144)), 1);
            v49 = (uint32)a1;
            if (r_u32((uint32)((a1 + 200))))
            {
                v69 = sub_800524AC(a1);
                v49 = (uint32)a1;
                if (v69 != 1)
                {
                LABEL_202:
                    v64 = r_u16((uint32)((a1 + 18)));
                    v65 = (v69 + r_u16((uint32)((a1 + 270)))) & 0xFFF;
                LABEL_203:
                    w_u16((uint32)((a1 + 18)), sub_80051EB8(v64, v65));
                    goto LABEL_342;
                }
                v50 = 45;
            }
            else
            {
                v50 = 0;
            }
        LABEL_341:
            sub_800513CC(v49, v50);
            goto LABEL_342;
        case 0x1C:
            v90 = r_u8((uint32)((a1 + 96)));
            w_u16((uint32)((a1 + 242)), 1);
            if (!v90)
                goto LABEL_342;
            w_u32((uint32)((a1 + 200)), 0);
            v49 = (uint32)a1;
            v50 = 0;
            goto LABEL_341;
        case 0x1D:
            w_u8((uint32)((a1 + 244)), 0);
            (w_u16((uint32)(0x800718F8u), r_u16((uint32)(0x800718F8u)) + 1u), r_u16((uint32)(0x800718F8u)));
            v49 = (uint32)a1;
            if (r_u16((uint32)(0x800718F8u)) != 120)
                goto LABEL_342;
            v50 = 0;
            w_u16((uint32)(0x8007199Cu), 0);
            w_u8((uint32)(0x80071544u), 0);
            goto LABEL_341;
        case 0x1E:
            v120 = (sint16)r_u16((uint32)((a1 + 92)));
            v121 = v120;
            if (v120 == 1)
            {
                w_u16((uint32)((a1 + 284)), sub_8004496C());
                sub_8004486C(1, r_u16((uint32)((a1 + 284))), 30, 1200, 32000, 512);
            }
            if (v120 >= 32)
                v121 = 31;
            v122 = 31 - v121;
            v123 = (31 - v121) << 16;
            if ((r_u16((uint32)(0x800719D0u)) & 3) == 0)
            {
                w_u16((uint32)(0x8007155Cu), 8 * v122);
                w_u16((uint32)(0x8007156Cu), 8 * v122);
                w_u16((uint32)(0x8007158Cu), 4 * v122);
                w_u16((uint32)(0x80071A50u), 32);
                v123 = v122 << 16;
            }
            if (v123 && (r_u16((uint32)(0x800719D0u)) & 1) != 0)
                w_u16((uint32)((a1 + 272)), v122 | ((uint16)v122 << 10) | (32 * v122));
            v124 = r_u16((uint32)((a1 + 214)));
            w_u8((uint32)(0x80071690u), r_u8((uint32)(0x80071690u)) | (1u));
            w_u8((uint32)((a1 + 244)), 0);
            if (v124 != 35)
                sub_80052078(a1, 768, 10000);
            if (!r_u8((uint32)((a1 + 96))))
                goto LABEL_342;
            v125 = r_u16((uint32)((a1 + 284)));
            if (v125 != 0xFFFF)
            {
                sub_800449A0(v125);
                sub_8004486C(4, r_u16((uint32)((a1 + 284))), 0, 0, 0, 0);
                w_u16((uint32)((a1 + 284)), -1);
            }
            v49 = (uint32)a1;
            v50 = 0;
            goto LABEL_341;
        default:
            goto LABEL_342;
    }
}

uint32 sub_8004591C(uint32 a1, uint32 a2, uint32 a3)
{
    FUNCTION_MARKER(0x8004591Cu, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

    sint32 result;
    uint32 v6;
    uint32 v7;
    uint32 v8;
    sint32 v9;
    sint32 v10;
    sint32 v11;
    sint32 v12;
    sint32 v13;
    uint16 v14;
    sint32 v15;
    sint32 v16;
    sint32 v17;
    sint32 v18;
    sint32 v19;
    sint32 v20;
    sint32 v21;
    sint32 v22;
    sint32 v23;
    uint32 v24;
    sint32 v25;
    uint32 v26;
    uint32 v27;
    sint32 v28;
    sint32 v29;
    sint32 v30;
    sint16 v31;
    uint32 v32;
    sint32 v33;
    sint32 v34;
    sint32 v35;
    uint16 v36;
    uint16 v37;
    sint32 v38;

    result = sub_8004E0A0(a1);
    if (result < 0)
        return result;
    sub_8004DD18(-2147018636, 4);
    sub_8004DD18(-2147018628, 4);
    sub_8004DD18(-2147018632, 4);
    sub_8004DD18(-2147018624, 4);
    sub_8004DD18(0x80071598u, 4);
    sub_8004DD18(0x800715B0u, 4);
    sub_8004DD18(-2147018652, 4);
    sub_8004DD18(-2147018620, 4);
    sub_8004DD18(draft_local_address(&v36, sizeof(v36)), 2);
    v38 = 12 * v36;
    w_u32((uint32)(0x80071934u), sub_80011A98(v38));
    sub_8004DD18(r_u32((uint32)(0x80071934u)), v38);
    sub_8004DD18(draft_local_address(&v37, sizeof(v37)), 2);
    v38 = 14 * v37;
    w_u32((uint32)(0x80071704u), (sint32)sub_80011A98(v38));
    sub_8004DD18(r_u32((uint32)(0x80071704u)), v38);
    v38 = 4 * r_u32((uint32)(0x80071598u)) * r_u32((uint32)(0x800715B0u));
    w_u32((uint32)(0x800718D0u), sub_80011A98(v38));
    sub_8004DD18(r_u32((uint32)(0x800718D0u)), v38);
    sub_8004DD18(draft_local_address(&v38, sizeof(v38)), 4);
    v38 *= 2;
    w_u32((uint32)(0x80071714u), (sint32)sub_80011A98(v38));
    sub_8004DD18(r_u32((uint32)(0x80071714u)), v38);
    sub_8004DD18(0x80071728u, 2);
    w_u32((uint32)(0x800718E4u), sub_80011A98(8 * (uint16)r_u16((uint32)(0x80071728u))));
    w_u32((uint32)(0x80071954u), sub_80011A98(8 * (uint16)r_u16((uint32)(0x80071728u))));
    v6 = sub_80011A98(8 * (uint16)r_u16((uint32)(0x80071728u)));
    v7 = sub_80011A98(8 * (uint16)r_u16((uint32)(0x80071728u)));
    v8 = v6;
    if (a2)
    {
        v9 = (uint16)r_u16((uint32)(0x80071728u));
        v10 = 0;
        if (r_u16((uint32)(0x80071728u)))
        {
            v8 = 0;
            do
            {
                sub_8004DD18((v6 + 4u * (2 * (v9 - ((uint32)v8 + 1)))), 8);
                ++v10;
                v9 = (uint16)r_u16((uint32)(0x80071728u));
                v8 = (uint32)(uint16)v10;
            } while ((uint16)v10 < (uint32)(uint16)r_u16((uint32)(0x80071728u)));
            v9 = (uint16)r_u16((uint32)(0x80071728u));
        }
        v11 = 0;
        if (v9)
        {
            v8 = 0;
            do
            {
                sub_8004DD18((v7 + 4u * (2 * (v9 - ((uint32)v8 + 1)))), 8);
                ++v11;
                v9 = (uint16)r_u16((uint32)(0x80071728u));
                v8 = (uint32)(uint16)v11;
            } while ((uint16)v11 < (uint32)(uint16)r_u16((uint32)(0x80071728u)));
        }
    }
    else
    {
        sub_8004DD18(v6, 8 * (uint16)r_u16((uint32)(0x80071728u)));
        sub_8004DD18(v7, 8 * (uint16)r_u16((uint32)(0x80071728u)));
    }
    nullsub_2();
    if (!a2)
        goto LABEL_15;
    v12 = 0;
    if (v37)
    {
        v13 = 0;
        do
        {
            ++v12;
            w_u8((uint32)((14 * v13 + r_u32((uint32)(0x80071704u)) + 9)), r_u16((uint32)(0x80071728u)) - (r_u8((uint32)((14 * v13 + r_u32((uint32)(0x80071704u)) + 9))) + 1));
            v13 = (uint16)v12;
        } while ((uint16)v12 < (uint32)v37);
    LABEL_15:
        v14 = 0;
        if (v37)
        {
            v15 = 0;
            do
            {
                v16 = 14 * v15 + r_u32((uint32)(0x80071704u));
                v17 = r_u8((uint32)((v16 + 9))) - a3;
                if (v17 >= (uint16)r_u16((uint32)(0x80071728u)))
                    v17 -= (uint16)r_u16((uint32)(0x80071728u));
                ++v14;
                if (v17 < 0)
                    v17 = (uint8)(v17 + r_u16((uint32)(0x80071728u)));
                w_u8((uint32)((v16 + 9)), v17);
                v15 = v14;
            } while (v14 < (uint32)v37);
        }
    }
    v18 = (uint16)r_u16((uint32)(0x80071728u));
    v19 = 0;
    if (r_u16((uint32)(0x80071728u)))
    {
        v20 = 0;
        do
        {
            v21 = v20 + a3;
            if (v21 >= v18)
                v21 -= v18;
            v22 = 8 * v20;
            if (v21 < 0)
                v21 += v18;
            v23 = 2 * v21;
            ++v19;
            v24 = (uint32)(v22 + r_u32((uint32)(0x800718E4u)));
            v25 = r_u32((uint32)(v6 + 4u * (v23 + 1)));
            w_u32((uint32)(v24), r_u32((uint32)(v6 + 4u * (v23))));
            w_u32((uint32)(v24 + 4u * (1)), v25);
            v26 = (v7 + 4u * (v23));
            v27 = (uint32)(v22 + r_u32((uint32)(0x80071954u)));
            v28 = r_u32((uint32)(v26 + 4u * (1)));
            w_u32((uint32)(v27), r_u32((uint32)(v26)));
            w_u32((uint32)(v27 + 4u * (1)), v28);
            v18 = (uint16)r_u16((uint32)(0x80071728u));
            v20 = (uint16)v19;
        } while ((uint16)v19 < (uint32)(uint16)r_u16((uint32)(0x80071728u)));
    }
    sub_80011AF8((sint32)v6);
    sub_80011AF8((sint32)v7);
    w_u32((uint32)(0x800716D0u), (sint32)sub_80011A98(2 * (uint16)r_u16((uint32)(0x80071728u))));
    v29 = 0;
    if (r_u16((uint32)(0x80071728u)))
    {
        v30 = 0;
        do
        {
            v31 = sub_80045788(v30);
            v32 = (uint16)r_u16((uint32)(0x80071728u));
            ++v29;
            w_u16((uint32)((2 * v30 + r_u32((uint32)(0x800716D0u)))), v31);
            v30 = (uint16)v29;
        } while ((uint16)v29 < v32);
    }
    result = v37;
    v33 = 0;
    if (v37)
    {
        v34 = 0;
        do
        {
            v35 = 14 * v34 + r_u32((uint32)(0x80071704u));
            if ((uint32)r_u8((uint32)((v35 + 8))) - 1 >= 2)
            {
                if (!r_u8((uint32)((v35 + 9))))
                {
                    w_u8((uint32)((v35 + 8)), 2);
                    w_u16((uint32)((v35 + 12)), r_u16((uint32)(r_u32((uint32)(0x800716D0u)))));
                }
                if (r_u8((uint32)((v35 + 9))) == (uint16)r_u16((uint32)(0x80071728u)) - 1)
                {
                    w_u8((uint32)((v35 + 8)), 2);
                    w_u16((uint32)((v35 + 12)), (r_u16((uint32)((2 * (unsigned __int16)r_u16((uint32)(0x80071728u)) + r_u32((uint32)(0x800716D0u)) - 4))) + 2048) & 0xFFF);
                }
            }
            result = (uint16)++v33 < (uint32)v37;
            v34 = (uint16)v33;
        } while ((uint16)v33 < (uint32)v37);
    }
    return result;
}

uint32 sub_80056C28(void)
{
    FUNCTION_MARKER(0x80056C28u, "SLES_007.30");
    /* TODO: Resolve remaining signed wrapping, local aggregate layout and caller argument gaps during integration */

    sint32 v0;
    uint32 v1;
    sint32 i;
    sint32 v3;
    sint32 v4;
    sint32 v5;
    sint32 v6;
    uint32 v7;
    sint32 v8;
    sint32 v9;
    sint32 v10;
    uint32 v11;
    sint32 j;
    sint32 v13;
    sint32 v14;
    sint32 v15;
    sint32 v16;
    uint32 v17;
    sint32 v18;
    sint32 v19;
    sint32 v20;
    sint32 v21;
    sint32 v22;
    sint32 v23;
    /* GP resolves to 0x80071474 */
    sint32 v25;
    sint32 v26;
    sint32 v27;
    uint32 v28;
    sint8 v29;
    uint32 v30;
    sint32 v31;
    sint32 v32;
    sint32 v33;
    uint32 v34;
    sint8 v35;
    sint16 v36;
    sint8 v37;
    sint16 v38;
    sint8 v39;
    sint16 v40;
    sint8 v41;
    sint16 v42;
    sint32 v43;
    sint32 v44;
    sint32 result;

    w_u8((uint32)(0x80071690u), 0);
    v0 = sub_800119DC(288);
    v1 = (uint32)v0;
    for (i = -2146763072; i != -2146762784; i += 16)
    {
        v3 = r_u32((uint32)((i + 4)));
        v4 = r_u32((uint32)((i + 8)));
        v5 = r_u32((uint32)((i + 12)));
        w_u32((uint32)(v1), r_u32((uint32)(i)));
        w_u32((uint32)(v1 + 4u * (1)), v3);
        w_u32((uint32)(v1 + 4u * (2)), v4);
        w_u32((uint32)(v1 + 4u * (3)), v5);
        v1 += 4u * (4);
    }
    sub_80054454(v0, 0);
    v6 = -2146763072;
    v7 = (uint32)v0;
    do
    {
        v8 = r_u32((uint32)(v7 + 4u * (1)));
        v9 = r_u32((uint32)(v7 + 4u * (2)));
        v10 = r_u32((uint32)(v7 + 4u * (3)));
        w_u32((uint32)(v6), r_u32((uint32)(v7)));
        w_u32((uint32)((v6 + 4)), v8);
        w_u32((uint32)((v6 + 8)), v9);
        w_u32((uint32)((v6 + 12)), v10);
        v7 += 4u * (4);
        v6 += 16;
    } while (v7 != (uint32)(v0 + 288));
    v11 = (uint32)v0;
    if (r_u8((uint32)((v0 + 240))))
        w_u32((uint32)(0x80071614u), -2146763072);
    for (j = -2146762784; j != -2146762496; j += 16)
    {
        v13 = r_u32((uint32)((j + 4)));
        v14 = r_u32((uint32)((j + 8)));
        v15 = r_u32((uint32)((j + 12)));
        w_u32((uint32)(v11), r_u32((uint32)(j)));
        w_u32((uint32)(v11 + 4u * (1)), v13);
        w_u32((uint32)(v11 + 4u * (2)), v14);
        w_u32((uint32)(v11 + 4u * (3)), v15);
        v11 += 4u * (4);
    }
    sub_80054454(v0, 1u);
    v16 = -2146762784;
    v17 = (uint32)v0;
    do
    {
        v18 = r_u32((uint32)(v17 + 4u * (1)));
        v19 = r_u32((uint32)(v17 + 4u * (2)));
        v20 = r_u32((uint32)(v17 + 4u * (3)));
        w_u32((uint32)(v16), r_u32((uint32)(v17)));
        w_u32((uint32)((v16 + 4)), v18);
        w_u32((uint32)((v16 + 8)), v19);
        w_u32((uint32)((v16 + 12)), v20);
        v17 += 4u * (4);
        v16 += 16;
    } while (v17 != (uint32)(v0 + 288));
    v21 = 0;
    if (r_u8((uint32)((v0 + 240))))
        w_u32((uint32)(0x80071614u), -2146762784);
    sub_80011A70(288);
    v22 = 0;
    do
    {
        v23 = 288 * v22 - 2146763072;
        if (r_u8((uint32)((v23 + 240))))
        {
            sub_80046278(r_u16((uint32)((v23 + 266))));
            if (r_u8((uint32)((v23 + 212))) == 1)
            {
                v25 = r_u32((uint32)((r_u32((uint32)(r_u32((uint32)((v23 + 52))))) + 180)));
                w_u32((uint32)((0x80071474u + 920)), v25);
                w_u32((uint32)((0x80071474u + 1088)), v25);
            }
            if (r_u16((uint32)((v23 + 274))))
            {
                v26 = (r_u16((uint32)(0x800719D0u)) >> 1) & 1;
                (w_u16((uint32)((v23 + 274)), r_u16((uint32)((v23 + 274))) - 1u), r_u16((uint32)((v23 + 274))));
                if (v26)
                {
                    v27 = 16;
                    v28 = r_u32((uint32)((v23 + 52)));
                    v29 = 0;
                }
                else
                {
                    v27 = 192;
                    v28 = r_u32((uint32)((v23 + 52)));
                    v29 = 32;
                }
                sub_8001A7A8(r_u32((uint32)(v28)), v27, v29, 0);
                sub_800540C0(v23);
            }
            else
            {
                if ((r_u16((uint32)((v23 + 278))) & 1) == 0)
                {
                    if (r_u16((uint32)((v23 + 272))))
                        sub_8001A7A8(r_u32((uint32)(r_u32((uint32)((v23 + 52))))), (r_u16((uint32)((v23 + 272))) >> 7) & 0xF8, (r_u16((uint32)((v23 + 272))) >> 2) & 0xF8, 8 * (r_u8((uint32)((v23 + 272))) & 0x1F));
                    else
                        sub_8001DEB0(r_u32((uint32)(r_u32((uint32)((v23 + 52))))));
                }
                sub_80032A20((uint32)(v23 + 136));
                if (r_u16((uint32)((v23 + 246))) == 8 && (r_u16((uint32)(0x800719D0u)) & 3) == 0)
                {
                    v30 = r_u32((uint32)(r_u32((uint32)((v23 + 52)))));
                    v31 = r_u32((uint32)(v30 + 4u * (381)));
                    v32 = r_u32((uint32)(v30 + 4u * (382)));
                    v33 = r_u32((uint32)(v30 + 4u * (383)));
                    w_u32((uint32)(0x1F800028u), r_u32((uint32)(v30 + 4u * (380))));
                    w_u32((uint32)(0x1F800034u), v33);
                    w_u32((uint32)(0x1F800028u), r_u32((uint32)(0x1F800028u)) - (127));
                    w_u32((uint32)(0x1F80002Cu), v31 - 127);
                    w_u32((uint32)(0x1F800030u), v32 - 127);
                    w_u32((uint32)(0x1F800028u), r_u32((uint32)(0x1F800028u)) + ((uint8)sub_80011B8C()));
                    w_u32((uint32)(0x1F80002Cu), r_u32((uint32)(0x1F80002Cu)) + ((uint8)sub_80011B8C()));
                    w_u32((uint32)(0x1F800030u), r_u32((uint32)(0x1F800030u)) + ((uint8)sub_80011B8C()));
                    v34 = sub_80011B8C() & 3;
                    if (v34 == 1)
                    {
                        v38 = sub_80011B8C() & 1 | 4;
                        v37 = sub_80011B8C();
                        sub_80029DD4((uint32)0x1F800028, -20, 4, v38, v37 & 1, 128, 96, 64);
                    }
                    else if (v34 >= 2)
                    {
                        if (v34 == 2)
                        {
                            v40 = sub_80011B8C() & 1 | 4;
                            v39 = sub_80011B8C();
                            sub_80029DD4((uint32)0x1F800028, -20, 4, v40, v39 & 1, 64, 128, 96);
                        }
                        else
                        {
                            v42 = sub_80011B8C() & 1 | 4;
                            v41 = sub_80011B8C();
                            sub_80029DD4((uint32)0x1F800028, -20, 4, v42, v41 & 1, 96, 128, 64);
                        }
                    }
                    else
                    {
                        v36 = sub_80011B8C() & 1 | 4;
                        v35 = sub_80011B8C();
                        sub_80029DD4((uint32)0x1F800028, -20, 4, v36, v35 & 1, 64, 96, 128);
                    }
                }
            }
            v43 = r_u16((uint32)((v23 + 98)));
            if (v43 != 0xFFFF)
            {
                v44 = 168 * r_u16((uint32)((v23 + 102))) + r_u32((uint32)(r_u32((uint32)((v23 + 52)))));
                sub_8003133C(v43, (uint32)(v44 + 8), r_u16((uint32)((v23 + 100))), (uint32)(v44 + 32));
            }
            if (r_u8((uint32)((v23 + 212))) == 1)
                sub_800542D4(v23);
        }
        result = (uint16)++v21 < 2u;
        v22 = (uint16)v21;
    } while ((uint16)v21 < 2u);
    return result;
}
