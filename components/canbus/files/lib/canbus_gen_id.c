
#include <private/canbus_p.h>

canbus_addr_t canbus_gen_id(const canbus_addr_t source, const canbus_addr_t command) {
    canbus_addr_t _ret=(canbus_addr_t)-1;
    
    if(source<CANBUS_EQP_MIN) goto _exit;
    if(source>CANBUS_EQP_MAX) goto _exit;
    
    _ret=((command&CANBUS_CMD_MASK)<<CANBUS_CMD_SHIFT) + (source&CANBUS_EQP_MASK);
    
_exit:
    return _ret;
}