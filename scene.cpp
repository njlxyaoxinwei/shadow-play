#include "scene.h"

#include <vector>

#include <QGLViewer/qglviewer.h>
#include <QGLViewer/manipulatedFrame.h>

#include "mesh.h"

namespace {
  using qglviewer::ManipulatedFrame;
  using qglviewer::Vec;
  using std::vector;
  using std::max;
} // namespace

Scene::Scene(const vector<Mesh>& ms) 
    : meshes(ms),
      n(ms.size()),
      radius(max(n, 3)),
      light_frame(new ManipulatedFrame()) {
  // Initialize mesh frames and light
  light_frame->setPosition(0, 0, 3);
  mesh_frames.resize(n);
  for (int i = 0; i < n; i++) {
    mesh_frames[i] = new ManipulatedFrame();
    mesh_frames[i]->setPosition(2 * i + 1 - n, 0, 1);
  }
}

Scene::~Scene() {
  for (int i = 0; i < n; i++) {
    delete mesh_frames[i];
  }
  mesh_frames.clear();
}


