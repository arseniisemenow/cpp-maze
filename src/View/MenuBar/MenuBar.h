#ifndef A1_MAZE_CPP_1_VIEW_MENU_BAR_MENU_BAR_H_
#define A1_MAZE_CPP_1_VIEW_MENU_BAR_MENU_BAR_H_

#include <QAction>
#include <QApplication>
#include <QFileDialog>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>

namespace s21 {
class MenuBar final : public QMenuBar {
  Q_OBJECT

 public:
  explicit MenuBar(QWidget* parent = nullptr) : QMenuBar(parent) {}
  void SetupMenuBar();

  void OpenFileDialogToLoadFile();
  void OpenFileDialogToSaveFile();

  void UpdateStyles();

  void LoadAnotherFile(const std::string& file_name) {
    emit EventLoadAnotherFile(file_name);
  }

  void SaveFile(const std::string& file_name) { emit EventSaveFile(file_name); }

 signals:
  void EventLoadAnotherFile(const std::string&);
  void EventSaveFile(const std::string&);
};
}  // namespace s21

#endif  // A1_MAZE_CPP_1_VIEW_MENU_BAR_MENU_BAR_H_