#include "tablemodel.h"
//#include "../../journal/src/rowdata.h"

#include "QFont"
//#include "QBrush"
#include "QIcon"
#include "QDebug"
#include "QStandardItem"

QVariantList valCells;

TableModel::TableModel(QObject* parent)
            : QAbstractTableModel(parent)
{
    //Идентифицируем созданную таблицу датой
    m_dataCells[0][7] = QDate::currentDate().toString("MM.yyyy");
    //Для информации помещаем дату и время создания таблицы
    m_dataCells[1][7] =  QDateTime::currentDateTime().toString("dd.MM.yyyy в hh:mm");

    int rows = QDate::currentDate().daysInMonth();

    for(int row = 0; row < rows; ++row) {
        m_dataCells[row][6] = "0";
        m_dataCells[row][0] = QString("%1.%2.%3")
                                    .arg(row+1)
                                    .arg(QDate::currentDate().month())
                                    .arg(QDate::currentDate().year());
    }
}

int TableModel::rowCount(const QModelIndex& /*parent*/) const
{
   return QDate::currentDate().daysInMonth();
}

int TableModel::columnCount(const QModelIndex& /*parent*/) const
{
    return 6;
}

void TableModel::refreshModel()
{
    beginResetModel();
    endResetModel();
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int col = index.column();
    switch (role)
    {
        case Qt::DisplayRole:
            if(col == 0)
                return m_dataCells[row][col];
             else
                return m_dataCells[row][col];

            break;

        case Qt::FontRole:
            if (col == 0) { // change font only for cell(0,0)
                QFont boldFont;
                boldFont.setItalic(true);
                boldFont.setBold(true);
                return boldFont;
            }
            break;

//        case Qt::BackgroundRole:
//            if (row < QDate::currentDate().day()-1) {  // change background only for cell(1,2)
//                //QLinearGradient linearGrad(QPointF(1, 1), QPointF(30, 50));
//                //linearGrad.setColorAt(0, Qt::black);
//                //linearGrad.setColorAt(1, Qt::white);
//                //linearGrad.setColorAt(1, Qt::green);

//                return QBrush(Qt::lightGray);
//            }
//            break;

        case Qt::TextAlignmentRole:
                return int(Qt::AlignHCenter | Qt::AlignVCenter);
            break;

        case Qt::DecorationRole:
            if (col == 0) {
                switch (numIcon(index.row())) {
                    case 0: return QIcon(":/1.png");
                    case 1: return QIcon(":/2.png");
                    case 2: return QIcon(":/3.png");
                }
                break;
            }
    }
    return QVariant();
}

bool TableModel::setData(const QModelIndex & index,
                         const QVariant & value, int role)
{
    if (role == Qt::EditRole)
    {
        m_dataCells[index.row()][index.column()] = value.toString();
    }
    return true;
}

QVariant TableModel::headerData(int section,
                             Qt::Orientation orientation,
                             int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section)
        {
            case 0:
                return QString("Дата:");
            case 1:
                return QString("Вода,мл:");
            case 2:
                return QString("Вдох, сек:");
            case 3:
                return QString("Выдох, сек:");
            case 4:
                return QString("ПДА, сек:");
            case 5:
                return QString("Тренировка, мин:");
            case 6:
                return QString("Примечание:");
            default:
                break;
        }
    }

    //Устанавливаем шрифт
    switch (role)
    {
        case Qt::FontRole:
            QFont boldFont;
            boldFont.setItalic(true);
            boldFont.setBold(true);
            return boldFont;
    }

    return QVariant();
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable |
           Qt::ItemIsEditable |
           Qt::ItemIsEnabled | QAbstractTableModel::flags(index);
}

void TableModel::setRotateIcon(const int row)
{
    int limitIcon = 3;
    int flag = m_dataCells[row][6].toInt();
    ++flag;
    if(flag == limitIcon)
        flag = 0;

    m_dataCells[row][6] = QString::number(flag);
}

void TableModel::copy(const QModelIndexList& inModelsIdx)
{
    for (const auto &index : inModelsIdx) {
        valCells.append(index.data());
    }
}

void TableModel::past(const QModelIndexList& inModelsIdx)
{
    QVariantList::Iterator it = valCells.begin();
    for (const auto& index : inModelsIdx) {
        if(!index.isValid())
            return;

        if(it == valCells.end())
            it = valCells.begin();

        this->setData(index, it->toString(), 2);
        ++it;
    }
    refreshModel();
}

void TableModel::clear(const QModelIndexList &inModelsIdx)
{

    for (const auto &index : inModelsIdx) {
        this->setData(index, "", 2);
    }
    refreshModel();
}

int TableModel::numIcon(const int row) const
{
    return m_dataCells[row][6].toInt();
}










