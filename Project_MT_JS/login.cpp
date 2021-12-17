#include "login.h"
#include "register.h"
#include "home.h"
#include <iostream>
#include <regex>
#include <fstream>
#include <stdio.h>
#include <QDebug>
using namespace std;


/**
 * \file login.cpp
 * \brief contains Login class definition
 *
 * Login class provides the users with the ability to login to their accounts,
 * register for an account if they don't have one, or log-in as guest users
 */
Login::Login(QWidget *parent) :
    QWidget(parent)
{

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-this->width()) / 2;
    int y = (screenGeometry.height()-this->height()) / 2;
    this->move(x, y);


    this->setStyleSheet("background-color:#363945;");
    rocketPicture = new QLabel();
    rocketPicture->setPixmap(QPixmap(":/users_images/rocket.png").scaled(150, 150));
    username = new QLabel("Username:");
    password = new QLabel("Password:");
    usernameField  = new QLineEdit();
    passwordField = new QLineEdit();
    this->passwordField->setEchoMode(QLineEdit::Password);
    loginButton = new QPushButton("Login");
    registerButton = new QPushButton("Register");
    playAsGuestButton = new QPushButton("Play as Guest");
    gridLayout = new QGridLayout();

    setColors();
    setGridLayout();

    QObject::connect(loginButton, SIGNAL(clicked(bool)), this, SLOT(onLoginClicked()));
    QObject::connect(registerButton, SIGNAL(clicked(bool)), this, SLOT(onRegisterClicked()));
    QObject::connect(playAsGuestButton, SIGNAL(clicked(bool)), this, SLOT(onPlayAsGuestClicked()));

}



// Methods
/**
 * \brief Sets the GridLayout for the login-page
 */
void Login::setGridLayout()
{
    gridLayout->addWidget(rocketPicture, 0, 1);
    gridLayout->addWidget(username, 1, 0);
    gridLayout->addWidget(password, 2, 0);
    gridLayout->addWidget(usernameField, 1, 1);
    gridLayout->addWidget(passwordField, 2, 1);
    gridLayout->addWidget(loginButton, 3, 1);
    gridLayout->addWidget(registerButton, 4, 1);
    gridLayout->addWidget(playAsGuestButton, 5, 1);
    gridLayout->addItem(new QSpacerItem(100, 10), 0, 2);
    setLayout(gridLayout);

}

/**
 * \brief Sets the colors for the login-page
 */
void Login::setColors()
{
    username->setStyleSheet("color: #F0EDE5;");
    password->setStyleSheet("color:#F0EDE5;");
    usernameField->setStyleSheet("background-color:#F0EDE5;color:#363945;");
    passwordField->setStyleSheet("background-color:#F0EDE5;color:#363945;");
    loginButton->setStyleSheet("color:#F0EDE5; border-radius:12px;padding:6px;"
      "font-size:16px; background-color:orange;");
    registerButton->setStyleSheet("color:#F0EDE5;border-radius:12px;"
        "padding:6px;""font-size:16px; background-color:orange;");
    playAsGuestButton->setStyleSheet("color:#F0EDE5;border-radius:12px;"
        "padding:6px;font-size:16px; background-color:orange;");

}


// ----------------------------------------------------------------
// ----------------------------------------------------------------


// SLOTS
/**
 * \brief Responds to a click on the Login button and navigates user to the homepage
 * if the login was successful, otherwise displays an error message describing the error
 */
void Login::onLoginClicked()
{
    //QFile* usersFile = new QFile("/Users/jawadsrour/Dropbox/My Mac (Jawads-M1-Macbook-Pro.local)/Desktop/EECE435L/Project/EECE435LProject/users.txt");
    QFile* usersFile = new QFile(":/users.txt");
     // check username is unique ( does not exist in stored user objects)
    usersFile->open(QIODevice::ReadOnly|QIODevice::Text);

    QTextStream in(usersFile);

    bool isAuthenticated = false;
    QStringList* userObjectPtr;
    while (!in.atEnd()) {
        QString tempUserString = in.readLine(); // 1 line == 1 record == 1 user
        QStringList tempUserList = tempUserString.split(" ");

        if (tempUserList[0] == usernameField->text() && tempUserList[1] == passwordField->text())
        {
           isAuthenticated = true;
           userObjectPtr = new QStringList(tempUserList);
           Home* homePage = new Home(userObjectPtr);
           homePage->show();
           this->hide();
        }
    }


// if user is not authenticated, display message box

    if(!isAuthenticated)
    {
        QMessageBox msgBox;
        // c_str method is used to convert a std::string to QString if needed
        msgBox.setText("Username or Password is incorrect!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }


    usersFile->close();
}

/**
 * \brief Responds to a click on the Register button and navigates user to the registration page
 */
void Login::onRegisterClicked()
{
    // must be a pointer since if we stack allocate the allocated memory address gets de-allocated once out of scope
    Register* registrationPage = new Register();
    registrationPage->show();
    this->hide();//this will disappear main window
}

/**
 * \brief Responds to a click on the Play as Guest button and navigates
 * user to the home page as a guest user
 */
void Login::onPlayAsGuestClicked()
{
    Home* homePage = new Home();
    homePage->show();
    this->hide();

}
