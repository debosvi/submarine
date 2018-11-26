
#include <s6canbus/canmsg.h>

#include <skalibs/bytestr.h>

int s6canmsg_init(s6canmsg_buf_t* const b, const char* const buf, const size_t max) {
    if(!b || !buf) return 0;
   
    b->p=0;
    b->m=max;
    b->n=0;
    b->x=(char*)buf;
    return 1;
}
