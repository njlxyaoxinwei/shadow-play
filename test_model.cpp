#include <iostream>

#include "model.h"

int main(int argc, char const *argv[]) {
  Model *m = new Model("data/eight.off");
  printf("%lu\n", m->meshes.size());
  for (const auto& mesh : m->meshes) {
    printf("%lu %lu\n", mesh.vertices.size(), mesh.indices.size());
  }
  return 0;
}
