#include "PlayForm.h"
void PlayForm::ToggleWidget(QWidget* disabledForm, QWidget* enabledForm)
{
	disabledForm->setVisible(false);
	enabledForm->setVisible(true);
}
PlayForm::PlayForm(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);
}

PlayForm::PlayForm(const Player& player, QWidget* parent)
{
	ui.setupUi(this);

	this->player = player;
}

PlayForm::~PlayForm()
{
}
