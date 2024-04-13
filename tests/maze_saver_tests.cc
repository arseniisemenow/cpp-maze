#include <gtest/gtest.h>

#include "../src/Controller/Controller.h"
#include "../src/Model/Model.h"

const std::string kTestFileNameList[] = {
    "tests/maze_data/maze_data_1x1.txt", "tests/maze_data/maze_data_2x2.txt",
    "tests/maze_data/maze_data_3x3.txt", "tests/maze_data/maze_data_4x4.txt"};
const std::string kTestFileNameListSaved[] = {
    "tests/maze_data/maze_data_1x1_saved.txt",
    "tests/maze_data/maze_data_2x2_saved.txt",
    "tests/maze_data/maze_data_3x3_saved.txt",
    "tests/maze_data/maze_data_4x4_saved.txt"};

namespace s21 {
class MazeSaverTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  Model model{};
  Controller controller{&model};
};

TEST_F(MazeSaverTest, MazeData1x1Test) {
  const std::vector<std::vector<bool>> expected_vertical_matrix{{true}};
  const std::vector<std::vector<bool>> expected_horizontal_matrix{{false}};

  const LoadResult result{controller.LoadFile(kTestFileNameList[0])};

  controller.SaveFile(kTestFileNameListSaved[0], result.maze_data);
  const LoadResult result_saved{controller.LoadFile(kTestFileNameListSaved[0])};

  ASSERT_EQ(result_saved.maze_data.matrix_vertical_walls,
            expected_vertical_matrix);
  ASSERT_EQ(result_saved.maze_data.matrix_horizontal_walls,
            expected_horizontal_matrix);
}
TEST_F(MazeSaverTest, MazeData2x2Test) {
  const std::vector<std::vector<bool>> expected_vertical_matrix{{true, false},
                                                                {false, true}};
  const std::vector<std::vector<bool>> expected_horizontal_matrix{
      {false, true}, {true, false}};

  const LoadResult result{controller.LoadFile(kTestFileNameList[1])};

  controller.SaveFile(kTestFileNameListSaved[1], result.maze_data);
  const LoadResult result_saved{controller.LoadFile(kTestFileNameListSaved[1])};

  ASSERT_EQ(result_saved.maze_data.matrix_vertical_walls,
            expected_vertical_matrix);
  ASSERT_EQ(result_saved.maze_data.matrix_horizontal_walls,
            expected_horizontal_matrix);
}

TEST_F(MazeSaverTest, MazeData3x3Test) {
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

  controller.SaveFile(kTestFileNameListSaved[2], result.maze_data);
  const LoadResult result_saved{controller.LoadFile(kTestFileNameListSaved[2])};

  ASSERT_EQ(result_saved.maze_data.matrix_vertical_walls,
            expected_vertical_matrix);
  ASSERT_EQ(result_saved.maze_data.matrix_horizontal_walls,
            expected_horizontal_matrix);
}

TEST_F(MazeSaverTest, MazeData4x4Test) {
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

  controller.SaveFile(kTestFileNameListSaved[3], result.maze_data);
  const LoadResult result_saved{controller.LoadFile(kTestFileNameListSaved[3])};

  ASSERT_EQ(result_saved.maze_data.matrix_vertical_walls,
            expected_vertical_matrix);
  ASSERT_EQ(result_saved.maze_data.matrix_horizontal_walls,
            expected_horizontal_matrix);
}
}  // namespace s21
