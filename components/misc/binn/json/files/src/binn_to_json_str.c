
#include "private/json_p.h"

///////////////////////////////////////////////////////////////////////////////
char* binn_to_json_str(const binn_t node) {
    json_t *json=0;
    char *ptr=0;
    json = binn_to_json(node);
    if(!json) goto exit;
    ptr = json_dumps(json, JSON_PRESERVE_ORDER);
    json_decref(json);
exit:    
    if(!json) {
        BINN_PRINT_ERROR("%s: no json generated\n", __FUNCTION__);
    }
    return ptr;
}