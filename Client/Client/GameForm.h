#pragma once
#include <QtWidgets/QMainWindow>
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

	int GetPlayerCount();
	void DisplayPlayerMap(int playerCount);
	void GetMapRegions(int playerCount);
	void EmptyLabels();

private slots:

};

