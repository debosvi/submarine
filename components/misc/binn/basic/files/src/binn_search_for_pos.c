
#include "private/binn_p.h"

typedef struct {
    unsigned int pos;
    binn_t binn;
} sid_stuff_t;

///////////////////////////////////////////////////////////////////////////////
static int binn_search_for_pos_iter_func(char *item, void *stuff) {
    int _ret=1;
    binn_t *elem=(binn_t*)item;
    BINN_PRINT_DEBUG("%s: elem(%d)\n", __FUNCTION__, *elem);    
    sid_stuff_t* owned = (sid_stuff_t*)stuff;
    binn_internal_t* p=binn_get_internal(*elem);  
    BINN_PRINT_DEBUG("%s: ids, expected (%d), current(%d)\n", __FUNCTION__, owned->pos, p->id);    
    if(p->id == owned->pos) { 
        BINN_PRINT_DEBUG("%s: match ids (%d)\n", __FUNCTION__, p->id);   
        owned->binn=(*elem);
        _ret=0;
    }    
    return _ret;
}

///////////////////////////////////////////////////////////////////////////////
binn_t binn_search_for_pos(binn_t node, const unsigned int pos) {
    binn_t _ret=BINN_INVALID;
    binn_internal_t* p=0;
    sid_stuff_t stuff = { .binn=BINN_INVALID, .pos=pos };
            
    p = binn_get_internal(node);
    if(!p) goto exit;
    
    BINN_PRINT_DEBUG("%s: pos (%d)\n", __FUNCTION__, pos);
    
    gensetdyn_iter(&p->data.container, binn_search_for_pos_iter_func, &stuff);
    
    if(stuff.binn!=BINN_INVALID)
        _ret=stuff.binn;
    
exit:
    if(_ret==BINN_INVALID) {
        BINN_PRINT_ERROR("%s: unable to find pos(%d)\n", __FUNCTION__, pos);
    }
    return _ret;
}