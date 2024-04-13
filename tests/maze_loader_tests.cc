#include <gtest/gtest.h>

#include "../src/Controller/Controller.h"
#include "../src/Model/Model.h"

const std::string kTestFileNameList[] = {
    "tests/maze_data/maze_data_1x1.txt", "tests/maze_data/maze_data_2x2.txt",
    "tests/maze_data/maze_data_3x3.txt", "tests/maze_data/maze_data_4x4.txt"};

namespace s21 {
class MazeLoaderTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  Model model{};
  Controller controller{&model};
};

TEST_F(MazeLoaderTest, MazeData1x1Test) {
  const std::vector<std::vector<bool>> expected_vertical_matrix{{true}};
  const std::vector<std::vector<bool>> expected_horizontal_matrix{{false}};

  const LoadResult result{controller.LoadFile(kTestFileNameList[0])};
  ASSERT_EQ(result.maze_data.matrix_vertical_walls, expected_vertical_matrix);
  ASSERT_EQ(result.maze_data.matrix_horizontal_walls,
            expected_horizontal_matrix);
}
TEST_F(MazeLoaderTest, MazeData2x2Test) {
  const std::vector<std::vector<bool>> expected_vertical_matrix{{true, false},
                                                                {false, true}};
  const std::vector<std::vector<bool>> expected_horizontal_matrix{
      {false, true}, {true, false}};

  const LoadResult result{controller.LoadFile(kTestFileNameList[1])};
  ASSERT_EQ(result.maze_data.matrix_vertical_walls, expected_vertical_matrix);
  ASSERT_EQ(result.maze_data.matrix_horizontal_walls,
            expected_horizontal_matrix);
}

TEST_F(MazeLoaderTest, MazeData3x3Test) {
  const std::vector<std::vector<bool>> expected_vertical_matrix{
      {true, false, false},
      {false, true, false},
      {false, false, true},
  };
  const std::vector<std::vector<bool>> expected_horizontal_matrix{
      {false, false, true},
      {false, true, false},
      {true, false, false},
  };

  const LoadResult result{controller.LoadFile(kTestFileNameList[2])};
  ASSERT_EQ(result.maze_data.matrix_vertical_walls, expected_vertical_matrix);
  ASSERT_EQ(result.maze_data.matrix_horizontal_walls,
            expected_horizontal_matrix);
}

TEST_F(MazeLoaderTest, MazeData4x4Test) {
  const std::vector<std::vector<bool>> expected_vertical_matrix{
      {true, false, false, false},
      {false, true, false, false},
      {false, false, true, false},
      {false, false, false, true},
  };
  const std::vector<std::vector<bool>> expected_horizontal_matrix{
      {false, false, false, true},
      {false, false, true, false},
      {false, true, false, false},
      {true, false, false, false},
  };

  const LoadResult result{controller.LoadFile(kTestFileNameList[3])};
  ASSERT_EQ(result.maze_data.matrix_vertical_walls, expected_vertical_matrix);
  ASSERT_EQ(result.maze_data.matrix_horizontal_walls,
            expected_horizontal_matrix);
}
}  // namespace s21
