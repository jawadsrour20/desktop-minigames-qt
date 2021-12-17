#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QtWidgets>

/**
* \file login.h
* \brief Login class
*
* Login class provides the users with the ability to login to their accounts,
* register for an account if they don't have one, or log-in as guest users
*/
class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);


private:

    QLabel* rocketPicture;//!< pointer to rocket picture url string
    QLabel* username;//!< pointer to user name label
    QLabel* password;//!< pointer to password label
    QLineEdit* usernameField;//!< pointer to input user name field
    QLineEdit* passwordField;//!< pointer to input password field
    QPushButton* loginButton;//!< pointer to login button
    QPushButton* registerButton;//!< pointer to register button
    QPushButton* playAsGuestButton;//!< pointer to play as guest button
    QGridLayout* gridLayout;//!< pointer to grid layout object
    void setGridLayout();
    void setColors();

signals:

// slots must be defined under the slots keyword
private slots:

    void onLoginClicked();
    void onRegisterClicked();
    void onPlayAsGuestClicked();


};

#endif // LOGIN_H
