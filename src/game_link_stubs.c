#include "psx.h"
#include <stdlib.h>

#define XPORT_LINK_STUB(symbol, address, image) \
    uint32 symbol() \
    { \
        FUNCTION_MARKER(address, image); \
        abort(); \
        return 0; \
    }

XPORT_LINK_STUB(sub_80063E20, 0x80063E20u, "SLES_007.30")
XPORT_LINK_STUB(sub_8006841C, 0x8006841Cu, "SLES_007.30")
