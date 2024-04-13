#ifndef A1_MAZE_CPP_1_VIEW_FILE_HANDLER_FILE_HANDLER_H_
#define A1_MAZE_CPP_1_VIEW_FILE_HANDLER_FILE_HANDLER_H_

#include "Controller/Controller.h"
#include "View/EventHandler/EventHandler.h"
#include "common/MazeData.h"

namespace s21 {
class FileHandler final : public QObject {
  Q_OBJECT

 public:
  static FileHandler &Get(Controller *controller) {
    static FileHandler instance{controller};
    return instance;
  }
  void SetMaze(const MazeData *p_maze_data) { p_maze_data_ = p_maze_data; }

  ~FileHandler() override = default;

  void Load(const std::string &file_name) {
    const auto result{controller_->LoadFile(file_name)};
    if (!result.error) {
      emit EventFileLoaded(result.maze_data);
    }
  }

  void Save(const std::string &file_name) {
    const int error_code = controller_->SaveFile(file_name, *p_maze_data_);
    emit EventFileSaved(error_code);
  }

 signals:
  void EventFileLoaded(const s21::MazeData &maze_data);
  void EventFileSaved(int error_code);

 private:
  explicit FileHandler(Controller *controller) : controller_(controller) {
    connect(&EventHandler::Get(), &EventHandler::EventLoadAnotherFile, this,
            &FileHandler::Load);

    connect(&EventHandler::Get(), &EventHandler::EventSaveFile, this,
            &FileHandler::Save);

    connect(this, &FileHandler::EventFileLoaded, &EventHandler::Get(),
            &EventHandler::FileHandlerFileLoaded);
    connect(this, &FileHandler::EventFileSaved, &EventHandler::Get(),
            &EventHandler::FileHandlerFileSaved);
  }

  Controller *controller_;
  const MazeData *p_maze_data_{nullptr};
};
}  // namespace s21

#endif  // A1_MAZE_CPP_1_VIEW_FILE_HANDLER_FILE_HANDLER_H_