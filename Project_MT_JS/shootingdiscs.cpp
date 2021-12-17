#include "shootingdiscs.h"
#include "home.h"

// Reference for Images --> http://www.freepik.com
/**
 * \file shootingdiscs.cpp
 * \brief contains ShootingDiscs class definition
 * \param loggedInUser first argument, pointer to the currently logged in user name
 * \param loggedInUserObject second argument, pointer to the currently logged in user object
 */
ShootingDiscs::ShootingDiscs(QString* loggedInUser, QStringList* loggedInUserObject, QWidget *parent)
{

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-this->width()) / 2;
    int y = (screenGeometry.height()-this->height()) / 2;
    this->move(x, y);

    Q_UNUSED(parent);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    if (loggedInUser != nullptr && loggedInUserObject != nullptr)
        scene = new ShootingDiscsScene(loggedInUser, loggedInUserObject);
    else
        scene = new ShootingDiscsScene(nullptr, nullptr);
    scene->setSceneRect(0,0,600,900);
    setScene(scene);


    connect(scene, &ShootingDiscsScene::hideView, [this](){
       this->hide();
    });


    QAction *pressF1ToStart = new QAction(this);
    pressF1ToStart->setShortcut(Qt::Key_F1);

    connect(pressF1ToStart, SIGNAL(triggered()), scene, SLOT(onStartGameClicked()));
    this->addAction(pressF1ToStart);

}
/**
 * \brief passing mouse press event input to graphics view object
 * \param event first argument for the mouse press event
 */
void ShootingDiscs::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}

