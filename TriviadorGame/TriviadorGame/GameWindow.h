#pragma once

#include <QDialog>

#include "Player.h"
#include "ui_GameWindow.h"

class GameWindow : public QDialog
{
	Q_OBJECT

private:
	Ui::GameWindow ui;
	Player player;


public:
	explicit GameWindow(QWidget* parent = nullptr);

	~GameWindow();
};

