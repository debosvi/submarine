
#include "private/J1939_OS_p.h"

///////////////////////////////////////////////////////////////////////////////
J1939_error_t J1939_OS_copymem(void* dest, const void* src, uint8_t lg) {
    J1939_error_t _ret=J1939_ERR_SUCCESS;
    uint8_t *ps=(uint8_t*)src;
    uint8_t *pd=(uint8_t*)dest;
    uint8_t i=0;
    
    if(!src || !dest) { _ret=J1939_ERR_NULLPTR; goto exit; }
    
    for(; i<lg; i++) {
        (*pd)=*(ps);
        pd++; ps++;
    }    
    
exit:
//     if(_ret!=J1939_ERR_SUCCESS) {
//     }
    return _ret;
}
