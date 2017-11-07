
include_directories(${CMAKE_SYSROOT}/include)

link_directories(${CMAKE_SYSROOT}/lib)
link_directories(${CMAKE_SYSROOT}/lib/skalibs)

if(${USE_MUSL})
    set(PRELOAD_S6 ON)
endif()
