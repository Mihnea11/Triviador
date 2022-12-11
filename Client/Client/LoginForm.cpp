#include "LoginForm.h"
#include "MenuForm.h"
LoginForm::LoginForm(QWidget* parent): QMainWindow(parent)
{
    ui.setupUi(this);
    
    ui.LoginForm->setVisible(true);
    ui.RegisterForm->setVisible(false);
    ui.RegistrationConfirmationForm->setVisible(false);
    ui.LoggingWait->setVisible(false);

    connect(ui.LoginButton, SIGNAL(clicked()), this, SLOT(LoginButtonClicked()));
    connect(ui.RegisterButton, SIGNAL(clicked()), this, SLOT(RegisterButtonClicked()));
    connect(ui.LoginRegisterButton, SIGNAL(clicked()), this, SLOT(LoginRegisterButtonClicked()));
    connect(ui.RegisterBackButton, SIGNAL(clicked()), this, SLOT(RegisterBackButtonClicked()));
}

LoginForm::~LoginForm()
{

}

void LoginForm::ToggleWidget(QWidget* disabledForm, QWidget* enabledForm)
{
    disabledForm->setVisible(false);
    enabledForm->setVisible(true);
}

void LoginForm::RegisterUser()
{
    std::string user = ui.RegisterUsernameField->text().toStdString();
    std::string email = ui.RegisterEmailField->text().toStdString();
    std::string password = ui.RegisterPasswordField->text().toStdString();

    try
    {
        ValidateUserRegister(user, email, password);

        ToggleWidget(ui.RegisterForm, ui.RegistrationConfirmationForm);
        WaitForSeconds(3);
        ToggleWidget(ui.RegistrationConfirmationForm, ui.LoginForm);
    }
    catch (std::exception exception)
    {
        ui.RegisterErrorLabel->setText(exception.what());
    }
}

void LoginForm::LoginUser()
{
    std::string username = ui.LoginUsernameField->text().toStdString();
    std::string password = ui.LoginPasswordField->text().toStdString();

    try
    {
        ValidateUserLogin(username, password);

        cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/User_" + username });

        auto userInformation = crow::json::load(response.text);
        
        std::string email = userInformation["Email"].s();
        std::string imagePath = userInformation["Image path"].s();

        email = curl_unescape(email.c_str(), email.length());
        imagePath = curl_unescape(imagePath.c_str(), imagePath.length());

        Player user;
        user.SetName(username);
        user.SetPassword(password);
        user.SetEmail(email);
        user.SetImagePath(imagePath);


        ToggleWidget(ui.LoginForm, ui.LoggingWait);
        WaitForSeconds(1);

        MenuForm* menu = new MenuForm(std::move(user));
        menu->show();

        close();
    }
    catch (std::exception exception)
    {
        ui.LoginErrorLabel->setText(exception.what());
    }
}

void LoginForm::WaitForSeconds(int seconds)
{
    QTime delayTime = QTime::currentTime().addSecs(seconds);
    while (QTime::currentTime() < delayTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void LoginForm::CheckUser(const std::string & user)
{
    if (user == "")
    {
        throw std::exception("Username field can't be empty");
    }

    if (ui.RegisterForm->isVisible() == true)
    {
        if (std::find(user.begin(), user.end(), ' ') != user.end())
        {
            std::string suggestion = user;

            std::replace(suggestion.begin(), suggestion.end(), ' ', '_');
            suggestion = "Username can't contain any spaces\nTry: " + suggestion;

            throw std::exception(suggestion.c_str());
        }
    }
}

void LoginForm::CheckEmail(const std::string& email)
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

void LoginForm::CheckPassword(const std::string& password)
{
    if (password == "")
    {
        throw std::exception("Password field can't be empty");
    }

    if (ui.RegisterForm->isVisible() == true)
    {
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
}

void LoginForm::ValidateUserRegister(const std::string& user, const std::string& email, const std::string& password)
{
    CheckUser(user);
    CheckEmail(email);
    CheckPassword(password);

    cpr::Response registerRequest = cpr::Put(
        cpr::Url{ "http://localhost:18080/RegisterUser" },
        cpr::Payload
        {
            {"Username", user},
            {"Email", email},
            {"Password", password},
            {"Image path", " "}
        }
    );

    if (registerRequest.status_code != 200)
    {
        throw std::exception(registerRequest.text.c_str());
    }
}

void LoginForm::ValidateUserLogin(const std::string& user, const std::string& password)
{
    CheckUser(user);
    CheckPassword(password);

    cpr::Response loginRequest = cpr::Put(
        cpr::Url{ "http://localhost:18080/LoginUser" },
        cpr::Payload
        {
            {"Username", user},
            {"Password", password}
        }
    );

    if (loginRequest.status_code != 200)
    {
        throw std::exception(loginRequest.text.c_str());
    }
}
