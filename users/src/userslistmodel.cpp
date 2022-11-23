#include "userslistmodel.h"
#include "QDebug"

UsersListModel::UsersListModel(QObject *parent)
                    : QAbstractListModel(parent)
{
    qDebug() << "UsersListModel";
}

UsersListModel::~UsersListModel()
{
    qDebug() << "~UsersListModel";
}

void UsersListModel::setUsers(const QStringList& inUsers)
{
    m_users = inUsers;
}

int UsersListModel::rowCount(const QModelIndex &) const
{
    return m_users.count();
}

QVariant UsersListModel::data( const QModelIndex &index, int role ) const
{

    QVariant value;

        switch ( role )
        {
            case Qt::DisplayRole: //string
            {
                value = m_users.at(index.row());
            }
            break;

            case Qt::UserRole: //data
            {
                value = m_users.at(index.row());
            }
            break;

            default:
                break;
        }

    return value;
}

void UsersListModel::refreshModel()
{
    beginResetModel();
    endResetModel();
}
