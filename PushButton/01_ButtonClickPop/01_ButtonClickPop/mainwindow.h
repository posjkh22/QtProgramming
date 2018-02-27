
#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H
#include <QPushButton>
#include <QMessageBox>
#include <QMainWindow>
#include <QVBoxLayout>

class MyMainWindow: public QMainWindow
{
  Q_OBJECT

public:
  MyMainWindow(){}
  ~ MyMainWindow(){}

  void Execute()
  {

    QPushButton *button = new QPushButton(this);
    QPushButton *button2 = new QPushButton(this);

    button->setText("Button No. 1");
    button2->setText("Button No. 2");

    QObject::connect(button, SIGNAL(clicked()),this, SLOT(clickedSlot()));
    QObject::connect(button2, SIGNAL(clicked()),this, SLOT(clickedSlot()));

    button->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    button2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    layout->addWidget(button);
    layout->addWidget(button2);

    setCentralWidget(centralWidget);
    setWindowTitle("Pushbutton Clicked Signal Test");
    show();
  }

public slots:
  void clickedSlot()
  {
    QMessageBox msgBox;
    msgBox.setWindowTitle("MessageBox Title");
    msgBox.setText("You Clicked "+ ((QPushButton*)sender())->text());
    msgBox.exec();
  }
};
#endif // MYMAINWINDOW_H
