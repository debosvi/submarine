/* ISC license. */

#ifndef __S6CANBUS_FILLBUF_PRIVATE_H__
#define __S6CANBUS_FILLBUF_PRIVATE_H__

#include <s6canbus/errors.h>
#include <s6canbus/fillbuf.h>

#include <skalibs/bitarray.h>

#define S6CANBUS_FILLBUF_MAX_BUF_SIZE   (64)
#define S6CANBUS_FILLBUF_MAX_BUF_BYTES  (S6CANBUS_FILLBUF_MAX_BUF_SIZE>>3)

typedef struct {
    void*               buf;
    void*               own;
    s6cb_fillbuf_fct    func;
    s6canbus_id_t       id;
    size_t              size;
    unsigned char       bits[S6CANBUS_FILLBUF_MAX_BUF_BYTES];
} s6cb_fillbuf_data_t;

#define S6CB_FILLBUF_DATA_ZERO   { .id=S6CANBUS_ID_INVALID, .buf=0, .size=0, .bits={0}, .func=0, .own=0 }
extern s6cb_fillbuf_data_t s6cb_fillbuf_data_zero;

typedef struct {
    size_t n;
    s6cb_fillbuf_data_t d[S6CANBUS_FILLBUF_MAX_IDS];
} s6cb_fillbuf_storage_t;

#define S6CB_FILLBUF_STORAGE_ZERO   { .n=0, .d={[0 ... S6CANBUS_FILLBUF_MAX_IDS-1]=S6CB_FILLBUF_DATA_ZERO} }
extern s6cb_fillbuf_storage_t s6cb_fillbuf_storage_zero;
extern s6cb_fillbuf_storage_t s6cb_fillbuf_storage_data;

// private functions
int priv_s6cb_fillbuf_find_id(const s6canbus_id_t id);

#endif // __S6CANBUS_FILLBUF_PRIVATE_H__
