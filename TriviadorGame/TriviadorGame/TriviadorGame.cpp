#include "TriviadorGame.h"

TriviadorGame::TriviadorGame(QWidget *parent): QMainWindow(parent)
{
    ui.setupUi(this);

    enableLoginForm = false;

    ui.LoginForm->setVisible(!enableLoginForm);
    ui.RegisterForm->setVisible(enableLoginForm);

    connect(ui.LoginButton, SIGNAL(clicked()), this, SLOT(LoginButtonClicked()));
    connect(ui.RegisterButton, SIGNAL(clicked()), this, SLOT(RegisterButtonClicked()));
    connect(ui.LoginRegisterButton, SIGNAL(clicked()), this, SLOT(ChangeFormClicked()));
    connect(ui.RegisterBackButton, SIGNAL(clicked()), this, SLOT(ChangeFormClicked()));
}

TriviadorGame::~TriviadorGame()
{

}

void TriviadorGame::CheckUser(std::string user)
{
    std::ifstream in("user_details.txt");

    std::string currentUser;
    while (in >> currentUser)
    {
        if (user == currentUser)
        {
            throw std::exception("Username already used!");
        }

        in.get();
    }
}

void TriviadorGame::CheckEmail(std::string email)
{
    const std::regex emailPattern("^([a-zA-Z0-9_\\ \\.+)@([a-zA-Z0-9_\\-\\.]+)\\.([a-zA-Z]{2,5})$");
    
    if (!std::regex_match(email, emailPattern))
    {
        throw std::exception("Invalid email!");
    }
}

void TriviadorGame::CheckPassword(std::string password)
{
    const std::regex passwordPattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$");
    if (!std::regex_match(password, passwordPattern))
    {
        throw std::exception("Invalid password! The password must containt at least 8 characters, a number and a special character!");
    }
}

void TriviadorGame::SaveUserDetails(std::string userName, std::string userEmail, std::string userPassword)
{
    std::ofstream out;
    out.open("user_details.txt", std::ios::app);

    Player player;
    player.SetUserName(userName);
    player.SetUserEmail(userEmail);
    player.SetUserPassword(userPassword);

    out << player;

    out.close();
}

void TriviadorGame::RegisterUser()
{
    std::string userName = ui.RegisterUsernameField->text().toStdString();
    std::string password = ui.RegisterPasswordField->text().toStdString();
    std::string email = ui.RegisterEmailField->text().toStdString();

    try 
    {
        CheckUser(userName);
        CheckPassword(password);
        CheckEmail(email);

        SaveUserDetails(userName, password, email);
    }
    catch (std::exception exception) 
    {
        ui.ErrorLabel->setText(exception.what());
    }
}

void TriviadorGame::LoginUser()
{
    std::ifstream in("user_details.txt");

    std::string userName = ui.LoginUsernameField->text().toStdString();
    std::string passWord = ui.LoginPasswordField->text().toStdString();

    std::string currentName;
    std::string currentEmail;
    std::string currentPassWord;
    while (in >> currentName >> currentEmail >> currentPassWord)
    {
        if (currentName == userName && currentPassWord == passWord)
        {
            //TO DO: log in user;
            break;
        }
        else if (currentName == userName && currentPassWord != passWord)
        {
            throw std::exception("Invalid password");
        }
    }

    throw std::exception("Username not found");
}

void TriviadorGame::ChangeForm()
{
    ui.LoginForm->setVisible(enableLoginForm);
    ui.RegisterForm->setVisible(!enableLoginForm);
    enableLoginForm = !enableLoginForm;

    update();
}

