#include "GridWidget.h"

#include <iostream>

#include "View/EventHandler/EventHandler.h"

GridWidget::GridWidget(QWidget *parent) : QWidget(parent) {
  setFixedSize(s21::constants::kBoardSize, s21::constants::kBoardSize);

  connect(&s21::EventHandler::Get(),
          &s21::EventHandler::EventFileHandlerFileLoaded, this,
          &GridWidget::UpdateGridWidget);

  connect(this, &GridWidget::EventPathSourceOrDestinationChanged,
          &s21::EventHandler::Get(),
          &s21::EventHandler::PathSourceOrDestinationChanged);

  connect(&s21::EventHandler::Get(), &s21::EventHandler::EventMazeSizeChanged,
          this, &GridWidget::ResetPathSourceAndDestination);

  connect(&s21::EventHandler::Get(), &s21::EventHandler::EventMazeSizeChanged,
          this, [this]() { repaint(); });

  /* Would be much better to avoid this timer... */
  timer_ = new QTimer(this);
  connect(timer_, &QTimer::timeout, this, [this]() { repaint(); });
  timer_->start(50);
  /*  */
}

void GridWidget::UpdateGridWidget(const s21::MazeData &maze_data) {
  *p_maze_data_ = maze_data;
}

void GridWidget::paintEvent(QPaintEvent *event) {
  if (!p_begin_ || !p_end_ || !p_maze_data_ || !p_solution_) {
    return;
  }
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  const int rows = p_maze_data_->matrix_horizontal_walls.size();

  if (rows == 0) {
    return;
  }
  const int columns = p_maze_data_->matrix_vertical_walls[0].size();

  if (columns == 0) {
    return;
  }

  const int cell_width = width() / columns;
  const int cell_height = height() / rows;

  QBrush brush_white = {{195, 195, 195}};
  QBrush brush_red = {{165, 55, 55}};
  painter.setPen(QPen(brush_white, 4));

  painter.drawRect(0, 0, cell_width * columns, cell_height * rows);

  painter.setPen(QPen(brush_white, 2));
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < columns; ++col) {
      if (p_maze_data_->matrix_vertical_walls[row][col]) {
        painter.drawLine((col + 1) * cell_width, row * cell_height,
                         (col + 1) * cell_width, (row + 1) * cell_height);
      }
    }
  }

  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < columns; ++col) {
      if (p_maze_data_->matrix_horizontal_walls[row][col]) {
        painter.drawLine(col * cell_width, (row + 1) * cell_height,
                         (col + 1) * cell_width, (row + 1) * cell_height);
      }
    }
  }

  painter.setPen(QPen(brush_red, 2));
  std::stack<std::pair<int, int>> solution_copy = *p_solution_;
  QPoint prev_point;
  while (!solution_copy.empty()) {
    auto [current_point_x, current_point_y] = solution_copy.top();
    solution_copy.pop();

    QPoint current_point((current_point_y + 0.5) * cell_width,
                         (current_point_x + 0.5) * cell_height);

    if (!prev_point.isNull()) {
      painter.drawLine(prev_point, current_point);
    }
    prev_point = current_point;
  }
}

void GridWidget::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    HandleLeftClick(event);
  } else if (event->button() == Qt::RightButton) {
    HandleRightClick(event);
  }

  QWidget::mousePressEvent(event);
  repaint();
}

std::pair<int, int> GridWidget::GetClickPosition(QMouseEvent *event) {
  if (!p_begin_ || !p_end_ || !p_maze_data_ || !p_solution_) {
    return {};
  }
  if (p_maze_data_->matrix_vertical_walls.size() == 0 ||
      p_maze_data_->matrix_horizontal_walls.size() == 0)
    return {};
  const int pos_x = event->pos().x();
  const int pos_y = event->pos().y();

  const int cell_width =
      width() / p_maze_data_->matrix_vertical_walls[0].size();
  const int cell_height =
      height() / p_maze_data_->matrix_horizontal_walls.size();

  int column_index = pos_x / cell_width;
  int row_index = pos_y / cell_height;

  if (row_index >= p_maze_data_->matrix_vertical_walls.size()) {
    row_index = p_maze_data_->matrix_vertical_walls.size() - 1;
  }
  if (column_index >= p_maze_data_->matrix_vertical_walls[0].size()) {
    column_index = p_maze_data_->matrix_vertical_walls[0].size() - 1;
  }

  std::pair<int, int> pair{row_index, column_index};

  return pair;
}

void GridWidget::HandleLeftClick(QMouseEvent *event) {
  const auto pair = GetClickPosition(event);

  PathSourceChanged(pair);
}

void GridWidget::HandleRightClick(QMouseEvent *event) {
  const auto pair = GetClickPosition(event);

  PathDestinationChanged(pair);
}

/* If the size of the maze is changed, resetting begin and end positions */
void GridWidget::ResetPathSourceAndDestination() {
  if (!p_begin_ || !p_end_ || !p_maze_data_ || !p_solution_) {
    return;
  }
  p_begin_->first = 0;
  p_begin_->second = 0;
  p_end_->first = 0;
  p_end_->second = 0;

  PathSourceChanged(*p_begin_);
  PathDestinationChanged(*p_end_);
}
