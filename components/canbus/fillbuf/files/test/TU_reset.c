/* ISC license. */

#include <stdio.h>

#include <s6canbus/s6canbus.h>

#define MSG1_SIZE   12
s6canbus_id_t id1=0x1234;
char msg1[MSG1_SIZE];

int main(void) {
    int r=0;
    
    r=s6cb_fillbuf_init();
    if(r!=S6CANBUS_ERROR_NONE) {
        fprintf(stderr, "s6cb_fillbuf_init failed, err(%d)\n", r);
    }
    
    r=s6cb_fillbuf_register_id(id1, msg1, MSG1_SIZE);
    if(r!=S6CANBUS_ERROR_NONE) {
        fprintf(stderr, "s6cb_fillbuf_register_id failed, err(%d)\n", r);
    }
    
    r=s6cb_fillbuf_reset_id(id1);
    if(r!=S6CANBUS_ERROR_NONE) {
        fprintf(stderr, "s6cb_fillbuf_reset_id failed, err(%d)\n", r);
    }
    
    r=s6cb_fillbuf_fini();
    if(r!=S6CANBUS_ERROR_NONE) {
        fprintf(stderr, "s6cb_fillbuf_fini failed, err(%d)\n", r);
    }
    
    return 1;
}