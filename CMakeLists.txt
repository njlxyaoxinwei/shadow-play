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
  add_library(mylib_mesh STATIC mesh.cpp)
  add_library(mylib_model STATIC model.cpp)
  add_library(mylib_scene STATIC scene.cpp)

  target_link_libraries(mylib_model assimp mylib_mesh)
  qt5_use_modules(mylib_scene Xml OpenGL)
  target_link_libraries(mylib_scene mylib_mesh 
                        ${QT_LIBRARIES} ${QGLVIEWER_LIBRARIES})

  set_target_properties(mylib_mesh mylib_model mylib_scene PROPERTIES
                        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
  
  # Test Executables
  add_executable(test_model test_model.cpp)
  target_link_libraries(test_model mylib_model)

  add_executable(test_simpleViewer test_simpleViewer.cpp simpleViewer.cpp)
  qt5_use_modules(test_simpleViewer Xml OpenGL)
  target_link_libraries(test_simpleViewer ${QT_LIBRARIES} ${QGLVIEWER_LIBRARIES}
                        mylib_model mylib_mesh)
  
  add_executable(test_viewer test_viewer.cpp viewer.cpp shadowViewer.cpp)
  qt5_use_modules(test_viewer Xml OpenGL)
  target_link_libraries(test_viewer ${QT_LIBRARIES} ${QGLVIEWER_LIBRARIES}
                        mylib_model mylib_scene)
  
  set_target_properties(test_model test_simpleViewer test_viewer PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test")

else()

  message(FATAL_ERROR "FATAL: This example requires CGAL, QGLViewer, Qt5, GLM and Assimp.")

endif()
