set(SOURCES math_test.cc)

include_directories(${GMOCK_INCLUDE_DIRS})
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(math_test ${SOURCES})

target_link_libraries(math_test ${GTEST_LIBRARIES})
target_link_libraries(math_test ${GTEST_MAIN_LIBRARIES})
