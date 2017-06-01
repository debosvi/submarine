
#include <string.h>
#include "private/canprot_p.h"

#define ARBITRARY_LOOP_ORDER_MAX (2*CANPROT_MAX_TOSEND_FRAMES)

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int canprot_tosend_add_frame(const canbus_frame_t* frame) {
    int _ret=1;
    register unsigned int i=0;
    
    if(!frame) goto _exit;
    if((!frame->dlc) || (frame->dlc>CANBUS_DATA_SIZE_MAX) ) goto _exit;
    if(canprot_tosend_run_g.count==CANPROT_MAX_TOSEND_FRAMES) goto _exit;
    
    for(; i<CANPROT_MAX_TOSEND_FRAMES; i++) {
        if(canprot_tosend_frames_storage_g[i].order==CANPROT_TOSEND_INVALID_ORDER) break;
        
    }
    if(i==CANPROT_MAX_TOSEND_FRAMES) goto _exit;
    
    // set all fileds in storage frame
    memcpy(&canprot_tosend_frames_storage_g[i].frame, frame, sizeof(canbus_frame_t));
    canprot_tosend_frames_storage_g[i].order=canprot_tosend_run_g.n_order;
    
    // update run var
    if(canprot_tosend_run_g.next==CANPROT_TOSEND_RUN_INVALID_NEXT)
        canprot_tosend_run_g.next=i;    
    canprot_tosend_run_g.count++;
    canprot_tosend_run_g.n_order=(canprot_tosend_run_g.n_order+1)%ARBITRARY_LOOP_ORDER_MAX;
    
    // all is okay
    _ret=0;
    
_exit:    
    return _ret;
}