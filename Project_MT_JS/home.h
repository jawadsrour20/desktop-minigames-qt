#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QtWidgets>
#include<string>
using namespace std;

/**
* \file home.h
* \brief Home class
*
* Home class contains the implementation that provides with a UI that
* shows the user the current date, their username, their set country name and flag,
* the user's profile photo. It displays guest and a default guest profile photo for
* guest users.
* allows the user to choose a game to play from 2 games,
* history page to view if they are not guest users, and the option to log out of their account
*/
class Home : public QWidget
{
    Q_OBJECT
public:

    // constructor
    explicit Home( QStringList* userObject = nullptr, QWidget *parent = nullptr);


private:

    QString playerName;//!< string of the player name
    QLabel* username; //!< pointer to the logged-in user name
    QLabel* profilePicture;//!< pointer to string of user profile picture url
    QLabel* currentDate;//!< pointer to current date string object
    QLabel* countryName;//!< pointer to country name
    QLabel* countryFlag;//!< pointer to country flag
    QPushButton* battleShipGame;//!< pointer to Battleship game button
    QPushButton* shootingDiscsGame;//!< pointer to Shooting Discs Game button
    QPushButton* history;//!< pointer to history page button
    QPushButton* logout;//!< pointer to logout button

    QStringList* loggedInUser;//!< pointer to loggedin user object

    QGridLayout* gridLayout;//!< pointer to GridLayout object for the home page
    void setGridLayout();
    void setColors();


signals:

private slots:

    void onPlayBattleshipGameClicked();
    void onPlayShootingDiscsGameClicked();
    void onHistoryClicked();
    void onLogoutClicked();
    void onGuestHistoryClicked();
};

#endif // HOME_H
