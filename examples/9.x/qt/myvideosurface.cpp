#include "myvideosurface.h"
#include "./ui_mainwindow.h"

MyVideoSurface::MyVideoSurface(QObject *parent, Ui::MainWindow *ui, void *reader, QCamera *camera) : QAbstractVideoSurface(parent)
{
    this->ui = ui;
    this->reader = reader;
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
            std::vector<BarcodeInfo> info;
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
                    BarcodeInfo barcodeInfo = info.at(index);
                    out += "Index: " + QString::number(index) + ", Elapsed time: " + barcodeInfo.decodingTime + "ms\n";
                    out += "Barcode format: " + barcodeInfo.format + "\n";
                    out += "Barcode value: " + barcodeInfo.text + "\n";
                    out += "Bounding box: (" + QString::number(barcodeInfo.x1) + ", " + QString::number(barcodeInfo.y1) + ") "
                    + "(" + QString::number(barcodeInfo.x2) + ", " + QString::number(barcodeInfo.y2) + ") "
                    + "(" + QString::number(barcodeInfo.x3) + ", " + QString::number(barcodeInfo.y3) + ") "
                    + "(" + QString::number(barcodeInfo.x4) + ", " + QString::number(barcodeInfo.y4) + ")\n";
                    out += "----------------------------------------------------------------------------------------\n";

                    painter.drawLine(barcodeInfo.x1, barcodeInfo.y1, barcodeInfo.x2, barcodeInfo.y2);
                    painter.drawLine(barcodeInfo.x2, barcodeInfo.y2, barcodeInfo.x3, barcodeInfo.y3);
                    painter.drawLine(barcodeInfo.x3, barcodeInfo.y3, barcodeInfo.x4, barcodeInfo.y4);
                    painter.drawLine(barcodeInfo.x4, barcodeInfo.y4, barcodeInfo.x1, barcodeInfo.y1);
                }
                painter.end();
            }
            else
            {
                out = "No barcode detected";
            }
            ui->textEdit_results->setText(out);
            ui->label->setPixmap(pm.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        else 
        {
            QPixmap pm = QPixmap::fromImage(cp);
            QPainter painter(&pm);
            painter.setPen(Qt::red);

            // Get the template content and initialize the runtime settings.
            QString content = ui->textEdit_results->toPlainText();
            char errorMessage[256];
            if (!content.isEmpty()) {
                DBR_InitRuntimeSettingsWithString(reader, content.toStdString().c_str(), CM_OVERWRITE, errorMessage, 256);
            }

            // Set barcode types.
            int types = 0, types2 = 0;
            if (ui->checkBox_code39->isChecked()) {types |= BF_CODE_39;}
            if (ui->checkBox_code93->isChecked()) {types |= BF_CODE_93;}
            if (ui->checkBox_code128->isChecked()){ types |= BF_CODE_128;}
            if (ui->checkBox_codabar->isChecked()){ types |= BF_CODABAR;}
            if (ui->checkBox_itf->isChecked()){ types |= BF_ITF;}
            if (ui->checkBox_ean13->isChecked()){ types |= BF_EAN_13;}
            if (ui->checkBox_ean8->isChecked()){ types |= BF_EAN_8;}
            if (ui->checkBox_upca->isChecked()){ types |= BF_UPC_A;}
            if (ui->checkBox_upce->isChecked()){ types |= BF_UPC_E;}
            if (ui->checkBox_industrial25->isChecked()){ types |= BF_INDUSTRIAL_25;}
            if (ui->checkBox_qrcode->isChecked()){ types |= BF_QR_CODE;}
            if (ui->checkBox_pdf417->isChecked()){ types |= BF_PDF417;}
            if (ui->checkBox_aztec->isChecked()){ types |= BF_AZTEC;}
            if (ui->checkBox_maxicode->isChecked()){ types |= BF_MAXICODE;}
            if (ui->checkBox_datamatrix->isChecked()){ types |= BF_DATAMATRIX;}
            if (ui->checkBox_gs1->isChecked()){ types |= BF_GS1_COMPOSITE;}
            if (ui->checkBox_patchcode->isChecked()){ types |= BF_PATCHCODE;}
            if (ui->checkBox_dotcode->isChecked()){ types2 |= BF2_DOTCODE;}
            if (ui->checkBox_postalcode->isChecked()){ types2 |= BF2_POSTALCODE;}
            
            PublicRuntimeSettings settings;
            DBR_GetRuntimeSettings(reader, &settings);
            settings.deblurLevel = 0;
            settings.timeout = 50;
            settings.expectedBarcodesCount = 0;
            settings.barcodeFormatIds = types;
            settings.barcodeFormatIds_2 = types2;
            DBR_UpdateRuntimeSettings(reader, &settings, errorMessage, 256);

            // Decode barcode and draw results
            QDateTime start = QDateTime::currentDateTime();
            int ret = DBR_DecodeBuffer(reader, (unsigned char *)cp.bits(), cp.width(), cp.height(), cp.bytesPerLine(), IPF_ARGB_8888, "");
            QDateTime end = QDateTime::currentDateTime();
            TextResultArray *handler = NULL;
            DBR_GetAllTextResults(reader, &handler);

            if (handler->resultsCount == 0)
            {
                QString message = "No barcode found. Elapsed time: " + QString::number(start.msecsTo(end)) + "ms\n";
                ui->textEdit_results->setText(message);
                DBR_FreeTextResults(&handler);
                ui->label->setPixmap(pm.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
                return true;
            }

            if (ui->checkBox_autostop->isChecked()) pause();

            QString out = "";
            TextResult **results = handler->results;
            for (int index = 0; index < handler->resultsCount; index++)
            {
                LocalizationResult* localizationResult = results[index]->localizationResult;
                out += "Index: " + QString::number(index) + ", Elapsed time: " + QString::number(start.msecsTo(end)) + "ms\n";
                out += "Barcode format: " + QString(results[index]->barcodeFormatString) + "\n";
                out += "Barcode value: " + QString(results[index]->barcodeText) + "\n";
                out += "Bounding box: (" + QString::number(localizationResult->x1) + ", " + QString::number(localizationResult->y1) + ") "
                + "(" + QString::number(localizationResult->x2) + ", " + QString::number(localizationResult->y2) + ") "
                + "(" + QString::number(localizationResult->x3) + ", " + QString::number(localizationResult->y3) + ") "
                + "(" + QString::number(localizationResult->x4) + ", " + QString::number(localizationResult->y4) + ")\n";
                out += "----------------------------------------------------------------------------------------\n";

                painter.drawLine(localizationResult->x1, localizationResult->y1, localizationResult->x2, localizationResult->y2);
                painter.drawLine(localizationResult->x2, localizationResult->y2, localizationResult->x3, localizationResult->y3);
                painter.drawLine(localizationResult->x3, localizationResult->y3, localizationResult->x4, localizationResult->y4);
                painter.drawLine(localizationResult->x4, localizationResult->y4, localizationResult->x1, localizationResult->y1);
            }

            DBR_FreeTextResults(&handler);

            painter.end();
            ui->label->setPixmap(pm.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

            ui->textEdit_results->setText(out);
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

void MyVideoSurface::appendResult(std::vector<BarcodeInfo> &result)
{
    mutex.lock();
    if (queue.size() == 4) queue.clear();
    queue.push_back(result);
    mutex.unlock();
}