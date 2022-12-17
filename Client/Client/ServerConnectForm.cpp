#include "ServerConnectForm.h"

ServerConnectForm::ServerConnectForm(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.IPConnectButton, SIGNAL(clicked()), this, SLOT(ConnectButtonClicked()));
}

void ServerConnectForm::ConnectButton()
{
	std::string ip = ui.IPEnterIp->text().toStdString();
	std::regex ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");

	try
	{
		if (ip != "")
		{
			CheckIp(ip);

			Server::SetIp(ip);
		}
	}
	catch (std::exception exception)
	{
		ui.IPErrorLabel->setText(exception.what());
	}

	LoginForm* window = new LoginForm();
	window->show();

	close();
}

void ServerConnectForm::CheckIp(const std::string& ip)
{
	std::regex ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");

	if (std::regex_match(ip, ipv4) == false)
	{
		throw std::exception("Invalid ip adress");
	}
}
