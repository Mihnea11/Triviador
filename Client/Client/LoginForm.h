#pragma once
#include <QtWidgets/QMainWindow>
#include <curl/curl.h>
#include <cpr/cpr.h>
#include <algorithm>
#include <crow.h>
#include <regex>

#include "User.h"
#include "Utils.h"
#include "MenuForm.h"
#include "ui_LoginForm.h"

#define REGEX_STACK_COUNT 1000

class LoginForm : public QMainWindow
{
    Q_OBJECT

public:
    LoginForm(QWidget* parent = nullptr);
    ~LoginForm();

    void RegisterUser();
    void LoginUser();

private:
    Ui::LoginFormClass m_ui;

    void ToggleWidget(QWidget* disabledForm, QWidget* enabledForm);
    void WaitForSeconds(int seconds);
    void CheckUser(const std::string& user);
    void CheckEmail(const std::string& email);
    void CheckPassword(const std::string& password);
    void ValidateUserRegister(const std::string& user, const std::string& email, const std::string& password);
    void ValidateUserLogin(const std::string& user, const std::string& password);

private slots:
    void RegisterButtonClicked() { RegisterUser(); }
    void LoginButtonClicked() { LoginUser(); }
    void LoginRegisterButtonClicked() { ToggleWidget(m_ui.LoginForm, m_ui.RegisterForm); }
    void RegisterBackButtonClicked() { ToggleWidget(m_ui.RegisterForm, m_ui.LoginForm); }
};
