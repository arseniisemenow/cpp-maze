#ifndef A1_MAZE_CPP_1_VIEW_EVENT_HANDLER_EVENT_HANDLER_H_
#define A1_MAZE_CPP_1_VIEW_EVENT_HANDLER_EVENT_HANDLER_H_

#include <QObject>

#include "common/MazeData.h"

namespace s21 {
class EventHandler final : public QObject {
  Q_OBJECT

 public:
  ~EventHandler() override = default;

 public:
  static EventHandler &Get() {
    static EventHandler instance{};
    return instance;
  }

 public slots:
  /* actions */
  void ActionLoadFileTriggered() { emit EventActionLoadFileTriggered(); }

  void ActionSaveFileTriggered() { emit EventActionSaveFileTriggered(); }

  void ActionAboutTriggered() { emit EventActionAboutTriggered(); }

  /* Call this from FileDialog */
  void FileIsSelected(const QString &file_name) {
    emit EventFileIsSelected(file_name);
  }

  void CloseViewWindow() { emit EventCloseViewWindow(); }

  /* FileDialog */
  void FileDialogSelectButtonClicked() {
    emit EventFileDialogSelectButtonClicked();
  }

  void FileDialogOpenFile() { emit EventFileDialogOpenFile(); }

  void FileDialogCloseWindow() { emit EventFileDialogCloseWindow(); }

  void OpenFileDialogToLoadFile() { emit EventOpenFileDialogToLoadFile(); }
  void OpenFileDialogToSaveFile() { emit EventOpenFileDialogToSaveFile(); }

  /* FileHandler */
  void FileHandlerFileLoaded(const s21::MazeData &maze_data) {
    emit EventFileHandlerFileLoaded(maze_data);
  }
  void FileHandlerFileSaved(const int error_code) {
    emit EventFileHandlerFileSaved(error_code);
  }

  /* MenuBar */

  void LoadAnotherFile(const std::string &file_name) {
    emit EventLoadAnotherFile(file_name);
  }
  void SaveFile(const std::string &file_name) { emit EventSaveFile(file_name); }

  /* SpinBox */
  void LeftMouseButtonPressed(const QPoint &pressed_pos) {
    emit EventLeftMouseButtonPressed(pressed_pos);
  }

  void LeftMouseButtonReleased(const QPoint &released_pos) {
    emit EventLeftMouseButtonReleased(released_pos);
  }

  /* InputManager */
  void MazeSizeChanged(const std::pair<int, int> &maze_size,
                       const bool random_figure_flag) {
    emit EventMazeSizeChanged(maze_size, random_figure_flag);
  }

  /* GridWidget */
  void PathSourceOrDestinationChanged(
      const std::pair<const std::pair<int, int>, const std::pair<int, int>>
          pair) {
    emit EventPathSourceOrDestinationChanged(pair);
  }

 signals:
  void EventActionSaveFileTriggered();
  void EventFileIsSelected(const QString &);
  void EventActionLoadFileTriggered();
  void EventActionAboutTriggered();
  void EventCloseViewWindow();

  /* FileDialog */
  void EventFileDialogSelectButtonClicked();
  void EventFileDialogOpenFile();
  void EventFileDialogCloseWindow();
  void EventOpenFileDialogToLoadFile();
  void EventOpenFileDialogToSaveFile();

  /* FileHandler */
  void EventFileHandlerFileLoaded(const MazeData &maze_data);
  void EventFileHandlerFileSaved(int error_code);

  /* MenuBar */

  void EventLoadAnotherFile(const std::string &);
  void EventSaveFile(const std::string &);

  /* SpinBox */
  void EventLeftMouseButtonPressed(const QPoint &pressed_pos);
  void EventLeftMouseButtonReleased(const QPoint &released_pos);

  /* InputManager */
  void EventMazeSizeChanged(const std::pair<int, int> &maze_size, bool);

  /* GridWidget */

  void EventPathSourceOrDestinationChanged(
      std::pair<const std::pair<int, int>, const std::pair<int, int>> pair);

 private:
  EventHandler() = default;
};
}  // namespace s21

#endif  // A1_MAZE_CPP_1_VIEW_EVENT_HANDLER_EVENT_HANDLER_H_