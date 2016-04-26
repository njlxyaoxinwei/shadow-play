project (shadow_play)

cmake_minimum_required(VERSION 2.8)

add_compile_options(-std=c++11 -pedantic -Wall)

find_package(CGAL COMPONENTS Qt5)
include(${CGAL_USE_FILE})

find_package(Qt5 QUIET COMPONENTS Xml OpenGL)

find_package(QGLViewer)

find_package(assimp REQUIRED)

find_package(glm REQUIRED)

if (Qt5_FOUND AND QGLVIEWER_FOUND)
  include_directories(${QGLVIEWER_INCLUDE_DIR})
  include_directories(${GLM_INCLUDE_DIR})
  include_directories(${ASSIMP_INCLUDE_DIR})
  
  # My Libraries
  add_library(mylib_mesh SHARED mesh.cpp)
  add_library(mylib_model SHARED model.cpp)

  target_link_libraries(mylib_model assimp mylib_mesh)
  set_target_properties(mylib_mesh mylib_model PROPERTIES
                        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
  
  # Test Executables
  add_executable(test_model test_model.cpp)
  target_link_libraries(test_model mylib_model)

  add_executable(test_simpleViewer test_simpleViewer.cpp simpleViewer.cpp)
  qt5_use_modules(test_simpleViewer Xml OpenGL)
  target_link_libraries(test_simpleViewer ${QT_LIBRARIES} ${QGLVIEWER_LIBRARIES}
                        mylib_model mylib_mesh)
  set_target_properties(test_model test_simpleViewer PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test")

else()

  message(FATAL_ERROR "FATAL: This example requires CGAL, QGLViewer, Qt5, GLM and Assimp.")

endif()
