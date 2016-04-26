#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>

#include <assimp/scene.h>

#include "mesh.h"

class Model {
 public:
  std::vector<Mesh> meshes;
  Model(const std::string& path) {
    loadModel_(path);
  }
  ~Model() {};
  Mesh joined_mesh() const;

 private:
  bool loadModel_(const std::string& path);
  Mesh processMesh_(aiMesh* mesh);
};


#endif
