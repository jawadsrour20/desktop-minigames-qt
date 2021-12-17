#ifndef SCORESMODEL_H
#define SCORESMODEL_H

#include <QAbstractTableModel>
#include <QtWidgets>
#include <QDebug>

/**
* \file scoresmodel.h
* \brief ScoresModel class.
* Sets up the table view with the logged in user's scores and the global best scores for the 2 games
*
*/
class ScoresModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    // constructor
    explicit ScoresModel(QString* username = nullptr, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
private:
    QString loggedInUser;//!< logged in user name
    QStringList* battleshipUserScoresList;//!< pointer to battleship game scores list
    QStringList* shootingUserScoresList;//!< pointer to shooting game scores list
    int battleshipUserBestScore;//!< user's best score for battleship game
    int shootingUserBestScore;//!< user's best score for shooting discs game
    int battleshipGlobalBestScore;//!< global best score for battleship game
    int shootingGlobalBestScore;//!< global best score for shooting discs game
    int rowCounter;//!< counter for number of rows of history table

};

#endif // SCORESMODEL_H
