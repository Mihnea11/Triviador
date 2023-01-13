#pragma once
#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QMouseEvent>
#include <cpr/cpr.h>
#include <QObject>
#include <crow.h>
#include <QTimer>

#include "User.h"
#include "Utils.h"
#include "Question.h"
#include "ui_GameForm.h"

class GameForm : public QMainWindow
{
	Q_OBJECT

public:
	GameForm(QWidget* parent = nullptr);
	GameForm(const User& player, const std::string& gameCode, bool isOwner = false, QWidget* parent = nullptr);
	~GameForm();

	void SetIsOwner(bool isOwner);

	bool GetIsOwner() const;

	//virtual void mousePressEvent(QMouseEvent* event) override;

private:
	Ui::GameForm m_ui;
	User m_player;
	std::string m_gameCode;
	QList<QLabel*> m_regions;
	bool m_isOwner;
	std::shared_ptr<QTimer> m_updateTimer;
	std::shared_ptr<QTimer> m_answerTimer;

	std::unique_ptr<QPixmap> m_playerOneTower;
	std::unique_ptr<QPixmap> m_playerTwoTower;
	std::unique_ptr<QPixmap> m_playerThreeTower;
	std::unique_ptr<QPixmap> m_playerFourTower;

	std::unique_ptr<QPixmap> m_playerOneFlag;
	std::unique_ptr<QPixmap> m_playerTwoFlag;
	std::unique_ptr<QPixmap> m_playerThreeFlag;
	std::unique_ptr<QPixmap> m_playerFourFlag;

	int GetPlayerCount();
	void JoinPlayer();
	void LoadPlayerIcons(int playerCount);
	void DisplayPlayerMap(int playerCount);
	void GetMapRegions(int playerCount);
	void SendRegionCount();
	void EmptyLabels();
	void UpdateGame();
	void UpdateCountdown();

	void SendNumericalAnswer();
	void SendChosenAnswer();

	void DisplayQuestion(bool isNumerical, const Question& question);
	void BaseSelectionFight();

private slots:
	void UpdateGameState() { UpdateGame(); }
	void UpdateCountdownTimer() { UpdateCountdown(); }
	void SendNumericalAnswerToServer() { SendNumericalAnswer(); }

};

