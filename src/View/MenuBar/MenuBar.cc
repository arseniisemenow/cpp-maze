#include "MenuBar.h"

#include "View/EventHandler/EventHandler.h"
#include "View/FileHandler/FileHandler.h"
#include "View/modal_widgets/FileDialog/FileDialog.h"
#include "View/styles/styles.h"

namespace s21 {
void MenuBar::SetupMenuBar() {
  QMenu *file_menu = addMenu(tr("File"));

  auto *load_action = new QAction(tr("Load File"), this);
  connect(load_action, &QAction::triggered, &EventHandler::Get(),
          &EventHandler::ActionLoadFileTriggered);
  file_menu->addAction(load_action);

  auto *save_action = new QAction(tr("Save File"), this);
  connect(save_action, &QAction::triggered, &EventHandler::Get(),
          &EventHandler::ActionSaveFileTriggered);
  file_menu->addAction(save_action);

  connect(&EventHandler::Get(), &EventHandler::EventActionLoadFileTriggered,
          &EventHandler::Get(), &EventHandler::OpenFileDialogToLoadFile);

  connect(&EventHandler::Get(), &EventHandler::EventOpenFileDialogToLoadFile,
          this, &MenuBar::OpenFileDialogToLoadFile);
  connect(this, &MenuBar::EventLoadAnotherFile, &EventHandler::Get(),
          &EventHandler::LoadAnotherFile);

  connect(&EventHandler::Get(), &EventHandler::EventActionSaveFileTriggered,
          &EventHandler::Get(), &EventHandler::OpenFileDialogToSaveFile);

  connect(&EventHandler::Get(), &EventHandler::EventOpenFileDialogToSaveFile,
          this, &MenuBar::OpenFileDialogToSaveFile);
  connect(this, &MenuBar::EventSaveFile, &EventHandler::Get(),
          &EventHandler::SaveFile);
  UpdateStyles();
}

void MenuBar::OpenFileDialogToLoadFile() {
  auto *file_dialog = new FileDialog(1000, 600);
  file_dialog->SetNameFilters({".txt"});

  file_dialog->SetRootPath(QDir::homePath());

  if (file_dialog->exec() == QDialog::Accepted) {
    const auto path = file_dialog->GetSelectedPath();
    LoadAnotherFile(path.toStdString());
  }
}
void MenuBar::OpenFileDialogToSaveFile() {
  auto *file_dialog = new FileDialog(1000, 600);
  file_dialog->SetNameFilters({".txt"});

  file_dialog->SetRootPath(QDir::homePath());

  if (file_dialog->exec() == QDialog::Accepted) {
    const auto path = file_dialog->GetSelectedPath();
    SaveFile(path.toStdString());
  }
}

void MenuBar::UpdateStyles() {
  this->setStyleSheet(GetStylesFromFile(PATH_MENU_BAR_STYLES_FILE));
}
}  // namespace s21
