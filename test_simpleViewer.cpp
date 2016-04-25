#include "simpleViewer.h"
#include <qapplication.h>

int main(int argc, char** argv) {
  // Read command lines arguments.
  QApplication app(argc, argv);
  
  // Instantiate the Viewer.
  Viewer viewer("../data/eight.off");
  
  viewer.setWindowTitle("Mesh Viewer");
  
  // Make the viewer window visible on screen.
  viewer.show();

  // Run main loop.
  return app.exec();
}
