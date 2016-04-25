#include <iostream>

#include "model.h"

int main(int argc, char const *argv[]) {
  Model *m = new Model("data/eight.off");
  printf("%i\n", m->meshes.size());
  for (const auto& mesh : m->meshes) {
    printf("%i %i\n", mesh.vertices.size(), mesh.indices.size());
  }
  return 0;
}
