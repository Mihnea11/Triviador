#pragma once
#include <QtWidgets/QMainWindow>

#include "ui_GameForm.h"

class GameForm : public QMainWindow
{
	Q_OBJECT

public:
	GameForm(QWidget* parent = nullptr);
	~GameForm();

private:
	Ui::GameForm ui;

private slots:

};

