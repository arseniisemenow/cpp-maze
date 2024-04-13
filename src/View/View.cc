#include "View/View.h"

#include "./ui_View.h"
#include "EventHandler/EventHandler.h"
#include "FileHandler/FileHandler.h"
#include "View/MenuBar/MenuBar.h"

namespace s21 {
View::View(QWidget *parent, Controller *controller)
    : QMainWindow(parent),
      ui_(new Ui::View),
      controller_(controller),
      about_window_(new AboutWindow()),
      input_manager_(new InputManager()) {
  ui_->setupUi(this);
  ui_->grid_widget->SetPointers(&solution_, &maze_data_, &begin_, &end_);
  SetupMenuBar();
  FileHandler::Get(controller_).SetMaze(&maze_data_);

  ui_->grid_layout->addWidget(input_manager_);

  connect(&EventHandler::Get(), &EventHandler::EventActionAboutTriggered, this,
          &View::OpenAboutWindow);

  connect(
      &EventHandler::Get(), &EventHandler::EventPathSourceOrDestinationChanged,
      [=](const std::pair<const std::pair<int, int>, const std::pair<int, int>>
              pair) {
        solution_ = controller_->CalculateSolution(maze_data_, begin_, end_);
      });

  connect(&EventHandler::Get(), &EventHandler::EventMazeSizeChanged,
          [=](const std::pair<int, int> &maze_size, bool random_figure_flag) {
            maze_data_ = controller_->GenerateMaze(
                maze_size.first, maze_size.second, random_figure_flag);
          });

  maze_data_ = controller_->GenerateMaze(constants::kDefaultRows,
                                         constants::kDefaultColumns, false);
  UpdateStyles();
}

View::~View() { delete ui_; }

void View::SetupMenuBar() {
  const auto menu_bar_widget = new MenuBar(this);

  QMenu *view_menu = menu_bar_widget->addMenu(tr("s21_maze"));

  auto *about_action = new QAction(tr("About"), this);
  connect(about_action, &QAction::triggered, &EventHandler::Get(),
          &EventHandler::ActionAboutTriggered);
  view_menu->addAction(about_action);

  const auto action_quit = new QAction(tr("Quit"), this);
  connect(action_quit, &QAction::triggered, &EventHandler::Get(),
          &EventHandler::CloseViewWindow);

  menu_bar_widget->SetupMenuBar();

  setMenuBar(menu_bar_widget);
}

void View::OpenAboutWindow() const { about_window_->show(); }

void View::CloseAboutWindow() const { about_window_->close(); }

void View::CloseViewWindow() {
  CloseAboutWindow();
  this->close();
}
void View::UpdateStyles() {
  this->setStyleSheet(GetStylesFromFile(PATH_MAIN_WINDOW_STYLES_FILE));
}
}  // namespace s21
