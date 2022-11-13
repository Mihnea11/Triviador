#include "TriviadorGame.h"

TriviadorGame::TriviadorGame(QWidget *parent): QMainWindow(parent)
{
    ui.setupUi(this);
    
   

    connect(ui.RegisterButton, SIGNAL(clicked()), this, SLOT(RegisterButtonClicked()));
    connect(ui.LoginButton, SIGNAL(clicked()), this, SLOT(LoginButtonClicked()));



}

TriviadorGame::~TriviadorGame()
{

}

void TriviadorGame::RegisterUser()
{
   

    update();
    //TO DO: add player to database
}

void TriviadorGame::LoginUser()
{
    //TO DO: check if player exists in database
}

void TriviadorGame::RegisterButtonClicked()
{
    std::string email = ui.UserField->text().toStdString();/// this function translates a qstring to a std string
    std::string password = ui.PasswordFIeld->text().toStdString();

}