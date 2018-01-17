
#include <s6canbus/canmsg.h>

#include <skalibs/bytestr.h>

int s6canmsg_rewind(s6canmsg_buf_t* const b) {
    if(!b) return 0;
    b->p=0;
    return 1;
}
