#include <QApplication>

#include "Controller/Controller.h"
#include "Model/Model.h"
#include "View/View.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QIcon icon(":/human_open_parentheses_scary_close_parentheses.png");
  QApplication::setWindowIcon(icon);

  s21::Model model{};
  s21::Controller controller{&model};
  s21::View view{nullptr, &controller};
  view.show();
  return QApplication::exec();
}