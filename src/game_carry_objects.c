#include "psx.h"
#include "game_draft_signatures.h"

static void carry_copy_position(uint32 output, uint32 input)
{
    uint32 x = r_u32(input), y = r_u32(input + 4), z = r_u32(input + 8), pad = r_u32(input + 12);
    w_u32(output, x);
    w_u32(output + 4, y);
    w_u32(output + 8, z);
    w_u32(output + 12, pad);
}

static void carry_follow_player(uint32 mesh, uint32 index)
{
    uint32 player = 0x800AFEC0 + 288 * index, first = r_u32(player + 16), second = r_u32(player + 20);
    w_u32(mesh + 24, first);
    w_u32(mesh + 28, second);
    w_u16(mesh + 26, (r_u16(mesh + 26) + 2048) & 4095);
    sub_80051208(index);
    carry_copy_position(mesh + 8, 0x1F800028);
}

void sub_80033700(uint32 node)
{
    uint32 mesh = r_u32(node + 12), motion = r_u32(node + 16), held = 0;
    uint32 state, region, contact, player, index, record, proximity[7], flash[4], local, height;
    if ((sint16)r_u16(motion + 28))
    {
        carry_copy_position(mesh + 8, motion);
        w_u16(node + 106, 0);
    }
    if (r_u32(r_u32(node + 24) + 128))
    {
        sub_8003368C(mesh);
        sub_800233BC(mesh + 8, mesh + 8, r_u16(node + 114) & 127, 24);
        sub_80044CC0(r_u32(mesh + 8), r_u32(mesh + 16));
        sub_80044DC8(r_u32(mesh + 8), r_u32(mesh + 16));
        sub_8003278C(1100);
        sub_80033638(node);
        sub_80032FD0(node);
        return;
    }
    record = draft_local_address(proximity, sizeof(proximity));
    sub_80051F74(mesh + 8, record);
    state = r_u16(node + 106);
    if (!state)
    {
        sub_80031088(mesh + 8, (uint32)(sint32)(sint16)r_u16(node + 110), (uint32)(sint32)(sint16)r_u16(node + 112));
        sub_80044CC0(r_u32(mesh + 8), r_u32(mesh + 16));
        sub_80044DC8(r_u32(mesh + 8), r_u32(mesh + 16));
        height = sub_80046324(r_u32(mesh + 8), r_u32(mesh + 16), node + 104);
        region = r_u16(node + 104);
        w_u32(node + 100, height);
        if (region != 0xFFFF)
            sub_80046A28(r_u32(0x80071704) + 14 * region, region, mesh + 8);
        sub_800325CC(node + 28, mesh + 8, r_u32(node + 100), 1);
        if ((sint16)r_u16(node + 34))
        {
            index = r_u8(r_u32(0x80071704) + 14 * r_u16(node + 104) + 9);
            w_u16(mesh + 26, (r_u16(r_u32(0x800716D0) + 2 * index) - 1024) & 4095);
            w_u16(node + 106, 1);
            w_u16(node + 112, 0);
        }
        contact = r_u32(node + 20);
        if (r_u32(contact + 128))
        {
            w_u32(contact + 128, 0);
            w_u32(node + 28, (uint32)-2000);
            w_u16(node + 112, (sint16)r_u16(node + 112) / 8);
            w_u16(node + 110, (r_u16(node + 110) + 2048) & 4095);
        }
        sub_8005178C(mesh + 8, 1000, mesh + 24, r_u16(node + 104), node + 36);
        if ((sint32)r_u32(node + 28) > 0)
        {
            w_u32(r_u32(node + 20) + 132, 32770);
            w_u16(r_u32(node + 20) + 136, r_u16(node + 110));
            w_u16(r_u32(node + 20) + 148, 80);
            sub_800475A8(r_u32(node + 20));
        }
    }
    else if (state == 1)
    {
        if ((uint16)sub_80032360(mesh + 8, record, 1600))
        {
            if ((r_u16(0x800719D0) & 15) < 8)
            {
                local = draft_local_address(flash, sizeof(flash));
                carry_copy_position(local, mesh + 8);
                w_u32(local + 4, r_u32(local + 4) - 1300);
                sub_80017C8C(local, 192, 0, 40000, 128);
            }
            index = (uint16)sub_80033170(mesh + 8, record, 1600);
            if (index)
            {
                held = 1;
                w_u32(0x800AFF88 + 288 * (index - 1), node);
                w_u16(node + 108, index - 1);
                w_u16(node + 106, 2);
            }
        }
    }
    else if (state == 2)
    {
        index = r_u16(node + 108);
        player = 0x800AFEC0 + 288 * index;
        if (!r_u32(player + 200))
        {
            w_u16(node + 106, 0);
            w_u32(node + 28, (uint32)-1000);
            w_u16(node + 112, 160);
            w_u16(node + 110, r_u16(player + 18));
            w_u16(r_u32(node + 20) + 138, index);
        }
        else
            carry_follow_player(mesh, index);
        held = 1;
    }
    if (held)
    {
        w_u16(r_u32(node + 16) + 28, 0);
        sub_80046278(r_u16(node + 104));
        sub_8001DEB0(mesh);
        return;
    }
    carry_copy_position(r_u32(node + 16), mesh + 8);
    w_u16(r_u32(node + 16) + 24, r_u16(mesh + 26));
    sub_800471E8(r_u32(node + 16));
    sub_800475F4(r_u32(node + 24));
    sub_80032A20(node + 36);
    if ((sint32)r_u32(record + 16 + 4 * r_u16(record + 24)) < 3000)
    {
        height = r_u32(node + 100);
        sub_80021288(r_u32(mesh + 8), r_u32(mesh + 16), height, (uint32)((sint32)(r_u32(mesh + 12) - height) >> 1) + height, 0);
    }
    if ((sint32)r_u32(record + 16 + 4 * r_u16(record + 24)) < 6000)
        sub_8004E520(mesh + 8, 2);
    sub_80030FE0(record);
    sub_80046278(r_u16(node + 104));
    sub_8001DEB0(mesh);
    if (!(r_u16(node + 114) & 128) && (uint16)legend_pickup_region_check(r_u16(node + 104), 15))
    {
        sub_80033638(node);
        sub_80032FD0(node);
    }
}

uint32 sub_80034D48(uint32 node)
{
    uint32 mesh = r_u32(node + 12), child = r_u32(node + 16), motion = r_u32(node + 20);
    uint32 state, region, contact, held = 0, player, index, record, proximity[7], flash[4], local, result;
    if ((sint16)r_u16(motion + 28))
    {
        carry_copy_position(mesh + 8, motion);
        w_u16(node + 110, 0);
    }
    if (r_u32(r_u32(node + 28) + 128))
    {
        sub_80044CC0(r_u32(mesh + 8), r_u32(mesh + 16));
        sub_80044DC8(r_u32(mesh + 8), r_u32(mesh + 16));
        sub_8003278C(1000);
        sub_800327F0(1000);
        w_u32(0x1F80002C, 5);
        w_u32(0x1F800028, 0);
        w_u32(0x1F800030, 0);
        sub_80022F08(mesh + 8, 0x1F800028, 5, 6, 3);
        sub_8004EC38(4);
        sub_80027F08(mesh, 4);
        sub_80027F08(child, 4);
        sub_800233BC(mesh + 8, mesh + 8, r_u16(node + 120) & 127, 24);
        sub_80034CE8(node);
        return sub_80032FD0(node);
    }
    record = draft_local_address(proximity, sizeof(proximity));
    sub_80051F74(mesh + 8, record);
    state = r_u16(node + 110);
    if (!state)
    {
        sub_80031088(mesh + 8, (uint32)(sint32)(sint16)r_u16(node + 116), (uint32)(sint32)(sint16)r_u16(node + 118));
        sub_80044CC0(r_u32(mesh + 8), r_u32(mesh + 16));
        sub_80044DC8(r_u32(mesh + 8), r_u32(mesh + 16));
        result = sub_80046324(r_u32(mesh + 8), r_u32(mesh + 16), node + 108);
        region = r_u16(node + 108);
        w_u32(node + 104, result);
        if (region != 0xFFFF)
            sub_80046A28(r_u32(0x80071704) + 14 * region, region, mesh + 8);
        sub_800325CC(node + 32, mesh + 8, r_u32(node + 104), 1);
        if ((sint16)r_u16(node + 38))
        {
            index = r_u8(r_u32(0x80071704) + 14 * r_u16(node + 108) + 9);
            w_u16(mesh + 26, (r_u16(r_u32(0x800716D0) + 2 * index) - 1024) & 4095);
            w_u16(node + 118, 0);
            w_u16(node + 110, 1);
        }
        contact = r_u32(node + 24);
        if (r_u32(contact + 128))
        {
            w_u32(contact + 128, 0);
            w_u32(node + 32, (uint32)-2000);
            w_u16(node + 118, (sint16)r_u16(node + 118) / 8);
            w_u16(node + 116, (r_u16(node + 116) + 2048) & 4095);
        }
        sub_8005178C(mesh + 8, 1300, mesh + 24, r_u16(node + 108), node + 40);
        if ((sint32)r_u32(node + 32) > 0)
        {
            w_u32(r_u32(node + 24) + 132, 32772);
            w_u16(r_u32(node + 24) + 136, r_u16(node + 116));
            w_u16(r_u32(node + 24) + 148, 80);
            sub_800475A8(r_u32(node + 24));
        }
    }
    else if (state == 1)
    {
        w_u16(child + 24, r_u16(0x80071808) << 6);
        if ((uint16)sub_80032360(mesh + 8, record, 1600))
        {
            if ((r_u16(0x800719D0) & 15) < 8)
            {
                local = draft_local_address(flash, sizeof(flash));
                carry_copy_position(local, mesh + 8);
                w_u32(local + 4, r_u32(local + 4) - 1200);
                sub_80017C8C(local, 192, 0, 40000, 128);
            }
            index = (uint16)sub_80033170(mesh + 8, record, 1600);
            if (index)
            {
                held = 1;
                w_u32(0x800AFF88 + 288 * (index - 1), node);
                w_u16(node + 114, index - 1);
                w_u16(node + 110, 2);
            }
        }
    }
    else if (state == 2)
    {
        w_u16(child + 24, r_u16(0x80071808) << 6);
        index = r_u16(node + 114);
        player = 0x800AFEC0 + 288 * index;
        if (!r_u32(player + 200))
        {
            w_u16(node + 110, 0);
            w_u32(node + 32, (uint32)-1000);
            w_u16(node + 116, r_u16(player + 18));
            w_u16(node + 118, r_u16(player + 214) == 42 ? 160 : 0);
            w_u16(r_u32(node + 24) + 138, index);
        }
        else
            carry_follow_player(mesh, index);
        held = 1;
    }
    if (held)
    {
        w_u16(r_u32(node + 20) + 28, 0);
        sub_80046278(r_u16(node + 108));
        return sub_8001C4B8(mesh);
    }
    carry_copy_position(r_u32(node + 20), mesh + 8);
    w_u16(r_u32(node + 20) + 24, r_u16(mesh + 26));
    sub_800471E8(r_u32(node + 20));
    sub_800475F4(r_u32(node + 28));
    sub_80032A20(node + 40);
    if ((sint32)r_u32(record + 16 + 4 * r_u16(record + 24)) < 3000)
    {
        result = r_u32(node + 104);
        sub_80021288(r_u32(mesh + 8), r_u32(mesh + 16), result, (uint32)((sint32)(r_u32(mesh + 12) - result) >> 1) + result, 0);
    }
    if ((sint32)r_u32(record + 16 + 4 * r_u16(record + 24)) < 6000)
        sub_8004E520(mesh + 8, 2);
    sub_80030FE0(record);
    sub_80046278(r_u16(node + 108));
    sub_8001C4B8(mesh);
    result = r_u16(node + 120) & 128;
    if (!result)
    {
        result = (uint16)legend_pickup_region_check(r_u16(node + 108), 15);
        if (result)
        {
            sub_80034CE8(node);
            return sub_80032FD0(node);
        }
    }
    return result;
}
