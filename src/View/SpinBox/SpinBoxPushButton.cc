#include "SpinBoxPushButton.h"

namespace s21 {
SpinBoxPushButton::SpinBoxPushButton(double &init_value, double multiplier,
                                     double &min_value, double &max_value,
                                     QWidget *parent)
    : current_value_(init_value),
      min_value_(min_value),
      max_value_(max_value),
      multiplier_(multiplier) {
  setMinimumWidth(100);
  setMaximumWidth(200);
  SetupUi();
}

double SpinBoxPushButton::GetValue() { return current_value_; }

void SpinBoxPushButton::SetValue(double new_value) {
  if (new_value > max_value_ || new_value < min_value_) {
    return;
  }
  current_value_ = new_value;

  step_size_ = (multiplier_ == multiplier_) ? multiplier_ : DELTA_VALUE;

  UpdateButtonText();
  emit EventValueChanged(current_value_);
}

void SpinBoxPushButton::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    is_mouse_pressed_ = true;
    last_mouse_pos_ = event->pos();
  }

  QPushButton::mousePressEvent(event);
}

void SpinBoxPushButton::mouseReleaseEvent(QMouseEvent *event) {
  is_mouse_pressed_ = false;
  QPushButton::mouseReleaseEvent(event);
}

void SpinBoxPushButton::mouseMoveEvent(QMouseEvent *event) {
  if (is_mouse_pressed_) {
    const double delta_x = event->pos().x() - last_mouse_pos_.x();
    const double delta_value = delta_x / (GetSingleStep());
    const double new_value = current_value_ + delta_value;
    SetValue(new_value);
    last_mouse_pos_ = event->pos();
  }

  QPushButton::mouseMoveEvent(event);
}
#ifdef Q_OS_MACOS
void SpinBoxPushButton::enterEvent(QEnterEvent *event) {
  setCursor(Qt::SizeHorCursor);
  QPushButton::enterEvent(event);
}
#elif defined(Q_OS_LINUX)
void SpinBoxPushButton::enterEvent(QEvent *event) {
  setCursor(Qt::SizeHorCursor);
  QPushButton::enterEvent(event);
}
#endif  // Q_OS_MACOS
void SpinBoxPushButton::leaveEvent(QEvent *event) {
  unsetCursor();
  QPushButton::leaveEvent(event);
}

void SpinBoxPushButton::SetupUi() {
  setFocusPolicy(Qt::NoFocus);

  int current_value = current_value_;
  setText(QString::number(current_value));
}

double SpinBoxPushButton::GetSingleStep() const {
  return DELTA_VALUE / step_size_;
}

void SpinBoxPushButton::UpdateButtonText() {
  int current_value = current_value_;
  setText(QString::number(current_value));
}
}  // namespace s21
