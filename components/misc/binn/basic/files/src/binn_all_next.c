
#include "private/binn_p.h"

///////////////////////////////////////////////////////////////////////////////
int binn_all_next(binn_iter_t *iter, binn_t *node, const binn_type_t type) {
    int _ret=1;
    binn_t *elem=0;    
    
    BINN_PRINT_DEBUG("%s: iter(%p), node(%p)\n", __FUNCTION__, iter, node);
    
    if(!iter) goto exit;
    if(!node) goto exit;
    if(iter->type != type) goto exit;
    if(iter->current >= iter->count) goto exit;
    
    elem=GENSETDYN_P(binn_t, &iter->data->container, iter->current);
    (*node)=(*elem);
    iter->current++;
      
    _ret=0;

exit:
    if(_ret) {
        BINN_PRINT_DEBUG("%s: unable get next node\n", __FUNCTION__);
    }
    return _ret;
}