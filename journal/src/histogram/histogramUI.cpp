#include "histogramUI.h"
#include "ui_histogramUI.h"

#include <QPushButton>
#include <QDebug>

HistogramUI::HistogramUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistogramUI)
{
    ui->setupUi(this);

    pb = new QPushButton(
                               "&Download", this);
    pb->setIcon(QIcon(":/1.png"));
    pb->setIconSize(QSize(25, 25));
    pb->show();
    qDebug() << "HistogramUI";
}

HistogramUI::~HistogramUI()
{
    delete ui;
    delete pb;
    qDebug() << "~HistogramUI";
}
