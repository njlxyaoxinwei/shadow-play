#include "viewer.h"

#include <QDebug>
#include <QObject>
#include <QGLViewer/manipulatedFrame.h>
#include <QGLViewer/qglviewer.h>

#include "scene.h"

namespace {
  using qglviewer::Vec;
} // namespace

void Viewer::control_frame_() {
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

void Viewer::control_init_() {
  // Override mouse bindings
  setMouseBinding(Qt::NoModifier, Qt::LeftButton, 
                  QGLViewer::CAMERA, QGLViewer::ROTATE);
  setMouseBinding(Qt::NoModifier, Qt::RightButton, 
                  QGLViewer::CAMERA, QGLViewer::TRANSLATE);
  setMouseBinding(Qt::NoModifier, Qt::MidButton, 
                  QGLViewer::CAMERA, QGLViewer::ZOOM);
  setWheelBinding(Qt::NoModifier, QGLViewer::CAMERA, QGLViewer::ZOOM);

  setMouseBinding(Qt::ControlModifier, Qt::LeftButton, 
                  QGLViewer::FRAME, QGLViewer::ROTATE);
  setMouseBinding(Qt::ControlModifier, Qt::RightButton, 
                  QGLViewer::FRAME, QGLViewer::TRANSLATE);
  setMouseBinding(Qt::ControlModifier, Qt::MidButton, 
                  QGLViewer::FRAME, QGLViewer::ZOOM);
  setWheelBinding(Qt::ControlModifier, QGLViewer::FRAME, QGLViewer::ZOOM);
}

void Viewer::light_init_() {
  glDisable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  // ambient light
  constexpr GLfloat light0_ambient[4] = {1.0f, 1.0f, 1.0f, 1.0f};
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
  setSceneRadius(scene_->radius);
  camera()->showEntireScene();

  control_init_();

  light_init_();

  qDebug() << "Viewer OpenGL: " << (char *)glGetString(GL_VERSION);
}

void Viewer::draw_light_() {
  bool selected = (selectedName() == 0);
  glEnable(GL_LIGHT0);
  if (selected) {
    drawLight(GL_LIGHT1, 1.3f);
  } else {
    drawLight(GL_LIGHT1);
  }
  glDisable(GL_LIGHT0);
}


void Viewer::draw_mesh_(const int& i) {
  const auto& mesh = scene_->meshes[i];
  bool selected = (selectedName() == i + 1);
  if (selected) {
    drawAxis();
  }
  const auto nTriangles = mesh.indices.size() / 3;
  glBegin(GL_TRIANGLES);

  for (unsigned int i = 0; i < nTriangles; i++) {
    unsigned int j = 3 * i;
    unsigned int is[3] = {
      mesh.indices[j],
      mesh.indices[j+1],
      mesh.indices[j+2]
    };
    if (selected) {
      glColor3f(1.0f, 1.0f, 1.0f);
    } else {
      glColor3f(0.8f, 0.8f, 0.8f);
    }
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
  glColor3f(1.0f, 1.0f, 1.0f);
}

void Viewer::update_light_() {
  float pos[4] = {0.0, 0.0, 0.0, 1.0};
  Vec pos_v = scene_->light_frame->position();
  pos[0] = float(pos_v.x);
  pos[1] = float(pos_v.y);
  pos[2] = float(pos_v.z);
  glLightfv(GL_LIGHT1, GL_POSITION, pos);
}

void Viewer::draw() {
  drawGrid(scene_->radius);

  update_light_();
  draw_light_();

  for (int i = 0; i < scene_->n; i++) {
    glPushMatrix();
    glMultMatrixd(scene_->mesh_frames[i]->matrix());
    draw_mesh_(i);
    glPopMatrix();
  }
}

void Viewer::drawWithNames() {
  glPushName(0);
  draw_light_();
  glPopName();
  for (int i = 0; i < scene_->n; i++) {
    glPushMatrix();
    glMultMatrixd(scene_->mesh_frames[i]->matrix());
    glPushName(i+1);
    draw_mesh_(i);
    glPopName();
    glPopMatrix();
  }
}

void Viewer::postSelection(const QPoint& point) {
  int selected = selectedName();
  if (selected > 0) {
    setManipulatedFrame(scene_->mesh_frames[selected - 1]);
    control_frame_();
    qDebug() << "Mesh " << selected << " Selected!";
  } else if (selected == 0) {
    setManipulatedFrame(scene_->light_frame);
    control_frame_();
    qDebug() << "Light Selected!";
  } else {
    setManipulatedFrame(NULL);
    control_init_();
  }
}
