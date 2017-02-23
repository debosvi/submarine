
#include "private/binn_p.h"

const binn_iter_t binn_iter_zero = BINN_ITER_ZERO;

///////////////////////////////////////////////////////////////////////////////
int binn_iter_init(binn_iter_t *iter, const binn_t node, const binn_type_t type) {
    int _ret=1;
    binn_internal_t* p=0;
    binn_type_t ltype=BINN_TYPE_INIT;
    unsigned int count=0;
    
    if(!iter) goto exit;
    
    (*iter) = binn_iter_zero;
    
    p = binn_get_internal(node);
    if(!p) goto exit;
    
    if(binn_is_valid(p, &ltype, &count)) goto exit;

    if (type != ltype) {
        BINN_PRINT_ERROR("%s: bad types, expected(%d), current(%d)\n", __FUNCTION__, type, ltype);
        goto exit;   
    }
      // iter->plimit = (unsigned char *)ptr + size - 1;
      // iter->pnext = (unsigned char *)ptr + header_size;
    iter->data=&p->data;
    iter->count = count;
    iter->current = 0;
    iter->type = type;    
      
    _ret=0;

exit:
    if(_ret) {
        BINN_PRINT_ERROR("%s: unable init iter\n", __FUNCTION__);
    }
    return _ret;
}