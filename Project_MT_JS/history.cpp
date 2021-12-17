#include "history.h"
#include "scoresmodel.h"
#include "home.h"


// References on Table View
// https://doc.qt.io/archives/4.6/itemviews-addressbook.html
// https://doc.qt.io/qt-5/modelview.html
/**
 * \file history.cpp
 * \brief contains History class definition
 *
 * History class contains the implementation that provides with a UI that
 * displays the leader-board stats for the viewing user and those of the top ranked user
 */
History::History(QString* loggedInUser, QStringList* loggedInUserObject, QWidget *parent) : QWidget(parent)
{

    setFixedSize(300, 300); //this is for the go back button

    this->setStyleSheet("background-color:#363945;");

    if (loggedInUserObject != nullptr && loggedInUser != nullptr) {

        this->loggedInUserObject = loggedInUserObject;
        this->loggedInUser = loggedInUser;
        tableView = new QTableView();
        tableView->setFixedSize(900,300);
        ScoresModel* scoresModel = new ScoresModel(loggedInUser);
        tableView->setModel(scoresModel);
        tableView->show();

    }
    else {

        tableView = new QTableView();
        tableView->setFixedSize(900,300);
        ScoresModel* scoresModel = new ScoresModel();
        tableView->setModel(scoresModel);
        tableView->show();

    }

    backButton = new QPushButton("GO BACK");
    QObject::connect(backButton, SIGNAL(clicked(bool)), this, SLOT(onBackClicked()));

    backButton->setStyleSheet("color:#F0EDE5;border-radius:12px;"
        "padding:6px;""font-size:16px; background-color:orange; font-size:40px;");
    gridLayout = new QGridLayout();

    gridLayout->addWidget(backButton, 0, 0);

    setLayout(gridLayout);
}

/**
 * \brief SLOT responding to the signal issued by the Back button
 * navigating the user back to the home-page
 */
void History::onBackClicked()
{
    Home* homePage = new Home(loggedInUserObject);
    homePage->show();
    tableView->hide();
    this->hide();
}
