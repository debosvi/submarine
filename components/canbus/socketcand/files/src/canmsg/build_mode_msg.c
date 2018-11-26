
#include <binn/json.h>

#include "private/canmsg_p.h"

///////////////////////////////////////////////////////////////////////////////
char* build_mode_msg(const canio_mode_t mode) {
    char *p=0;
    
    binn_t head=binn_object();
    binn_object_add_item(head, "cmd", binn_string("mode"));
    binn_object_add_item(head, "mode", binn_uint8(mode));

    p=binn_to_json_str(head);
    binn_free(head);
    
    return p;
}
