#ifndef GRIDESQUARE_H
#define GRIDESQUARE_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QWidget>
#include<QGraphicsSimpleTextItem>
#include <random>
#include<unistd.h>
#include<QMediaPlayer>

using namespace std;

/**
* \file GrideSquare.h
* \brief GrideSquare class
*
* This class inherits from QGraphicsRectItem. It is the unit of the grid used in the game.
* This rectangle is like a container for the ship and their flags.
*/

class GrideSquare :public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    //constructor
    GrideSquare(QGraphicsItem* parent=NULL);

    //functions
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    //attribute
    QGraphicsPixmapItem *fireReady; //!this hold the aming images that appears and disappears which hovering over the rectangle
    QGraphicsPixmapItem *missOrHit; //!this holds the one of the images: miss if there is no ship in this square, hit id there is a ship.
    int flag=0;                     //!if flag==0 then this rectangle does not contain a ship. If flag==1 then it does.
    int used=0;                     //!saves if the rectangle was already fired or not
    QMediaPlayer* music;            //!music file played when firing, sound of an explotion.

signals:

};

#endif // GRIDESQUARE_H
