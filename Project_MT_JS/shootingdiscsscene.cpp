#include "shootingdiscsscene.h"
#include "home.h"


/**
 * \file shootingdiscsscene.cpp
 * \brief contains ShootingDiscsScene class definition
 * \param loggedInUser first argument, pointer to the currently logged in user name
 * \param loggedInUserObject second argument, pointer to the currently logged in user object
 */
ShootingDiscsScene::ShootingDiscsScene(QString* loggedInUser, QStringList* loggedInUserObject, QObject *parent) : QGraphicsScene(parent)
{


    if (loggedInUserObject != nullptr && loggedInUser != nullptr) {

        this->loggedInUserObject = loggedInUserObject;
        this->loggedInUser = loggedInUser;
    }
    else
    {
        this->loggedInUserObject = nullptr;
        this->loggedInUser = new QString("guest");
    }


    this->setMenuPageBackground();

    startGame = new Button("START");
    quitGame = new Button("QUIT");

    startGame->setPos(SCREEN_WIDTH/3.2, SCREEN_HEIGHT/2);
    quitGame->setPos(SCREEN_WIDTH/3.2, 3 * SCREEN_HEIGHT/4);

    this->addItem(startGame);
    this->addItem(quitGame);

    connect(startGame, SIGNAL(clicked()), this, SLOT(onStartGameClicked()));
    connect(quitGame, SIGNAL(clicked()), this, SLOT(onQuitGameClicked()));


    backgroundMusic = new QMediaPlayer();
    backgroundMusic->setMedia(QUrl("qrc:/game_bg.mp3"));
    backgroundMusic->play();



}

// METHODS
/**
 * \brief sets the background for the menu page of shooting discs game
 */
void ShootingDiscsScene::setMenuPageBackground()
{
    clear();

    this->setBackgroundBrush(QBrush(QImage(":/images/SD_background.jpg").scaled(SCREEN_WIDTH, SCREEN_HEIGHT, Qt::KeepAspectRatio)));

}


// SLOTS

/**
 * \brief sets up the actual shooting discs game when Start button is clicked
 */
void ShootingDiscsScene::onStartGameClicked()
{
    this->clear();
    this->setBackgroundBrush(QBrush(QImage(":/images/game_grid.png").scaled(SCREEN_WIDTH, SCREEN_HEIGHT, Qt::KeepAspectRatio)));



    redShooter = new DiscShooter();
    greenShooter = new DiscShooter();
    blueShooter = new DiscShooter();

    redShooter->setPixmap((QPixmap(":/images/red_button.png")).scaled(80,80));
    redShooter->setPos(100, SCREEN_HEIGHT - 40);
    redShooter->setFlag(QGraphicsItem::ItemIsFocusable);

    greenShooter->setPixmap((QPixmap(":/images/green_button.png")).scaled(80,80));
    greenShooter->setPos(SCREEN_WIDTH/2 - 40, SCREEN_HEIGHT - 40);
    greenShooter->setFlag(QGraphicsItem::ItemIsFocusable);

    blueShooter->setPixmap((QPixmap(":/images/blue_button.png")).scaled(80,80));
    blueShooter->setPos(SCREEN_WIDTH - 160, SCREEN_HEIGHT - 40);
    blueShooter->setFlag(QGraphicsItem::ItemIsFocusable);


    redShooter->setFocus();



    shootingSound = new QMediaPlayer();
    shootingSound->setMedia(QUrl("qrc:/shoot.wav"));

    redShooterTimer = new QTimer(this);
    redBeam = new QGraphicsPixmapItem();
    redBeam->setPixmap((QPixmap(":/images/beam.png")).scaled(70,400));
    redBeam->setPos(100, SCREEN_HEIGHT - 400);

    greenShooterTimer = new QTimer(this);
    greenBeam = new QGraphicsPixmapItem();
    greenBeam->setPixmap((QPixmap(":/images/beam.png")).scaled(70,400));
    greenBeam->setPos(SCREEN_WIDTH/2 - 30, SCREEN_HEIGHT - 400);

    blueShooterTimer = new QTimer(this);
    blueBeam = new QGraphicsPixmapItem();
    blueBeam->setPixmap((QPixmap(":/images/beam.png")).scaled(70,400));
    blueBeam->setPos(SCREEN_WIDTH - 160, SCREEN_HEIGHT - 400);





    heart1 = new QGraphicsPixmapItem();
    heart1->setPixmap((QPixmap(":/images/heart.png")).scaled(40,40));
    heart1->setPos(10, 80);
    heart2 = new QGraphicsPixmapItem();
    heart2->setPixmap((QPixmap(":/images/heart.png")).scaled(40,40));
    heart2->setPos(45, 80);
    heart3 = new QGraphicsPixmapItem();
    heart3->setPixmap((QPixmap(":/images/heart.png")).scaled(40,40));
    heart3->setPos(80, 80);
    QGraphicsTextItem* scoreLabel = new QGraphicsTextItem(QString("SCORE: "));
    QFont titleFont("fantasy",18);
    scoreLabel->setFont(titleFont);
    QColor titleColor("white");
    scoreLabel->setDefaultTextColor(titleColor);
    scoreLabel->setPos(SCREEN_WIDTH/2 - 80, 80);

    string temp1 = to_string(score);
    QString temp2 =QString::fromStdString(temp1);
    scoreValue = new QGraphicsTextItem(QString(temp2));
    scoreValue->setFont(titleFont);
    scoreValue->setDefaultTextColor(titleColor);
    scoreValue->setPos(SCREEN_WIDTH/2 + 50, 80);


    multiplier = new QGraphicsPixmapItem();
    multiplier->setPixmap((QPixmap(":/images/mult1x.png")).scaled(30,30));
    multiplier->setPos(SCREEN_WIDTH - 50, 80);


    // Setting Timers for creating TARGET DISCS




    redTargetDiscsCreationTimer = new QTimer(this);
    connect(redTargetDiscsCreationTimer, SIGNAL(timeout()), this, SLOT(addNewRedDiscTarget()));
    redTargetDiscsCreationTimer->start((arc4random() % 7000) + 1300);

    greenTargetDiscsCreationTimer = new QTimer(this);
    connect(greenTargetDiscsCreationTimer, SIGNAL(timeout()), this, SLOT(addNewGreenDiscTarget()));
    greenTargetDiscsCreationTimer->start((arc4random() % 8000) + 1100);

    blueTargetDiscsCreationTimer = new QTimer(this);
    connect(blueTargetDiscsCreationTimer, SIGNAL(timeout()), this, SLOT(addNewBlueDiscTarget()));
    blueTargetDiscsCreationTimer->start((arc4random() % 9000) + 1200);



    // PROVIDING CAPABILITY OF SHOOTING LASER BEAMS

    connect(redShooter, &DiscShooter::shoot, [this](char input) {
        if (input == 'R')
            onShootRed();
        else if (input == 'G')
            onShootGreen();
        else if (input == 'B')
            onShootBlue();
    });

    this->addItem(redShooter);
    this->addItem(greenShooter);
    this->addItem(blueShooter);
    this->addItem(heart1);
    this->addItem(heart2);
    this->addItem(heart3);
    this->addItem(scoreLabel);
    this->addItem(scoreValue);
    this->addItem(multiplier);
}

/**
 * \brief quits the shooting discs game when Quit button is clicked
 */
void ShootingDiscsScene::onQuitGameClicked()
{ 
    backgroundMusic->stop();

    //    this->clear();
    Home* homePage;
    if (loggedInUserObject != nullptr)
        homePage= new Home(loggedInUserObject);
    else
        homePage = new Home(nullptr);
    homePage->show();

    emit hideView();
}
/**
 * \brief shoots a beam from the red shooter
 */
void ShootingDiscsScene::onShootRed(){


    shootingSound->play();
    this->addItem(redBeam);
    connect(redShooterTimer, &QTimer::timeout, [this]() {
        this->removeItem(redBeam);
        redShooterTimer->stop();
    });
    redShooterTimer->start(400);
}

/**
 * \brief shoots a beam from the green shooter
 */
void ShootingDiscsScene::onShootGreen(){


    shootingSound->play();
    this->addItem(greenBeam);
    connect(greenShooterTimer, &QTimer::timeout, [this]() {
        this->removeItem(greenBeam);
        greenShooterTimer->stop();
    });
    greenShooterTimer->start(400);

}
/**
 * \brief shoots a beam from the blue shooter
 */
void ShootingDiscsScene::onShootBlue(){

    shootingSound->play();
    this->addItem(blueBeam);
    connect(blueShooterTimer, &QTimer::timeout, [this]() {
        this->removeItem(blueBeam);
        blueShooterTimer->stop();
    });
    blueShooterTimer->start(400);

}
/**
 * \brief adds new targets for the red shooter
 */
void ShootingDiscsScene::addNewRedDiscTarget(){
    redDiscTarget = new targetDisc();
    redDiscTarget->setPixmap((QPixmap(":/images/red_disc.png")).scaled(50,50));
    redDiscTarget->setPos(130, 400);
    redDiscTarget->timer->setInterval(currentSpeed);

    this->addItem(redDiscTarget);
    // RESPONDING TO A TARGET MISS
    connect(redDiscTarget, &targetDisc::missed, [this]() {
        onMissed();
    });
    // RESPONDING TO A TARGET HIT
    connect(redDiscTarget, &targetDisc::hit, [this]() {
        onHit('R');
    });

}

/**
 * \brief adds new targets for the green shooter
 */
void ShootingDiscsScene::addNewGreenDiscTarget(){
    greenDiscTarget = new targetDisc();
    greenDiscTarget->setPixmap((QPixmap(":/images/green_disc.png")).scaled(50,50));
    greenDiscTarget->setPos(SCREEN_WIDTH/2 - 30, 400);
    greenDiscTarget->timer->setInterval(currentSpeed);
    this->addItem(greenDiscTarget);
    connect(greenDiscTarget, &targetDisc::missed, [this]() {
        onMissed();
    });
    connect(greenDiscTarget, &targetDisc::hit, [this]() {
        onHit('G');
    });

}
/**
 * \brief adds new targets for the blue shooter
 */
void ShootingDiscsScene::addNewBlueDiscTarget(){
    blueDiscTarget = new targetDisc();
    blueDiscTarget->setPixmap((QPixmap(":/images/blue_disc.png")).scaled(50,50));
    blueDiscTarget->setPos(SCREEN_WIDTH - 160, 400);
    blueDiscTarget->timer->setInterval(currentSpeed);
    this->addItem(blueDiscTarget);
    connect(blueDiscTarget, &targetDisc::missed, [this]() {
        onMissed();
    });
    connect(blueDiscTarget, &targetDisc::hit, [this]() {
        onHit('B');
    });

}

/**
 * \brief removes a heart when a target disc is missed.
 * Issues a call to gameover() if no hearts remain
 */
void ShootingDiscsScene::onMissed(){


    remainingHearts--;



    if (remainingHearts == 2)
    {
        this->removeItem(heart3);
        delete heart3;
    }
    else if (remainingHearts == 1)
    {
        this->removeItem(heart2);
        delete heart2;
    }
    else if (remainingHearts == 0)
    {
        this->removeItem(heart1);
        delete heart1;
        gameOver();
    }



}
/**
 * \brief modifies the score when a target disc is successfully hit
 * and calls  updateScore() and updateMultiplier() methods
 * \param sender first argument, determines the shooter that hit a target disc
 */
void ShootingDiscsScene::onHit(char sender){

    if (sender == 'R')
        score += 3;
    else if (sender == 'G')
        score += 5;
    else if (sender == 'B')
        score += 7;

    updateScore();
    updateMultiplier();
}

/**
 * \brief saves the user's score when the game is over and allows user to go back to home page
 */
void ShootingDiscsScene::gameOver(){



    //add score to history only if the user is registered

    QString* guest = new QString("guest");
    if(*loggedInUser!= *guest){

        qDebug() << "current user " << *loggedInUser;

        QList<QString> newScores;

        QFile* scoresFile = new QFile(":/shooting_scores.txt");
        scoresFile->open(QIODevice::ReadOnly|QIODevice::Text);
        QTextStream in(scoresFile);

        QString line, userName;
        QStringList lineList;
        int posOfSpace=0;

        while (!in.atEnd()) {
            line = in.readLine();
            posOfSpace= line.indexOf(" ");
            userName=line.mid(0, posOfSpace);
            if(userName == *loggedInUser){
                line = line + " " + QString::number(score);
            }

            newScores.append(line);
        }
        scoresFile->close();


//        QFile* scoresFile2 = new QFile("/Users/jawadsrour/Project_MT_JS/shooting_scores.txt");
                QFile* scoresFile2 = new QFile(QDir().absoluteFilePath("../Project_MT_JS/shooting_scores.txt"));
        scoresFile2->open(QIODevice::WriteOnly|QIODevice::Text);
        QTextStream writeto(scoresFile2);

        for (int i=0;i<newScores.length();i++){
            qDebug() << newScores[i];
            writeto << newScores[i];
            writeto << endl;
        }

        scoresFile2->close();
    }

    QGraphicsTextItem* titleText = new QGraphicsTextItem();
    QFont titleFont("fantasy",50);
    QColor titleColor("black");

    if (score>=150){
        titleText = new QGraphicsTextItem(QString("YOU WON!"));
        titleText->setFont(titleFont);
        titleText->setDefaultTextColor(titleColor);
        titleText->setPos(SCREEN_WIDTH/2 - 100, 180);
        this->addItem(titleText);
    }

    else{
        titleText = new QGraphicsTextItem(QString("YOU LOST!"));
        titleText->setFont(titleFont);
        titleText->setDefaultTextColor("white");
        titleText->setPos(SCREEN_WIDTH/2 - 120, 180);
        this->addItem(titleText);
    }

    titleText = new QGraphicsTextItem(QString("SCORE = "));
    titleText->setFont(titleFont);
    titleText->setDefaultTextColor("white");
    titleText->setPos(SCREEN_WIDTH/2 - 120, 250);
    this->addItem(titleText);

    string temp1 = to_string(this->score);
    QString temp2 = QString::fromStdString(temp1);

    titleText = new QGraphicsTextItem(QString(temp2));
    titleText->setFont(titleFont);
    titleText->setDefaultTextColor("white");
    titleText->setPos(SCREEN_WIDTH/2 + 90, 250);
    this->addItem(titleText);

    Button* exit = new Button("EXIT");
    exit->setPos(SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT - 100);
    connect(exit,SIGNAL(clicked()),this,SLOT(onQuitGameClicked()));
    this->addItem(exit);
}

/**
 * \brief updates the displayed score on the UI
 */
void ShootingDiscsScene::updateScore(){

    removeItem(scoreValue);
    delete scoreValue;
    string temp1 = to_string(score);
    QString temp2 =QString::fromStdString(temp1);
    scoreValue = new QGraphicsTextItem(QString(temp2));
    QFont titleFont("fantasy",30);
    QColor titleColor("white");
    scoreValue->setFont(titleFont);
    scoreValue->setDefaultTextColor(titleColor);
    scoreValue->setPos(SCREEN_WIDTH/2 + 40, 80);
    addItem(scoreValue);
}
/**
 * \brief updates the multiplier and speed of disc targets based on the current score
 */
void ShootingDiscsScene::updateMultiplier(){

    removeItem(multiplier);
    delete multiplier;

    multiplier = new QGraphicsPixmapItem();
    multiplier->setPos(SCREEN_WIDTH - 50, 80);
    // x16
    if (score >= 120)
    {
        multiplier->setPixmap((QPixmap(":/images/mult16x.png")).scaled(30,30));
        currentSpeed = 60;

    }
    // x8
    else if (score >= 90)
    {
        multiplier->setPixmap((QPixmap(":/images/mult8x.png")).scaled(30,30));
        currentSpeed = 90;
    }
    // x4
    else if (score >= 60)
    {
        multiplier->setPixmap((QPixmap(":/images/mult4x.png")).scaled(30,30));
        currentSpeed = 200;
    }
    // x2
    else if (score >= 30)
    {
        multiplier->setPixmap((QPixmap(":/images/mult2x.png")).scaled(30,30));
        currentSpeed = 300;
    }
    // remains at x1
    else
    {
        multiplier->setPixmap((QPixmap(":/images/mult1x.png")).scaled(30,30));
    }

    addItem(multiplier);

}

