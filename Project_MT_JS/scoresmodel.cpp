#include "scoresmodel.h"



/**
 * \file scoresmodel.cpp
 * \brief contains ScoresModel class implementation
 * \param username first argument, pointer to the currently logged in user name
 *
 * Sets up the table view with the logged in user's scores and the global best scores for the 2 games
 */
ScoresModel::ScoresModel(QString* username, QObject *parent)
    : QAbstractTableModel(parent)
{

    if (username != nullptr)
        loggedInUser = (*username);


    battleshipUserBestScore = 0;
    shootingUserBestScore = 0;
    battleshipGlobalBestScore = 0;
    shootingGlobalBestScore = 0;

//    QFile* battleShipScoresFile = new QFile(QDir().absoluteFilePath("../Project_MT_JS/battleship_scores.txt"));
    QFile* battleShipScoresFile = new QFile(":/battleship_scores.txt");
    battleShipScoresFile->open(QIODevice::ReadOnly|QIODevice::Text);


    QTextStream in(battleShipScoresFile);

    while (!in.atEnd()) {
        QString tempUserString = in.readLine(); // 1 line == 1 record == 1 user
        QStringList tempUserList = tempUserString.split(" ");


        if (tempUserList[0] == loggedInUser)
        {

            battleshipUserScoresList = new QStringList(tempUserList);
            for(int i=1; i < tempUserList.size(); i++)
                if(tempUserList[i].toInt() >= battleshipUserBestScore)
                {
                    battleshipUserBestScore = tempUserList[i].toInt();
                }

        }
        for(int i=1; i < tempUserList.size(); i++)
            if(tempUserList[i].toInt() >= battleshipGlobalBestScore)
                battleshipGlobalBestScore = tempUserList[i].toInt();
    }
    battleShipScoresFile->close();


    QFile* shootingScoresFile = new QFile(":/shooting_scores.txt");
    shootingScoresFile->open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream in2(shootingScoresFile);


    while (!in2.atEnd()) {
        QString tempUserString = in2.readLine(); // 1 line == 1 record == 1 user
        QStringList tempUserList = tempUserString.split(" ");


        if (tempUserList[0] == loggedInUser)
        {
            shootingUserScoresList = new QStringList(tempUserList);
            for(int i=1; i < tempUserList.size(); i++)
                if(tempUserList[i].toInt() >= shootingUserBestScore)
                    shootingUserBestScore = tempUserList[i].toInt();
        }
        for(int i=1; i < tempUserList.size(); i++)
            if(tempUserList[i].toInt() >= shootingGlobalBestScore)
                shootingGlobalBestScore = tempUserList[i].toInt();
    }
    shootingScoresFile->close();

    // getting max nb of rows between two games

    rowCounter = battleshipUserScoresList->size() > shootingUserScoresList->size() ?
                battleShipScoresFile->size() : shootingUserScoresList->size();
    // first element is username we remove it from counter
    rowCounter--;



    qDebug() << "User shooting best score" << shootingUserBestScore;
    qDebug() << "Global shooting best score" << shootingGlobalBestScore;
    qDebug() << "User Battlehship best score" << battleshipUserBestScore;
    qDebug() << "Global battleship best score" << battleshipGlobalBestScore;
}

/**
 * \brief Gets the number of rows for the history table
 * \return int value of number of rows
 */
int ScoresModel::rowCount(const QModelIndex & /*parent*/) const
{
    return rowCounter;
}
/**
 * \brief Gets the number of columns for the history table
 * \return int value of number of columns
 */
int ScoresModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 6;
}

/**
 * \brief Sets the history table's data
 * \return QVariant for the data of the table
 */
QVariant ScoresModel::data(const QModelIndex &index, int role) const
{


    if (!index.isValid())
        return QVariant();

    int row = index.row();
    int col = index.column();

    if ( role == Qt::DisplayRole && row == 0 && col == 2)
        return QString(QString::number(battleshipUserBestScore));

    if ( role == Qt::DisplayRole && row == 0 && col == 3)
        return QString(QString::number(shootingUserBestScore));

    if (role == Qt::DisplayRole && row == 0 && col == 4)
        return QString(QString::number(battleshipGlobalBestScore));

    if (role == Qt::DisplayRole && row == 0 && col == 5)
        return QString(QString::number(shootingGlobalBestScore));

    if (role == Qt::FontRole && row == 0 && col == 4)
    {
        QFont boldFont;
        boldFont.setBold(true);
        return boldFont;
    }
    if (role == Qt::FontRole && row == 0 && col == 5)
    {
        QFont boldFont;
        boldFont.setBold(true);
        return boldFont;
    }

    if (role == Qt::BackgroundRole && row == 0 && col == 4)
    {
        return QBrush(Qt::yellow);
    }
    if (role == Qt::BackgroundRole && row == 0 && col == 5)
    {
        return QBrush(Qt::yellow);
    }


    if (role == Qt::BackgroundRole && row == 0 && col == 2)
    {
        return QBrush(Qt::red);
    }

    if (role == Qt::BackgroundRole && row == 0 && col == 3)
    {
        return QBrush(Qt::red);
    }

    for(int i=1; i < battleshipUserScoresList->size(); i++)
    {
        if (role == Qt::DisplayRole && row == (i-1) && col == 0)
            return (*battleshipUserScoresList)[i];
    }

    for(int i=1; i < shootingUserScoresList->size(); i++)
    {
        if (role == Qt::DisplayRole && row == (i-1) && col == 1)
            return (*shootingUserScoresList)[i];
    }

    return QVariant();

}
/**
 * \brief Sets the headers of the history table
 * \return QVariant for the header data of the table
 */
QVariant ScoresModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return tr("BS_Scores");

        case 1:
            return tr("SD_Scores");

        case 2:
            return tr("Best_BS_Score");
        case 3:
            return tr("Best_SD_Score");

        case 4:
            return tr("Global_BS");
        case 5:
            return tr("Global_SD");

        default:
            return QVariant();
        }
    }
    return QVariant();
}
