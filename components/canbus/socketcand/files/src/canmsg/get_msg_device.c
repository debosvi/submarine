
#include "private/canmsg_p.h"

///////////////////////////////////////////////////////////////////////////////
char* get_msg_device(binn_t head) {
    char *p=0;
    binn_t dev=BINN_INVALID;
    
    if(head==BINN_INVALID) return p;
    
    binn_object_get_item(head, "device", &dev);
    binn_to_string(dev, &p);
    
    return p;
}
