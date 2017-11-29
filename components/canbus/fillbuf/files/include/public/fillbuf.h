/* ISC license. */

#ifndef __S6CANBUS_FILLBUF_H__
#define __S6CANBUS_FILLBUF_H__

#include <s6canbus/types.h>

#define S6CANBUS_FILLBUF_MAX_IDS    (16)

int s6cb_fillbuf_init(void);
int s6cb_fillbuf_fini(void);
int s6cb_fillbuf_register_id(const s6canbus_id_t id, const char* const buf, size_t size);
int s6cb_fillbuf_unregister_id(const s6canbus_id_t id);
int s6cb_fillbuf_reset_id(const s6canbus_id_t id);
int s6cb_fillbuf_fill_id(const s6canbus_id_t id, const char* const buf, size_t size);

#endif // __S6CANBUS_FILLBUF_H__
