
#include "private/canprot_p.h"

#define ALL_MSGS_LIMIT  (64)
#define ALL_SIGS_LIMIT  (64*ALL_MSGS_LIMIT)

static int canprot_prev_msgs_count_g=-1;
extern int canprot_get_msgs_count(void) {
    register int c=0;
    
    if(canprot_prev_msgs_count_g>=0) goto _exit;
    
    for(; c<ALL_MSGS_LIMIT; c++) {
        if(!canprot_msgs_decl_g[c]) { 
            // not useful since NULL terminated list
            // c++;
            break;
        }        
    }
    if(c>=ALL_MSGS_LIMIT)
        c=-1;
    else canprot_prev_msgs_count_g=c;
    
_exit:
    return canprot_prev_msgs_count_g;    
}

static int canprot_prev_sigs_count_g=-1;
extern int canprot_get_sigs_count(void) {
    register int c=0;
    
    if(canprot_prev_sigs_count_g>=0) goto _exit;
    
    for(; c<ALL_SIGS_LIMIT; c++) {
        if(!canprot_sigs_decl_g[c]) { 
            // not useful since NULL terminated list
            // c++;
            break;
        }        
    }
    if(c>=ALL_SIGS_LIMIT)
        c=-1;
    else canprot_prev_sigs_count_g=c;
    
_exit:
    return canprot_prev_sigs_count_g;    
}