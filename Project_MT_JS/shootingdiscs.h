#ifndef SHOOTINGDISCS_H
#define SHOOTINGDISCS_H

#include <QGraphicsView>
#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include "shootingdiscsscene.h"

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 600

/**
* \file shootingdiscs.h
* \brief ShootingDiscs class.
* ShootingDiscs GraphicsView which is passed a shooting discs scene for the game
*
*/
class ShootingDiscs : public QGraphicsView
{
    Q_OBJECT
public:
    // constructor
    ShootingDiscs(QString* loggedInUser=nullptr, QStringList* loggedInUserObject=nullptr, QWidget *parent = nullptr);


protected:
    void mousePressEvent(QMouseEvent *event);


private:

    ShootingDiscsScene* scene;//!< pointer to ShootingDiscsScene object

    void scrollContentsBy(int, int){}

};

#endif // SHOOTINGDISCS_H
