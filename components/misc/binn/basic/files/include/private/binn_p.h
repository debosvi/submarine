
#ifndef PRIVATE_BINN_H
#define PRIVATE_BINN_H

#include <stdio.h>      // fprintf
#include <stdlib.h>     // free

#include <binn/binn.h>
#include <restricted/binn_r.h>

#define BINN_ITEM_MAGIC     ((int)0xA55A1234)

extern int binn_initialized;

extern gensetdyn binn_storage_g;
#define BINN_STORAGE_ZERO   GENSETDYN_ZERO 

typedef void (*binn_mem_free)(void*);

extern binn_type_t binn_type(binn_t node);

extern binn_t binn_search_for_key(const binn_t node, const char const *key);
extern binn_t binn_search_for_id(const binn_t node, const unsigned int id);
extern binn_t binn_search_for_pos(const binn_t node, const unsigned int pos);

extern int binn_add_value_from_key(binn_internal_t* p, const char const *key, const binn_t item);
extern int binn_add_value_from_id(binn_internal_t* p, const unsigned int id, const binn_t item);
extern int binn_add_value_from_pos(binn_internal_t* p, const binn_t item);

extern int binn_get_value_from_key(const binn_t node, const char const *key, binn_t *item);
extern int binn_get_value_from_id(const binn_t node, const unsigned int id, binn_t *item);
extern int binn_get_value_from_pos(binn_t node, const unsigned int pos, binn_t *item);

extern binn_t binn_new(const binn_type_t type, const void const *ptr, const unsigned int size);
extern int binn_create(const binn_t item, const binn_type_t type, const void const *ptr, const unsigned int size);
extern binn_t binn_value(const binn_type_t type, const void const *pvalue, const unsigned int size, binn_mem_free freefn);

// extern int binn_list_add(const binn_t list, const binn_type_t type, const void *pvalue, const unsigned int size);
// extern int binn_list_get(const binn_t list, const unsigned int pos, const binn_type_t type, void *pvalue, unsigned int *psize);
// extern int binn_map_get(const binn_t map, const unsigned int id, const binn_type_t type, void *pvalue, unsigned int *psize);
// extern int binn_map_set(const binn_t map, const unsigned int id, const binn_type_t type, const void const *pvalue, const unsigned int size);
// extern int binn_object_get(const binn_t obj, const char const *key, const binn_type_t type, void *pvalue, unsigned int *psize);
// extern int binn_object_set(const binn_t obj, const char const *key, const binn_type_t type, const void const *pvalue, const unsigned int size);

extern int binn_copy_value(const void const *psource, void *pdest, const binn_type_t type, const unsigned int size);
extern int binn_get_value(const void const *psource, void *pdest, const binn_type_t type);

#endif // PRIVATE_BINN_H
