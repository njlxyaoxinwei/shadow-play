#include <iostream>
#include <string>

#include <qapplication.h>

#include "simpleViewer.h"

namespace {
  using std::string;
} // namespace



int main(int argc, char** argv) {

  // Read command lines arguments.
  QApplication app(argc, argv);
  
  // Get model path
  const auto& path = QApplication::arguments().at(1).toStdString();

  // Instantiate the Viewer.
  Viewer viewer(path);
  
  viewer.setWindowTitle("Mesh Viewer");
  
  // Make the viewer window visible on screen.
  viewer.show();

  // Run main loop.
  return app.exec();
}
