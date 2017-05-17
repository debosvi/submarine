
#include <private/canbus_p.h>

#ifdef __USE_CANUDP
const char canbus_udp_addr[4] = { 0, 0, 0, 0 };
const char canbus_mcast_addr[4] = { 224, 0, 0, 1 };
const uint16_t canbus_udp_port = 4444;
#endif

const canbus_frame_t canbus_frame_zero = CANBUS_FRAME_ZERO;
