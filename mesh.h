#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>

#include <vector>

struct Vertex {
  // Position
  glm::vec3 Position;
  // Normal
  glm::vec3 Normal;
};

class Mesh {
 public:
  /* Mesh Data */
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

  Mesh() {};

  Mesh(const std::vector<Vertex>& vs, 
       const std::vector<unsigned int>& is) {
    vertices = vs;
    indices = is;
  };
  ~Mesh() {};

  // Move mesh to the center of local coordinates
  glm::vec3 center_mesh();

  // Normalized device coordinates to [-1, 1]
  void normalize_coords();

  // Mesh& operator+=(const Mesh& mesh);
  
 };

#endif
