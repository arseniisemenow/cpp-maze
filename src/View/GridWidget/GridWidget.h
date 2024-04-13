#ifndef A1_MAZE_CPP_1_VIEW_GRID_WIDGET_GRID_WIDGET_H_
#define A1_MAZE_CPP_1_VIEW_GRID_WIDGET_GRID_WIDGET_H_

#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>
#include <stack>

#include "View/common/constants.h"
#include "common/MazeData.h"

class GridWidget final : public QWidget {
  Q_OBJECT
 public:
  explicit GridWidget(QWidget *parent = nullptr);

  void UpdateGridWidget(const s21::MazeData &maze_data);

  void SetPointers(std::stack<std::pair<int, int>> *p_solution,
                   s21::MazeData *p_maze_data, std::pair<int, int> *p_begin,
                   std::pair<int, int> *p_end) {
    p_solution_ = p_solution;
    p_maze_data_ = p_maze_data;
    p_begin_ = p_begin;
    p_end_ = p_end;
  }

  void Repaint() { repaint(); }

 protected:
  std::pair<int, int> GetClickPosition(QMouseEvent *event);

  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;

  void HandleLeftClick(QMouseEvent *event);
  void HandleRightClick(QMouseEvent *event);

  void ResetPathSourceAndDestination();

  void PathSourceChanged(const std::pair<int, int> pair) {
    *p_begin_ = pair;
    PathSourceOrDestinationChanged({pair, *p_end_});
  }
  void PathDestinationChanged(const std::pair<int, int> pair) {
    *p_end_ = pair;
    PathSourceOrDestinationChanged({*p_begin_, pair});
  }
  void PathSourceOrDestinationChanged(
      const std::pair<const std::pair<int, int>, const std::pair<int, int>>
          pair) {
    emit EventPathSourceOrDestinationChanged(pair);
  }
 signals:
  void EventPathSourceOrDestinationChanged(
      std::pair<const std::pair<int, int>, const std::pair<int, int>> pair);

 private:
  s21::MazeData *p_maze_data_{nullptr};
  std::pair<int, int> *p_begin_{nullptr};
  std::pair<int, int> *p_end_{nullptr};
  std::stack<std::pair<int, int>> *p_solution_{nullptr};
  QTimer *timer_;
};

#endif  // A1_MAZE_CPP_1_VIEW_GRID_WIDGET_GRID_WIDGET_H_
