#include "psx.h"
#include "xport.h"

uint32 sub_80022B24(uint32 matrix)
{
    uint32 result = r_u8(0x800715E4);
    if (result)
        return result;
    if (matrix && matrix != r_u32(0x80071994))
        return 1;
    w_u8(0x800715E4, 1);
    w_u8(0x800716EC, matrix == 0);
    result = r_u16(0x800718E0);
    w_u16(0x80071654, result);
    return result;
}
