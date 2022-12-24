#pragma once
#include <QtWidgets/QMainWindow>
#include <QPainterPath>
#include <QFileDialog>
#include <QPainter>
#include <QTimer>

#include "Utils.h"
#include "Player.h"
#include "MenuForm.h"
#include "ui_PlayForm.h"

class PlayForm : public QMainWindow
{
	Q_OBJECT

public:
	PlayForm(QWidget* parent = nullptr);
	PlayForm(const Player& player, QWidget* parent = nullptr);
	~PlayForm();

private:
	Ui::PlayFormClass ui;
	Player m_player;
	QTimer* timer;

	void ConnectUi();
	void ToggleWidget(QWidget* disabledForm, QWidget* enabledForm);

private slots:

};

