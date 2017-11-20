
#include <s6canbus/s6canmsg.h>

#include <skalibs/bytestr.h>

int s6canmsg_init_buf(s6canmsg_buf_t* const b, const char* const buf, const size_t n) {
    if(!b || !buf) return 0;
    if(n>S6CANMSG_MAX_LENGTH) return 0;
    
    b->p=0;
    b->n=n;
    b->x=(char*)buf;
    return n;
}
