#include "TriviadorGame.h"

TriviadorGame::TriviadorGame(QWidget *parent): QMainWindow(parent)
{
    ui.setupUi(this);
 
   

    connect(ui.RegisterButton, SIGNAL(clicked()), this, SLOT(RegisterButtonClicked()));
  



}

bool TriviadorGame::emailCheck(std::string email)
{
    const std::regex emailPattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    if (!std::regex_match(email, emailPattern))
    {
        throw std::exception("Invalid email!");
    }
    return true;
}


bool TriviadorGame::passwordCheck(std::string password)
{
    const std::regex passwordPattern("(? = .*[A - z\d] + )(? = .*[A - z@!? ] + )(? = .*[a - z\d@!? ] + )(? = .*[A - Z\d@!? ] + )[A - z\d@!? ]{8,}");
    if (!std::regex_match(password, passwordPattern))
    {
        throw std::exception("Invalid password! The password must containt at least 8 characters, a number and a special character!");
    }
    return true;
}

bool TriviadorGame::ValidateInput(std::string user, std::string password)
{
    if (!emailCheck(user) || !passwordCheck(password)) return false;
    return true;
}

TriviadorGame::~TriviadorGame()
{

}

void TriviadorGame::RegisterUser()
{
    std::string userName = ui.RegisterUsernameField->text().toStdString();
    std::string password = ui.RegisterPasswordField->text().toStdString();
    std::string email = ui.RegisterEmailField->text().toStdString();
    
    
}

void TriviadorGame::LoginUser()
{
    //TO DO: check if player exists in database
}

