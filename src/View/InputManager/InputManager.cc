#include "InputManager.h"

namespace s21 {
InputManager::InputManager(QWidget *parent) : QWidget(parent) {
  auto *rows_label = new QLabel("Rows count:", this);
  auto *cols_label = new QLabel("Columns count:", this);

  rows_label->setStyleSheet("color: rgb(250,250,250)");
  cols_label->setStyleSheet("color: rgb(250,250,250)");

  row_spin_box_ = new SpinBox(10, 1, this);
  column_spin_box_ = new SpinBox(10, 1, this);

  row_spin_box_->SetMinValue(5);
  row_spin_box_->SetMaxValue(50);
  column_spin_box_->SetMinValue(5);
  column_spin_box_->SetMaxValue(50);

  auto *layout = new QGridLayout(this);
  layout->addWidget(rows_label, 0, 0);
  layout->addWidget(row_spin_box_, 0, 1);
  layout->addWidget(cols_label, 2, 0);
  layout->addWidget(column_spin_box_, 2, 1);
  AddButtonPin(layout);
  AddButtonRandomFigure(layout);

  connect(row_spin_box_, &SpinBox::EventValueChanged, this,
          &InputManager::HandleSpinBoxValueChanged);
  connect(column_spin_box_, &SpinBox::EventValueChanged, this,
          &InputManager::HandleSpinBoxValueChanged);

  connect(this, &InputManager::EventMazeSizeChanged, &EventHandler::Get(),
          &EventHandler::MazeSizeChanged);

  layout->addItem(
      new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding), 4,
      0, 1, 2);

  setLayout(layout);
  UpdateStyles();
}

[[nodiscard]] int InputManager::GetRowCount() const {
  return row_spin_box_->GetValue();
}

[[nodiscard]] int InputManager::GetColumnCount() const {
  return column_spin_box_->GetValue();
}

void InputManager::HandleSpinBoxValueChanged(const int some_value) {
  if (check_box_pin_->isChecked()) {
    row_spin_box_->SetValue(static_cast<double>(some_value));
    column_spin_box_->SetValue(static_cast<double>(some_value));
  }
  int rows_count = row_spin_box_->GetValue();
  int columns_count = column_spin_box_->GetValue();
  const std::pair maze_size{rows_count, columns_count};
  const bool random_figure_flag = check_box_random_figure_->isChecked();
  emit EventMazeSizeChanged(maze_size, random_figure_flag);
}
[[nodiscard]] bool InputManager::GetIsRandomFigureCheckBoxChecked() const {
  return check_box_random_figure_->isChecked();
}

void InputManager::AddButtonPin(QGridLayout *layout) {
  auto *pin_values_label = new QLabel("Pin values:", this);
  pin_values_label->setStyleSheet("color: rgb(250,250,250)");

  check_box_pin_ = new QCheckBox(this);
  check_box_pin_->setCheckable(true);
  check_box_pin_->setChecked(true);
  check_box_pin_->setFixedSize(24, 24);
  check_box_pin_->setToolTip(
      "Check this to pin your <b>Rows</b> and <b>Columns</b>");
  check_box_pin_->setObjectName("check_box_pin_");

  layout->addWidget(pin_values_label, 1, 0);
  layout->addWidget(check_box_pin_, 1, 1);
}
void InputManager::AddButtonRandomFigure(QGridLayout *layout) {
  auto *gameplay_mode_label = new QLabel("Gameplay mode:", this);
  gameplay_mode_label->setStyleSheet("color: rgb(250,250,250)");

  check_box_random_figure_ = new QCheckBox(this);
  check_box_random_figure_->setCheckable(true);
  check_box_random_figure_->setChecked(false);
  check_box_random_figure_->setFixedSize(24, 24);
  check_box_random_figure_->setToolTip(
      "Check this if you are <b>BRAVE</b> enough!");
  check_box_random_figure_->setObjectName("check_box_random_figure_");
  layout->addWidget(gameplay_mode_label, 3, 0);
  layout->addWidget(check_box_random_figure_, 3, 1);
}

void InputManager::UpdateStyles() {
  this->setStyleSheet(GetStylesFromFile(PATH_INPUT_MANAGER_STYLES_FILE));
}

}  // namespace s21
