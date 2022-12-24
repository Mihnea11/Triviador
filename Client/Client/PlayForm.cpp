#include "PlayForm.h"

PlayForm::PlayForm(QWidget* parent)	: QMainWindow(parent)
{
	ui.setupUi(this);

	timer = new QTimer(this);

	ConnectUi();
}

PlayForm::PlayForm(const Player& player, QWidget* parent)
{
	ui.setupUi(this);

	m_player = player;
	timer = new QTimer(this);

	ConnectUi();
}

PlayForm::~PlayForm()
{

}

void PlayForm::ConnectUi()
{

}

void PlayForm::ToggleWidget(QWidget* disabledForm, QWidget* enabledForm)
{
	disabledForm->setVisible(false);
	enabledForm->setVisible(true);
}
