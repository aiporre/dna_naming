//#include <QFileDialog>
//#include <QApplication>
//#include <QWidget>
//#include <QTreeWidget>
//#include <QPushButton>
//#include <QStringList>
//#include <QModelIndex>
//#include <QDir>
//#include <QDebug>
#include "dhramacon.h"

//class FileDialog : public QFileDialog
//{
//Q_OBJECT
//public:
//    explicit FileDialog(QWidget *parent = Q_NULLPTR)
//            : QFileDialog(parent)
//    {
//        setOption(QFileDialog::DontUseNativeDialog);
//        setFileMode(QFileDialog::Directory);
//        // setFileMode(QFileDialog::ExistingFiles);
//        for (auto *pushButton : findChildren<QPushButton*>()) {
//            qDebug() << pushButton->text();
//            if (pushButton->text() == "&Open" || pushButton->text() == "&Choose") {
//                openButton = pushButton;
//                break;
//            }
//        }
//        disconnect(openButton, SIGNAL(clicked(bool)));
//        connect(openButton, &QPushButton::clicked, this, &FileDialog::openClicked);
//        treeView = findChild<QTreeView*>();
//    }
//
//    QStringList selected() const
//    {
//        return selectedFilePaths;
//    }
//
//public slots:
//    void openClicked()
//    {
//        selectedFilePaths.clear();
//        qDebug() << treeView->selectionModel()->selection();
//        for (const auto& modelIndex : treeView->selectionModel()->selectedIndexes()) {
//            qDebug() << modelIndex.column();
//            if (modelIndex.column() == 0)
//                selectedFilePaths.append(directory().absolutePath() + modelIndex.data().toString());
//        }
//        emit filesSelected(selectedFilePaths);
//        hide();
//        qDebug() << selectedFilePaths;
//
//        for(auto filename: selectedFilePaths){
//            string filenameString = filename.toStdString();
//            cout << "Processing file: " << filenameString << endl;
//            if(processFolder(reinterpret_cast<const char *>(&filenameString)) == 1){
//                processFile(filenameString);
//            }
//        }
//        system("pause");
//
//    }
//
//private:
//    QTreeView *treeView;
//    QPushButton *openButton;
//    QStringList selectedFilePaths;
//};
//
//#include "wizard.moc"
//
//int main(int argc, char **argv)
//{
//    QApplication application(argc, argv);
//    FileDialog fileDialog;
//    fileDialog.show();
//    return application.exec();
//}
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









