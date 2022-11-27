#include "GameWindow.h"
#include "Quiz.h"

GameWindow::GameWindow() : QDialog()
{
	ui.setupUi(this);

	ui.GameMenu->setVisible(true);
	ui.PlayerProfile->setVisible(false);
	ui.EditPlayerProfile->setVisible(false);
	ui.Settings->setVisible(false);
	ui.Game->setVisible(false);

	connect(ui.MenuPlayButton, SIGNAL(clicked()), this, SLOT(MenuPlayButtonClicked()));
	connect(ui.MenuSettingsButton, SIGNAL(clicked()), this, SLOT(MenuSettingsButtonClicked()));
	connect(ui.MenuQuitButton, SIGNAL(clicked()), this, SLOT(MenuQuitButtonClicked()));
	connect(ui.MenuViewProfileButton, SIGNAL(clicked()), this, SLOT(MenuViewProfileButtonClicked()));
	connect(ui.SettingsSaveButton, SIGNAL(clicked()), this, SLOT(SettingsSaveButtonClicked()));
	connect(ui.ProfileChangePictureButton, SIGNAL(clicked()), this, SLOT(ProfileChangePictureButtonClicked()));
	connect(ui.ProfileEditButton, SIGNAL(clicked()), this, SLOT(ProfileEditButtonClicked()));
	connect(ui.ProfileSaveButton, SIGNAL(clicked()), this, SLOT(ProfileSaveButtonClicked()));
	connect(ui.EditSaveChangesButton, SIGNAL(clicked()), this, SLOT(EditProfileSaveButtonClicked()));
}

bool GameWindow::CheckAnswer(Quiz quiz)
{
	std::string answer = ui.AnswerLabel->toPlainText().toStdString();
	if (answer == quiz.GetQuestionAnswer())
	{
		return true;
	}

	return false;
}

GameWindow::~GameWindow()
{
}

void GameWindow::DisplayPlayerInfo()
{
	//TO DO: reffrence player
	ui.ProfileUsernameLabel->setText(QString::fromStdString(player.GetUserName()));
	ui.ProfileEmailLabel->setText(QString::fromStdString(player.GetUserEmail()));
	ui.ProfileDisplayWonGames->setText(QString::fromStdString(std::to_string(player.GetWonGames())));
	ui.ProfileDisplayPlayedGames->setText(QString::fromStdString(std::to_string(player.GetPlayedGames())));
	ui.ProfileDisplayWinRate->setText(QString::fromStdString(std::to_string(player.GetWinRate())));
}

void GameWindow::ToggleForm(QWidget* disabledForm, QWidget* enabledForm)
{
	disabledForm->setVisible(false);
	enabledForm->setVisible(true);
}

void GameWindow::PlayButton()
{
	ToggleForm(ui.GameMenu, ui.Game);
	RandomQuestion();
}

void GameWindow::VerifyButton()
{

}

void GameWindow::MenuPlayButton()
{
	ToggleForm(ui.GameMenu, ui.Game);
}

void GameWindow::MenuSettingsButton()
{
	ToggleForm(ui.GameMenu, ui.Settings);
}

void GameWindow::MenuQuitButton()
{
	this->close();
}

void GameWindow::MenuViewProfileButton()
{
	DisplayPlayerInfo();
	ToggleForm(ui.GameMenu, ui.PlayerProfile);
}

void GameWindow::SettingsSaveButton()
{
	//TO DO: save settings
	ToggleForm(ui.Settings, ui.GameMenu);
}

void GameWindow::ProfileChangePictureButton()
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

void GameWindow::ProfileEditButton()
{
	ToggleForm(ui.PlayerProfile, ui.EditPlayerProfile);
}

void GameWindow::ProfileSaveButton()
{
	ToggleForm(ui.PlayerProfile, ui.GameMenu);
}

void GameWindow::EditProfileSaveButton()
{
	ToggleForm(ui.EditPlayerProfile, ui.PlayerProfile);
}

void GameWindow::RandomQuestion()
{
	Quiz question;
	question = question.PickRandomQuiz();
	ui.QuestionLabel->setText(QString::fromStdString(question.GetQuestionText()));
	if (CheckAnswer(question))
	{
		ui.VerifyAnswerLabel->setText("Correct!");
	}
	else ui.VerifyAnswerLabel->setText("Wrong!");
}

