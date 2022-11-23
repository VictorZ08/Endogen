#include "authorizeusersUI.h"
#include "ui_authorizeusersUI.h"
#include "../../users/src/registeruserUI.h"
#include "../../users/src/userslistmodel.h"
#include "../../database/database.h"

#include <memory>
#include <QStringListModel>
#include <QSqlQuery>
#include <QSqlError>
#include "QDebug"

AuthorizeUsersUI::AuthorizeUsersUI(QWidget *parent)
                    : QWidget(parent)
                    , ui(new Ui::AuthorizeUsersUI)
                    , m_ptrRegUserUI{ std::make_unique<RegisterUserUI>() }
                    , m_ptrDataBase{ std::make_unique<DataBase>() }
                    , m_model{ new UsersListModel(this) }
{
    ui->setupUi(this);
    connectSlots();

    if(!m_ptrDataBase->connectToDataBase()) {
        ui->m_enterUser_pb->setEnabled(false);
        ui->m_createUser_pb->setEnabled(false);
        ui->m_deleteUser_pb->setEnabled(false);
        ui->m_statusDB_l->setText("Статус БД: База данных не подключена!");
    } else {
        ui->m_statusDB_l->setText("Статус БД: База данных подключена.");
    }

    m_model->setUsers( m_ptrDataBase->dataUsers() );
    ui->m_autorize_lv->setModel(m_model);

    qDebug() << "AuthorizeUsersUI";
}

AuthorizeUsersUI::~AuthorizeUsersUI()
{
    delete ui;
    qDebug() << "~AuthorizeUsersUI";
}

void AuthorizeUsersUI::connectSlots()
{
    connect(ui->m_enterUser_pb, SIGNAL(clicked()),
            this, SLOT(enterUser()));

    connect(ui->m_createUser_pb, SIGNAL(clicked()),
            this, SLOT(registerUser()));

    connect(ui->m_deleteUser_pb, SIGNAL(clicked()),
            this, SLOT(deleteUser()));

    connect(ui->m_quit_pb, SIGNAL(clicked()),
            this, SLOT(close()));

    connect(m_ptrRegUserUI.get(), SIGNAL(emitShowAuthorizeUsersUI()),
            this, SLOT(showUI()));

    connect(m_ptrRegUserUI.get(), SIGNAL(emitCreateUser(const QString&)),
            this, SLOT(createUser(const QString&)));
}

void AuthorizeUsersUI::registerUser()
{
    this->hide();
    m_ptrRegUserUI->show();
}

void AuthorizeUsersUI::enterUser()
{
    qDebug() << "enterUser";
}

void AuthorizeUsersUI::createUser(const QString& inNameUser)
{
    m_ptrDataBase->inserIntoTableUser(inNameUser);
    m_model->setUsers(m_ptrDataBase->dataUsers());
    m_model->refreshModel();
    ui->m_autorize_lv->setModel(m_model);
}

void AuthorizeUsersUI::deleteUser()
{
    auto select = ui->m_autorize_lv->selectionModel()->selectedIndexes();
    if(select.isEmpty())
        return;

    m_ptrDataBase->deleteUser(select.back().data().toString());
    m_model->setUsers(m_ptrDataBase->dataUsers());
    m_model->refreshModel();
    ui->m_autorize_lv->setModel(m_model);
}

void AuthorizeUsersUI::showUI()
{
    this->show();
}












