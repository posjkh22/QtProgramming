
#include <QApplication>
#include <QMessageBox>

int main(int argc,char** argv)
{
  QApplication app(argc,argv);

  QMessageBox messageBox;
  messageBox.setIconPixmap(QPixmap("coffee-cup-icon.png"));
  messageBox.setText("This QMessageBox is with\ncustom icon !!!");
  messageBox.setWindowTitle("QMessageBox with Custom Icon..");
  messageBox.show();

  return app.exec();
}
