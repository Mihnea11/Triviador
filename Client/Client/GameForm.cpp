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
}


GameForm::~GameForm()
{
}

int GameForm::GetPlayerCount()
{
	cpr::Response response=cpr::Get(cpr::Url{Server::GetUrl()+"/Game_"+m_gameCode});
	auto arguments = crow::json::load(response.text);
	int playerCount = arguments["Player count"].i();

	return playerCount;
}
