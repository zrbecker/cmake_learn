
find_path(FRUIT_INCLUDE_DIRS "fruit/fruit.h")
find_library(FRUIT_LIBRARIES NAMES "fruit")

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(fruit
  REQUIRED_VARS FRUIT_INCLUDE_DIRS FRUIT_LIBRARIES)
