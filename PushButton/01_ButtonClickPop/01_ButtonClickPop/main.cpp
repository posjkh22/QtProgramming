
#include <QApplication>
#include <QMainWindow>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  MyMainWindow window;

  window.setWindowTitle(QString::fromUtf8("MainWindow"));
  window.resize(250,200);
  window.Execute();

  return app.exec();

}
