#ifndef A1_MAZE_CPP_1_VIEW_SPIN_BOX_SPIN_BOX_LINE_EDIT_H_
#define A1_MAZE_CPP_1_VIEW_SPIN_BOX_SPIN_BOX_LINE_EDIT_H_

#include <QLineEdit>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QValidator>
#include <QWidget>
#include <iostream>

#include "View/EventHandler/EventHandler.h"

namespace s21 {
class SpinBoxLineEdit final : public QLineEdit {
  Q_OBJECT

 public:
  SpinBoxLineEdit(double &init_value, double multiplier, double &min_value,
                  double &max_value, QWidget *parent = nullptr);

  void HandleClickInWidget(const QPoint &click_pos);

  [[nodiscard]] double GetValue() const { return current_value_; }

  void SetValue(double new_value);

 public slots:
  void UpdateCurrentValue(const QString &text);

 signals:
  void EventValueChanged(double);
  void FocusOut();

 protected:
  void mousePressEvent(QMouseEvent *event) override;

  void focusOutEvent(QFocusEvent *event) override;

  void keyPressEvent(QKeyEvent *event) override;

  [[nodiscard]] bool IsClickInsideTextRect(const QPoint &click_pos) const;
 signals:
  void EventEditingFinished(double value);

 private:
  bool is_fractional_{false};
  double &current_value_;
  double &min_value_;
  double &max_value_;
  bool is_editable_;
  double multiplier_;
};
}  // namespace s21
#endif  // A1_MAZE_CPP_1_VIEW_SPIN_BOX_SPIN_BOX_LINE_EDIT_H_
