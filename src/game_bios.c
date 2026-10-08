#include "psx.h"

static uint32 card_pending_ports;

sint32 legend_bios_configure(sint32 events,sint32 threads,uint32 stack_top)
{
    uint32 descriptor,event_table,thread_slot,thread_table,index;
    if(events<=0||threads<=0||(uint32)events>256u||(uint32)threads>32u)return 0;
    /* SCPH-5502 SetConf BFC06750 uses signed displacements from A0010000 */
    w_u32(0xA000B948u,stack_top);w_u32(0xA000B944u,(uint32)events);w_u32(0xA000B940u,(uint32)threads);
    psx_bios_init_kernel_heap(0xA000E000u,0x2000u);
    descriptor=psx_bios_kernel_malloc(32u);
    if(!descriptor||descriptor==~0u)return 0;
    for(index=0;index<32u;index+=4u)w_u32(descriptor+index,0);
    w_u32(0xA0000100u,descriptor);w_u32(0xA0000104u,32);
    psx_bios_init_rcnt(0);psx_bios_init_default_interrupts(3);
    event_table=psx_bios_kernel_malloc(28u*(uint32)events);
    if(!event_table||event_table==~0u)return 0;
    w_u32(0xA0000124u,28u*(uint32)events);w_u32(0xA0000120u,event_table);
    for(index=0;index<(uint32)events;++index)w_u32(event_table+index*28u+4u,0);
    if(!psx_bios_bind_events(event_table,28u*(uint32)events))return 0;
    w_u32(0xA000010Cu,4);w_u32(0xA0000114u,192u*(uint32)threads);
    thread_slot=psx_bios_kernel_malloc(4);
    if(!thread_slot||thread_slot==~0u)return 0;
    thread_table=psx_bios_kernel_malloc(192u*(uint32)threads);
    if(!thread_table||thread_table==~0u)return 0;
    w_u32(thread_slot,0);
    for(index=0;index<(uint32)threads;++index)w_u32(thread_table+index*192u,0x1000u);
    w_u32(thread_table,0x4000u);w_u32(thread_slot,thread_table);
    w_u32(0xA0000108u,thread_slot);w_u32(0xA0000110u,thread_table);
    psx_bios_enqueue_timer_vblank(1);psx_bios_reset_entry_interrupt();
    return 1;
}

/* SCPH-5502 BFC0BFF0 completion shared by the card error callbacks */
static void game_bios_card_complete(uint32 port,uint32 specification)
{
    uint32 offset=port*4u;
    w_u32(0xA0009F20u+offset,0);
    w_u32(0xA0009F28u+offset,0);
    w_u32(0xA0009F30u+offset,0);
    DeliverEvent(0xF4000001u,specification);
}

static sint32 game_bios_card_event_service(void *context)
{
    uint32 port,pending=card_pending_ports;
    (void)context;
    card_pending_ports=0;
    for(port=0;port<2u;++port){
        if(!(pending&(1u<<port)))continue;
        /* Unmounted native ports have no serial responder, BIOS BFC14B58 timeout */
        w_u8(0x755Au,0);w_u32(0x74A4u,0);w_u32(0x7514u,0);w_u32(0x74C0u,0);
        w_u8(0x7568u+port,0x11u);w_u32(0x751Cu,port);
        DeliverEvent(0xF0000011u,0x100u);
        /* BIOS BFC0B54C dispatches the no-response completion callback */
        if(r_u32(0xA0009F20u+port*4u))game_bios_card_complete(port,0x100u);
    }
    return 1;
}

uint32 legend_bios_card_info(uint32 channel)
{
    sint32 port=(sint32)channel/16;
    uint32 offset,flag;
    if(port<0||port>1)return 0;
    offset=(uint32)port*4u;flag=0x7568u+(uint32)port;
    w_u32(0xA0009F20u+offset,1);
    if(!(r_u8(flag)&1u)){w_u32(0xA0009F20u+offset,0);return 0;}
    w_u32(0x7514u,0);w_u32(0x74A4u,0);w_u32(0x7500u+offset,channel);
    w_u32(0x7550u+offset,0);w_u32(0x7528u+offset,0x5B64u);w_u32(0x7508u+offset,0);
    w_u8(flag,8);card_pending_ports|=1u<<(uint32)port;
    return 1;
}

void legend_bios_init(void)
{
    card_pending_ports=0;
    psx_bios_bind_event_service(game_bios_card_event_service,NULL);
}

