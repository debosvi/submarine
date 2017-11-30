/* ISC license. */

#include <string.h>

#include <private/fillbuf_p.h>

int s6cb_fillbuf_fill_id(const s6canbus_id_t id, const void* const buf, size_t offset, size_t size) {
    if(!buf) return S6CANBUS_ERROR_NULLPTR;
    int i=priv_s6cb_fillbuf_find_id(id);
    if(i<0) return S6CANBUS_ERROR_NOTFOUND;

    s6cb_fillbuf_data_t *p=&s6cb_fillbuf_storage_data.d[i];
    if(p->id!=id) return S6CANBUS_ERROR_INTERNAL;
    if(offset+size>=p->size) return S6CANBUS_ERROR_OVERLAY;
    
    memcpy(p->buf+offset, buf, size);
    return S6CANBUS_ERROR_NONE;
}
