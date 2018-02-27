#include "filedialog.h"
#include <QApplication>


int main( int argc, char **argv )
{
  QApplication app( argc, argv );

  QFileDialogTester test;
  test.openFile();

  return 0;
}
