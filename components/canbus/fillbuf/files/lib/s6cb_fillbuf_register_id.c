/* ISC license. */

#include <private/fillbuf_p.h>

int s6cb_fillbuf_register_id(const s6canbus_id_t id, const char* const buf, size_t size) {
    if(!buf) return S6CANBUS_ERROR_NULLPTR;
    if(s6cb_fillbuf_storage_data.n>=S6CANBUS_FILLBUF_MAX_IDS) return S6CANBUS_ERROR_FULL;
    if(s6cb_fillbuf_find_id(id)) return S6CANBUS_ERROR_ALREADY;
    
    s6cb_fillbuf_storage_data.d[s6cb_fillbuf_storage_data.n].id=id;
    s6cb_fillbuf_storage_data.d[s6cb_fillbuf_storage_data.n].buf=(char*)buf;
    s6cb_fillbuf_storage_data.d[s6cb_fillbuf_storage_data.n].size=size;    
    
    return S6CANBUS_ERROR_NONE;
}
