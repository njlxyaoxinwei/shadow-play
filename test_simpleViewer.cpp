#include <iostream>
#include <string>

#include <qapplication.h>

#include "helpers.h"
#include "model.h"
#include "simpleViewer.h"

namespace {
  using std::string;

  Mesh GetMeshFromPath(const string& path) {
    Model m(path);
    if (m.meshes.empty()) {
      Die("No Mesh Detected!");
    }
    return m.joined_mesh();
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
