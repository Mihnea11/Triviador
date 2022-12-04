#include "MenuForm.h"

void MenuForm::ToggleWidget(QWidget* disabledForm, QWidget* enabledForm)
{
	disabledForm->setVisible(false);
	enabledForm->setVisible(true);
}

MenuForm::MenuForm(QWidget* parent): QMainWindow(parent)
{
	ui.setupUi(this);
	ui.EditProfileWidget->setVisible(false);
	connect(ui.ProfileButton, SIGNAL(clicked()), this, SLOT(ProfileButtonClicked()));
}

MenuForm::~MenuForm()
{

}
