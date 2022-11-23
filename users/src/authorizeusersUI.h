#ifndef AuthorizeUsersUIUI_H
#define AuthorizeUsersUIUI_H

#include <QWidget>

class RegisterUserUI;
class DataBase;
class UsersListModel;

namespace Ui {
class AuthorizeUsersUI;
}

class AuthorizeUsersUI final : public QWidget
{
    Q_OBJECT

public:
    explicit AuthorizeUsersUI(QWidget *parent = nullptr);
    ~AuthorizeUsersUI();

private:
    void connectSlots();

private slots:
    void registerUser();
    void enterUser();
    void createUser(const QString& inNameUser);
    void deleteUser();
    void showUI();

//signals:
//    void emitBackAuthorizeUsersUi();

private:
    Ui::AuthorizeUsersUI *ui = nullptr;
    std::unique_ptr<RegisterUserUI> m_ptrRegUserUI;

    std::unique_ptr<DataBase> m_ptrDataBase;
    UsersListModel* m_model = nullptr;
};

#endif // AuthorizeUsersUIUI_H
