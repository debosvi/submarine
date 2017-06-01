
#include "private/canprot_p.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
canbus_frame_t* canprot_tosend_get_next(void) {
    if(canprot_tosend_run_g.next!=CANPROT_TOSEND_RUN_INVALID_NEXT)
        return &canprot_tosend_frames_storage_g[canprot_tosend_run_g.next].frame;
    
    return 0;
}