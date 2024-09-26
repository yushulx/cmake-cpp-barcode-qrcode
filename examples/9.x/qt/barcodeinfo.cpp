#include "barcodeinfo.h"

BarcodeInfo::BarcodeInfo(QString &format, QString &text, QString &decodingTime, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    this->format = format;
    this->text = text;
    this->decodingTime = decodingTime;
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    this->x3 = x3;
    this->y3 = y3;
    this->x4 = x4;
    this->y4 = y4;
}

bool BarcodeInfo::isNull()
{
    if (format.isEmpty() || text.isEmpty() || decodingTime.isEmpty())
        return true;
        
    return false;
}