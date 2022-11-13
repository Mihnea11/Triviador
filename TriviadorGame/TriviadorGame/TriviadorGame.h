#pragma once
#include <regex>
#include <QtWidgets/QMainWindow>
#include "ui_TriviadorGame.h"
#include <fstream>
#include "Player.h"

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
    bool EmailCheck(std::string email);
    bool PasswordCheck(std::string password);
    bool ValidateInput(std::string user, std::string password);
    void SaveUserDetails(std::string userName, std::string userEmail, std::string userPassword);
    ~TriviadorGame();

private slots:
    void RegisterButtonClicked() { RegisterUser(); }
    void LoginButtonClicked() { LoginUser(); }
    void ChangeFormClicked() { ChangeForm(); }
};
