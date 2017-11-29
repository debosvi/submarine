/* ISC license. */

#include <private/fillbuf_p.h>

int s6cb_fillbuf_unregister_id(const s6canbus_id_t id) {
    if(s6cb_fillbuf_storage_data.n<=0) return S6CANBUS_ERROR_EMPTY;
    int i=s6cb_fillbuf_find_id(id);
    if(i<0) return S6CANBUS_ERROR_NOTFOUND;
    
    s6cb_fillbuf_storage_data.d[s6cb_fillbuf_storage_data.n] = s6cb_fillbuf_data_zero;    
    
    return S6CANBUS_ERROR_NONE;
}
