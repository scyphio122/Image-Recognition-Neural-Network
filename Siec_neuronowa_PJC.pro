#-------------------------------------------------
#
# Project created by QtCreator 2015-03-30T18:29:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Siec_neuronowa_PJC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    layer.cpp \
    neuron.cpp \
    bias.cpp \
    commonneuron.cpp \
    connection.cpp \
    filehandler.cpp \
    network.cpp \
    create_network.cpp

HEADERS  += mainwindow.h \
    layer.h \
    neuron.h \
    bias.h \
    commonneuron.h \
    connection.h \
    filehandler.h \
    network.h \
    create_network.h

FORMS    += mainwindow.ui \
    create_network.ui

INCLUDEPATH += D:\opencv-mingw\install\include
LIBS += -L D:/opencv-mingw/install/x64/mingw/bin”
LIBS += -lopencv_core249 -lopencv_highgui249 -lopencv_imgproc249
