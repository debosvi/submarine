
#include "private/binn_p.h"

///////////////////////////////////////////////////////////////////////////////
int binn_add_value_from_pos(binn_internal_t* p, const binn_t item) {
    int _ret=1;
    binn_internal_t *p2=0;
    binn_t *elem=0;
    unsigned int nc=0;
           
    if(!p) goto exit;
    p2 = binn_get_internal(item);
    if(!p2) goto exit;
    
    BINN_PRINT_DEBUG("%s: internal(%p), item(%d)\n", __FUNCTION__, p, item);
	
    if(!gensetdyn_new(&p->data.container, &nc)) {
        BINN_PRINT_ERROR("%s: no more space (container)\n", __FUNCTION__);
        goto exit;
    }   

    elem=GENSETDYN_P(binn_t, &p->data.container, nc);
    BINN_PRINT_DEBUG("%s: value added in pos (%d)\n", __FUNCTION__, nc);
	p2->id=nc;
	(*elem)=item;
    _ret=0;
        
exit:
    if(_ret) {
        BINN_PRINT_ERROR("%s: unable add new position\n", __FUNCTION__);
    }
    return _ret;
}