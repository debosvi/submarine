
#include "private/canprot_p.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int canprot_tosend_remove_frame(const unsigned int idx) {
    int _ret=1;
    register unsigned int i=0;
    register unsigned int sav=0;
    
    if(!canprot_tosend_run_g.count) goto _exit;
    if(idx>=CANPROT_MAX_TOSEND_FRAMES) goto _exit;    
    if(canprot_tosend_frames_storage_g[idx].order==CANPROT_TOSEND_INVALID_ORDER) goto _exit;
    
    canprot_tosend_frames_storage_g[idx]=canprot_tosend_zero;
    canprot_tosend_run_g.count--;
    
    if(canprot_tosend_run_g.next==idx) {
        register unsigned int current=0;
        unsigned int min_order=(unsigned int)CANPROT_TOSEND_INVALID_ORDER ;  
        // canprot_tosend_run_g.next=0;
        for(; i<CANPROT_MAX_TOSEND_FRAMES; i++) {
            current=canprot_tosend_frames_storage_g[i].order;
            if( (current!=(unsigned int)CANPROT_TOSEND_INVALID_ORDER) && 
                (current<min_order) ){
                min_order=current;
                sav=i;
            }        
        }
        canprot_tosend_run_g.next=sav;
    }
    
    // all is okay
    _ret=0;
    
_exit:    
    return _ret;
}