#include "PlayForm.h"
void PlayForm::ToggleWidget(QWidget* disabledForm, QWidget* enabledForm)
{
	disabledForm->setVisible(false);
	enabledForm->setVisible(true);
}

void PlayForm::CreateButton()
{
	ui.RoomForm->setVisible(true);
}

PlayForm::PlayForm(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	ui.centralwidget->setVisible(true);
	ui.RoomForm->setVisible(false);

	ui.RoomPlayers->addItems({ "Two Players", "Three Players", "Four Players" });

	connect(ui.CreateRoomPlayForm, SIGNAL(clicked()), this, SLOT(CreateButtonClicked()));
}

PlayForm::PlayForm(const Player& player, QWidget* parent)
{
	ui.setupUi(this);

	ui.centralwidget->setVisible(true);
	ui.RoomForm->setVisible(false);

	ui.RoomPlayers->addItems({ "Two Players", "Three Players", "Four Players" });

	this->player = player;

	connect(ui.CreateRoomPlayForm, SIGNAL(clicked()), this, SLOT(CreateButtonClicked()));
}

PlayForm::~PlayForm()
{
}
