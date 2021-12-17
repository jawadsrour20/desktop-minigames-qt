#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>
#include <QtWidgets>
#include <QTableView>

/**
* \file history.h
* \brief History class
*
* This class provides user with a history page containing their stats for the games and the global best stats.
*/
class History : public QWidget
{
    Q_OBJECT
public:
    explicit History(QString* loggedInUser=nullptr, QStringList* loggedInUserObject=nullptr, QWidget *parent = nullptr);

private:

    QStringList* loggedInUserObject; //!< pointer to the currently logged in user object
    QPushButton* backButton; //!< pointer to the Back button that navigates back to the homepage
    QString* loggedInUser; //!< pointer to the currently logged in user name
    QGridLayout* gridLayout; //!< pointer to GridLayout object for the page
    QTableView* tableView; //!< pointer to QTableView object for history stats table


signals:


private slots:
    // slot called when Back button is clicked
    void onBackClicked();
};

#endif // HISTORY_H
