#include "journal.h"
#include "ui_journal.h"

Journal::Journal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Journal)
{
    ui->setupUi(this);
}

Journal::~Journal()
{
    delete ui;
}
