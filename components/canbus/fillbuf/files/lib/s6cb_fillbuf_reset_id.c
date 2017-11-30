/* ISC license. */

#include <string.h>

#include <private/fillbuf_p.h>

int s6cb_fillbuf_reset_id(const s6canbus_id_t id) {
    if(s6cb_fillbuf_storage_data.n<=0) return S6CANBUS_ERROR_EMPTY;
    int i=priv_s6cb_fillbuf_find_id(id);
    if(i<0) return S6CANBUS_ERROR_NOTFOUND;
    
    s6cb_fillbuf_data_t *p=&s6cb_fillbuf_storage_data.d[i];
    if(p->id!=id) return S6CANBUS_ERROR_INTERNAL;
    
    memset(p->buf, S6CANBUS_FILLBUF_RESET_PATTERN, p->size);
    return S6CANBUS_ERROR_NONE;
}
