#ifndef HistogramUI_H
#define HistogramUI_H

#include <QWidget>

class QPushButton;

namespace Ui {
class HistogramUI;
}

class HistogramUI final : public QWidget
{
    Q_OBJECT

public:
    explicit HistogramUI(QWidget *parent = nullptr);
    ~HistogramUI();

private:
    Ui::HistogramUI *ui;
    QPushButton* pb;
};

#endif // HistogramUI_H
