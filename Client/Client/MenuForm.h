#pragma once
#include <QtWidgets/QMainWindow>
#include <QPainterPath>
#include <QFileDialog>
#include <QPainter>
#include <QTimer>

#include "Utils.h"
#include "Player.h"
#include "LoginForm.h"
#include "ui_MenuForm.h"

class MenuForm : public QMainWindow
{
	Q_OBJECT

public:
	MenuForm(QWidget* parent = nullptr);
	MenuForm(const Player& player, QWidget* parent = nullptr);
	~MenuForm();

	void SetPlayer(const Player& player);

	Player GetPlayer();

private:
	Ui::MenuFormClass ui;
	Player m_player;
	QTimer* timer;

	void ConnectUi();
	void LoadPlayerInfo();
	void UploadImageToLabel(QLabel* label, const Player& player);
	void ToggleWidget(QWidget* disabledForm, QWidget* enabledForm);
	void DisplayPlayer(const std::string& playerCount, const Player& currentUser);
	void DisplayRoom(const std::string& roomCode);
	void UpdateRoom();
	void WaitForSeconds(int seconds);

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
	void RoomCreateRoomButton();

	void ValidateNewInformation();

private slots:
	void MenuEditProfileButtonClicked() { MenuEditProfileButton(); }
	void EditProfileBackButtonClicked() { EditProfileBackButton(); }
	void EditProfileChangePictureButtonClicked() { EditProfileChangeProfilePictureButton(); }
	void EditProfileButtonClicked() { EditProfileButton(); }
	void ChangeInformationsSaveButtonClicked() { ChangeInformationsSaveButton(); }
	void MenuQuitButtonClicked() { MenuQuitButton(); }
	void MenuPlayButtonClicked() { MenuPLayButton(); }
	void PlayGameBackButtonClicked() { PlayGameBackButton(); }
	void PlayGameJoinRoomButtonClicked() { PlayGameJoinRoomButton(); }
	void PlayGameEnterCodeButtonClicked() { PlayGameEnterCodeButton(); }
	void PlayGameCreateRoomButtonClicked() { PlayGameCreateRoomButton(); }
	void RoomOptionsBackButtonClicked() { RoomOptionsBackButton(); }
	void RoomCreateRoomButtonClicked() { RoomCreateRoomButton(); }
	void UpdateRoomInformation() { UpdateRoom(); }
};