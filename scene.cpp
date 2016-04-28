#include <QGLViewer/qglviewer.h>
#include <QGLViewer/manipulatedFrame.h>

#include "mesh.h"
#include "scene.h"

namespace {
  using qglviewer::ManipulatedFrame;
  using qglviewer::Vec;
} // namespace

Scene::Scene(const Mesh& m) 
    : mesh(m),
      mesh_frame(new ManipulatedFrame()),
      light_frame(new ManipulatedFrame()) {
  // Initialize mesh frames and light
  mesh_frame->setPosition(0, 0, 1);
  light_frame->setPosition(0, 0, 2.5);
}


