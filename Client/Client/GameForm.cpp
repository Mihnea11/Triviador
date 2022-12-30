#include "GameForm.h"

GameForm::GameForm(QWidget* parent)
{
	ui.setupUi(this);
	int playerCount = GetPlayerCount();
}

GameForm::GameForm(const std::string& gameCode, QWidget* parent)
{
	ui.setupUi(this);

	m_gameCode = gameCode;
	int playerCount = GetPlayerCount();
	DisplayPlayerMap(playerCount);
}


GameForm::~GameForm()
{
}

int GameForm::GetPlayerCount()
{
	cpr::Response response = cpr::Get(cpr::Url{ Server::GetUrl() + "/Game_" + m_gameCode });

	auto arguments = crow::json::load(response.text);
	int playerCount = arguments["Player count"].i();

	return playerCount;
}

void GameForm::DisplayPlayerMap(int playerCount)
{
	ui.PlayerMap2->setVisible(false);
	ui.PlayerMap3->setVisible(false);
	ui.PlayerMap4->setVisible(false);

	switch (playerCount)
	{
	case 2:
		ui.PlayerMap2->setVisible(true);
		break;

	case 3:
		ui.PlayerMap3->setVisible(true);
		break;

	case 4:
		ui.PlayerMap4->setVisible(true);
		break;
	}
}
