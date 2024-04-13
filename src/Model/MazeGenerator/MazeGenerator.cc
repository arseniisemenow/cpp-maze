#include "MazeGenerator.h"

// #include <__random/random_device.h>
#include <iostream>
#include <random>
#include <set>

#include "Model/MazeGenerator/CustomFigures/CustomFigures.h"
#include "common/constants.h"

namespace s21 {

void MazeGenerator::InitSetsMatrix(std::vector<std::vector<int>> &matrix,
                                   const int rows, const int columns) {
  matrix.resize(rows);
  for (int i = 0; i < rows; ++i) {
    matrix[i].resize(columns);
  }

  int num = 1;
  for (auto &i : matrix) {
    for (int &j : i) {
      j = num++;
    }
  }
}

void MergeColumns(std::vector<int> &line,
                  std::vector<bool> &line_vertical_walls) {
  int num_cells = line.size();

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 1);

  for (int i = 0; i < num_cells; ++i) {
    if (i < num_cells - 1 && line[i] != line[i + 1] && dis(gen) == 1) {
      if (line[i] == constants::kMagicNumber) {
        continue;
      }
      line_vertical_walls[i] = false;
      int set_id_to_merge = line[i + 1];
      for (int j = 0; j < num_cells; ++j) {
        if (line[j] == set_id_to_merge) {
          line[j] = line[i];
        }
      }
    }
  }
}
void MergeAllColumns(std::vector<int> &line,
                     std::vector<bool> &line_vertical_walls) {
  int num_cells = line.size();

  for (int i = 0; i < num_cells; ++i) {
    if (i < num_cells - 1 && line[i] != line[i + 1]) {
      line_vertical_walls[i] = false;
      int set_id_to_merge = line[i + 1];
      for (int j = 0; j < num_cells; ++j) {
        if (line[j] == set_id_to_merge) {
          line[j] = line[i];
        }
      }
    }
  }
}

int GetSameNumberLength(const std::vector<int> &previous_line, int index) {
  int length = 1;
  while (previous_line.size() > index + 1 &&
         previous_line[index] == previous_line[index + 1]) {
    index++;
    length++;
  }
  return length;
}

void RandomHole(const std::vector<int> &previous_line, int &i) {
  std::random_device rd;
  std::mt19937 gen(rd());

  const int length = GetSameNumberLength(previous_line, i);
  std::uniform_int_distribution<> dis(0, length - 1);
  i += dis(gen);
}
void MergeRows(const std::vector<int> &previous_line,
               std::vector<int> &current_line,
               std::vector<bool> &line_horizontal_walls) {
  std::set<int> merged_sets{};

  for (int i = 0; i < previous_line.size(); ++i) {
    if (merged_sets.find(previous_line[i]) == merged_sets.end()) {
      if (current_line[i] == constants::kMagicNumber) {
        continue;
      }

      // RandomHole(previous_line, i);

      line_horizontal_walls[i] = false;
      current_line[i] = previous_line[i];
      merged_sets.insert(previous_line[i]);
    }
  }
}

MazeData GetRandomFigure() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, kCustomFigures.size() - 1);

  return kCustomFigures[dis(gen)];
}

void DrawRandomFigure(std::vector<std::vector<int>> &sets,
                      MazeData &maze_data) {
  MazeData figure_data = GetRandomFigure();
  if (maze_data.GetRows() <= figure_data.GetRows()) {
    return;
  }
  if (maze_data.GetColumns() <= figure_data.GetColumns()) {
    return;
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis_row(
      0, maze_data.GetRows() - figure_data.GetRows() - 1);
  std::uniform_int_distribution<> dis_column(
      0, maze_data.GetColumns() - figure_data.GetRows() - 1);

  const int figure_row_index = dis_row(gen);
  const int figure_column_index = dis_column(gen);

  for (int i = 0; i < figure_data.GetRows(); ++i) {
    for (int j = 0; j < figure_data.GetColumns(); ++j) {
      sets[figure_row_index + i][figure_column_index + j] =
          constants::kMagicNumber;
      maze_data.matrix_horizontal_walls[figure_row_index + i]
                                       [figure_column_index + j] =
          figure_data.matrix_horizontal_walls[i][j];
      maze_data.matrix_vertical_walls[figure_row_index + i]
                                     [figure_column_index + j] =
          figure_data.matrix_vertical_walls[i][j];
    }
  }
}

MazeData MazeGenerator::Generate(const int rows, const int columns,
                                 const bool random_figure_flag) {
  MazeData maze_data{rows, columns};

  for (int i = 0; i < maze_data.GetRows(); ++i) {
    for (int j = 0; j < maze_data.GetColumns(); ++j) {
      maze_data.matrix_horizontal_walls[i][j] = true;
      maze_data.matrix_vertical_walls[i][j] = true;
    }
  }
  std::vector<std::vector<int>> sets;

  InitSetsMatrix(sets, rows, columns);
  if (random_figure_flag) {
    DrawRandomFigure(sets, maze_data);
  }

  for (int i = 0; i < sets.size(); ++i) {
    MergeColumns(sets[i], maze_data.matrix_vertical_walls[i]);
    if (i < sets.size() - 1) {
      MergeRows(sets[i], sets[i + 1], maze_data.matrix_horizontal_walls[i]);
    } else {
      MergeAllColumns(sets[i], maze_data.matrix_vertical_walls[i]);
    }
  }

  return maze_data;
}

}  // namespace s21