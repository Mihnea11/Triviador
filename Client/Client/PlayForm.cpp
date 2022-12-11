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

void PlayForm::RoomBackButton()
{
	ui.RoomForm->setVisible(false);
}

void PlayForm::BackButton()
{
	MenuForm* menu = new MenuForm(std::move(player));
	menu->show();

	close();
}

PlayForm::PlayForm(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	ui.centralwidget->setVisible(true);
	ui.RoomForm->setVisible(false);

	ui.RoomPlayerSelection->addItems({ "Two Players", "Three Players", "Four Players" });

	connect(ui.CreateRoomPlayForm, SIGNAL(clicked()), this, SLOT(CreateButtonClicked()));
	connect(ui.RoomBackButton, SIGNAL(clicked()), this, SLOT(RoomBackButtonClicked()));
	connect(ui.BackButton, SIGNAL(clicked()), this, SLOT(BackButtonClicked()));
}

PlayForm::PlayForm(const Player& player, QWidget* parent)
{
	ui.setupUi(this);

	ui.centralwidget->setVisible(true);
	ui.RoomForm->setVisible(false);

	ui.RoomPlayerSelection->addItems({ "Two Players", "Three Players", "Four Players" });

	this->player = player;

	connect(ui.CreateRoomPlayForm, SIGNAL(clicked()), this, SLOT(CreateButtonClicked()));
	connect(ui.RoomBackButton, SIGNAL(clicked()), this, SLOT(RoomBackButtonClicked()));
	connect(ui.BackButton, SIGNAL(clicked()), this, SLOT(BackButtonClicked()));
}

PlayForm::~PlayForm()
{
}
