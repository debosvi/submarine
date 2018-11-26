/* ISC license. */

#ifndef __S6CANBUS_ASYNCIO_H__
#define __S6CANBUS_ASYNCIO_H__

#include <stdint.h>

typedef uint8_t s6cb_asyncio_id_t;
typedef uint16_t s6cb_asyncio_stamp_t;

typedef (*s6cb_asyncio_stamp_f)(const s6cb_asyncio_stamp_t now, s6cb_asyncio_t* const out, void* priv);
typedef (*s6cb_asyncio_buffer_f)(const s6cb_asyncio_id_t id, char* const frame, void* priv);

typedef struct {
    s6cb_asyncio_id_t id;
    s6cb_asyncio_stamp_t stamp;    
} s6cb_asyncio_t;

int s6cb_asyncio_get_stamp(const s6cb_asyncio_stamp_t now, s6cb_asyncio_stamp_f f, s6cb_asyncio_t* const out);
int s6cb_asyncio_get_buffer(const s6cb_asyncio_id_t id, s6cb_asyncio_buffer_f f, char* const frame);

#endif // __S6CANBUS_ASYNCIO_H__
