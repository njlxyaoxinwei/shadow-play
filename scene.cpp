#include "scene.h"

#include <fstream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QGLViewer/qglviewer.h>
#include <QGLViewer/manipulatedFrame.h>

#include "helpers.h"
#include "mesh.h"

namespace {
  using glm::vec3;
  using glm::vec4;
  using glm::mat4;
  using qglviewer::ManipulatedFrame;
  using qglviewer::Vec;
  using std::vector;
  using std::max;
  using std::ofstream;
  using std::endl;

  vec3 ApplyMat4ToPoint(const mat4& mat, const vec3& p) {
    vec3 np(mat * vec4(p, 1));
    return np;
  }
} // namespace

Scene::Scene(const vector<Mesh>& ms) 
    : meshes(ms),
      n(ms.size()),
      radius(max(n, 3)),
      light_frame(new ManipulatedFrame()) {
  // Initialize mesh frames and light
  light_frame->setPosition(0, 0, 3);
  mesh_frames.resize(n);
  for (int i = 0; i < n; i++) {
    mesh_frames[i] = new ManipulatedFrame();
    mesh_frames[i]->setPosition(2 * i + 1 - n, 0, 1);
  }
}

Scene::~Scene() {
  for (int i = 0; i < n; i++) {
    delete mesh_frames[i];
  }
  mesh_frames.clear();
}

void Scene::exportScene() const {
  if (n == 0) {
    LogError("No Meshes to export!");
    return;
  }
  ofstream file("meshes.off");
  // Build Accumulator Mesh
  Mesh acc;
  for (int i = 0; i < n; i++) {
    const auto& mesh = meshes[i];
    unsigned int nv = mesh.vertices.size();
    vector<Vertex> vs(nv);
    const auto& newps = meshVertexWorldPositions(i);
    for (unsigned int j = 0; j < nv; j++) {
      vs[j].Position = newps[j];
    }
    acc += Mesh(vs, mesh.indices);
  }

  // Export acc
  file << "OFF" << endl;
  file << "# Created with Shadow Play by David Yao" << endl;
  Vec pos = light_frame->position();
  file << "# Point light at " << pos.x << " " << pos.y << " " << pos.z << endl;
  file << acc.vertices.size() << " " << acc.indices.size() / 3 << " 0" << endl;
  for (const auto& v : acc.vertices) {
    vec3 p = v.Position;
    file << p.x << " " << p.y << " " << p.z << endl;
  }
  for (unsigned int i = 0; i < acc.indices.size() / 3; i++) {
    unsigned int index = i * 3;
    file << 3 << " " << 
        acc.indices[index] << " " << 
        acc.indices[index+1] << " " <<
        acc.indices[index+2] << endl;
  }
  file.close();
}

vector<vec3> Scene::meshVertexWorldPositions(const int& index) const {
  mat4 mat = glm::make_mat4(mesh_frames[index]->worldMatrix());
  unsigned int nv = meshes[index].vertices.size();
  vector<vec3> result(nv);
  for (unsigned int i = 0; i < nv; i++) {
    result[i] = ApplyMat4ToPoint(mat, meshes[index].vertices[i].Position);
  }
  return result;
}

