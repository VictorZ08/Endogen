#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>

class JournalWidget;

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
    void m_currentDA_pb();
    void updateTimerWorkout();

    void m_showJournal_menu();

    void m_start_pb();
    void m_pause_pb();
    void m_reset_pb();

private:
    Ui::MainWindow *ui = nullptr;
    std::unique_ptr<JournalWidget> m_ptrJournalWidget;

    QTimer* m_timerWorkout = nullptr;
    QTimer* m_timerInhale = nullptr;
    QTime m_timeWorkout;

    int m_stepInhaleProgress = 1;
    int m_stepDAProgress = 0;
};
#endif // MAINWINDOW_H
