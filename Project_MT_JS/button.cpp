/**
* \file Button.cpp
* \brief this is the implemetation of the buttons used in the game
*
This class implemets the reaction of the buttons to hovering events and allows connection with signals.
*
* \author Mariam Termos
*/

#include "button.h"

/**
 * \file button.cpp
* \brief Constructor of the class, initializes the style of the button
* \param name, which is the label of the button
* \return no return value
*/
Button::Button(QString name, QGraphicsItem *parent): QGraphicsRectItem(parent){
    // draw the rectangle
    setRect(0,0,200,50);

    //setting the style of the rectangle
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    setBrush(brush);

    // draw the text
    text = new QGraphicsTextItem(name,this);
    text->setFont(QFont("Helvetica", 20));
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);

    // allow responding to hover events
    setAcceptHoverEvents(true);
}

/**
* \brief funtion invoked on mouse press, each button takes user to a different page
* \param event, which is the mouse click
* \return no return value
*/
void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
}

/**
* \brief changes the color of the button when a hovering in event occurs
* \param event, which is the hovering of the mourse over the button
* \return no return value
*/
void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    // change color to cyan
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);
}

/**
* \brief changes the color of the button back to original when a hovering out event occurs
* \param event, which is the hovering of the mourse away from the button
* \return no return value
*/
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    // change color to dark cyan
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    setBrush(brush);
}

