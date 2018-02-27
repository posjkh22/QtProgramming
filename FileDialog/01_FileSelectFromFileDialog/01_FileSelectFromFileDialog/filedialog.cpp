#include "filedialog.h"

void QFileDialogTester::openFile()
{
  QStringList filename =  QFileDialog::getOpenFileNames(
        this,
        "Open Document",
        QDir::currentPath(),
        "All files (*.*) ;; Document files (*.doc *.rtf);; PNG files (*.png)");

  if( !filename.isEmpty() )
  {
    qDebug() << "selected file paths : " << filename.join(",").toUtf8();
  }
}
