
## generation profile name.
## mandatory (generates library profile)
set(COMP_SRC_PROFILE "library")

## COMP_SRC_LIB_TYPE var must be set to either 'static', 'shared' or 'both'.
## mandatory
set(COMP_SRC_LIB_TYPE "static")

## COMP_SRC_LIB_NAME var must be set to library name (without prefix and extension).
## mandatory
set(COMP_SRC_LIB_NAME "canprot")

## LOCAL_SRC_DIR_SUFFIX is the relative path prefix to append to component files directory in order to find source files to compile.
## optional but recommended
set(LOCAL_SRC_DIR_SUFFIX lib)

## LOCAL_SRC_FILES is the list of files to compile (do not use any absolute path, automatic appending is performed by complete makefiles scheme.
## mandatory
set(LOCAL_SRC_FILES 
    # public APIs
    canprot_p.c
    canprot_zero.c
    canprot_init.c
    canprot_fini.c
    canprot_set_default_value.c
    canprot_set_init_value.c
    
    # private APIs
    canprot_set_data_value.c
    dm_set_data64_lsb.c
    dm_set_data64_msb.c
    dm_compute_mask8.c
    dm_compute_mask64.c
    dm_compute_mask_shift8.c
)

## LOCAL_SRC_FILES_ADDED is the list of files to compile with absolute path (useful if generated files are somewhere).
## optional
# set(LOCAL_SRC_FILES_ADDED <somewhere absolute>)

## COMP_SRC_LIB_DEPS is the list of library dependencies (internal dependencies only).
## Build system will decide which static or shared is recommended.
## optional
# set(COMP_SRC_LIB_DEPS other_lib)

## COMP_SRC_LIB_DEPS_STATIC is the list of static library dependencies (internal dependencies only).
## Be careful about system compatibility between static and shared libraries
## optional
set(COMP_SRC_LIB_DEPS_STATIC canbus)

## COMP_SRC_LIB_DEPS_SHARED is the list of shared library dependencies (internal dependencies only).
## Be careful about system compatibility between static and shared libraries.
## optional
# set(COMP_SRC_LIB_DEPS_SHARED other_shared_lib)


## COMP_EXT_LIB_DEPS is the list of external library dependencies.
## optional
# set(COMP_EXT_LIB_DEPS skarnet)

