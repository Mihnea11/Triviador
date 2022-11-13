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
    bool emailCheck(std::string email);
    bool passwordCheck(std::string password);
    bool ValidateInput(std::string user, std::string password);
    ~TriviadorGame();

private slots:
    void RegisterButtonClicked() { RegisterUser(); }
};
