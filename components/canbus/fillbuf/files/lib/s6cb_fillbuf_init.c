/* ISC license. */

#include <private/fillbuf_p.h>

int s6cb_fillbuf_init(void) {
    s6cb_fillbuf_storage_data = s6cb_fillbuf_storage_zero;
    return S6CANBUS_ERROR_NONE;
}
