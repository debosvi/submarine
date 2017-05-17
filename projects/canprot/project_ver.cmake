set(${PROJECT_NAME}_VERSION_MAJOR 0)
message ("${PROJECT_NAME}_VERSION_MAJOR: ${${PROJECT_NAME}_VERSION_MAJOR}")

set(${PROJECT_NAME}_VERSION_MINOR 1)
message ("${PROJECT_NAME}_VERSION_MINOR: ${${PROJECT_NAME}_VERSION_MINOR}")

execute_process(COMMAND "date" "+%s" OUTPUT_VARIABLE ${PROJECT_NAME}_VERSION_PATCH)
string(STRIP ${${PROJECT_NAME}_VERSION_PATCH} ${PROJECT_NAME}_VERSION_PATCH)
message ("${PROJECT_NAME}_VERSION_PATCH: ${${PROJECT_NAME}_VERSION_PATCH}")
