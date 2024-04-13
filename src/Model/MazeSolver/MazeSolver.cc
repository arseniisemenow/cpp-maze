#include "MazeSolver.h"

#include "DirectionType.h"
#include "common/constants.h"

namespace s21 {

std::stack<std::pair<int, int>> MazeSolver::CalculateSolution(
    const MazeData &maze_data, const std::pair<int, int> &begin,
    const std::pair<int, int> &end) {
  if (maze_data.GetRows() <= 0 || maze_data.GetColumns() <= 0) {
    return {};
  }

  std::stack<std::pair<int, int>> solution{
      PerformAStarAlgorithm(maze_data, begin, end)};

  return solution;
}

std::stack<std::pair<int, int>> MazeSolver::PerformAStarAlgorithm(
    const MazeData &maze_data, const std::pair<int, int> begin,
    const std::pair<int, int> end) {
  constexpr std::array<std::pair<int, int>, 4> directions{
      {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};

  open_set_.push_back(new CellNode{begin});

  CellNode *current{nullptr};
  while (!open_set_.empty()) {
    auto current_iter{open_set_.begin()};
    current = GetNodeWithMinimumScore(current_iter);

    if (current->coordinate == end) {
      break;
    }

    closed_set_.push_back(current);
    open_set_.erase(current_iter);

    CheckAllDirections(current, directions, maze_data, end);
  }

  std::stack<std::pair<int, int>> solution{};
  while (current != nullptr) {
    solution.push(current->coordinate);
    current = current->next;
  }

  ClearSets();

  return solution;
}

MazeSolver::CellNode *MazeSolver::GetNodeWithMinimumScore(
    std::vector<CellNode *>::iterator &current_iter) {
  CellNode *current{*current_iter};
  for (auto iter{open_set_.begin()}; iter != open_set_.end(); ++iter) {
    CellNode *node{*iter};
    if (node->GetScore() <= current->GetScore()) {
      current = node;
      current_iter = iter;
    }
  }

  return current;
}

void MazeSolver::CheckAllDirections(
    CellNode *current, const std::array<std::pair<int, int>, 4> &directions,
    const MazeData &maze_data, std::pair<int, int> end) {
  for (int i{0}; i < 4; ++i) {
    std::pair<int, int> new_coordinate{
        current->coordinate.first + directions[i].first,
        current->coordinate.second + directions[i].second};

    if (IsColliding(maze_data, new_coordinate, directions[i],
                    current->coordinate) ||
        FindNode(closed_set_, new_coordinate)) {
      continue;
    }

    const int total_cost{current->cost_from_start + constants::kStepCost};

    CellNode *successor{FindNode(open_set_, new_coordinate)};
    if (successor == nullptr) {
      successor = new CellNode{new_coordinate, current};
      successor->cost_from_start = total_cost;
      successor->estimate_cost = ManhattanHeuristic(successor->coordinate, end);
      open_set_.push_back(successor);
    } else if (total_cost < successor->cost_from_start) {
      successor->next = current;
      successor->cost_from_start = total_cost;
    }
  }
}

bool MazeSolver::IsColliding(const MazeData &maze_data,
                             const std::pair<int, int> new_coordinate,
                             const std::pair<int, int> direction,
                             const std::pair<int, int> old_coordinate) {
  const int rows{maze_data.GetRows()};
  const int cols{maze_data.GetColumns()};

  bool is_colliding{false};
  if (new_coordinate.first >= rows || new_coordinate.second >= cols ||
      new_coordinate.first < 0 || new_coordinate.second < 0) {
    is_colliding = true;
  } else {
    DirectionType direction_type{constants::kDirectionMap.at(direction)};

    if (direction_type == DirectionType::kUp) {
      is_colliding = maze_data.matrix_vertical_walls[new_coordinate.first]
                                                    [new_coordinate.second];
    } else if (direction_type == DirectionType::kDown) {
      is_colliding = maze_data.matrix_vertical_walls[old_coordinate.first]
                                                    [old_coordinate.second];
    } else if (direction_type == DirectionType::kRight) {
      is_colliding = maze_data.matrix_horizontal_walls[old_coordinate.first]
                                                      [old_coordinate.second];
    } else if (direction_type == DirectionType::kLeft) {
      is_colliding = maze_data.matrix_horizontal_walls[new_coordinate.first]
                                                      [new_coordinate.second];
    }
  }

  return is_colliding;
}

MazeSolver::CellNode *MazeSolver::FindNode(
    const std::vector<CellNode *> &nodes,
    const std::pair<int, int> coordinate) {
  for (const auto &node : nodes) {
    if (node->coordinate == coordinate) {
      return node;
    }
  }

  return nullptr;
}

int MazeSolver::ManhattanHeuristic(std::pair<int, int> begin,
                                   std::pair<int, int> end) {
  std::pair<int, int> delta{std::abs(begin.first - end.first),
                            std::abs(begin.second - end.second)};
  return constants::kStepCost * (delta.first + delta.second);
}

bool MazeSolver::AreAllCellsReachable(const MazeData &maze_data) {
  bool reachable{true};

  const int rows{maze_data.GetRows()};
  const int cols{maze_data.GetColumns()};

  const std::pair<int, int> beginning{0, 0};
  for (int i{0}; i < rows && reachable; ++i) {
    for (int j{0}; j < cols && reachable; ++j) {
      std::pair<int, int> end{i, j};
      if (end != beginning) {
        auto solution{PerformAStarAlgorithm(maze_data, beginning, end)};
        std::vector<std::pair<int, int>> vec_solution{};
        while (!solution.empty()) {
          vec_solution.push_back(solution.top());
          solution.pop();
        }
        if (vec_solution.empty() || vec_solution.back() != end) {
          reachable = false;
        }
      }
    }
  }

  return reachable;
}

void MazeSolver::ClearSets() {
  for (auto &element : open_set_) {
    delete element;
  }

  for (auto &element : closed_set_) {
    delete element;
  }

  open_set_.clear();
  closed_set_.clear();
}
}  // namespace s21
