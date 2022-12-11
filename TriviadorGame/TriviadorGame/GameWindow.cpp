#include "GameWindow.h"

GameWindow::GameWindow(QWidget* parent) : QDialog(parent)
{
	ui.setupUi(this);
    ui.GameWindowForm->setVisible(true);
    ui.ProfileForm->setVisible(false);
    

    connect(ui.EditButton, SIGNAL(clicked()), this, SLOT(EditButtonClicked()));
    connect(ui.SaveButtonProfileForm, SIGNAL(clicked()), this, SLOT(SaveButtonProfileFormClicked()));
}
void GameWindow::ToggleForm(QWidget* disabledForm, QWidget* enabledForm)
{
    disabledForm->setVisible(false);
    enabledForm->setVisible(true);
}
GameWindow::~GameWindow()
{
}
