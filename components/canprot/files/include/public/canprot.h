
#ifndef __CANPROT_H__
#define __CANPROT_H__

#include <canbus/canbus.h>

typedef uint16_t canprot_idx_t;
typedef uint8_t canprot_data_sz_t;

#define CANPROT_MSG_TYPE_RX     (1<<0)
#define CANPROT_MSG_TYPE_TX     (1<<1)

#define CANPROT_MSG_CYCLE_ONESHOT (1<<0)
#define CANPROT_MSG_CYCLE_CYCLIC (1<<1)

typedef struct {
    canbus_addr_t id;       // message identifier
    uint8_t type;           // message type
    uint8_t cycle;          // message cycle type
    uint8_t bytes;          // nb bytes length (must be less or equal to CANBUS_DATA_SIZE_MAX (see canbus header file)
    uint16_t ms;            // message cycle time in ms (only valid if cycle matches mask CANPROT_MSG_CYCLE_CYCLIC
} canprot_msg_t;
#define CANPROT_MSG_ZERO { .id=(canbus_addr_t)-1, .type=0, .cycle=0, .ms=0, .bytes=0}
extern const canprot_msg_t canprot_msg_zero;

typedef struct {
    const canprot_msg_t* msg;       // message vector reference
    const canbus_data_t* def;       // default value
    const canbus_data_t* init;      // init value
    canprot_data_sz_t def_sz;       // default value size (in bytes)  
    canprot_data_sz_t init_sz;      // default value size (in bytes)  
    canprot_data_sz_t pos;          // position in bits in message
    canprot_data_sz_t bits;         // bits size in message
} canprot_sig_t;
#define CANPROT_SIG_ZERO { .msg=0, .pos=0, .bits=0, .def=0, .init=0, .def_sz=0, .init_sz=0 }
extern const canprot_sig_t canprot_sig_zero;

typedef struct {
    canbus_data_t   data[CANBUS_DATA_SIZE_MAX];        // bits size in message
    
} canprot_msg_state_t;
#define CANPROT_MSG_STATE_ZERO { .data={0} }
extern const canprot_msg_state_t canprot_msg_state_zero;

// return 0 on success, 1 otherwise
extern int canprot_init(void);
// return 0 on success, 1 otherwise
extern int canprot_fini(void);

// return 0 on success, 1 otherwise
extern int canprot_set_default_value(const canprot_idx_t msg_idx);
// return 0 on success, 1 otherwise
extern int canprot_set_init_value(const canprot_idx_t msg_idx);
// return 0 on success, 1 otherwise
extern int canprot_set_signal_value(const canprot_idx_t sig_idx, const canbus_data_t* value);
// return 0 on success, 1 otherwise
extern int canprot_send_msg(const canprot_idx_t);

// application specific file part

extern const canprot_msg_t* canprot_msgs_decl_g[];              // all messages to manage, must end with NULL pointer
extern const canprot_sig_t* canprot_sigs_decl_g[];              // all signals to manage, must end with NULL pointer
extern canprot_msg_state_t canprot_msg_cur_g[];                  // all current messages state

#endif // __CANPROT_H__