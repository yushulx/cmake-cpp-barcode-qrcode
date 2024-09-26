#include "work.h"
#include "./ui_mainwindow.h"

Work::Work(Ui::MainWindow *ui, void *reader, MyVideoSurface *surface)
{
    this->ui = ui;
    this->reader = reader;
    this->surface = surface;
    m_bIsRunning = true;
}

void Work::detectBarcode()
{
    while (m_bIsRunning)
    {
        QImage image;
        m_mutex.lock();
        // wait for QList
        if (queue.isEmpty())
        {
            m_listIsEmpty.wait(&m_mutex);
        }

        if (!queue.isEmpty())
        {
            image = queue.takeFirst();
        }
        m_mutex.unlock();

        if (!image.isNull())
        {
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
            int ret = DBR_DecodeBuffer(reader, (unsigned char *)image.bits(), image.width(), image.height(), image.bytesPerLine(), IPF_ARGB_8888, "");
            QDateTime end = QDateTime::currentDateTime();
            TextResultArray *handler = NULL;
            DBR_GetAllTextResults(reader, &handler);
            std::vector<BarcodeInfo> out;
            TextResult **results = handler->results;
            for (int index = 0; index < handler->resultsCount; index++)
            {
                BarcodeInfo info;
                LocalizationResult* localizationResult = results[index]->localizationResult;
                info.format = results[index]->barcodeFormatString;
                info.text = results[index]->barcodeText;
                info.decodingTime = QString::number(start.msecsTo(end));
                info.x1 = localizationResult->x1;
                info.y1 = localizationResult->y1;
                info.x2 = localizationResult->x2;
                info.y2 = localizationResult->y2;
                info.x3 = localizationResult->x3;
                info.y3 = localizationResult->y3;
                info.x4 = localizationResult->x4;
                info.y4 = localizationResult->y4;
                out.push_back(info);
            }
            DBR_FreeTextResults(&handler);
            surface->appendResult(out);
        }
    }
    
    qDebug() << "Work::detectBarcode() exit";
}

void Work::appendFrame(const QImage &frame)
{
    m_mutex.lock();
    if (queue.size() == 4) queue.clear();
    queue << frame;
    m_listIsEmpty.wakeAll();
    m_mutex.unlock();
}

void Work::stop()
{
    m_bIsRunning = false; 
    m_mutex.lock();
    m_listIsEmpty.wakeAll();
    m_mutex.unlock();
}

void Work::updateUI(QString results)
{
    QImage image;
    m_mutex.lock();
    if (queue.size() > 0) image = queue.takeLast();
    m_mutex.unlock();

    if (!image.isNull())
    {
        ui->textEdit_results->setText(results);

        // QImage image = queue.takeLast();
        // QPixmap pm = QPixmap::fromImage(image);
        // QPainter painter(&pm);
        // painter.setPen(Qt::red);

        // TextResultArray *handler = NULL;
        // DBR_GetAllTextResults(reader, &handler);

        // if (handler->resultsCount == 0)
        // {
        //     QString message = "No barcode found. Elapsed time: " + elapsedTime + "ms\n";
        //     ui->textEdit_results->setText(message);
        //     DBR_FreeTextResults(&handler);
        //     return;
        // }

        // if (ui->checkBox_autostop->isChecked()) surface->pause();

        // QString out = "";
        // TextResult **results = handler->results;
        // for (int index = 0; index < handler->resultsCount; index++)
        // {
        //     LocalizationResult* localizationResult = results[index]->localizationResult;
        //     out += "Index: " + QString::number(index) + ", Elapsed time: " + elapsedTime + "ms\n";
        //     out += "Barcode format: " + QString(results[index]->barcodeFormatString) + "\n";
        //     out += "Barcode value: " + QString(results[index]->barcodeText) + "\n";
        //     out += "Bounding box: (" + QString::number(localizationResult->x1) + ", " + QString::number(localizationResult->y1) + ") "
        //     + "(" + QString::number(localizationResult->x2) + ", " + QString::number(localizationResult->y2) + ") "
        //     + "(" + QString::number(localizationResult->x3) + ", " + QString::number(localizationResult->y3) + ") "
        //     + "(" + QString::number(localizationResult->x4) + ", " + QString::number(localizationResult->y4) + ")\n";
        //     out += "----------------------------------------------------------------------------------------\n";

        //     painter.drawLine(localizationResult->x1, localizationResult->y1, localizationResult->x2, localizationResult->y2);
        //     painter.drawLine(localizationResult->x2, localizationResult->y2, localizationResult->x3, localizationResult->y3);
        //     painter.drawLine(localizationResult->x3, localizationResult->y3, localizationResult->x4, localizationResult->y4);
        //     painter.drawLine(localizationResult->x4, localizationResult->y4, localizationResult->x1, localizationResult->y1);
        // }

        // DBR_FreeTextResults(&handler);

        // painter.end();
  
        // ui->label->setPixmap(pm.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        // ui->textEdit_results->setText(out);
    }
}
