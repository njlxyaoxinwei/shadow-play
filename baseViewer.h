#ifndef BASE_VIEWER_H
#define BASE_VIEWER_H

#include <QObject>
#include <QGLViewer/qglviewer.h>
#include <QGLViewer/manipulatedFrame.h>

#include "scene.h"

class BaseViewer : public QGLViewer {

 public:
  BaseViewer(const Scene* const s,
             QWidget* parent = NULL,
             const QGLWidget* sharedWidget = NULL)
      : QGLViewer(parent, sharedWidget), scene_(s) {
    connect(scene_->light_frame, SIGNAL(manipulated()), this, SLOT(update()));
    for (const auto& fp : scene_->mesh_frames) {
      connect(fp, SIGNAL(manipulated()), this, SLOT(update()));
      connect(fp, SIGNAL(spun()), this, SLOT(update()));
    }
  }

 protected:
  virtual void draw() {};
  virtual void init() {};
  const Scene* const scene_;

};

#endif
