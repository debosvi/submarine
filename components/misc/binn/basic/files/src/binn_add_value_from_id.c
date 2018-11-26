
#include "private/binn_p.h"

///////////////////////////////////////////////////////////////////////////////
int binn_add_value_from_id(binn_internal_t* p, const unsigned int id, const binn_t item) {
    int _ret=1;
    binn_internal_t *p2=0;
    binn_t *elem=0;
    unsigned int nc=0;
           
    if(!p) goto exit;
    p2 = binn_get_internal(item);
    if(!p2) goto exit;
	p2->id=id;
    
    BINN_PRINT_DEBUG("%s: internal(%p), item(%d)\n", __FUNCTION__, p, item);
	
    if(!gensetdyn_new(&p->data.container, &nc)) {
        BINN_PRINT_ERROR("%s: no more space (container)\n", __FUNCTION__);
        goto exit;
    }   

    elem=GENSETDYN_P(binn_t, &p->data.container, nc);
    BINN_PRINT_DEBUG("%s: value added in pos (%d)\n", __FUNCTION__, nc);
	(*elem)=item;
    _ret=0;
        
exit:
    if(_ret) {
        BINN_PRINT_ERROR("%s: unable to find id(%d)\n", __FUNCTION__, id);
    }
    return _ret;
}