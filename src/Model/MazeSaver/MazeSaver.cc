#include "MazeSaver.h"

#include <fstream>
#include <iostream>

namespace s21 {
int MazeSaver::SaveFile(const std::string &file_name,
                        const MazeData &maze_data) {
  std::ofstream file(file_name);
  if (!file.is_open()) {
    return 1;
  }

  file << maze_data.matrix_horizontal_walls.size() << " "
       << maze_data.matrix_vertical_walls.size() << "\n";

  for (const auto &row : maze_data.matrix_vertical_walls) {
    for (int wall : row) {
      file << wall << " ";
    }
    file << "\n";
  }

  file << "\n";

  for (const auto &row : maze_data.matrix_horizontal_walls) {
    for (int wall : row) {
      file << wall << " ";
    }
    file << "\n";
  }

  file.close();

  return 0;
}

}  // namespace s21
