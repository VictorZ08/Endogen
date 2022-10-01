#include "histogramwidget.h"
#include "ui_histogramwidget.h"

#include <QDebug>

HistogramWidget::HistogramWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistogramWidget)
{
    ui->setupUi(this);

    qDebug() << "HistogramWidget";
}

HistogramWidget::~HistogramWidget()
{
    delete ui;
    qDebug() << "~HistogramWidget";
}
