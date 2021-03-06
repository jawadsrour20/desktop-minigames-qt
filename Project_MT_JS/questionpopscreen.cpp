/**
* \file questionPopScreen.cpp
* \brief this is the implemetation of the pop-up question widget
*
This class implemets the different functions of the widget. it is mainly
responsable of the preparing the items of the pop-up screen: first we have the drop down menu to allow
the user to choose the topic of the question. Then the question is selected and printed.
And finally we have 4 buttons, one for each option of the answer, and each buttton is connected to
a signal depending on whether the button contains the correct answer or not.
*
* \author Mariam Termos
*/

#include "questionpopscreen.h"
#include"battleship.h"

extern BattleShip* game;

/**
 * \file questionpopscreen.cpp
* \brief Constructor, initializes the instances of the class.
* \param no input argument
* \return no return value
*/
questionPopScreen::questionPopScreen(QWidget *parent) : QWidget(parent){

    this->setStyleSheet("background-color:#363945;");

    question = new QLabel();
    apply = new QPushButton("Apply");
    answer1 = new QPushButton();
    answer2 = new QPushButton();
    answer3 = new QPushButton();
    answer4 = new QPushButton();
    gridLayout = new QGridLayout();
    verticalLayout = new QVBoxLayout();
    chooseTopic = new QComboBox();

    //we will add a firing sound that plays when player or enemy fires.
    music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/explotion.mp3"));

}

/**
* \brief selects a question randomly from the question list. If the user specifies a topic for the question using the drop down menu, the questions will be selected randomly from the group belonging to the specific topic.
* \param no input argument
* \return no return value
*/
void questionPopScreen:: selectQuestion(){

    random_device rand_dev;
    mt19937 generator(rand_dev());
    int selectedLineIndex;

    askedQuestions.append(1);
    askedQuestions.append(15);
    askedQuestions.append(31);

    if(topic=="Not specified"){
        uniform_int_distribution<int>  distr(1, 45);
        do{
            selectedLineIndex = distr(generator);
                                                 }while( askedQuestions.indexOf(selectedLineIndex)!=-1);
    }
    if(topic=="Debugging"){
        uniform_int_distribution<int>  distr(2, 14);
        do{
            selectedLineIndex = distr(generator);
                                                 }while(askedQuestions.indexOf(selectedLineIndex)!=-1);
    }
    if(topic=="OOP"){
        uniform_int_distribution<int>  distr(16, 30);
        do{
            selectedLineIndex = distr(generator);
                                                 }while(askedQuestions.indexOf(selectedLineIndex)!=-1);
    }
    if(topic=="version control"){
        uniform_int_distribution<int>  distr(32, 45);
        do{
            selectedLineIndex = distr(generator);
                                                 }while(askedQuestions.indexOf(selectedLineIndex)!=-1);
    }

    askedQuestions.append(selectedLineIndex);

    QFile questionsList(":/questions.txt");
    QString line, subLine, selectedQuestion, ans;

    int lineCount=1, posOfColumn=0, posOfComma=0;
    string temp;

    if (questionsList.open(QIODevice::ReadOnly)) {

       QTextStream in(&questionsList);
       while (!questionsList.atEnd()) {
           line = questionsList.readLine();
           if (lineCount==selectedLineIndex){
               posOfColumn= line.indexOf(":");
               selectedQuestion=line.mid(0, posOfColumn);
               question->setText(selectedQuestion);
               subLine = line.mid(posOfColumn+2, line.length());

               posOfComma= subLine.indexOf(",");
               temp= (subLine.mid(0, posOfComma)).toStdString();
               temp=temp[temp.length()-1];
               if (temp == "1") flag1=1;
               else flag1=0;
               ans=subLine.mid(0, posOfComma -1 );
               answer1->setText(ans);
               subLine = subLine.mid(posOfComma+2, subLine.length() );

               posOfComma= subLine.indexOf(",");
               temp= (subLine.mid(0, posOfComma)).toStdString();
               temp=temp[temp.length()-1];
               if (temp == "1") flag2=1;
               else flag2=0;
               ans=subLine.mid(0, posOfComma -1 );
               answer2->setText(ans);
               subLine = subLine.mid(posOfComma+2, subLine.length() );

               posOfComma= subLine.indexOf(",");
               temp= (subLine.mid(0, posOfComma)).toStdString();
               temp=temp[temp.length()-1];
               if (temp == "1") flag3=1;
               else flag3=0;
               ans=subLine.mid(0, posOfComma -1 );
               answer3->setText(ans);
               subLine = subLine.mid(posOfComma+2, subLine.length() );

               posOfComma= subLine.indexOf(".");
               temp= (subLine.mid(0, posOfComma)).toStdString();
               temp=temp[temp.length()-1];
               if (temp == "1") flag4=1;
               else flag4=0;
               ans=subLine.mid(0, posOfComma -1 );
               answer4->setText(ans);


               break;
        }
        lineCount++;
    }
  }
  questionsList.close();
}

/**
* \brief Connects the 4 buttons of the answers to their corresponding signals depending on whether the button holds the correct answer or not
* \param no input argument
* \return no return value
*/
void questionPopScreen::connectSlots(){

    QObject::connect(apply, SIGNAL(clicked(bool)), this, SLOT(changeTopic()));

    if (flag1==1){ //flag==1 means that this is the correct answer
        QObject::connect(answer1, SIGNAL(clicked(bool)), this, SLOT(clickedOnRightAns()));
        oldFlag1=1; //save this flag as old flag so that the next time we choose a question, we can disconnect the button from the previous signal and attach it to the new signal.
   }
   if (flag1==0){
        QObject::connect(answer1, SIGNAL(clicked(bool)), this, SLOT(clickedOnWrongAns()));
        oldFlag1=0;
   }
    if (flag2==1){
        QObject::connect(answer2, SIGNAL(clicked(bool)), this, SLOT(clickedOnRightAns()));
        oldFlag2=1;
    }
    if (flag2==0){
        QObject::connect(answer2, SIGNAL(clicked(bool)), this, SLOT(clickedOnWrongAns()));
        oldFlag2=0;
    }
    if (flag3==1){
        QObject::connect(answer3, SIGNAL(clicked(bool)), this, SLOT(clickedOnRightAns()));
        oldFlag3=1;
    }
    if (flag3==0){
        QObject::connect(answer3, SIGNAL(clicked(bool)), this, SLOT(clickedOnWrongAns()));
        oldFlag3=0;
    }
    if (flag4==1){
        QObject::connect(answer4, SIGNAL(clicked(bool)), this, SLOT(clickedOnRightAns()));
        oldFlag4=1;
    }
    if(flag4==0){
        QObject::connect(answer4, SIGNAL(clicked(bool)), this, SLOT(clickedOnWrongAns()));
        oldFlag4=0;
    }
}

/**
* \brief Disconnects the 4 buttons of the answers from their previous signals to be able to connect them to new signals, If the button where not connected, this function returns void.
* \param no input argument
* \return no return value
*/
void questionPopScreen::disconnectSlots(){

    if (oldFlag1==-1) return ;

    if (oldFlag1==1){
        QObject::disconnect(answer1, SIGNAL(clicked(bool)), this, SLOT(clickedOnRightAns()));
   }
   if (oldFlag1==0){
        QObject::disconnect(answer1, SIGNAL(clicked(bool)), this, SLOT(clickedOnWrongAns()));
   }
    if (oldFlag2==1){
        QObject::disconnect(answer2, SIGNAL(clicked(bool)), this, SLOT(clickedOnRightAns()));
    }
    if (oldFlag2==0){
        QObject::disconnect(answer2, SIGNAL(clicked(bool)), this, SLOT(clickedOnWrongAns()));
    }
    if (oldFlag3==1){
        QObject::disconnect(answer3, SIGNAL(clicked(bool)), this, SLOT(clickedOnRightAns()));
    }
    if (oldFlag3==0){
        QObject::disconnect(answer3, SIGNAL(clicked(bool)), this, SLOT(clickedOnWrongAns()));
    }
    if (oldFlag4==1){
        QObject::disconnect(answer4, SIGNAL(clicked(bool)), this, SLOT(clickedOnRightAns()));
    }
    if(oldFlag4==0){
        QObject::disconnect(answer4, SIGNAL(clicked(bool)), this, SLOT(clickedOnWrongAns()));
    }

}

/**
* \brief Sets the styleSheet from the buttons and text
* \param no input argument
* \return no return value
*/
void questionPopScreen::setColors()
{
    if (flagConstruct==0) return;

    question->setStyleSheet("color: #F0EDE5;font-size:20px;");
    question->setWordWrap(true);
    apply->setStyleSheet("color:#F0EDE5;border-radius:12px;"
        "padding:6px;font-size:16px; background-color:orange;");
    answer1->setStyleSheet("color:#F0EDE5; border-radius:12px;padding:6px;"
      "font-size:16px; background-color:orange;");
    answer2->setStyleSheet("color:#F0EDE5;border-radius:12px;"
        "padding:6px;""font-size:16px; background-color:orange;");
    answer3->setStyleSheet("color:#F0EDE5;border-radius:12px;"
        "padding:6px;font-size:16px; background-color:orange;");
    answer4->setStyleSheet("color:#F0EDE5;border-radius:12px;"
        "padding:6px;font-size:16px; background-color:orange;");
    chooseTopic->setStyleSheet("color:#F0EDE5;border-radius:12px;padding:6px;font-size:16px; background-color:orange;");
}

/**
* \brief Adds all the items to the layout of the widget
* \param no input argument
* \return no return value
*/
void questionPopScreen:: setGridLayout(){

    if (flagConstruct ==0) return;

    chooseTopic->addItem("Not specified");
    chooseTopic->addItem("Debugging");
    chooseTopic->addItem("version control");
    chooseTopic->addItem("OOP");
    verticalLayout->addWidget(chooseTopic);
    verticalLayout->addWidget(apply);
    verticalLayout->addWidget(question);
    gridLayout->addWidget(answer1, 1, 0);
    gridLayout->addWidget(answer2, 3, 0);
    gridLayout->addWidget(answer3, 1, 2);
    gridLayout->addWidget(answer4, 3, 2);
    gridLayout->addItem(new QSpacerItem(100, 10), 2,0 );
    gridLayout->addItem(new QSpacerItem(100, 10), 1,1 );
    gridLayout->addItem(new QSpacerItem(100, 10), 3,1 );
    verticalLayout->addItem(gridLayout);
    setLayout(verticalLayout);

    flagConstruct=0;

}

/**
* \brief Called when user selects the right answer, it increases the score, play the firing sound, and shows the image of the hit
* \param no input argument
* \return no return value
*/
void questionPopScreen::clickedOnRightAns()
{
    game->show();
    game->score++;
    game->scene->updateScore();

    QGraphicsPixmapItem* missOrHit = new QGraphicsPixmapItem;
    missOrHit-> setPixmap( (QPixmap(":/images/hit.png")).scaled(50,50));
    missOrHit->setPos(this->squareToHit->x(),this->squareToHit->y());
    game->scene->addItem(missOrHit);
    music->play();
    this->hide();

}

/**
* \brief Called when user selects a wrong answers. It calls the function that allows the enemy to fire from the PlayGame1 class.
* \param no input argument
* \return no return value
*/
void questionPopScreen::clickedOnWrongAns(){

    this->squareToHit->used=0;
    game->show();
    game->scene->enemyAttack();
    this->hide();

}

/**
* \brief Called when user changes the topic of the question. This function calls selectQuestion function after updating the topic.
* \param no input argument
* \return no return value
*/
void questionPopScreen::changeTopic(){

    if (topic != chooseTopic->currentText()){
       topic=chooseTopic->currentText();
       selectQuestion();
    }
    //else
      //  QMessageBox::information(this,"!!!","Topic already chosen");
}

/**
* \brief This function prepares the components of the widget by calling the other functions from this class
* \param no input argument
* \return no return value
*/
void questionPopScreen::prepareScreen(GrideSquare* squareToHitI){

    this->squareToHit = squareToHitI;
    selectQuestion();
    setColors();
    setGridLayout();
    setFixedSize(500,400);
    disconnectSlots();
    connectSlots();
    show();
}
