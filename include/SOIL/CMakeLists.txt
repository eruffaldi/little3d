include_directories(..)
add_library(SOIL SOIL.c stb_image_aug.c image_helper.c image_DXT.c stb_image_write.c lodepng.cpp)

install(TARGETS SOIL
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
