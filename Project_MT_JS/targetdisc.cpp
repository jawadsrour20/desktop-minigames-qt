#include "targetdisc.h"
#define NEXT_MOVE 50
/**
 * \file targetdisc.cpp
 * \brief contains targetDisc implementation
 * defines the target discs to be shot and a timer for their creation
 */
targetDisc::targetDisc(QObject* parent) : QObject(parent)
{


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateDiscTargetCurrentPosition()));
    timer->start(1000);

}
/**
 * \brief updates the position of the target discs.
 *
 * A disc keeps moving till either it collides with a beam from the scene object
 * or till it reaches the shooter buttons at the bottom
 */
void targetDisc::updateDiscTargetCurrentPosition()
{

    if (scene() != NULL){
        // target HIT
        if (!scene()->collidingItems(this).isEmpty())
        {
            scene()->removeItem(this);
            emit hit();
            delete this;

        }

        // target MISS
        else if (this->y() + NEXT_MOVE >= 700){

            scene()->removeItem(this);
            emit missed();
            delete this;


        }
        else
        {
            this->setPos(this->x(), this->y() + NEXT_MOVE);
        }
    }
}
