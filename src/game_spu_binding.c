#include "psx.h"
#include "psx_spu.h"
#include <stdio.h>
#include <stdlib.h>

void xport_bind_native_spu_transfer(void)
{
    SpuNativeTransferGuestBinding binding;
    binding.requested_mode = 0x8006FDD4u;
    binding.normalized_mode = 0x8006FE60u;
    binding.address_units = 0x8006FE5Cu;
    binding.completion = 0x8006FE78u;
    binding.completion_callback = 0x8006FE7Cu;
    binding.source_address = 0x8006FE98u;
    binding.dma_blocks = 0x8006FE9Cu;
    binding.address_shift = r_u32(0x8006FE6Cu);
    if (binding.address_shift > 15u || !spu_bind_native_transfer_guest(&binding))
    {
        fprintf(stderr, "Legend native SPU transfer binding failed\n");
        abort();
    }
}
