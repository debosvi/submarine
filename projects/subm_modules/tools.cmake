
find_package(CUnit REQUIRED)

message(STATUS "CUnit inc dir : ${CUnit_INCLUDE_DIRS}")
message(STATUS "CUnit link dir: ${CUnit_LIBRARY_DIRS}")
message(STATUS "CUnit libs dir: ${CUnit_LIBRARIES}")

include_directories(${CUnit_INCLUDE_DIRS})
link_directories(${CUnit_LIBRARY_DIRS})

find_package(Skalibs REQUIRED)

message(STATUS "Skalibs inc dir : ${Skalibs_INCLUDE_DIRS}")
message(STATUS "Skalibs link dir: ${Skalibs_LIBRARY_DIRS}")
message(STATUS "Skalibs libs dir: ${Skalibs_LIBRARIES}")

include_directories(${Skalibs_INCLUDE_DIRS})
link_directories(${Skalibs_LIBRARY_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/configs)
# add_definitions(-DUSE_FILLBUF_CONFIG_FILE)
add_definitions(-DUSE_CANDEV_CONFIG_FILE)

# add_definitions(-DS6CANBUS_FILLBUF_CHECK_FILL_OVERLAY)
