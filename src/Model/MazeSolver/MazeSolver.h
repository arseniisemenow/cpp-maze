#ifndef A1_MAZE_CPP_1_MODEL_MAZE_SOLVER_MAZE_SOLVER_H_
#define A1_MAZE_CPP_1_MODEL_MAZE_SOLVER_MAZE_SOLVER_H_

#include <array>
#include <iostream>
#include <stack>

#include "common/MazeData.h"

namespace s21 {
class MazeSolver {
 public:
  std::stack<std::pair<int, int>> CalculateSolution(
      const MazeData &maze_data, const std::pair<int, int> &begin,
      const std::pair<int, int> &end);

  [[nodiscard]] bool AreAllCellsReachable(const MazeData &maze_data);

 private:
  struct CellNode {
    std::pair<int, int> coordinate{};
    int cost_from_start{};
    int estimate_cost{};

    CellNode *next{};

    CellNode(std::pair<int, int> coord, CellNode *next = nullptr)
        : coordinate{coord}, next{next} {}

    [[nodiscard]] int GetScore() const {
      return cost_from_start + estimate_cost;
    }
  };

 private:
  std::stack<std::pair<int, int>> PerformAStarAlgorithm(
      const MazeData &maze_data, std::pair<int, int> begin,
      std::pair<int, int> end);

  CellNode *GetNodeWithMinimumScore(
      std::vector<CellNode *>::iterator &current_iter);
  void CheckAllDirections(CellNode *current,
                          const std::array<std::pair<int, int>, 4> &directions,
                          const MazeData &maze_data, std::pair<int, int> end);
  bool IsColliding(const MazeData &maze_data,
                   std::pair<int, int> new_coordinate,
                   std::pair<int, int> direction,
                   std::pair<int, int> old_coordinate);
  CellNode *FindNode(const std::vector<CellNode *> &nodes,
                     std::pair<int, int> coordinate);
  int ManhattanHeuristic(std::pair<int, int> begin, std::pair<int, int> end);

  void ClearSets();

 private:
  std::vector<CellNode *> open_set_{};
  std::vector<CellNode *> closed_set_{};
};
}  // namespace s21

#endif  // A1_MAZE_CPP_1_MODEL_MAZE_SOLVER_MAZE_SOLVER_H_