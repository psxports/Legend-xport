#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

/* FILE.DAT entry 11 owns the text table and credits renderer */
extern uint32 sub_8005EEB8(uint32,uint32,uint32,uint32,uint32);
extern void sub_8005E4D0(uint32,uint32),sub_8005DFE4(uint32),sub_8005B278(uint32);
extern void sub_8005E814(uint32),sub_8005E648(uint32),sub_8005E5D8(uint32);

static uint32 credits_packet(uint32 upper)
{
    uint32 packet=r_u32(0x80071680u),i,ordering=r_u32(0x8007184Cu);
    w_u32(0x80071680u,packet+40u);
    w_u8(packet+3u,8);w_u8(packet+7u,58);
    for(i=0;i<4u;++i) {
        uint32 color=((i<2u)==(upper!=0u))?255u:0u;
        w_u8(packet+4u+8u*i,color);w_u8(packet+5u+8u*i,color);w_u8(packet+6u+8u*i,color);
        w_u16(packet+8u+8u*i,(i&1u)?384u:0u);
        w_u16(packet+10u+8u*i,upper?((i<2u)?0u:64u):((i<2u)?192u:256u));
    }
    w_u32(packet,(r_u32(packet)&0xFF000000u)|(r_u32(ordering)&0xFFFFFFu));
    w_u32(ordering,(r_u32(ordering)&0xFF000000u)|(packet&0xFFFFFFu));
    return packet;
}

uint32 sub_800CB02C(void)
{
    uint32 scroll=256u,index,packet,ordering;
    sub_80014848();sub_80014F0C(17,0,1000);sub_800129E8();sub_80044800();
    w_u16(0x8007194Cu,254);w_u16(0x800717A4u,0xFFC0u);
    w_u16(0x800719D0u,0);w_u16(0x800715E8u,0);w_u16(0x800716FCu,2);
    sub_80013B64(1,0,0,0);sub_800451B8(240,0,240,0);sub_80013FE8(9,230,0xFFFFu);
    while((sint16)r_u16(0x8007194Cu)!=255 || (sint16)r_u16(0x800717A4u)!=0) {
        uint32 y=scroll;
        sub_80011BB8();sub_800139C0();sub_8005E4D0(r_u32(0x8007184Cu),2500);
        for(index=0;index<85u;++index,y+=16u) {
            if((uint16)(y+16u)<273u) {
                uint32 string=r_u32(0x800CB50Cu+4u*index);
                sint32 shade=(sint16)(r_u8(string)+0xFFD0u);
                sint32 width;
                shade=(sint16)((uint32)shade*64u+80u);
                ++string;width=(sint32)sub_8004ED48(string);
                sub_8004EEFC((uint32)(sint32)(sint16)(192-(width>>1)),(uint32)(sint32)(sint16)y,
                    string,(uint32)shade,(uint32)shade,(uint32)shade,2);
            }
        }
        if(!(r_u16(0x800719D0u)&3u))--scroll;
        if((r_u16(0x80071790u)&0x800u) && !r_u16(0x800717A4u)) {
            w_u16(0x800717A4u,8);sub_800451B8(0x8000u,0xFFFFFFF8u,0x8000u,0);
        }
        if((sint16)scroll < -1424 && !r_u16(0x800717A4u)) {
            w_u16(0x800717A4u,8);sub_800451B8(0x8000u,0xFFFFFFF8u,0x8000u,0);
        }
        credits_packet(1);credits_packet(0);
        packet=r_u32(0x80071680u);w_u32(0x80071680u,packet+40u);
        sub_8005EEB8(packet,1,1,r_u16(0x80071784u),0);
        ordering=r_u32(0x8007184Cu);
        w_u32(packet,(r_u32(packet)&0xFF000000u)|(r_u32(ordering)&0xFFFFFFu));
        w_u32(ordering,(r_u32(ordering)&0xFF000000u)|(packet&0xFFFFFFu));
        sub_8002F36C();sub_800140DC();sub_8005DFE4(0);sub_80045048(0);sub_8005B278(0);
        sub_8005E814(r_u32(0x800719D4u));sub_8005E648(r_u32(0x800719CCu));
        sub_8005E5D8(r_u32(0x8007184Cu)+9996u);
        w_u16(0x800715E8u,r_u16(0x800715E8u)^1u);w_u16(0x800719D0u,r_u16(0x800719D0u)+1u);
    }
    sub_80013B64(0,0,0,0);sub_80013974();return sub_80013F80();
}
