
#include <s6canbus/canmsg.h>

#include <skalibs/bytestr.h>

int s6canmsg_ack(s6canmsg_buf_t* const b, const size_t n) {
    if(!b) return 0;
    if(n>b->m) return 0;
    size_t r=((b->p+n>b->n) ? (size_t)(b->n-b->p) : (n));
    b->p+=r;
    return r;
}
