#include "../../users/src/authorizeusersUI.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AuthorizeUsersUI u;
    u.show();


    return a.exec();
}
