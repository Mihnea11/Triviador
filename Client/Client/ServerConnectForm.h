#pragma once
#include <QtWidgets/QMainWindow>
#include <cpr/cpr.h>
#include <regex>

#include "Utils.h"
#include "LoginForm.h"
#include "ui_ServerConnectForm.h"

class ServerConnectForm : public QMainWindow
{
	Q_OBJECT

public:
	ServerConnectForm(QWidget* parent = nullptr);

private:
	Ui::ServerConnectForm ui;

	void ConnectButton();
	void CheckIp(const std::string& ip);

private slots:
	void ConnectButtonClicked() { ConnectButton(); }
};

