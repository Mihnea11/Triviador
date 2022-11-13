#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TriviadorGame.h"

class TriviadorGame : public QMainWindow
{
    Q_OBJECT

private:
    Ui::TriviadorGameClass ui;

    void RegisterUser();
    void LoginUser();
public:
    TriviadorGame(QWidget *parent = nullptr);
    ~TriviadorGame();

private slots:
    void RegisterButtonClicked() { RegisterUser(); }
    void LoginButtonClicked() { LoginUser(); }
};
