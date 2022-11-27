#include "GameWindow.h"



GameWindow::GameWindow(QWidget* parent) : QDialog(parent)
{
	ui.setupUi(this);

	ui.ShowWonGamesLabel->setText(QString::fromStdString(std::to_string(player.GetWonGames())));
	ui.ShowPlayedGamesLabel->setText(QString::fromStdString(std::to_string(player.GetPlayedGames())));
	ui.ShowWinrateLabel->setText(QString::fromStdString(std::to_string(player.GetWinRate())));

	ui.SoundSlider->setMinimum(0);
	ui.SoundSlider->setMaximum(100);
	ui.SoundSlider->setValue(50);

	ui.ShowSoundLabel->setText("50");

	ui.UsernameProfileFrom->setText(QString::fromStdString(player.GetUserName()));
	ui.EmailLabelProfileForm->setText(QString::fromStdString(player.GetUserEmail()));

	ui.GameForm->setVisible(true);
	ui.ProfileForm->setVisible(false);
	ui.EditProfileForm->setVisible(false);
	ui.SettingsForm->setVisible(false);

	connect(ui.EditButton, SIGNAL(clicked()), this, SLOT(EditButtonClicked()));
	connect(ui.SaveButton, SIGNAL(clicked()), this, SLOT(SaveButtonClicked()));
	connect(ui.EditButtonProfileForm, SIGNAL(clicked()), this, SLOT(EditProfileButtonClicked()));
	connect(ui.SaveProfileButton, SIGNAL(clicked()), this, SLOT(SaveProfileButtonClicked()));
	connect(ui.SettingsButton, SIGNAL(clicked()), this, SLOT(SettingsButtonClicked()));
	connect(ui.SaveSettingsButton, SIGNAL(clicked()), this, SLOT(SaveSettingsButtonClicked()));

	QObject::connect(ui.SoundSlider, &QSlider::valueChanged, [&]() { ui.ShowSoundLabel->setText(QString::fromStdString(std::to_string(ui.SoundSlider->value()))); });
}

GameWindow::~GameWindow()
{
}
void GameWindow::ToggleForm(QWidget* disabledForm, QWidget* enabledForm)
{
	disabledForm->setVisible(false);
	enabledForm->setVisible(true);
}

void GameWindow::on_ChangeProfilePictureButton_clicked()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.png *.jpg *.jpeg *.bmp)"));
	if (QString::compare(filename, QString()) != 0)
	{
		QImage image;
		bool valid = image.load(filename);
		if (valid)
		{	
			image = image.scaledToWidth(ui.ProfilePictureLabel->width(), Qt::SmoothTransformation);
			ui.ProfilePictureLabel->setPixmap(QPixmap::fromImage(image));
		}
	}
}
