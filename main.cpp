#include <string>

#include <qapplication.h>
#include <qsplitter.h>

#include "helpers.h"
#include "model.h"
#include "viewer.h"
#include "shadowViewer.h"

namespace {
  using std::string;
  using std::vector;

  Mesh GetMeshFromPath(const string& path) {
    Model m(path);
    if (m.meshes.empty()) {
      Die("No Mesh Detected in file " + path);
    }
    return m.joined_mesh();
  }
} // namespace

int main(int argc, char** argv) {
  QApplication app(argc, argv);

  // Get Model Path
  vector<Mesh> meshes;
  for (int i = 1; i < argc; i++) {
    const auto& path = QApplication::arguments().at(i).toStdString();
    meshes.push_back(GetMeshFromPath(path));
  }
  // Create Scene
  Scene* s = new Scene(meshes);

  // Create Splitters
  QSplitter *hSplit  = new QSplitter(Qt::Horizontal);
  Viewer v1(s, hSplit);
  ShadowViewer v2(s, hSplit, &v1);

  hSplit->setWindowTitle("Shadow Play");
  hSplit->show();

  return app.exec();
}
