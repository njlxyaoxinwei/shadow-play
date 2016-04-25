#include <string>

#include <QGLViewer/qglviewer.h>

#include "model.h"

class Viewer : public QGLViewer {
 public:
  Viewer(const std::string& path);

 protected:
  virtual void draw();
  virtual void init();
 private:
  Model model_;
};


