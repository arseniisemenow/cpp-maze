#ifndef A1_MAZE_CPP_1_VIEW_STYLES_STYLES_H_
#define A1_MAZE_CPP_1_VIEW_STYLES_STYLES_H_

#include <QFile>
#include <QString>
#include <QTextStream>
#include <iostream>

#include "global_styles.h"

#define PATH_FILE_DIALOG_STYLES_FILE ":/FileDialogStyles.qss"
#define PATH_MENU_BAR_STYLES_FILE ":/MenuBarStyles.qss"
#define PATH_MAIN_WINDOW_STYLES_FILE ":/MainWindowStyles.qss"
#define PATH_INPUT_MANAGER_STYLES_FILE ":/InputManagerStyles.qss"

namespace s21 {
QString GetStylesFromFile(const QString& fileName);
}

#endif  // A1_MAZE_CPP_1_VIEW_STYLES_STYLES_H_
