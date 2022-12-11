#pragma once
#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QPainter>
#include <QPainterPath>

#include "Player.h"
#include "LoginForm.h"
#include "ui_PlayForm.h"

class PlayForm : public QMainWindow
{
	Q_OBJECT

private:
	Ui::PlayFormClass ui;
	void ToggleWidget(QWidget* disabledForm, QWidget* enabledForm);
	Player player;

	void CreateButton();

public:
	PlayForm(QWidget* parent = nullptr);
	PlayForm(const Player& player, QWidget* parent = nullptr);
	~PlayForm();

private slots:
	void CreateButtonClicked() { CreateButton(); }
};





