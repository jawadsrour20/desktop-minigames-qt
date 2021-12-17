#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QWidget>
#include<QGraphicsSimpleTextItem>
#include <QGraphicsTextItem>
#include <QBrush>

/**
* \file Button.h
* \brief Button class.
*
* This class inherits from QGraphicsRectItem. It is basically a rectangle that we are making act as a button.
* this button reacts to hovering of the mouse in and out by changing its color.
*/

class Button:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    // constructors
    Button(QString name, QGraphicsItem* parent=NULL);

    // public methods (events)
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    void clicked();
    void pressed();

private:
    QGraphicsTextItem* text; //!< label of the button
};

#endif // BUTTON_H
