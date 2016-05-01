#ifndef VIEWER_H
#define VIEWER_H

#include <QGLViewer/qglviewer.h>

#include "baseViewer.h"
#include "scene.h"

class Viewer : public BaseViewer {
 public:
  using BaseViewer::BaseViewer;

 protected:
  virtual void drawWithNames();
  virtual void postSelection(const QPoint& p);
  virtual void draw();
  virtual void init();
  virtual QString helpString() const;

 private:
  void control_init_();
  void control_frame_();
  void light_init_();
  void draw_light_();
  void draw_mesh_(const int& i);
  void update_light_();
};

#endif
