#include "GameWindow.h"


GameWindow::GameWindow(QWidget* parent) : QDialog(parent)
{
	ui.setupUi(this);

	ui.ShowWonGamesLabel->setText(QStringLiteral().arg(player.GetWonGames()));
	ui.ShowPlayedGamesLabel->setText(QStringLiteral().arg(player.GetPlayedGames()));
	ui.ShowWinrateLabel->setText(QStringLiteral().arg(player.GetWinRate()));

	ui.UsernameProfileFrom->setText(QString::fromStdString(player.GetUserName()));
	ui.EmailLabelProfileForm->setText(QString::fromStdString(player.GetUserEmail()));

	ui.GameForm->setVisible(true);
	ui.ProfileForm->setVisible(false);
	ui.EditProfileForm->setVisible(false);

	connect(ui.EditButton, SIGNAL(clicked()), this, SLOT(EditButtonClicked()));
	connect(ui.SaveButton, SIGNAL(clicked()), this, SLOT(SaveButtonClicked()));
	connect(ui.EditButtonProfileForm, SIGNAL(clicked()), this, SLOT(EditProfileButtonClicked()));
	connect(ui.SaveProfileButton, SIGNAL(clicked()), this, SLOT(SaveProfileButtonClicked()));
}

GameWindow::~GameWindow()
{
}
void GameWindow::ToggleForm(QWidget* disabledForm, QWidget* enabledForm)
{
	disabledForm->setVisible(false);
	enabledForm->setVisible(true);
}
