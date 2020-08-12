
#include "dhramacon.h"

#include <QApplication>
#include <QFileDialog>
#include <QDebug>

class QFileDialogTester : public QWidget
{
public:
    void openFile()
    {
        QString dirname =  QFileDialog::getExistingDirectory(
                this,
                "Open Summary Intensity Files");

        if( !dirname.isNull() )
        {
            qDebug() << "selected file path : " << dirname.toUtf8();
        }
        string dirnameString = dirname.toStdString();
        processFolder(dirnameString);
    }
};


int main( int argc, char **argv )
{
    QApplication app( argc, argv );

    QFileDialogTester test;
    test.openFile();

    return 0;
}









