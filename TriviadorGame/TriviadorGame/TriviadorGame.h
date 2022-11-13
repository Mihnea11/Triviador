#pragma once
#include <regex>
#include <QtWidgets/QMainWindow>
#include "ui_TriviadorGame.h"
#include <fstream>
#include "Player.h"

#define _REGEX_MAX_STACK_COUNT 1000

class TriviadorGame : public QMainWindow
{
    Q_OBJECT

private:
    Ui::TriviadorGameClass ui;
    bool enableLoginForm;
    
    void RegisterUser();
    void LoginUser();
    void ChangeForm();

public:
    TriviadorGame(QWidget *parent = nullptr);
    ~TriviadorGame();

    void CheckUser(std::string user);
    void CheckEmail(std::string email);
    void CheckPassword(std::string password);
    void CheckLoginCredentials(std::string userName, std::string passWord);

    void SaveUserDetails(std::string userName, std::string userEmail, std::string userPassword);

private slots:
    void RegisterButtonClicked() { RegisterUser(); }
    void LoginButtonClicked() { LoginUser(); }
    void ChangeFormClicked() { ChangeForm(); }
};
