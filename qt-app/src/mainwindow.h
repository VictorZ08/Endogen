#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void connectSlots() const;

private slots:
    void m_inhale_le(int val);
    void m_preloadBelly_le(int val);
    void m_countDown_cb(int chek);
    void updateTimerWorkout();


    void m_start_pb();
    void m_pause_pb();
    void m_reset_pb();

private:
    Ui::MainWindow *ui;

    QTimer* m_timerWorkout = nullptr;
    QTime m_timeWorkout;
};
#endif // MAINWINDOW_H
