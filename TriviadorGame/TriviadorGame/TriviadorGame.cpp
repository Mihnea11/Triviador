#include "TriviadorGame.h"
#define _REGEX_MAX_STACK_COUNT 1000

TriviadorGame::TriviadorGame(QWidget *parent): QMainWindow(parent)
{
    ui.setupUi(this);
 
   

    connect(ui.RegisterButton, SIGNAL(clicked()), this, SLOT(RegisterButtonClicked()));
  



}

bool TriviadorGame::EmailCheck(std::string email)
{
    const std::regex emailPattern("^([a-zA-Z0-9_\\ \\.+)@([a-zA-Z0-9_\\-\\.]+)\\.([a-zA-Z]{2,5})$");
    if (!std::regex_match(email, emailPattern))
    {
        throw std::exception("Invalid email!");
    }
    return true;
}


bool TriviadorGame::PasswordCheck(std::string password)
{
    const std::regex passwordPattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$");
    if (!std::regex_match(password, passwordPattern))
    {
        throw std::exception("Invalid password! The password must containt at least 8 characters, a number and a special character!");
    }
    return true;
}

bool TriviadorGame::ValidateInput(std::string user, std::string password)
{
    if (!EmailCheck(user) || !PasswordCheck(password)) return false;
    return true;
}

void TriviadorGame::SaveUserDetails(std::string userName, std::string userEmail, std::string userPassword)
{
    std::ofstream out("user_details.txt");
    Player player;
    player.SetUserName(userName);
    player.SetUserEmail(userEmail);
    player.SetUserPassword(userPassword);
    out << player;
}

TriviadorGame::~TriviadorGame()
{

}

void TriviadorGame::RegisterUser()
{
    std::string userName = ui.RegisterUsernameField->text().toStdString();
    std::string password = ui.RegisterPasswordField->text().toStdString();
    std::string email = ui.RegisterEmailField->text().toStdString();
    try {
        ValidateInput(email, password);
        SaveUserDetails(userName, password, email);
    }
    catch (std::exception exception) {

    }
     
}

void TriviadorGame::LoginUser()
{
    //TO DO: check if player exists in database
}

