#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../../journal/src/journalUI.h"
#include <memory>

#include <QTimer>
#include <QDebug>

static bool flagDA = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_ptrJournalUI{std::make_unique<JournalUI>()}
    , m_timerWorkout{new QTimer(this)}
    , m_timerInhale{new QTimer(this)}
    , m_timeWorkout{QTime::fromString("00:00:00", "hh:mm:ss")}
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
    qDebug() << "~MainWindow";
}

void MainWindow::connectSlots() const
{
    connect(ui->m_inhale_sr, SIGNAL(valueChanged(int)),
            this, SLOT(m_inhale_le(int)));

    connect(ui->m_preloadBelly_sr, SIGNAL(valueChanged(int)),
            this, SLOT(m_preloadBelly_le(int)));

    connect(ui->m_countDown_cb, SIGNAL(stateChanged(int)),
            this, SLOT(m_countDown_cb(int)));

    connect(m_timerWorkout, SIGNAL(timeout()),
            this, SLOT(updateTimerWorkout()));

    connect(m_timerInhale, SIGNAL(timeout()),
            this, SLOT(m_currentDA_pb()));

    connect(ui->m_start_pb, SIGNAL(clicked()),
            this, SLOT(m_start_pb()));

    connect(ui->m_pause_pb, SIGNAL(clicked()),
            this, SLOT(m_pause_pb()));

    connect(ui->m_reset_pb, SIGNAL(clicked()),
            this, SLOT(m_reset_pb()));

    connect(ui->m_journal_an, SIGNAL(triggered()),
            this, SLOT(m_showJournal_menu()));
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
    if(chek) {
        m_timeWorkout.setHMS(0, 0, 0);
        int sec = ui->m_durationLesson_sb->text().toInt()*60;
        m_timeWorkout = m_timeWorkout.addSecs(sec);
    } else {
        m_timeWorkout.setHMS(0, 0, 0);
    }

    ui->m_timeWorkout_lcdN->display(m_timeWorkout.toString());
}

void MainWindow::m_currentDA_pb()
{
    if(ui->m_currentDA_pb->value() == ui->m_currentDA_pb->maximum()
       && flagDA == false)
    {
        m_timerInhale->stop();
        m_stepInhaleProgress = 0;
        int progress = 100 * ui->m_PDA_sb->text().toInt();
        ui->m_currentDA_pb->setMaximum(progress);
        flagDA = true;
        m_timerInhale->start();
    }
    else if(ui->m_currentDA_pb->value() == ui->m_currentDA_pb->maximum()
            && flagDA == true)
    {
        m_timerInhale->stop();
        m_stepInhaleProgress = 0;
        int progress = 100 *
                       ui->m_inhale_le->text().toDouble();
        ui->m_currentDA_pb->setMaximum(progress);
        flagDA = false;
        m_timerInhale->start();
    }

    ui->m_currentDA_pb->setValue(m_stepInhaleProgress);
    ui->m_currentDA_pb->update();
    ++m_stepInhaleProgress;
}

void MainWindow::updateTimerWorkout()
{
    if(ui->m_countDown_cb->isChecked()) {
        m_timeWorkout = m_timeWorkout.addSecs(-1);
    } else {
        m_timeWorkout = m_timeWorkout.addSecs(1);
    }
    ui->m_timeWorkout_lcdN->display(m_timeWorkout.toString());
}

void MainWindow::m_showJournal_menu()
{
    m_ptrJournalUI->show();
    qDebug() << "m_showJournal_menu";
}

void MainWindow::m_start_pb()
{
    ui->m_start_pb->setEnabled(false);
    ui->m_pause_pb->setEnabled(true);
    ui->m_reset_pb->setEnabled(true);
    ui->m_durationLesson_sb->setEnabled(false);
    ui->m_countDown_cb->setEnabled(false);

    int progress = 100 *
                   ui->m_inhale_le->text().toDouble();
    ui->m_currentDA_pb->setMaximum(progress);

    m_timerWorkout->start(std::chrono::seconds(1));
    m_timerInhale->start(std::chrono::milliseconds(10));
}

void MainWindow::m_pause_pb()
{
    ui->m_start_pb->setEnabled(true);
    ui->m_pause_pb->setEnabled(false);
    ui->m_reset_pb->setEnabled(true);
    m_timerWorkout->stop();

    m_timerInhale->stop();
    m_stepInhaleProgress = 0;
    ui->m_currentDA_pb->setValue(m_stepInhaleProgress);
    ui->m_currentDA_pb->update();
    int progress = 100 *
                   ui->m_inhale_le->text().toDouble();
    ui->m_currentDA_pb->setMaximum(progress);
    flagDA = false;
}

void MainWindow::m_reset_pb()
{
    ui->m_start_pb->setEnabled(true);
    ui->m_pause_pb->setEnabled(false);
    ui->m_reset_pb->setEnabled(false);
    ui->m_durationLesson_sb->setEnabled(true);
    ui->m_countDown_cb->setEnabled(true);
    m_timerWorkout->stop();

    if(ui->m_countDown_cb->isChecked()) {
        m_timeWorkout.setHMS(0, 0, 0);
        int sec = ui->m_durationLesson_sb->text().toInt()*60;
        m_timeWorkout = m_timeWorkout.addSecs(sec);
    } else {
        m_timeWorkout.setHMS(0, 0, 0);
    }

    ui->m_timeWorkout_lcdN->display(m_timeWorkout.toString());

    m_timerInhale->stop();
    m_stepInhaleProgress = 0;
    ui->m_currentDA_pb->setValue(m_stepInhaleProgress);
    ui->m_currentDA_pb->update();
    int progress = 100 *
                   ui->m_inhale_le->text().toDouble();
    ui->m_currentDA_pb->setMaximum(progress);
    flagDA = false;
}
















