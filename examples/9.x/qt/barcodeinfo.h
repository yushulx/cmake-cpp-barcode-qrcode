#ifndef BARCODEINFO_H
#define BARCODEINFO_H

#include <QString>

#include "DynamsoftCommon.h"
#include "DynamsoftBarcodeReader.h"

class BarcodeInfo
{
public:
    BarcodeInfo() = default;
    BarcodeInfo(QString &format, QString &text, QString &decodingTime, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

    ~BarcodeInfo(){};

    bool isNull();

public:
    QString format, text, decodingTime;
    int x1, y1, x2, y2, x3, y3, x4, y4;
};

#endif // BARCODEINFO_H
