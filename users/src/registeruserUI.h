#ifndef REGISTERUSERUI_H
#define REGISTERUSERUI_H

#include <QWidget>

namespace Ui {
class RegisterUserUI;
}

class RegisterUserUI final : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterUserUI(QWidget *parent = nullptr);
    ~RegisterUserUI();


private:
    void connectSlots();

    virtual void closeEvent(QCloseEvent* inEvent) override;

private slots:
    void showAuthorizeUsersUI();
    void createUser();

signals:
    void emitShowAuthorizeUsersUI();
    void emitCreateUser(const QString&);

private:
    Ui::RegisterUserUI *ui = nullptr;
};

#endif // REGISTERUSERUI_H
