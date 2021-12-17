#ifndef QUESTIONPOPSCREEN_H
#define QUESTIONPOPSCREEN_H

#include <QWidget>
#include<QtWidgets>
#include <random>
#include<unistd.h>
#include<QGraphicsPixmapItem>
#include<QMediaPlayer>
#include "gridesquare.h"

using namespace std;

/**
* \file questionPopScreen.h
* \brief questionPopScreen class.
*
* This class inherits from QWidget. It consists the elements for the pop-up widget used for the question
* to be answered by the user
*
*/

class questionPopScreen : public QWidget {
    Q_OBJECT

public:
    //constructor
    explicit questionPopScreen(QWidget *parent = nullptr);

    //functions
    void setGridLayout();
    void setColors();
    void selectQuestion();
    void connectSlots();
    void disconnectSlots();
    void prepareScreen(GrideSquare* squareToHit);


    //attributes
    QLabel* question; //!the question itself
    QComboBox* chooseTopic; //!the menu of choices of the topic for the questions
    QPushButton* apply; //!apply button used after changing the topic
    QPushButton* answer1; //!Button for first option
    QPushButton* answer2; //!Button for second option
    QPushButton* answer3; //!Button for third option
    QPushButton* answer4; //!button for forth option

    //for each answer button we have 2 flags. they are used to connect and disconnect buttons from the signals
    int flag1=0;  //!this flag indicates the currect value (correct/incorrect) of the answer hold by the button
    int oldFlag1=-1; //!this flag indicates the previous value (correct/incorrect) of the answer, which allows us to disconnect the button from the previous signal
    int flag2=0;
    int oldFlag2=-1;
    int flag3=0;
    int oldFlag3=-1;
    int flag4=0;
    int oldFlag4=-1;
    int flagConstruct=-1;

    GrideSquare* squareToHit; //!This is the square that called the pop-up question
    QGridLayout* gridLayout;  //!A sub-layout of the widget
    QVBoxLayout *verticalLayout; //!the main layout of the widget
    QList<int> askedQuestions; //!list that holds the line numbers of the asked question. This is to avaoid asking the same question multiple times
    QMediaPlayer* music;  //!music file of the explotion
    QString topic="Not specified"; //!topic of the questions


signals:

// slots must be defined under the slots keyword
private slots:

    void clickedOnWrongAns();
    void clickedOnRightAns();
    void changeTopic();

};

#endif // QUESTIONPOPSCREEN_H
