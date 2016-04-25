#include <string>

#include <QDebug>

#include "model.h"
#include "simpleViewer.h"

namespace {
  using std::string;

} // namepsace

Viewer::Viewer(const string& path) : model_(path) {}


void Viewer::draw() {

  // draw first mesh
  const auto& mesh = model_.meshes[0];
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

void Viewer::init() {
  // Restore previous viewer state.
  restoreStateFromFile();
  // Opens help window
  // help();
} 
