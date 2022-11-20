#pragma once

#include <QDialog>

#include "ui_GameWindow.h"

class GameWindow : public QDialog
{
	Q_OBJECT

private:
	Ui::GameWindow ui;

public:
	explicit GameWindow(QWidget* parent = nullptr);
	~GameWindow();
};

