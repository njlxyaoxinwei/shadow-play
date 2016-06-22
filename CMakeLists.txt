project (shadow_play)

cmake_minimum_required(VERSION 2.8)

if (POLICY CMP0043)
  cmake_policy(SET CMP0043 NEW)
endif()

add_compile_options(-std=c++11 -pedantic -Wall)

find_package(CGAL COMPONENTS Qt5)
include(${CGAL_USE_FILE})

find_package(Qt5 QUIET COMPONENTS Xml OpenGL)

find_package(QGLViewer REQUIRED)

find_package(assimp REQUIRED)

find_package(glm)

if (Qt5_FOUND AND QGLVIEWER_FOUND)
  include_directories(${QGLVIEWER_INCLUDE_DIR})
  include_directories(${GLM_INCLUDE_DIR})
  include_directories(${ASSIMP_INCLUDE_DIR})
  
  # My Libraries
  add_library(mylib_mesh SHARED mesh.cpp)
  add_library(mylib_model SHARED model.cpp)
  add_library(mylib_scene SHARED scene.cpp)

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
  
  set_target_properties(test_model test_simpleViewer PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test")

  # Main Target
  add_executable(shadow_play main.cpp viewer.cpp shadowViewer.cpp)
  qt5_use_modules(shadow_play Xml OpenGL)
  target_link_libraries(shadow_play ${QT_LIBRARIES} ${QGLVIEWER_LIBRARIES}
                        mylib_model mylib_scene)
else()

  message(FATAL_ERROR "FATAL: This example requires CGAL, QGLViewer, Qt5, GLM and Assimp.")

endif()
