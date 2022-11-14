#include "journalUI.h"
#include "ui_journalUI.h"

#include "../../journal/src/histogram/histogramUI.h"
#include "../../journal/src/tablemodel.h"
#include "../../journal/src/noteditabledelegate.h"

#include <QDebug>

#include <QStandardItemModel>

JournalUI::JournalUI(QWidget *parent)
            : QWidget(parent)
            , ui{new Ui::JournalUI}
            , m_ptrHistogramWidget{std::make_unique<HistogramUI>()}
            , m_model{ new TableModel(this) }
{
    ui->setupUi(this);

    connectSlots();

    ui->m_journal_tv->setItemDelegateForColumn(0, new NotEditableDelegate(this));
    ui->m_journal_tv->setAlternatingRowColors(true);
    ui->m_journal_tv->setModel(m_model);
    ui->m_journal_tv->horizontalHeader()->setStretchLastSection(true);
    connect(ui->m_journal_tv, SIGNAL(clicked(const QModelIndex& )),
            this, SLOT(rotateIcon(const QModelIndex& )));

    qDebug() << "JournalUI";
}

JournalUI::~JournalUI()
{
    delete ui;
    qDebug() << "~JournalUI";
}

void JournalUI::connectSlots()
{
    connect(ui->m_reviewHistogram_pb, SIGNAL(clicked()),
            this, SLOT(m_hisogramShow()));

    connect(ui->m_copy_pb, SIGNAL(clicked()),
            this, SLOT(copy()));
    connect(ui->m_past_pb, SIGNAL(clicked()),
            this, SLOT(past()));
    connect(ui->m_clear_pb, SIGNAL(clicked()),
            this, SLOT(clear()));
}

void JournalUI::m_hisogramShow()
{
    m_ptrHistogramWidget->show();
}

void JournalUI::rotateIcon(const QModelIndex& index)
{
    if(index.column() != 0)
        return;

    m_model->setRotateIcon(index.row());
    ui->m_journal_tv->setModel(m_model);
}

void JournalUI::copy()
{
    auto indexes = ui->m_journal_tv->selectionModel()->selectedIndexes();
    m_model->copy(indexes);
}

void JournalUI::past()
{
    auto indexes = ui->m_journal_tv->selectionModel()->selectedIndexes();
    m_model->past(indexes);
}

void JournalUI::clear()
{
    auto indexes = ui->m_journal_tv->selectionModel()->selectedIndexes();
    m_model->clear(indexes);
    ui->m_journal_tv->update();
}









