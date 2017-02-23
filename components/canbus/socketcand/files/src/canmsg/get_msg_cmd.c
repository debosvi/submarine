
#include "private/canmsg_p.h"

///////////////////////////////////////////////////////////////////////////////
char* get_msg_cmd(binn_t head) {
    char *p=0;
    binn_t cmd=BINN_INVALID;
    
    if(head==BINN_INVALID) return p;
    
    binn_object_get_item(head, "cmd", &cmd);
    binn_to_string(cmd, &p);
    
    return p;
}
