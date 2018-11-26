
#ifndef SHARED_BINN_H
#define SHARED_BINN_H

#include <skalibs/gensetdyn.h>

typedef enum {
    BINN_TYPE_LIST=0,
    BINN_TYPE_MAP,
    BINN_TYPE_OBJECT,

    BINN_TYPE_NULL,
    BINN_TYPE_TRUE,
    BINN_TYPE_FALSE,
    BINN_TYPE_BOOL,

    BINN_TYPE_UINT8,
    BINN_TYPE_INT8,
    BINN_TYPE_UINT16,
    BINN_TYPE_INT16,
    BINN_TYPE_UINT32,
    BINN_TYPE_INT32,
    BINN_TYPE_UINT64,
    BINN_TYPE_INT64,

    BINN_TYPE_STRING,
    BINN_TYPE_FLOAT,
    BINN_TYPE_DOUBLE,
    
    BINN_TYPE_BLOB,
    BINN_TYPE_COUNT,
    BINN_TYPE_INIT=255
} binn_type_t;

typedef union {
    stralloc		str;   // used for blob and string
    gensetdyn       container;  // storage type is 'binn_t', used for list, map and object
    
    // integers
    int8_t      vint8;
    int16_t     vint16;
    int32_t     vint32;
    int64_t     vint64;
    uint8_t     vuint8;
    uint16_t    vuint16;
    uint32_t    vuint32;
    uint64_t    vuint64;

    // decimals
    float       vfloat;
    double      vdouble;
    
    //
    char        vbool;
} binn_data_t;
#define BINN_DATA_ZERO  { .vdouble=0.0f }

typedef struct {
    int             magic;
    binn_type_t     type; 
    char*           key;
    unsigned int    id;
    binn_data_t     data;
} binn_internal_t;
#define BINN_INTERNAL_ZERO  { .magic=0, .type=BINN_TYPE_INIT, .key=0, .id=0, .data=BINN_DATA_ZERO }
extern const binn_internal_t binn_internal_zero;

extern binn_internal_t* binn_get_internal(binn_t node);

extern int binn_is_valid(binn_internal_t *item, binn_type_t *ptype, unsigned int *pcount);

extern int binn_object_get_key(const binn_t node, char **key);
extern int binn_map_get_id(const binn_t node, unsigned int *id);

// iterations
typedef struct {
    binn_data_t *data;
    binn_type_t type;
    int   count;
    int   current;
} binn_iter_t;
#define BINN_ITER_ZERO { .data=0, .type=BINN_INVALID, .count=0, .current=0 }
extern const binn_iter_t binn_iter_zero;

extern int binn_iter_init(binn_iter_t *iter, const binn_t node, const binn_type_t type);

extern int binn_all_next(binn_iter_t *iter, binn_t *node, const binn_type_t type);
extern int binn_map_next(binn_iter_t *iter, binn_t *node, const binn_type_t type);
extern int binn_object_next(binn_iter_t *iter, binn_t *node, const binn_type_t type);


#define binn_list_foreach(list, value)              \
    binn_iter_init(&iter, list, BINN_TYPE_LIST);    \
    while (!binn_all_next(&iter, &value, BINN_TYPE_LIST))

#define binn_map_foreach(map, value)                \
    binn_iter_init(&iter, map, BINN_TYPE_MAP);      \
    while (!binn_all_next(&iter, &value, BINN_TYPE_MAP))

#define binn_object_foreach(obj, value)             \
    binn_iter_init(&iter, obj, BINN_TYPE_OBJECT);   \
    while (!binn_all_next(&iter, &value, BINN_TYPE_OBJECT))

// debug

// #define __DEBUG__
#ifdef __DEBUG__
#define BINN_PRINT_DEBUG(...)   fprintf(stderr, __VA_ARGS__)
#else
#define BINN_PRINT_DEBUG(...)
#endif

#define BINN_PRINT_ERROR(...)   fprintf(stderr, __VA_ARGS__)

#endif // SHARED_BINN_H
