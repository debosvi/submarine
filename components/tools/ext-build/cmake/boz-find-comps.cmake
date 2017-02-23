
include(${CMAKE_CURRENT_LIST_DIR}/boz-find-comp-gen.cmake)

macro(COMP_CHECK_VARS)
    if("${COMP_NAME}" STREQUAL "")
        message(SEND_ERROR "Unable to retreive component name (variable COMP_NAME)")
    endif()

    if("${COMP_HEADER_PREFIX}" STREQUAL "")
        message(AUTHOR_WARNING "Unable to retreive component header prefix at install step (variable COMP_HEADER_PREFIX)")
    endif()
endmacro()

macro (BOZ_COMP_FIND_APIS dir)
    message(STATUS "Find APIs directory in ${dir}")
    ## find PUBLIC include dir
    if(EXISTS "${dir}/include/public" AND IS_DIRECTORY "${dir}/include/public")
        file(GLOB ALL_PUBLIC "${dir}/include/public/*.h")
        if(NOT "${ALL_PUBLIC}" STREQUAL "")
            foreach(api ${ALL_PUBLIC})
                file(RELATIVE_PATH cp_file ${dir}/include/public ${api} )
                configure_file(
                    ${api}
                    ${GENERATED_INCLUDE_DIR}/public/${COMP_HEADER_PREFIX}/${cp_file}
                    @ONLY)
                    
                BOZ_INSTALL_HEADER(${COMP_HEADER_PREFIX}/${cp_file})
            endforeach()
        else()
            message(SEND_ERROR "Not any public API found in ${dir}")
        endif()       
    else()
        message(SEND_ERROR "Unable to find public API directory in ${dir}")
    endif()
    
    ## find RESTRICTED include dir
    if(EXISTS "${dir}/include/restricted" AND IS_DIRECTORY "${dir}/include/restricted")
        file(GLOB ALL_RESTRICTED "${dir}/include/restricted/*.h")
        if(NOT "${ALL_RESTRICTED}" STREQUAL "")
            foreach(api ${ALL_RESTRICTED})
                file(RELATIVE_PATH cp_file ${dir}/include/restricted ${api} )
                configure_file(
                    ${api}
                    ${GENERATED_INCLUDE_DIR}/restricted/${cp_file}
                    @ONLY)
            endforeach()
        else()
            message(AUTHOR_WARNING "Not any restricted API found in ${dir}")
        endif()       
    else()
        message(AUTHOR_WARNING "Unable to find restricted API directory in ${dir}")
    endif()
endmacro()

macro (BOZ_COMPS_FIND_ALL main_dir)
    message(STATUS "Find components from root directory: ${main_dir}")
    file(GLOB_RECURSE ALL_COMPS 
        RELATIVE ${main_dir}
        "${main_dir}/*/comp.cmake")
    message(STATUS "Components found from root directory: ${ALL_COMPS}")
    if(NOT "${ALL_COMPS}" STREQUAL "")
        foreach(comp ${ALL_COMPS})
            get_filename_component(comp_dir ${comp} DIRECTORY)
            get_filename_component(comp_dir2 ${comp_dir} NAME)
            
            ## prepare configure_file
            set(LOCAL_COMP_ROOTDIR ${main_dir}/${comp_dir})
            set(LOCAL_COMP_SRCDIR ${CMAKE_BINARY_DIR}/comps/src/${comp_dir2})
            set(LOCAL_COMP_GENDIR ${CMAKE_BINARY_DIR}/comps/build/${comp_dir2})

            configure_file(
                    ${BOZ_EXT_BUILD_DIR}/generic/CMakeLists.comp.txt
                    ${CMAKE_BINARY_DIR}/comps/src/${comp_dir2}/CMakeLists.txt
                    @ONLY)  
            add_subdirectory(${CMAKE_BINARY_DIR}/comps/src/${comp_dir2} ${CMAKE_BINARY_DIR}/comps/build/${comp_dir2})
        endforeach()
    else()
        message(SEND_ERROR "Unable to find any components in ${main_dir}")
    endif()    
endmacro()


