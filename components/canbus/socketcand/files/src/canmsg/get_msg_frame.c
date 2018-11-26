
#include <stdio.h>
#include <stdlib.h>

#include "private/canmsg_p.h"

///////////////////////////////////////////////////////////////////////////////
int get_msg_frame(binn_t head, struct can_frame *frame) {
    int64_t i64=-1;
    int ret=-1;
    binn_t bm=BINN_INVALID;
    
    if((head==BINN_INVALID) || !frame) goto exit;
    
    memset(frame, 0, sizeof(struct can_frame));
    
    binn_object_get_item(head, "id", &bm);
    if(bm!=BINN_INVALID) {
        char* s=0;
        if(!binn_to_string(bm, &s)) {
            uint32_t val=0;
            sscanf(s, "%08X", &val);
            frame->can_id = val;
            if((val&CAN_SFF_MASK)!=val)
                frame->can_id |= CAN_EFF_FLAG;
            ret++;
        }
    }
    binn_object_get_item(head, "dlc", &bm);
    if(!binn_to_int64(bm, &i64)) {
        frame->can_dlc = i64;
        ret++;
    }
    binn_object_get_item(head, "data", &bm);
    if(bm!=BINN_INVALID) {
        binn_t bs=BINN_INVALID;
        char* s=0;
        for(int i=0; i<frame->can_dlc; i++) {
            binn_list_get_item(bm, i, &bs);
            binn_to_string(bs, &s);
            if(s) {
                unsigned int val=0;
                sscanf(s, "%02x", &val);
                frame->data[i] = val;
                ret++;            
            }
        }
    }    
    
exit:
    if((ret>=0) && (ret!= (1+frame->can_dlc)))
        ret=-1;
    else ret=0;
    
    return ret;
}
