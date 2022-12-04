#pragma once
#include <QtWidgets/QMainWindow>

#include "ui_MenuForm.h"

class MenuForm: public QMainWindow
{
	Q_OBJECT

private:
	Ui::MenuFormClass ui;

public:
	MenuForm(QWidget* parent = nullptr);
	~MenuForm();
};

