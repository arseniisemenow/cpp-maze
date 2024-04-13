#ifndef A1_MAZE_CPP_1_VIEW_SPIN_BOX_SPIN_BOX_H_
#define A1_MAZE_CPP_1_VIEW_SPIN_BOX_SPIN_BOX_H_

#include <QFocusEvent>
#include <QIntValidator>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>

#include "SpinBoxLineEdit.h"
#include "SpinBoxPushButton.h"

namespace s21 {

class SpinBox : public QWidget {
  Q_OBJECT

 public:
  explicit SpinBox(double initial_value = 0, double multiplier = 1,
                   QWidget *parent = nullptr);

  [[nodiscard]] double GetValue() const;
  void UpdateValue(const double new_value);
  void SetValue(const double new_value);
  [[nodiscard]] SpinBoxLineEdit *GetLineEdit() const { return line_edit_; }
  [[nodiscard]] SpinBoxPushButton *GetPushButton() const {
    return push_button_;
  }

  void SetMinValue(double min_value) {
    min_value_ = min_value;
    if (current_value_ < min_value_) {
      current_value_ = min_value_;
      emit EventValueChanged(current_value_);
    }
  }

  void SetMaxValue(double max_value) {
    max_value_ = max_value;
    if (current_value_ > max_value_) {
      current_value_ = max_value_;
      emit EventValueChanged(current_value_);
    }
  }

 public slots:
  void ToggleEditing();

 signals:
  void EventValueChanged(double new_value);

 private:
  SpinBoxLineEdit *line_edit_;
  SpinBoxPushButton *push_button_;
  QWidget *current_widget_{};
  double current_value_;
  double multiplier_;

  double min_value_{std::numeric_limits<double>::lowest()};
  double max_value_{std::numeric_limits<double>::max()};
};
}  // namespace s21

#endif  // A1_MAZE_CPP_1_VIEW_SPIN_BOX_SPIN_BOX_H_
