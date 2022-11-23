#include "database.h"

#include <QMessageBox>
#include "QDir"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include "QDebug"

const QString nameTableUsers = "TableUsers";

DataBase::DataBase(QObject *parent)
            : QObject{ parent }
{
    qDebug() << "Create DataBase";
}

DataBase::~DataBase()
{
    qDebug() << "~DataBase";
}

bool DataBase::connectToDataBase()
{
    if(!QFile(QDir::currentPath()+"/db/db.sql").exists())
    {
        if(this->restoreDataBase())
            return openDataBase();
    } else {
        return openDataBase();
    }
    return false;
}

bool DataBase::restoreDataBase()
{    
    if(this->messageError())
    {
        createDataBase();
    }
    return false;
}

bool DataBase::messageError()
{
    QString pathDB = QDir::currentPath() + "/db/db.sql";
    QMessageBox msgBox;
    msgBox.setText("Файл: " + pathDB+ " не найден!");
    msgBox.setInformativeText("Создать новый файл для базы данных?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);

    int ret = msgBox.exec();
    switch (ret) {
      case QMessageBox::Ok:
        return true;
      case QMessageBox::Cancel:
        return false;
    }
    return false;
}

bool DataBase::createDataBase()
{
    QString pathDB = QDir::currentPath() + "/db/db.sql";
    QFile file(pathDB);
    if (!file.open(QIODevice::ReadOnly | QIODevice::WriteOnly)) {
        qDebug() << "Не удалось создать файл бд!";
        return false;
    }
    file.close();
    return true;
}

bool DataBase::openDataBase()
{
    QString pathDB = QDir::currentPath() + "/db/db.sql";
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setHostName("EndogenDB");
    m_db.setDatabaseName(pathDB);
    if (!m_db.open()) {
        qDebug() << "Cannot open database:" << m_db.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::inserIntoTableJournal(const QVariantList& data,
                                     const QString &nameTableJournal)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " + nameTableJournal +
                  " ("
                         "Date"      " TEXT      PRIMARY KEY,"
                         "Water"     " INTEGER   ,"
                         "Inhale"    " INTEGER   ,"
                         "Exhale"    " INTEGER   ,"
                         "PDA"       " INTEGER   ,"
                         "Workout"   " INTEGER   ,"
                         "NumICON"   " INTEGER   ,"
                         "IdTable"   " TEXT      PRIMARY KEY,"
                  " )"
                  "VALUES (:Date, :Water, :Inhale, :Exhale, "
                          ":PDA, :Workout, :NumICON, :IdTable )");
    query.bindValue(":Date",    data[0].toString());
    query.bindValue(":Water",   data[1].toString());
    query.bindValue(":Inhale",  data[2].toString());
    query.bindValue(":Exhale",  data[3].toString());
    query.bindValue(":PDA",     data[4].toString());
    query.bindValue(":Workout", data[5].toString());
    query.bindValue(":NumICON", data[6].toString());
    query.bindValue(":IdTable", data[7].toString());
    // После чего выполняется запросом методом exec()
    if(!query.exec()) {
        qDebug() << "error insert into " << nameTableJournal;
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::inserIntoTableUser(const QString& inNameUser)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " + nameTableUsers +
                  " ("
                        "nameUser"
                  " )"
                  "VALUES (:nameUser)");
    query.bindValue(":nameUser",    inNameUser);
    // После чего выполняется запросом методом exec()
    if(!query.exec()) {
        qDebug() << "error insert into " << inNameUser;
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::createTableJournal(const QString& nameTableJournal)
{
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " + nameTableJournal +
                    " ("
                            "Date"      " TEXT      PRIMARY KEY,"
                            "Water"     " INTEGER   ,"
                            "Inhale"    " INTEGER   ,"
                            "Exhale"    " INTEGER   ,"
                            "PDA"       " INTEGER   ,"
                            "Workout"   " INTEGER   ,"
                            "NumICON"   " INTEGER   ,"
                            "IdTable"   " TEXT      PRIMARY KEY,"
                    " )" ))
    {
        qDebug() << "DataBase: error of create " << nameTableJournal;
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

void DataBase::deleteUser(const QString& nameUser)
{
    QSqlQuery query;
    QString error = query.lastError().text();
    if (query.exec("DELETE FROM " + nameTableUsers +
                   " WHERE nameUser = '" + nameUser + "'"))
        qDebug() << "DELETE ok";
    else
        qDebug() << "DELETE no";
}

QStringList DataBase::dataUsers()
{
    createTableUser();

    QStringList users;
    QSqlQuery query;
    if(!query.exec("SELECT nameUser FROM " + nameTableUsers)) {
        qDebug() << "No open TableUsers";
    }
    int fieldNo = query.record().indexOf("nameUser");
    while (query.next())
        users.append(query.value(fieldNo).toString());

    return users;
}

bool DataBase::createTableUser()
{
    QSqlQuery query;
    if(!query.exec( "create table " + nameTableUsers +
                    "("
                         "nameUser varchar(20) PRIMARY KEY"
                    " )" ))
    {
        qDebug() << "DataBase: error of create " << nameTableUsers;
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

void DataBase::closeDataBase()
{
    m_db.close();
}

//bool DataBase::isEmpty()
//{
//    int size;
//    QSqlQuery query("SELECT count(*) FROM TableUsers WHERE type = 'table' AND name != 'android_metadata' AND name != 'sqlite_sequence';");
//        if (query.next()) {
//            size = query.value(0).toInt();
//            qDebug() << size;
//        }

//        return 0;
//        //QSqlQuery query("SELECT count(*) FROM sqlite_master WHERE type = 'table' AND name != 'android_metadata' AND name != 'sqlite_sequence';");
//}


