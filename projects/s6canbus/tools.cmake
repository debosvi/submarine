
if("${CROSS_SYSROOT}" STREQUAL "")
	message(STATUS "Use CMAKE_SYSROOT: ${CMAKE_SYSROOT}")
	set(CROSS_SYSROOT ${CMAKE_SYSROOT})
endif()

include_directories(${CROSS_SYSROOT}/include)

link_directories(${CROSS_SYSROOT}/lib)
link_directories(${CROSS_SYSROOT}/lib/skalibs)
