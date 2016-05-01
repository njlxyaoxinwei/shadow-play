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
  using glm::vec3;
  using glm::vec2;
  using glm::mat4;

  vec3 ApplyMat4(const vec3& p, const mat4& mat) {
    vec3 np(mat * vec4(p, 1));
    return np;
  }

  bool ProjectXY(const vec3& p, const vec3& pos, vec2& ans) {
    vec3 v = p - pos;
    if (v.z == 0) {
      return false;
    }
    float t = - p.z / v.z;
    if (t >= 0) {
      ans = vec2(p.x + t * v.x, p.y + t * v.y);
      return true;
    } else {
      return false;
    }
  }
} // namespace

void ShadowViewer::draw_shadow_(const int& i, const Vec& pos) {
  const auto& mesh = scene_->meshes[i];
  const auto nTriangles = mesh.indices.size() / 3;
  glBegin(GL_TRIANGLES);
  vec3 light_pos = vec3(pos.x, pos.y, pos.z);
  const auto& coords = scene_->meshVertexWorldPositions(i);
  for (unsigned int i = 0; i < nTriangles; i++) {
    unsigned int j = 3 * i;
    unsigned int is[3] = {
      mesh.indices[j],
      mesh.indices[j+1],
      mesh.indices[j+2]
    };
    vec3 w[3] = {
      coords[is[0]],
      coords[is[1]],
      coords[is[2]]
    };
    vec2 s[3];
    bool succ = ProjectXY(w[0], light_pos, s[0]);
    succ &= ProjectXY(w[1], light_pos, s[1]);
    succ &= ProjectXY(w[2], light_pos, s[2]);
    if (succ) { 
      glVertex2f(s[0].x, s[0].y);
      glVertex2f(s[1].x, s[1].y);
      glVertex2f(s[2].x, s[2].y);
    }
  }
  glEnd();
}

void ShadowViewer::draw() {
  Vec light_pos = scene_->light_frame->position();
  for (int i = 0; i < scene_->n; i++) {
    draw_shadow_(i, light_pos);
  }
  glColor3f(1.0f, 0.0f, 0.0f);
  drawGrid(scene_->radius);
}

void ShadowViewer::init() {
  // Set camera
  setSceneRadius(scene_->radius);
  camera()->showEntireScene();
  control_init_();
  setBackgroundColor(QColor(255, 255, 255));
  setForegroundColor(QColor(0, 0, 0));
  glDisable(GL_LIGHT0);

  qDebug() << "ShadowViewer OpenGL: " << (char *)glGetString(GL_VERSION);
}

void ShadowViewer::control_init_() {
  // Override mouse bindings
  clearMouseBindings();
  setMouseBinding(Qt::NoModifier, Qt::MidButton, 
                  QGLViewer::CAMERA, QGLViewer::ZOOM);
  setWheelBinding(Qt::NoModifier, QGLViewer::CAMERA, QGLViewer::ZOOM);
}
