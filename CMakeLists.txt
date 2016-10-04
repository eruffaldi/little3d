cmake_minimum_required(VERSION 2.8)
project(little3d)

find_package(catkin REQUIRED COMPONENTS 
  roscpp std_msgs cmake_modules message_generation
  roscpp
  std_srvs
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR} ${catkin_INCLUDE_DIR})

# why catkin is not finding opencv2?
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_libraries(${OpenCV_LIBS})

# why catkin is not finding assimp?
find_package(AssImp REQUIRED)
include_directories(${ASSIMP_INCLUDE_DIRS})
link_directories(${ASSIMP_LIBRARY_DIRS})
link_libraries(${ASSIMP_LIBRARIES})

# why catkin is not finding glew?
find_package(Glew REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})
link_libraries(${GLEW_LIBRARIES})

# why catkin is not finding opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
link_libraries(${OPENGL_LIBRARIES})

# these were already present in cmakego
find_library(XXF86_LIBRARY Xxf86vm)
find_library(X11_LIBRARY X11)
find_library(XX_LIBRARY Xxf86vm)
find_library(XRANDR_LIBRARY Xrandr)
find_library(XI_LIBRARY Xi)
find_library(XINEARAMA_LIBRARY Xinerama)
find_library(XEXT_LIBRARY Xext)
find_library(XCURSOR_LIBRARY Xcursor)
link_libraries( 
      ${XXF86_LIBRARY}
      ${X11_LIBRARY}
      ${XX_LIBRARY}
      ${XINEARAMA_LIBRARY}
      ${XRANDR_LIBRARY}
      ${XI_LIBRARY}
      ${XEXT_LIBRARY}
      ${XCURSOR_LIBRARY}
      dl  m
      )    
if(LINUX)
link_libraries(rt)
elseif(APPLE)
            set(DISPLAY_INCLUDE_DIR /System/Library/Frameworks)
            find_library(COCOA_LIBRARY Cocoa)
            find_library(COREVIDEO_LIBRARY CoreVideo)
            find_library(IOKIT_FRAMEWORK IOKit)
            find_library(QTKIT_FRAMEWORK QtKit)
            find_library(COREMEDIA_FRAMEWORK CoreMedia)
            find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
            find_library(AV_FOUNDATION_FRAMEWORK AVFoundation)
            set(DISPLAY_LIBRARIES
                ${COCOA_LIBRARY}
                ${COREVIDEO_LIBRARY}
                ${IOKIT_FRAMEWORK}
                ${QTKIT_FRAMEWORK}
                ${COREMEDIA_FRAMEWORK}
                ${AV_FOUNDATION_FRAMEWORK}
                ${CORE_FOUNDATION_FRAMEWORK})
            link_libraries(${DISPLAY_LIBRARIES})
endif()       

# why catkin is not finding glfw3
find_package(GLFW3 REQUIRED)
link_libraries(${GLFW3_LIBRARIES})
include_directories(${GLFW3_INCLUDE_DIRS})

# why catkin is not finding eigen3
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

## Declare a catkin package
catkin_package( 
	INCLUDE_DIRS include
  LIBRARIES SOIL 
  #CATKIN_DEPENDS
  #DEPENDS
)
include_directories(include ${catkin_INCLUDE_DIRS})

add_subdirectory(include/SOIL)
add_executable(showimage src/showimage.cpp)
target_link_libraries(showimage SOIL)


install(TARGETS showimage
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY res/
   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
   FILES_MATCHING PATTERN "*"
)

install(DIRECTORY include/
   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
   FILES_MATCHING PATTERN "*"
)



