
#include "private/canprot_p.h"
#include "private/data_multiplexer.h"

int canprot_set_data_value(const canprot_idx_t msg_idx, const unsigned int is_def) {
    int _ret=1;
    
    if(msg_idx<canprot_get_msgs_count()) {
        register canprot_msg_t* msg=(canprot_msg_t*)canprot_msgs_decl_g[msg_idx];
        register int s=0;
        int r=DM_ERR_NO_ERROR;

        
        for(; s<canprot_get_sigs_count(); s++) {
            register int i=0;
            uint64_t value=0;            
            
            if(msg!=canprot_sigs_decl_g[s]->msg) continue;
            
            for(; i<canprot_sigs_decl_g[s]->sz_val; i++) {
                value=value<<8;
                if(is_def) {
                    value+=canprot_sigs_decl_g[s]->def_val[i];
                }
                else {
                    value+=canprot_sigs_decl_g[s]->init_val[i];
                }
            }            
            
            r=dm_set_data_msb(&canprot_msg_cur_g[msg_idx].data[0], msg->bytes*8, canprot_sigs_decl_g[s]->pos, canprot_sigs_decl_g[s]->bits, value);
            if(r!=DM_ERR_NO_ERROR)
                break;
                    
        }
            
        // canprot_msg_current_g[msg_idx]->data[0]
    }

    return _ret;
}