/**
* \file PlayGame1.cpp
* \brief this is the implemetation of the scene of the game
*
This class implemets the different functions of the scene. it is mainly
responsable of the preparing the gadgets of the game: adding squares to form the grid,
adding ships, adding flags, in addition to displaying the score and number of attempts.
*
* \author Mariam Termos
*/

#include "playgame1.h"
#include "battleship.h"

extern BattleShip* game;

/**
* \file playgame1.cpp
* \brief Constructor, initialize attributes of the scene
* \param no input arguments
* \return no return value
*/
PlayGame1::PlayGame1() {

    bigShip = new QGraphicsPixmapItem ;
    mediumShip = new QGraphicsPixmapItem ;
    mediumShip2 = new QGraphicsPixmapItem ;
    smallShip1 = new QGraphicsPixmapItem ;
    smallShip2 = new QGraphicsPixmapItem;
    smallShip3 = new QGraphicsPixmapItem;

    music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/explotion.mp3"));

}

/**
* \brief Draws the grid by adding instances of GridSquare class in two 4X4 matrices, one for player and one for enemy
* \param no input argument
* \return no return value
*/
void PlayGame1 :: drawGrid(){


    //title for player grid
    QGraphicsTextItem* titlePlayer = new QGraphicsTextItem(QString("Good Coding Practices"));
    QFont titleFont("fantasy",20);
    titlePlayer->setFont(titleFont);
    titlePlayer->setPos(55, 100);
    this->addItem(titlePlayer);

    //grid for player
    for (int i=100; i<300; i+=50){
        for (int j=150; j<350; j+=50){
            GrideSquare* square = new GrideSquare();
            square->setPos(i,j);
            this->playerSquares.append(square);
            this->addItem(square);

        }
    }

    //title for enemy grid
    QGraphicsTextItem* titleEnemy = new QGraphicsTextItem(QString("Bad Coding Practices"));
    titleEnemy->setFont(titleFont);
    titleEnemy->setPos(560, 100);
    this->addItem(titleEnemy);

    //grid for enemy

    for (int i=600; i<800; i+=50){
        for (int j=150; j<350; j+=50){
            GrideSquare* square = new GrideSquare();
            square->setPos(i,j);
            this->enemySquares.append(square);
            this->addItem(square);
        }
    }
}

/**
* \brief adds the ships of the player to the player grid. The positions are always the same
* \param no input argument
* \return no return value
*/
void PlayGame1 :: addPlayerShips(){

    QGraphicsPixmapItem* ship1 = new QGraphicsPixmapItem();
    ship1-> setPixmap( (QPixmap(":/images/big ship.png")).scaled(150,50));
    ship1->setRotation(90);
    ship1->setPos(200,200); //actual coord. are (150, 200)
    this->addItem(ship1);

    QGraphicsPixmapItem* ship2 = new QGraphicsPixmapItem();
    ship2-> setPixmap( (QPixmap(":/images/small ship.png")).scaled(50,50));
    ship2->setPos(250, 300);
    this->addItem(ship2);

    QGraphicsPixmapItem* ship3 = new QGraphicsPixmapItem();
    ship3-> setPixmap( (QPixmap(":/images/small ship.png")).scaled(50,50));
    ship3->setPos(100, 200);
    this->addItem(ship3);

    QGraphicsPixmapItem* ship4 = new QGraphicsPixmapItem();
    ship4-> setPixmap( (QPixmap(":/images/Medium Ship.png")).scaled(100,50));
    ship4->setTransformOriginPoint(50,0);
    ship4->setRotation(90);
    ship4->setPos(250, 200); //actual coord are (150,150)
    this->addItem(ship4);
}

/**
* \brief adds the ships of the enemy to the enemy grid in a random way.
* \param no input argument
* \return no return value
*/
void PlayGame1 :: addEnemyShips(){

    QList<int> xPositions({600, 650, 700, 750});
    QList<int> yPositions({150, 200, 250, 300});

    int rotateFlag;

    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int>  distr(0, 3);

    //big ship
    int XBigShip;
    int YBigShip;
    //QGraphicsPixmapItem* bigShip = new QGraphicsPixmapItem();

    do{
        XBigShip = distr(generator);
        YBigShip = distr(generator);

    } while (XBigShip>=2 && YBigShip>=2);

    if (XBigShip>=2){  //special case 1: ship do not fit horizontaly, must flip
        bigShip-> setPixmap( (QPixmap(":/images/big ship.png")).scaled(150,50));
        bigShip->setTransformOriginPoint(50,0);
        bigShip->setRotation(90);

        bigShip->setPos(xPositions[XBigShip],yPositions[YBigShip+1]);
        this->addItem(bigShip);
    }

    else if (YBigShip>=2){ //special case 2: ship do not fit verticaly, must keep straight
        bigShip-> setPixmap( (QPixmap(":/images/big ship.png")).scaled(150,50));
        bigShip->setPos(xPositions[XBigShip],yPositions[YBigShip]);
        this->addItem(bigShip);
    }

    else{  //no special case
        rotateFlag = rand() % 2;
        if (rotateFlag==0){    //Do not flip
            bigShip-> setPixmap( (QPixmap(":/images/big ship.png")).scaled(150,50));
            bigShip->setPos(xPositions[XBigShip],yPositions[YBigShip]);
            this->addItem(bigShip);
        }

        else{   //flip
            bigShip-> setPixmap( (QPixmap(":/images/big ship.png")).scaled(150,50));
            bigShip->setTransformOriginPoint(50,0);
            bigShip->setRotation(90);

            bigShip->setPos(xPositions[XBigShip],yPositions[YBigShip+1]);
            this->addItem(bigShip);
        }
    }

    QList<QGraphicsItem *> collidingItemsObjects;
    //medium ship
    int XMedShip;
    int YMedShip;
    bool flag = false;

    while(flag==false){
        //QGraphicsPixmapItem* mediumShip = new QGraphicsPixmapItem();
        mediumShip-> setPixmap( (QPixmap(":/images/Medium Ship.png")).scaled(100,50));
        do{

            XMedShip = distr(generator);
            YMedShip = distr(generator);

        }while(XMedShip==3 && YMedShip==3);

        if (XMedShip==3){  //special case 1: ship do not fit horizontaly, must flip
            mediumShip->setTransformOriginPoint(50,0);
            mediumShip->setRotation(90);
            mediumShip->setPos(xPositions[XMedShip],yPositions[YMedShip+1]);
            this->addItem(mediumShip);
        }
        else if (YMedShip==3){ //special case 2: ship do not fit verticaly, must keep straight
            mediumShip->setPos(xPositions[XMedShip],yPositions[YMedShip]);
            this->addItem(mediumShip);
        }
        else{  //no special case
            rotateFlag = rand() % 2;
            if (rotateFlag==0){    //Do not flip
                mediumShip->setPos(xPositions[XMedShip],yPositions[YMedShip]);
                this->addItem(mediumShip);
            }

            else{   //flip
                mediumShip->setTransformOriginPoint(50,0);
                mediumShip->setRotation(90);
                mediumShip->setPos(xPositions[XMedShip],yPositions[YMedShip+1]);
                this->addItem(mediumShip);
            }

        }
        collidingItemsObjects = mediumShip->collidingItems();
        if (collidingItemsObjects.size()>=3) {this->removeItem(mediumShip); mediumShip->setRotation(0); }
        else {
            flag=true;
        }
    }

    //medium ship2
    int XMedShip2;
    int YMedShip2;
    flag = false;

    while(flag==false){
        //QGraphicsPixmapItem* mediumShip = new QGraphicsPixmapItem();
        mediumShip2-> setPixmap( (QPixmap(":/images/Medium Ship.png")).scaled(100,50));
        do{

            XMedShip2 = distr(generator);
            YMedShip2 = distr(generator);

        }while(XMedShip2==3 && YMedShip2==3);

        if (XMedShip2==3){  //special case 1: ship do not fit horizontaly, must flip
            mediumShip2->setTransformOriginPoint(50,0);
            mediumShip2->setRotation(90);
            mediumShip2->setPos(xPositions[XMedShip2],yPositions[YMedShip2+1]);
            this->addItem(mediumShip2);
        }
        else if (YMedShip2==3){ //special case 2: ship do not fit verticaly, must keep straight
            mediumShip2->setPos(xPositions[XMedShip2],yPositions[YMedShip2]);
            this->addItem(mediumShip2);
        }
        else{  //no special case
            rotateFlag = rand() % 2;
            if (rotateFlag==0){    //Do not flip
                mediumShip2->setPos(xPositions[XMedShip2],yPositions[YMedShip2]);
                this->addItem(mediumShip2);
            }

            else{   //flip
                mediumShip2->setTransformOriginPoint(50,0);
                mediumShip2->setRotation(90);
                mediumShip2->setPos(xPositions[XMedShip2],yPositions[YMedShip2+1]);
                this->addItem(mediumShip2);
            }

        }
        collidingItemsObjects = mediumShip2->collidingItems();
        if (collidingItemsObjects.size()>=3) {this->removeItem(mediumShip2); mediumShip2->setRotation(0); }
        else {
            flag=true;
        }
    }

    //first small ship
    int XsmallShip1;
    int YsmallShip1;
    flag = false;

    while(flag==false){
        //QGraphicsPixmapItem* smallShip1 = new QGraphicsPixmapItem();
        smallShip1-> setPixmap( (QPixmap(":/images/small ship.png")).scaled(50,50));
        XsmallShip1 = distr(generator);
        YsmallShip1 = distr(generator);
        smallShip1->setPos(xPositions[XsmallShip1],yPositions[YsmallShip1]);
        this->addItem(smallShip1);
        collidingItemsObjects = smallShip1->collidingItems();
        if (collidingItemsObjects.size()>=2) {this->removeItem(smallShip1); //delete(smallShip1);
        }
        else {
            flag=true;
        }
    }

    //second small ship
    int XsmallShip2;
    int YsmallShip2;
    flag = false;

    while(flag==false){
        //QGraphicsPixmapItem* smallShip1 = new QGraphicsPixmapItem();
        smallShip2-> setPixmap( (QPixmap(":/images/small ship.png")).scaled(50,50));
        XsmallShip2 = distr(generator);
        YsmallShip2 = distr(generator);
        smallShip2->setPos(xPositions[XsmallShip2],yPositions[YsmallShip2]);
        this->addItem(smallShip2);
        collidingItemsObjects = smallShip2->collidingItems();
        if (collidingItemsObjects.size()>=2) {this->removeItem(smallShip2);}
        else {
            flag=true;
        }
    }

    //third small ship
    int XsmallShip3;
    int YsmallShip3;
    flag = false;

    while(flag==false){
        //QGraphicsPixmapItem* smallShip1 = new QGraphicsPixmapItem();
        smallShip3-> setPixmap( (QPixmap(":/images/small ship.png")).scaled(50,50));
        XsmallShip3 = distr(generator);
        YsmallShip3 = distr(generator);
        smallShip3->setPos(xPositions[XsmallShip3],yPositions[YsmallShip3]);
        this->addItem(smallShip3);
        collidingItemsObjects = smallShip3->collidingItems();
        if (collidingItemsObjects.size()>=2) {this->removeItem(smallShip3);}
        else {
            flag=true;
        }
    }

}

/**
* \brief sets the data attribute flag for each square in the enemy grid to either 0 or 1, o means that there is no ship on that square, 1 means that there is. Hides enemy ships from the grid after that.
* \param no input argument
* \return no return value
*/
void PlayGame1 :: addFlags(){

    QList<QGraphicsItem *> collidingItemsObjects;

    //flags for enemy squares
    for(int i=0; i<this->enemySquares.size(); i++){
        enemySquares[i]->flag=0;
        enemySquares[i]->missOrHit -> setPixmap( (QPixmap(":/images/miss.png")).scaled(50,50));
        enemySquares[i]->missOrHit->setPos(enemySquares[i]->x(), enemySquares[i]->y());
        this->addItem(this->enemySquares[i]->missOrHit);

        collidingItemsObjects = this->enemySquares[i]->missOrHit->collidingItems();
        if (collidingItemsObjects.size()>1){
            this->removeItem(enemySquares[i]->missOrHit);
            enemySquares[i]->flag=1;
        }
    }

    bigShip->hide();
    mediumShip->hide();
    mediumShip2->hide();
    smallShip1->hide();
    smallShip2->hide();
    smallShip3->hide();
}

/**
* \brief This function is called when the player answers the question incorrectly, it allows the enemy to select a random square from the player's grid and fire at it. It may miss or hit
* \param no input argument
* \return no return value
*/
void PlayGame1 :: enemyAttack(){

    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int>  distr(0, 15);

    int cible;
    do{
        cible = distr(generator);
    }while(playerSquares[cible]->used==1);

    QGraphicsPixmapItem* attack = new QGraphicsPixmapItem();
    //first assume it's a miss
    attack-> setPixmap( (QPixmap(":/images/miss.png")).scaled(50,50));
    attack->setPos(playerSquares[cible]->x(), playerSquares[cible]->y());
    this->addItem(attack);

    QList<QGraphicsItem *> collidingItemsObjects = attack->collidingItems();

    //check how may colliding items
    if (collidingItemsObjects.size()==2) {
        //many colliding items, then there is a ship, it's a hit
        this->removeItem(attack);
        attack = new QGraphicsPixmapItem();
        attack-> setPixmap( (QPixmap(":/images/hit.png")).scaled(50,50));
        attack->setPos(playerSquares[cible]->x(), playerSquares[cible]->y());
        this->addItem(attack);
    }

    music->play(); //play sound of firing
    playerSquares[cible]->used=1; //set the fired squared to used so that it is not fired again
}

/**
* \brief Displays the initial score on the screen
* \param no input argument
* \return no return value
*/
void PlayGame1 :: displayScore(){

    scoreText = new QGraphicsTextItem(QString("Score:"));
    QFont titleFont("fantasy",20);
    scoreText->setFont(titleFont);
    QColor titleColor("white");
    scoreText->setDefaultTextColor(titleColor);
    scoreText->setPos(10, 20);
    this->addItem(scoreText);

    string temp1 = to_string(game->score);
    QString temp2 =QString::fromStdString(temp1);

    scoreValue = new QGraphicsTextItem(QString(temp2));
    scoreValue->setFont(titleFont);
    scoreValue->setDefaultTextColor(titleColor);
    scoreValue->setPos(100, 20);
    this->addItem(scoreValue);
}

/**
* \brief Displays the initial number of attempts on the screen
* \param no input argument
* \return no return value
*/
void PlayGame1 :: displayAttempts(){

    attemptsText = new QGraphicsTextItem(QString("Attempts:"));
    QFont titleFont("fantasy",20);
    attemptsText->setFont(titleFont);
    QColor titleColor("white");
    attemptsText->setDefaultTextColor(titleColor);
    attemptsText->setPos(710, 20);
    this->addItem(attemptsText);

    string temp1 = to_string(game->attempts);
    QString temp2 =QString::fromStdString(temp1);

    attemptsValue = new QGraphicsTextItem(QString(temp2));
    attemptsValue->setFont(titleFont);
    attemptsValue->setDefaultTextColor(titleColor);
    attemptsValue->setPos(850, 20);
    this->addItem(attemptsValue);
}

/**
* \brief It is called when the value of attempts is changed. It displays the new value.
* \param no input argument
* \return no return value
*/
void PlayGame1 :: updateAttempts(){

    this->removeItem(attemptsValue);

    string temp1 = to_string(game->attempts);
    QString temp2 =QString::fromStdString(temp1);

    attemptsValue = new QGraphicsTextItem(QString(temp2));
    QFont titleFont("fantasy",20);
    attemptsValue->setFont(titleFont);
    QColor titleColor("white");
    attemptsValue->setDefaultTextColor(titleColor);
    attemptsValue->setPos(850, 20);
    this->addItem(attemptsValue);

}

/**
* \brief It is called when the value of score is changed. It displays the new value.
* \param no input argument
* \return no return value
*/
void PlayGame1 :: updateScore(){

    this->removeItem(scoreValue);

    string temp1 = to_string(game->score);
    QString temp2 =QString::fromStdString(temp1);

    scoreValue = new QGraphicsTextItem(QString(temp2));
    QFont titleFont("fantasy",20);
    scoreValue->setFont(titleFont);
    QColor titleColor("white");
    scoreValue->setDefaultTextColor(titleColor);
    scoreValue->setPos(100, 20);
    this->addItem(scoreValue);

}

/**
* \brief destructor of the scene PlayGame1
* \param no input argument
* \return no return value
*/
