#ifndef SHOOTINGDISCSSCENE_H
#define SHOOTINGDISCSSCENE_H

#include <QGraphicsScene>
#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include <QString>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>
#include <random>
#include <QList>
#include <QMediaPlayer>
#include <QGraphicsView>
#include <QShortcut>
#include <QKeySequence>
#include "button.h"
#include "discshooter.h"
#include "targetdisc.h"

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 600
/**
* \file shootingdiscsscene.h
* \brief ShootingDiscsScene class
*
* This class provides the ShootingDiscsScene which is Shooting Discs game
*/
class ShootingDiscsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit ShootingDiscsScene(QString* loggedInUser=nullptr, QStringList* loggedInUserObject=nullptr, QObject *parent = nullptr);


private:
    QStringList* loggedInUserObject;//!< pointer to currently logged in user object
    QGraphicsPixmapItem* menuPageBackground;//!< pointer to menu page background
    Button* startGame;//!< pointer to start game button
    Button* quitGame;//!< pointer to quit game button
    QString* loggedInUser;//!< pointer to logged in user name
    DiscShooter* redShooter;//!< pointer to  red shooter object
    DiscShooter* greenShooter;//!< pointer to green shooter object
    DiscShooter* blueShooter;//!< pointer to blue shooter object
    QGraphicsPixmapItem* heart1;//!< pointer to heart1
    QGraphicsPixmapItem* heart2;//!< pointer to heart2
    QGraphicsPixmapItem* heart3;//!< pointer to heart 3
    QGraphicsTextItem* scoreLabel;//!< pointer to score labe
    QGraphicsPixmapItem* multiplier;//!< multiplier
    QGraphicsPixmapItem* redBeam;//!< red shooter beam
    QGraphicsPixmapItem* greenBeam;//!< green shooter beam
    QGraphicsPixmapItem* blueBeam;//!< blue shooter beam
    QGraphicsTextItem* scoreValue;//!< score value
    QTimer* redShooterTimer;//!< red shooter timer
    QTimer* greenShooterTimer;//!< green shooter timer
    QTimer* blueShooterTimer;//!< blue shooter timer
    QTimer* redTargetDiscsCreationTimer;//!< red target discs creation timer
    QTimer* greenTargetDiscsCreationTimer;//!< green target discs creation timer
    QTimer* blueTargetDiscsCreationTimer;//!< blue target discs creation timer
    QMediaPlayer* shootingSound;//!< shooting sound
    QMediaPlayer* menuMusic;//!< background music
    QMediaPlayer* backgroundMusic;//!< background music
    targetDisc* redDiscTarget;//!< red disc target object pointer
    targetDisc* greenDiscTarget;//!< green disc target object pointer
    targetDisc* blueDiscTarget;//!< blue disc target object pointer
    int score = 0; //!< int score value
    int remainingHearts = 3; //!< int remaining hearts number
    int currentSpeed = 800;//!< int current speed for target discs


    void setMenuPageBackground();
    void setStartGameBackground();
    void onShootRed();
    void onShootGreen();
    void onShootBlue();
    void onMissed();
    void onHit(char sender);
    void updateScore();
    void updateMultiplier();
    void gameOver();


signals:
    void hideView();

public slots:
    void onStartGameClicked();
    void onQuitGameClicked();
    void addNewRedDiscTarget();
    void addNewGreenDiscTarget();
    void addNewBlueDiscTarget();

};

#endif // SHOOTINGDISCSSCENE_H
