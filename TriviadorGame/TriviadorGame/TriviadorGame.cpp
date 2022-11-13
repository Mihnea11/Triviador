#include "TriviadorGame.h"

TriviadorGame::TriviadorGame(QWidget *parent): QMainWindow(parent)
{
    ui.setupUi(this);
    
    ui.LoginForm->setEnabled(true);
    ui.RegisterForm->setEnabled(false);

    connect(ui.RegisterButton, SIGNAL(clicked()), this, SLOT(RegisterButtonClicked()));
    connect(ui.LoginButton, SIGNAL(clicked()), this, SLOT(LoginButtonClicked()));
}

TriviadorGame::~TriviadorGame()
{

}

void TriviadorGame::RegisterUser()
{
    ui.LoginForm->setEnabled(false);
    ui.RegisterForm->setEnabled(true);

    update();
    //TO DO: add player to database
}

void TriviadorGame::LoginUser()
{
    //TO DO: check if player exists in database
}
