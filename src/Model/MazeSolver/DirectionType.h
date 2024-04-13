#ifndef A1_MAZE_CPP_1_MODEL_MAZE_SOLVER_DIRECTION_TYPE_H_
#define A1_MAZE_CPP_1_MODEL_MAZE_SOLVER_DIRECTION_TYPE_H_

#include <cstddef>
#include <unordered_map>

namespace s21 {
enum class DirectionType { kUp, kDown, kLeft, kRight };

struct PairHash {
  template <typename T, typename U>
  std::size_t operator()(const std::pair<T, U> &x) const {
    return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
  }
};

namespace constants {
inline const std::unordered_map<std::pair<int, int>, DirectionType, PairHash>
    kDirectionMap{{{0, -1}, DirectionType::kUp},
                  {{0, 1}, DirectionType::kDown},
                  {{1, 0}, DirectionType::kRight},
                  {{-1, 0}, DirectionType::kLeft}};
}
}  // namespace s21

#endif  // A1_MAZE_CPP_1_MODEL_MAZE_SOLVER_DIRECTION_TYPE_H_
