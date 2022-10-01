#include "journalwidget.h"
#include "ui_journalwidget.h"

#include "../../journal/src/histogram/histogramwidget.h"

#include <QDebug>

#include <QStringListModel>

JournalWidget::JournalWidget(QWidget *parent)
            : QWidget(parent)
            , ui(new Ui::JournalWidget)
            , m_ptrHistogramWidget{std::make_unique<HistogramWidget>()}
{
    ui->setupUi(this);

    connectSlots();

    test();

    qDebug() << "JournalWidget";
}

JournalWidget::~JournalWidget()
{
    delete ui;
    qDebug() << "~JournalWidget";
}

void JournalWidget::connectSlots()
{
    connect(ui->m_reviewHistogram_pb, SIGNAL(clicked()),
            this, SLOT(m_hisogramShow()));
}

void JournalWidget::m_hisogramShow()
{
    m_ptrHistogramWidget->show();
    qDebug() << "m_hisogrammShow";
}

void JournalWidget::test()
{
    QStringList numbers;
    numbers << "One" << "Two" << "Three" << "Four" << "Five";
    model = new QStringListModel(numbers);
    ui->m_journal_tv->setModel(model);
}









