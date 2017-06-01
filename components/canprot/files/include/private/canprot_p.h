
#ifndef __CANPROT_PRIV_H__
#define __CANPROT_PRIV_H__

#include <canprot/canprot.h>
#include <dm/datamux.h>

#define CANPROT_MAX_TOSEND_FRAMES       (16)
#define CANPROT_TOSEND_INVALID_ORDER    (-1)

typedef struct {
    canbus_frame_t  frame;
    int order;
} canprot_tosend_t;
#define CANPROT_TOSEND_ZERO { .frame=CANBUS_FRAME_ZERO, .order=CANPROT_TOSEND_INVALID_ORDER }
extern const canprot_tosend_t canprot_tosend_zero;

extern canprot_tosend_t canprot_tosend_frames_storage_g[CANPROT_MAX_TOSEND_FRAMES];

#define CANPROT_TOSEND_RUN_INVALID_NEXT    ((unsigned int)-1)

typedef struct {
    unsigned int next;
    unsigned int count;
    unsigned int n_order;    
} canprot_tosend_run_t;
#define CANPROT_TOSEND_RUN_ZERO { .next=CANPROT_TOSEND_RUN_INVALID_NEXT, .count=0, .n_order=0 }
extern const canprot_tosend_run_t canprot_tosend_run_zero;

extern canprot_tosend_run_t canprot_tosend_run_g;

extern int canprot_tosend_add_frame(const canbus_frame_t* frame);
extern int canprot_tosend_remove_frame(const unsigned int idx);

// return -1 on error (limit reached), cont of message otherwise
extern int canprot_get_msgs_count(void);
// return -1 on error (limit reached), cont of message otherwise
extern int canprot_get_sigs_count(void);

// return 0 on success, 1 otherwise
extern int canprot_set_data_value(const canprot_idx_t msg_idx, const unsigned int is_def);

#endif // __CANPROT_PRIV_H__