#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

/* Exact per-type constants and ordered collider attachments from 80024074 */
typedef struct SpawnConfig
{
    uint32 radius, height, range, speed, model, animation, behavior, count;

    struct
    {
        uint16 offset, mode;
    } bones[15];
} SpawnConfig;

static const SpawnConfig spawn_configs[27] = {
    {2000u, 600u, 6000u, 160u, 3u, 0x80069A84u, 0x80069A60u, 11u, {{168u, 0u}, {336u, 0u}, {504u, 0u}, {672u, 0u}, {840u, 0u}, {1008u, 0u}, {1176u, 0u}, {1680u, 0u}, {1848u, 0u}, {2016u, 0u}, {2184u, 0u}}},                                                       /* Type 0 */
    {2000u, 700u, 6000u, 160u, 4u, 0x80069A84u, 0x80069B20u, 11u, {{168u, 1u}, {336u, 1u}, {504u, 0u}, {672u, 1u}, {840u, 1u}, {1008u, 0u}, {1176u, 0u}, {1680u, 0u}, {1848u, 0u}, {2016u, 0u}, {2184u, 0u}}},                                                       /* Type 1 */
    {2000u, 1000u, 6000u, 160u, 5u, 0x80069A84u, 0x80069B44u, 11u, {{168u, 0u}, {336u, 0u}, {504u, 0u}, {672u, 0u}, {840u, 0u}, {1008u, 0u}, {1176u, 0u}, {1680u, 0u}, {1848u, 0u}, {2016u, 0u}, {2184u, 0u}}},                                                      /* Type 2 */
    {2000u, 1200u, 6000u, 160u, 7u, 0x80069A84u, 0x80069B68u, 11u, {{168u, 1u}, {336u, 1u}, {504u, 0u}, {672u, 0u}, {840u, 0u}, {1008u, 0u}, {1176u, 0u}, {1680u, 0u}, {1848u, 0u}, {2016u, 0u}, {2184u, 0u}}},                                                      /* Type 3 */
    {2000u, 800u, 6000u, 160u, 8u, 0x80069A84u, 0x80069B8Cu, 11u, {{168u, 1u}, {336u, 1u}, {504u, 1u}, {672u, 1u}, {840u, 1u}, {1008u, 1u}, {1176u, 1u}, {1680u, 1u}, {1848u, 1u}, {2016u, 1u}, {2184u, 1u}}},                                                       /* Type 4 */
    {2000u, 800u, 7000u, 160u, 9u, 0x80069A84u, 0x80069BB0u, 11u, {{168u, 1u}, {336u, 1u}, {504u, 0u}, {672u, 1u}, {840u, 1u}, {1008u, 0u}, {1176u, 0u}, {1680u, 0u}, {1848u, 0u}, {2016u, 0u}, {2184u, 0u}}},                                                       /* Type 5 */
    {2000u, 900u, 7000u, 160u, 10u, 0x80069A84u, 0x80069BD4u, 11u, {{168u, 2u}, {336u, 2u}, {504u, 2u}, {672u, 2u}, {840u, 2u}, {1008u, 1u}, {1176u, 1u}, {1680u, 2u}, {1848u, 2u}, {2016u, 2u}, {2184u, 2u}}},                                                      /* Type 6 */
    {2000u, 900u, 7000u, 160u, 11u, 0x80069A84u, 0x80069BF8u, 11u, {{168u, 0u}, {336u, 0u}, {504u, 0u}, {672u, 0u}, {840u, 0u}, {1008u, 0u}, {1176u, 0u}, {1680u, 0u}, {1848u, 0u}, {2016u, 0u}, {2184u, 0u}}},                                                      /* Type 7 */
    {2000u, 1200u, 7000u, 160u, 12u, 0x80069A84u, 0x80069CDCu, 11u, {{168u, 0u}, {336u, 0u}, {504u, 0u}, {672u, 0u}, {840u, 0u}, {1344u, 0u}, {1512u, 0u}, {2016u, 0u}, {2184u, 0u}, {2688u, 0u}, {2856u, 0u}}},                                                     /* Type 8 */
    {2000u, 900u, 7000u, 160u, 13u, 0x80069C1Cu, 0x80069CB8u, 11u, {{168u, 0u}, {336u, 0u}, {504u, 0u}, {672u, 0u}, {840u, 0u}, {1344u, 0u}, {1512u, 0u}, {2016u, 0u}, {2184u, 0u}, {2688u, 0u}, {2856u, 0u}}},                                                      /* Type 9 */
    {2000u, 800u, 7000u, 160u, 26u, 0x80069E8Cu, 0x80069F28u, 11u, {{168u, 0u}, {336u, 0u}, {504u, 0u}, {672u, 0u}, {840u, 0u}, {1008u, 0u}, {1176u, 0u}, {1680u, 0u}, {1848u, 0u}, {2016u, 0u}, {2184u, 0u}}},                                                      /* Type 10 */
    {2000u, 800u, 7000u, 160u, 26u, 0x80069E8Cu, 0x80069F4Cu, 11u, {{168u, 0u}, {336u, 0u}, {504u, 0u}, {672u, 0u}, {840u, 0u}, {1008u, 0u}, {1176u, 0u}, {1680u, 0u}, {1848u, 0u}, {2016u, 0u}, {2184u, 0u}}},                                                      /* Type 11 */
    {2000u, 1200u, 9000u, 160u, 26u, 0x80069E8Cu, 0x80069F70u, 11u, {{168u, 0u}, {336u, 0u}, {504u, 0u}, {672u, 0u}, {840u, 0u}, {1008u, 0u}, {1176u, 0u}, {1680u, 0u}, {1848u, 0u}, {2016u, 0u}, {2184u, 0u}}},                                                     /* Type 12 */
    {2000u, 600u, 6000u, 160u, 14u, 0x80069A84u, 0x80069D00u, 11u, {{168u, 1u}, {336u, 1u}, {504u, 0u}, {672u, 1u}, {840u, 1u}, {1008u, 0u}, {1176u, 0u}, {1680u, 0u}, {1848u, 0u}, {2016u, 0u}, {2184u, 0u}}},                                                      /* Type 13 */
    {2000u, 600u, 6000u, 160u, 15u, 0x80069A84u, 0x80069D24u, 11u, {{168u, 1u}, {336u, 1u}, {504u, 0u}, {672u, 1u}, {840u, 1u}, {1008u, 0u}, {1176u, 0u}, {1680u, 0u}, {1848u, 0u}, {2016u, 0u}, {2184u, 0u}}},                                                      /* Type 14 */
    {2000u, 1200u, 7000u, 160u, 16u, 0x80069A84u, 0x80069E68u, 2u, {{168u, 0u}, {336u, 0u}}},                                                                                                                                                                        /* Type 15 */
    {2000u, 800u, 6000u, 160u, 17u, 0x80069A84u, 0x80069D48u, 11u, {{168u, 0u}, {336u, 0u}, {504u, 0u}, {672u, 0u}, {840u, 0u}, {1008u, 0u}, {1176u, 0u}, {1680u, 0u}, {1848u, 0u}, {2016u, 0u}, {2184u, 0u}}},                                                      /* Type 16 */
    {2000u, 800u, 6000u, 160u, 18u, 0x80069A84u, 0x80069D6Cu, 11u, {{168u, 0u}, {336u, 0u}, {504u, 0u}, {672u, 0u}, {840u, 0u}, {1008u, 0u}, {1176u, 0u}, {1680u, 0u}, {1848u, 0u}, {2016u, 0u}, {2184u, 0u}}},                                                      /* Type 17 */
    {2000u, 600u, 6000u, 160u, 19u, 0x80069A84u, 0x80069D90u, 11u, {{168u, 0u}, {336u, 0u}, {504u, 0u}, {672u, 0u}, {840u, 0u}, {1008u, 0u}, {1176u, 0u}, {1680u, 0u}, {1848u, 0u}, {2016u, 0u}, {2184u, 0u}}},                                                      /* Type 18 */
    {2000u, 600u, 7000u, 160u, 20u, 0x80069A84u, 0x80069DB4u, 11u, {{168u, 0u}, {336u, 0u}, {504u, 0u}, {672u, 0u}, {840u, 0u}, {1008u, 0u}, {1176u, 0u}, {1680u, 0u}, {1848u, 0u}, {2016u, 0u}, {2184u, 0u}}},                                                      /* Type 19 */
    {2000u, 2000u, 9000u, 300u, 26u, 0x80069E8Cu, 0x80069F94u, 14u, {{168u, 0u}, {336u, 0u}, {504u, 0u}, {672u, 0u}, {840u, 0u}, {1008u, 0u}, {1176u, 0u}, {1344u, 0u}, {1848u, 0u}, {2016u, 0u}, {2184u, 0u}, {2352u, 0u}, {2520u, 0u}, {2688u, 0u}}},              /* Type 20 */
    {2000u, 1200u, 6000u, 160u, 22u, 0x80069A84u, 0x80069DD8u, 11u, {{168u, 1u}, {336u, 1u}, {504u, 0u}, {672u, 0u}, {840u, 0u}, {1008u, 0u}, {1176u, 0u}, {1680u, 0u}, {1848u, 0u}, {2016u, 0u}, {2184u, 0u}}},                                                     /* Type 21 */
    {2000u, 1200u, 7000u, 160u, 23u, 0x80069A84u, 0x80069DFCu, 12u, {{168u, 0u}, {336u, 0u}, {504u, 0u}, {672u, 0u}, {840u, 0u}, {1008u, 0u}, {1176u, 0u}, {1344u, 0u}, {1680u, 0u}, {1848u, 0u}, {2016u, 0u}, {2184u, 0u}}},                                        /* Type 22 */
    {2000u, 800u, 6000u, 160u, 24u, 0x80069A84u, 0x80069E44u, 11u, {{168u, 0u}, {336u, 0u}, {504u, 0u}, {672u, 0u}, {840u, 0u}, {1008u, 1u}, {1176u, 1u}, {1680u, 0u}, {1848u, 0u}, {2016u, 1u}, {2184u, 1u}}},                                                      /* Type 23 */
    {2000u, 700u, 6000u, 160u, 25u, 0x80069A84u, 0x80069E20u, 11u, {{168u, 0u}, {336u, 0u}, {504u, 0u}, {672u, 0u}, {840u, 0u}, {1008u, 0u}, {1176u, 0u}, {1680u, 0u}, {1848u, 0u}, {2016u, 0u}, {2184u, 0u}}},                                                      /* Type 24 */
    {2000u, 1200u, 9000u, 160u, 26u, 0x80069E8Cu, 0x80069FB8u, 11u, {{168u, 1u}, {336u, 1u}, {504u, 0u}, {672u, 1u}, {840u, 1u}, {1008u, 1u}, {1176u, 1u}, {1680u, 1u}, {1848u, 1u}, {2016u, 1u}, {2184u, 1u}}},                                                     /* Type 25 */
    {2000u, 1200u, 9000u, 160u, 27u, 0x80069E8Cu, 0x80069FDCu, 15u, {{168u, 0u}, {336u, 0u}, {504u, 0u}, {672u, 0u}, {840u, 0u}, {1008u, 0u}, {1176u, 0u}, {1680u, 0u}, {1848u, 0u}, {2016u, 0u}, {2184u, 0u}, {2688u, 0u}, {2856u, 0u}, {3024u, 0u}, {3192u, 0u}}}, /* Type 26 */
};

uint32 sub_80024074(uint32 x, uint32 z, uint32 kind, uint32 strength, uint32 slot)
{
    FUNCTION_MARKER(0x80024074u, "SLES_007.30");
    uint32 item, actor, collider, attack, model, entry_mode, type, facing = 1024u;
    uint32 state, index;
    kind = (uint16)kind;
    slot = (uint16)slot;
    if (r_u16(0x800715F0u))
        strength = 2u;
    if (r_u16(0x8007172Cu) == 3u || (slot != 1024u && r_u8(0x800C9D68u + slot)))
        return sub_80023E84((uint32)(sint32)(sint16)x, (uint32)(sint32)(sint16)z, kind, (uint16)strength, slot);
    item = sub_80032EF0();
    if (!item)
        return item;
    actor = item + 12u;
    w_u32(item + 8u, 13u);
    w_u16(0x8007172Cu, r_u16(0x8007172Cu) + 1u);
    sub_8002F0D4(actor, 252u);
    entry_mode = kind >> 7;
    type = kind & 127u;
    collider = sub_800471B4();
    w_u32(item + 20u, collider);
    w_u16(collider + 26u, 0u);
    w_u32(item + 28u, sub_800474F4());
    attack = sub_800474F4();
    w_u32(item + 24u, attack);
    w_u32(attack + 124u, r_u32(item + 28u));
    if (!r_u16(0x800719C8u))
    {
        strength = (uint16)strength >> 1;
        if (!strength)
            strength = 1u;
    }
    if (r_u8(0x800AFFB0u) && r_u8(0x800B00D0u))
    {
        strength += (uint16)strength / 3u;
        if ((uint16)strength >= 289u)
            strength = 288u;
    }
    w_u32(actor + 4u, 0u);
    w_u8(actor + 245u, 0u);
    w_u8(actor + 244u, 0u);
    if (type < 27u)
    {
        const SpawnConfig *config = &spawn_configs[type];
        w_u32(r_u32(actor + 8u) + 16u, config->radius);
        w_u32(r_u32(actor + 8u) + 20u, config->height);
        if (type == 20u)
            facing = 2048u;
        w_u16(actor + 234u, config->range);
        w_u16(actor + 76u, config->speed);
        w_u32(actor, sub_8001F150(config->model));
        for (index = 0u; index < config->count; ++index)
            sub_80047534(attack, r_u32(r_u32(actor)) + config->bones[index].offset, config->bones[index].mode);
        w_u16(actor + 80u, config->model);
        w_u32(actor + 36u, config->animation);
        w_u32(actor + 40u, config->behavior);
        if (type == 20u)
            w_u16(0x800717FCu, 0u);
        if (type == 2u || type == 20u)
            sub_80023F10(actor, type == 2u ? 6u : 21u, 2u, 0u, type == 2u ? (uint32)-250 : (uint32)-290, 0u);
        if (type == 10u || type == 11u || type == 12u || type == 25u || type == 26u)
            w_u16(0x800717FCu, 0u);
    }
    model = r_u32(r_u32(actor));
    if ((sint16)x < 0)
        x = 0u;
    if ((sint16)x >= (sint32)r_u16(0x80071728u))
        x = r_u16(0x80071728u) - 1u;
    w_u16(actor + 222u, type);
    w_u16(actor + 102u, 0xFFFFu);
    w_u32(actor + 72u, 0u);
    w_u16(actor + 78u, 0u);
    w_u32(actor + 68u, 0u);
    w_u16(actor + 236u, 0u);
    w_u16(actor + 226u, strength);
    w_u16(actor + 224u, strength);
    w_u16(actor + 232u, 0u);
    w_u32(actor + 44u, 0u);
    w_u32(actor + 84u, r_u32(r_u32(actor) + 4u));
    w_u16(model + 24u, 0u);
    w_u16(model + 28u, 0u);
    if (r_u16(actor + 222u) == 26u)
    {
        w_u16(model + 26u, 2048u);
        uint32 px = r_u32(0x800AFEB0u), py = r_u32(0x800AFEB4u), pz = r_u32(0x800AFEB8u);
        w_u32(model + 8u, px);
        w_u32(model + 12u, py);
        w_u32(model + 16u, pz);
        w_u32(model + 20u, r_u32(0x800AFEBCu));
    }
    else
    {
        uint32 heading = sub_8005129C((uint32)(sint32)(sint16)x, (uint32)(sint32)(sint16)z, model + 8u);
        w_u16(model + 26u, (facing + heading) & 4095u);
    }
    w_u16(actor + 212u, 0xFFFFu);
    w_u32(actor + 208u, 0u);
    w_u16(actor + 220u, 0u);
    w_u16(actor + 240u, slot);
    if (slot != 1024u)
        w_u8(0x800C9D68u + slot, 1u);
    if (entry_mode == 0u)
        return sub_800599B4(actor);
    if (entry_mode == 1u)
        return sub_8005915C(actor, 21u);
    if (entry_mode >= 2u && entry_mode <= 5u)
    {
        uint32 px = r_u32(model + 8u), py = r_u32(model + 12u);
        uint32 pz = r_u32(model + 16u), padding = r_u32(model + 20u);
        w_u32(actor + 20u, px);
        w_u32(actor + 24u, py);
        w_u32(actor + 28u, pz);
        w_u32(actor + 32u, padding);
        state = entry_mode == 2u ? 34u : 35u;
        if (entry_mode == 5u)
            w_u32(model + 12u, r_u32(model + 12u) - 6000u);
        else
        {
            w_u32(model + 8u, r_u32(model + 8u) + (uint32)(sint32)(sint16)r_u16(0x80071850u));
            w_u32(model + 12u, r_u32(model + 12u) + (uint32)(sint32)(sint16)r_u16(0x80071852u));
            w_u32(model + 16u, r_u32(model + 16u) + (uint32)(sint32)(sint16)r_u16(0x80071854u));
            if (entry_mode == 3u)
                w_u32(actor + 72u, (uint32)-4000);
            if (entry_mode == 4u)
                w_u32(actor + 72u, (uint32)-5500);
        }
        return sub_8005915C(actor, state);
    }
    return 640u;
}
