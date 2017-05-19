
#include "private/data_multiplexer.h"


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
uint8_t dm_compute_mask_shift8(const uint8_t lsb, const uint8_t size, const uint8_t shift) {
    uint8_t mask=0;
    uint8_t pos=0;
    uint8_t sz=0;
    
    if(lsb<size) goto _exit;
    if((lsb>>3)<shift) goto _exit;
    
    // pos=
    
    
_exit:
    return mask;
}
