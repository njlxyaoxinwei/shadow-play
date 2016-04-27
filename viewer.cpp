#include "viewer.h"

#include <QDebug>
#include <QObject>
#include <QGLViewer/manipulatedFrame.h>
#include <QGLViewer/qglviewer.h>

#include "scene.h"

namespace {
  using qglviewer::Vec;
} // namespace

Viewer::Viewer(const Scene* const s, 
               QWidget* parent, 
               const QGLWidget* sharedWidget) 
    : QGLViewer(parent, sharedWidget), scene_(s) {
  connect(scene_->light_frame_, SIGNAL(manipulated()), this, SLOT(update()));
  connect(scene_->mesh_frame_, SIGNAL(manipulated()), this, SLOT(update()));
}

void Viewer::control_init_() {
  // Override mouse bindings
  setMouseBinding(Qt::ControlModifier, Qt::LeftButton, 
                  QGLViewer::CAMERA, QGLViewer::ROTATE);
  setMouseBinding(Qt::ControlModifier, Qt::RightButton, 
                  QGLViewer::CAMERA, QGLViewer::TRANSLATE);
  setMouseBinding(Qt::ControlModifier, Qt::MidButton, 
                  QGLViewer::CAMERA, QGLViewer::ZOOM);
  setWheelBinding(Qt::ControlModifier, QGLViewer::CAMERA, QGLViewer::ZOOM);

  setMouseBinding(Qt::NoModifier, Qt::LeftButton, 
                  QGLViewer::FRAME, QGLViewer::ROTATE);
  setMouseBinding(Qt::NoModifier, Qt::RightButton, 
                  QGLViewer::FRAME, QGLViewer::TRANSLATE);
  setMouseBinding(Qt::NoModifier, Qt::MidButton, 
                  QGLViewer::FRAME, QGLViewer::ZOOM);
  setWheelBinding(Qt::NoModifier, QGLViewer::FRAME, QGLViewer::ZOOM);
}

void Viewer::light_init_() {
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  // ambient light
  constexpr GLfloat light0_ambient[4] = {0.3f, 0.3f, 0.3f, 1.0f};
  constexpr GLfloat light0_diffuse[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  constexpr GLfloat light0_specular[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

  // point light source on z+
  constexpr GLfloat light1_ambient[4] = {0.1f, 0.1f, 0.1f, 1.0f};
  constexpr GLfloat light1_diffuse[4] = {0.7f, 0.7f, 0.7f, 1.0f};
  constexpr GLfloat light1_specular[4] = {0.2f, 0.2f, 0.2f, 1.0f};
  glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
}


void Viewer::init() {
  // Set camera
  setSceneRadius(2);
  camera()->showEntireScene();

  control_init_();

  setManipulatedFrame(scene_->mesh_frame_);

  light_init_();
  setMouseTracking(true);

  qDebug() << "Viewer OpenGL: " << (char *)glGetString(GL_VERSION);
}

void Viewer::draw_light_() {
  if (scene_->light_frame_->grabsMouse()) {
    glPointSize(15.0f);
  } else {
    glPointSize(10.0f);
  }
  
  drawLight(GL_LIGHT1, 1.5f);
  glColor3f(1.0f, 1.0f, 1.0f);
  Vec pos_v = scene_->light_frame_->position();
  glBegin(GL_POINTS);
    glVertex3f(pos_v.x, pos_v.y, pos_v.z);
  glEnd();

}


void Viewer::draw_mesh_(const Mesh& mesh) {

  const auto nTriangles = mesh.indices.size() / 3;
  glBegin(GL_TRIANGLES);

  for (unsigned int i = 0; i < nTriangles; i++) {
    unsigned int j = 3 * i;
    unsigned int is[3] = {
      mesh.indices[j],
      mesh.indices[j+1],
      mesh.indices[j+2]
    };
    glColor3f(1.0f, 1.0f, 1.0f);
    Vertex v[3] = {
      mesh.vertices[is[0]],
      mesh.vertices[is[1]],
      mesh.vertices[is[2]]
    };
    glNormal3f(v[0].Normal.x, v[0].Normal.y, v[0].Normal.z);
    glVertex3f(v[0].Position.x, v[0].Position.y, v[0].Position.z);
    glVertex3f(v[1].Position.x, v[1].Position.y, v[1].Position.z);
    glVertex3f(v[2].Position.x, v[2].Position.y, v[2].Position.z);
  }
  glEnd();
}

void Viewer::update_light_() {
  float pos[4] = {0.0, 0.0, 0.0, 0.0};
  Vec pos_v = scene_->light_frame_->position();
  pos[0] = float(pos_v.x);
  pos[1] = float(pos_v.y);
  pos[2] = float(pos_v.z);
  glLightfv(GL_LIGHT1, GL_POSITION, pos);
}

void Viewer::draw() {
  update_light_();

  drawGrid(2);
  draw_light_();

  glPushMatrix();
  glMultMatrixd(scene_->mesh_frame_->matrix());
  drawAxis();
  draw_mesh_(scene_->mesh);
  glPopMatrix();
}
