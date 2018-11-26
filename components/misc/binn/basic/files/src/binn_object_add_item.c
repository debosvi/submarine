
#include "private/binn_p.h"

///////////////////////////////////////////////////////////////////////////////
int binn_object_add_item(binn_t object, const char const *key, const binn_t item) {
    int _ret=1;
    binn_internal_t* p=0;
    binn_type_t ltype=BINN_TYPE_INIT;
    unsigned int count=0;
    
    p = binn_get_internal(object);
    if(!p) goto exit;
    
    if(binn_is_valid(p, &ltype, &count)) goto exit;
    BINN_PRINT_DEBUG("%s: bin is valid, type(%d), count(%d)\n", __FUNCTION__, ltype, count);
    
    if(ltype!=BINN_TYPE_OBJECT) {
        BINN_PRINT_ERROR("%s: bad type, expected(%d), found(%d)!\n", __FUNCTION__, BINN_TYPE_OBJECT, ltype);
        goto exit;
    }    
	
	if(binn_search_for_key(object, key)!=BINN_INVALID) {
        BINN_PRINT_ERROR("%s: key already found!\n", __FUNCTION__);
        goto exit;
    }
    
    _ret=binn_add_value_from_key(p, key, item);
    
exit:
    if(_ret) {
        BINN_PRINT_ERROR("%s: unable to add element, binn(%d)!\n", __FUNCTION__, object);
    }
    return _ret;    
}