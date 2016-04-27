#ifndef SCENE_H
#define SCENE_H

#include <QGLViewer/qglviewer.h>

#include "mesh.h"


/* Holding the shared scene across viewers */
class Scene {
 public:
  Mesh mesh; 
  
  Scene(const Mesh&);
  ~Scene() {};
 
  qglviewer::ManipulatedFrame* const mesh_frame_;
  qglviewer::ManipulatedFrame* const light_frame_;
 
};

#endif
