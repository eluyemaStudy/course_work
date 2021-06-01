QT       += core gui

QT += qml   quick  widgets  charts  network quickcontrols2 svg
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GaussSeidel.cpp \
    Gradient.cpp \
    Jacoby.cpp \
    Matrix.cpp \
    Method.cpp \
    main.cpp \
    mainwindow.cpp \
    printgraph.cpp \
    solutionlog.cpp

HEADERS += \
    GaussSeidel.h \
    Gradient.h \
    Jacoby.h \
    Matrix.h \
    Method.h \
    mainwindow.h \
    printgraph.h \
    solutionlog.h

FORMS += \
    mainwindow.ui \
    printgraph.ui \
    solutionlog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
