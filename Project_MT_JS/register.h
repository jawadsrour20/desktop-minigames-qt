#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QtWidgets>

/**
* \file register.h
* \brief Register class.
* Provides user with capability to register for an account
*
*/
class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);

private:


    QLabel* rocketPicture;//!< pointer to rocket picture
    QLabel* username;//!< pointer to user name label
    QLabel* password;//!< pointer to password label
    QLabel* firstName;//!< pointer to first name label
    QLabel* lastName;//!< poniter to lat name label
    QLabel* profilePicture;//!< pointer to profile picture label
    QLabel* phoneNumber;//!< pointer to phone number label
    QLabel* birthDateLabel;//!< pointer to birth date label
    QLabel* gender;//!< pointer to gender label
    QLineEdit* usernameField;//!< pointer to input user name field
    QLineEdit* passwordField;//!< pointer to input password field
    QLineEdit* firstNameField;//!< pointer to input first name field
    QLineEdit* lastNameField;//!< pointer to input last name field
    QLineEdit* profilePictureField;//!< pointer to input profile picture field
    QLineEdit* phoneNumberField;//!< pointer to input phone number field
    QDateEdit* birthDate;//!< pointer to input birth date field
    QComboBox* genderComboBox; //!< pointer to gender combo box
    QPushButton* backButton;//!< pointer to back button
    QPushButton* registerButton;//!< pointer to register button
    QGridLayout* gridLayout;//!< pointer to GridLayout object
    void setGridLayout();
    void setColors();

signals:

private slots:
    void onRegisterClicked();
    void onBackClicked();
};

#endif // REGISTER_H
