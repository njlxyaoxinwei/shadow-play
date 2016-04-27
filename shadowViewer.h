#ifndef SHADOW_VIEWER_H
#define SHADOW_VIEWER_H

#include <QGLViewer/qglviewer.h>
#include "scene.h"

class ShadowViewer : public QGLViewer {
 public:
  ShadowViewer(const Scene* const s, 
         QWidget* parent = NULL, 
         const QGLWidget* sharedWidget = NULL);
 
 protected:
  virtual void draw();
  virtual void init();

 private:
  const Scene* const scene_;
  void light_init_();
  void draw_shadow_(const Mesh& mesh, const qglviewer::Vec& pos);

};

#endif
