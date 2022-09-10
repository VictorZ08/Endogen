#ifndef JOURNAL_H
#define JOURNAL_H

#include <QWidget>

namespace Ui {
class Journal;
}

class Journal : public QWidget
{
    Q_OBJECT

public:
    explicit Journal(QWidget *parent = nullptr);
    ~Journal();

private:
    Ui::Journal *ui;
};

#endif // JOURNAL_H
