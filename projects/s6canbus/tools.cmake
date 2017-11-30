
if("${CROSS_SYSROOT}" STREQUAL "")
	message(STATUS "Use CMAKE_SYSROOT: ${CMAKE_SYSROOT}")
	set(CROSS_SYSROOT ${CMAKE_SYSROOT})
endif()

include_directories(${CROSS_SYSROOT}/include)

link_directories(${CROSS_SYSROOT}/lib)
link_directories(${CROSS_SYSROOT}/lib/skalibs)

find_package(CUnit REQUIRED)

add_definitions(-DUSE_FILLBUF_CONFIG_FILE)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
