
#include "private/canmsg_p.h"

///////////////////////////////////////////////////////////////////////////////
int get_msg_mode(binn_t head, canio_mode_t *mode) {
    int64_t imode=-1;
    int ret=-1;
    binn_t bm=BINN_INVALID;
    
    if((head==BINN_INVALID) || !mode) goto exit;
    
    binn_object_get_item(head, "mode", &bm);
    if(!binn_to_int64(bm, &imode)) {
        (*mode)=(canio_mode_t)imode;
        ret=0;
    }
    
exit:
    return ret;
}
