
#include <string.h>
#include "private/canprot_p.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int canprot_tosend_add_frame(const canbus_frame_t* frame) {
    int _ret=1;
    register unsigned int i=0;
    
    if(!frame) goto _exit;
    if((!frame->dlc) || (frame->dlc>CANBUS_DATA_SIZE_MAX) ) goto _exit;
    if(canprot_tosend_frames_count_g==CANPROT_MAX_TOSEND_FRAMES) goto _exit;
    
    for(; i<CANPROT_MAX_TOSEND_FRAMES; i++) {
        if(canprot_tosend_frames_storage_g[i].idx==CANPROT_TOSEND_INVALID_IDX) break;
        
    }
    if(i==CANPROT_MAX_TOSEND_FRAMES) goto _exit;
    
    memcpy(&canprot_tosend_frames_storage_g[i].frame, frame, sizeof(canbus_frame_t));
    canprot_tosend_frames_storage_g[i].idx=i;    
    canprot_tosend_frames_list_g[canprot_tosend_frames_count_g] = &canprot_tosend_frames_storage_g[i];    
    canprot_tosend_frames_count_g++;
    
    // all is okay
    _ret=0;
    
_exit:    
    return _ret;
}