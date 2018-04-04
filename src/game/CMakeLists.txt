
add_subdirectory(engine)
add_subdirectory(scenes/cat_scene)

include_directories(..)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})

add_executable(game main.cc)

target_link_libraries(game game.engine)
target_link_libraries(game game.scenes.cat_scene)
