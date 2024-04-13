#ifndef A1_MAZE_CPP_1_COMMON_LOAD_RESULT_H_
#define A1_MAZE_CPP_1_COMMON_LOAD_RESULT_H_

#include "common/MazeData.h"

namespace s21 {
struct LoadResult {
  MazeData maze_data{};
  int error{};
};
}  // namespace s21
#endif  // A1_MAZE_CPP_1_COMMON_LOAD_RESULT_H_
