
#include <private/canprot_p.h>
#include <restricted/canprot_r.h>

int canprot_check_valid_decl(void) {
    int _ret=1;
    
    // check 'canprot_msgs_decl_g' non empty
    if(canprot_get_msgs_count()<=0) goto _exit;
    
    // check 'canprot_sigs_decl_g' non empty
    if(canprot_get_sigs_count()<=0) goto _exit;
    
    // check 'canprot_sigs_decl_g' bits valid in regards default value size
    {
        register int c=0;
        for(; c<canprot_get_sigs_count(); c++) {
            if((canprot_sigs_decl_g[c]->bits)>(8*canprot_sigs_decl_g[c]->def_sz)) goto _exit;
            if((canprot_sigs_decl_g[c]->bits)>(8*canprot_sigs_decl_g[c]->init_sz)) goto _exit;
        }
    }
    
    // check 'canprot_sigs_decl_g' bits sum valid in regards 'canprot_msgs_decl_g' total bits
    {
        register int m=0;
        for(; m<canprot_get_msgs_count(); m++) {
            register int c=0;
            int sum=0;
            for(; c<canprot_get_sigs_count(); c++) {
                if(canprot_sigs_decl_g[c]->msg==canprot_msgs_decl_g[m]) {
                    sum+=canprot_sigs_decl_g[c]->bits;
                }
            }
            
            if(sum>8*canprot_msgs_decl_g[m]->bytes) 
                goto _exit;
        }
    }
    
    // all is okay
    _ret=0;
    
_exit:    
    return _ret;
}