#ifndef WORK_H
#define WORK_H

#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QPainter>
#include <QDateTime>
#include <QMutex>
#include <QWaitCondition>
#include <QList>
#include <vector>

#include "DynamsoftCommon.h"
#include "DynamsoftBarcodeReader.h"

#include "myvideosurface.h"
#include "barcodeinfo.h"

class MyVideoSurface;
class BarcodeInfo;

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class Work: public QObject
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    void *reader;
    MyVideoSurface *surface;
    QMutex m_mutex;
    QWaitCondition m_listIsEmpty;
    QList<QImage> queue;
    bool m_bIsRunning;

public:
    Work(Ui::MainWindow *ui, void *reader,  MyVideoSurface *surface);
    virtual ~Work(){};
    void appendFrame(const QImage &frame);
    void stop();
    void updateUI(QString results);

public slots:
    void detectBarcode();

signals: 
    void update(QString results);                
};

#endif // WORK_H
