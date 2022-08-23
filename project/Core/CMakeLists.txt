project(Core)

file(GLOB SOURCES definition/*.cpp)

set(Include_dir ${CMAKE_CURRENT_SOURCE_DIR}/include/
        ${CMAKE_CURRENT_SOURCE_DIR}/definition/)


file(GLOB INCLUDE_DIRS Include_dir)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${Include_dir})

set(Core_lib_libs ${PROJECT_NAME} CACHE FILEPATH "" FORCE)
set(Core_lib_include ${Include_dir} CACHE FILEPATH "" FORCE)
