
#ifndef __S6CANMSG_H__
#define __S6CANMSG_H__

#include <stdint.h>
#include <stddef.h>

#define S6CANMSG_MAX_LENGTH     (64)

typedef uint8_t s6canmsg_size_t;
typedef struct {
    char *x;
    s6canmsg_size_t p;
    s6canmsg_size_t n;
} s6canmsg_buf_t;   
#define S6CANMSG_BUF_ZERO   { .x=0, .p=0, .n=0 }
extern const s6canmsg_buf_t s6canmsg_buf_zero;

int s6canmsg_init_buf(s6canmsg_buf_t* const b, const char* const buf, const size_t n);
int s6canmsg_get_next(s6canmsg_buf_t* const b, char* const buf, const size_t n);
int s6canmsg_ack_current(s6canmsg_buf_t* const b, const size_t n);

#endif // __S6CANMSG_H__
