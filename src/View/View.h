#ifndef A1_MAZE_CPP_1_VIEW_VIEW_H_
#define A1_MAZE_CPP_1_VIEW_VIEW_H_

#include <QMainWindow>

#include "Controller/Controller.h"
#include "View/GridWidget/GridWidget.h"
#include "View/InputManager/InputManager.h"
#include "View/modal_widgets/AboutWindow/AboutWindow.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class View;
}

QT_END_NAMESPACE

namespace s21 {
class View final : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr, Controller *controller = nullptr);
  ~View();

 private:
  void SetupMenuBar();
  void OpenAboutWindow() const;
  void CloseAboutWindow() const;
  void CloseViewWindow();
  void UpdateStyles();

 private:
  Ui::View *ui_;
  Controller *controller_;
  AboutWindow *about_window_;
  InputManager *input_manager_;

  MazeData maze_data_{};
  std::pair<int, int> begin_{};
  std::pair<int, int> end_{};
  std::stack<std::pair<int, int>> solution_;
};
}  // namespace s21

#endif  // A1_MAZE_CPP_1_VIEW_VIEW_H_
