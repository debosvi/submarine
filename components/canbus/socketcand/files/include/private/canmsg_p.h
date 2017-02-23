
#ifndef __PRIVATE_CANMSG_H__
#define __PRIVATE_CANMSG_H__

#include <linux/can.h>
#include <binn/binn.h>
// #include <linux/can/bcm.h>
// #include <linux/can/error.h>
#include "daemon_p.h"

extern char* get_msg_cmd(binn_t head);
extern char* get_msg_device(binn_t head);
extern char* get_msg_status(binn_t head);
extern int get_msg_mode(binn_t head, canio_mode_t *mode);
extern int get_msg_frame(binn_t head, struct can_frame *frame);

extern char* build_hi_msg(void);
extern char* build_ok_msg(void);
extern char* build_nok_msg(void);
extern char* build_open_device(const char* const dname);
extern char* build_mode_msg(const canio_mode_t mode);
extern char* build_can_frame(struct can_frame *frame);


#endif // __PRIVATE_CANMSG_H__
