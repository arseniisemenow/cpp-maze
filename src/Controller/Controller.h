#ifndef A1_MAZE_CPP_1_CONTROLLER_CONTROLLER_H_
#define A1_MAZE_CPP_1_CONTROLLER_CONTROLLER_H_

#include <stack>
#include <string>

#include "Model/Model.h"
#include "common/LoadResult.h"

namespace s21 {
class Controller {
 public:
  explicit Controller(Model *model) : model_(model) {}

  [[nodiscard]] LoadResult LoadFile(const std::string &file_name) const;
  int SaveFile(const std::string &file_name, const MazeData &maze_data) const;

  [[nodiscard]] std::stack<std::pair<int, int>> CalculateSolution(
      const MazeData &maze_data, const std::pair<int, int> &begin,
      const std::pair<int, int> &end) const;
  [[nodiscard]] bool AreAllCellsReachable(const MazeData &maze_data) const;

  [[nodiscard]] MazeData GenerateMaze(int rows, int columns,
                                      bool random_figure_flag) const;

 private:
  Model *model_;
};

}  // namespace s21

#endif  // A1_MAZE_CPP_1_CONTROLLER_CONTROLLER_H_
