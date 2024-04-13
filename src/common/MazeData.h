#ifndef A1_MAZE_CPP_1_COMMON_MAZE_DATA_H_
#define A1_MAZE_CPP_1_COMMON_MAZE_DATA_H_

#include <vector>

namespace s21 {
struct MazeData {
  std::vector<std::vector<bool>> matrix_vertical_walls{};
  std::vector<std::vector<bool>> matrix_horizontal_walls{};

  MazeData() = default;
  MazeData(const int rows, const int columns) {
    matrix_vertical_walls.resize(rows);
    matrix_horizontal_walls.resize(rows);

    for (int i = 0; i < rows; ++i) {
      matrix_vertical_walls[i].resize(columns);
      matrix_horizontal_walls[i].resize(columns);
    }
  }
  MazeData(
      const std::vector<std::vector<bool>> &other_matrix_vertical_walls,
      const std::vector<std::vector<bool>> &other_matrix_horizontal_walls) {
    matrix_vertical_walls = other_matrix_vertical_walls;
    matrix_horizontal_walls = other_matrix_horizontal_walls;
  }
  void Clear() {
    matrix_vertical_walls.clear();
    matrix_horizontal_walls.clear();
  }

  [[nodiscard]] int GetRows() const { return matrix_vertical_walls.size(); }
  [[nodiscard]] int GetColumns() const {
    if (matrix_vertical_walls.size() != 0) {
      return matrix_vertical_walls[0].size();
    }
    return 0;
  }
};
}  // namespace s21

#endif  // A1_MAZE_CPP_1_COMMON_MAZE_DATA_H_