
## generation profile name.
## mandatory (generates application)
set(COMP_SRC_PROFILE "application")

## COMP_SRC_APP_NAME var must be set to binary name.
## mandatory
set(COMP_SRC_APP_NAME "socketcand")

## LOCAL_SRC_DIR_SUFFIX is the relative path prefix to append to component files directory in order to find source files to compile.
## optional but recommended
set(LOCAL_SRC_DIR_SUFFIX src/daemon)

## LOCAL_SRC_FILES is the list of files to compile (do not use any absolute path, automatic appending is performed by complete makefiles scheme.
## mandatory
set(LOCAL_SRC_FILES 
    daemon.c
    determine_address.c
    determine_address_bcast.c
    init_server_fd.c
    init_bcast_fd.c
    init_sig_fd.c
    canio_add_remove_fd.c
    candev_add.c
    handle_signals.c
    handle_accept.c
    handle_client.c
    handle_bcast.c
    handle_candev.c
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
set(COMP_SRC_LIB_DEPS_STATIC
    canmsg
)

## COMP_SRC_LIB_DEPS_SHARED is the list of shared library dependencies (internal dependencies only).
## Be careful about system compatibility between static and shared libraries.
## optional
# set(COMP_SRC_LIB_DEPS_SHARED other_shared_lib)


## COMP_EXT_LIB_DEPS is the list of external library dependencies.
## optional
set(COMP_EXT_LIB_DEPS 
    )
