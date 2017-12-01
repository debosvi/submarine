/* ISC license. */

#ifndef __S6CANBUS_FILLBUF_H__
#define __S6CANBUS_FILLBUF_H__

#include <s6canbus/types.h>

#if !defined(USE_FILLBUF_CONFIG_FILE)
    #define S6CANBUS_FILLBUF_MAX_IDS        (1)
    #define S6CANBUS_FILLBUF_RESET_PATTERN  (0xFF)
#endif

int s6cb_fillbuf_init(void);
int s6cb_fillbuf_fini(void);
#define s6cb_fillbuf_reset_all s6cb_fillbuf_init
int s6cb_fillbuf_register_id(const s6canbus_id_t id, const void* const buf, size_t size);
int s6cb_fillbuf_unregister_id(const s6canbus_id_t id);
int s6cb_fillbuf_reset_id(const s6canbus_id_t id);
int s6cb_fillbuf_fill_id(const s6canbus_id_t id, const void* const buf, size_t offset, size_t size);

#if defined(USE_FILLBUF_CONFIG_FILE)
#include "fillbuf-config.h"

#ifndef S6CANBUS_FILLBUF_MAX_IDS
#error "Custom FILLBUF config file must define S6CANBUS_FILLBUF_MAX_IDS"
#endif
#ifndef S6CANBUS_FILLBUF_RESET_PATTERN
#error "Custom FILLBUF config file must define S6CANBUS_FILLBUF_RESET_PATTERN"
#endif

#endif // defined USE_FILLBUF_CONFIG_FILE

#endif // __S6CANBUS_FILLBUF_H__
