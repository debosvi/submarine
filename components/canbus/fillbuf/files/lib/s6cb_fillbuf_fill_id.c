/* ISC license. */

#include <string.h>

#include <private/fillbuf_p.h>

int s6cb_fillbuf_fill_id(const s6canbus_id_t id, const void* const buf, size_t offset, size_t size) {
    if(!size) return S6CANBUS_ERROR_INVAL;
    if(!buf) return S6CANBUS_ERROR_NULLPTR;
    int i=priv_s6cb_fillbuf_find_id(id);
    if(i<0) return S6CANBUS_ERROR_NOTFOUND;

    s6cb_fillbuf_data_t *p=&s6cb_fillbuf_storage_data.d[i];
    if(p->id!=id) return S6CANBUS_ERROR_INTERNAL;
    if(offset+size>p->size) return S6CANBUS_ERROR_OVERLAY;
    
#ifdef S6CANBUS_FILLBUF_CHECK_FILL_OVERLAY
    if(bitarray_firstset_skip (p->bits, S6CANBUS_FILLBUF_MAX_BUF_SIZE, offset)<(offset+size))
        return S6CANBUS_ERROR_OVERLAY;
#endif
    
    memcpy(p->buf+offset, buf, size);
    bitarray_setn(p->bits, offset, size);
    
    if(bitarray_countones(p->bits, S6CANBUS_FILLBUF_MAX_BUF_SIZE)>=p->size) 
        (*p->func)(p->id, p->own);
    
    return S6CANBUS_ERROR_NONE;
}
