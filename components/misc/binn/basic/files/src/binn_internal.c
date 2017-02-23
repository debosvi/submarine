
#include "private/binn_p.h"

///////////////////////////////////////////////////////////////////////////////
gensetdyn binn_storage_g = BINN_STORAGE_ZERO;
const binn_internal_t binn_internal_zero = BINN_INTERNAL_ZERO;
int binn_initialized = 0;

///////////////////////////////////////////////////////////////////////////////
binn_internal_t* binn_get_internal(binn_t node) {
    binn_internal_t* _p=0;
    
    if(node==BINN_INVALID) goto exit;
    _p = GENSETDYN_P(binn_internal_t, &binn_storage_g, node);
    
exit:
    return _p;
}