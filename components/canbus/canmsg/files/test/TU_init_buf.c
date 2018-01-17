/* ISC license. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <skalibs/bytestr.h>
#include <s6canbus/canmsg.h>

#define BASIC_LENGTH   (8)
#define S6CANMSG_MSG1_LENGTH   (64)
char buf[S6CANMSG_MSG1_LENGTH];
const char* data1 = "012345678901234567890123456789";
const char* data2 = "45678901234567890123456";

s6canmsg_buf_t buf_msg1 = S6CANMSG_BUF_ZERO;

static void init_buf(char *b) {
    memset(b, '0', S6CANMSG_MSG1_LENGTH);
}

static void show_buf(char *b, size_t n) {
    if(b) {
        int i=0;
        fprintf(stderr, "buf: \n");
        for(; i<(int)n; i++) {
            if(i && !(i%8))
                fprintf(stderr, "\n");
            fprintf(stderr, "%c ", b[i]);
        }
        fprintf(stderr, "\n");
    }
}

static void try_buf(char *b, size_t n) {
    char tmp[BASIC_LENGTH];
    int r=0;
    int i=0;
    
    init_buf(buf);  
        
    r=s6canmsg_init(&buf_msg1, buf, S6CANMSG_MSG1_LENGTH);
    fprintf(stderr, "s6canmsg_init: r(%d)\n", r);
        
    r=s6canmsg_fill(&buf_msg1, b, n);
    fprintf(stderr, "s6canmsg_fill: r(%d)\n", r);
    
    show_buf(buf, S6CANMSG_MSG1_LENGTH);
    
    while(1) {
        r=s6canmsg_next(&buf_msg1, tmp, BASIC_LENGTH);
        fprintf(stderr, "\n%d: s6canmsg_next: r(%d)\n", i, r);
        if(!r) break;
    
        show_buf(tmp, r);
        
        r=s6canmsg_ack(&buf_msg1, BASIC_LENGTH);
        fprintf(stderr, "%d: s6canmsg_ack: r(%d)\n", i, r);

        i++;
    }
    
    r=s6canmsg_rewind(&buf_msg1);
    fprintf(stderr, "%d: s6canmsg_rewind: r(%d)\n", i, r);

}

int main (void) {

    
	try_buf((char*)data1, str_len(data1));
	try_buf((char*)data2, str_len(data2));
    
    return 0;
}
