
#include "private/binn_p.h"

///////////////////////////////////////////////////////////////////////////////
static void binn_free_internal_storage(binn_internal_t* p) {
    register gensetdyn *container=0;
    binn_t *elem=0;
    unsigned int nelems=0;
    
    if(!p) return;
    
    container=&p->data.container;    
    nelems=gensetdyn_n(container);
    BINN_PRINT_DEBUG("%s: nb elems (%d)\n", __FUNCTION__, nelems);
    
    for(int i=0; i<(int)nelems; i++) {
        elem=GENSETDYN_P(binn_t, container, i);
        BINN_PRINT_DEBUG("%s: free elem (%d)\n", __FUNCTION__, *elem);
        binn_free(*elem);
    }  
    
    gensetdyn_free(container);
}

///////////////////////////////////////////////////////////////////////////////
void binn_free(binn_t item) {
    binn_internal_t* _p=0;
    
    if(item==BINN_INVALID) goto exit;
    
    
    _p = GENSETDYN_P(binn_internal_t, &binn_storage_g, item);
    if(!_p) goto exit;
    BINN_PRINT_DEBUG("%s: binn (%d), type(%d), key(%p)\n", __FUNCTION__, item, _p->type, _p->key);            

    // internal frees
    switch(_p->type) {
        case BINN_TYPE_LIST:
        case BINN_TYPE_MAP:
        case BINN_TYPE_OBJECT:
            binn_free_internal_storage(_p);   
            break;
            
        case BINN_TYPE_NULL:
        case BINN_TYPE_BOOL:
        case BINN_TYPE_TRUE:
        case BINN_TYPE_FALSE:
        case BINN_TYPE_UINT8:
        case BINN_TYPE_INT8:
        case BINN_TYPE_UINT16:
        case BINN_TYPE_INT16:
        case BINN_TYPE_UINT32:
        case BINN_TYPE_INT32:
        case BINN_TYPE_UINT64:
        case BINN_TYPE_INT64:
        case BINN_TYPE_FLOAT:
        case BINN_TYPE_DOUBLE:
            break;
            
        case BINN_TYPE_STRING:
        case BINN_TYPE_BLOB:
            stralloc_free(&_p->data.str);            
            break;
            
        default:
            BINN_PRINT_ERROR("%s: should not happen, type (%d)\n", __FUNCTION__, _p->type);   
            break;
    }
    
    
    // key free
    if(_p->key) {
        BINN_PRINT_DEBUG("%s: free key (%p)\n", __FUNCTION__, _p->key);            
        free(_p->key);
        _p->key=0;
    }

    // last reset
    (*_p)= binn_internal_zero;
    if(gensetdyn_delete (&binn_storage_g, item)) goto exit;
    

exit:
    return ;
}
