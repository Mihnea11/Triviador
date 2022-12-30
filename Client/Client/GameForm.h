#pragma once
#include <QtWidgets/QMainWindow>
#include <cpr/cpr.h>
#include <crow.h>

#include "Utils.h"
#include "ui_GameForm.h"

class GameForm : public QMainWindow
{
	Q_OBJECT

public:
	GameForm(QWidget* parent = nullptr);
	GameForm(const std::string& gameCode, QWidget* parent = nullptr);
	~GameForm();

private:
	Ui::GameForm ui;
	std::string m_gameCode;

	int GetPlayerCount();
	void DisplayPlayerMap(int playerCount);

private slots:

};

