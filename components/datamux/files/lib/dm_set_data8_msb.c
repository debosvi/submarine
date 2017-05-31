
#include "private/datamux_p.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int dm_set_data8_msb(void* out, const uint16_t max, const uint8_t pos, const uint8_t size, const uint8_t* const in) {
    int _ret=DM_ERR_NO_ERROR;
    
    if(size>DM_INPUT_MAX_BITS) _ret=DM_ERR_BAD_PARAM;
    else if(pos>(max-size))
        _ret=DM_ERR_OVERLAP;
    else
        _ret=dm_set_data8_lsb(out, max, max-pos-size, size, in);
    
    return _ret;
}