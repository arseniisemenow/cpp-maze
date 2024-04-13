#include "Controller.h"

namespace s21 {
[[nodiscard]] LoadResult Controller::LoadFile(
    const std::string &file_name) const {
  return model_->LoadFile(file_name);
}

[[nodiscard]] int Controller::SaveFile(const std::string &file_name,
                                       const MazeData &maze_data) const {
  return model_->SaveFile(file_name, maze_data);
}

[[nodiscard]] std::stack<std::pair<int, int>> Controller::CalculateSolution(
    const MazeData &maze_data, const std::pair<int, int> &begin,
    const std::pair<int, int> &end) const {
  return model_->CalculateSolution(maze_data, begin, end);
}

[[nodiscard]] bool Controller::AreAllCellsReachable(
    const MazeData &maze_data) const {
  return model_->AreAllCellsReachable(maze_data);
};

[[nodiscard]] MazeData Controller::GenerateMaze(
    const int rows, const int columns, const bool random_figure_flag) const {
  return model_->GenerateMaze(rows, columns, random_figure_flag);
}

}  // namespace s21
