#include <gtest/gtest.h>

#include <stack>

#include "../src/Controller/Controller.h"
#include "../src/Model/Model.h"

const std::string kTestFileNameList[] = {"tests/maze_data/maze_data_3x3.txt",
                                         "tests/maze_data/maze_data_4x4.txt",
                                         "tests/maze_data/maze_data_10x10.txt"};

namespace s21 {
class MazeSolverTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  Model model{};
  Controller controller{&model};
};

TEST_F(MazeSolverTest, MazeSolver3x3Test1) {
  LoadResult result{controller.LoadFile(kTestFileNameList[0])};

  std::pair<int, int> beginning{0, 0};
  std::pair<int, int> end{1, 2};

  std::stack<std::pair<int, int>> expected_solution{
      {{1, 2}, {2, 2}, {2, 1}, {2, 0}, {1, 0}, {0, 0}}};

  std::stack<std::pair<int, int>> my_solution{
      controller.CalculateSolution(result.maze_data, beginning, end)};

  ASSERT_EQ(expected_solution.size(), my_solution.size());

  while (!expected_solution.empty()) {
    ASSERT_EQ(expected_solution.top(), my_solution.top());

    expected_solution.pop();
    my_solution.pop();
  }
}

TEST_F(MazeSolverTest, MazeSolver3x3Test2) {
  LoadResult result{controller.LoadFile(kTestFileNameList[0])};

  std::pair<int, int> beginning{2, 0};
  std::pair<int, int> end{0, 2};

  std::stack<std::pair<int, int>> expected_solution{
      {{0, 2}, {0, 1}, {1, 1}, {1, 0}, {2, 0}}};

  std::stack<std::pair<int, int>> my_solution{
      controller.CalculateSolution(result.maze_data, beginning, end)};

  ASSERT_EQ(expected_solution.size(), my_solution.size());

  while (!expected_solution.empty()) {
    ASSERT_EQ(expected_solution.top(), my_solution.top());

    expected_solution.pop();
    my_solution.pop();
  }
}

TEST_F(MazeSolverTest, MazeSolverSamePointTest) {
  LoadResult result{controller.LoadFile(kTestFileNameList[0])};

  std::pair<int, int> beginning{0, 0};
  std::pair<int, int> end{0, 0};

  std::stack<std::pair<int, int>> expected_solution{{{0, 0}}};

  std::stack<std::pair<int, int>> my_solution{
      controller.CalculateSolution(result.maze_data, beginning, end)};

  ASSERT_EQ(expected_solution.size(), my_solution.size());

  while (!expected_solution.empty()) {
    ASSERT_EQ(expected_solution.top(), my_solution.top());

    expected_solution.pop();
    my_solution.pop();
  }
}

TEST_F(MazeSolverTest, MazeSolver4x4Test1) {
  LoadResult result{controller.LoadFile(kTestFileNameList[1])};

  std::pair<int, int> beginning{0, 0};
  std::pair<int, int> end{3, 3};

  std::stack<std::pair<int, int>> expected_solution{
      {{3, 3}, {3, 2}, {3, 1}, {3, 0}, {2, 0}, {1, 0}, {0, 0}}};

  std::stack<std::pair<int, int>> my_solution{
      controller.CalculateSolution(result.maze_data, beginning, end)};

  ASSERT_EQ(expected_solution.size(), my_solution.size());

  while (!expected_solution.empty()) {
    ASSERT_EQ(expected_solution.top(), my_solution.top());

    expected_solution.pop();
    my_solution.pop();
  }
}

TEST_F(MazeSolverTest, MazeSolver10x10Test) {
  LoadResult result{controller.LoadFile(kTestFileNameList[2])};

  std::pair<int, int> beginning{3, 8};
  std::pair<int, int> end{1, 3};

  std::stack<std::pair<int, int>> expected_solution{
      {{1, 3}, {2, 3}, {2, 2}, {2, 1}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0},
       {7, 0}, {8, 0}, {9, 0}, {9, 1}, {9, 2}, {9, 3}, {8, 3}, {7, 3}, {7, 4},
       {7, 5}, {7, 6}, {6, 6}, {5, 6}, {4, 6}, {4, 7}, {4, 8}, {3, 8}}};

  std::stack<std::pair<int, int>> my_solution{
      controller.CalculateSolution(result.maze_data, beginning, end)};

  ASSERT_EQ(expected_solution.size(), my_solution.size());

  while (!expected_solution.empty()) {
    ASSERT_EQ(expected_solution.top(), my_solution.top());

    expected_solution.pop();
    my_solution.pop();
  }
}
}  // namespace s21
