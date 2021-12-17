#ifndef BATTLESHIP_H
#define BATTLESHIP_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QMediaPlayer>
#include "playgame1.h"
#include "questionpopscreen.h"
#include "button.h"
#include "home.h"

/**
* \file Battleship.h
* \brief BattleShip class.
*
* This class inherits from QGraphicsView. It consists the view for our game.
*/

class BattleShip : public QGraphicsView{
    Q_OBJECT
public:
    //constructor
    BattleShip(QWidget* parent=NULL);

    // public methods
    void gameOver();

    // public attributes
    Home* returnTo; //!< this attribute saves the home page (the page that shows up after logging in) to be able to return to it after finishing the turn
    string playerName; //!< this is to know to which player we should add the score obtained
    PlayGame1*  scene; //!< this is the scene of the game
    questionPopScreen popQuestion; //!this is the pop-up screen for the questions
    int attempts=16; //!< number of attempts
    int score=0; //!< score


public slots:
    void returnHome();
    void startGame();
    void endPage();
    void displayMainMenu();
    void instructions();

};

#endif // BATTLESHIP_H
