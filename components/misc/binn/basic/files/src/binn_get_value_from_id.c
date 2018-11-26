
#include "private/binn_p.h"

typedef struct {
    unsigned int id;
    binn_t elem;
} sid_stuff_t;

///////////////////////////////////////////////////////////////////////////////
static int binn_get_value_from_id_iter_func(char *item, void *stuff) {
    int _ret=1;
    binn_t *elem=(binn_t*)item;
    sid_stuff_t* owned = (sid_stuff_t*)stuff;
    binn_internal_t* p=binn_get_internal(*elem);  
    BINN_PRINT_DEBUG("%s: ids, expected (%d), current(%d)\n", __FUNCTION__, owned->id, p->id);    
    if(p->id == owned->id) { 
        BINN_PRINT_DEBUG("%s: match ids (%d)\n", __FUNCTION__, p->id);   
        owned->elem=(*elem);
        _ret=0;
    }    
    return _ret;
}

///////////////////////////////////////////////////////////////////////////////
int binn_get_value_from_id(binn_t node, const unsigned int id, binn_t *item) {
    int _ret=1;
    binn_internal_t* p=0;
    sid_stuff_t stuff = { .elem=BINN_INVALID, .id=id };
           
    p = binn_get_internal(node);
    if(!p) goto exit;
    
    BINN_PRINT_DEBUG("%s: id(%d)\n", __FUNCTION__, id);
    
    gensetdyn_iter(&p->data.container, binn_get_value_from_id_iter_func, &stuff);
        
	if(stuff.elem!=BINN_INVALID) {        
		(*item) = stuff.elem;            
		_ret=0;
	}
	else {
		BINN_PRINT_ERROR("%s: no elem found for id (%d)\n", __FUNCTION__, id);
	}
    
exit:
    if(_ret) {
        BINN_PRINT_ERROR("%s: unable to find id(%d)\n", __FUNCTION__, id);
    }
    return _ret;
}