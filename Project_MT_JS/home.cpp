#include "home.h"
#include "login.h"
#include "history.h"
#include <iostream>
#include <regex>
#include <fstream>
#include <stdio.h>
#include <QDebug>
#include "battleship.h"
#include "shootingdiscs.h"

BattleShip* game;

/**
 * \file home.cpp
 * \brief contains Home class definition
 *
 * Home class contains the implementation that provides with a UI that
 * shows the user the current date, their username, their set country name and flag,
 * the user's profile photo. It displays guest and a default guest profile photo for
 * guest users.
 * allows the user to choose a game to play from 2 games,
 * history page to view if they are not guest users, and the option to log out of their account
 */
Home::Home( QStringList* userObject, QWidget *parent) : QWidget(parent)
{
    //guest
    if (userObject == nullptr){

        this->setStyleSheet("background-color:#363945;");
        username = new QLabel("Welcome Guest!");
        this->playerName="guest";
        profilePicture = new QLabel();
        profilePicture->setPixmap(QPixmap(":/users_images/guest.png").scaled(150, 150));

        currentDate = new QLabel(QDate::currentDate().toString());
        countryName = new QLabel("United Kingdom");
        countryFlag = new QLabel(); //image
        countryFlag->setPixmap(QPixmap(":/users_images/uk.png").scaled(50, 50));
        battleShipGame = new QPushButton("Play Battleship");
        shootingDiscsGame = new QPushButton("Play Shooting Discs");
        history = new QPushButton("History");
        logout = new QPushButton("Logout");

        gridLayout = new QGridLayout();

        setGridLayout();
        setColors();

        QObject::connect(battleShipGame, SIGNAL(clicked(bool)), this, SLOT(onPlayBattleshipGameClicked()));
        QObject::connect(shootingDiscsGame, SIGNAL(clicked(bool)), this, SLOT(onPlayShootingDiscsGameClicked()));
        QObject::connect(history, SIGNAL(clicked(bool)), this, SLOT(onGuestHistoryClicked()));
        QObject::connect(logout, SIGNAL(clicked(bool)), this, SLOT(onLogoutClicked()));
    }

    else{

        loggedInUser = userObject;

        this->setStyleSheet("background-color:#363945;");
        QString tempUserName = (*userObject)[0] + "!";
        username = new QLabel("Welcome " + tempUserName);
        this->playerName = tempUserName;

        profilePicture = new QLabel();
        QString tempProfilePictureName = (*userObject)[8];
        QString tempProfilePictureDirectory = ":/users_images/" + tempProfilePictureName;
        profilePicture->setPixmap(QPixmap(tempProfilePictureDirectory).scaled(150, 150));

        currentDate = new QLabel(QDate::currentDate().toString());

        QString tempCountryCode = (*userObject)[7];
        QString tempCountryName;
        QString tempFlagDirectory = ":/users_images/";
        if (tempCountryCode == "+961")
        {
            tempCountryName = "Lebanon";
            tempFlagDirectory += "LB.png";
        }
        else if (tempCountryCode == "+964")
        {
            tempCountryName = "Iraq";
            tempFlagDirectory += "iraq.png";
        }
        else if (tempCountryCode == "+971")
        {
            tempCountryName = "UAE";
            tempFlagDirectory += "UAE.png";
        }
        else if (tempCountryCode == "+81")
        {
            tempCountryName = "Japan";
            tempFlagDirectory += "JP.png";
        }
        else if (tempCountryCode == "+1")
        {
            tempCountryName = "Canada";
            tempFlagDirectory += "CA.png";
        }
        else
        {
            tempCountryName = "UK";
            tempFlagDirectory += "uk.png";
        }


        countryName = new QLabel(tempCountryName);
        countryFlag = new QLabel(); //image
        countryFlag->setPixmap(QPixmap(tempFlagDirectory).scaled(50, 50));
        battleShipGame = new QPushButton("Play Battleship");
        shootingDiscsGame = new QPushButton("Play Shooting Discs");
        history = new QPushButton("History");
        logout = new QPushButton("Logout");

        gridLayout = new QGridLayout();

        setGridLayout();
        setColors();

        QObject::connect(battleShipGame, SIGNAL(clicked(bool)), this, SLOT(onPlayBattleshipGameClicked()));
        QObject::connect(shootingDiscsGame, SIGNAL(clicked(bool)), this, SLOT(onPlayShootingDiscsGameClicked()));
        QObject::connect(history, SIGNAL(clicked(bool)), this, SLOT(onHistoryClicked()));
        QObject::connect(logout, SIGNAL(clicked(bool)), this, SLOT(onLogoutClicked()));
    }
}


// Methods

/**
 * \brief Sets the GridLayout for the home-page
 */
void Home::setGridLayout()
{
    gridLayout->addWidget(username, 2, 0);
    gridLayout->addWidget(profilePicture, 4, 1);
    gridLayout->addWidget(currentDate, 0, 2);
    gridLayout->addWidget(countryName, 0, 0);
    gridLayout->addWidget(countryFlag, 1, 0);
    gridLayout->addWidget(battleShipGame, 5, 1);
    gridLayout->addWidget(shootingDiscsGame, 6, 1);
    gridLayout->addWidget(history, 7, 1);
    gridLayout->addWidget(logout, 8, 1);
    setLayout(gridLayout);

}
/**
 * \brief Sets the colors for the home-page
 */
void Home::setColors()
{
    username->setStyleSheet("color: #F0EDE5;");
    currentDate->setStyleSheet("color: #F0EDE5;");
    countryName->setStyleSheet("color: #F0EDE5;");

    profilePicture->setStyleSheet("border-radius:50%;");
    battleShipGame->setStyleSheet("color:#F0EDE5;border-radius:12px;"
        "padding:6px;""font-size:16px; background-color:orange;");
    shootingDiscsGame->setStyleSheet("color:#F0EDE5;border-radius:12px;"
        "padding:6px;""font-size:16px; background-color:orange;");
    history->setStyleSheet("color:#F0EDE5;border-radius:12px;"
        "padding:6px;""font-size:16px; background-color:orange;");
    logout->setStyleSheet("color:#F0EDE5;border-radius:12px;"
        "padding:6px;""font-size:16px; background-color:orange;");

}

// ------------------------------
// ------------------------------

// SLOTS

/**
 * \brief responds to a button clicked signal and navigates the user to the BattleShip game
 */
void Home::onPlayBattleshipGameClicked() {

    game = new BattleShip();
    game->show();
    game->displayMainMenu();
    game->returnTo=this;

    QString player;
    for (int i=0;i<playerName.length()-1;i++)
        player[i]=playerName[i];

    game->playerName=player.toStdString();
    this->hide();
}

/**
 * \brief responds to a button clicked signal and navigates the user to the Shooting Discs game
 */
void Home::onPlayShootingDiscsGameClicked() {


    ShootingDiscs* shootingDiscsGame;
    if (this->playerName != "guest")
    {
        QString* tempLoggedInUser = new QString((*loggedInUser)[0]);
        shootingDiscsGame = new ShootingDiscs(tempLoggedInUser, loggedInUser);
    }
    else
        shootingDiscsGame = new ShootingDiscs();

    shootingDiscsGame->show();
    this->hide();
}

/**
 * \brief responds to a button clicked signal and navigates the user to the History page
 */
void Home::onHistoryClicked() {

    QString* tempLoggedInUser = new QString((*loggedInUser)[0]);
    History* historyPage = new History(tempLoggedInUser, loggedInUser);
    historyPage->show();
    this->hide();

}

/**
 * \brief Logs the user out of their account
 */
void Home::onLogoutClicked() {
    Login* loginPage = new Login();
    loginPage->show();
    this->hide();
}

/**
 * \brief responds to a history button clicked signalfor a guest user and displays a message for them
 */
void Home::onGuestHistoryClicked() {
    QMessageBox msgBox;
    // c_str method is used to convert a std::string to QString if needed
    msgBox.setText("You are not a registered User!");
    msgBox.setInformativeText("Please sign-in to view scores history.");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}
