set(SOURCES engine.cc frame_counter.cc)

add_subdirectory(sdl_impl)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})

add_library(game.engine ${SOURCES})

target_link_libraries(game.engine game.engine.sdl_impl)
