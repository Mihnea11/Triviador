#pragma once
#include <regex>
#include <fstream>
#include <QTime>
#include <QtWidgets/QMainWindow>

#include "ui_TriviadorGame.h"
#include "GameWindow.h"
#include "Player.h"

#define _REGEX_MAX_STACK_COUNT 1000

class TriviadorGame : public QMainWindow
{
    Q_OBJECT

private:
    Ui::TriviadorGameClass ui;
    
    void RegisterUser();
    void LoginUser();
    void ToggleForm(QWidget* disabledForm, QWidget* enabledForm);
    void WaitForSeconds(int seconds);

public:
    TriviadorGame(QWidget *parent = nullptr);
    ~TriviadorGame();

    void CheckUser(const std::string& user);
    void CheckEmail(const std::string& email);
    void CheckPassword(const std::string& password);
    void CheckLoginCredentials(const std::string& userName, const std::string& password);

    void SaveUserDetails(const std::string& userName, const std::string& userEmail, const std::string& userPassword);
    
private slots:
    void RegisterButtonClicked() { RegisterUser(); }
    void LoginButtonClicked() { LoginUser(); }
    void LoginRegisterButtonClicked() { ToggleForm(ui.LoginForm, ui.RegisterForm); }
    void RegisterBackButtonClicked() { ToggleForm(ui.RegisterForm, ui.LoginForm); }
};
