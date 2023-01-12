#include "GameForm.h"

GameForm::GameForm(QWidget* parent)
{
	m_ui.setupUi(this);
	int playerCount = GetPlayerCount();
}

GameForm::GameForm(const User& player, const std::string& gameCode, bool isOwner, QWidget* parent)
{
	m_ui.setupUi(this);

	m_player = player;
	m_isOwner = isOwner;
	m_gameCode = gameCode;
	int playerCount = GetPlayerCount();

	JoinPlayer();
	LoadPlayerIcons(playerCount);
	DisplayPlayerMap(playerCount);
	GetMapRegions(playerCount);
	EmptyLabels();
	if (m_isOwner == true)
	{
		SendRegionCount();
	}

	m_timer = std::make_shared<QTimer>(this);

	connect(m_timer.get(), SIGNAL(timeout()), this, SLOT(WaitingForPlayersToJoin()));

	m_ui.QuestionDisplay->setVisible(false);
	m_timer->start(100);
}

GameForm::~GameForm()
{
}

void GameForm::SetIsOwner(bool isOwner)
{
	m_isOwner = true;
}

bool GameForm::GetIsOwner() const
{
	return m_isOwner;
}

int GameForm::GetPlayerCount()
{
	cpr::Response response = cpr::Get(cpr::Url{ Server::GetUrl() + "/Game_" + m_gameCode });

	auto arguments = crow::json::load(response.text);
	int playerCount = arguments["Player count"].i();

	return playerCount;
}

void GameForm::JoinPlayer()
{
	cpr::Response response = cpr::Put(
		cpr::Url{ Server::GetUrl() + "/Game_" + m_gameCode },
		cpr::Payload
		{
			{"Player name", m_player.GetName()}
		}
	);
}

void GameForm::LoadPlayerIcons(int playerCount)
{
	switch (playerCount)
	{
	case 4:
		m_playerFourTower = std::make_unique<QPixmap>();
		m_playerFourFlag = std::make_unique<QPixmap>();

		m_playerFourTower->load(QDir::currentPath() + "/Castle_P4.png");
		m_playerFourFlag->load(QDir::currentPath() + "/Flag_P4.png");
		__fallthrough;

	case 3:
		m_playerThreeTower = std::make_unique<QPixmap>();
		m_playerThreeFlag = std::make_unique<QPixmap>();

		m_playerThreeTower->load(QDir::currentPath() + "/Castle_P3.png");
		m_playerThreeFlag->load(QDir::currentPath() + "/Flag_P3.png");
		__fallthrough;

	case 2:
		m_playerOneTower = std::make_unique<QPixmap>();
		m_playerTwoTower = std::make_unique<QPixmap>();
		m_playerOneFlag = std::make_unique<QPixmap>();
		m_playerTwoFlag = std::make_unique<QPixmap>();

		m_playerTwoTower->load(QDir::currentPath() + "/Castle_P2.png");
		m_playerOneTower->load(QDir::currentPath() + "/Castle_P1.png");
		m_playerTwoFlag->load(QDir::currentPath() + "/Flag_P2.png");
		m_playerOneFlag->load(QDir::currentPath() + "/Flag_P1.png");
		break;
	}
}

void GameForm::DisplayPlayerMap(int playerCount)
{
	m_ui.PlayerMap2->setVisible(false);
	m_ui.PlayerMap3->setVisible(false);
	m_ui.PlayerMap4->setVisible(false);

	switch (playerCount)
	{
	case 2:
		m_ui.PlayerMap2->setVisible(true);
		break;

	case 3:
		m_ui.PlayerMap3->setVisible(true);
		break;

	case 4:
		m_ui.PlayerMap4->setVisible(true);
		break;
	}
}

void GameForm::GetMapRegions(int playerCount)
{

	switch (playerCount)
	{
	case 2:
		m_regions = m_ui.Regions2->findChildren<QLabel*>();
		break;

	case 3:
		m_regions = m_ui.Regions3->findChildren<QLabel*>();
		break;

	case 4:
		m_regions = m_ui.Regions4->findChildren<QLabel*>();
		break;
	}
}

void GameForm::SendRegionCount()
{
	cpr::Response response = cpr::Put(
		cpr::Url{ Server::GetUrl() + "/Game_" + m_gameCode },
		cpr::Payload
		{
			{"Regions count", std::to_string(m_regions.size())}
		}
	);
}

void GameForm::WaitForPlayers()
{
	cpr::Response response = cpr::Get(cpr::Url{ Server::GetUrl() + "/Game_" + m_gameCode });

	auto arguments = crow::json::load(response.text);
	std::string gameState = arguments["Game state"].s();

	if (gameState != "JOINING")
	{
		m_timer->stop();
		BaseSelectionFight();
	}
}

void GameForm::EmptyLabels()
{
	for (int i = 0; i < m_regions.size(); i++)
	{
		m_regions[i]->setPixmap(QPixmap());
	}
}

void GameForm::DisplayQuestion(bool isNumerical, const Question& question)
{
	m_ui.QuestionDisplay->setVisible(true);
	m_ui.QuestionDisplay->raise();

	if (isNumerical == true)
	{
		m_ui.NumericalQuestion->setVisible(true);
		m_ui.MultipleChoiceQuestion->setVisible(false);
		m_ui.TrueFalseQuestion->setVisible(false);

		m_ui.QuestionText->setText(QString::fromStdString(question.GetText()));
	}
	else
	{

	}
}

void GameForm::BaseSelectionFight()
{
	//TO DO: add ui to inform players the game state

	cpr::Response response = cpr::Get(cpr::Url{ Server::GetUrl() + "/Game_" + m_gameCode });

	auto arguments = crow::json::load(response.text);
	std::string gameState = arguments["Game state"].s();

	if (gameState != "BASE_FIGHT")
	{

	}
	else
	{
		Question currentQuestion;

		std::string questionText = arguments["Question text"].s();
		int questionType = arguments["Question type"].i();

		currentQuestion.SetText(questionText);
		currentQuestion.SetIsNumerical(questionType);

		DisplayQuestion(true, currentQuestion);
	}
}
