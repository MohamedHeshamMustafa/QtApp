// STL
#include <iostream>
// Qt
#include <QApplication>
//Internal
#include "MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication QApplication(argc, argv);
    MainWindow mainWindow;
    mainWindow.showMaximized();
    return QApplication.exec();
}
