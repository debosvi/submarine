
#ifndef __CANPROT_PRIV_H__
#define __CANPROT_PRIV_H__

#include <canprot/canprot.h>
#include <dm/datamux.h>

#define CANPROT_MAX_TOSEND_FRAMES   (16)
#define CANPROT_TOSEND_INVALID_IDX  (-1)

typedef struct {
    canbus_frame_t  frame;
    char idx;
} canprot_tosend_t;
#define CANPROT_TOSEND_ZERO { .frame=CANBUS_FRAME_ZERO, .idx=CANPROT_TOSEND_INVALID_IDX }
extern const canprot_tosend_t canprot_tosend_zero;

extern canprot_tosend_t canprot_tosend_frames_storage_g[CANPROT_MAX_TOSEND_FRAMES];
extern canprot_tosend_t* canprot_tosend_frames_list_g[CANPROT_MAX_TOSEND_FRAMES];
extern uint8_t canprot_tosend_frames_count_g;

extern int canprot_tosend_add_frame(const canbus_frame_t* frame);
extern int canprot_tosend_remove_frame(const unsigned int list_idx);

// return -1 on error (limit reached), cont of message otherwise
extern int canprot_get_msgs_count(void);
// return -1 on error (limit reached), cont of message otherwise
extern int canprot_get_sigs_count(void);

// return 0 on success, 1 otherwise
extern int canprot_set_data_value(const canprot_idx_t msg_idx, const unsigned int is_def);

#endif // __CANPROT_PRIV_H__