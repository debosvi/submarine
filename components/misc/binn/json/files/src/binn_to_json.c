
#include "private/json_p.h"

///////////////////////////////////////////////////////////////////////////////
static json_t* binn_to_json_int(const binn_type_t type, const binn_data_t const *data) {
    json_int_t value=0;
    switch(type) {
        case BINN_TYPE_INT8: value = data->vint8; break;
        case BINN_TYPE_UINT8: value = data->vuint8; break;
        case BINN_TYPE_INT16: value = data->vint16; break;
        case BINN_TYPE_UINT16: value = data->vuint16; break;
        case BINN_TYPE_INT32: value = data->vint32; break;
        case BINN_TYPE_UINT32: value = data->vuint32; break;
        case BINN_TYPE_INT64: value = data->vint64; break;
        case BINN_TYPE_UINT64: value = data->vuint64; break;
        
        default: 
            BINN_PRINT_ERROR("%s: type not allowed (%d)\n", __FUNCTION__, type);
            break;
    }
    return json_integer(value);
}

///////////////////////////////////////////////////////////////////////////////
static json_t* binn_to_json_complex(const binn_type_t type, const binn_t node) {
    binn_iter_t iter;
    json_t *value=0;
    char *key=0;
    unsigned int id=0;
    binn_t binn_value = BINN_INVALID;
    char tmp[16];
    
    switch(type) {
        case BINN_TYPE_LIST: 
            value = json_array();
            binn_list_foreach(node, binn_value) {
                BINN_PRINT_DEBUG("%s: loop list binn (%d)\n", __FUNCTION__, binn_value);
                json_array_append_new(value, binn_to_json(binn_value));
            }
            break;
            
        case BINN_TYPE_MAP: 
            value = json_object();
            binn_map_foreach(node, binn_value) {
                BINN_PRINT_DEBUG("%s: loop object binn (%d)\n", __FUNCTION__, binn_value);
                binn_map_get_id(binn_value, &id);
                BINN_PRINT_DEBUG("%s: id (%d)\n", __FUNCTION__, id);
                snprintf(tmp, 16, "%d", id);                
                json_object_set_new(value, tmp, binn_to_json(binn_value));
            }
            break;
            
        case BINN_TYPE_OBJECT: 
            value = json_object();
            binn_object_foreach(node, binn_value) {
                BINN_PRINT_DEBUG("%s: loop object binn (%d)\n", __FUNCTION__, binn_value);
                binn_object_get_key(binn_value, &key);
                BINN_PRINT_DEBUG("%s: key (%s)\n", __FUNCTION__, key);
                json_object_set_new(value, key, binn_to_json(binn_value));
            }
            break;
        
        default: 
            BINN_PRINT_ERROR("%s: type not allowed (%d)\n", __FUNCTION__, type);
            break;
    }
    return value;
}

///////////////////////////////////////////////////////////////////////////////
json_t* binn_to_json(const binn_t node) {
    binn_internal_t* p=0;
    json_t    *value=0;
    binn_type_t ltype=BINN_TYPE_INIT;
    unsigned int count=0;
    
    p = binn_get_internal(node);
    if(!p) goto exit;
    
    if(binn_is_valid(p, &ltype, &count)) goto exit;
    BINN_PRINT_DEBUG("%s: bin is valid, type(%d), count(%d)\n", __FUNCTION__, ltype, count);
    
    // binn_iter  iter;
    // binn   binn_value={0};
    // int    id;
    // char   key[256], *ptr;
    // double floatvalue;


    switch (p->type) {
        case BINN_TYPE_STRING:
  // case BINN_DATE:
  // case BINN_TIME:
  // case BINN_DATETIME:
  // case BINN_DECIMAL:
  // case BINN_XML:
  // case BINN_HTML:
  // case BINN_CSS:
  // case BINN_JSON:
  // case BINN_JAVASCRIPT:
            value = json_string(p->data.str.s);
            break;

  //case BINN_BLOB:
  //  value = json_string((char *)base->ptr);
  //  break;

        case BINN_TYPE_INT8: 
        case BINN_TYPE_UINT8: 
        case BINN_TYPE_INT16: 
        case BINN_TYPE_UINT16: 
        case BINN_TYPE_INT32: 
        case BINN_TYPE_UINT32: 
        case BINN_TYPE_INT64: 
        case BINN_TYPE_UINT64: 
            value=binn_to_json_int(p->type, &p->data);
            break;

  // case BINN_BOOL:
    // if (base->vbool)
      // value = json_true();
    // else
      // value = json_false();
    // break;

  // case BINN_FLOAT:
    // value = json_real(base->vfloat);
    // break;
  // case BINN_DOUBLE:
    // value = json_real(base->vdouble);
    // break;

  // case BINN_CURRENCYSTR:
    // ptr = (char *)base->ptr;
    // floatvalue = atof(ptr);
    // value = json_real(floatvalue);
    // break;

  // case BINN_OBJECT:
    // value = json_object();
    // binn_object_foreach(base, key, binn_value) {
      // json_object_set_new(value, key, binn_to_json_obj2(&binn_value));
    // }
    // break;

  // case BINN_MAP:
    // value = json_object();
    // binn_map_foreach(base, id, binn_value) {
// #ifdef _MSC_VER
      // itoa(id, key, 10);
// #else
      // snprintf(key, sizeof(key), "%d", id);
// #endif
      // json_object_set_new(value, key, binn_to_json_obj2(&binn_value));
    // }
    // break;

        case BINN_TYPE_LIST:
        case BINN_TYPE_MAP:
        case BINN_TYPE_OBJECT:
            value = binn_to_json_complex(p->type, node);
            break;

  // case BINN_NULL:
    // value = json_null();
    // break;

        default:
            BINN_PRINT_ERROR("%s: type not managed (%d)\n", __FUNCTION__, p->type);
            break;
    }

exit:    
    return value;
}