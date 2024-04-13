#include "Model.h"

namespace s21 {
LoadResult Model::LoadFile(const std::string &file_name) {
  return maze_loader_.LoadFile(file_name);
}

int Model::SaveFile(const std::string &file_name, const MazeData &maze_data) {
  return maze_saver_.SaveFile(file_name, maze_data);
}

std::stack<std::pair<int, int> > Model::CalculateSolution(
    const MazeData &maze_data, const std::pair<int, int> &begin,
    const std::pair<int, int> &end) {
  return maze_solver_.CalculateSolution(maze_data, begin, end);
}

bool Model::AreAllCellsReachable(const MazeData &maze_data) {
  return maze_solver_.AreAllCellsReachable(maze_data);
}

MazeData Model::GenerateMaze(const int rows, const int columns,
                             const bool random_figure_flag) {
  return maze_generator_.Generate(rows, columns, random_figure_flag);
}
}  // namespace s21
