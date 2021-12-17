#include "register.h"
#include "login.h"
#include "home.h"
#include <iostream>
#include <regex>
#include <fstream>
#include <stdio.h>
#include <QDebug>
using namespace std;
/**
 * \file register.cpp
 * \brief contains Register class definition
 *
 * Provides user with capability to register for an account
 */
Register::Register(QWidget *parent) : QWidget(parent)
{

    this->setStyleSheet("background-color:#363945;");
    rocketPicture = new QLabel();
    rocketPicture->setPixmap(QPixmap(":/users_images/rocket.png").scaled(150, 150));
    username = new QLabel("Username:");
    password = new QLabel("Password:");
    firstName = new QLabel("First Name:");
    lastName = new QLabel("Last Name:");
    profilePicture = new QLabel("Profile Picture: ");
    phoneNumber = new QLabel("Phone Number:");
    usernameField = new QLineEdit();
    usernameField->setPlaceholderText("user1");
    passwordField = new QLineEdit();
    this->passwordField->setEchoMode(QLineEdit::Password);
    passwordField->setPlaceholderText("*******");
    firstNameField = new QLineEdit();
    firstNameField->setPlaceholderText("John");
    lastNameField = new QLineEdit();
    lastNameField->setPlaceholderText("Smith");
    profilePictureField = new QLineEdit();
    profilePictureField->setPlaceholderText("guest.png");
    phoneNumberField = new QLineEdit();
    phoneNumberField->setPlaceholderText("+961-70100200");
    birthDateLabel = new QLabel("Birthdate:");
    birthDate = new QDateEdit();
    birthDate->setDate(QDate::currentDate());

    gender = new QLabel("Gender:");
    genderComboBox = new QComboBox();
    genderComboBox->addItem("Male");
    genderComboBox->addItem("Female");
    backButton = new QPushButton("Back");
    registerButton = new QPushButton("Register");
    gridLayout = new QGridLayout();


    setGridLayout();
    setColors();

    QObject::connect(registerButton, SIGNAL(clicked(bool)), this, SLOT(onRegisterClicked()));
    QObject::connect(backButton, SIGNAL(clicked(bool)), this, SLOT(onBackClicked()));
}

// Methods
/**
 * \brief Sets the GridLayout for the registration page
 */
void Register::setGridLayout()
{
    gridLayout->addWidget(rocketPicture, 0, 1);
    gridLayout->addWidget(username, 1, 0);
    gridLayout->addWidget(password, 2, 0);
    gridLayout->addWidget(usernameField, 1, 1);
    gridLayout->addWidget(passwordField, 2, 1);
    gridLayout->addWidget(firstName, 3, 0);
    gridLayout->addWidget(firstNameField, 3, 1);
    gridLayout->addWidget(lastName, 4, 0);
    gridLayout->addWidget(lastNameField, 4, 1);
    gridLayout->addWidget(gender, 5, 0);
    gridLayout->addWidget(genderComboBox, 5, 1);
    gridLayout->addWidget(birthDate, 6, 1);
    gridLayout->addWidget(birthDateLabel, 6, 0);
    gridLayout->addWidget(phoneNumber, 7, 0);
    gridLayout->addWidget(phoneNumberField, 7, 1);
    gridLayout->addWidget(profilePicture, 8, 0);
    gridLayout->addWidget(profilePictureField, 8, 1);
    gridLayout->addWidget(registerButton, 10, 2);
    gridLayout->addWidget(backButton, 10, 0);
    gridLayout->addItem(new QSpacerItem(100, 10), 0, 2);
    setLayout(gridLayout);

}
/**
 * \brief Sets the colors for the registration page
 */
void Register::setColors()
{
    username->setStyleSheet("color: #F0EDE5;");
    password->setStyleSheet("color:#F0EDE5;");
    firstName->setStyleSheet("color:#F0EDE5;");
    lastName->setStyleSheet("color:#F0EDE5;");
    gender->setStyleSheet("color:#F0EDE5");
    birthDateLabel->setStyleSheet("color:#F0EDE5");
    phoneNumber->setStyleSheet("color:#F0EDE5");
    profilePicture->setStyleSheet("color:#F0EDE5");

    usernameField->setStyleSheet("background-color:#F0EDE5;color:#363945;border-radius:4px;");
    passwordField->setStyleSheet("background-color:#F0EDE5;color:#363945;border-radius:4px;");
    firstNameField->setStyleSheet("background-color:#F0EDE5;color:#363945;border-radius:4px;");
    genderComboBox->setStyleSheet("background-color:#F0EDE5;color:black;border-radius:4px;"
        "border-color: rgba(255,255,255,200);border-width: 1px;border-style: solid;");
    birthDate->setStyleSheet("background-color:#F0EDE5;color:#363945;");
    lastNameField->setStyleSheet("background-color:#F0EDE5;color:#363945;border-radius:4px;");
    phoneNumberField->setStyleSheet("background-color:#F0EDE5;color:#363945;border-radius:4px;");
    profilePictureField->setStyleSheet("background-color:#F0EDE5;color:#363945;border-radius:4px;");
    registerButton->setStyleSheet("color:#F0EDE5;border-radius:12px;"
        "padding:6px;""font-size:16px; background-color:orange;");
    backButton->setStyleSheet("color:#F0EDE5;border-radius:12px;"
        "padding:6px;""font-size:16px; background-color:orange;");

}


// ----------------------------------------------------------------
// ----------------------------------------------------------------

// SLOTS
/**
 * \brief Responds to a click on the Reigster button and validates the provided information
 * If the provided information does not satisfy set coniditions, it displays a message to the user
 * asking to change the information causing the registration error
 */
void Register::onRegisterClicked()
{
    // regular expression that checks for required password conditions
    // password should consist of at least 8 characters and contain at least one number, upper and lower case letters
    const std::regex passwordValidation("^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9]).{8,}$");
    const std::string phoneNumberDelimiter = "-";
    std::string inputPhoneCountryCode = phoneNumberField->text().toStdString().substr(0, phoneNumberField->text().toStdString().find(phoneNumberDelimiter));


    if (usernameField->text() == "" || passwordField->text() == "" || firstNameField->text() == ""
            || lastNameField->text() == "" || phoneNumberField->text() == "")
    {
        QMessageBox msgBox;
        msgBox.setText("Please fill all of the required fields to register!");
        msgBox.setInformativeText("You can only leave the profile picture empty");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }

    else if(! std::regex_match(passwordField->text().toStdString(), passwordValidation) )
    {
        QMessageBox msgBox;
        msgBox.setText("Password Conditions Not Satisfied!");
        msgBox.setInformativeText("Password should contain at least 8 charatcers, 1 number, upper and lower case letters");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }


    else if (inputPhoneCountryCode != "+961" && inputPhoneCountryCode != "+964" && inputPhoneCountryCode != "+971"
             && inputPhoneCountryCode != "+81" && inputPhoneCountryCode != "+1")
    {
        QMessageBox msgBox;
        // c_str method is used to convert a std::string to QString if needed
        msgBox.setText("Invalid Phone Number Provided!");
        msgBox.setInformativeText("Make sure you input the correct country code!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }

    else {

//        QFile* usersFile = new QFile("/Users/jawadsrour/Project_MT_JS/users.txt");
                QFile* usersFile = new QFile(":/users.txt");
        bool isExistingUser = false;
        // check username is unique ( does not exist in stored user objects)
        usersFile->open(QIODevice::ReadOnly|QIODevice::Text);

        QTextStream in(usersFile);

        while (!in.atEnd()) {
            QString tempUserString = in.readLine(); // 1 line == 1 record == 1 user
            QStringList tempUserList = tempUserString.split(" ");
            if (tempUserList[0] == usernameField->text())
            {
                isExistingUser = true;
                QMessageBox msgBox;
                // c_str method is used to convert a std::string to QString if needed
                msgBox.setText("Username Already Exists!");
                msgBox.setInformativeText("Please try another username.");
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.setDefaultButton(QMessageBox::Ok);
                msgBox.exec();
            }
        }

        usersFile->close();

        // register user successfully. Add user object to users JSON

        if (! isExistingUser){
            usersFile->open(QIODevice::Append|QIODevice::Text);

            QTextStream out(usersFile);

            QString tempUser = usernameField->text();
            QString tempPassword = passwordField->text();
            QString tempFirstName = firstNameField->text();
            QString tempLastName = lastNameField->text();
            QString tempGender = genderComboBox->currentText();
            QString tempBirthDate = birthDate->text();
            QString tempPhoneNumber = phoneNumberField->text();
            QString tempPhoneCountryCode = inputPhoneCountryCode.c_str();
            QString tempProfilePicture = profilePictureField->text();

            if (tempProfilePicture == "")
                tempProfilePicture = "guest.png";

            out << tempUser << " " << tempPassword << " " << tempFirstName << " " << tempLastName <<
                   " " << tempGender << " " << tempBirthDate << " " << tempPhoneNumber << " " << tempPhoneCountryCode
                << " " << tempProfilePicture;
            //out << Qt::endl; gives error
            out << endl; //TODO


            usersFile->close();

//            QFile* battleshipScoresFile = new QFile("/Users/jawadsrour/Project_MT_JS/battleship_scores.txt");
               QFile* battleshipScoresFile = new QFile(":/battleship_scores.txt");
            battleshipScoresFile->open(QIODevice::Append|QIODevice::Text);
            QTextStream outBattleshipScoresFile(battleshipScoresFile);

            outBattleshipScoresFile << tempUser << " "  << "0";
            outBattleshipScoresFile << endl; //TODO
            battleshipScoresFile->close();

//            QFile* shootingScoresFile = new QFile("/Users/jawadsrour/Project_MT_JS/shooting_scores.txt");

                        QFile* shootingScoresFile = new QFile(":/shooting_scores.txt");
            shootingScoresFile->open(QIODevice::Append|QIODevice::Text);
            QTextStream outShootingScoresFile(shootingScoresFile);

            outShootingScoresFile << tempUser << " " << "0";
            outShootingScoresFile << endl; //TODO
            shootingScoresFile->close();

            qDebug() << "User added successfully!";


            usersFile->open(QIODevice::ReadOnly|QIODevice::Text);

            QTextStream in(usersFile);
            QStringList* userObjectPtr;
            while (!in.atEnd()) {
                QString tempUserString = in.readLine(); // 1 line == 1 record == 1 user
                QStringList tempUserList = tempUserString.split(" ");

                if (tempUserList[0] == tempUser && tempUserList[1] == tempPassword)
                {

                    userObjectPtr = new QStringList(tempUserList);
                    Home* homePage = new Home(userObjectPtr);
                    homePage->show();
                    this->hide();
                }

            }
        }
    }


}
/**
 * \brief Responds to a click on the Back button and navigates
 * user back to the main login page
 */
void Register::onBackClicked()
{
    Login* loginPage = new Login();
    loginPage->show();
    this->hide();
}

