#include "MenuForm.h"

void MenuForm::ToggleWidget(QWidget * disabledForm, QWidget * enabledForm)
{
	disabledForm->setVisible(false);
	enabledForm->setVisible(true);
}

void MenuForm::ChangeProfilePictureButton()
{

	QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.png *.jpg *.jpeg *.bmp)"));
	if (QString::compare(filename, QString()) != 0)
	{
		QImage image;
		bool valid = image.load(filename);
		if (valid)
		{
			image = image.scaledToWidth(ui.Picture->width(), Qt::SmoothTransformation);
			ui.Picture->setPixmap(QPixmap::fromImage(image));
		}
	}

}

void MenuForm::SaveInformationsButton()
{

}

void MenuForm::EditProfileButton()
{
	ToggleWidget(ui.EditProfileWidget, ui.ChangeInformationsWidget);
}

MenuForm::MenuForm(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	ui.EditProfileWidget->setVisible(false);
	ui.ChangeInformationsWidget->setVisible(false);
	connect(ui.ProfileButton, SIGNAL(clicked()), this, SLOT(ProfileButtonClicked()));
	connect(ui.BackButton, SIGNAL(clicked()), this, SLOT(BackButtonClicked()));
	connect(ui.ChangePictureButton, SIGNAL(clicked()), this, SLOT(ChangePictureButtonClicked()));
	connect(ui.SaveButton, SIGNAL(clicked()), this, SLOT(SaveInformationsButtonClicked()));
	connect(ui.EditProfileButton, SIGNAL(clicked()), this, SLOT(EditProfileButtonClicked()));
}

MenuForm::~MenuForm()
{

}