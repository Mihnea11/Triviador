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
	void ToggleForm(QWidget* disabledForm, QWidget* enabledForm);


public:
	explicit GameWindow(QWidget* parent = nullptr);

	~GameWindow();
private slots:

	void EditButtonClicked() { ToggleForm(ui.GameForm, ui.ProfileForm); }
	void SaveButtonClicked() { ToggleForm(ui.ProfileForm, ui.GameForm); }
	void EditProfileButtonClicked() { ToggleForm(ui.ProfileForm, ui.EditProfileForm); }
	void SaveProfileButtonClicked() { ToggleForm(ui.EditProfileForm, ui.ProfileForm); }
};

