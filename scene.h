#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include <QGLViewer/qglviewer.h>

#include "mesh.h"


/* Holding the shared scene across viewers */
class Scene {
 public:
  std::vector<Mesh> meshes; 
  const int n;
  const float radius;
  
  Scene(const std::vector<Mesh>& ms);
  ~Scene();
 
  std::vector<qglviewer::ManipulatedFrame*> mesh_frames;
  qglviewer::ManipulatedFrame* light_frame;
 
};

#endif
