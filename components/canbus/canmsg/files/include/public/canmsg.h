
#ifndef __S6CANMSG_H__
#define __S6CANMSG_H__

#include <stdint.h>
#include <stddef.h>

//#define S6CANMSG_MAX_LENGTH     (64)

typedef uint8_t s6canmsg_size_t;
typedef struct {
    char *x;
    s6canmsg_size_t p;
    s6canmsg_size_t m;
    s6canmsg_size_t n;
} s6canmsg_buf_t;   
#define S6CANMSG_BUF_ZERO   { .x=0, .p=0, .m=0, .n=0 }
extern const s6canmsg_buf_t s6canmsg_buf_zero;

#define S6CANMSG_BUF_INIT(x,m)  { .x=x, .p=0, .n=0, .m=m }

int s6canmsg_init(s6canmsg_buf_t* const b, const char* const buf, const size_t max);
int s6canmsg_next(s6canmsg_buf_t* const b, char* const buf, const size_t n);
int s6canmsg_ack(s6canmsg_buf_t* const b, const size_t n);
int s6canmsg_fill(s6canmsg_buf_t* const b, const char* const buf, const size_t n);
int s6canmsg_rewind(s6canmsg_buf_t* const b);

#define S6CANMSG_HAS_DATA(b)	((b)->p<(b)->n)

#endif // __S6CANMSG_H__
