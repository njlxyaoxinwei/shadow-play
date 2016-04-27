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
      mesh_frame_(new ManipulatedFrame()),
      light_frame_(new ManipulatedFrame()) {
  // Initialize mesh frames and light
  mesh_frame_->setPosition(0, 0, 1);
  light_frame_->setPosition(0, 0, 2.5);
}


