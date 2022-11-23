#ifndef JournalUI_H
#define JournalUI_H

#include <QWidget>

class HistogramUI;
class TableModel;

namespace Ui {
class JournalUI;
}

class JournalUI final : public QWidget
{
    Q_OBJECT

public:
    explicit JournalUI(QWidget *parent = nullptr);
    ~JournalUI();

private:
    void connectSlots();

private slots:
    void m_hisogramShow();
    void rotateIcon(const QModelIndex &index);

    void copy();
    void past();
    void clear();

private:
    Ui::JournalUI *ui = nullptr;
    std::unique_ptr<HistogramUI> m_ptrHistogramUI;

    TableModel* m_model = nullptr;
};

#endif // JournalUI_H
