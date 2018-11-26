
###############################################################################
set(COMP_SRC_PROFILE "library")

set(COMP_SRC_LIB_TYPE "both")
set(COMP_SRC_LIB_NAME "binn_json")

set(COMP_SRC_LIB_DEPS binn)
set(COMP_EXT_LIB_DEPS jansson)

###############################################################################
set(LOCAL_SRC_DIR_SUFFIX src)

set(LOCAL_SRC_FILES
    json_to_binn.c
    binn_to_json.c
    binn_to_json_str.c
)
