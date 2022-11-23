#include "registeruserUI.h"
#include "ui_registeruserUI.h"

#include "QDebug"

RegisterUserUI::RegisterUserUI(QWidget *parent)
                : QWidget(parent)
                , ui(new Ui::RegisterUserUI)
{
    ui->setupUi(this);


    connectSlots();

    qDebug() << "RegisterUserUI";
}

RegisterUserUI::~RegisterUserUI()
{
    delete ui;
    qDebug() << "~RegisterUserUI";
}

void RegisterUserUI::connectSlots()
{
    connect(ui->m_cancel_pb, SIGNAL(clicked()),
            this, SLOT(showAuthorizeUsersUI()));

    connect(ui->m_create_pb, SIGNAL(clicked()),
            this, SLOT(createUser()));
}

void RegisterUserUI::closeEvent(QCloseEvent *inEvent)
{
    Q_UNUSED(inEvent)
    this->hide();
    emit emitShowAuthorizeUsersUI();
}

void RegisterUserUI::showAuthorizeUsersUI()
{
    this->hide();
    emit emitShowAuthorizeUsersUI();
}

void RegisterUserUI::createUser()
{
    QString input(ui->m_inputUser_le->text());
    emit emitCreateUser(input);
    showAuthorizeUsersUI();
}


















