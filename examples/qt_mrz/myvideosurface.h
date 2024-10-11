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

#include "DynamsoftLabelRecognizer.h"
#include "DynamsoftCore.h"
#include "work.h"
#include "mrzinfo.h"

class Work;
class MRZInfo;

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
    void *recognizer;
    bool is_detecting;
    Work* worker;
    std::vector<std::vector<MRZInfo>> queue;
    QMutex mutex;
    QCamera *camera;

public:
    MyVideoSurface(QObject *parent, Ui::MainWindow *ui, void *recognizer, QCamera *camera);
    ~MyVideoSurface();

    void reset();
    void pause();
    void setWorker(Work* worker);
    void appendResult(std::vector<MRZInfo> &result);

    QList<QVideoFrame::PixelFormat>
    supportedPixelFormats(QAbstractVideoBuffer::HandleType type) const;

    bool present(const QVideoFrame &frame);
};
#endif // MYVIDEOSURFACE_H
