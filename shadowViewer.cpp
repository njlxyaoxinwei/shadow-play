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

ShadowViewer::ShadowViewer(const Scene* const s,
                           QWidget* parent,
                           const QGLWidget* sharedWidget)
    : QGLViewer(parent, sharedWidget), scene_(s) {
  connect(scene_->light_frame_, SIGNAL(manipulated()), this, SLOT(update()));
  connect(scene_->mesh_frame_, SIGNAL(manipulated()), this, SLOT(update())); 
  connect(scene_->mesh_frame_, SIGNAL(spun()), this, SLOT(update()));   
}

void ShadowViewer::draw_shadow_(const Mesh& mesh, const Vec& pos) {
  const auto nTriangles = mesh.indices.size() / 3;
  glBegin(GL_TRIANGLES);
  mat4 mat = make_mat4(scene_->mesh_frame_->worldMatrix());
  vec3 light_pos = vec3(pos.x, pos.y, pos.z);
  for (unsigned int i = 0; i < nTriangles; i++) {
    unsigned int j = 3 * i;
    unsigned int is[3] = {
      mesh.indices[j],
      mesh.indices[j+1],
      mesh.indices[j+2]
    };
    glColor3f(0.0f, 0.0f, 0.0f);
    Vertex v[3] = {
      mesh.vertices[is[0]],
      mesh.vertices[is[1]],
      mesh.vertices[is[2]]
    };
    vec3 w[3] = {
      ApplyMat4(v[0].Position, mat),
      ApplyMat4(v[1].Position, mat),
      ApplyMat4(v[2].Position, mat)
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
  Vec light_pos = scene_->light_frame_->position();
  draw_shadow_(scene_->mesh, light_pos);
}

void ShadowViewer::init() {
  // Set camera
  setSceneRadius(2);
  camera()->showEntireScene();

  setBackgroundColor(QColor(255, 255, 255));
  setForegroundColor(QColor(0, 0, 0));
  glDisable(GL_LIGHT0);


  qDebug() << "ShadowViewer OpenGL: " << (char *)glGetString(GL_VERSION);
}
