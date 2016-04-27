#include <string>

#include <qapplication.h>
#include <qsplitter.h>

#include "helpers.h"
#include "model.h"
#include "viewer.h"

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
  QApplication app(argc, argv);

  if (argc <= 1) {
    Die("No Path Specified!");
  }
  // Get Model Path
  const auto& path = QApplication::arguments().at(1).toStdString();
  // Create Scene
  Scene* s = new Scene(GetMeshFromPath(path));

  // Create Splitters
  QSplitter *hSplit  = new QSplitter(Qt::Vertical);
  Viewer v1(s, hSplit);
  Viewer v2(s, hSplit, &v1);

  hSplit->setWindowTitle("Two Viewer");
  hSplit->show();

  return app.exec();
}
