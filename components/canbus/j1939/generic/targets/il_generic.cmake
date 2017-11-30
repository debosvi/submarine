
## generation profile name.
## mandatory (generates library profile)
set(COMP_SRC_PROFILE "library")

## COMP_SRC_LIB_TYPE var must be set to either 'static', 'shared' or 'both'.
## mandatory
set(COMP_SRC_LIB_TYPE "static")

## COMP_SRC_LIB_NAME var must be set to library name (without prefix and extension).
## mandatory
set(COMP_SRC_LIB_NAME "j1939_il_generic")

## LOCAL_SRC_DIR_SUFFIX is the relative path prefix to append to component files directory in order to find source files to compile.
## optional but recommended
set(LOCAL_SRC_DIR_SUFFIX "src/il")

## LOCAL_SRC_FILES is the list of files to compile (do not use any absolute path, automatic appending is performed by complete makefiles scheme.
## mandatory
set(LOCAL_SRC_FILES 
    J1939_IL_priv.c
    J1939_IL_ctx_zero.c
    J1939_IL_periodic_zero.c
    J1939_IL_static_trf_elt_zero.c
    J1939_IL_start.c
    J1939_IL_stop.c
    J1939_IL_init_all.c
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
# set(COMP_SRC_LIB_DEPS_STATIC other_static_lib)

## COMP_SRC_LIB_DEPS_SHARED is the list of shared library dependencies (internal dependencies only).
## Be careful about system compatibility between static and shared libraries.
## optional
# set(COMP_SRC_LIB_DEPS_SHARED )


## COMP_EXT_LIB_DEPS is the list of external library dependencies.
## optional
# set(COMP_EXT_LIB_DEPS)