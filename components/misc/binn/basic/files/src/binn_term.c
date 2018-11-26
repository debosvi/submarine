
#include "private/binn_p.h"

///////////////////////////////////////////////////////////////////////////////
void binn_term(void) {
    if(binn_initialized) {
        BINN_PRINT_DEBUG("%s: free\n", __FUNCTION__);
        gensetdyn_free(&binn_storage_g) ;
        binn_initialized=0;
    }
}
