#include <iostream>
#include <string>

#include <qapplication.h>

#include "mesh.h"
#include "model.h"
#include "simpleViewer.h"

namespace {
  using std::string;
  using std::endl;
  using std::cerr;

  template<typename T>
  void Die(const T& str) {
    cerr << "ERROR:: " << str << endl;
    exit(EXIT_FAILURE);
  }

  Mesh GetMeshFromPath(const string& path) {
    Model m(path);
    if (m.meshes.size() > 0) {
      return m.meshes[0];
    } else {
      Die("No Mesh Detected!");
    }
  }
} // namespace



int main(int argc, char** argv) {

  // Read command lines arguments.
  QApplication app(argc, argv);
  
  // Get model path
  const auto& path = QApplication::arguments().at(1).toStdString();

  // Instantiate the Viewer.
  Viewer viewer(GetMeshFromPath(path));
  
  viewer.setWindowTitle("Mesh Viewer");
  
  // Make the viewer window visible on screen.
  viewer.show();

  // Run main loop.
  return app.exec();
}
