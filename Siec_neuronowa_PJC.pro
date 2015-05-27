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
    create_network_dialog.cpp \
    teacher.cpp \
    image.cpp \
    imageparameters.cpp \
    classifier.cpp

HEADERS  += mainwindow.h \
    layer.h \
    neuron.h \
    bias.h \
    commonneuron.h \
    connection.h \
    filehandler.h \
    network.h \
    create_network_dialog.h \
    teacher.h \
    image.h \
    imageparameters.h \
    classifier.h

FORMS    += mainwindow.ui \
    create_network.ui

INCLUDEPATH += D:/OpenCV_RELEASE_2.4.10_x86/install/include \
                D:/OpenCV_RELEASE_2.4.10_x86/install/include/opencv \
                D:/OpenCV_RELEASE_2.4.10_x86/install/include/opencv2

DEPENDPATH  += D:/OpenCV_RELEASE_2.4.10_x86/install/x64/include

LIBS += D:/OpenCV_RELEASE_2.4.10_x86/install/x64/mingw/lib/libopencv_highgui2410.dll.a
LIBS += D:/OpenCV_RELEASE_2.4.10_x86/install/x64/mingw/lib/libopencv_core2410.dll.a
LIBS += D:/OpenCV_RELEASE_2.4.10_x86/install/x64/mingw/lib/libopencv_imgproc2410.dll.a
LIBS += D:/OpenCV_RELEASE_2.4.10_x86/install/x64/mingw/lib/libopencv_calib3d2410.dll.a
LIBS += D:/OpenCV_RELEASE_2.4.10_x86/install/x64/mingw/lib/libopencv_contrib2410.dll.a
LIBS += D:/OpenCV_RELEASE_2.4.10_x86/install/x64/mingw/lib/libopencv_features2d2410.dll.a
LIBS += D:/OpenCV_RELEASE_2.4.10_x86/install/x64/mingw/lib/libopencv_flann2410.dll.a
LIBS += D:/OpenCV_RELEASE_2.4.10_x86/install/x64/mingw/lib/libopencv_gpu2410.dll.a
LIBS += D:/OpenCV_RELEASE_2.4.10_x86/install/x64/mingw/lib/libopencv_legacy2410.dll.a
LIBS += D:/OpenCV_RELEASE_2.4.10_x86/install/x64/mingw/lib/libopencv_ml2410.dll.a
LIBS += D:/OpenCV_RELEASE_2.4.10_x86/install/x64/mingw/lib/libopencv_nonfree2410.dll.a
LIBS += D:/OpenCV_RELEASE_2.4.10_x86/install/x64/mingw/lib/libopencv_objdetect2410.dll.a
LIBS += D:/OpenCV_RELEASE_2.4.10_x86/install/x64/mingw/lib/libopencv_ocl2410.dll.a
LIBS += D:/OpenCV_RELEASE_2.4.10_x86/install/x64/mingw/lib/libopencv_photo2410.dll.a
LIBS += D:/OpenCV_RELEASE_2.4.10_x86/install/x64/mingw/lib/libopencv_stitching2410.dll.a
LIBS += D:/OpenCV_RELEASE_2.4.10_x86/install/x64/mingw/lib/libopencv_superres2410.dll.a
LIBS += D:/OpenCV_RELEASE_2.4.10_x86/install/x64/mingw/lib/libopencv_video2410.dll.a
LIBS += D:/OpenCV_RELEASE_2.4.10_x86/install/x64/mingw/lib/libopencv_videostab2410.dll.a
//LIBS += "D:/OpenCV_RELEASE_2.4.10_x86/install/x64/mingw/lib/opencv_ffmpeg2410.dll"

