#pragma once

#include <QDialog>
#include <QFileDialog>
#include "Player.h"
#include "ui_GameWindow.h"


class GameWindow : public QDialog
{
	Q_OBJECT

private:
	Ui::GameWindow ui;
	Player player;
	void ToggleForm(QWidget* disabledForm, QWidget* enabledForm);
	void RandomQuestion();
	void PlayButton();
	

public:
	explicit GameWindow();

	~GameWindow();
private slots:

	void EditButtonClicked() { ToggleForm(ui.GameForm, ui.ProfileForm); }
	void SaveButtonClicked() { ToggleForm(ui.ProfileForm, ui.GameForm); }
	void EditProfileButtonClicked() { ToggleForm(ui.ProfileForm, ui.EditProfileForm); }
	void SaveProfileButtonClicked() { ToggleForm(ui.EditProfileForm, ui.ProfileForm); }
	void SettingsButtonClicked() { ToggleForm(ui.GameForm, ui.SettingsForm); }
	void SaveSettingsButtonClicked() { ToggleForm(ui.SettingsForm, ui.GameForm); }
	void on_ChangeProfilePictureButton_clicked();
	void PlayButtonClicked() { PlayButton(); }
	
};

