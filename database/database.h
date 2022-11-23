#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();

    bool connectToDataBase();
    bool inserIntoTableJournal(const QVariantList& data,
                               const QString& nameTableJournal);
    bool inserIntoTableUser(const QString& inNameUser);
    bool createTableJournal(const QString& nameTableJournal);
    void deleteUser(const QString& nameUser);
    void closeDataBase();
    //bool isEmpty();

    QStringList dataUsers();

private:
    bool messageError();
    bool createDataBase();
    bool createTableUser();
    bool openDataBase();
    bool restoreDataBase();

private:
    QSqlDatabase m_db;
    //QString m_nameTable;
    //QStringList m_nameTableUsers;
};

#endif // DATABASE_H
