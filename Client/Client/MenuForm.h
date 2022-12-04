#pragma once
#include <QtWidgets/QMainWindow>
#include "LoginForm.h"
#include "ui_MenuForm.h"

class MenuForm: public QMainWindow
{
	Q_OBJECT

private:
	Ui::MenuFormClass ui;
	void ToggleWidget(QWidget* disabledForm, QWidget* enabledForm);

public:
	MenuForm(QWidget* parent = nullptr);
	~MenuForm();

private slots:
	void ProfileButtonClicked() { ToggleWidget(ui.GameMenu, ui.EditProfileWidget); }
};

