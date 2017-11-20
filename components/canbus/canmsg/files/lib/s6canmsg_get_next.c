
#include <s6canbus/s6canmsg.h>

#include <skalibs/bytestr.h>

int s6canmsg_get_next(s6canmsg_buf_t* const b, char* const buf, const size_t n) {
    if(!b || !buf) return 0;
    if(n>S6CANMSG_MAX_LENGTH) return 0;
    size_t r=((b->p+n>b->n) ? (size_t)(b->n-b->p) : (n));
    byte_copy(buf, r, b->x+b->p);
    return r;
}
