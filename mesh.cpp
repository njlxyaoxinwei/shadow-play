

#include <glm/glm.hpp>

#include "mesh.h"

namespace {
  using glm::vec3;
} // namespace

vec3 Mesh::center_mesh() {
  vec3 center(0, 0, 0);
  const float r = 1 / float(vertices.size());
  for (const auto& v : vertices) {
    center += v.Position * r;
  }
  for (auto& v : vertices) {
    v.Position -= center;
  }
  return center;
}

void Mesh::normalize_coords() {
  vec3 maxv(1, 1, 1);
  for (const auto& v : vertices) {
    maxv = glm::max(maxv, glm::abs(v.Position));
  }
  float normalizer = 1 / (std::max(maxv.x, std::max(maxv.y, maxv.z)));
  for (auto& v : vertices) {
    v.Position = v.Position * normalizer;
  }
}

Mesh& Mesh::operator+=(const Mesh& new_mesh) {
  const auto offset = vertices.size();
  vertices.insert(vertices.end(), 
      new_mesh.vertices.begin(), new_mesh.vertices.end());
  for (const auto& i : new_mesh.indices) {
    indices.push_back(i + offset);
  }
}
