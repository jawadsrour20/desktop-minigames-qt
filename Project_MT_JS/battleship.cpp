/**
* \file BattleShip.cpp
* \brief this is the implemetation of the view of the game
*
This class implements the different pages related to  the batttleship game,
from the main menu to the main game screen to the game over screen and finally
to the exit screen.
*
* \author Mariam Termos
*/

#include "battleship.h"

/**
 * \file battleship.cpp
* \brief Constructor of the class, initializes the scene
* \param no input argument
* \return no return value
*/
BattleShip::BattleShip(QWidget *parent) {

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(900, 500);

    scene = new PlayGame1();
    scene->setSceneRect(0,0,900,500);
    setScene(scene);

}

/**
* \brief Prepares the game by calling all the functions responsible of setting the background, drawing the grid, adding ships, displaying initial score and attempts from PlayGmae1 class
* \param no input argument
* \return no return value
*/
void BattleShip :: startGame(){
    // clear the screen
    scene->clear();

    //setting the scene for the game
    setBackgroundBrush(QBrush(QImage(":/images/blue.jpeg").scaledToHeight(500).scaledToWidth(900)));
    scene->drawGrid();
    scene->addPlayerShips();
    scene->addEnemyShips();
    scene->addFlags();
    scene->displayScore();
    scene->displayAttempts();
}

/**
* \brief Displays the main menu
* \param no input argument
* \return no return value
*/
void BattleShip :: displayMainMenu(){

    scene->clear();

    //adding title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Battleship Game"));
    QFont titleFont("fantasy",30);
    titleText->setFont(titleFont);
    QColor titleColor("Blue");
    titleText->setDefaultTextColor(titleColor);
    titleText->setPos(550, 100);
    scene->addItem(titleText);

    //adding buttons
    Button* playButton = new Button("Play");
    playButton->setPos(600, 200);
    connect(playButton,SIGNAL(clicked()),this,SLOT(startGame()));
    scene->addItem(playButton);

    Button* howToPlayButton = new Button("How To Play");
    howToPlayButton->setPos(600, 270);
    scene->addItem(howToPlayButton);
    connect(howToPlayButton,SIGNAL(clicked()),this,SLOT(instructions()));

    Button* quitButton = new Button("Quit");
    quitButton->setPos(600, 340);
    scene->addItem(quitButton);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(returnHome()));

    //setting the backgroud
    setBackgroundBrush(QBrush(QImage(":/images/Background2.jpeg").scaledToHeight(512).scaledToWidth(910)));
    setSceneRect(0, 0, 900, 500);
}

/**
* \brief Prints that the game is over when the number of attempts is 0 or when all player's ships are destroted
* \param no input argument
* \return no return value
*/
void BattleShip :: gameOver() {

    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("GAME OVER"));
    QFont titleFont("fantasy",80);
    titleText->setFont(titleFont);
    QColor titleColor("black");
    titleText->setDefaultTextColor(titleColor);
    titleText->setPos(150, 150);
    scene->addItem(titleText);

    Button* continueButton = new Button("Continue");
    continueButton->setPos(350, 300);
    connect(continueButton,SIGNAL(clicked()),this,SLOT(endPage()));
    scene->addItem(continueButton);


}

/**
* \brief Display ending page, which shows the score and a button to go back to home page
* \param no input argument
* \return no return value
*/
void BattleShip :: endPage(){

    // clear the screen
    scene->clear();
    //setting the scene for the game
    setBackgroundBrush(QBrush(QImage(":/images/blue.jpeg").scaledToHeight(500).scaledToWidth(900)));

    //add score to history only if the user is registered

    if(playerName!="guest"){



        QList<QString> newScores;
//        QFile* scoresFile = new QFile("/Users/jawadsrour/Project_MT_JS/battleship_scores.txt");
                QFile* scoresFile = new QFile(QDir().absoluteFilePath("../Project_MT_JS/battleship_scores.txt"));
        scoresFile->open(QIODevice::ReadOnly|QIODevice::Text);
        QTextStream in(scoresFile);

        QString line, userName;
        QStringList lineList;
        int posOfSpace=0;

        while (!in.atEnd()) {
            line = in.readLine();
            posOfSpace= line.indexOf(" ");
            userName=line.mid(0, posOfSpace);
            if(userName.toStdString() == playerName){
                line = line + " " + QString::number(score);;
            }

            newScores.append(line);
        }
        scoresFile->close();


//        QFile* scoresFile2 = new QFile("/Users/jawadsrour/Project_MT_JS/battleship_scores.txt");
                QFile* scoresFile2 = new QFile(QDir().absoluteFilePath("../Project_MT_JS/battleship_scores.txt"));
        scoresFile2->open(QIODevice::WriteOnly|QIODevice::Text);
        QTextStream writeto(scoresFile2);

        for (int i=0;i<newScores.length();i++){
            writeto << newScores[i];
            writeto << endl;
        }

        scoresFile2->close();
    }

    QGraphicsTextItem* titleText = new QGraphicsTextItem();
    QFont titleFont("fantasy",50);
    QColor titleColor("black");

    if (score>=7){
        titleText = new QGraphicsTextItem(QString("YOU WON!"));
        titleText->setFont(titleFont);
        titleText->setDefaultTextColor(titleColor);
        titleText->setPos(300, 100);
        scene->addItem(titleText);
    }

    else{
        titleText = new QGraphicsTextItem(QString("you lost"));
        titleText->setFont(titleFont);
        titleText->setDefaultTextColor(titleColor);
        titleText->setPos(300, 100);
        scene->addItem(titleText);
    }

    titleText = new QGraphicsTextItem(QString("score = "));
    titleText->setFont(titleFont);
    titleText->setDefaultTextColor(titleColor);
    titleText->setPos(250, 200);
    scene->addItem(titleText);

    string temp1 = to_string(this->score);
    QString temp2 = QString::fromStdString(temp1);

    titleText = new QGraphicsTextItem(QString(temp2));
    titleText->setFont(titleFont);
    titleText->setDefaultTextColor(titleColor);
    titleText->setPos(550, 200);
    scene->addItem(titleText);

    Button* exit = new Button("Quit");
    exit->setPos(600, 340);
    connect(exit,SIGNAL(clicked()),this,SLOT(returnHome()));
    scene->addItem(exit);
}

/**
* \brief Takes user back to the inital home page (page shown after logging in)
* \param no input argument
* \return no return value
*/
void BattleShip::returnHome(){

    returnTo->show();
    this->hide();
}

/**
* \brief Takes user to the page that explains the game
* \param no input argument
* \return no return value
*/
void BattleShip :: instructions(){

    // clear the screen
    scene->clear();

    //setting the scene for the game
    setBackgroundBrush(QBrush(QImage(":/images/blue.jpeg").scaledToHeight(500).scaledToWidth(900)));

    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("How to play: \n 1-Grid on left contains your ships. Grid on right contains enemy ships. "
                                              "\n 2-Press on a case in enemy grid to fire. \n 3-If you hit, you will have to answer a question so that"
                                              " you hit takes effect. \n 4-If your answer is wrong, enemy will fire back and your hit won't be considered."
                                              "\n 5-If you answer correctly, you get one score point. \n 6- In all cases, you lose one attempt."
                                              "\n 7-Game is over when all attempts are used. You win if you get a score of 7 or more.   "));
    QFont titleFont("fantasy", 15);
    titleText->setFont(titleFont);
    QColor titleColor("black");
    titleText->setDefaultTextColor(titleColor);
    titleText->setPos(10, 10);
    scene->addItem(titleText);

    Button* back = new Button("Back");
    back->setPos(350, 300);
    connect(back,SIGNAL(clicked()),this,SLOT(displayMainMenu()));
    scene->addItem(back);
}
