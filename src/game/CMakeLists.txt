
add_subdirectory(engine)
add_subdirectory(scenes/cat_scene)

add_executable(game main.cc)

target_link_libraries(game game.engine)
target_link_libraries(game game.scenes.cat_scene)
