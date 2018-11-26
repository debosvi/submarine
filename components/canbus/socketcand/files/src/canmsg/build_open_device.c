
#include <binn/json.h>

#include "private/canmsg_p.h"

///////////////////////////////////////////////////////////////////////////////
char* build_open_device(const char* const dname) {
    char *p=0;
    
    if(!dname) goto exit;
    
    binn_t head=binn_object();
    binn_object_add_item(head, "cmd", binn_string("open"));
    binn_object_add_item(head, "device", binn_string(dname));

    p=binn_to_json_str(head);
    binn_free(head);
    
exit:
    return p;
}