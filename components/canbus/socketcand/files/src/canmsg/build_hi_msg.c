
#include <binn/json.h>

#include "private/canmsg_p.h"

///////////////////////////////////////////////////////////////////////////////
char* build_hi_msg(void) {
    char *p=0;
    
    binn_t head=binn_object();
    binn_object_add_item(head, "cmd", binn_string("hi"));

    p=binn_to_json_str(head);
    binn_free(head);
    
    return p;
}
