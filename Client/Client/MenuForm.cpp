#include "MenuForm.h"

MenuForm::MenuForm(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	ui.EditProfileWidget->setVisible(false);
	ui.ChangeInformationsWidget->setVisible(false);

	LoadMenuProfileImage();

	connect(ui.MenuEditProfileButton, SIGNAL(clicked()), this, SLOT(ProfileButtonClicked()));
	connect(ui.BackButton, SIGNAL(clicked()), this, SLOT(BackButtonClicked()));
	connect(ui.ChangePictureButton, SIGNAL(clicked()), this, SLOT(ChangePictureButtonClicked()));
	connect(ui.SaveButton, SIGNAL(clicked()), this, SLOT(SaveInformationsButtonClicked()));
	connect(ui.EditProfileButton, SIGNAL(clicked()), this, SLOT(EditProfileButtonClicked()));
}

MenuForm::MenuForm(const Player& player, QWidget* parent)
{
	ui.setupUi(this);

	this->player = player;

	ui.EditProfileWidget->setVisible(false);
	ui.ChangeInformationsWidget->setVisible(false);
	
	ui.MenuProfilePicture->setPixmap(QPixmap(QString::fromStdString(player.GetImagePath())));

	connect(ui.MenuEditProfileButton, SIGNAL(clicked()), this, SLOT(ProfileButtonClicked()));
	connect(ui.BackButton, SIGNAL(clicked()), this, SLOT(BackButtonClicked()));
	connect(ui.ChangePictureButton, SIGNAL(clicked()), this, SLOT(ChangePictureButtonClicked()));
	connect(ui.SaveButton, SIGNAL(clicked()), this, SLOT(SaveInformationsButtonClicked()));
	connect(ui.EditProfileButton, SIGNAL(clicked()), this, SLOT(EditProfileButtonClicked()));
	connect(ui.QuitButton, SIGNAL(clicked()), this, SLOT(QuitButtonClicked()));
}

MenuForm::~MenuForm()
{

}

void MenuForm::UploadImageToLabel(QLabel* label)
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.png *.jpg *.jpeg *.bmp)"));

	if (QString::compare(fileName, QString()) != 0)
	{
		QImage image;
		bool valid = image.load(fileName);
		if (valid)
		{
			label->setPixmap(QPixmap::fromImage(image));
		}
	}

	player.SetImagePath(fileName.toStdString());
}

void MenuForm::LoadMenuProfileImage()
{
	ui.MenuProfilePicture->setPixmap(QPixmap(QString::fromStdString(player.GetImagePath())));
}

void MenuForm::ToggleWidget(QWidget* disabledForm, QWidget* enabledForm)
{
	disabledForm->setVisible(false);
	enabledForm->setVisible(true);
}

void MenuForm::ProfileButton()
{
	ToggleWidget(ui.GameMenu, ui.EditProfileWidget);

	ui.UsernameField->setText(QString::fromStdString(player.GetName()));
	ui.EmailField->setText(QString::fromStdString(player.GetEmail()));

	if (player.GetImagePath() != " ")
	{
		ui.ProfilePicture->setPixmap(QPixmap(QString::fromStdString(player.GetImagePath())));
	}

	cpr::Response response = cpr::Put(
		cpr::Url{ "http://localhost:18080/Users" },
		cpr::Payload
		{
			{"Id", player.GetName()},
			{"Email", player.GetEmail()},
			{"Password", player.GetPassword()},
			{"Image path", player.GetImagePath()}
		}
	);
}

void MenuForm::BackButton()
{
	ToggleWidget(ui.EditProfileWidget, ui.GameMenu);

	LoadMenuProfileImage();
}

void MenuForm::ChangeProfilePictureButton()
{
	UploadImageToLabel(ui.ProfilePicture);
}

void MenuForm::SaveInformationsButton()
{

}

void MenuForm::EditProfileButton()
{
	ToggleWidget(ui.EditProfileWidget, ui.ChangeInformationsWidget);
}

void MenuForm::QuitButton()
{
	close();
}
