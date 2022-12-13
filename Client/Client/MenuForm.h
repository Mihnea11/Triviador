#pragma once
#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QPainter>
#include <QPainterPath>

#include "Player.h"
#include "LoginForm.h"
#include "ui_MenuForm.h"

class MenuForm : public QMainWindow
{
	Q_OBJECT

private:
	Ui::MenuFormClass ui;
	Player player;

	void LoadPlayerInfo();
	void UploadImageToLabel(QLabel* label);
	void ToggleWidget(QWidget* disabledForm, QWidget* enabledForm);
	void MenuEditProfileButton();
	void EditProfileBackButton();
	void EditProfileChangeProfilePictureButton();
	void ChangeInformationsSaveButton();
	void EditProfileButton();
	void MenuQuitButton();
	void MenuPLayButton();
	void PlayGameBackButton();
	void PlayGameJoinRoomButton();
	void PlayGameEnterCodeButton();
	void PlayGameCreateRoomButton();
	void RoomOptionsBackButton();

	void ValidateNewInformation();
public:
	MenuForm(QWidget* parent = nullptr);
	MenuForm(const Player& player, QWidget* parent = nullptr);
	~MenuForm();

	void SetPlayer(const Player& player);

	Player GetPlayer();

private slots:
	void MenuEditProfileButtonClicked() { MenuEditProfileButton(); }
	void EditProfileBackButtonClicked() { EditProfileBackButton(); }
	void EditProfileChangePictureButtonClicked() { EditProfileChangeProfilePictureButton(); }
	void EditProfileButtonClicked(){ EditProfileButton(); }
	void ChangeInformationsSaveButtonClicked() { ChangeInformationsSaveButton(); }
	void MenuQuitButtonClicked() { MenuQuitButton(); }
	void MenuPlayButtonClicked() { MenuPLayButton(); }
	void PlayGameBackButtonClicked() { PlayGameBackButton(); }
	void PlayGameJoinRoomButtonClicked() { PlayGameJoinRoomButton(); }
	void PlayGameEnterCodeButtonClicked() { PlayGameEnterCodeButton(); }
	void PlayGameCreateRoomButtonClicked() { PlayGameCreateRoomButton(); }
	void RoomOptionsBackButtonClicked() { RoomOptionsBackButton(); }
};


