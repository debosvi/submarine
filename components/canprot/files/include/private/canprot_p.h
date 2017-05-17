
#ifndef __CANPROT_PRIV_H__
#define __CANPROT_PRIV_H__

#include <canprot/canprot.h>

// return -1 on error (limit reached), cont of message otherwise
extern int canprot_get_msgs_count(void);
// return -1 on error (limit reached), cont of message otherwise
extern int canprot_get_sigs_count(void);

// return 0 on success, 1 otherwise
extern int canprot_set_data_value(const canprot_idx_t msg_idx, const canprot_data_sz_t pos, const canprot_data_sz_t bits, const canbus_data_t* const buf);

#endif // __CANPROT_PRIV_H__