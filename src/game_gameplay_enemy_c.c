#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

/* Guest fields use the project address adapter, including borrowed local records */
#define E8(a) (*(uint8 *)psx_addr((uint32)(a), 1))
#define E16(a) (*(uint16 *)psx_addr((uint32)(a), 2))
#define E32(a) (*(uint32 *)psx_addr((uint32)(a), 4))
#define ES16(a) ((sint16)E16(a))
#define ES32(a) ((sint32)E32(a))

extern uint32 sub_8003FDCC(uint32, uint32);
extern uint32 sub_8003FC28(uint32);
extern uint32 sub_80040314(uint32);
extern uint32 sub_80040428(uint32);
extern uint32 sub_800404EC(uint32);
extern uint32 sub_80040A50(uint32);
extern uint32 sub_80041160(uint32);
extern uint32 sub_800411A0(uint32, uint32);
extern uint32 sub_8003F994(uint32);
extern uint32 sub_80051F74(uint32, uint32);
extern uint32 sub_80040ABC(uint32, uint32, uint32);
extern uint32 sub_80040C7C(uint32, uint32, uint32);
extern uint32 sub_80040E0C(uint32, uint32, uint32);
extern uint32 sub_80040FD0(uint32, uint32, uint32);
extern uint32 sub_80022DD4(uint32, uint32, uint32, uint32, uint32, uint32, uint32);
extern uint32 sub_80022C40(uint32, uint32, uint32, uint32, uint32, uint32, uint32, uint32, uint32);
extern uint32 sub_80022CC0(uint32, uint32, uint32, uint32);
extern uint32 sub_80022B24(uint32);
extern uint32 sub_80023DF0(uint32);
extern uint32 sub_80030FE0(uint32);
extern uint32 sub_800322A4(uint32);

static sint32 enemy_angle_distance(uint32 angle)
{
    sint32 distance = (sint16)sub_80046D0C((sint16)angle);
    return distance < 0 ? -distance : distance;
}

static void enemy_vector_copy(uint32 destination, uint32 source)
{
    uint32 x = E32(source), y = E32(source + 4), z = E32(source + 8), pad = E32(source + 12);
    E32(destination) = x; E32(destination + 4) = y;
    E32(destination + 8) = z; E32(destination + 12) = pad;
}

uint32 sub_80041528(uint32 node)
{
    struct { uint32 position[4]; sint32 distance[2]; uint16 nearest; uint16 pad; } proximity;
    uint32 record = draft_local_address(&proximity, sizeof(proximity));
    uint32 actor = node + 12, mesh = E32(E32(actor));
    uint32 table, collision, state, kind, value, target, damage, hit_player, random, flags;
    uint32 speed, index, old_rotation[2], child, countdown, mask, result;
    sint32 turn, distance, frame, limit, height;
    uint16 shadow = 1, ground_effect = 1, landing_effect = 1;
    uint8 region_update = 1, obstacle_update = 1, hit_tests = 0;
    uint8 gravity_update = 1, proximity_update = 1, alternate_gravity = 0, preserve_rotation = 0;

    E16(node + 240) = 0;
    E16(0x800716C0) = E16(node + 226);
    E16(0x80071794) = E16(E32(node + 52));
    sub_80044CC0(E32(mesh + 8), E32(mesh + 16));
    sub_80044DC8(E32(mesh + 8), E32(mesh + 16));
    if (E16(E32(node + 20) + 28)) enemy_vector_copy(mesh + 8, E32(node + 20));
    if (E16(0x8007171C)) sub_800407D8(actor);
    collision = E32(node + 24);
    if (E32(collision + 128)) {
        E16(node + 240) = 0x7FFF;
        if (E16(node + 226) == 26) { E32(collision + 132) |= 0x8000; sub_80040658(actor); }
        E16(node + 250) = E16(E32(node + 24) + 148);
        if (E16(node + 230) & 2) {
            E16(node + 244) += 10 * ES16(0x800719C8) + 25 + ((64 - ES16(0x800716F8)) >> 1);
            collision = E32(node + 24);
            damage = E8(collision + 132);
            turn = (sint16)sub_80046D0C((sint16)(E16(collision + 136) - E16(mesh + 26)));
            if ((uint32)(E16(node + 226) - 17) < 2) damage >>= 4;
            hit_player = E16(E32(node + 24) + 138);
            if (hit_player == 0xFFFF) { damage >>= 1; if (!(uint16)damage) damage = 1; }
            if (damage < E16(node + 236)) E16(node + 236) -= damage;
            else E16(node + 236) = 0;
            if (hit_player < 2 && damage) {
                if (!(E16(0x80071794) & 0x80)) {
                    target = 0x800AFFC0 + 288 * hit_player;
                    E16(target + 2) = 45; E16(target) = E16(node + 234);
                    E16(target + 4) = E16(node + 236); E16(target + 6) = E16(node + 238);
                }
                sub_8005267C(hit_player, 50);
            }
            if ((E32(E32(node + 24) + 132) & 0x4000) && damage) E16(node + 248) = 60;
            if (!E16(node + 236)) {
                sub_8003F7F4(actor); sub_8003F928(E16(node + 92));
                if ((E16(0x80071794) & 0x80) || (sub_80040A50(mesh), (E16(0x80071794) & 0x80))) {
                    E32(E32(node + 24) + 132) &= 0x7FFF;
                    E16(node + 90) = 1; E16(0x800717C4) = 60;
                    E16(0x80071A34) = E16(E32(node + 24) + 138); sub_80013F80();
                }
                if ((E16(0x80071794) & 4) && (sub_80011B8C() & 127) >= 64) {
                    sub_80040314(actor); goto remove_item;
                }
                if (!E8(node + 256) && E16(E32(node + 24) + 150) &&
                    (E16(0x80071794) & 0x1000) && !E16(0x800719BC)) {
                    switch (sub_80011B8C() & 7) {
                    case 0: sub_800411A0(actor, 3); break;
                    case 1: sub_800411A0(actor, 2); break;
                    case 2: sub_800411A0(actor, 4); break;
                    case 3: sub_800411A0(actor, 5); break;
                    }
                }
                if (!(E32(E32(node + 24) + 132) & 0x8000) && E16(node + 90)) {
                    if ((sub_80011B8C() & 127) < 64 && (turn < 0 ? -turn : turn) >= 1024 && (E16(0x80071794) & 0x800)) {
                        E16(node + 232) = 32; sub_8005915C(actor, 16);
                    } else sub_8005915C(actor, 15);
                } else sub_8003FD5C(mesh, actor, turn);
            } else if (damage) {
                if (!(E32(E32(node + 24) + 132) & 0x8000) && E16(node + 90)) {
                    sub_8003F8D0(E16(node + 92));
                    if ((turn < 0 ? -turn : turn) < 1024) {
                        E16(mesh + 26) = E16(E32(node + 24) + 136) & 4095;
                        sub_8005915C(actor, 12); sub_8003F7F4(actor);
                    } else {
                        E16(mesh + 26) = (E16(E32(node + 24) + 136) + 2048) & 4095;
                        random = sub_80011B8C() & 127;
                        if (random < 43) sub_8005915C(actor, 9);
                        if (random - 43 < 43) sub_8005915C(actor, 10);
                        if (random >= 86) sub_8005915C(actor, 11);
                    }
                } else { sub_8003F7F4(actor); sub_8003FCC4(mesh, actor, turn); }
            } else {
                sub_8003F7F4(actor); sub_8003F9F0();
                E16(mesh + 26) = (E16(E32(node + 24) + 136) + 2048) & 4095;
                sub_8005915C(actor, 18);
            }
        }
    }
    if (E16(node + 90)) E32(node + 80) = ES32(node + 80) < 8 ? 0 : E32(node + 80) - 8;
    E32(node + 68) = 0; E16(node + 230) = 3; E16(E32(node + 24) + 144) = 0;
    sub_80051F74(mesh + 8, record); sub_800591A4(actor, record); sub_8003FDCC(actor, mesh);
    child = E32(node + 16);
    if (child) {
        kind = E16(node + 226);
        if (E16(node + 234) == 2) {
            E32(child + 68) = 0;
            if (kind >= 9 && kind < 13) E32(child + 68) = 1;
            else if (kind == 35) E32(child + 68) = 2;
        }
        if (E16(node + 234) == 20) {
            E32(E32(node + 16) + 68) = 2;
            if (kind >= 9 && kind < 13) E32(E32(node + 16) + 68) = 1;
            else if (kind == 39) E32(E32(node + 16) + 68) = 0;
        }
    }
    kind = E16(node + 226);
    if ((kind - 9 < 2 || kind == 11) && E32(node + 56) && (uint32)(E16(E32(node + 56) + 214) - 45) < 2) E16(node + 228) = 7;
    if (E16(0x80071794) & 0x80) {
        E8(0x800716CC) = E8(node + 234); E16(0x800715E0) = E16(node + 236);
        E8(0x80071760) |= 1; E16(0x800716B8) = E16(node + 238);
    }
    state = E16(node + 228);
    switch (state) {
    case 0:
        sub_80041160(actor); sub_80059288(actor, record, 1);
        sub_80059318(actor, ES16(E32(node + 52) + 10 + 2 * E16(node + 242)));
        hit_tests = 1;
        turn = (sint16)sub_80046D0C((sint16)(E16(mesh + 26) - E16(0x8007189C)));
        distance = turn < 0 ? -turn : turn;
        value = distance < 512 ? 0 : distance >= 1537 ? 1 : turn < 0 ? 2 : 3;
        if (E16(node + 226) != value) sub_8005915C(actor, value);
        table = E32(node + 52);
        if (ES16(table + 10 + 2 * E16(node + 242)) + ES16(table + 6) < proximity.distance[ES16(0x800718CC)]) {
            if ((sub_80011B8C() & 127) >= 64 && (E16(0x80071794) & 2)) { value = 4; goto change_state; }
            if (E16(0x80071794) & 0x400) {
                enemy_vector_copy(node + 32, 0x800AF6D0); E32(node + 84) = -2000; value = 35; goto change_state;
            }
        }
        if (sub_800599FC(actor, record)) { value = (sub_80011B8C() & 127) < 33 ? ((sub_80011B8C() & 127) < 64 ? 20 : 19) : 17; goto change_state; }
        if (E16(node + 236) < 12 && (E16(0x80071794) & 64) && E8(node + 257) < 2 && proximity.distance[ES16(0x800718CC)] < 4000) {
            if (enemy_angle_distance(E16(mesh + 26) - E16(E32(node + 220) + 18)) >= 1801 && (sub_80011B8C() & 127) >= 65) {
                sub_8005915C(actor, 33); ++E8(node + 257); break;
            }
        }
        speed = (sint16)sub_80059830(actor, ES16(E32(node + 52) + 2));
        if (!sub_80030E5C(mesh + 8, 0x800AF6D0, speed, 512) && enemy_angle_distance(E16(mesh + 26) - E16(0x80071608)) < 64) {
            E16(node + 232) = 0; value = E8(E32(node + 220) + 244) ? 36 : ((sub_80011B8C() & 127) < 64 ? 23 : 22); goto change_state;
        }
        if (--E16(node + 232)) break;
        if (ES16(E32(node + 52) + 6) < proximity.distance[ES16(0x800718CC)] && (E16(0x80071794) & 8)) {
            E16(node + 232) = 60; sub_8005915C(actor, 5); sub_8003F994(E16(node + 92)); break;
        }
        goto reset_countdown;
    case 1:
        sub_80041160(actor); sub_80059288(actor, record, 1);
        E16(node + 60) = 0; E16(node + 64) = 0; E16(node + 62) = E16(mesh + 26);
        E32(node + 68) = ES16(E32(node + 52) + 4);
        if (proximity.distance[ES16(0x800718CC)] < ES16(E32(node + 52) + 6)) goto slow_idle;
        break;
    case 2:
        sub_80059288(actor, record, 0); hit_tests = 1;
        if (proximity.distance[ES16(0x800718CC)] < 2500 || E8(node + 112)) goto idle_clear;
        break;
    case 3:
        E16(node + 90) = 0; E16(mesh + 26) = (E16(E32(node + 56) + 18) + 2048) & 4095;
        proximity_update = 0; sub_80051208(E8(E32(node + 56) + 240) - 1);
        enemy_vector_copy(mesh + 8, 0x1F800028); E32(mesh + 12) -= 128;
        obstacle_update = region_update = gravity_update = 0;
        countdown = E16(node + 254); E16(node + 254) = countdown + 1;
        if (countdown >= 211 && E32(node + 56)) E32(E32(node + 56) + 200) = 0;
        if (!E32(E32(node + 56) + 200)) {
            E32(node + 56) = 0; E32(node + 84) = -200; sub_8005915C(actor, 38);
            sub_8003F8D0(E16(node + 92)); E16(node + 108) = 7;
        }
        break;
    case 4:
        E16(node + 90) = 1;
        E32(mesh + 24) = E32(E32(node + 56) + 16); E32(mesh + 28) = E32(E32(node + 56) + 20);
        target = E32(E32(E32(node + 56) + 52));
        E16(0x1F800020) = 0; E16(0x1F800022) = E16(target + 170) + 1700; E16(0x1F800024) = 800;
        sub_8005CDD8(target + 32, 0x1F800020, 0x1F800028);
        target = E32(E32(E32(node + 56) + 52)); enemy_vector_copy(mesh + 8, target + 8);
        E32(mesh + 8) += E32(0x1F800028); E32(mesh + 12) += E32(0x1F80002C); E32(mesh + 16) += E32(0x1F800030);
        proximity_update = obstacle_update = region_update = gravity_update = 0; preserve_rotation = 1;
        countdown = E16(node + 254); E16(node + 254) = countdown + 1;
        if (countdown >= 211 && E32(node + 56)) E32(E32(node + 56) + 200) = 0;
        if (!E32(E32(node + 56) + 200)) { E32(node + 56) = 0; goto idle_clear; }
        break;
    case 5:
        hit_tests = 1; if (!E16(node + 232) || !--E16(node + 232)) goto idle_clear; break;
    case 6:
        frame = ES16(node + 108); hit_tests = 1;
        if (frame < 8) E16(node + 230) = 0;
        if (frame == 2) { E16(node + 74) = (E16(mesh + 26) + (E16(node + 226) == 12 ? 0 : 2048)) & 4095; E32(node + 80) = E16(node + 250); }
        if (E16(node + 226) == 18) E16(E32(node + 24) + 144) = 1;
        if (E8(node + 112)) goto idle_clear;
        break;
    case 7:
        E16(node + 230) = 1; if (E8(node + 112)) { value = 7; goto change_state; } break;
    case 8: case 9: case 28:
        landing_effect = 0; frame = ES16(node + 108);
        E16(node + 230) = state == 28 && !E16(node + 236) ? 0 : E16(0x800719D0) & 1;
        if (frame == 2) E16(node + 232) = 0;
        limit = state == 8 ? 43 : state == 9 ? 44 : 31;
        if (frame >= (state == 28 ? 3 : 7) && frame < limit) {
            E16(node + 60) = E16(node + 64) = 0;
            E16(node + 62) = (E16(mesh + 26) - (state == 8 ? 0 : 2048)) & 4095;
            E32(node + 68) = state == 9 && E16(node + 226) == 38 ? 80 : 100;
        }
        if (frame == limit) { E32(node + 72) = E32(node + 60); E32(node + 76) = E32(node + 64); E32(node + 80) = state == 8 ? 100 : 80; }
        if (frame == (state == 8 ? 29 : state == 9 ? 35 : 10) && !E16(node + 90)) E16(node + 108) = --frame;
        if (state == 9 && E16(node + 226) == 38 && !(E16(0x800719D0) & 1) && frame < 44) {
            target = E32(node + 28); E32(target + 20) = 0; E32(target + 132) = 32770;
            E16(target + 136) = E16(mesh + 26) + 2048; E16(target + 138) = 0xFFFF; E16(target + 148) = 80;
            sub_80047534(target, E32(E32(actor)) + 336, 0);
            sub_80047534(E32(node + 28), E32(E32(actor)) + 504, 0); sub_800475A8(E32(node + 28));
        }
        if (E8(node + 112)) {
            ++E16(node + 232); if (!E16(node + 236)) goto dying;
            if (E16(node + 232) >= 11) { value = state == 8 ? 24 : 25; goto change_state; }
        }
        break;
    case 10: case 16:
        if (state == 10) {
            shadow = 0; ground_effect = 1; E16(node + 230) = E16(0x800719D0) & 1;
            if ((E16(0x80071794) & 0x80) && E16(node + 108) == 3) sub_8004148C(actor);
        } else if (E16(0x80071794) & 0x80) obstacle_update = 0;
        if (E16(node + 234) == 25) {
            if (state == 10) E16(node + 230) = 0;
            if (state == 10) E16(0x80071810) = 0;
            if ((uint32)(E16(node + 108) - (state == 10 ? 101 : 161)) >= (state == 10 ? 149u : 89u)) {
                sub_80013B64(1, 0, 0, 0); E16(0x800717F8) = 6; E8(0x80071544) = 0;
            } else {
                E8(0x80071544) = 1;
                if (E16(0x800719D0) & 1) { sub_80013B64(1, 255, state == 10 ? 128 : 255, state == 10 ? 0 : 255); E16(0x800717F8) = 0xFFFF; }
                else { sub_80013B64(1, 0, 0, 0); E16(0x800717F8) = 6; E16(0x8007156C) = E16(0x8007158C) = 128; if (state == 16) E16(0x8007155C) = 128; E16(0x80071A50) = 64; }
                if (state == 10 && !(E16(0x800719D0) & 7)) {
                    E32(0x1F800028) = E32(0x1F800030) = 0; E32(0x1F80002C) = -120;
                    sub_80022DD4(mesh + 8, 0x1F800028, 6, 6, 0, 128, 0);
                }
            }
            if (state == 10 && E16(node + 108) == 105) { E16(0x800717FC) = 2; enemy_vector_copy(0x800AFEB0, mesh + 8); }
        }
        if (state == 16) { sub_80041160(actor); hit_tests = 1; }
        if (E8(node + 112)) {
            if (state == 10) {
                if (E16(node + 234) == 26) { sub_80022B24(0); sub_80040314(actor); goto remove_item; }
                E16(node + 232) = 1; goto dying;
            }
            E32(node + 220) = 0; sub_800599B4(actor);
            if (E16(0x80071794) & 0x80) { E16(0x800717FC) |= 1; sub_80022B24(mesh + 8); }
        }
        break;
    case 11:
        shadow = ground_effect = proximity_update = 0; E16(node + 230) = E16(0x800719D0) & 1;
        if (!(++E16(node + 232) & 1)) break;
        countdown = E16(node + 232) >> 3; if (countdown >= 9) countdown = 8;
        E16(node + 240) = 2 * (8 - countdown); if (E16(node + 240)) break;
        if ((E16(0x80071794) & 0x80) && E16(node + 234) != 25) sub_80022B24(0);
        goto remove_item;
    case 12:
        E16(node + 230) = E16(0x800719D0) & 1; if (!--E16(node + 232)) { value = 14; goto change_state; } break;
    case 13:
        E16(E32(node + 24) + 144) = 1; sub_80059288(actor, record, 1);
        if (!E8(node + 112)) break;
        E32(node + 220) = 0; sub_800599B4(actor);
        if (E16(node + 244) >= 151) { value = E16(node + 242) + 27; goto change_state; } break;
    case 14:
        E16(E32(node + 24) + 144) = 1; E16(node + 230) = E16(0x800719D0) & 1;
        sub_80059288(actor, record, 1); E16(node + 60) = E16(node + 64) = 0;
        E16(node + 62) = E16(mesh + 26) + (E16(node + 226) == 19 ? -1024 : 1024); E32(node + 68) = 160;
        if (E8(node + 112)) {
            E32(node + 72) = E32(node + 60); E32(node + 76) = E32(node + 64); E32(node + 80) = 120;
            E32(node + 220) = 0; sub_800599B4(actor);
            if (E16(node + 244) >= 151) { value = E16(node + 242) + 27; goto change_state; }
        }
        break;
    case 15:
        sub_80041160(actor); if (ES16(node + 108) == 39) E16(node + 108) = 0;
        distance = (sint16)(E16(E32(node + 220) + 268) - E8(E32(0x80071704) + 14 * E16(node + 224) + 9));
        if ((distance < 0 ? -distance : distance) >= 4 && E16(node + 234) != 26) break;
        if (E16(0x80071794) & 0x80) {
            obstacle_update = 0; if (E16(node + 108) != 38) break;
            E16(node + 226) = 40; E16(node + 228) = 16;
            switch (E16(node + 234)) {
            case 10: sub_80022C40(mesh + 8, mesh + 8, -3522, -1878, 0, 0, -2624, 0, 2288); value = 16; break;
            case 11: sub_80022C40(mesh + 8, mesh + 8, -3570, -3302, 0, 0, -2768, 0, 2417); value = 17; break;
            case 12: sub_80022C40(mesh + 8, mesh + 8, -3570, -230, 0, 0, -3152, 0, ES16(mesh + 26)); value = 18; break;
            case 20: sub_80022C40(mesh + 8, E32(E32(actor)) + 3200, -8530, -678, 0, 0, 688, 0, 2865); value = 19; break;
            case 25: sub_80022C40(mesh + 8, E32(E32(actor)) + 176, -3570, -2614, 0, 0, -400, 0, 2241); value = 20; break;
            case 26: sub_80022C40(mesh + 8, E32(E32(actor)) + 176, -4354, -4006, 0, 0, -400, 0, 2241); value = 21; break;
            default: goto frame_tail;
            }
            sub_80013FE8(value, 230, 1);
        } else { E16(node + 226) = 40; E16(node + 228) = 16; }
        break;
    case 17:
        sub_80059288(actor, record, 1); hit_tests = 1; if (!E8(node + 112)) break;
        if ((sub_80011B8C() & 127) >= 101) goto idle_clear;
        value = (sub_80011B8C() & 127) < 64 ? 20 : 19; goto change_state;
    case 18:
        hit_tests = 1; kind = E16(node + 226); frame = ES16(node + 108);
        if (kind == 22 && frame == 2) sub_8003F94C(E16(node + 92));
        if (E16(node + 226) == 23 && frame == 2) sub_8003F970(E16(node + 92));
        sub_80059288(actor, record, 0);
        if (enemy_angle_distance(E16(mesh + 26) - E16(0x80071608)) >= 257) goto idle_clear;
        if (E8(E32(node + 220) + 244)) {
            ++E16(node + 232); limit = (uint16)(E16(E32(node + 52) + 22 + 2 * E16(node + 242)) - E16(0x800719C8));
            if (enemy_angle_distance(E16(mesh + 26) - E16(E32(node + 220) + 18)) < 1024) limit *= 5;
            limit = (uint16)((uint16)(limit + 10 * (E16(0x8007172C) - 1)) * ES16(0x800716F8)) >> 6;
            if (E16(node + 232) >= (uint32)limit) { value = E16(node + 242) + 27; goto change_state; }
        } else {
            E16(node + 232) = 0;
            if (E16(node + 226) == 36 && !E8(0x80071690)) { value = (sub_80011B8C() & 127) < 64 ? 23 : 22; goto change_state; }
        }
        break;
    case 19:
        hit_tests = 1;
        if (sub_800599FC(actor, record)) { value = (sub_80011B8C() & 127) < 65 ? ((sub_80011B8C() & 127) < 64 ? 20 : 19) : 17; goto change_state; }
        if (!E8(node + 112)) break;
        if (E16(node + 236) < 16 && (sub_80011B8C() & 127) >= 64 && (E16(0x80071794) & 32)) { sub_8005915C(actor, 8); E16(node + 232) = 120; break; }
        goto idle_clear;
    case 20:
        sub_800404EC(actor); countdown = --E16(node + 232);
        if (countdown < 90) { mask = countdown < 20 ? 1 : countdown < 40 ? 3 : countdown < 60 ? 7 : countdown < 80 ? 15 : 31; if (!(countdown & mask)) E16(node + 240) = 0x7FFF; }
        if (E16(node + 232)) break;
        sub_80040658(actor); goto idle_clear;
    case 21:
        frame = ES16(node + 108);
        if ((E16(0x80071794) & 0x80) && E16(node + 242) >= 4 && frame < 60) E16(node + 230) = !(E16(0x800719D0) & 3);
        if (E16(node + 244) < 151 || E8(0x80071690)) {
            if (frame < 20 && sub_800599FC(actor, record)) { value = (sub_80011B8C() & 127) < 65 ? ((sub_80011B8C() & 127) < 64 ? 20 : 19) : 17; goto change_state; }
        } else {
            if (frame < 40) E16(node + 230) = !(E16(0x800719D0) & 3);
            if (frame == 40) E16(node + 244) >>= 1;
        }
        if (frame < 40 || (E16(0x80071794) & 0x80)) sub_80059288(actor, record, 1);
        shadow = 2; if (E8(node + 112) && E16(node + 90)) goto idle_clear;
        break;
    case 22:
        sub_80041160(actor); sub_80059288(actor, record, 1); region_update = gravity_update = 0;
        if ((sint16)(E16(E32(node + 220) + 268) - E8(E32(0x80071704) + 14 * E16(node + 224) + 9)) >= -2) ++E16(node + 232);
        if (E16(node + 232) >= 91 || E16(0x8007172C) == 1) { E32(node + 84) = -1800; value = 35; goto change_state; }
        break;
    case 23:
        sub_80059288(actor, record, 1); sub_80030E5C(mesh + 8, node + 32, 120, 256); region_update = 0;
        if (E16(0x80071794) & 0x400) alternate_gravity = 1;
        if (!E16(node + 90)) break;
        index = E16(node + 252); if (index != 1024) { E8(0x800C9D68 + index) = 0; E16(node + 252) = 1024; }
        goto idle;
    case 24:
        E16(node + 230) = 0;
        if (ES16(node + 108) == 35 && !E16(node + 90)) E16(node + 108) = 34;
        countdown = E16(node + 232); E16(mesh + 26) = (E16(mesh + 26) + 4 * countdown) & 4095; E16(node + 232) = countdown + 1;
        if (E16(node + 232) >= 60) E16(node + 88) = 100;
        else { E32(node + 84) = 0; E16(node + 90) = E16(node + 88) = 0; E32(mesh + 12) = E32(node + 216) - (E16(node + 232) << 6); }
        if (E16(node + 232) & 1) E16(node + 240) = 512;
        height = ES32(mesh + 12); E32(mesh + 12) = E32(node + 216);
        if (!(E16(node + 232) & 3)) { E32(0x1F800028) = E32(0x1F800030) = 0; E32(0x1F80002C) = -120; sub_80022DD4(mesh + 8, 0x1F800028, 6, 6, 0, 128, 0); }
        E32(mesh + 12) = height; if (!E16(node + 90)) break;
        E32(0x1F800028) = E32(0x1F800030) = 0; E32(0x1F80002C) = -8;
        sub_80022DD4(mesh + 8, 0x1F800028, 6, 6, 0, 128, 0); sub_80023DF0(mesh + 8); goto remove_item;
    case 25: case 26:
        sub_80041160(actor);
        if (!(E16(node + 108) & 7) && (sub_80011B8C() & 127) >= 101) sub_8003F904(E16(node + 92));
        sub_80059288(actor, record, 0);
        sub_80059318(actor, ES16(E32(node + 52) + 10 + 2 * E16(node + 242)));
        if (state == 25 && ES32(0x80071860) < 2000) {
            sub_80046D0C((sint16)(E16(mesh + 26) - E16(0x80071608))); sub_80059288(actor, record, 1);
            speed = (sint16)sub_80059830(actor, ES16(E32(node + 52) + 2));
            if (!sub_80030E5C(mesh + 8, 0x800AF6D0, speed, 1024) && enemy_angle_distance(E16(mesh + 26) - E16(0x80071608)) < 64) {
                E16(node + 232) = 0; value = E8(E32(node + 220) + 244) ? 36 : ((sub_80011B8C() & 127) < 64 ? 23 : 22); goto change_state;
            }
            goto decrement_countdown;
        }
        if (enemy_angle_distance(E16(mesh + 26) - E16(0x8007189C)) >= 1537) { value = state == 25 && ES32(0x80071860) < 4001 ? 1 : 2; goto change_state; }
        E16(mesh + 26) = sub_80059224(ES16(mesh + 26), ES16(0x8007189C));
        if (state == 25) {
            if (ES32(0x80071860) >= 4001) { value = 4; goto change_state; }
            speed = (sint16)sub_80059830(actor, ES16(E32(node + 52) + 2)); sub_80030E5C(mesh + 8, 0x800AF6D0, speed, 1024); break;
        }
        E16(node + 60) = E16(node + 64) = 0; E16(node + 62) = E16(mesh + 26);
        E32(node + 68) = ES16(E32(node + 52) + 4);
        if (ES32(0x80071860) < ES16(E32(node + 52) + 6)) goto slow_idle;
        goto decrement_countdown;
    case 27: value = 14; goto turn_around;
    case 30: if (E8(node + 112)) { value = 0; goto turn_around; } break;
    case 31:
        if (!(E16(node + 108) & 7) && (sub_80011B8C() & 127) >= 101) sub_8003F904(E16(node + 92));
        if (E8(node + 112)) { value = 4; goto turn_around; } break;
    default: break;
    }
    goto frame_tail;
turn_around:
    E16(mesh + 26) = (E16(mesh + 26) + 2048) & 4095;
change_state:
    sub_8005915C(actor, value); goto frame_tail;
dying:
    E16(node + 226) = 39; E16(node + 228) = 11; goto frame_tail;
slow_idle:
    E32(node + 72) = E32(mesh + 24); E32(node + 76) = E32(mesh + 28);
    E32(node + 80) = ES16(E32(node + 52) + 4) / 2; goto idle;
decrement_countdown:
    if (--E16(node + 232)) goto frame_tail;
reset_countdown:
    E16(node + 232) = 63; sub_800598CC(actor); goto frame_tail;
idle_clear:
    E32(node + 220) = 0;
idle:
    sub_800599B4(actor);
frame_tail:
    speed = E32(node + 68); if (speed) sub_80051550(mesh + 8, speed, node + 60);
    speed = E32(node + 80);
    if (speed) {
        sub_80051550(mesh + 8, speed, node + 72);
        if (E16(node + 90) && !(E16(0x800719D0) & 3)) {
            E32(0x1F800028) = E32(0x1F800030) = 0; E32(0x1F80002C) = 5;
            sub_80022CC0(mesh + 8, 0x1F800028, 2, 5);
        }
    }
    sub_80058484(node + 92, E32(actor)); sub_80051614(mesh + 8, node + 92, ES16(mesh + 26));
    sub_80046324(E32(mesh + 8), E32(mesh + 16), node + 224);
    index = E16(node + 224);
    if (index != 0xFFFF && region_update) sub_80046A28(E32(0x80071704) + 14 * index, index, mesh + 8);
    old_rotation[0] = E32(mesh + 24); old_rotation[1] = E32(mesh + 28);
    E32(node + 216) = sub_8005178C(mesh + 8, 1000, mesh + 24, E16(node + 224), node + 152);
    if (!E16(node + 90)) {
        if (ES32(node + 84) >= 0) { E32(mesh + 24) = old_rotation[0]; E32(mesh + 28) = old_rotation[1]; }
        else { E16(mesh + 24) = sub_80051EB8((sint16)old_rotation[0], 0); E16(mesh + 28) = sub_80051EB8((sint16)old_rotation[1], 0); }
    }
    if (preserve_rotation) { E32(mesh + 24) = old_rotation[0]; E32(mesh + 28) = old_rotation[1]; }
    if (gravity_update) {
        if (alternate_gravity) sub_80051B14(node + 84, mesh + 8, E32(node + 216), landing_effect);
        else sub_800519E4(node + 84, mesh + 8, E32(node + 216), landing_effect);
    }
    if (obstacle_update) {
        enemy_vector_copy(E32(node + 20), mesh + 8);
        E16(E32(node + 20) + 24) = E16(mesh + 26); sub_800471E8(E32(node + 20));
    } else E16(E32(node + 20) + 28) = 0;
    sub_800585D8(node + 92); if (proximity_update) sub_80030FE0(record);
    if (hit_tests) {
        mask = sub_80040ABC(actor, record, 4000);
        if ((uint16)mask) { if (mask & 1) sub_80040C7C(actor, record, 0); if (mask & 2) sub_80040C7C(actor, record, 1); }
        mask = sub_80040E0C(actor, record, 4000);
        if ((uint16)mask) { if (mask & 1) sub_80040FD0(actor, record, 0); if (mask & 2) sub_80040FD0(actor, record, 1); }
    }
    if (proximity.distance[proximity.nearest] < ES16(node + 246) && (shadow | ground_effect)) {
        if (shadow) sub_800322A4(record);
        if (ground_effect) sub_80021288(E32(mesh + 8), E32(mesh + 16), E32(node + 216),
            ((sint32)(E32(mesh + 12) - E32(node + 216)) >> 1) + E32(node + 216), 0);
    }
    if (proximity.distance[proximity.nearest] < 9000) sub_8004E520(mesh + 8, 1);
    sub_80032A20(node + 152); sub_80046278(E16(node + 224));
    if (E16(node + 248)) {
        --E16(node + 248); flags = (E16(0x800719D0) >> 1) & 1;
        sub_8001A7A8(E32(E32(actor)), flags ? 16 : 192, flags ? 0 : 32, 0); sub_80040428(actor);
    } else if (E16(node + 240)) {
        value = E16(node + 240); sub_8001A7A8(mesh, (value >> 7) & 248, (value >> 2) & 248, 8 * (value & 31));
    } else if (E16(0x800BFD2C + 40 * E16(node + 92)) == 2) sub_8001DEB0(mesh);
    else sub_8001C4B8(mesh);
    value = E16(node + 114);
    if (value != 0xFFFF) {
        target = E32(E32(actor)) + 168 * E16(node + 118); sub_8003133C(value, target + 8, E16(node + 116), target + 32);
    }
    index = E8(node + 256);
    if (index) {
        if (!(E16(0x800719D0) & 7)) {
            sub_800271A4(E32(E32(actor)) + 168 * index + 8, 2, ES16(mesh + 26), 0);
            sub_800271A4(E32(E32(actor)) + 168 * E8(node + 260) + 8, 2, ES16(mesh + 26), 0); index = E8(node + 256);
        }
        target = E32(E32(actor)) + 168 * index;
        height = (sint32)(E32(target + 12) + ES16(node + 258)); E16(node + 258) += 16;
        if (ES32(node + 216) < height) height = ES32(node + 216);
        E32(E32(E32(actor)) + 168 * E8(node + 256) + 12) = height;
        target = E32(E32(actor)) + 168 * E8(node + 256);
        if (E16(0x800BFD2C + 40 * E16(node + 92)) == 2) sub_8001DEB0(target); else sub_8001C4B8(target);
    }
    if (E16(node + 230)) return sub_800475F4(E32(node + 24));
    result = E32(node + 24); E32(result + 128) = 0; return result;
remove_item:
    sub_8003FC28(node); return sub_80032FD0(node);
}

#undef E8
#undef E16
#undef E32
#undef ES16
#undef ES32
