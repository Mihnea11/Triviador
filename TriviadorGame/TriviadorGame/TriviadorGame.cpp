#include "TriviadorGame.h"

TriviadorGame::TriviadorGame(QWidget *parent): QMainWindow(parent)
{
    ui.setupUi(this);

    ui.LoginForm->setVisible(true);
    ui.RegisterForm->setVisible(false);
    ui.RegistrationConfirmationForm->setVisible(false);

    connect(ui.LoginButton, SIGNAL(clicked()), this, SLOT(LoginButtonClicked()));
    connect(ui.RegisterButton, SIGNAL(clicked()), this, SLOT(RegisterButtonClicked()));
    connect(ui.LoginRegisterButton, SIGNAL(clicked()), this, SLOT(LoginRegisterButtonClicked()));
    connect(ui.RegisterBackButton, SIGNAL(clicked()), this, SLOT(RegisterBackButtonClicked()));
}

TriviadorGame::~TriviadorGame()
{

}

void TriviadorGame::CheckUser(const std::string& user)
{
    if (user == "")
    {
        throw std::exception("Username field can't be empty");
    }

    std::ifstream in("user_details.txt");

    std::string currentUser;
    while (in >> currentUser)
    {
        if (user == currentUser)
        {
            throw std::exception("Username already used");
        }

        in.get();
    }
}

void TriviadorGame::CheckEmail(const std::string& email)
{
    if (email == "")
    {
        throw std::exception("Email field can't be empty");
    }

    const std::regex emailPattern("^([a-zA-Z0-9_\\ \\.+)@([a-zA-Z0-9_\\-\\.]+)\\.([a-zA-Z]{2,5})$");
    
    if (!std::regex_match(email, emailPattern))
    {
        throw std::exception("Invalid email");
    }
}

void TriviadorGame::CheckPassword(const std::string& password)
{
    if (password == "")
    {
        throw std::exception("Password field can't be empty");
    }
    if (password != ui.RegisterConfirmPassword->text().toStdString())
    {
        throw std::exception("Passwords do not match");
    }

    const std::regex passwordPattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$");
    
    if (!std::regex_match(password, passwordPattern))
    {
        throw std::exception("Invalid password!\nThe password must containt at least:\n-8 characters\n-a number\n-a special character");
    }
}

void TriviadorGame::CheckLoginCredentials(const std::string& userName, const std::string& password)
{
    std::ifstream in("user_details.txt");


    bool found = false;
    std::string currentName;
    std::string currentPassword;
    while (in >> currentName >> currentPassword)
    {
        if (currentName == userName && currentPassword != password)
        {
            throw std::exception("Invalid password");
        }

        if (currentName == userName)
        {
            found = true;
        }

        in.get();
    }

    if (found == false)
    {
        throw std::exception("Username not found");
    }
}

void TriviadorGame::SaveUserDetails(const std::string& userName, const std::string& userPassword, const std::string& userEmail)
{
    std::ofstream out;
    out.open("user_details.txt", std::ios::app);

    out << userName << " " << userPassword << " " << userEmail << "\n";

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
        CheckEmail(email);
        CheckPassword(password);

        SaveUserDetails(userName, password, email);
        ToggleForm(ui.RegisterForm, ui.RegistrationConfirmationForm);
        WaitForSeconds(3);
        ToggleForm(ui.RegistrationConfirmationForm, ui.LoginForm);
    }
    catch (std::exception exception)
    {
        ui.RegisterErrorLabel->setText(exception.what());
    }
}

void TriviadorGame::LoginUser()
{
    std::string userName = ui.LoginUsernameField->text().toStdString();
    std::string password = ui.LoginPasswordField->text().toStdString();

    try
    {
        CheckLoginCredentials(userName, password);

        //TO DO: login user
    }
    catch (std::exception exception)
    {
        ui.LoginErrorLabel->setText(exception.what());
    }
}

void TriviadorGame::ToggleForm(QWidget* disabledForm, QWidget* enabledForm)
{
    disabledForm->setVisible(false);
    enabledForm->setVisible(true);
}

void TriviadorGame::WaitForSeconds(int seconds)
{
    QTime delayTime = QTime::currentTime().addSecs(seconds);
    while (QTime::currentTime() < delayTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

