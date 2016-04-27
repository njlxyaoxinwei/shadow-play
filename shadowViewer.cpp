#include "shadowViewer.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QDebug>
#include <QObject>
#include <QGLViewer/manipulatedFrame.h>
#include <QGLViewer/qglviewer.h>

#include "scene.h"

namespace {
  using qglviewer::Vec;
  using glm::make_mat4;
  using glm::vec4;
} // namespace

ShadowViewer::ShadowViewer(const Scene* const s,
                           QWidget* parent,
                           const QGLWidget* sharedWidget)
    : QGLViewer(parent, sharedWidget), scene_(s) {
  connect(scene_->light_frame_, SIGNAL(manipulated()), this, SLOT(update()));
  connect(scene_->mesh_frame_, SIGNAL(manipulated()), this, SLOT(update()));    
}

void ShadowViewer::light_init_() {
  glEnable(GL_LIGHT0);
  constexpr GLfloat light0_ambient[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  constexpr GLfloat light0_diffuse[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  constexpr GLfloat light0_specular[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
}

void ShadowViewer::draw_shadow_(const Mesh& mesh, const Vec& pos) {
  const auto nTriangles = mesh.indices.size() / 3;
  glBegin(GL_TRIANGLES);
  glm::mat4 mat = make_mat4(scene_->mesh_frame_->worldMatrix());
  for (unsigned int i = 0; i < nTriangles; i++) {
    unsigned int j = 3 * i;
    unsigned int is[3] = {
      mesh.indices[j],
      mesh.indices[j+1],
      mesh.indices[j+2]
    };
    // glColor3f(1.0f, 1.0f, 1.0f);
    Vertex v[3] = {
      mesh.vertices[is[0]],
      mesh.vertices[is[1]],
      mesh.vertices[is[2]]
    };
    glm::vec4 w[3] = {
      (mat * vec4(v[0].Position, 1)),
      (mat * vec4(v[1].Position, 1)),
      (mat * vec4(v[2].Position, 1))
    };
    // glNormal3f(v[0].Normal.x, v[0].Normal.y, v[0].Normal.z);
    glVertex2f(w[0].x, w[0].y);
    glVertex2f(w[1].x, w[1].y);
    glVertex2f(w[2].x, w[2].y);
  }
  glEnd();
}

void ShadowViewer::draw() {
  Vec light_pos = scene_->light_frame_->position();
  draw_shadow_(scene_->mesh, light_pos);
}

void ShadowViewer::init() {
  // Set camera
  setSceneRadius(2);
  camera()->showEntireScene();

  setBackgroundColor(QColor(255, 255, 255));
  setForegroundColor(QColor(0, 0, 0));
  light_init_();

  qDebug() << "ShadowViewer OpenGL: " << (char *)glGetString(GL_VERSION);
}
