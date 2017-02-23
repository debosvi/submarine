
#include "private/binn_p.h"

typedef struct {
    char *key;
    binn_t binn;
} sid_stuff_t;

///////////////////////////////////////////////////////////////////////////////
static int binn_search_for_key_iter_func(char *item, void *stuff) {
    int _ret=1;
    binn_t *elem=(binn_t*)item;
    sid_stuff_t* owned = (sid_stuff_t*)stuff;
    char *k=owned->key;
    char *next=0;
    binn_internal_t* p=0;
    
    next=strchr(k, '.');
    if(next) (*next)=0;

    p=binn_get_internal(*elem);      
    if(!strcmp(p->key, owned->key)) { 
        if(next) return binn_search_for_key(*elem, next+1);          
        owned->binn=(*elem);
        _ret=0;
    }    
    return _ret;
}

///////////////////////////////////////////////////////////////////////////////
binn_t binn_search_for_key(binn_t node, const char const *key) {
    binn_t _ret=BINN_INVALID;
    binn_internal_t* p=0;
    sid_stuff_t stuff = { .binn=BINN_INVALID, .key=(char*)key };
            
    p = binn_get_internal(node);
    if(!p) goto exit;
    
    BINN_PRINT_DEBUG("%s: key (%s)\n", __FUNCTION__, key);
    
    if(!key) goto exit;

    gensetdyn_iter(&p->data.container, binn_search_for_key_iter_func, &stuff);
    
    if(stuff.binn!=BINN_INVALID)
        _ret=stuff.binn;
    
exit:
    if(_ret==BINN_INVALID) {
        BINN_PRINT_DEBUG("%s: unable to find key(%s)\n", __FUNCTION__, key);
    }
    return _ret;
}