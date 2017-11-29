/* ISC license. */

#include <private/fillbuf_p.h>

int s6cb_fillbuf_find_id(const s6canbus_id_t id) {
    int _ret=-1;
    unsigned i=0;
    while(i<(unsigned)s6cb_fillbuf_storage_data.n) {
        if(s6cb_fillbuf_storage_data.d[i].id==id) { _ret=i; break; }
        i++;
    }
    return _ret;
}
