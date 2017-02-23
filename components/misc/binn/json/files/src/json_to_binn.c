
#include "private/json_p.h"

#define MAX_CHUNK_SIZE  (16)

typedef struct {
    const char *data;
    size_t off;
    size_t cap;
    char delim;
} binn_source_t;

///////////////////////////////////////////////////////////////////////////////
static size_t binn_reader_cb(void *buf, size_t buflen, void *arg) {
    binn_source_t *s = (binn_source_t*)arg;
    char *p=(char*)buf;
    char inc=1;
    size_t lg=0;
    
    BINN_PRINT_DEBUG("%s: buf(%p), len(%d)\n", __FUNCTION__, buf, buflen);
    
    if( s->off >= s->cap) return 0;
    if( s->off && (p[s->off-1] ==']')) return 0;
    if( s->off && (p[s->off-1] =='}')) return 0;
    
    // search for start delimiter
    if(!s->delim) {
        p=(char*)s->data;
        while((size_t)(p-(char*)s->data)<s->cap) {
            if(((*p)==']') || ((*p)=='}')) break;   
            if(((*p)=='{') || ((*p)=='[')) {
                s->delim=(*p);
                break;
            }
            p++;
        }
    }
    if(!s->delim) {
        BINN_PRINT_ERROR("%s: JSON not contains any start delimiter\n", __FUNCTION__);
        return 0;
    }

    // search for end delimiter
    if(!p)
        p=(char*)s->data;
    else p++;
    
    while((size_t)(p-(char*)s->data)<s->cap) {
        if((s->delim=='{') && ((*p)=='{')) ++inc;
        if((s->delim=='[') && ((*p)=='[')) ++inc;
        if((s->delim=='{') && ((*p)=='}')) --inc;
        if((s->delim=='[') && ((*p)==']')) --inc;
        p++;        
        if(!inc) break;
    }
    
    if(inc) {
        BINN_PRINT_ERROR("%s: JSON not contains any stop delimiter\n", __FUNCTION__);
        return 0;
    }
    
    lg=p-s->data;
    lg=(buflen>lg?lg:buflen);
    
    if (lg > s->cap - s->off)
        lg = s->cap - s->off;
    if (lg > 0) {
        memcpy(buf, s->data + s->off, lg);
        s->off += lg;
        fprintf(stderr, "%s: buffer(%s)\n", __PRETTY_FUNCTION__, (char*)buf);
        return lg;
    } else {
        return 0;
    }
}

///////////////////////////////////////////////////////////////////////////////
binn_t json_obj_to_binn(json_t *base) {
    binn_t head=BINN_INVALID;
    json_t  *value=0;

    switch (json_typeof(base)) {
        case JSON_OBJECT:
        {
            const char *key=0;
            head = binn_object();
            json_object_foreach(base, key, value) {
                if(binn_object_add_item(head, key, json_obj_to_binn(value))) break;
            }
        }
            break;

        case JSON_ARRAY:
        {
            unsigned int i=0;
            size_t  count=json_array_size(base);
            head = binn_list();
            for (i = 0; i < (unsigned int)count; i++) {
                value = json_array_get(base, i);
                if(binn_list_add_item(head, json_obj_to_binn(value))) break;
            }
        }
            break;

        case JSON_STRING:
            head = binn_string(json_string_value(base));
            break;

        case JSON_INTEGER:
            head = binn_int64(json_integer_value(base));
            break;

        case JSON_REAL:
            head = binn_double(json_real_value(base));
            break;

        case JSON_TRUE:
            head = binn_bool(1);
            break;

        case JSON_FALSE:
            head = binn_bool(0);
            break;

        // case JSON_NULL:
            // return binn_null();
            // break;

        default:
            BINN_PRINT_ERROR("%s: JSON type not yet managed (%d)\n", __FUNCTION__, json_typeof(base));
            break;
    }

    return head;
}

///////////////////////////////////////////////////////////////////////////////
int json_to_binn(const char const *json, binn_t *head) {
    int _ret=-1;
    json_t *base=0;
    binn_t h=BINN_INVALID;
    binn_source_t source;
    json_error_t error;
    
    if(!json || !head) goto exit;
    
    source.data = json;
    source.cap=strlen(json);
    source.off=0;
    source.delim=0;
    
    base = json_load_callback(binn_reader_cb, &source, 0, &error);
    if(!base) {
        if(source.off) _ret=-2;
        goto exit;
    }

    h = json_obj_to_binn(base);
    json_decref(base);

    (*head)=h;
    _ret=source.off;
    
exit:
    if(_ret<0) 
        (*head)=BINN_INVALID;
    return _ret;
}