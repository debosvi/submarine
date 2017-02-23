
// TO ENABLE INLINE FUNCTIONS:
//   ON MSVC: enable the 'Inline Function Expansion' (/Ob2) compiler option, and maybe the
//            'Whole Program Optimitazion' (/GL), that requires the
//            'Link Time Code Generation' (/LTCG) linker option to be enabled too

#ifndef __BINN_H__
#define __BINN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

typedef int binn_t;
#define BINN_INVALID    ((binn_t)-1)

extern void binn_init(void);
extern void binn_term(void);

// --- GENERAL FUNCTIONS  ----------------------------------------------------------
extern binn_t binn_list(void);
extern binn_t binn_map(void);
extern binn_t binn_object(void);
extern binn_t binn_clone(const binn_t item);

extern void binn_free(binn_t item);

// --- ALLOCATION FUNCTIONS  ----------------------------------------------------------
typedef void* (*binn_malloc_f)(size_t);
typedef void* (*binn_realloc_f)(void*,size_t);
typedef void (*binn_free_f)(void*);

extern void binn_set_alloc_functions(binn_malloc_f bm, binn_realloc_f br, binn_free_f bf);

///////////////////////////////////////////////////////////////////////////////
////////////////////////// BASIC TYPES CONSTRUCTORS ///////////////////////////
///////////////////////////////////////////////////////////////////////////////
extern binn_t binn_int8(const int8_t value);
extern binn_t binn_int16(const int16_t value);
extern binn_t binn_int32(const int32_t value);
extern binn_t binn_int64(const int64_t value);
extern binn_t binn_uint8(const uint8_t value);
extern binn_t binn_uint16(const uint16_t value);
extern binn_t binn_uint32(const uint32_t value);
extern binn_t binn_uint64(const uint64_t value);
extern binn_t binn_float(const float value);
extern binn_t binn_double(const double value);
extern binn_t binn_bool(const char value);
extern binn_t binn_string(const char const *value);
extern binn_t binn_blob(const char const *value, const unsigned int size);

///////////////////////////////////////////////////////////////////////////////
////////////////////////// BASIC TYPES CONSTRUCTORS ///////////////////////////
///////////////////////////////////////////////////////////////////////////////
extern int binn_to_int8(const binn_t item, int8_t *pvalue);
extern int binn_to_int16(const binn_t item, int16_t *pvalue);
extern int binn_to_int32(const binn_t item, int32_t *pvalue);
extern int binn_to_int64(const binn_t item, int64_t *pvalue);
extern int binn_to_uint8(const binn_t item, uint8_t *pvalue);
extern int binn_to_uint16(const binn_t item, uint16_t *pvalue);
extern int binn_to_uint32(const binn_t item, uint32_t *pvalue);
extern int binn_to_uint64(const binn_t item, uint64_t *pvalue);
extern int binn_to_float(const binn_t item, float *pvalue);
extern int binn_to_double(const binn_t item, double *pvalue);
extern int binn_to_bool(const binn_t item, char *pvalue);
extern int binn_to_string(const binn_t item, char **pvalue);
extern int binn_to_blob(const binn_t item, char **pvalue, unsigned int *psize);

///////////////////////////////////////////////////////////////////////////////
///////////////////////////// WRITE ACCESSES //////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
extern int binn_list_add_item(binn_t list, const binn_t item);
//extern int binn_list_add_null(binn_t list);
extern int binn_map_add_item(binn_t map, const unsigned int id, const binn_t item);
//extern int binn_map_set_null(binn_t map, const int id);
extern int binn_object_add_item(binn_t object, const char const *key, const binn_t item);
//extern int binn_object_set_null(binn_t object, const char const *key);

///////////////////////////////////////////////////////////////////////////////
///////////////////////////// READ ACCESSES ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
extern int binn_list_get_item(binn_t list, const unsigned int pos, binn_t *item);
extern int binn_map_get_item(binn_t map, const unsigned int id, binn_t *item);
extern int binn_object_get_item(binn_t object, const char const *key, binn_t *item);

#ifdef __cplusplus
}
#endif

#endif //__BINN_H__
