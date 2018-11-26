
###############################################################################
set(COMP_SRC_PROFILE "library")

set(COMP_SRC_LIB_TYPE "both")
set(COMP_SRC_LIB_NAME "binn")

set(COMP_EXT_LIB_DEPS skarnet)

###############################################################################
set(LOCAL_SRC_DIR_SUFFIX src)

set(LOCAL_SRC_FILES
    binn_add_value_from_key.c
    binn_add_value_from_id.c
    binn_add_value_from_pos.c
    binn_blob.c
    binn_copy_value.c
    binn_create.c
    binn_free.c
    binn_get_value.c
    binn_get_value_from_key.c
    binn_get_value_from_id.c
    binn_get_value_from_pos.c
    binn_init.c
    binn_internal.c
    binn_is_valid.c
    binn_list.c
    binn_list_add_item.c
    binn_list_get_item.c
    binn_map.c
    binn_map_add_item.c
    binn_map_get_item.c
    binn_map_get_id.c
    binn_new.c
    binn_object.c
    binn_object_add_item.c
    binn_object_get_item.c
    binn_object_get_key.c
    binn_search_for_id.c
    binn_search_for_key.c
    binn_search_for_pos.c
    binn_string.c
    binn_term.c
    binn_to_blob.c
    binn_to_string.c
    
    ## iterations
    binn_iter_init.c
    binn_all_next.c
)

###############################################################################
set(LOCAL_GEN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/gen)
include(${CMAKE_CURRENT_LIST_DIR}/gen_macros.add)

GEN_BINN_ALL_XXX("int8"      "int8_t"    "BINN_TYPE_INT8")
GEN_BINN_ALL_XXX("uint8"     "uint8_t"   "BINN_TYPE_UINT8")
GEN_BINN_ALL_XXX("int16"     "int16_t"   "BINN_TYPE_INT16")
GEN_BINN_ALL_XXX("uint16"    "uint16_t"  "BINN_TYPE_UINT16")
GEN_BINN_ALL_XXX("int32"     "int32_t"   "BINN_TYPE_INT32")
GEN_BINN_ALL_XXX("uint32"    "uint32_t"  "BINN_TYPE_UINT32")
GEN_BINN_ALL_XXX("int64"     "int64_t"   "BINN_TYPE_INT64")
GEN_BINN_ALL_XXX("uint64"    "uint64_t"  "BINN_TYPE_UINT64")
GEN_BINN_ALL_XXX("float"     "float"     "BINN_TYPE_FLOAT")
GEN_BINN_ALL_XXX("double"    "double"    "BINN_TYPE_DOUBLE")
GEN_BINN_ALL_XXX("bool"      "char"      "BINN_TYPE_BOOL")

file(GLOB_RECURSE LOCAL_GEN_FILES ${LOCAL_GEN_DIR}/*.c)
set(LOCAL_SRC_FILES_ADDED ${LOCAL_GEN_FILES})

# BOZ_INSTALL_ITEM_WITH_PREFIX(binn "binn")
