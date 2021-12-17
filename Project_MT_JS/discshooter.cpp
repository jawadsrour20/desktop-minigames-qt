#include "discshooter.h"
/**
 * \file discshooter.cpp
 * \brief contains DiscShooter class definition
 */
DiscShooter::DiscShooter(QObject *parent) : QObject(parent)
{

}

/**
 * \brief emits a signal for the disc shooter based on which key was pressed.
 * Left key for the red shooter, down key for the green shooter, and right key for the blue shooter.
 * \param event first argument, to detect a key press
 */
void DiscShooter::keyPressEvent(QKeyEvent *event){

    // red shooter
    if (event->key() == Qt::Key_Left)
        emit shoot('R');

    // green shooter
    if (event->key() == Qt::Key_Down)
        emit shoot('G');
    // blue shooter
    if (event->key() == Qt::Key_Right)
        emit shoot('B');

}
