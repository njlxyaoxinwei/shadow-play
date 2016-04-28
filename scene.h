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
 
  qglviewer::ManipulatedFrame* mesh_frame;
  qglviewer::ManipulatedFrame* light_frame;
 
};

#endif
