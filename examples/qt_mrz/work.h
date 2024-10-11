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
#include <string>
#include "myvideosurface.h"
#include "mrzinfo.h"
#include "DynamsoftLabelRecognizer.h"
#include "DynamsoftCore.h"

using namespace std;

class MyVideoSurface;
class MRZInfo;

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
    void *recognizer;
    MyVideoSurface *surface;
    QMutex m_mutex;
    QWaitCondition m_listIsEmpty;
    QList<QImage> queue;
    bool m_bIsRunning;

public:
    Work(Ui::MainWindow *ui, void *recognizer,  MyVideoSurface *surface);
    virtual ~Work(){qDebug() << "Work destructor";};
    void appendFrame(const QImage &frame);
    void stop();

public slots:
    void detectMRZ();
};

#endif // WORK_H
