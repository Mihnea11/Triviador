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

	void UploadImageToLabel(QLabel* label);
	void LoadMenuProfileImage();
	void ToggleWidget(QWidget* disabledForm, QWidget* enabledForm);
	void ProfileButton();
	void BackButton();
	void ChangeProfilePictureButton();
	void SaveInformationsButton();
	void EditProfileButton();
	void QuitButton();

public:
	MenuForm(QWidget* parent = nullptr);
	MenuForm(const Player& player, QWidget* parent = nullptr);
	~MenuForm();

private slots:
	void ProfileButtonClicked() { ProfileButton(); }
	void BackButtonClicked() { BackButton(); }
	void ChangePictureButtonClicked() { ChangeProfilePictureButton(); }
	void EditProfileButtonClicked(){ EditProfileButton(); }
	void SaveInformationsButtonClicked() { ToggleWidget(ui.ChangeInformationsWidget, ui.EditProfileWidget); }
	void QuitButtonClicked() { QuitButton(); }

};


