
#ifndef __CANBUS_H__
#define __CANBUS_H__

#include <stdint.h>
#include <stdlib.h>

#define CANBUS_EQP_CCS      (1) // calculateur central
#define CANBUS_EQP_PWR      (2) // boitier de puissance
#define CANBUS_EQP_GVR1     (3) // governail arri�re 1
#define CANBUS_EQP_GVR2     (4) // governail arri�re 2 
#define CANBUS_EQP_INRT     (5) // centrale inertielle
#define CANBUS_EQP_GVRK     (6) // gouvernail du kiosque

#define CANBUS_ID_INRT_BASE    (0x0100)
#define CANBUS_ID_PWR_BASE     (0x1000)
#define CANBUS_ID_GVR_BASE     (0x2000)

#define CANBUS_ID_PWR_STATUS   (0)
#define CANBUS_ID_PWR_CDEALIM  (1)
#define CANBUS_ID_PWR_CRALIM   (2)

#define CANBUS_GEN_ID(base,id)  (base+id)

typedef uint32_t canbus_addr_t;

#define CANBUS_DATA_SIZE    (8)

typedef struct {
    canbus_addr_t   id;
    uint8_t data[CANBUS_DATA_SIZE];
    uint8_t dlc;    
} canbus_msg_t;
#define CANBUS_MSG_ZERO { .id=0xffffffff, .data={0}, .dlc=0 }
extern const canbus_msg_t canbus_msg_zero;

extern int canbus_open(const char* const device, const int use_stamp);
extern int canbus_close(const int fd);
extern int canbus_add_mask(const canbus_addr_t id, const canbus_addr_t mask);

extern int canbus_send_data(const int fd, const canbus_msg_t* msg);
extern int canbus_recv_data(const int fd, canbus_msg_t* msg);

extern uint32_t canbus_gen_id(const canbus_addr_t source, const canbus_addr_t command);

#endif // __CANBUS_H__