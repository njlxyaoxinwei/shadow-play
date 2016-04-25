#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"

class Model {
 public:
  std::vector<Mesh> meshes;
  Model(const std::string& path) {
    loadModel_(path);
  }
  ~Model() {};

 private:
  bool loadModel_(const std::string& path);
  Mesh processMesh_(aiMesh* mesh);
};


#endif
