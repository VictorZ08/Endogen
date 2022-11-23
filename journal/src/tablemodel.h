#ifndef TableModel_H
#define TableModel_H

#include <QAbstractTableModel>
#include <QDate>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject* parent = nullptr);
    ~TableModel();

    void setRotateIcon(const int row);
    void copy(const QModelIndexList& inModelsIdx);
    void past(const QModelIndexList& inModelsIdx);
    void clear(const QModelIndexList& inModelsIdx);

    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;

private:
    void refreshModel();
    int numIcon(const int row) const;
    virtual QVariant data(const QModelIndex& index,
                          int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex & index,
                         const QVariant & value, int role) override;
    virtual QVariant headerData(int section,
                                Qt::Orientation orientation,
                                int role) const override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    QString m_dataCells[30][8];
    QString m_idTable;
};

#endif // TableModel_H
