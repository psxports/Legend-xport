#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

extern uint32 sub_8005CDD8(uint32 matrix,uint32 input,uint32 output);

static uint32 collision_radius_reduction(uint32 collider)
{
    uint32 angle=(r_u16(collider+30u)-r_u16(collider+24u)+1024u)&4095u;
    uint32 factor,product,adjusted,sum;
    if(angle<1024u)factor=angle;
    else if(angle<2048u)factor=2048u-angle;
    else if(angle<3072u)factor=angle-2048u;
    else factor=4096u-angle;
    product=factor*r_u32(collider+20u);
    adjusted=(sint32)product<0 ? product+1023u : product;
    sum=(uint32)((sint32)adjusted>>10)+(uint32)((sint32)adjusted>>12);
    return (uint32)((sint32)sum>>1);
}

uint32 sub_80046D2C(uint32 first,uint32 second)
{
    uint32 height_first=r_u32(first+4u),height_second=r_u32(second+4u),difference,radius,distance,angle,penetration,dx,dz,result;
    if((sint32)height_first<(sint32)height_second) {
        difference=height_second-height_first;
        if((sint32)r_u32(second+16u)<(sint32)difference)return 1u;
    } else {
        difference=height_first-height_second;
        if((sint32)r_u32(first+16u)<(sint32)difference)return 1u;
    }
    radius=r_u32(first+20u)+r_u32(second+20u);
    distance=sub_80046570(r_u32(first)-r_u32(second),r_u32(first+8u)-r_u32(second+8u));
    if((sint32)radius<(sint32)distance)return 1u;
    angle=sub_80046B84(r_u32(second)-r_u32(first),r_u32(second+8u)-r_u32(first+8u),distance)&4095u;
    w_u16(first+30u,angle);w_u16(second+30u,(angle+2048u)&4095u);
    if(r_u16(first+26u)&1u)radius-=collision_radius_reduction(first);
    if(r_u16(second+26u)&1u)radius-=collision_radius_reduction(second);
    if(((r_u16(first+26u)|r_u16(second+26u))&1u) && (sint32)radius<(sint32)distance)return 1u;
    w_u16(second+28u,1u);w_u16(first+28u,1u);
    w_u16(0x1F800020u,0u);w_u16(0x1F800024u,0u);w_u16(0x1F800022u,r_u16(second+30u));
    sub_8005D138(0x1F800020u,0x1F800000u);
    penetration=(radius-distance)&0xFFFFu;
    if(penetration&0x8000u)penetration=0u;
    w_u16(0x1F800020u,0u);w_u16(0x1F800022u,0u);w_u16(0x1F800024u,penetration+8u);
    sub_8005CDD8(0x1F800000u,0x1F800020u,0x1F800028u);
    dx=r_u32(0x1F800028u);dz=r_u32(0x1F800030u);
    if((r_u16(first+26u)|r_u16(second+26u))&128u) {
        if(r_u16(second+26u)&128u) {
            w_u32(first,r_u32(first)+dx);result=r_u32(first+8u)+dz;w_u32(first+8u,result);
        } else {
            w_u32(second,r_u32(second)-dx);result=r_u32(second+8u)-dz;w_u32(second+8u,result);
        }
    } else {
        w_u32(first,r_u32(first)+(uint32)((sint32)dx>>1));
        w_u32(first+8u,r_u32(first+8u)+(uint32)((sint32)dz>>1));
        w_u32(second,r_u32(second)-(uint32)((sint32)dx>>1));
        result=(uint32)((sint32)dz>>1);w_u32(second+8u,r_u32(second+8u)-result);
    }
    return result;
}
