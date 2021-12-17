#include <QApplication>
#include "battleship.h"
#include<fstream>
#include<string>
#include<iostream>
#include "login.h"
#include "register.h"
#include "home.h"
#include "shootingdiscs.h"

//BattleShip* game;

/**
 * \mainpage JawadSrour_MariamTermos_EECE435L_Project
 * \author Jawad Srour
 * \author Mariam Termos
 * \date 11-27-2021
 */
int main(int argc, char **argv){

    QApplication app (argc, argv);



    Login loginPage;
    loginPage.show();

    return app.exec();

}
