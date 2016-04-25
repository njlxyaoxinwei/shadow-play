#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>

#include <vector>

/* Header only Mesh Class */

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

  Mesh(const std::vector<Vertex>& vs, 
       const std::vector<unsigned int>& is) {
    vertices = vs;
    indices = is;
  };
  ~Mesh();
  
};

#endif
