#ifndef TARGETDISC_H
#define TARGETDISC_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>

/**
* \file targetdisc.h
* \brief targetDisc class
* For the creation of target discs to be shot by shooters
*/
class targetDisc : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    targetDisc(QObject *parent = nullptr);
    QTimer* timer;//!< timer for the target disc object

signals:
    void missed();
    void hit();

public slots:
    void updateDiscTargetCurrentPosition();
};

#endif // TARGETDISC_H
