#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"
#include <stdlib.h>
/* Unverified draft; integration deferred */
/* TODO: SDK declarations require future fail-fast adapters */
extern uint32 sub_8005D138(uint32 angles, uint32 matrix);
extern uint32 sub_8005D3C8(uint32 angles, uint32 matrix);
extern uint32 sub_8005D658(uint32 angles, uint32 matrix);
extern uint32 sub_8005CC48(uint32 matrix, uint32 input, uint32 output);
extern uint32 sub_8005CF68(uint32 matrix);
extern uint32 sub_8005CDA8(uint32 input, uint32 output);
extern uint32 sub_800449A0(uint32 handle);
extern uint32 sub_80023B78(void);
extern uint32 sub_8005EEB8(uint32 packet, uint32 draw, uint32 dither, uint32 page, uint32 window);

static void b04_link(uint32 packet, uint32 slot, uint32 length)
{
    w_u32(packet, r_u32(slot) | (length << 24));
    w_u32(slot, packet & 0xFFFFFFu);
}

static void b04_rotate_columns(uint32 source, uint32 destination)
{
    uint32 col, row;
    for (col = 0; col != 3; ++col) {
        for (row = 0; row != 3; ++row)
            draft_gte_data(9 + row, (uint32)(sint32)(sint16)r_u16(source + 6 * row + 2 * col));
        draft_gte_command(0x49E012u);
        for (row = 0; row != 3; ++row)
            w_u16(destination + 6 * row + 2 * col, draft_gte_read(9 + row));
    }
}

void sub_8001DEB0(uint32 object)
{
    uint32 once = 1, visible = r_u16(object + 90), result = 0, i, geometry, parent, radius, depth;
    do {
        geometry = r_u32(object + 80);
        w_u16(object + 88, r_u16(object + 88) & 1u);
        switch (r_u16(object + 86)) {
        case 0: sub_8005D138(object + 24, object + 32); break;
        case 1: sub_8005D3C8(object + 24, object + 32); break;
        case 2: sub_8005D658(object + 24, object + 32); break;
        }
        parent = r_u32(object + 96);
        if (parent) {
            for (i = 0; i != 5; ++i) draft_gte_control(i, r_u32(parent + 32 + 4 * i));
            for (i = 0; i != 3; ++i) draft_gte_control(5 + i, r_u32(parent + 8 + 4 * i));
            draft_gte_data(0, r_u32(object)); draft_gte_data(1, r_u32(object + 4));
            draft_gte_command(0x480012u);
            for (i = 0; i != 3; ++i) w_u32(object + 8 + 4 * i, draft_gte_read(25 + i));
            b04_rotate_columns(object + 32, object + 32);
        }
        for (i = 0; i != 3; ++i) w_u32(0x1F800028u + 4 * i, r_u32(object + 8 + 4 * i) - r_u32(0x800BBFC4u + 4 * i));
        result = sub_8005CC48(0x800BBFDCu, 0x1F800028u, object + 64);
        if (geometry && visible) {
            depth = r_u32(object + 72); radius = r_u32(geometry + 16);
            result = depth - radius;
            if ((sint32)(depth + radius) >= 129) {
                result = (sint32)result < 20000;
                if (result) {
                    result = r_u16(object + 88);
                    if (result) {
                        uint32 clip = sub_8001A694(object, radius) & 0xFFFFu;
                        result = once;
                        if (!clip) {
                            if (once) { sub_8001B7A0(0); once = 0; }
                            w_u16(object + 88, r_u16(object + 88) | 2u);
                            for (i = 0; i != 5; ++i) draft_gte_control(i, r_u32(0x800B7184u + 4 * i));
                            b04_rotate_columns(object + 32, 0x1F800000u);
                            for (i = 0; i != 5; ++i) draft_gte_control(8 + i, r_u32(0x1F800000u + 4 * i));
                            for (i = 0; i != 5; ++i) draft_gte_control(i, r_u32(0x800BBFDCu + 4 * i));
                            if (!r_u16(object + 84)) {
                                b04_rotate_columns(object + 32, 0x1F800000u);
                                for (i = 0; i != 5; ++i) draft_gte_control(i, r_u32(0x1F800000u + 4 * i));
                            }
                            sub_8005A7FC(r_u32(geometry), r_u32(geometry + 12), r_u32(geometry + 4), r_u32(object + 164));
                        }
                    }
                }
            }
        }
        object = r_u32(object + 92);
    } while (object);
}

void sub_800485D0(uint32 ordering)
{
    uint32 selected = r_u16(0x800717F8u), bands, owner, level, height, offset = 0;
    sint32 angle, top, length, start[3], end[3], i;
    if (selected == 0xFFFFu) return;
    bands = r_u32(0x800689A4u + 4 * selected);
    angle = r_u16(0x800BBFD4u) & 0xFFFu;
    if (angle >= 0x801) angle = (sint16)(angle | 0xF000);
    angle = (angle >> 1) - (angle >> 2);
    if (angle < -96) angle = -96;
    if (angle >= 129) angle = 128;
    top = -angle - 96;
    owner = r_u16(0x800BC0CCu);
    level = owner == 0xFFFFu ? 0 : r_u8(r_u32(0x80071704u) + 14 * owner + 9);
    height = r_u8(r_u32(0x80071A1Cu) + level);
    while ((length = (sint16)r_u16(bands + offset)) != 0) {
        uint32 packet;
        if (top >= (sint32)height) break;
        for (i = 0; i != 3; ++i) {
            start[i] = (sint16)((uint32)(sint32)(sint16)r_u16(bands + offset + 2 + 2 * i) * r_u16(0x800718F4u)) >> 7;
            end[i] = (sint16)((uint32)(sint32)(sint16)r_u16(bands + offset + 8 + 2 * i) * r_u16(0x800718F4u)) >> 7;
        }
        if (top + length > 0) {
            if (top < 0) {
                sint32 skip = -top;
                /* TODO: Malformed band division follows the guest BREAK path */
                if (!length) abort();
                for (i = 0; i != 3; ++i) start[i] += (sint32)((uint32)(end[i] - start[i]) * (uint32)skip) / length;
                length -= skip; top = 0;
            }
            if ((sint32)height < top + length) {
                sint32 part = (sint16)(height - top);
                if (!length) abort();
                for (i = 0; i != 3; ++i) end[i] = start[i] + (sint32)((uint32)(end[i] - start[i]) * (uint32)part) / length;
                length = height - top;
            }
            if (length) {
                packet = r_u32(0x80071680u); w_u32(0x80071680u, packet + 40);
                if (start[0] == end[0] && start[1] == end[1] && start[2] == end[2]) {
                    w_u8(packet + 3, 3); w_u8(packet + 7, 96);
                    w_u16(packet + 8, 0); w_u16(packet + 10, top);
                    w_u16(packet + 12, 384); w_u16(packet + 14, length);
                    for (i = 0; i != 3; ++i) w_u8(packet + 4 + i, start[i]);
                } else {
                    w_u8(packet + 3, 8); w_u8(packet + 7, 56);
                    for (i = 0; i != 4; ++i) {
                        w_u16(packet + 8 + 8 * i, (i & 1) ? 384 : 0);
                        w_u16(packet + 10 + 8 * i, i < 2 ? top : top + length);
                        w_u8(packet + 4 + 8 * i, i < 2 ? start[0] : end[0]);
                        w_u8(packet + 5 + 8 * i, i < 2 ? start[1] : end[1]);
                        w_u8(packet + 6 + 8 * i, i < 2 ? start[2] : end[2]);
                    }
                }
                w_u32(packet, (r_u32(packet) & 0xFF000000u) | (r_u32(ordering) & 0xFFFFFFu));
                w_u32(ordering, (r_u32(ordering) & 0xFF000000u) | (packet & 0xFFFFFFu));
            }
        }
        offset += 14; top += length;
    }
}

void sub_8003076C(void)
{
    uint32 counter = r_u16(0x80071744u), particles = r_u32(0x80071530u), packet, i, j, slot;
    sint32 fade = 64;
    if (!counter) return;
    if (counter == 1) {
        w_u16(0x80071A28u, sub_8004496C());
        sub_8004486C(1, r_u16(0x80071A28u), r_u8(0x80071998u), 1548, 16000, 512);
    }
    if (counter < 64) fade = counter;
    if ((sint32)r_u16(0x800718B0u) - 64 < (sint32)counter) fade = r_u16(0x800718B0u) - counter;
    counter = (uint16)(counter + 1); w_u16(0x80071744u, counter);
    if (fade >= 61 && r_u16(0x800715CCu) < 24) { sub_80023B78(); sub_80023B78(); }
    if (!(counter & 511u)) {
        w_u16(0x8007155Cu, 170); w_u16(0x8007156Cu, 170); w_u16(0x8007158Cu, 170);
        w_u16(0x80071A50u, 8);
        sub_8004486C(1, sub_800448F4() & 0xFFFFu, 23, 1800, 16383, 512);
    }
    if (fade != 64) sub_8004486C(2, r_u16(0x80071A28u), 0, 0, (uint16)(fade * 200), 512);
    if (counter == r_u16(0x800718B0u)) {
        w_u16(0x80071744u, 0); sub_800449A0(r_u16(0x80071A28u));
        sub_8004486C(4, r_u16(0x80071A28u), 0, 0, 0, 0);
    }
    w_u32(0x1F800028u, r_u32(0x800BC050u)); w_u32(0x1F80002Cu, 0); w_u32(0x1F800030u, r_u32(0x800BC058u));
    sub_8005CC48(0x800AFE80u, 0x1F800028u, 0x1F800028u);
    w_u16(0x1F800022u, 0); w_u16(0x1F800020u, r_u16(0x800BBFD4u)); w_u16(0x1F800024u, r_u16(0x800BBFD8u));
    w_u32(0x1F800028u, (sint32)r_u32(0x1F800028u) >> 3); w_u32(0x1F800030u, (sint32)r_u32(0x1F800030u) >> 3);
    sub_8005D138(0x1F800020u, 0x1F800000u);
    for (j = 0; j != 5; ++j) draft_gte_control(j, r_u32(0x1F800000u + 4 * j));
    packet = r_u32(0x80071680u);
    for (i = 0; i != 75; ++i, particles += 40, packet += 20) {
        uint32 color = 255u - ((sint32)r_u32(particles + 8) >> 1);
        w_u8(packet + 3, 4); w_u8(packet + 7, 34);
        draft_gte_control(5, r_u32(particles) - 256); draft_gte_control(6, r_u32(particles + 4) - 256); draft_gte_control(7, r_u32(particles + 8) + 256);
        for (j = 0; j != 6; ++j) draft_gte_data(j, r_u32(particles + 16 + 4 * j));
        draft_gte_command(0x280030u);
        if (color > (uint32)fade) color = fade;
        color >>= 1; w_u8(packet + 4, (uint8)color >> 1); w_u8(packet + 5, color); w_u8(packet + 6, color);
        w_u32(particles + 4, ((uint16)r_u32(particles + 4) + 80u) & 511u);
        w_u32(particles + 8, ((uint16)r_u32(particles + 8) - r_u32(0x1F800030u)) & 511u);
        w_u32(particles, ((uint16)r_u32(particles) - r_u32(0x1F800028u)) & 511u);
        for (j = 0; j != 3; ++j) w_u32(packet + 8 + 4 * j, draft_gte_read(12 + j));
        slot = r_u32(0x8007184Cu) + 1024;
        w_u32(packet, (r_u32(packet) & 0xFF000000u) | (r_u32(slot) & 0xFFFFFFu));
        w_u32(slot, (r_u32(slot) & 0xFF000000u) | (packet & 0xFFFFFFu));
    }
    w_u32(0x80071680u, packet + 40);
    sub_8005EEB8(packet, 1, 1, r_u16(0x80071782u), 0);
    slot = r_u32(0x8007184Cu) + 1024;
    w_u32(packet, (r_u32(packet) & 0xFF000000u) | (r_u32(slot) & 0xFFFFFFu));
    w_u32(slot, (r_u32(slot) & 0xFF000000u) | (packet & 0xFFFFFFu));
}

uint32 sub_8002FC3C(void)
{
    uint32 particles = r_u32(0x80071530u), packet, i, j, uv[4], page, clut;
    sint32 brightness = (sint16)r_u16(0x8007188Cu), delta = (sint16)r_u16(0x800716E8u);
    if (!brightness && !delta) return 0;
    if (delta > 0) {
        w_u16(0x8007188Cu, brightness + delta);
        if ((sint16)(brightness + delta) >= 128) { w_u16(0x8007188Cu, 128); w_u16(0x800716E8u, 0); }
    }
    delta = (sint16)r_u16(0x800716E8u);
    if (delta < 0) {
        uint32 sum = r_u16(0x8007188Cu) + (uint32)delta;
        w_u16(0x8007188Cu, sum);
        if ((sint32)(sum << 16) <= 0) { w_u16(0x8007188Cu, 0); w_u16(0x800716E8u, 0); }
    }
    w_u32(0x1F800028u, (uint32)(sint32)(sint16)r_u16(0x80071804u) + r_u32(0x800BC050u));
    w_u32(0x1F80002Cu, r_u32(0x800BC054u)); w_u32(0x1F800030u, r_u32(0x800BC058u));
    sub_8005CC48(0x800AFE80u, 0x1F800028u, 0x1F800028u);
    w_u16(0x1F800020u, 0); w_u16(0x1F800022u, 0); w_u16(0x1F800024u, (r_u16(0x800719D0u) << 6) & 4095u);
    w_u32(0x1F800028u, (sint32)r_u32(0x1F800028u) >> 3); w_u32(0x1F80002Cu, (sint32)r_u32(0x1F80002Cu) >> 3); w_u32(0x1F800030u, (sint32)r_u32(0x1F800030u) >> 4);
    sub_8005D138(0x1F800020u, 0x1F800000u);
    for (j = 0; j != 5; ++j) draft_gte_control(j, r_u32(0x1F800000u + 4 * j));
    clut = r_u16(0x800C1496u); page = r_u16(0x800C1494u) | r_u16(0x80071782u);
    uv[0] = r_u8(0x800C1498u); uv[1] = r_u8(0x800C149Au); uv[2] = uv[0] + r_u8(0x800C149Cu) - 1; uv[3] = uv[1] + r_u8(0x800C149Eu) - 1;
    packet = r_u32(0x80071680u);
    for (i = 0; i != 96; ++i, particles += 40) {
        sint32 difference; uint32 color, depth, slot;
        w_u8(packet + 3, 7); w_u8(packet + 7, 38);
        draft_gte_control(5, r_u32(particles) - 256); draft_gte_control(6, r_u32(particles + 4) - 256); draft_gte_control(7, 2 * r_u32(particles + 8) + 128);
        for (j = 0; j != 6; ++j) draft_gte_data(j, r_u32(particles + 16 + 4 * j));
        draft_gte_command(0x280030u);
        difference = (sint32)((uint32)brightness - (uint32)((sint32)r_u32(particles + 8) >> 2));
        color = difference < 0 ? 0 : (uint8)difference; color -= color >> 3;
        w_u8(packet + 4, color); w_u8(packet + 5, color); w_u8(packet + 6, color);
        w_u32(particles + 4, (uint16)(r_u32(particles + 4) + 1 + (i & 3)));
        w_u32(particles + 4, ((uint16)r_u32(particles + 4) - r_u32(0x1F80002Cu)) & 511u);
        w_u32(particles + 8, ((uint16)r_u32(particles + 8) - r_u32(0x1F800030u)) & 511u);
        w_u32(particles, ((uint16)r_u32(particles) - (i & 3) - r_u32(0x1F800028u)) & 511u);
        w_u16(packet + 14, clut); w_u16(packet + 22, page);
        w_u8(packet + 20, uv[2]); w_u8(packet + 28, uv[0]); w_u8(packet + 13, uv[1]); w_u8(packet + 21, uv[1]); w_u8(packet + 29, uv[3]); w_u8(packet + 12, uv[0]);
        depth = ((sint32)r_u32(particles + 8) >> 1) + 256;
        if ((sint32)depth < 2500) {
            for (j = 0; j != 3; ++j) w_u32(packet + 8 + 8 * j, draft_gte_read(12 + j));
            slot = r_u32(0x8007184Cu) + 4 * depth;
            w_u32(packet, (r_u32(packet) & 0xFF000000u) | (r_u32(slot) & 0xFFFFFFu));
            w_u32(slot, (r_u32(slot) & 0xFF000000u) | (packet & 0xFFFFFFu)); packet += 32;
        }
    }
    w_u32(0x80071680u, packet); return 0;
}

static void b04_read_local(void *destination, uint32 size)
{
    sub_8004DD18(draft_local_address(destination, size), size);
}

static void b04_remap_primitive(uint32 primitive, uint32 kind, const uint16 *textures, uint32 invalidate)
{
    uint32 flags = primitive + 3, texture, palette, previous, index;
    if (kind < 4) {
        switch (kind) {
        case 0: sub_80018E88(primitive); break;
        case 1: sub_80018E9C(primitive); break;
        case 2: sub_80018EB0(primitive); break;
        case 3: sub_80018EF4(primitive); break;
        }
        if (invalidate && (r_u8(flags) & 64)) {
            static const uint32 offsets[4] = {7, 9, 15, 21};
            w_u16(flags + offsets[kind], 0xFFFFu);
        }
        w_u8(flags, r_u8(flags) & 63u);
        return;
    }
    previous = r_u16(flags + 7); index = previous & 31u;
    texture = textures ? textures[index] : r_u16(0u - 2146733792u + 2 * index);
    w_u16(flags + 7, r_u16(0u - 2146767244u + 2 * texture) | (invalidate ? previous & 192u : 0));
    if (r_u8(0u - 2146696692u + texture) != 2) {
        palette = r_u8(0u - 2146764952u + 40 * texture + r_u16(flags + 3));
        w_u16(flags + 3, r_u16(0u - 2146696668u + 2 * palette));
    }
    if (invalidate && (r_u8(flags) & 64)) w_u16(flags + ((kind & 1) ? 21 : 19), 0xFFFFu);
    w_u8(flags, r_u8(flags) & (invalidate ? 60u : 252u));
    if (kind & 1) sub_80018F6C(primitive); else sub_80018F38(primitive);
    if (!invalidate) w_u8(flags, r_u8(flags) & 63u);
}

uint32 sub_8002B358(uint32 image)
{
    uint16 skip, count16; uint32 count, bytes, allocation, cursor, vertices, i, j, entry;
    uint32 result = sub_8004E0A0((uint16)image);
    static const uint32 stride[8] = {12, 16, 20, 28, 24, 28, 24, 28};
    static const uint32 fields[6] = {0u-2147018496u, 0u-2147018476u, 0u-2147018480u, 0u-2147018468u, 0u-2147018532u, 0u-2147018464u};
    if ((sint32)result < 0) return result;
    b04_read_local(&skip, 2); if (skip) sub_8004DE84(2u * skip);
    b04_read_local(&count, 4); allocation = sub_80011A98(4 * count);
    w_u32(0x80071924u, allocation); sub_8004DD18(allocation, 4 * count);
    b04_read_local(&bytes, 4); allocation = sub_80011A98(bytes);
    w_u32(0x800716A4u, allocation); sub_8004DD18(allocation, bytes);
    w_u16(0x1F800020u, 0); w_u16(0x1F800022u, 0); w_u16(0x1F800024u, 2048);
    sub_8005D138(0x1F800020u, 0x1F800000u); sub_8005CF68(0x1F800000u);
    cursor = allocation;
    for (i = 0; i != count; ++i) {
        uint32 vertex_count = r_u32(cursor + 24);
        vertices = cursor + 28;
        for (j = 0; j != vertex_count; ++j, vertices += 8) {
            sub_8005CDA8(vertices, 0x1F800028u);
            w_u16(vertices, 0u - r_u32(0x1F800028u)); w_u16(vertices + 2, r_u32(0x1F80002Cu)); w_u16(vertices + 4, r_u32(0x1F800030u));
        }
        cursor = vertices;
        while (r_u32(cursor) != 8) {
            uint32 header = r_u32(cursor), kind = header & 7u, n = header >> 16;
            cursor += 4;
            for (j = 0; j != n; ++j, cursor += stride[kind]) b04_remap_primitive(cursor, kind, 0, 1);
        }
        cursor += 4;
    }
    for (i = 0; i != 6; ++i) sub_8004DD18(fields[i], 4);
    sub_8004DD18(0x80071618u, 4); sub_8004DD18(0x80071644u, 4);
    bytes = 4 * r_u32(0x80071618u) * r_u32(0x80071644u); allocation = sub_80011A98(bytes);
    w_u32(0x800719B8u, allocation); sub_8004DD18(allocation, bytes);
    b04_read_local(&bytes, 4); bytes *= 2; allocation = sub_80011A98(bytes);
    w_u32(0x800717CCu, allocation); sub_8004DD18(allocation, bytes);
    b04_read_local(&count16, 2); allocation = sub_80011A98(8u * count16);
    w_u32(0x800717B8u, allocation); sub_8004DD18(allocation, 8u * count16);
    for (i = 0; i != count16; ++i) {
        entry = allocation + 8 * i; sub_8005CDA8(entry, 0x1F800028u);
        w_u16(entry, 0u - 4 * r_u32(0x1F800028u)); w_u16(entry + 2, 4 * r_u32(0x1F80002Cu)); w_u16(entry + 4, 4 * r_u32(0x1F800030u));
    }
    sub_8004E20C(); w_u32(0x80071580u, (uint32)-1000000); return (uint32)-1000000;
}

uint32 sub_80019BD4(uint32 image, uint32 slot, uint32 xscale, uint32 yscale, uint32 zscale, uint32 mode)
{
    uint16 textures[64], texture_count, unexpected, vertex_count, normal_count, ignored;
    uint32 record = 0x800B0120u + 56 * (uint16)slot, vertices, normals = 0, bytes, primitives, cursor, result, i, j, radius = 0;
    static const uint32 stride[8] = {12,16,20,28,24,28,24,28};
    uint32 scales[3] = {xscale, yscale, zscale};
    result = r_u32(record + 12); if (result) return result;
    result = sub_8004E0A0((uint16)image); if ((sint32)result < 0) return result;
    b04_read_local(&texture_count, 2);
    /* TODO: Malformed texture counts exceed the original local table */
    if (texture_count > 64) abort();
    if (texture_count) b04_read_local(textures, 2u * texture_count);
    b04_read_local(&unexpected, 2);
    if (unexpected) return draft_unknown_return("80019BD4 nullsub"); /* TODO: Empty callback return carrier */
    for (i = 0; i != texture_count; ++i) textures[i] = sub_800127C8(textures[i], 0xFFFFu);
    b04_read_local(&vertex_count, 2); vertices = sub_80011A98(8u * vertex_count);
    if (!vertices) return draft_unknown_return("80019BD4 allocation nullsub");
    w_u16(0x1F800020u, 0); w_u16(0x1F800022u, 0); w_u16(0x1F800024u, 2048);
    sub_8005D138(0x1F800020u, 0x1F800000u); sub_8005CF68(0x1F800000u);
    sub_8004DD18(vertices, 8u * vertex_count);
    for (i = 0; i != vertex_count; ++i) {
        uint32 vertex = vertices + 8 * i;
        sub_8005CDA8(vertex, 0x1F800028u);
        for (j = 0; j != 3; ++j) {
            sint32 product = (sint32)(scales[j] * r_u32(0x1F800028u + 4 * j));
            sint32 scaled = product / 128, component, magnitude;
            w_u32(0x1F800028u + 4 * j, scaled);
            component = (sint16)(j ? scaled : 0u - (uint32)scaled);
            w_u16(vertex + 2 * j, component);
            magnitude = component < 0 ? -component : component;
            if (radius < (uint32)magnitude) radius = magnitude;
        }
    }
    b04_read_local(&normal_count, 2);
    if (mode) {
        normals = sub_80011A98(8u * normal_count); sub_8004DD18(normals, 8u * normal_count);
        for (i = 0; i != normal_count; ++i) {
            uint32 normal = normals + 8 * i;
            sub_8005CDA8(normal, 0x1F800028u);
            w_u16(normal, 0u - 4 * r_u32(0x1F800028u)); w_u16(normal + 2, 4 * r_u32(0x1F80002Cu)); w_u16(normal + 4, 4 * r_u32(0x1F800030u));
        }
    } else if ((uint16)(8u * normal_count)) sub_8004DE84((uint16)(8u * normal_count));
    b04_read_local(&ignored, 2); b04_read_local(&bytes, 4);
    primitives = sub_80011A98(bytes); sub_8004DD18(primitives, bytes);
    /* TODO: Empty original callback has no host side effect */
    w_u32(record, vertices); w_u32(record + 4, normals); w_u32(record + 12, primitives);
    w_u32(record + 16, radius); w_u16(record + 52, 0); w_u32(record + 8, vertex_count);
    cursor = primitives;
    while (r_u32(cursor) != 8) {
        uint32 header = r_u32(cursor), kind = header & 7u, count = header >> 16;
        cursor += 4;
        /* TODO: Texture indices refer to the local remapping table; unspecified entries need input constraints */
        for (i = 0; i != count; ++i, cursor += stride[kind]) b04_remap_primitive(cursor, kind, textures, 0);
    }
    return (uint16)mode == 2 ? sub_80019000((uint16)slot) : 2;
}

uint32 sub_8004AD78(void)
{
    static const uint32 addresses[] = {
        0x800BF928u,0x800BF92Au,0x800BF92Cu,0x800BF92Eu,
        0x800AEA94u,0x800AEA8Cu,0x800AEA92u,0x800AEA9Cu,0x800AEA9Au,0x800AEA8Eu,0x800AEA90u,
        0x800BF938u,0x800AEA9Eu,0x800BF93Au,0x800AEAA0u,0x800BF93Cu,0x800AEAA2u,0x800BF93Eu};
    static const uint16 values[] = {1200,1200,1200,1200,11,7,7,7,65,8,8,1000,21,800,8,1000,21,800};
    static const uint32 locations[] = {0x800AFB1Cu,0x800AFB1Au,0x800AFB18u,0x800AFB24u,0x800AFB22u,0x800AFB20u,
        0x800AFB4Cu,0x800AFB4Au,0x800AFB48u,0x800AFB3Cu,0x800AFB3Au,0x800AFB38u,0x800AFB44u,0x800AFB42u,0x800AFB40u,0x800AFB54u,0x800AFB52u,0x800AFB50u};
    static const uint16 slots[] = {82,84,83,85,86,87,88,89,90,91,92};
    uint32 i;
    sub_800456A8(1,700);
    for (i = 0; i != 18; ++i) w_u16(addresses[i], values[i]);
    sub_8001EE9C();
    for (i = 0; i != 18; ++i) w_u16(locations[i], i < 6 ? 300 : 200);
    sub_8001EEE8(90,93,89,67,360,360,360,1,2);
    for (i = 0; i != 11; ++i) sub_80019BD4(108+i,slots[i],360,360,360,2);

    sub_8001F44C(119,0,67,400,400,400);
    sub_8001F44C(120,1,69,400,400,400);
    sub_80019648(82,300,300,300); sub_80019648(84,120,120,120); sub_80019648(83,120,120,120); sub_80019648(85,120,120,120);
    sub_80019648(87,300,300,100); sub_80019648(88,100,100,100); sub_80019648(89,200,200,200); sub_80019648(90,200,200,200);
    sub_80019648(91,100,100,100); return sub_80019648(86,100,100,100);
}

