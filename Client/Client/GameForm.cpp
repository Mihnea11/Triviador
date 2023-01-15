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

	m_updateTimer = std::make_shared<QTimer>(this);
	m_answerTimer = std::make_shared<QTimer>(this);

	connect(m_ui.NumericalConfirmAnswer, SIGNAL(clicked()), this, SLOT(SendNumericalAnswerToServer()));

	connect(m_updateTimer.get(), SIGNAL(timeout()), this, SLOT(UpdateGameState()));
	connect(m_answerTimer.get(), SIGNAL(timeout()), this, SLOT(UpdateCountdownTimer()));

	m_ui.QuestionDisplay->setVisible(false);
	
	m_updateTimer->start(500);
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

void GameForm::EmptyLabels()
{
	for (int i = 0; i < m_regions.size(); i++)
	{
		m_regions[i]->setPixmap(QPixmap());
	}
}

void GameForm::UpdateGame()
{
	cpr::Response response = cpr::Get(cpr::Url{ Server::GetUrl() + "/Game_" + m_gameCode });

	auto arguments = crow::json::load(response.text);
	std::string gameState = arguments["Game state"].s();

	if (gameState == "JOINING")
	{
		m_ui.WaitingPlayers->setVisible(true);
	}
	else if (gameState == "BASE_FIGHT")
	{
		m_ui.WaitingPlayers->setVisible(false);
		m_updateTimer->stop();
		BaseSelectionFight();
	}
	else if (gameState == "BASE_SELECTION")
	{
		m_ui.QuestionDisplay->setVisible(false);
	}
}

void GameForm::UpdateCountdown()
{
	std::string digits = "0123456789";
	std::string timerText = m_ui.TimerLabel->text().toStdString();

	std::size_t start = timerText.find_first_of(digits);
	std::size_t end = timerText.find_first_not_of(digits, start);
	std::string timeLeftText = timerText.substr(start, end != std::string::npos ? start - end : end);
	
	int timeLeft = std::stoi(timeLeftText);
	timeLeft -= 1;
	m_ui.TimerLabel->setText("Time left: " + QString::number(timeLeft));

	if (timeLeft == 0)
	{
		m_answerTimer->stop();

		if (m_ui.NumericalQuestion->isVisible() == true)
		{
			SendNumericalAnswer();
		}
		else
		{
			SendChosenAnswer();
		}
	}
}

void GameForm::SendNumericalAnswer()
{
	m_answerTimer->stop();

	std::string digits = "0123456789";
	std::string timerText = m_ui.TimerLabel->text().toStdString();

	std::size_t start = timerText.find_first_of(digits);
	std::size_t end = timerText.find_first_not_of(digits, start);
	std::string timeLeftText = timerText.substr(start, end != std::string::npos ? start - end : end);

	int timeLeft = std::stoi(timeLeftText);
	int answerTime = 10 - timeLeft;

	cpr::Response response = cpr::Put(
		cpr::Url{ Server::GetUrl() + "/Game_" + m_gameCode },
		cpr::Payload
		{
			{"Player name", m_player.GetName()},
			{"Answer", m_ui.NumericalAnswer->text().toStdString()},
			{"Answer time", std::to_string(answerTime)}
		}
	);

	m_updateTimer->start(500);
}

void GameForm::SendChosenAnswer()
{
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
		if (question.GetIncorrectAnswers().size() != 3)
		{
			m_ui.NumericalQuestion->setVisible(false);
			m_ui.MultipleChoiceQuestion->setVisible(false);
			m_ui.TrueFalseQuestion->setVisible(true);

			m_ui.QuestionText->setText(QString::fromStdString(question.GetText()));
		}
		else
		{
			m_ui.NumericalQuestion->setVisible(false);
			m_ui.MultipleChoiceQuestion->setVisible(true);
			m_ui.TrueFalseQuestion->setVisible(false);

			m_ui.QuestionText->setText(QString::fromStdString(question.GetText()));
			//TO DO: load answers
		}
	}

	m_ui.TimerLabel->setText("Time left: 10");
	m_answerTimer->start(1000);
}

void GameForm::BaseSelectionFight()
{
	//TO DO: add ui to inform players the game state

	cpr::Response response = cpr::Get(cpr::Url{ Server::GetUrl() + "/Game_" + m_gameCode });

	auto arguments = crow::json::load(response.text);
	std::string gameState = arguments["Game state"].s();

	Question currentQuestion;

	std::string questionText = arguments["Question text"].s();
	int questionType = arguments["Question type"].i();

	currentQuestion.SetText(questionText);
	currentQuestion.SetIsNumerical(questionType);

	DisplayQuestion(true, currentQuestion);
}
