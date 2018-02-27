#include "mainwindow.h"

#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
{
   // Create the button, make "this" the parent
   m_button = new QPushButton("Button Start", this);
   // set size and location of the button
   m_button->setGeometry(QRect(QPoint(100, 100),
   QSize(100, 100)));

   // Connect button signal to appropriate slot
   connect(m_button, SIGNAL (released()), this, SLOT (handleButton1()));

}

void MainWindow::handleButton1()
{
   // change the text
   m_button->setText("Button 1");
   // resize button
   m_button->resize(100,100);
   connect(m_button, SIGNAL (released()), this, SLOT (handleButton2()));

}

void MainWindow::handleButton2()
{
   // change the text
   m_button->setText("Button 2");
   // resize button
   m_button->resize(100,100);
}
