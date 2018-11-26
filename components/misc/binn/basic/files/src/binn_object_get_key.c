
#include "private/binn_p.h"

///////////////////////////////////////////////////////////////////////////////
int binn_object_get_key(const binn_t node, char **key) {
    int _ret=1;
    binn_internal_t* p=0;
    binn_type_t ltype=BINN_TYPE_INIT;
    unsigned int count=0;
    
    if(!key) goto exit;
    p = binn_get_internal(node);
    if(!p) goto exit;
    
    if(binn_is_valid(p, &ltype, &count)) goto exit;
    BINN_PRINT_DEBUG("%s: bin is valid, type(%d), count(%d)\n", __FUNCTION__, ltype, count);
    
    // if(ltype!=BINN_TYPE_OBJECT) {
        // BINN_PRINT_ERROR("%s: bad type, expected(%d), current(%d)\n", __FUNCTION__, BINN_TYPE_OBJECT, ltype);
        // goto exit;
    // }
    
    (*key)=p->key;
    _ret=0;

exit:
    if(_ret) {
        BINN_PRINT_ERROR("%s: unable get next node\n", __FUNCTION__);
    }
    return _ret;
}