#include "MenuForm.h"

MenuForm::MenuForm(QWidget* parent) : QMainWindow(parent)
{
	m_ui.setupUi(this);

	m_ui.EditProfileWidget->setVisible(false);
	m_ui.ChangeInformationsWidget->setVisible(false);
	m_ui.PlayGameOptions->setVisible(false);
	m_ui.PlayGameEnterRoomCode->setVisible(false);
	m_ui.PlayGameEnterCodeButton->setVisible(false);
	m_ui.RoomWidget->setVisible(false);
	m_ui.WaitingWidget->setVisible(false);
	m_ui.JoiningWidget->setVisible(false);
	m_ui.RoomStartGameButton->setVisible(false);
	m_ui.LeftRoomWidget->setVisible(false);

	m_timer = std::make_shared<QTimer>(this);

	LoadPlayerInfo();
	UploadImageToLabel(m_ui.MenuProfilePicture, m_user);
	UploadImageToLabel(m_ui.EditProfileProfilePicture, m_user);
	ConnectUi();
}

MenuForm::MenuForm(const User& user, QWidget* parent) : QMainWindow(parent)
{
	m_ui.setupUi(this);

	m_ui.EditProfileWidget->setVisible(false);
	m_ui.ChangeInformationsWidget->setVisible(false);
	m_ui.PlayGameOptions->setVisible(false);
	m_ui.PlayGameEnterRoomCode->setVisible(false);
	m_ui.PlayGameEnterCodeButton->setVisible(false);
	m_ui.RoomWidget->setVisible(false);
	m_ui.WaitingWidget->setVisible(false);
	m_ui.JoiningWidget->setVisible(false);
	m_ui.RoomStartGameButton->setVisible(false);
	m_ui.LeftRoomWidget->setVisible(false);

	this->m_user = user;
	m_timer = std::make_shared<QTimer>(this);

	LoadPlayerInfo();
	UploadImageToLabel(m_ui.MenuProfilePicture, m_user);
	UploadImageToLabel(m_ui.EditProfileProfilePicture, m_user);
	ConnectUi();
}

MenuForm::~MenuForm()
{

}

void MenuForm::SetUser(const User& user)
{
	this->m_user = user;
}

User MenuForm::GetUser()
{
	return m_user;
}

void MenuForm::ConnectUi()
{
	connect(m_ui.MenuEditProfileButton, SIGNAL(clicked()), this, SLOT(MenuEditProfileButtonClicked()));
	connect(m_ui.MenuQuitButton, SIGNAL(clicked()), this, SLOT(MenuQuitButtonClicked()));
	connect(m_ui.EditProfileBackButton, SIGNAL(clicked()), this, SLOT(EditProfileBackButtonClicked()));
	connect(m_ui.EditProfileChangePictureButton, SIGNAL(clicked()), this, SLOT(EditProfileChangePictureButtonClicked()));
	connect(m_ui.ChangeInformationsSaveButton, SIGNAL(clicked()), this, SLOT(ChangeInformationsSaveButtonClicked()));
	connect(m_ui.EditProfileButton, SIGNAL(clicked()), this, SLOT(EditProfileButtonClicked()));
	connect(m_ui.MenuPlayButton, SIGNAL(clicked()), this, SLOT(MenuPlayButtonClicked()));
	connect(m_ui.PlayGameBackButton, SIGNAL(clicked()), this, SLOT(PlayGameBackButtonClicked()));
	connect(m_ui.PlayGameJoinRoomButton, SIGNAL(clicked()), this, SLOT(PlayGameJoinRoomButtonClicked()));
	connect(m_ui.PlayGameCreateRoomButton, SIGNAL(clicked()), this, SLOT(PlayGameCreateRoomButtonClicked()));
	connect(m_ui.PlayGameEnterCodeButton, SIGNAL(clicked()), this, SLOT(PlayGameEnterCodeButtonClicked()));
	connect(m_ui.RoomOptionsBackButton, SIGNAL(clicked()), this, SLOT(RoomOptionsBackButtonClicked()));
	connect(m_ui.RoomCreateRoomButton, SIGNAL(clicked()), this, SLOT(RoomCreateRoomButtonClicked()));
	connect(m_ui.RoomStartGameButton, SIGNAL(clicked()), this, SLOT(StartGameButtonClicked()));
	connect(m_ui.LeftRoomOKButton, SIGNAL(clicked()), this, SLOT(LeftRoomOkButtonClicked()));

	connect(m_timer.get(), SIGNAL(timeout()), this, SLOT(UpdateRoomInformation()));
}

void MenuForm::LoadPlayerInfo()
{
	m_ui.UsernameField->setText(QString::fromStdString(m_user.GetName()));
	m_ui.EmailField->setText(QString::fromStdString(m_user.GetEmail()));

	/*ui.WonGamesLabel->setText(QString::fromStdString(player.GetWonGames()));
	ui.PlayedGamesLabel->setText(QString::fromStdString(player.GetPlayedGames()));
	ui.WinRateLabel->setText(QString::fromStdString(player.GetWinRate()));*/
}

void MenuForm::UploadImageToLabel(QLabel* label, const User& user)
{
	QImage image;

	bool valid = image.load(QString::fromStdString(user.GetImagePath()));
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

void MenuForm::DisplayUser(const std::string& playerCount, const User& currentUser)
{
	if (playerCount == "Player1")
	{
		m_ui.RoomPlayer1->setVisible(true);
		m_ui.RoomPlayer1Username->setText(QString::fromStdString(currentUser.GetName()));
		UploadImageToLabel(m_ui.RoomPlayer1ProfilePicture, currentUser);
	}
	if (playerCount == "Player2")
	{
		m_ui.RoomPlayer2->setVisible(true);
		m_ui.RoomPlayer2Username->setText(QString::fromStdString(currentUser.GetName()));
		UploadImageToLabel(m_ui.RoomPlayer2ProfilePicture, currentUser);
	}
	if (playerCount == "Player3")
	{
		m_ui.RoomPlayer3->setVisible(true);
		m_ui.RoomPlayer3Username->setText(QString::fromStdString(currentUser.GetName()));
		UploadImageToLabel(m_ui.RoomPlayer3ProfilePicture, currentUser);
	}
	if (playerCount == "Player4")
	{
		m_ui.RoomPlayer4->setVisible(true);
		m_ui.RoomPlayer4Username->setText(QString::fromStdString(currentUser.GetName()));
		UploadImageToLabel(m_ui.RoomPlayer4ProfilePicture, currentUser);
	}
}

void MenuForm::DisplayRoom(const std::string& roomCode)
{
	m_ui.RoomPlayerSelection->setVisible(false);
	m_ui.RoomCreateRoomButton->setVisible(false);
	m_ui.RoomSelectedPlayers->setVisible(true);
	m_ui.RoomCode->setText(QString::fromStdString(roomCode));
	m_ui.RoomPlayer1->setVisible(false);
	m_ui.RoomPlayer2->setVisible(false);
	m_ui.RoomPlayer3->setVisible(false);
	m_ui.RoomPlayer4->setVisible(false);

	cpr::Response response = cpr::Get(cpr::Url{ Server::GetUrl() + "/Room_" + roomCode });

	auto arguments = crow::json::load(response.text);

	std::string ownerName;
	std::string playerCount;
	for (int i = 0; i < arguments.size(); i++)
	{
		if (arguments[i].has("Owner") == true)
		{
			ownerName = arguments[i]["Owner"].s();
		}

		if (arguments[i].has("Player count") == true)
		{
			playerCount = std::to_string(arguments[i]["Player count"].i());
		}
	}

	m_ui.RoomOwnerUsername->setText(QString::fromStdString(ownerName));
	m_ui.RoomSelectedPlayers->setText(QString::fromStdString(playerCount));

	UpdateRoom();
}

void MenuForm::UpdateRoom()
{
	std::string roomCode = m_ui.RoomCode->text().toStdString();
	if (roomCode == "")
	{
		roomCode = m_ui.PlayGameEnterRoomCode->text().toStdString();
	}
	cpr::Response response = cpr::Get(cpr::Url{ Server::GetUrl() + "/Room_" + roomCode });

	if (response.text == "\"\"")
	{
		m_ui.RoomWidget->setVisible(false);
		m_ui.GameMenu->setVisible(true);
		m_ui.LeftRoomWidget->setVisible(true);
		m_timer->stop();

		return;
	}

	auto roomInformation = crow::json::load(response.text);
	int playerIndex = 1;

	m_ui.RoomPlayer1->setVisible(false);
	m_ui.RoomPlayer2->setVisible(false);
	m_ui.RoomPlayer3->setVisible(false);
	m_ui.RoomPlayer4->setVisible(false);
	for (int i = 0; i < roomInformation.size(); i++)
	{
		if (roomInformation[i].has("User name") == false || roomInformation[i].has("Image path") == false)
		{
			continue;
		}

		User currentUser;

		std::string username = roomInformation[i]["User name"].s();
		std::string imagePath = roomInformation[i]["Image path"].s();

		username = curl_unescape(username.c_str(), username.length());
		imagePath = curl_unescape(imagePath.c_str(), imagePath.length());

		currentUser.SetName(username);
		currentUser.SetImagePath(imagePath);

		DisplayUser("Player" + std::to_string(playerIndex), currentUser);
		playerIndex++;
	}

	if (m_user.GetName() == m_ui.RoomOwnerUsername->text().toStdString())
	{
		int index = 0;
		int maxPlayers = std::stoi(m_ui.RoomSelectedPlayers->text().toStdString());

		if (m_ui.RoomPlayer1->isVisible() == true)
		{
			index++;
		}
		if (m_ui.RoomPlayer2->isVisible() == true)
		{
			index++;
		}
		if (m_ui.RoomPlayer3->isVisible() == true)
		{
			index++;
		}
		if (m_ui.RoomPlayer4->isVisible() == true)
		{
			index++;
		}

		if (index == maxPlayers)
		{
			m_ui.RoomStartGameButton->setVisible(true);
		}
		else
		{
			m_ui.RoomStartGameButton->setVisible(false);
		}
	}

	int startGame = std::stoi(roomInformation[0]["Game start"].s());

	if (startGame == 1)
	{
		m_timer->stop();

		if (m_user.GetName() == m_ui.RoomOwnerUsername->text().toStdString())
		{
			GameForm* window = new GameForm(m_user, roomCode, true);
			window->show();
		}
		else
		{
			GameForm* window = new GameForm(m_user, roomCode);
			window->show();
		}

		close();
	}
}

void MenuForm::MenuEditProfileButton()
{
	ToggleWidget(m_ui.GameMenu, m_ui.EditProfileWidget);
}

void MenuForm::EditProfileBackButton()
{
	ToggleWidget(m_ui.EditProfileWidget, m_ui.GameMenu);
}

void MenuForm::EditProfileChangeProfilePictureButton()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.png *.jpg *.jpeg *.bmp)"));
	if (QString::compare(fileName, QString()) != 0)
	{
		m_user.SetImagePath(fileName.toStdString());
		UploadImageToLabel(m_ui.EditProfileProfilePicture, m_user);
		UploadImageToLabel(m_ui.MenuProfilePicture, m_user);
	}

	cpr::Response response = cpr::Post(
		cpr::Url{ Server::GetUrl() + "/User_" + m_user.GetName() },
		cpr::Payload
		{
			{"Image path", m_user.GetImagePath()}
		}
	);
}

void MenuForm::ChangeInformationsSaveButton()
{
	if (m_ui.ChangeInformationsEmail->text().isEmpty() == true && m_ui.ChangeInformationsNewPassword->text().isEmpty() == true)
	{
		ToggleWidget(m_ui.ChangeInformationsWidget, m_ui.EditProfileWidget);
		return;
	}

	try
	{
		ValidateNewInformation();

		cpr::Response response = cpr::Post(
			cpr::Url{ Server::GetUrl() + "/User_" + m_user.GetName() },
			cpr::Payload
			{
				{"Email", m_user.GetEmail()},
				{"Password", m_user.GetPassword()}
			}
		);

		LoadPlayerInfo();
		ToggleWidget(m_ui.ChangeInformationsWidget, m_ui.EditProfileWidget);
	}
	catch (std::exception exception)
	{
		m_ui.ChangeInformationsErrorLabel->setText(exception.what());
	}
}

void MenuForm::EditProfileButton()
{
	ToggleWidget(m_ui.EditProfileWidget, m_ui.ChangeInformationsWidget);
}

void MenuForm::MenuQuitButton()
{
	close();
}

void MenuForm::MenuPLayButton()
{
	ToggleWidget(m_ui.GameMenu, m_ui.PlayGameOptions);
}

void MenuForm::PlayGameBackButton()
{
	ToggleWidget(m_ui.PlayGameOptions, m_ui.GameMenu);

	m_ui.PlayGameEnterRoomCode->setVisible(false);
	m_ui.PlayGameEnterCodeButton->setVisible(false);
}

void MenuForm::PlayGameJoinRoomButton()
{
	m_ui.PlayGameEnterRoomCode->setVisible(true);
	m_ui.PlayGameEnterCodeButton->setVisible(true);
}

void MenuForm::PlayGameEnterCodeButton()
{
	std::string roomCode = m_ui.PlayGameEnterRoomCode->text().toStdString();

	cpr::Response response = cpr::Put(
		cpr::Url{ Server::GetUrl() + "/Room_" + roomCode },
		cpr::Payload
		{
			{"User name", m_user.GetName()},
			{"Image path", m_user.GetImagePath()}
		}
	);
	if (response.status_code != 200)
	{
		m_ui.PlayGameEnterRoomCode->setText("");
		m_ui.PlayGameEnterRoomCode->setPlaceholderText(QString::fromStdString(response.text));

		return;
	}

	m_ui.JoiningWidget->setVisible(true);
	WaitForSeconds(1);

	ToggleWidget(m_ui.PlayGameOptions, m_ui.RoomWidget);
	DisplayRoom(roomCode);
	m_ui.JoiningWidget->setVisible(false);

	m_timer->start(1000);
}

void MenuForm::PlayGameCreateRoomButton()
{
	m_ui.RoomSelectedPlayers->setVisible(false);
	m_ui.RoomCreateRoomButton->setVisible(true);
	m_ui.RoomPlayerSelection->setVisible(true);

	ToggleWidget(m_ui.PlayGameOptions, m_ui.RoomWidget);
}

void MenuForm::RoomOptionsBackButton()
{
	m_timer->stop();
	ToggleWidget(m_ui.RoomWidget, m_ui.PlayGameOptions);

	m_ui.RoomPlayerSelection->setDisabled(false);
	m_ui.RoomCreateRoomButton->setDisabled(false);
	m_ui.RoomCreateRoomButton->setVisible(true);
	m_ui.RoomSelectedPlayers->setVisible(false);

	m_ui.RoomPlayer1->setVisible(true);
	m_ui.RoomPlayer2->setVisible(true);
	m_ui.RoomPlayer3->setVisible(true);
	m_ui.RoomPlayer4->setVisible(true);

	m_ui.RoomPlayer1Username->setText("");
	m_ui.RoomPlayer2Username->setText("");
	m_ui.RoomPlayer3Username->setText("");
	m_ui.RoomPlayer4Username->setText("");

	m_ui.RoomPlayer1ProfilePicture->setPixmap(QPixmap());
	m_ui.RoomPlayer2ProfilePicture->setPixmap(QPixmap());
	m_ui.RoomPlayer3ProfilePicture->setPixmap(QPixmap());
	m_ui.RoomPlayer4ProfilePicture->setPixmap(QPixmap());

	m_ui.RoomStartGameButton->setVisible(false);

	std::string roomCode = m_ui.RoomCode->text().toStdString();
	cpr::Response response = cpr::Put(
		cpr::Url{ Server::GetUrl() + "/LeaveRoom_" + roomCode },
		cpr::Payload
		{
			{"User name", m_user.GetName()}
		}
	);

	m_ui.RoomOwnerUsername->setText("");
	m_ui.RoomCode->setText("");
}

void MenuForm::RoomCreateRoomButton()
{
	std::string playerCount = m_ui.RoomPlayerSelection->currentText().toStdString();
	cpr::Response request = cpr::Put(
		cpr::Url{ Server::GetUrl() + "/CreateRoom" },
		cpr::Payload
		{
			{"User name", m_user.GetName()},
			{"Image path", m_user.GetImagePath()},
			{"Player count", playerCount}
		}
	);

	std::string roomCode = crow::json::load(request.text)["Room code"].s();
	cpr::Response addOwner = cpr::Put(
		cpr::Url{ Server::GetUrl() + "/Room_" + roomCode },
		cpr::Payload
		{
			{"User name", m_user.GetName()},
			{"Image path", m_user.GetImagePath()}
		}
	);

	m_ui.WaitingWidget->setVisible(true);
	WaitForSeconds(1);

	DisplayRoom(roomCode);
	m_ui.WaitingWidget->setVisible(false);

	m_timer->start(1000);
}

void MenuForm::StartGameButton()
{
	std::string roomCode = m_ui.RoomCode->text().toStdString();

	cpr::Response response = cpr::Post(
		cpr::Url{ Server::GetUrl() + "/Room_" + roomCode },
		cpr::Payload
		{
			{"Game start", "1"}
		}
	);

	cpr::Response createGame = cpr::Get(cpr::Url{ Server::GetUrl() + "/CreateGame_" + roomCode });

	UpdateRoom();
}

void MenuForm::LeftRoomOkButton()
{
	m_ui.LeftRoomWidget->setVisible(false);
}

void MenuForm::ValidateNewInformation()
{
	std::string email = m_ui.ChangeInformationsEmail->text().toStdString();
	std::string newPassword = m_ui.ChangeInformationsNewPassword->text().toStdString();

	if (email != "")
	{
		const std::regex emailPattern("^([a-zA-Z0-9_\\ \\.+)@([a-zA-Z0-9_\\-\\.]+)\\.([a-zA-Z]{2,5})$");
		if (!std::regex_match(email, emailPattern))
		{
			throw std::exception("Invalid email");
		}

		m_user.SetEmail(email);
	}

	if (newPassword != "")
	{
		if (m_ui.ChangeInformationsOldPassowrd->text().toStdString() != m_user.GetPassword())
		{
			throw std::exception("Old password is invalid");
		}

		if (newPassword != m_ui.ChangeInformationsConfirmPassword->text().toStdString())
		{
			throw std::exception("Passwords do not match");
		}

		const std::regex passwordPattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$");
		if (!std::regex_match(newPassword, passwordPattern))
		{
			throw std::exception("Invalid password!\nThe password must containt at least: 8 characters, a number and a special character");
		}

		m_user.SetPassword(newPassword);
	}
}

void MenuForm::WaitForSeconds(int seconds)
{
	QTime delayTime = QTime::currentTime().addSecs(seconds);
	while (QTime::currentTime() < delayTime)
	{
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
	}
}