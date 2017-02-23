
#include "private/binn_p.h"

///////////////////////////////////////////////////////////////////////////////
void binn_init(void) {
    if(!binn_initialized) {
	BINN_PRINT_DEBUG("%s: initialize\n", __FUNCTION__);
        gensetdyn_init (&binn_storage_g, sizeof(binn_internal_t), 16, 3, 8) ;
        binn_initialized=1;
    }
}