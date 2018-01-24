
add_definitions(-DBOZ_SPI_MICROCHIP)

find_package(CUnit REQUIRED)

message(STATUS "CUnit inc dir : ${CUnit_INCLUDE_DIRS}")
message(STATUS "CUnit link dir: ${CUnit_LIBRARY_DIRS}")
message(STATUS "CUnit libs dir: ${CUnit_LIBRARIES}")

include_directories(${CUnit_INCLUDE_DIRS})
link_directories(${CUnit_LIBRARY_DIRS})

