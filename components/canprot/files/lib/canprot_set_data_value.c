
#include <private/canprot_p.h>

int canprot_set_data_value(const canprot_idx_t msg_idx, const canprot_data_sz_t pos, const canprot_data_sz_t bits, const canbus_data_t* const buf) {
    int _ret=1;
    
    if(buf && (msg_idx<canprot_get_msgs_count())) {
        memcpy(&canprot_msg_current_g[msg_idx]->data[0], &buf[0], 8);
        _ret=0;
    }

    return _ret;
}