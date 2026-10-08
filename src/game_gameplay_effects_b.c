#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

static void effects_copy_vector(uint32 source,uint32 destination)
{
    uint32 words[4],i;
    for(i=0u;i<4u;++i)words[i]=r_u32(source+4u*i);
    for(i=0u;i<4u;++i)w_u32(destination+4u*i,words[i]);
}

uint32 sub_8004E520(uint32 position,uint32 height)
{
    uint32 count=r_u16(0x800717C0u),destination;
    if(count==8u)return 8u;
    w_u16(0x800717C0u,count+1u);destination=r_u32(0x80071A3Cu)+16u*count;
    w_u32(destination,r_u32(position));w_u32(destination+4u,height&0xFFFFu);w_u32(destination+8u,r_u32(position+8u));
    return height&0xFFFFu;
}

uint32 sub_800271A4(uint32 position,uint32 kind,uint32 angle,uint32 color)
{
    static const uint16 settings[5][5]={{203,4,3,5,160},{207,3,3,5,160},{210,4,3,5,160},{214,2,3,5,160},{216,6,5,5,180}};
    uint32 item=sub_80032EF0(),result,i;
    if(!item)return 19u;
    w_u32(item+8u,19u);effects_copy_vector(position,item+12u);
    result=sub_80046D0C((uint32)(sint32)(sint16)(angle+r_u16(0x800BBFD6u)))<<16;
    w_u16(item+42u,(sint32)result>0 ? 0u : 1u);
    w_u16(item+32u,0u);w_u16(item+44u,0u);
    if(color) {
        w_u16(item+44u,1u);w_u16(item+46u,color&255u);
        w_u16(item+48u,(color>>8)&255u);w_u16(item+50u,(color>>16)&255u);
    }
    kind&=0xFFFFu;if(kind>=5u)return 0u;
    for(i=0u;i<5u;++i)w_u16(item+(i<2u ? 28u+2u*i : 30u+2u*i),settings[kind][i]);
    w_u16(item+40u,2u);return kind==3u ? 160u : 2u;
}

uint32 sub_80022DD4(uint32 position,uint32 velocity,uint32 size,uint32 count,uint32 a5,uint32 a6,uint32 a7)
{
    uint32 item=sub_80032EF0(),value,result;
    if(!item)return 0u;
    w_u32(item+8u,0u);effects_copy_vector(position,item+12u);
    w_u32(item+12u,r_u32(item+12u)+(uint32)((sint32)r_u32(velocity)>>1));
    w_u32(item+20u,r_u32(item+20u)+(uint32)((sint32)r_u32(velocity+8u)>>1));
    effects_copy_vector(velocity,item+28u);
    w_u16(item+48u,size);w_u16(item+50u,count-1u);w_u16(item+52u,a5);w_u16(item+54u,a6);w_u16(item+56u,a7);
    w_u16(item+46u,0u);w_u16(item+44u,0u);
    value=r_u32(item+28u);w_u32(item+28u,value-(uint32)((sint32)value>>3));
    value=r_u32(item+36u);w_u32(item+36u,value-(uint32)((sint32)value>>3));
    result=r_u32(item+32u)-20u;w_u32(item+32u,result);return result;
}

uint32 sub_80022C40(uint32 a1,uint32 a2,uint32 a3,uint32 a4,uint32 a5,uint32 a6,uint32 a7,uint32 a8,uint32 a9)
{
    w_u8(0x800715E4u,0u);w_u32(0x80071994u,a1);w_u32(0x800719F8u,a2);
    w_u32(0x800BF2B0u,a3);w_u32(0x800BF2B4u,a4);w_u16(0x800718E0u,0u);w_u8(0x800719B4u,1u);
    w_u32(0x800BF2B8u,a5);w_u32(0x800AEEC8u,a6);w_u32(0x800AEECCu,a7);w_u32(0x800AEED0u,a8);w_u16(0x800718ACu,a9);
    return 1u;
}

uint32 sub_80023DF0(uint32 position)
{
    uint32 item=sub_80032EF0();if(!item)return 32u;
    w_u32(item+8u,32u);w_u32(item+44u,0u);w_u16(item+48u,100u);w_u16(item+50u,0u);
    effects_copy_vector(position,item+12u);effects_copy_vector(item+12u,item+28u);
    w_u16(item+120u,0xFFFFu);w_u16(item+122u,0u);return 0xFFFFu;
}

uint32 sub_800322A4(uint32 record)
{
    uint32 i,player,band;sint32 distance;
    for(i=0u;i<2u;++i) {
        player=0x800AFEC0u+288u*i;if(!r_u8(player+240u))continue;
        distance=(sint32)r_u32(record+16u+4u*i);
        band=distance<3000 ? 0u : distance<6000 ? 1u : distance<12000 ? 2u : 3u;
        w_u16(player+234u,r_u16(player+234u)|(1u<<(band|8u)));
    }
    return 0u;
}
