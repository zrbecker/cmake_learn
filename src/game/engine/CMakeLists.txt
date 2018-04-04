set(SOURCES frame_counter.cc)

add_subdirectory(sdl_impl)
add_library(game.engine ${SOURCES})

target_link_libraries(game.engine game.engine.sdl_impl)
