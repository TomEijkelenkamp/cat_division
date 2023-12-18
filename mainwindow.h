#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>

#include "mesh/mesh.h"
#include "subdivision/subdivider.h"
#include "limitprojection/limitprojector.h"

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class represents the main window.
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

 private slots:
  void on_LoadOBJ_pressed();
  void on_MeshPresetComboBox_currentTextChanged(const QString &meshName);
  void on_SubdivSteps_valueChanged(int subdivLevel);
  void on_TessellationCheckBox_toggled(bool checked);
  void on_RegularPatchSplineCheckBox_toggled(bool checked);
  void on_LimitProjectionCheckBox_toggled(bool checked);
  void on_MeshCheckBox_toggled(bool checked);

 private:
  void importOBJ(const QString &fileName);

  Ui::MainWindow *ui;
  Subdivider *subdivider;
  Limitprojector *limitprojector;
  QVector<Mesh> meshes;
  Mesh mesh;
};

#endif  // MAINWINDOW_H
