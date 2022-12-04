#include "LoginForm.h"
#include "MenuForm.h"
LoginForm::LoginForm(QWidget* parent): QMainWindow(parent)
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
    std::string confirmedPassword = ui.RegisterConfirmPassword->text().toStdString();

    try
    {
        ValidateUserRegister(user, email, password);

        cpr::Response response = cpr::Put(
            cpr::Url{ "http://localhost:18080/Users" },
            cpr::Payload
            {
                {"Id", user},
                {"Email", email},
                {"Password", password}
            }
        );

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
    std::string userName = ui.LoginUsernameField->text().toStdString();
    std::string password = ui.LoginPasswordField->text().toStdString();

    try
    {
        ValidateUserLogin(userName, password);

        MenuForm* menuForm = new MenuForm();
        menuForm->show();

        close();
    }
    catch (std::exception exception)
    {
        ui.LoginErrorLabel->setText(exception.what());
    }
}

void LoginForm::WaitForSeconds(int seconds)
{
}

void LoginForm::CheckUser(const std::string & user)
{
    if (user == "")
    {
        throw std::exception("Username field can't be empty");
    }

    cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/Users" });
    auto db_users = crow::json::load(response.text);
    for (const auto& db_user : db_users)
    {
        std::string userDecoded = db_user["Id"].s();
        userDecoded = curl_escape(userDecoded.c_str(), userDecoded.length());

        if (user == userDecoded)
        {
            throw std::exception("Username already used");
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

void LoginForm::ValidateUserRegister(const std::string& user, const std::string& email, const std::string& password)
{
    CheckUser(user);
    CheckEmail(email);
    CheckPassword(password);
}

void LoginForm::ValidateUserLogin(const std::string& user, const std::string& password)
{
    if (user == "")
    {
        throw std::exception("Username field can't be empty");
    }
    if (password == "")
    {
        throw std::exception("Password field can't be empty");
    }

    cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/Users" });
    auto db_users = crow::json::load(response.text);
    for (const auto& db_user : db_users)
    {
        std::string userDecoded = db_user["Id"].s();
        std::string passwordDecoded = db_user["Password"].s();
        
        passwordDecoded = curl_unescape(passwordDecoded.c_str(), passwordDecoded.length());
        userDecoded = curl_unescape(userDecoded.c_str(), userDecoded.length());

        if (user == userDecoded && password != passwordDecoded)
        {
            throw std::exception("Incorrect password");
        }

        if (user == userDecoded && password == passwordDecoded)
        {
            return;
        }
    }

    throw std::exception("Invalid username");
}
