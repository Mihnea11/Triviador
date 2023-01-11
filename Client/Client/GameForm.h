#pragma once
#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QMouseEvent>
#include <cpr/cpr.h>
#include <QObject>
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

	//virtual void mousePressEvent(QMouseEvent* event) override;

private:
	Ui::GameForm ui;
	std::string m_gameCode;
	QList<QLabel*> m_regions;

	std::unique_ptr<QPixmap> m_playerOneTower;
	std::unique_ptr<QPixmap> m_playerTwoTower;
	std::unique_ptr<QPixmap> m_playerThreeTower;
	std::unique_ptr<QPixmap> m_playerFourTower;

	std::unique_ptr<QPixmap> m_playerOneFlag;
	std::unique_ptr<QPixmap> m_playerTwoFlag;
	std::unique_ptr<QPixmap> m_playerThreeFlag;
	std::unique_ptr<QPixmap> m_playerFourFlag;

	int GetPlayerCount();
	void LoadPlayerIcons(int playerCount);
	void DisplayPlayerMap(int playerCount);
	void GetMapRegions(int playerCount);
	void EmptyLabels();
};

