project(fun)
add_library(state SHARED ${PROJECT_SOURCE_DIR}/src/state.c)
target_include_directories(state PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(stack SHARED ${PROJECT_SOURCE_DIR}/src/stack.c)
target_include_directories(stack PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/fun.c)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} stack state)

