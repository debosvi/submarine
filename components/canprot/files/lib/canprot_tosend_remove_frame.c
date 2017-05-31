
#include <string.h>
#include "private/canprot_p.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int canprot_tosend_remove_frame(const unsigned int list_idx) {
    int _ret=1;
    register unsigned int idx=0;
    
    if(!canprot_tosend_frames_count_g) goto _exit;
    if(list_idx>(unsigned int)(canprot_tosend_frames_count_g-1)) goto _exit;    
    if(list_idx>CANPROT_MAX_TOSEND_FRAMES) goto _exit;    
    idx = canprot_tosend_frames_list_g[list_idx]->idx;
    if(idx>CANPROT_MAX_TOSEND_FRAMES) goto _exit;
       
    if(canprot_tosend_frames_count_g>1) {
        int sz=canprot_tosend_frames_count_g-idx-1;
        memcpy(&canprot_tosend_frames_list_g[list_idx], &canprot_tosend_frames_list_g[list_idx+1], sz*sizeof(canprot_tosend_t*));
    }
    canprot_tosend_frames_count_g--;
    canprot_tosend_frames_list_g[canprot_tosend_frames_count_g]=0;    
    
    // all is okay
    _ret=0;
    
_exit:    
    return _ret;
}