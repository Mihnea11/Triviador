#pragma once

#include <QDialog>

#include "ui_GameWindow.h"


class GameWindow : public QDialog
{
	Q_OBJECT

private:
	Ui::GameWindow ui;
	void ToggleForm(QWidget* disabledForm, QWidget* enabledForm);

public:
	explicit GameWindow(QWidget* parent = nullptr);
	~GameWindow();
private slots:
	void EditButtonClicked() { ToggleForm(ui.GameWindowForm, ui.ProfileForm); }
	void SaveButtonProfileFormClicked() {  }
	
};

