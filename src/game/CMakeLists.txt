set(SOURCES game.cc)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(game ${SOURCES})

target_link_libraries(game ${SDL2_LIBRARIES})
target_link_libraries(game ${SDL2_IMAGE_LIBRARIES})
