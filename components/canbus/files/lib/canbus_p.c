
#include <private/canbus_p.h>

#ifdef __USE_CANUDP
const char canbus_udp_addr[4] = { 127, 0, 0, 1 };
const char canbus_mcast_addr[4] = { 224, 0, 0, 1 };
const uint16_t canbus_udp_port = 4444;
#endif

const canbus_msg_t canbus_msg_zero = CANBUS_MSG_ZERO;
