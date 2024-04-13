#include <gtest/gtest.h>

#include "../src/Controller/Controller.h"
#include "../src/Model/Model.h"

namespace s21 {
class MazeGeneratorTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  Model model{};
  Controller controller{&model};
};

TEST_F(MazeGeneratorTest, MazeGenerator1x1Test) {
  const MazeData maze_data = controller.GenerateMaze(1, 1, false);
  const bool are_all_cells_reachable =
      controller.AreAllCellsReachable(maze_data);
  ASSERT_EQ(are_all_cells_reachable, true);
}
TEST_F(MazeGeneratorTest, MazeGenerator2x2Test) {
  const MazeData maze_data = controller.GenerateMaze(2, 2, false);
  const bool are_all_cells_reachable =
      controller.AreAllCellsReachable(maze_data);
  ASSERT_EQ(are_all_cells_reachable, true);
}
TEST_F(MazeGeneratorTest, MazeGenerator3x3Test) {
  const MazeData maze_data = controller.GenerateMaze(3, 3, false);
  const bool are_all_cells_reachable =
      controller.AreAllCellsReachable(maze_data);
  ASSERT_EQ(are_all_cells_reachable, true);
}
TEST_F(MazeGeneratorTest, MazeGenerator4x4Test) {
  const MazeData maze_data = controller.GenerateMaze(4, 4, false);
  const bool are_all_cells_reachable =
      controller.AreAllCellsReachable(maze_data);
  ASSERT_EQ(are_all_cells_reachable, true);
}
TEST_F(MazeGeneratorTest, MazeGenerator5x5Test) {
  const MazeData maze_data = controller.GenerateMaze(5, 5, false);
  const bool are_all_cells_reachable =
      controller.AreAllCellsReachable(maze_data);
  ASSERT_EQ(are_all_cells_reachable, true);
}
TEST_F(MazeGeneratorTest, MazeGenerator6x6Test) {
  const MazeData maze_data = controller.GenerateMaze(6, 6, false);
  const bool are_all_cells_reachable =
      controller.AreAllCellsReachable(maze_data);
  ASSERT_EQ(are_all_cells_reachable, true);
}
TEST_F(MazeGeneratorTest, MazeGenerator7x7Test) {
  const MazeData maze_data = controller.GenerateMaze(7, 7, false);
  const bool are_all_cells_reachable =
      controller.AreAllCellsReachable(maze_data);
  ASSERT_EQ(are_all_cells_reachable, true);
}
TEST_F(MazeGeneratorTest, MazeGenerator8x8Test) {
  const MazeData maze_data = controller.GenerateMaze(8, 8, false);
  const bool are_all_cells_reachable =
      controller.AreAllCellsReachable(maze_data);
  ASSERT_EQ(are_all_cells_reachable, true);
}
TEST_F(MazeGeneratorTest, MazeGenerator9x9Test) {
  const MazeData maze_data = controller.GenerateMaze(9, 9, false);
  const bool are_all_cells_reachable =
      controller.AreAllCellsReachable(maze_data);
  ASSERT_EQ(are_all_cells_reachable, true);
}
TEST_F(MazeGeneratorTest, MazeGenerator10x10Test) {
  const MazeData maze_data = controller.GenerateMaze(10, 10, false);
  const bool are_all_cells_reachable =
      controller.AreAllCellsReachable(maze_data);
  ASSERT_EQ(are_all_cells_reachable, true);
}
TEST_F(MazeGeneratorTest, MazeGeneratorXxXTest) {
  for (int x = 0; x < 25; ++x) {
    const MazeData maze_data = controller.GenerateMaze(x, x, false);
    const bool are_all_cells_reachable =
        controller.AreAllCellsReachable(maze_data);
    ASSERT_EQ(are_all_cells_reachable, true);
  }
}
TEST_F(MazeGeneratorTest, MazeGeneratorXxXXTest) {
  for (int x = 0; x < 15; ++x) {
    for (int xx = 0; xx < 15; ++xx) {
      const MazeData maze_data = controller.GenerateMaze(x, xx, false);
      const bool are_all_cells_reachable =
          controller.AreAllCellsReachable(maze_data);
      ASSERT_EQ(are_all_cells_reachable, true);
    }
  }
}
}  // namespace s21
