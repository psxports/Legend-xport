#include "psx.h"
#include "xport.h"
#include "game_draft_signatures.h"

void sub_8001A518(uint32 mesh)
{
    uint32 parent = r_u32(mesh + 96);
    if (parent) {
        sub_8005CDD8(parent + 32, mesh, mesh + 8);
        w_u32(mesh + 8, r_u32(mesh + 8) + r_u32(parent + 8));
        w_u32(mesh + 12, r_u32(mesh + 12) + r_u32(parent + 12));
        w_u32(mesh + 16, r_u32(mesh + 16) + r_u32(parent + 16));
    }
}

uint32 sub_8001A59C(uint32 mesh)
{
    uint32 parent = r_u32(mesh + 96), matrix, column, i;
    if (!parent) return parent + 32;
    matrix = parent + 32;
    for (i = 0; i < 5; ++i) draft_gte_control(i, r_u32(matrix + 4 * i));
    matrix = mesh + 32;
    for (column = 0; column < 3; ++column) {
        draft_gte_data(9, r_u16(matrix + 2 * column));
        draft_gte_data(10, r_u16(matrix + 6 + 2 * column));
        draft_gte_data(11, r_u16(matrix + 12 + 2 * column));
        draft_gte_command(0x49E012);
        w_u16(matrix + 2 * column, draft_gte_read(9));
        w_u16(matrix + 6 + 2 * column, draft_gte_read(10));
        w_u16(matrix + 12 + 2 * column, draft_gte_read(11));
    }
    return matrix;
}
