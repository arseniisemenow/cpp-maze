#ifndef A1_MAZE_CPP_1_MODEL_MAZE_GENERATOR_MAZE_GENERATOR_H_
#define A1_MAZE_CPP_1_MODEL_MAZE_GENERATOR_MAZE_GENERATOR_H_

#include <random>

#include "common/MazeData.h"

namespace s21 {
class MazeGenerator {
 public:
  [[nodiscard]] MazeData Generate(int rows, int columns,
                                  bool random_figure_flag);
  static void InitSetsMatrix(std::vector<std::vector<int>> &matrix, int rows,
                             int columns);
  static void PrintSetsMatrix(const std::vector<std::vector<int>> &matrix);
};

}  // namespace s21

#endif  // A1_MAZE_CPP_1_MODEL_MAZE_GENERATOR_MAZE_GENERATOR_H_
