#ifndef JOURNALWIDGET_H
#define JOURNALWIDGET_H

#include <QWidget>

#include <QAbstractItemModel>
class HistogramWidget;

namespace Ui {
class JournalWidget;
}

class JournalWidget : public QWidget
{
    Q_OBJECT

public:
    explicit JournalWidget(QWidget *parent = nullptr);
    ~JournalWidget();

private:
    void connectSlots();

private slots:
    void m_hisogramShow();

private:
    Ui::JournalWidget *ui;
    std::unique_ptr<HistogramWidget> m_ptrHistogramWidget;

    QAbstractItemModel *model;

    void test();
};

#endif // JOURNALWIDGET_H
