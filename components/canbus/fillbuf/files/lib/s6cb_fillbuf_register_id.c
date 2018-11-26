/* ISC license. */

#include <private/fillbuf_p.h>

int s6cb_fillbuf_register_id(const s6canbus_id_t id, const void* const buf, size_t size, const s6cb_fillbuf_fct func, void* own) {
    if(!buf) return S6CANBUS_ERROR_NULLPTR;
    if(s6cb_fillbuf_storage_data.n>=S6CANBUS_FILLBUF_MAX_IDS) return S6CANBUS_ERROR_FULL;
    if(priv_s6cb_fillbuf_find_id(id)>=0) return S6CANBUS_ERROR_ALREADY;
    
    {
        register s6cb_fillbuf_data_t *p=&s6cb_fillbuf_storage_data.d[s6cb_fillbuf_storage_data.n];
        p->id=id;
        p->buf=(char*)buf;
        p->size=size;   
        p->func=func;   
        p->own=own;   
        memset(p->bits, 0, S6CANBUS_FILLBUF_MAX_BUF_BYTES);
    }
    
    s6cb_fillbuf_storage_data.n++;
    
    return S6CANBUS_ERROR_NONE;
}
