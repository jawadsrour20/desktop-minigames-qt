/**
* \file GrideSquare.cpp
* \brief this is the implemetation of the squares
*
This class implements the characteristiques of the squares that forms the grids in the game.
*
* \author Mariam Termos
*/

#include "gridesquare.h"
#include "battleship.h"

extern BattleShip* game;

/**
 * \file gridesquare.cpp
* \brief Constructor of the class, initialize the attributes of the square in the grid
* \param no input argument
* \return no return value
*/
GrideSquare::GrideSquare(QGraphicsItem *parent): QGraphicsRectItem(parent) {

    setRect(0,0,50,50);

    missOrHit = new QGraphicsPixmapItem();

    missOrHit->hide();

    fireReady = new QGraphicsPixmapItem();
    fireReady-> setPixmap( (QPixmap(":/images/fire.png")).scaled(50,50));
    game->scene->addItem(fireReady);
    fireReady->hide();

    setAcceptHoverEvents(true);

    music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/explotion.mp3"));

}

/**
* \brief Responds to mouse clicks, if the square contains a ship pop-up question will appear. Number of attempts is deacresed in both cases. When attempts are 0, the function calls gameOver function from Battleship class
* \param event, which is the mourse click on the square
* \return no return value
*/
void GrideSquare::mousePressEvent(QGraphicsSceneMouseEvent *event){

    if(game->attempts>0){

        //can only select square inside of enemy grid, and those who where not fired before
        if(this->used==0 && this->x()>=600 && this->x()<=750 && this->y()>=150 && this->y()<=300){

            if(this->flag==1){   //flag=1 means that there is a ship in the square

                game->popQuestion.prepareScreen(this); //call pop-up question
                game->hide();                          //hide current window

            }

            if (this->flag==0){  //no ship in the square, thus a miss
                music->play();   //play sound of firing
                this->missOrHit->show();  //show the image of the miss
            }

            used=1;  //cell used, cannot attack same cell again

            //when attempts are 0, show all enemy ships and call gameOver function from the Battelship class
            game->attempts--;
            game->scene->updateAttempts();
            if (game->attempts==0){
                    game->scene->smallShip1->show();
                    game->scene->smallShip2->show();
                    game->scene->smallShip3->show();
                    game->scene->mediumShip->show();
                    game->scene->mediumShip2->show();
                    game->scene->bigShip->show();
                    game->gameOver();
            }
       }
    }
}

/**
* \brief shows an aiming image on the square when a hovering in event occurs
* \param event, which is the hovering of the mourse over the button
* \return no return value
*/
void GrideSquare::hoverEnterEvent(QGraphicsSceneHoverEvent *event){

    if(game->attempts>0){
        fireReady->setPos(this->x(),this->y());
        fireReady->show();
    }

}

/**
* \brief removes aiming image from the square when a hovering out event occurs
* \param event, which is the hovering of the mourse away from the button
* \return no return value
*/
void GrideSquare::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){

    fireReady->hide();

}

