#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connectSlots();

    QTime time = QTime::currentTime();
       QString text = time.toString("hh:mm:ss");
       if ((time.second() % 2) == 0)
           text[2] = ' ';

       ui->m_timeWorkout_lcdN->display(text);

    ui->m_PDA_sb->setValue(15);
    ui->m_inhale_sr->valueChanged(ui->m_inhale_sr->value());
    ui->m_preloadBelly_le->setText("0");
    ui->m_durationLesson_sb->setValue(15);

       qDebug() << "MainWindow";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectSlots() const
{
    connect(ui->m_inhale_sr, SIGNAL(valueChanged(int)),
            this, SLOT(changedInhale(int)));

    connect(ui->m_start_pb, SIGNAL(clicked()),
            this, SLOT(start()));
}

void MainWindow::changedInhale(int val)
{
    double res = val/10.0;
    ui->m_inhale_le->setText(QString::number(res, 'f', 1));
    qDebug() << val;
}

void MainWindow::start()
{
    qDebug() << "qqqqq";
}

