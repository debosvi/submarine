
#include <stdio.h>

#include <binn/json.h>

#include "private/canmsg_p.h"

///////////////////////////////////////////////////////////////////////////////
char* build_can_frame(struct can_frame *frame) {
    char tmp[10];
    char *p=0;
    
    binn_t head=binn_object();
    binn_t data=binn_list();
    binn_object_add_item(head, "cmd", binn_string("send"));
    
    if(frame->can_id & CAN_EFF_FLAG) {
        sprintf(tmp, "%08X", frame->can_id & CAN_EFF_MASK);
    } 
    else {
        sprintf(tmp, "%03X", frame->can_id & CAN_SFF_MASK);
    }
    binn_object_add_item(head, "id", binn_string(tmp));
    binn_object_add_item(head, "dlc", binn_uint8(frame->can_dlc));
    
    for(int i=0; i<frame->can_dlc; i++) {
        sprintf(tmp, "%02x", frame->data[i]);
        binn_list_add_item(data, binn_string(tmp));
    }
    binn_object_add_item(head, "data", data);

    p=binn_to_json_str(head);
    binn_free(head);
    
    return p;
}
