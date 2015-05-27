#include "mainwindow.h"
#include <QApplication>
#include <ctime>
#include <cstdlib>
#include "teacher.h"
#include "network.h"
#include "image.h"



int main(int argc, char *argv[])
{
    srand(time(NULL));
    Image image;
    Teacher teacher;
    Network network;

    QApplication a(argc, argv);
    MainWindow w;
    w.GetNetworkTeacherImage(&network, &teacher, &image);
    w.show();

    return a.exec();
}
