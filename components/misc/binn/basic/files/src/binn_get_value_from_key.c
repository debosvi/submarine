
#include "private/binn_p.h"

typedef struct {
    char *key;
    binn_t elem;
} sid_stuff_t;

///////////////////////////////////////////////////////////////////////////////
static int binn_get_value_from_key_iter_func(char *item, void *stuff) {
    int _ret=1;
    binn_t *elem=(binn_t*)item;
    sid_stuff_t* owned = (sid_stuff_t*)stuff;
    binn_internal_t* p=binn_get_internal(*elem);  
    BINN_PRINT_DEBUG("%s: ids, expected (%s), current(%s)\n", __FUNCTION__, owned->key, p->key);     
    if(!strcmp(p->key, owned->key)) { 
        BINN_PRINT_DEBUG("%s: match keys (%s)\n", __FUNCTION__, p->key);   
        owned->elem=(*elem);
        _ret=0;
    }    
    return _ret;
}

///////////////////////////////////////////////////////////////////////////////
int binn_get_value_from_key(const binn_t node, const char const *key, binn_t *item) {
    int _ret=1;
    binn_internal_t* p=0;
    sid_stuff_t stuff = { .elem=BINN_INVALID, .key=(char*)key };
           
    p = binn_get_internal(node);
    if(!p) goto exit;
    
    BINN_PRINT_DEBUG("%s: key(%s)\n", __FUNCTION__, key);
    
    if(!key) goto exit;    
    
    gensetdyn_iter(&p->data.container, binn_get_value_from_key_iter_func, &stuff);
        
	if(stuff.elem!=BINN_INVALID) {        
		(*item) = stuff.elem;            
		_ret=0;
	}
	else {
		BINN_PRINT_ERROR("%s: no elem found for key (%s)\n", __FUNCTION__, key);
	}
        
exit:
    if(_ret) {
        BINN_PRINT_ERROR("%s: unable to find key(%s)\n", __FUNCTION__, key);
    }
    return _ret;
}