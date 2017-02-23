
#include "private/binn_p.h"

///////////////////////////////////////////////////////////////////////////////
binn_t binn_new(const binn_type_t type, const void const *ptr, const unsigned int size) {
    binn_t item=BINN_INVALID;
    unsigned int n=0;
	
	BINN_PRINT_DEBUG("%s: type(%d), ptr(%p), size(%d)\n", __FUNCTION__, type, ptr, size);
    
    if((type<0) || (type>=BINN_TYPE_COUNT)) goto exit;
    if(ptr && !size) goto exit;
    
    binn_init();
    
    if(!gensetdyn_new (&binn_storage_g, &n)) goto exit;
	BINN_PRINT_DEBUG("%s: new elem(%d)\n", __FUNCTION__, n);

    item=n;
    if(binn_create(item, type, ptr, size)) goto exit;
  
exit:
    return item;
}