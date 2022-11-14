#ifndef NOTEDITABLEDELEGATE_H
#define NOTEDITABLEDELEGATE_H

#include <QStyledItemDelegate>

class NotEditableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit NotEditableDelegate( QObject *parent = nullptr )
                        : QStyledItemDelegate ( parent ) {}


    QWidget* createEditor( QWidget*,
                           const QStyleOptionViewItem&,
                           const QModelIndex& ) const { return 0; }
};


#endif // NOTEDITABLEDELEGATE_H
