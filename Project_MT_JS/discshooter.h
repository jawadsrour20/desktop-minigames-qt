#ifndef DISCSHOOTER_H
#define DISCSHOOTER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
/**
* \file discshooter.h
* \brief DiscShooter class.
*
* Defines the behavior of the Disc Shooters.
* This class inherits from QGraphicsPixMapItem and QObject.
*/
class DiscShooter : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:

    // constructor
    explicit DiscShooter(QObject *parent = nullptr);

    // event handler function. Called when item is focus + a key is pressed
    void keyPressEvent(QKeyEvent* event);



signals:
    // signal emitted by a disc shooter object to let it shoot a beam in the Scene
    void shoot(char sender);

};

#endif // DISCSHOOTER_H
