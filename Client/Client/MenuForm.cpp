#include "MenuForm.h"

MenuForm::MenuForm(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	ui.EditProfileWidget->setVisible(false);
	ui.ChangeInformationsWidget->setVisible(false);

	UploadImageToLabel(ui.MenuProfilePicture);

	connect(ui.MenuEditProfileButton, SIGNAL(clicked()), this, SLOT(MenuEditProfileButtonClicked()));
	connect(ui.MenuQuitButton, SIGNAL(clicked()), this, SLOT(MenuQuitButtonClicked()));
	connect(ui.EditProfileBackButton, SIGNAL(clicked()), this, SLOT(EditProfileBackButtonClicked()));
	connect(ui.EditProfileChangePictureButton, SIGNAL(clicked()), this, SLOT(EditProfileChangePictureButtonClicked()));
	connect(ui.SaveButton, SIGNAL(clicked()), this, SLOT(SaveInformationsButtonClicked()));
	connect(ui.EditProfileButton, SIGNAL(clicked()), this, SLOT(EditProfileButtonClicked()));
}

MenuForm::MenuForm(const Player& player, QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	ui.EditProfileWidget->setVisible(false);
	ui.ChangeInformationsWidget->setVisible(false);

	this->player = player;

	UploadImageToLabel(ui.MenuProfilePicture);

	connect(ui.MenuEditProfileButton, SIGNAL(clicked()), this, SLOT(MenuEditProfileButtonClicked()));
	connect(ui.MenuQuitButton, SIGNAL(clicked()), this, SLOT(MenuQuitButtonClicked()));
	connect(ui.EditProfileBackButton, SIGNAL(clicked()), this, SLOT(EditProfileBackButtonClicked()));
	connect(ui.EditProfileChangePictureButton, SIGNAL(clicked()), this, SLOT(EditProfileChangePictureButtonClicked()));
	connect(ui.SaveButton, SIGNAL(clicked()), this, SLOT(SaveInformationsButtonClicked()));
	connect(ui.EditProfileButton, SIGNAL(clicked()), this, SLOT(EditProfileButtonClicked()));
}

MenuForm::~MenuForm()
{

}

void MenuForm::SetPlayer(const Player& player)
{
	this->player = player;
}

Player MenuForm::GetPlayer()
{
	return player;
}

void MenuForm::UploadImageToLabel(QLabel* label)
{
	QImage image;

	bool valid = image.load(QString::fromStdString(player.GetImagePath()));
	if (valid == false)
	{
		QString defaultPath = QDir::currentPath() + "/DefaultUser.jpg";
		image.load(defaultPath);
	}

	label->setPixmap(QPixmap::fromImage(image));
}

void MenuForm::ToggleWidget(QWidget* disabledForm, QWidget* enabledForm)
{
	disabledForm->setVisible(false);
	enabledForm->setVisible(true);
}

void MenuForm::MenuEditProfileButton()
{
	ToggleWidget(ui.GameMenu, ui.EditProfileWidget);

	ui.UsernameField->setText(QString::fromStdString(player.GetName()));
	ui.EmailField->setText(QString::fromStdString(player.GetEmail()));

	UploadImageToLabel(ui.EditProfileProfilePicture);
}

void MenuForm::EditProfileBackButton()
{
	ToggleWidget(ui.EditProfileWidget, ui.GameMenu);

	UploadImageToLabel(ui.MenuProfilePicture);
}

void MenuForm::EditProfileChangeProfilePictureButton()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.png *.jpg *.jpeg *.bmp)"));
	if (QString::compare(fileName, QString()) != 0)
	{
		player.SetImagePath(fileName.toStdString());
		UploadImageToLabel(ui.EditProfileProfilePicture);
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

void MenuForm::SaveInformationsButton()
{

}

void MenuForm::EditProfileButton()
{
	ToggleWidget(ui.EditProfileWidget, ui.ChangeInformationsWidget);
}

void MenuForm::MenuQuitButton()
{
	close();
}
