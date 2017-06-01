
#include "private/canprot_p.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int canprot_init(void) {
    int _ret=1;
    int nbm=0, nbs=0;
    
    nbm=canprot_get_msgs_count();
    if(nbm<=0) goto _exit;

    nbs=canprot_get_sigs_count();
    if(nbs<=0) goto _exit;
    
    {
        register int m=0;
        for(; m<nbm; m++) {
            canprot_msg_cur_g[m].frame->dlc=canprot_msgs_decl_g[m]->bytes;
            canprot_msg_cur_g[m].frame->id=canprot_msgs_decl_g[m]->id;            
            canprot_set_init_value(m);
        }
    }
    
    {
        register int i=0;
        for(; i<CANPROT_MAX_TOSEND_FRAMES; i++) {
            canprot_tosend_frames_storage_g[i] = canprot_tosend_zero;
        }
    }

    _ret=0;
    
_exit:    
    return _ret;
}