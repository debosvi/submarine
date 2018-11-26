
#include "private/binn_p.h"

///////////////////////////////////////////////////////////////////////////////
int binn_object_get_item(binn_t object, const char const *key, binn_t *item) {
    int _ret=1;
    binn_internal_t* p=0;
    binn_type_t ltype=BINN_TYPE_INIT;
    unsigned int count=0;
    
    BINN_PRINT_DEBUG("%s: object (%d), key (%s), item (%p)\n", __FUNCTION__, object, key, item);
    
    p = binn_get_internal(object);
    if(!p) goto exit;
    
    if(binn_is_valid(p, &ltype, &count)) goto exit;
    BINN_PRINT_DEBUG("%s: bin is valid, type(%d), count(%d)\n", __FUNCTION__, ltype, count);
    
    if(ltype!=BINN_TYPE_OBJECT) {
        BINN_PRINT_ERROR("%s: bad type, expected(%d), found(%d)!\n", __FUNCTION__, BINN_TYPE_OBJECT, ltype);
        goto exit;
    }

    if(binn_search_for_key(object, key)==BINN_INVALID) {
        BINN_PRINT_ERROR("%s: key not found!\n", __FUNCTION__);
        goto exit;
    }
    
    if(binn_get_value_from_key(object, key, item)) {
        BINN_PRINT_ERROR("%s: unable to get value!\n", __FUNCTION__);
        goto exit;
    }
    
    _ret=0;    
    
exit:
    if(_ret) {
        BINN_PRINT_ERROR("%s: unable to get object, binn(%d), key(%s)!\n", __FUNCTION__, object, key);
    }
    return _ret;    
}