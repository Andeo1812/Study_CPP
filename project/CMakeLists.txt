add_subdirectory(Core)

file(GLOB SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${Core_lib_libs})