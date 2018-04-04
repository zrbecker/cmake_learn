set(SOURCES cat_game_logic.cc)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})
include_directories(../../..)
add_library(game.scenes.cat_scene ${SOURCES})
