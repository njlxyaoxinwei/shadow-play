#ifndef SHADOW_VIEWER_H
#define SHADOW_VIEWER_H

#include <QGLViewer/qglviewer.h>

#include "baseViewer.h"
#include "scene.h"

class ShadowViewer : public BaseViewer {
 public:
  using BaseViewer::BaseViewer;

 protected:
  virtual void draw();
  virtual void init();

 private:
  void draw_shadow_(const int& i, const qglviewer::Vec& pos);
  void control_init_();
};

#endif
