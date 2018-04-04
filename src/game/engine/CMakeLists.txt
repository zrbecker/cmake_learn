set(SOURCES engine.cc sdl_engine.cc frame_counter.cc)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})

add_library(game.engine ${SOURCES})

target_link_libraries(game.engine ${SDL2_LIBRARIES})
target_link_libraries(game.engine ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(game.engine ${SDL2_TTF_LIBRARIES})
