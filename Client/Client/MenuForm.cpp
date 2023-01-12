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
	ui.WaitingWidget->setVisible(false);
	ui.JoiningWidget->setVisible(false);
	ui.RoomStartGameButton->setVisible(false);
	ui.LeftRoomWidget->setVisible(false);

	m_timer = std::make_shared<QTimer>(this);

	LoadPlayerInfo();
	UploadImageToLabel(ui.MenuProfilePicture, m_player);
	UploadImageToLabel(ui.EditProfileProfilePicture, m_player);
	ConnectUi();
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
	ui.WaitingWidget->setVisible(false);
	ui.JoiningWidget->setVisible(false);
	ui.RoomStartGameButton->setVisible(false);
	ui.LeftRoomWidget->setVisible(false);

	this->m_player = player;
	m_timer = std::make_shared<QTimer>(this);

	LoadPlayerInfo();
	UploadImageToLabel(ui.MenuProfilePicture, m_player);
	UploadImageToLabel(ui.EditProfileProfilePicture, m_player);
	ConnectUi();
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

void MenuForm::ConnectUi()
{
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
	connect(ui.RoomCreateRoomButton, SIGNAL(clicked()), this, SLOT(RoomCreateRoomButtonClicked()));
	connect(ui.RoomStartGameButton, SIGNAL(clicked()), this, SLOT(StartGameButtonClicked()));
	connect(ui.LeftRoomOKButton, SIGNAL(clicked()), this, SLOT(LeftRoomOkButtonClicked()));

	connect(m_timer.get(), SIGNAL(timeout()), this, SLOT(UpdateRoomInformation()));
}

void MenuForm::LoadPlayerInfo()
{
	ui.UsernameField->setText(QString::fromStdString(m_player.GetName()));
	ui.EmailField->setText(QString::fromStdString(m_player.GetEmail()));

	/*ui.WonGamesLabel->setText(QString::fromStdString(player.GetWonGames()));
	ui.PlayedGamesLabel->setText(QString::fromStdString(player.GetPlayedGames()));
	ui.WinRateLabel->setText(QString::fromStdString(player.GetWinRate()));*/
}

void MenuForm::UploadImageToLabel(QLabel* label, const Player& player)
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

void MenuForm::DisplayPlayer(const std::string& playerCount, const Player& currentUser)
{
	if (playerCount == "Player1")
	{
		ui.RoomPlayer1->setVisible(true);
		ui.RoomPlayer1Username->setText(QString::fromStdString(currentUser.GetName()));
		UploadImageToLabel(ui.RoomPlayer1ProfilePicture, currentUser);
	}
	if (playerCount == "Player2")
	{
		ui.RoomPlayer2->setVisible(true);
		ui.RoomPlayer2Username->setText(QString::fromStdString(currentUser.GetName()));
		UploadImageToLabel(ui.RoomPlayer2ProfilePicture, currentUser);
	}
	if (playerCount == "Player3")
	{
		ui.RoomPlayer3->setVisible(true);
		ui.RoomPlayer3Username->setText(QString::fromStdString(currentUser.GetName()));
		UploadImageToLabel(ui.RoomPlayer3ProfilePicture, currentUser);
	}
	if (playerCount == "Player4")
	{
		ui.RoomPlayer4->setVisible(true);
		ui.RoomPlayer4Username->setText(QString::fromStdString(currentUser.GetName()));
		UploadImageToLabel(ui.RoomPlayer4ProfilePicture, currentUser);
	}
}

void MenuForm::DisplayRoom(const std::string& roomCode)
{
	ui.RoomPlayerSelection->setVisible(false);
	ui.RoomCreateRoomButton->setVisible(false);
	ui.RoomSelectedPlayers->setVisible(true);
	ui.RoomCode->setText(QString::fromStdString(roomCode));
	ui.RoomPlayer1->setVisible(false);
	ui.RoomPlayer2->setVisible(false);
	ui.RoomPlayer3->setVisible(false);
	ui.RoomPlayer4->setVisible(false);

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

	ui.RoomOwnerUsername->setText(QString::fromStdString(ownerName));
	ui.RoomSelectedPlayers->setText(QString::fromStdString(playerCount));

	UpdateRoom();
}

void MenuForm::UpdateRoom()
{
	std::string roomCode = ui.RoomCode->text().toStdString();
	if (roomCode == "")
	{
		roomCode = ui.PlayGameEnterRoomCode->text().toStdString();
	}
	cpr::Response response = cpr::Get(cpr::Url{ Server::GetUrl() + "/Room_" + roomCode });

	if (response.text == "\"\"")
	{
		ui.RoomWidget->setVisible(false);
		ui.GameMenu->setVisible(true);
		ui.LeftRoomWidget->setVisible(true);
		m_timer->stop();

		return;
	}

	auto roomInformation = crow::json::load(response.text);
	int playerIndex = 1;

	ui.RoomPlayer1->setVisible(false);
	ui.RoomPlayer2->setVisible(false);
	ui.RoomPlayer3->setVisible(false);
	ui.RoomPlayer4->setVisible(false);
	for (int i = 0; i < roomInformation.size(); i++)
	{
		if (roomInformation[i].has("User name") == false || roomInformation[i].has("Image path") == false)
		{
			continue;
		}

		Player currentUser;

		std::string username = roomInformation[i]["User name"].s();
		std::string imagePath = roomInformation[i]["Image path"].s();

		username = curl_unescape(username.c_str(), username.length());
		imagePath = curl_unescape(imagePath.c_str(), imagePath.length());

		currentUser.SetName(username);
		currentUser.SetImagePath(imagePath);

		DisplayPlayer("Player" + std::to_string(playerIndex), currentUser);
		playerIndex++;
	}

	if (m_player.GetName() == ui.RoomOwnerUsername->text().toStdString())
	{
		int index = 0;
		int maxPlayers = std::stoi(ui.RoomSelectedPlayers->text().toStdString());

		if (ui.RoomPlayer1->isVisible() == true)
		{
			index++;
		}
		if (ui.RoomPlayer2->isVisible() == true)
		{
			index++;
		}
		if (ui.RoomPlayer3->isVisible() == true)
		{
			index++;
		}
		if (ui.RoomPlayer4->isVisible() == true)
		{
			index++;
		}

		if (index == maxPlayers)
		{
			ui.RoomStartGameButton->setVisible(true);
		}
		else
		{
			ui.RoomStartGameButton->setVisible(false);
		}
	}

	int startGame = std::stoi(roomInformation[0]["Game start"].s());

	if (startGame == 1)
	{
		m_timer->stop();

		if (m_player.GetName() == ui.RoomOwnerUsername->text().toStdString())
		{
			GameForm* window = new GameForm(m_player, roomCode, true);
			window->show();
		}
		else
		{
			GameForm* window = new GameForm(m_player, roomCode);
			window->show();
		}

		close();
	}
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
		UploadImageToLabel(ui.EditProfileProfilePicture, m_player);
		UploadImageToLabel(ui.MenuProfilePicture, m_player);
	}

	cpr::Response response = cpr::Post(
		cpr::Url{ Server::GetUrl() + "/User_" + m_player.GetName() },
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
	std::string roomCode = ui.PlayGameEnterRoomCode->text().toStdString();

	cpr::Response response = cpr::Put(
		cpr::Url{ Server::GetUrl() + "/Room_" + roomCode },
		cpr::Payload
		{
			{"User name", m_player.GetName()},
			{"Image path", m_player.GetImagePath()}
		}
	);
	if (response.status_code != 200)
	{
		ui.PlayGameEnterRoomCode->setText("");
		ui.PlayGameEnterRoomCode->setPlaceholderText(QString::fromStdString(response.text));

		return;
	}

	ui.JoiningWidget->setVisible(true);
	WaitForSeconds(1);

	ToggleWidget(ui.PlayGameOptions, ui.RoomWidget);
	DisplayRoom(roomCode);
	ui.JoiningWidget->setVisible(false);

	m_timer->start(1000);
}

void MenuForm::PlayGameCreateRoomButton()
{
	ui.RoomSelectedPlayers->setVisible(false);
	ui.RoomCreateRoomButton->setVisible(true);
	ui.RoomPlayerSelection->setVisible(true);

	ToggleWidget(ui.PlayGameOptions, ui.RoomWidget);
}

void MenuForm::RoomOptionsBackButton()
{
	m_timer->stop();
	ToggleWidget(ui.RoomWidget, ui.PlayGameOptions);

	ui.RoomPlayerSelection->setDisabled(false);
	ui.RoomCreateRoomButton->setDisabled(false);
	ui.RoomCreateRoomButton->setVisible(true);
	ui.RoomSelectedPlayers->setVisible(false);

	ui.RoomPlayer1->setVisible(true);
	ui.RoomPlayer2->setVisible(true);
	ui.RoomPlayer3->setVisible(true);
	ui.RoomPlayer4->setVisible(true);

	ui.RoomPlayer1Username->setText("");
	ui.RoomPlayer2Username->setText("");
	ui.RoomPlayer3Username->setText("");
	ui.RoomPlayer4Username->setText("");

	ui.RoomPlayer1ProfilePicture->setPixmap(QPixmap());
	ui.RoomPlayer2ProfilePicture->setPixmap(QPixmap());
	ui.RoomPlayer3ProfilePicture->setPixmap(QPixmap());
	ui.RoomPlayer4ProfilePicture->setPixmap(QPixmap());

	ui.RoomStartGameButton->setVisible(false);

	std::string roomCode = ui.RoomCode->text().toStdString();
	cpr::Response response = cpr::Put(
		cpr::Url{ Server::GetUrl() + "/LeaveRoom_" + roomCode },
		cpr::Payload
		{
			{"User name", m_player.GetName()}
		}
	);

	ui.RoomOwnerUsername->setText("");
	ui.RoomCode->setText("");
}

void MenuForm::RoomCreateRoomButton()
{
	std::string playerCount = ui.RoomPlayerSelection->currentText().toStdString();
	cpr::Response request = cpr::Put(
		cpr::Url{ Server::GetUrl() + "/CreateRoom" },
		cpr::Payload
		{
			{"User name", m_player.GetName()},
			{"Image path", m_player.GetImagePath()},
			{"Player count", playerCount}
		}
	);

	std::string roomCode = crow::json::load(request.text)["Room code"].s();
	cpr::Response addOwner = cpr::Put(
		cpr::Url{ Server::GetUrl() + "/Room_" + roomCode },
		cpr::Payload
		{
			{"User name", m_player.GetName()},
			{"Image path", m_player.GetImagePath()}
		}
	);

	ui.WaitingWidget->setVisible(true);
	WaitForSeconds(1);

	DisplayRoom(roomCode);
	ui.WaitingWidget->setVisible(false);

	m_timer->start(1000);
}

void MenuForm::StartGameButton()
{
	std::string roomCode = ui.RoomCode->text().toStdString();

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
	ui.LeftRoomWidget->setVisible(false);
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

void MenuForm::WaitForSeconds(int seconds)
{
	QTime delayTime = QTime::currentTime().addSecs(seconds);
	while (QTime::currentTime() < delayTime)
	{
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
	}
}