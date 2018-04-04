set(SOURCES engine.cc frame_counter.cc)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})

add_subdirectory(sdl_impl)
add_library(game.engine ${SOURCES})

target_link_libraries(game.engine game.engine.sdl_impl)
