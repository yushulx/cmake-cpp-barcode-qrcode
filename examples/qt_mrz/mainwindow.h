#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QImage>
#include <QPixmap>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>
#include <QInputDialog>
#include <QPainter>
#include <QCameraViewfinder>
#include <QCamera>
#include <QCameraInfo>
#include <QAbstractVideoSurface>
#include <QDateTime>
#include <QThread>
#include <QMimeData>
#include <QUrl>
#include <string>
#include "DynamsoftLabelRecognizer.h"
#include "DynamsoftCore.h"
#include "myvideosurface.h"
#include "work.h"

using namespace dynamsoft::dlr;
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    Ui::MainWindow *ui;
    void *recognizer;
    void showImage(const QImage &image, QString fileName);
    void showMessageBox(QString title, QString content);
    QCamera *camera;
    MyVideoSurface *surface;
    Work* worker;
    QThread* thread;
    void loadFile(QString fileName);

private slots:
    void openFile();
    void openFolder();
    void listWidgetClicked(QListWidgetItem *item);
    void exportTemplate();
    void about();
    void setLicense();
    void startCamera();
    void stopCamera();
};
#endif // MAINWINDOW_H
