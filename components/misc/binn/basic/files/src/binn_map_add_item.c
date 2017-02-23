
#include "private/binn_p.h"

///////////////////////////////////////////////////////////////////////////////
int binn_map_add_item(binn_t map, const unsigned int id, const binn_t item) {
    int _ret=1;
    binn_internal_t* p=0;
    binn_type_t ltype=BINN_TYPE_INIT;
    unsigned int count=0;
    
    p = binn_get_internal(map);
    if(!p) goto exit;
    
    if(binn_is_valid(p, &ltype, &count)) goto exit;
    BINN_PRINT_DEBUG("%s: bin is valid, type(%d), count(%d)\n", __FUNCTION__, ltype, count);
    
    if(ltype!=BINN_TYPE_MAP) {
        BINN_PRINT_ERROR("%s: bad type, expected(%d), found(%d)!\n", __FUNCTION__, BINN_TYPE_OBJECT, ltype);
        goto exit;
    }    
	
	if(binn_search_for_id(map, id)!=BINN_INVALID) {
        BINN_PRINT_ERROR("%s: id already found!\n", __FUNCTION__);
        goto exit;
    }
    
    _ret=binn_add_value_from_id(p, id, item);
    
exit:
    if(_ret) {
        BINN_PRINT_ERROR("%s: unable to add element, binn(%d)!\n", __FUNCTION__, map);
    }
    return _ret;    
}