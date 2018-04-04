
add_subdirectory(engine)
add_subdirectory(scenes/cat_scene)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(game main.cc)

target_link_libraries(game game.engine)
target_link_libraries(game game.scenes.cat_scene)
