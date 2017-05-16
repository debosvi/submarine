
#ifndef __BDP_CAN_H__
#define __BDP_CAN_H__

#include <canbus/canbus.h>

void handle_send(const int fd, const unsigned idx);
void handle_read(const int fd);

void add_ongoing(const unsigned idx);

void set_msg_default(void);

int get_ongoing_nb(void);
int get_ongoing_less(void);

#endif // __BDP_CAN_H__
