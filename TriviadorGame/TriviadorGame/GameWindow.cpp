#include "GameWindow.h"


GameWindow::GameWindow(QWidget* parent) : QDialog(parent)
{
	ui.setupUi(this);

	ui.ShowWonGamesLabel->setText(QStringLiteral().arg(player.GetWonGames()));
	ui.ShowPlayedGamesLabel->setText(QStringLiteral().arg(player.GetPlayedGames()));
	ui.ShowWinrateLabel->setText(QStringLiteral().arg(player.GetWinRate()));

	ui.UsernameProfileFrom->setText(QString::fromStdString(player.GetUserName()));
	ui.EmailLabelProfileForm->setText(QString::fromStdString(player.GetUserEmail()));

}

GameWindow::~GameWindow()
{
}
