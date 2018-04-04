set(SOURCES cat_game_logic.cc)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(game.scenes.cat_scene ${SOURCES})
