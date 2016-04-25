#include <string>

#include <QGLViewer/qglviewer.h>

#include "mesh.h"

class Viewer : public QGLViewer {
 public:
  Viewer(const Mesh& mesh);

 protected:
  virtual void draw();
  virtual void init();
 private:
  Mesh mesh_;
  void draw_mesh_();
};


