#include "myvideosurface.h"
#include "./ui_mainwindow.h"

MyVideoSurface::MyVideoSurface(QObject *parent, Ui::MainWindow *ui, void *recognizer, QCamera *camera) : QAbstractVideoSurface(parent)
{
    this->ui = ui;
    this->recognizer = recognizer;
    this->camera = camera;
    this->is_detecting = true;
}

MyVideoSurface::~MyVideoSurface()
{
}

void MyVideoSurface::reset()
{
    this->is_detecting = true;
    this->queue.clear();
}

QList<QVideoFrame::PixelFormat> MyVideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType type) const
{
    if (type == QAbstractVideoBuffer::NoHandle)
    {
        return QList<QVideoFrame::PixelFormat>()
               << QVideoFrame::Format_RGB32;
    }
    else
    {
        return QList<QVideoFrame::PixelFormat>();
    }
}

bool MyVideoSurface::present(const QVideoFrame &frame)
{
    if (frame.isValid() && is_detecting)
    {
        QVideoFrame cloneFrame(frame);
        cloneFrame.map(QAbstractVideoBuffer::ReadOnly);
        const QImage img(cloneFrame.bits(),
                         cloneFrame.width(),
                         cloneFrame.height(),
                         QVideoFrame::imageFormatFromPixelFormat(cloneFrame.pixelFormat()));

        QImage cp = img.copy();

        cloneFrame.unmap();

        cp = cp.mirrored(false, true);

        if (worker)
        {
            worker->appendFrame(cp);
            std::vector<MRZInfo> info;
            mutex.lock();
            if (queue.size() > 0)
            {
                info = queue.back();
                queue.pop_back();
            } 
            mutex.unlock();
            
            QPixmap pm = QPixmap::fromImage(cp);
            QString out = "";
            if (info.size() > 0)
            {
                if (ui->checkBox_autostop->isChecked()) pause();

                QPainter painter(&pm);
                painter.setPen(Qt::red);

                for (int index = 0; index < info.size(); index++)
                {
                    MRZInfo mrzInfo = info.at(index);
                    out += mrzInfo.text + "\n";
                    out += "----------------------------------------------------------------------------------------\n";

                    painter.drawLine(mrzInfo.x1, mrzInfo.y1, mrzInfo.x2, mrzInfo.y2);
                    painter.drawLine(mrzInfo.x2, mrzInfo.y2, mrzInfo.x3, mrzInfo.y3);
                    painter.drawLine(mrzInfo.x3, mrzInfo.y3, mrzInfo.x4, mrzInfo.y4);
                    painter.drawLine(mrzInfo.x4, mrzInfo.y4, mrzInfo.x1, mrzInfo.y1);
                    painter.drawLine(mrzInfo.xx1, mrzInfo.yy1, mrzInfo.xx2, mrzInfo.yy2);
                    painter.drawLine(mrzInfo.xx2, mrzInfo.yy2, mrzInfo.xx3, mrzInfo.yy3);
                    painter.drawLine(mrzInfo.xx3, mrzInfo.yy3, mrzInfo.xx4, mrzInfo.yy4);
                    painter.drawLine(mrzInfo.xx4, mrzInfo.yy4, mrzInfo.xx1, mrzInfo.yy1);
                }
                painter.end();
            }
            else
            {
                out = "No MRZ detected";
            }
            ui->textEdit_results->setText(out);
            ui->label->setPixmap(pm.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }

        return true;
    }
    return false;
}

void MyVideoSurface::setWorker(Work* worker)
{
    this->worker = worker;
}

void MyVideoSurface::pause()
{
    is_detecting = false;
    worker->stop();
    camera->stop();
    queue.clear();
}

void MyVideoSurface::appendResult(std::vector<MRZInfo> &result)
{
    mutex.lock();
    if (queue.size() == 4) queue.clear();
    queue.push_back(result);
    mutex.unlock();
}