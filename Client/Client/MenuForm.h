#pragma once
#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QPainter>
#include <QPainterPath>

#include "Player.h"
#include "LoginForm.h"
#include "ui_MenuForm.h"
#include "PlayForm.h"

class MenuForm : public QMainWindow
{
	Q_OBJECT

private:
	Ui::MenuFormClass ui;
	Player player;

	void UploadImageToLabel(QLabel* label);
	void ToggleWidget(QWidget* disabledForm, QWidget* enabledForm);
	void MenuEditProfileButton();
	void EditProfileBackButton();
	void EditProfileChangeProfilePictureButton();
	void SaveInformationsButton();
	void EditProfileButton();
	void MenuQuitButton();
	void PLayButton();

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
	void SaveInformationsButtonClicked() { ToggleWidget(ui.ChangeInformationsWidget, ui.EditProfileWidget); }
	void MenuQuitButtonClicked() { MenuQuitButton(); }
	void PlayButtonClicked() { PLayButton(); }
};


