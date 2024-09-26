#ifndef MYVIDEOSURFACE_H
#define MYVIDEOSURFACE_H

#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QPainter>
#include <QCamera>
#include <QCameraInfo>
#include <QAbstractVideoSurface>
#include <QDateTime>
#include <QMutex>
#include <QList>
#include <vector>
#include "DynamsoftCommon.h"
#include "DynamsoftBarcodeReader.h"

#include "work.h"
#include "barcodeinfo.h"

class Work;
class BarcodeInfo;

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

// https://www.qtcentre.org/threads/57090-How-could-I-get-the-image-buffer-of-QCamera
class MyVideoSurface : public QAbstractVideoSurface
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    void *reader;
    bool is_detecting;
    Work* worker;
    std::vector<std::vector<BarcodeInfo>> queue;
    QMutex mutex;
    QCamera *camera;

public:
    MyVideoSurface(QObject *parent, Ui::MainWindow *ui, void *reader, QCamera *camera);
    ~MyVideoSurface();

    void reset();
    void pause();
    void setWorker(Work* worker);
    void appendResult(std::vector<BarcodeInfo> &result);

    QList<QVideoFrame::PixelFormat>
    supportedPixelFormats(QAbstractVideoBuffer::HandleType type) const;

    bool present(const QVideoFrame &frame);
};
#endif // MYVIDEOSURFACE_H
