
#include <stdio.h>

#include <s6canbus/s6canbus.h>

int main(void) {
    int r=0;
    
    r=s6cb_fillbuf_init();
    if(r!=S6CANBUS_ERROR_NONE) {
        fprintf(stderr, "s6cb_fillbuf_init failed, err(%d)\n", r);
    }
    
    r=s6cb_fillbuf_fini();
    if(r!=S6CANBUS_ERROR_NONE) {
        fprintf(stderr, "s6cb_fillbuf_fini failed, err(%d)\n", r);
    }
    
    return 1;
}
