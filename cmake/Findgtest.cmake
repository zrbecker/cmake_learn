
find_path(GMOCK_INCLUDE_DIRS "gmock/gmock.h")
find_path(GTEST_INCLUDE_DIRS "gtest/gtest.h")

find_library(GMOCK_LIBRARIES NAMES "gmock")
find_library(GMOCK_MAIN_LIBRARIES NAMES "gmock_main")
find_library(GTEST_LIBRARIES NAMES "gtest")
find_library(GTEST_MAIN_LIBRARIES NAMES "gtest_main")

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(gtest
  REQUIRED_VARS
    GTEST_INCLUDE_DIRS
    GTEST_LIBRARIES
    GTEST_MAIN_LIBRARIES

    GMOCK_LIBRARIES
    GMOCK_INCLUDE_DIRS
    GMOCK_MAIN_LIBRARIES
)
