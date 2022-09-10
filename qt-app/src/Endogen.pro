QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../journal/src/histogram/histogram.cpp \
    ../../journal/src/journal.cpp \
    ../../journal/src/table/table.cpp \
    ../../users/src/users.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../../journal/src/histogram/histogram.h \
    ../../journal/src/journal.h \
    ../../journal/src/table/table.h \
    ../../users/src/users.h \
    mainwindow.h

FORMS += \
    ../../journal/src/histogram/histogram.ui \
    ../../journal/src/journal.ui \
    ../../journal/src/table/table.ui \
    ../../users/src/users.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
