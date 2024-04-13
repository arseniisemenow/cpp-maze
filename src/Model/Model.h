#ifndef A1_MAZE_CPP_1_MODEL_MODEL_H_
#define A1_MAZE_CPP_1_MODEL_MODEL_H_

#include <stack>

#include "Model/MazeGenerator/MazeGenerator.h"
#include "Model/MazeLoader/MazeLoader.h"
#include "Model/MazeSaver/MazeSaver.h"
#include "Model/MazeSolver/MazeSolver.h"

namespace s21 {
class Model {
 public:
  Model() = default;

  LoadResult LoadFile(const std::string &file_name);
  int SaveFile(const std::string &file_name, const MazeData &maze_data);

  std::stack<std::pair<int, int>> CalculateSolution(
      const MazeData &maze_data, const std::pair<int, int> &begin,
      const std::pair<int, int> &end);

  [[nodiscard]] bool AreAllCellsReachable(const MazeData &maze_data);

  MazeData GenerateMaze(int rows, int columns, bool random_figure_flag);

 private:
  MazeLoader maze_loader_{};
  MazeSaver maze_saver_{};

  MazeSolver maze_solver_{};
  MazeGenerator maze_generator_{};
};
}  // namespace s21

#endif  // A1_MAZE_CPP_1_MODEL_MODEL_H_