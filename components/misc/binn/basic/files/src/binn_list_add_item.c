
#include "private/binn_p.h"

///////////////////////////////////////////////////////////////////////////////
int binn_list_add_item(binn_t list, const binn_t item) {
    int _ret=1;
    binn_internal_t* p=0;
    binn_type_t ltype=BINN_TYPE_INIT;
    unsigned int count=0;
    
    p = binn_get_internal(list);
    if(!p) goto exit;
    
    if(binn_is_valid(p, &ltype, &count)) goto exit;
    BINN_PRINT_DEBUG("%s: bin is valid, type(%d), count(%d)\n", __FUNCTION__, ltype, count);
    
    if(ltype!=BINN_TYPE_LIST) {
        BINN_PRINT_ERROR("%s: bad type, expected(%d), found(%d)!\n", __FUNCTION__, BINN_TYPE_OBJECT, ltype);
        goto exit;
    }    
    
    _ret=binn_add_value_from_pos(p, item);
    
exit:
    if(_ret) {
        BINN_PRINT_ERROR("%s: unable to add element, binn(%d)!\n", __FUNCTION__, list);
    }
    return _ret;    
}