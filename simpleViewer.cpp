#include <string>

#include <QDebug>
#include <QGLViewer/manipulatedFrame.h>

#include "mesh.h"
#include "simpleViewer.h"

namespace {
  using std::string;
  using qglviewer::ManipulatedFrame;
  using qglviewer::Vec;
} // namepsace

Viewer::Viewer(const Mesh& mesh) : mesh_(mesh) {}

void Viewer::draw_light_() {
  float pos[4] = {0.0, 0.0, 0.0, 1.0};
  Vec pos_v = light_frame_->position();
  pos[0] = float(pos_v.x);
  pos[1] = float(pos_v.y);
  pos[2] = float(pos_v.z);
  glLightfv(GL_LIGHT1, GL_POSITION, pos);

  if (light_frame_->grabsMouse()) {
    drawLight(GL_LIGHT1, 1.2f);
  } else {
    drawLight(GL_LIGHT1);
  }
}

void Viewer::draw() {
  draw_light_();

  glPushMatrix();
  glMultMatrixd(mesh_frame_->matrix());
  drawAxis();
  draw_mesh_();
  glPopMatrix();
}

void Viewer::draw_mesh_() {

  // draw first mesh
  const auto& mesh = mesh_;
  const auto nTriangles = mesh.indices.size() / 3;
  glBegin(GL_TRIANGLES);

  for (int i = 0; i < nTriangles; i++) {
    int j = 3 * i;
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

void Viewer::control_init_() {
  // Override mouse bindings
  setMouseBinding(Qt::ControlModifier, Qt::LeftButton, QGLViewer::CAMERA, QGLViewer::ROTATE);
  setMouseBinding(Qt::ControlModifier, Qt::RightButton, QGLViewer::CAMERA, QGLViewer::TRANSLATE);
  setMouseBinding(Qt::ControlModifier, Qt::MidButton, QGLViewer::CAMERA, QGLViewer::ZOOM);
  setWheelBinding(Qt::ControlModifier, QGLViewer::CAMERA, QGLViewer::ZOOM);

  setMouseBinding(Qt::NoModifier, Qt::LeftButton, QGLViewer::FRAME, QGLViewer::ROTATE);
  setMouseBinding(Qt::NoModifier, Qt::RightButton, QGLViewer::FRAME, QGLViewer::TRANSLATE);
  setMouseBinding(Qt::NoModifier, Qt::MidButton, QGLViewer::FRAME, QGLViewer::ZOOM);
  setWheelBinding(Qt::NoModifier, QGLViewer::FRAME, QGLViewer::ZOOM);
}


void Viewer::light_init_() {
  // ambient light
  glEnable(GL_LIGHT0);
  constexpr GLfloat light0_ambient[4] = {0.3f, 0.3f, 0.3f, 1.0f};
  constexpr GLfloat light0_diffuse[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  constexpr GLfloat light0_specular[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

  glEnable(GL_LIGHT1);
  constexpr GLfloat light1_ambient[4] = {0.1f, 0.1f, 0.1f, 1.0f};
  constexpr GLfloat light1_diffuse[4] = {0.7f, 0.7f, 0.7f, 1.0f};
  constexpr GLfloat light1_specular[4] = {0.2f, 0.2f, 0.2f, 1.0f};
  glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
  light_frame_ = new ManipulatedFrame();
  setMouseTracking(true);

  light_frame_->setPosition(0, 0, 2);
}

void Viewer::init() {
  // Set Camera
  setSceneRadius(2);
  camera()->showEntireScene();

  control_init_();

  mesh_frame_ = new ManipulatedFrame();
  
  setManipulatedFrame(mesh_frame_);
  mesh_frame_->setPosition(0, 0, 1);

  light_init_();
  // restoreStateFromFile();

  // Opens help window
  // help();
} 
