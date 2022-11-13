#pragma once
#include <regex>
#include <QtWidgets/QMainWindow>
#include "ui_TriviadorGame.h"
#include <regex>

class TriviadorGame : public QMainWindow
{
    Q_OBJECT

private:
    Ui::TriviadorGameClass ui;

    void RegisterUser();
    void LoginUser();
public:
    TriviadorGame(QWidget *parent = nullptr);
    bool emailCheck(std::string email)
    {
        const std::regex emailPattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
        return std::regex_match(email, emailPattern); ///returns true is match exists
    }
    bool passWordCheck(std::string passWord)
    {
        const std::regex passWordPattern("(? = .*[A - z\d] + )(? = .*[A - z@!? ] + )(? = .*[a - z\d@!? ] + )(? = .*[A - Z\d@!? ] + )[A - z\d@!? ]{8,}");
        return std::regex_match(passWord, passWordPattern);
    }
    bool ValidateInput(std::string user, std::string password)
    {
        if (!emailCheck(user) || !passWordCheck(password)) return false;
        return true;
    }
    ~TriviadorGame();

private slots:
    void RegisterButtonClicked() { RegisterUser(); }
    void LoginButtonClicked() { LoginUser(); }
};
