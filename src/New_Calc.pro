QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    View/creditwindow.cpp \
    View/graphwindow.cc \
    View/main.cc \
    View/mainwindow.cc \
    qcustomplot/qcustomplot.cc

HEADERS += \
    Controller/controller.h\
    View/creditwindow.h \
    View/graphwindow.h \
    View/mainwindow.h \
    Model/model_calculator.h \
    Model/model_credit.h \
    qcustomplot/qcustomplot.h


FORMS += \
    View/creditwindow.ui \
    View/graphwindow.ui \
    View/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../Makefile
