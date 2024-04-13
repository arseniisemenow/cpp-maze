#ifndef A1_MAZE_CPP_1_VIEW_INPUT_MANAGER_INPUT_MANAGER_H_
#define A1_MAZE_CPP_1_VIEW_INPUT_MANAGER_INPUT_MANAGER_H_

#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QWidget>

#include "View/SpinBox/SpinBox.h"
#include "View/styles/styles.h"

namespace s21 {
class InputManager final : public QWidget {
  Q_OBJECT
 public:
  explicit InputManager(QWidget *parent = nullptr);

  [[nodiscard]] int GetRowCount() const;
  [[nodiscard]] int GetColumnCount() const;
  void HandleSpinBoxValueChanged(int some_value);
  [[nodiscard]] bool GetIsRandomFigureCheckBoxChecked() const;
 signals:
  void EventMazeSizeChanged(const std::pair<int, int> &maze_size, bool);

 private:
  void AddButtonPin(QGridLayout *layout);
  void AddButtonRandomFigure(QGridLayout *layout);

  void UpdateStyles();

 private:
  SpinBox *row_spin_box_;
  SpinBox *column_spin_box_;
  QCheckBox *check_box_pin_;
  QCheckBox *check_box_random_figure_;
};

}  // namespace s21
#endif  // A1_MAZE_CPP_1_VIEW_INPUT_MANAGER_INPUT_MANAGER_H_