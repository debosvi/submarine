
#include "private/canprot_p.h"

int canprot_set_init_value(const canprot_idx_t msg_idx) {
    return canprot_set_data_value(msg_idx, 0);
}