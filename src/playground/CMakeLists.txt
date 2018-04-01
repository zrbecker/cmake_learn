set(SOURCES message.cc)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${FRUIT_INCLUDE_DIRS})

add_library(message ${SOURCES})

target_link_libraries(message ${SDL2_LIBRARIES})
target_link_libraries(message ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(message ${FRUIT_LIBRARIES})

install(TARGETS message DESTINATION lib)