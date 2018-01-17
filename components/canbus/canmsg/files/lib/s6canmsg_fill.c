
#include <s6canbus/canmsg.h>

#include <skalibs/bytestr.h>

int s6canmsg_fill(s6canmsg_buf_t* const b, const char* const buf, const size_t n) {
    if(!b || !buf) return 0;
    if(n>b->m) return 0;
    b->p=0;
    b->n=n;
    byte_copy(b->x, n, buf);
    return n;
}
