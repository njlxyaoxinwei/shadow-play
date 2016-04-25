project (shadow_play)

cmake_minimum_required(VERSION 2.8)

add_compile_options(-std=c++11)

find_package(CGAL COMPONENTS Qt5)
include(${CGAL_USE_FILE})

find_package(Qt5 QUIET COMPONENTS Xml OpenGL)

find_package(QGLViewer)

find_package(Assimp)

find_package(Glm)

if (Qt5_FOUND AND QGLVIEWER_FOUND AND ASSIMP_FOUND AND GLM_FOUND)

  include_directories(${QGLVIEWER_INCLUDE_DIR})
  include_directories(${GLM_INCLUDE_DIR})
  include_directories(${ASSIMP_INCLUDE_DIR})
  
  add_executable(test_model test_model.cpp model.cpp)

  target_link_libraries(test_model ${ASSIMP_LIBRARIES})

else()

  message(STATUS "NOTICE: This example requires CGAL, QGLViewer, Qt5, GLM and Assimp.")

endif()
