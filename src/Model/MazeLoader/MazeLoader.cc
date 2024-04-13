#include "MazeLoader.h"

namespace s21 {

[[nodiscard]] LoadResult MazeLoader::LoadFile(const std::string &filename) {
  LoadResult result;

  std::ifstream file(filename);
  if (!file.is_open()) {
    result.error = 1;
    return result;
  }

  std::stringstream file_content;
  file_content << file.rdbuf();
  file.close();
  std::string content = file_content.str();

  std::stringstream content_stream(content);

  int rows;
  int columns;
  content_stream >> rows >> columns;

  if (content_stream.fail()) {
    result.error = 2;
    return result;
  }

  MazeData maze(rows, columns);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      int wall;
      content_stream >> wall;
      if (content_stream.fail()) {
        result.error = 2;
        return result;
      }
      maze.matrix_vertical_walls[i][j] = wall;
    }
  }

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      int wall;
      content_stream >> wall;
      if (content_stream.fail()) {
        result.error = 2;
        return result;
      }
      maze.matrix_horizontal_walls[i][j] = wall;
    }
  }

  result.maze_data = maze;
  return result;
}
}  // namespace s21
