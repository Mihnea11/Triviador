#pragma once

#include <QDialog>
#include <QFileDialog>
#include "Player.h"
#include "ui_GameWindow.h"
#include "Quiz.h"

class GameWindow : public QDialog
{
	Q_OBJECT

private:
	Ui::GameWindow ui;
	Player player;

	void ToggleForm(QWidget* disabledForm, QWidget* enabledForm);
	void DisplayPlayerInfo();
	void RandomQuestion();
	void PlayButton();
	void VerifyButton();

	void MenuPlayButton();
	void MenuSettingsButton();
	void MenuQuitButton();
	void MenuViewProfileButton();
	void SettingsSaveButton();
	void ProfileChangePictureButton();
	void ProfileEditButton();
	void ProfileSaveButton();
	void EditProfileSaveButton();
public:
	explicit GameWindow();
	bool CheckAnswer(Quiz quiz);
	~GameWindow();

private slots:
	void MenuPlayButtonClicked() { MenuPlayButton(); }
	void MenuSettingsButtonClicked() { MenuSettingsButton(); }
	void MenuQuitButtonClicked() { MenuQuitButton(); }
	void MenuViewProfileButtonClicked() { MenuViewProfileButton(); }
	void SettingsSaveButtonClicked() { SettingsSaveButton(); }
	void ProfileChangePictureButtonClicked() { ProfileChangePictureButton(); }
	void ProfileEditButtonClicked() { ProfileEditButton(); }
	void ProfileSaveButtonClicked() { ProfileSaveButton(); }
	void EditProfileSaveButtonClicked() { EditProfileSaveButton(); }
};

