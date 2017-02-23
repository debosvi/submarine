
#include "private/binn_p.h"

///////////////////////////////////////////////////////////////////////////////
int binn_is_valid(binn_internal_t *item, binn_type_t *ptype, unsigned int *pcount) {
    unsigned int count=0;
    binn_type_t type=BINN_TYPE_INIT;
  
    if(item->magic!=BINN_ITEM_MAGIC) goto invalid;
    
    type=item->type;
    
    switch(type) {
        case BINN_TYPE_LIST:
        case BINN_TYPE_MAP:
        case BINN_TYPE_OBJECT:
            count = gensetdyn_n(&item->data.container);
            break;
        case BINN_TYPE_INT8:
        case BINN_TYPE_UINT8:
        case BINN_TYPE_INT16:
        case BINN_TYPE_UINT16:
        case BINN_TYPE_INT32:
        case BINN_TYPE_UINT32:
        case BINN_TYPE_INT64:
        case BINN_TYPE_UINT64:
            count = 1;
            break;
            
        default:
            BINN_PRINT_DEBUG("%s: type not managed (%d)\n", __FUNCTION__, type);
            break;
    }

    if (ptype) (*ptype) = type;
    if (pcount) (*pcount) = count;
    return 0;

invalid:
    if (ptype) (*ptype) = type;
    if (pcount) (*pcount) = 0;
    return 1;
}