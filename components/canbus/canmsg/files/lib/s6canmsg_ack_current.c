
#include <s6canbus/canmsg.h>

#include <skalibs/bytestr.h>

int s6canmsg_ack_current(s6canmsg_buf_t* const b, const size_t n) {
    if(!b) return 0;
    if(n>S6CANMSG_MAX_LENGTH) return 0;
    size_t r=((b->p+n>b->n) ? (size_t)(b->n-b->p) : (n));
    b->p+=r;
    return r;
}
