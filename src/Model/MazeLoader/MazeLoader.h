#ifndef A1_MAZE_CPP_1_MODEL_MAZE_LOADER_MAZE_LOADER_H_
#define A1_MAZE_CPP_1_MODEL_MAZE_LOADER_MAZE_LOADER_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "common/LoadResult.h"
#include "common/MazeData.h"

namespace s21 {
class MazeLoader {
 public:
  [[nodiscard]] LoadResult LoadFile(const std::string &filename);
};
}  // namespace s21

#endif  // A1_MAZE_CPP_1_MODEL_MAZE_LOADER_MAZE_LOADER_H_
