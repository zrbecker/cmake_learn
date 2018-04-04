set(SOURCES sdl_engine.cc)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})

add_library(game.engine.sdl_impl ${SOURCES})

target_link_libraries(game.engine.sdl_impl ${SDL2_LIBRARIES})
target_link_libraries(game.engine.sdl_impl ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(game.engine.sdl_impl ${SDL2_TTF_LIBRARIES})
