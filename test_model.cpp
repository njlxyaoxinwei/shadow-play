#include <iostream>

#include "model.h"

int main(int argc, char const *argv[]) {
  bool pass = true;
  Model *m = new Model("../data/xy63.dragon.200.stl");
  int nMesh = 1;
  int nFace = 200;
  printf("%s\n", "Testing on Dragon 200");
  printf("Should have %d mesh: %lu\n", nMesh, m->meshes.size());
  pass &= (nMesh == m->meshes.size());
  Mesh mesh = m->joined_mesh();
  printf("Should have %d faces: %lu\n", nFace, mesh.indices.size() / 3);
  pass &= (nFace == mesh.indices.size() / 3);
  printf("Should have %d vertices: %lu\n", nFace * 3, mesh.vertices.size());
  pass &= (nFace * 3 == mesh.vertices.size());
  if (pass) {
    printf("PASS\n");
  } else {
    printf("FAIL\n");
  }
  return pass;
}
