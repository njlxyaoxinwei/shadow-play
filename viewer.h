#ifndef VIEWER_H
#define VIEWER_H

#include <QGLViewer/qglviewer.h>
#include "scene.h"

class Viewer : public QGLViewer {
 public:
  Viewer(const Scene* const s, 
         QWidget* parent = NULL, 
         const QGLWidget* sharedWidget = NULL);
 
 protected:
  virtual void drawWithNames();
  virtual void postSelection(const QPoint& p);
  virtual void draw();
  virtual void init();

 private:
  const Scene* const scene_;
  void control_init_();
  void control_frame_();
  void light_init_();
  void draw_light_();
  void draw_mesh_(const Mesh& mesh);
  void update_light_();
};

#endif
