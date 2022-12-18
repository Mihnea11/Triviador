#include "MenuForm.h"

MenuForm::MenuForm(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	ui.EditProfileWidget->setVisible(false);
	ui.ChangeInformationsWidget->setVisible(false);
	ui.PlayGameOptions->setVisible(false);
	ui.PlayGameEnterRoomCode->setVisible(false);
	ui.PlayGameEnterCodeButton->setVisible(false);
	ui.RoomWidget->setVisible(false);

	LoadPlayerInfo();
	UploadImageToLabel(ui.MenuProfilePicture);
	UploadImageToLabel(ui.EditProfileProfilePicture);

	connect(ui.MenuEditProfileButton, SIGNAL(clicked()), this, SLOT(MenuEditProfileButtonClicked()));
	connect(ui.MenuQuitButton, SIGNAL(clicked()), this, SLOT(MenuQuitButtonClicked()));
	connect(ui.EditProfileBackButton, SIGNAL(clicked()), this, SLOT(EditProfileBackButtonClicked()));
	connect(ui.EditProfileChangePictureButton, SIGNAL(clicked()), this, SLOT(EditProfileChangePictureButtonClicked()));
	connect(ui.ChangeInformationsSaveButton, SIGNAL(clicked()), this, SLOT(ChangeInformationsSaveButtonClicked()));
	connect(ui.EditProfileButton, SIGNAL(clicked()), this, SLOT(EditProfileButtonClicked()));
	connect(ui.MenuPlayButton, SIGNAL(clicked()), this, SLOT(MenuPlayButtonClicked()));
	connect(ui.PlayGameBackButton, SIGNAL(clicked()), this, SLOT(PlayGameBackButtonClicked()));
	connect(ui.PlayGameJoinRoomButton, SIGNAL(clicked()), this, SLOT(PlayGameJoinRoomButtonClicked()));
	connect(ui.PlayGameCreateRoomButton, SIGNAL(clicked()), this, SLOT(PlayGameCreateRoomButtonClicked()));
	connect(ui.PlayGameEnterCodeButton, SIGNAL(clicked()), this, SLOT(PlayGameEnterCodeButtonClicked()));
	connect(ui.RoomOptionsBackButton, SIGNAL(clicked()), this, SLOT(RoomOptionsBackButtonClicked()));
}

MenuForm::MenuForm(const Player& player, QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	ui.EditProfileWidget->setVisible(false);
	ui.ChangeInformationsWidget->setVisible(false);
	ui.PlayGameOptions->setVisible(false);
	ui.PlayGameEnterRoomCode->setVisible(false);
	ui.PlayGameEnterCodeButton->setVisible(false);
	ui.RoomWidget->setVisible(false);

	this->m_player = player;

	LoadPlayerInfo();
	UploadImageToLabel(ui.MenuProfilePicture);
	UploadImageToLabel(ui.EditProfileProfilePicture);

	connect(ui.MenuEditProfileButton, SIGNAL(clicked()), this, SLOT(MenuEditProfileButtonClicked()));
	connect(ui.MenuQuitButton, SIGNAL(clicked()), this, SLOT(MenuQuitButtonClicked()));
	connect(ui.EditProfileBackButton, SIGNAL(clicked()), this, SLOT(EditProfileBackButtonClicked()));
	connect(ui.EditProfileChangePictureButton, SIGNAL(clicked()), this, SLOT(EditProfileChangePictureButtonClicked()));
	connect(ui.ChangeInformationsSaveButton, SIGNAL(clicked()), this, SLOT(ChangeInformationsSaveButtonClicked()));
	connect(ui.EditProfileButton, SIGNAL(clicked()), this, SLOT(EditProfileButtonClicked()));
	connect(ui.MenuPlayButton, SIGNAL(clicked()), this, SLOT(MenuPlayButtonClicked()));
	connect(ui.PlayGameBackButton, SIGNAL(clicked()), this, SLOT(PlayGameBackButtonClicked()));
	connect(ui.PlayGameJoinRoomButton, SIGNAL(clicked()), this, SLOT(PlayGameJoinRoomButtonClicked()));
	connect(ui.PlayGameCreateRoomButton, SIGNAL(clicked()), this, SLOT(PlayGameCreateRoomButtonClicked()));
	connect(ui.PlayGameEnterCodeButton, SIGNAL(clicked()), this, SLOT(PlayGameEnterCodeButtonClicked()));
	connect(ui.RoomOptionsBackButton, SIGNAL(clicked()), this, SLOT(RoomOptionsBackButtonClicked()));
}

MenuForm::~MenuForm()
{

}

void MenuForm::SetPlayer(const Player& player)
{
	this->m_player = player;
}

Player MenuForm::GetPlayer()
{
	return m_player;
}

void MenuForm::LoadPlayerInfo()
{
	ui.UsernameField->setText(QString::fromStdString(m_player.GetName()));
	ui.EmailField->setText(QString::fromStdString(m_player.GetEmail()));

	/*ui.WonGamesLabel->setText(QString::fromStdString(player.GetWonGames()));
	ui.PlayedGamesLabel->setText(QString::fromStdString(player.GetPlayedGames()));
	ui.WinRateLabel->setText(QString::fromStdString(player.GetWinRate()));*/
}

void MenuForm::UploadImageToLabel(QLabel* label)
{
	QImage image;

	bool valid = image.load(QString::fromStdString(m_player.GetImagePath()));
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
}

void MenuForm::EditProfileBackButton()
{
	ToggleWidget(ui.EditProfileWidget, ui.GameMenu);
}

void MenuForm::EditProfileChangeProfilePictureButton()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.png *.jpg *.jpeg *.bmp)"));
	if (QString::compare(fileName, QString()) != 0)
	{
		m_player.SetImagePath(fileName.toStdString());
		UploadImageToLabel(ui.EditProfileProfilePicture);
		UploadImageToLabel(ui.MenuProfilePicture);
	}

	cpr::Response response = cpr::Post(
		cpr::Url{ Server::GetUrl() + "/User_" + m_player.GetName()},
		cpr::Payload
		{
			{"Image path", m_player.GetImagePath()}
		}
	);
}

void MenuForm::ChangeInformationsSaveButton()
{
	if (ui.ChangeInformationsEmail->text().isEmpty() == true && ui.ChangeInformationsNewPassword->text().isEmpty() == true)
	{
		ToggleWidget(ui.ChangeInformationsWidget, ui.EditProfileWidget);
		return;
	}
	
	try
	{
		ValidateNewInformation();

		cpr::Response response = cpr::Post(
			cpr::Url{ Server::GetUrl() + "/User_" + m_player.GetName() },
			cpr::Payload
			{
				{"Email", m_player.GetEmail()},
				{"Password", m_player.GetPassword()}
			}
		);

		LoadPlayerInfo();
		ToggleWidget(ui.ChangeInformationsWidget, ui.EditProfileWidget);
	}
	catch (std::exception exception)
	{
		ui.ChangeInformationsErrorLabel->setText(exception.what());
	}
}

void MenuForm::EditProfileButton()
{
	ToggleWidget(ui.EditProfileWidget, ui.ChangeInformationsWidget);
}

void MenuForm::MenuQuitButton()
{
	close();
}

void MenuForm::MenuPLayButton()
{
	ToggleWidget(ui.GameMenu, ui.PlayGameOptions);
}

void MenuForm::PlayGameBackButton()
{
	ToggleWidget(ui.PlayGameOptions, ui.GameMenu);

	ui.PlayGameEnterRoomCode->setVisible(false);
	ui.PlayGameEnterCodeButton->setVisible(false);
}

void MenuForm::PlayGameJoinRoomButton()
{
	ui.PlayGameEnterRoomCode->setVisible(true);
	ui.PlayGameEnterCodeButton->setVisible(true);
}

void MenuForm::PlayGameEnterCodeButton()
{
	//TO DO: request from server to join room
}

void MenuForm::PlayGameCreateRoomButton()
{	
	cpr::Response createRoomRequest=cpr::Get(cpr::Url{ Server::GetUrl() + "/CreateRoom" });
	ToggleWidget(ui.PlayGameOptions, ui.RoomWidget);

	ui.PlayGameEnterRoomCode->setVisible(false);
	ui.PlayGameEnterCodeButton->setVisible(false);
	auto responseText = crow::json::load(createRoomRequest.text);
	std::string roomCode = responseText["Room code"].s();
	ui.RoomCode->setText(QString::fromStdString(roomCode));
	//DisplayJoinedPlayers();
}

void MenuForm::RoomOptionsBackButton()
{
	ToggleWidget(ui.RoomWidget, ui.PlayGameOptions);
}

void MenuForm::ValidateNewInformation()
{
	std::string email = ui.ChangeInformationsEmail->text().toStdString();
	std::string newPassword = ui.ChangeInformationsNewPassword->text().toStdString();

	if (email != "")
	{
		const std::regex emailPattern("^([a-zA-Z0-9_\\ \\.+)@([a-zA-Z0-9_\\-\\.]+)\\.([a-zA-Z]{2,5})$");
		if (!std::regex_match(email, emailPattern))
		{
			throw std::exception("Invalid email");
		}

		m_player.SetEmail(email);
	}

	if (newPassword != "")
	{
		if (ui.ChangeInformationsOldPassowrd->text().toStdString() != m_player.GetPassword())
		{
			throw std::exception("Old password is invalid");
		}

		if (newPassword != ui.ChangeInformationsConfirmPassword->text().toStdString())
		{
			throw std::exception("Passwords do not match");
		}

		const std::regex passwordPattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$");
		if (!std::regex_match(newPassword, passwordPattern))
		{
			throw std::exception("Invalid password!\nThe password must containt at least: 8 characters, a number and a special character");
		}

		m_player.SetPassword(newPassword);
	}
}
