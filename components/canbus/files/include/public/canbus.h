
#ifndef __CANBUS_H__
#define __CANBUS_H__

#include <stdint.h>
#include <stdlib.h>

typedef uint32_t canbus_addr_t;
typedef uint8_t canbus_data_t;

#define CANBUS_DATA_SIZE_MAX    (8)

typedef struct {
    canbus_addr_t   id;
    canbus_data_t   data[CANBUS_DATA_SIZE_MAX];
    uint8_t dlc;    
} canbus_frame_t;
#define CANBUS_FRAME_ZERO { .id=(canbus_addr_t)-1, .data={0}, .dlc=0 }
extern const canbus_frame_t canbus_frame_zero;

extern int canbus_open(const char* const device, const int use_stamp);
extern int canbus_close(const int fd);
extern int canbus_add_mask(const canbus_addr_t id, const canbus_addr_t mask);

extern int canbus_send_data(const int fd, const canbus_frame_t* msg);
extern int canbus_recv_data(const int fd, canbus_frame_t* msg);

#endif // __CANBUS_H__