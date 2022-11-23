QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../database/database.cpp \
    ../../journal/src/histogram/histogramUI.cpp \
    ../../journal/src/journalUI.cpp \
    ../../journal/src/rowdata.cpp \
    ../../journal/src/tablemodel.cpp \
    ../../users/src/authorizeusersUI.cpp \
    ../../users/src/registeruserUI.cpp \
    ../../users/src/userslistmodel.cpp \
    main.cpp \
    mainwindow.cpp \

HEADERS += \
    ../../database/database.h \
    ../../journal/src/histogram/histogramUI.h \
    ../../journal/src/journalUI.h \
    ../../journal/src/noteditabledelegate.h \
    ../../journal/src/rowdata.h \
    ../../journal/src/tablemodel.h \
    ../../users/src/authorizeusersUI.h \
    ../../users/src/registeruserUI.h \
    ../../users/src/userslistmodel.h \
    mainwindow.h \

FORMS += \
    ../../journal/src/histogram/histogramUI.ui \
    ../../journal/src/journalUI.ui \
    ../../users/src/authorizeusersUI.ui \
    ../../users/src/registeruserUI.ui \
    mainwindow.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../../journal/icon/1.qrc
