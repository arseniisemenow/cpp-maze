#ifndef A1_MAZE_CPP_1_MODEL_MAZE_SAVER_MAZE_SAVER_H_
#define A1_MAZE_CPP_1_MODEL_MAZE_SAVER_MAZE_SAVER_H_
#include <string>

#include "common/MazeData.h"

namespace s21 {
class MazeSaver {
 public:
  int SaveFile(const std::string &file_name, const MazeData &maze_data);
};
}  // namespace s21

#endif  // A1_MAZE_CPP_1_MODEL_MAZE_SAVER_MAZE_SAVER_H_
