#ifndef A1_MAZE_CPP_1_VIEW_SPIN_BOX_SPIN_BOX_PUSH_BUTTON_H_
#define A1_MAZE_CPP_1_VIEW_SPIN_BOX_SPIN_BOX_PUSH_BUTTON_H_

#include <QFocusEvent>
#include <QIntValidator>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>

#define DELTA_VALUE (1)

namespace s21 {
class SpinBoxPushButton final : public QPushButton {
  Q_OBJECT

 public:
  SpinBoxPushButton(double &init_value, double multiplier, double &min_value,
                    double &max_value, QWidget *parent = nullptr);

  double GetValue();

  void SetValue(double new_value);
  void UpdateButtonText();

 protected:
  void mousePressEvent(QMouseEvent *event) override;

  void mouseReleaseEvent(QMouseEvent *event) override;

  void mouseMoveEvent(QMouseEvent *event) override;

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
  void enterEvent(QEnterEvent *event) override;
#else
  void enterEvent(QEvent *event) override;
#endif  // QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)

  void leaveEvent(QEvent *event) override;

 signals:
  void EventValueChanged(double);

 private:
  void SetupUi();
  [[nodiscard]] double GetSingleStep() const;

  bool is_mouse_pressed_ = false;
  QPoint last_mouse_pos_;
  double &current_value_;
  double &min_value_;
  double &max_value_;
  double multiplier_;
  double step_size_{};
};
}  // namespace s21
#endif  // A1_MAZE_CPP_1_VIEW_SPIN_BOX_SPIN_BOX_PUSH_BUTTON_H_
