#ifndef PLAYGAME1_H
#define PLAYGAME1_H

#include <QWidget>
#include <QString>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>
#include <random>
#include <QList>
#include <QMediaPlayer>
#include"gridesquare.h"

using namespace  std;

/**
* \file PlayGame1.h
* \brief PlayGame1 class.
*
* This class inherits from QGraphicsScene. It consists the scene for our game.
* It holds all the attributes that we need to build the scene of our game.
*/

class PlayGame1 :  public QGraphicsScene {

public:
    //constructor
    PlayGame1();

    //functions
    void drawGrid();
    void addPlayerShips();
    void addEnemyShips();
    void addFlags();
    void enemyAttack();
    void displayScore();
    void displayAttempts();
    void updateScore();
    void updateAttempts();

    //attributes
    QGraphicsPixmapItem *bigShip;  //!these are all the enemy ships, they are set as attributes because we need to access them in other functions
    QGraphicsPixmapItem *mediumShip;
    QGraphicsPixmapItem *mediumShip2;
    QGraphicsPixmapItem *smallShip1;
    QGraphicsPixmapItem *smallShip2;
    QGraphicsPixmapItem *smallShip3;

private:
    //private attributes

    QList<GrideSquare*> enemySquares; //!this list contains all the squares that form the enemy grid
    QList<GrideSquare*> playerSquares; //!this list contains all the squares that form the player grid
    QGraphicsTextItem* scoreText; //!this text contains the word "score" that will be added to the scene, we need it as an attributes because it is needed in more than one function
    QGraphicsTextItem* scoreValue; //!this text contains the values of the score and will be updated and added to the scene, we need it as an attributes because it is needed in more than one function
    QGraphicsTextItem* attemptsText; //!this text contains the word "attempts" that will be added to the scene, we need it as an attributes because it is needed in more than one function
    QGraphicsTextItem* attemptsValue; //!this text contains the values of the attempts and will be updated and added to the scene, we need it as an attributes because it is needed in more than one function
    QMediaPlayer* music; //!media player containing the music file of the explotion

};

#endif // PLAYGAME1_H
