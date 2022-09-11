#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>


#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_timerWorkout(new QTimer(this))
    , m_timeWorkout(QTime::fromString("00:00:00", "hh:mm:ss"))
{
    ui->setupUi(this);

    connectSlots();

    ui->m_timeWorkout_lcdN->display(m_timeWorkout.toString());

    ui->m_PDA_sb->setValue(15);
    ui->m_inhale_sr->valueChanged(ui->m_inhale_sr->value());
    ui->m_preloadBelly_sr->valueChanged(ui->m_preloadBelly_sr->value());
    ui->m_durationLesson_sb->setValue(15);

    QTime t1(5,40,32);
    qDebug() << t1.toString();
    //QTime t2(3,55,48);

    t1 = t1.addSecs(-332);
    qDebug() << t1.toString();
//    int m = t1.hour() - t2.hour();
//    int s = t1.hour() - t2.hour();
       qDebug() << "MainWindow";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectSlots() const
{
    connect(ui->m_inhale_sr, SIGNAL(valueChanged(int)),
            this, SLOT(m_inhale_le(int)));

    connect(ui->m_preloadBelly_sr, SIGNAL(valueChanged(int)),
            this, SLOT(m_preloadBelly_le(int)));

    connect(ui->m_countdown_cb, SIGNAL(stateChanged(int)),
            this, SLOT(m_countDown_cb(int)));

    connect(m_timerWorkout, SIGNAL(timeout()),
            this, SLOT(updateTimerWorkout()));

    connect(ui->m_start_pb, SIGNAL(clicked()),
            this, SLOT(m_start_pb()));

    connect(ui->m_pause_pb, SIGNAL(clicked()),
            this, SLOT(m_pause_pb()));

    connect(ui->m_reset_pb, SIGNAL(clicked()),
            this, SLOT(m_reset_pb()));
}

void MainWindow::m_inhale_le(int val)
{
    double res = val/10.0;
    ui->m_inhale_le->setText(QString::number(res, 'f', 1));
}

void MainWindow::m_preloadBelly_le(int val)
{
    if(val == 9) {
        ui->m_preloadBelly_le->setText("Выкл");
        return;
    }

    double res = val/10.0;
    ui->m_preloadBelly_le->setText(QString::number(res, 'f', 1));
}

void MainWindow::m_countDown_cb(int chek)
{
    if(ui->m_countdown_cb->isChecked()) {
        m_timeWorkout.setHMS(0, 0, 0);
        int sec = ui->m_durationLesson_sb->text().toInt()*60;
        m_timeWorkout = m_timeWorkout.addSecs(sec);
    } else {
        m_timeWorkout.setHMS(0, 0, 0);
    }

    ui->m_timeWorkout_lcdN->display(m_timeWorkout.toString());
    qDebug() << chek;
}

void MainWindow::updateTimerWorkout()
{
    if(ui->m_countdown_cb->isChecked()) {
        m_timeWorkout = m_timeWorkout.addSecs(-1);
    } else {
        m_timeWorkout = m_timeWorkout.addSecs(1);
    }
    ui->m_timeWorkout_lcdN->display(m_timeWorkout.toString());
    qDebug() << "updateTimerWorkout";
}

void MainWindow::m_start_pb()
{
    ui->m_start_pb->setEnabled(false);
    ui->m_pause_pb->setEnabled(true);
    ui->m_reset_pb->setEnabled(true);
    ui->m_countdown_cb->setEnabled(false);
    m_timerWorkout->start(std::chrono::seconds(1));
    qDebug() << "start";
}

void MainWindow::m_pause_pb()
{
    ui->m_start_pb->setEnabled(true);
    ui->m_pause_pb->setEnabled(false);
    ui->m_reset_pb->setEnabled(true);
    m_timerWorkout->stop();
    qDebug() << "pause";
}

void MainWindow::m_reset_pb()
{
    ui->m_start_pb->setEnabled(true);
    ui->m_pause_pb->setEnabled(false);
    ui->m_reset_pb->setEnabled(false);
    ui->m_countdown_cb->setEnabled(true);
    m_timerWorkout->stop();

    if(ui->m_countdown_cb->isChecked()) {
        m_timeWorkout.setHMS(0, 0, 0);
        int sec = ui->m_durationLesson_sb->text().toInt()*60;
        m_timeWorkout = m_timeWorkout.addSecs(sec);
    } else {
        m_timeWorkout.setHMS(0, 0, 0);
    }

    ui->m_timeWorkout_lcdN->display(m_timeWorkout.toString());
    qDebug() << "reset";
}
















