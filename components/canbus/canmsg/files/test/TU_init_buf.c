/* ISC license. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <s6canbus/s6canmsg.h>

#define BASIC_LENGTH   (8)
#define S6CANMSG_MSG1_LENGTH   (47)
char buf[S6CANMSG_MSG1_LENGTH];

s6canmsg_buf_t buf_msg1 = S6CANMSG_BUF_ZERO;

static void init_buf(void) {
    int i=0;
    for(; i<S6CANMSG_MSG1_LENGTH; i++) {
        buf[i] = '0' + rand()%10;
    }
}

static void show_buf(char *b, size_t n) {
    if(b) {
        int i=0;
        for(; i<n; i++) {
            if(i && !(i%8))
                fprintf(stderr, "\n");
            fprintf(stderr, "%c ", b[i]);
        }
        fprintf(stderr, "\n");
    }
}

int main (void) {
    char tmp[BASIC_LENGTH];
    srand(time(0));
    
    init_buf();  
    show_buf(buf, S6CANMSG_MSG1_LENGTH);
        
    int r=s6canmsg_init_buf(&buf_msg1, buf, S6CANMSG_MSG1_LENGTH);
    fprintf(stderr, "s6canmsg_init_buf: r(%d)\n", r);
    
    for(int i=0; i<7; i++) {
        r=s6canmsg_get_next(&buf_msg1, tmp, BASIC_LENGTH);
        fprintf(stderr, "%d: s6canmsg_get_next: r(%d)\n", i, r);
    
        show_buf(tmp, r);
        
        r=s6canmsg_ack_current(&buf_msg1, BASIC_LENGTH);
        fprintf(stderr, "%d: s6canmsg_ack_current: r(%d)\n", i, r);
    }
    
    return 0;
}
