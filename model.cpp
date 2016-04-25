#include <string>
#include <iostream>

#include <assimp/Importer.hpp>

#include "mesh.h"
#include "model.h"

namespace {
  using std::vector;
  using std::string;
  using std::cerr;
  using std::endl;
  using glm::vec3;


  typedef unsigned int uint;

  template<typename T, typename S>
  T ConvertVector(const S& v1) {
    T v2;
    v2.x = v1.x;
    v2.y = v1.y;
    v2.z = v1.z;
    return v2;
  }
} // namespace

bool Model::loadModel_(const string& path) {
  // Read file via Assimp
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(
      path, aiProcess_Triangulate | aiProcess_GenNormals);

  // Check for errors
  if (!scene 
      || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE 
      || !scene->mRootNode) {
    cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
    return false;
  }
  for (uint i = 0; i < scene->mNumMeshes; i++) {
    aiMesh* mesh = scene->mMeshes[i];
    meshes.push_back(processMesh_(mesh));
  }
  return true;
}

Mesh Model::processMesh_(aiMesh* mesh) {
  vector<Vertex> vertices;
  vector<uint> indices;
  
  for (uint i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;
    const auto& v = mesh->mVertices[i];
    const auto& n = mesh->mNormals[i];
    vec3 v2;
    // Positions
    v2 = ConvertVector<vec3>(v);
    vertex.Position = v2;
    // Normals
    vertex.Normal = ConvertVector<vec3>(n);
    vertices.push_back(vertex);
  }

  for (uint i = 0; i < mesh->mNumFaces; i++) {
    const auto& face = mesh->mFaces[i];
    for (uint j = 0; j < face.mNumIndices; j++) {
      indices.push_back(face.mIndices[j]);
    }
  }

  return Mesh(vertices, indices);
}
