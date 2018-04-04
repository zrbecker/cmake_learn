
add_subdirectory(engine)
add_subdirectory(scenes/cat_scene)
add_subdirectory(scenes/space_game)

add_executable(game main.cc)

target_link_libraries(game game.engine)
target_link_libraries(game game.scenes.cat_scene)
target_link_libraries(game game.scenes.space_game)
