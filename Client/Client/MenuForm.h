#pragma once
#include <QtWidgets/QMainWindow>
#include <QPainterPath>
#include <QFileDialog>
#include <QPainter>
#include <QTimer>

#include "User.h"
#include "Utils.h"
#include "GameForm.h"
#include "LoginForm.h"
#include "ui_MenuForm.h"

class MenuForm : public QMainWindow
{
	Q_OBJECT

public:
	MenuForm(QWidget* parent = nullptr);
	MenuForm(const User& user, QWidget* parent = nullptr);
	~MenuForm();

	void SetUser(const User& user);

	User GetUser();

private:
	Ui::MenuFormClass m_ui;
	User m_user;
	std::shared_ptr<QTimer> m_timer;

	void ConnectUi();
	void LoadPlayerInfo();
	void UploadImageToLabel(QLabel* label, const User& player);
	void ToggleWidget(QWidget* disabledForm, QWidget* enabledForm);
	void DisplayUser(const std::string& playerCount, const User& currentUser);
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
	void StartGameButton();
	void LeftRoomOkButton();

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
	void StartGameButtonClicked() { StartGameButton(); }
	void LeftRoomOkButtonClicked() { LeftRoomOkButton(); }
	void UpdateRoomInformation() { UpdateRoom(); }
};