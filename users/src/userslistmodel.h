#ifndef USERSLISTMODEL_H
#define USERSLISTMODEL_H

#include <QAbstractListModel>

class UsersListModel : public QAbstractListModel
{
public:
    UsersListModel(QObject *parent = nullptr);
    ~UsersListModel();

    void setUsers(const QStringList& inUsers);
    virtual int rowCount(const QModelIndex &) const override;
    void refreshModel();

private:
    virtual QVariant data(const QModelIndex &index,
                          int role = Qt::DisplayRole) const override;

private:
    QStringList m_users;
};

#endif // USERSLISTMODEL_H
