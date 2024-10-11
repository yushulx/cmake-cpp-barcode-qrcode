#include "work.h"
#include "./ui_mainwindow.h"

Work::Work(Ui::MainWindow *ui, void *recognizer, MyVideoSurface *surface)
{
    this->ui = ui;
    this->recognizer = recognizer;
    this->surface = surface;
    m_bIsRunning = true;
}

void Work::detectMRZ()
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
            // Convert QImage to ImageData
            ImageData data;
            data.bytes = (unsigned char *)image.bits();
            data.width = image.width();
            data.height = image.height();
            data.stride = image.bytesPerLine();
            data.format = IPF_ARGB_8888;
            data.bytesLength = image.byteCount();

            QDateTime start = QDateTime::currentDateTime();
            int errorCode = DLR_RecognizeByBuffer(recognizer, &data, "locr");
            QDateTime end = QDateTime::currentDateTime();
            DLR_ResultArray *handler = NULL;
            DLR_GetAllResults(recognizer, &handler);
            std::vector<MRZInfo> all;
            QString out = "Elapsed time: " + QString::number(start.msecsTo(end)) + "ms\n\n";
            DLR_Result **results = handler->results;
            for (int ri = 0; ri < handler->resultsCount; ++ri)
            {
                DLR_Result* result = handler->results[ri];
                int lCount = result->lineResultsCount;
                if (lCount < 2)
                {
                    continue;
                }

                DLR_LineResult *l1 = result->lineResults[0];
                DLR_LineResult *l2 = result->lineResults[1];

                string line1 = l1->text;
                string line2 = l2->text;
                if (line1.length() != 44 || line2.length() != 44)
                {
                    continue;
                }
                if (line1[0] != 'P')
                    continue;

                MRZInfo info;
                
                DM_Point *points = l1->location.points;
                int x1 = points[0].x, y1 = points[0].y;
                int x2 = points[1].x, y2 = points[1].y;
                int x3 = points[2].x, y3 = points[2].y;
                int x4 = points[3].x, y4 = points[3].y;
                DM_Point *points2 = l2->location.points;
                int xx1 = points2[0].x, yy1 = points2[0].y;
                int xx2 = points2[1].x, yy2 = points2[1].y;
                int xx3 = points2[2].x, yy3 = points2[2].y;
                int xx4 = points2[3].x, yy4 = points2[3].y;

                // Type
                string tmp = "Type: ";
                tmp.insert(tmp.length(), 1, line1[0]);
                out += QString::fromStdString(tmp) + "\n";

                // Issuing country
                tmp = "Issuing country: "; line1.substr(2, 5);
                tmp += line1.substr(2, 3);		
                out += QString::fromStdString(tmp) + "\n";

                // Surname
                int index = 5;
                tmp = "Surname: ";
                for (; index < 44; index++)
                {
                    if (line1[index] != '<')
                    {
                        tmp.insert(tmp.length(), 1, line1[index]);
                    }
                    else 
                    {
                        break;
                    }
                }
                out += QString::fromStdString(tmp) + "\n";

                // Given names
                tmp = "Given Names: ";
                index += 2;
                for (; index < 44; index++)
                {
                    if (line1[index] != '<')
                    {
                        tmp.insert(tmp.length(), 1, line1[index]);
                    }
                    else 
                    {
                        tmp.insert(tmp.length(), 1, ' ');
                    }
                }
                out += QString::fromStdString(tmp) + "\n";

                // Passport number
                tmp = "Passport number: ";
                index = 0;
                for (; index < 9; index++)
                {
                    if (line2[index] != '<')
                    {
                        tmp.insert(tmp.length(), 1, line2[index]);
                    }
                    else 
                    {
                        break;
                    }
                }
                out += QString::fromStdString(tmp) + "\n";

                // Nationality
                tmp = "Nationality: ";
                tmp += line2.substr(10, 3);
                out += QString::fromStdString(tmp) + "\n";

                // Date of birth
                tmp = line2.substr(13, 6);
                tmp.insert(2, "/");
                tmp.insert(5, "/");
                tmp = "Date of birth (YYMMDD): " + tmp;
                out += QString::fromStdString(tmp) + "\n";

                // Sex
                tmp = "Sex: ";
                tmp.insert(tmp.length(), 1, line2[20]);
                out += QString::fromStdString(tmp) + "\n";

                // Expiration date of passport
                tmp = line2.substr(21, 6);
                tmp.insert(2, "/");
                tmp.insert(5, "/");
                tmp = "Expiration date of passport (YYMMDD): " + tmp;
                out += QString::fromStdString(tmp) + "\n";

                // Personal number
                if (line2[28] != '<')
                {
                    tmp = "Personal number: ";
                    for (index = 28; index < 42; index++)
                    {
                        if (line2[index] != '<')
                        {
                            tmp.insert(tmp.length(), 1, line2[index]);
                        }
                        else 
                        {
                            break;
                        }
                    }
                    out += QString::fromStdString(tmp) + "\n";
                }

                info.text = out;
                info.x1 = x1;
                info.y1 = y1;
                info.x2 = x2;
                info.y2 = y2;
                info.x3 = x3;
                info.y3 = y3;
                info.x4 = x4;
                info.y4 = y4;
                info.xx1 = xx1;
                info.yy1 = yy1;
                info.xx2 = xx2;
                info.yy2 = yy2;
                info.xx3 = xx3;
                info.yy3 = yy3;
                info.xx4 = xx4;
                info.yy4 = yy4;

                all.push_back(info);
            }

            DLR_FreeResults(&handler);
            surface->appendResult(all);
        }
    }
    
    qDebug() << "Worker thread exit";
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
