set(SOURCES hello_world.cc)

include_directories(../../src)
add_executable(hello_world ${SOURCES})

target_link_libraries(hello_world message)