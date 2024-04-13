#include "SpinBoxLineEdit.h"

namespace s21 {
SpinBoxLineEdit::SpinBoxLineEdit(double &init_value, double multiplier,
                                 double &min_value, double &max_value,
                                 QWidget *parent)
    : QLineEdit(parent),
      current_value_(init_value),
      min_value_(min_value),
      max_value_(max_value),
      is_editable_(true),
      multiplier_(multiplier) {
  is_fractional_ = ((int)(multiplier * 10)) % 10 > 0;
  if (is_fractional_) {
    setValidator(new QDoubleValidator(this));
  } else {
    auto validator = new QIntValidator(this);
    /* limit kostil' */
    validator->setBottom(5);
    validator->setTop(50);
    /* limit kostil' ends */
    setValidator(validator);
  }

  setAlignment(Qt::AlignCenter);

  connect(this, &SpinBoxLineEdit::textChanged, this,
          &SpinBoxLineEdit::UpdateCurrentValue);
  connect(&EventHandler::Get(), &EventHandler::EventLeftMouseButtonReleased,
          this, &SpinBoxLineEdit::HandleClickInWidget);
  connect(&EventHandler::Get(), &EventHandler::EventLeftMouseButtonPressed,
          this, &SpinBoxLineEdit::HandleClickInWidget);

  setMouseTracking(true);
}

void SpinBoxLineEdit::HandleClickInWidget(const QPoint &click_pos) {
  if (!IsClickInsideTextRect(click_pos) && this->hasFocus()) {
    emit FocusOut();
    clearFocus();  // FIXME May need
  }
}

void SpinBoxLineEdit::SetValue(const double new_value) {
  current_value_ = new_value;
  setText(QString::number(new_value));
}

void SpinBoxLineEdit::UpdateCurrentValue(const QString &text) {
  current_value_ = text.toDouble();

  emit EventValueChanged(current_value_);
}

void SpinBoxLineEdit::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    is_editable_ = true;
    setReadOnly(false);
    setFocus();
    selectAll();
  }

  QLineEdit::mousePressEvent(event);
}

bool SpinBoxLineEdit::IsClickInsideTextRect(const QPoint &click_pos) const {
  const auto text_rect = QRect(2, 2, width() - 4, height() - 4);
  return text_rect.contains(click_pos);
}

void SpinBoxLineEdit::focusOutEvent(QFocusEvent *event) {
  emit FocusOut();
  QLineEdit::focusOutEvent(event);
}

void SpinBoxLineEdit::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter ||
      event->key() == Qt::Key_Escape) {
    emit FocusOut();
  } else {
    QLineEdit::keyPressEvent(event);
  }
}
}  // namespace s21
