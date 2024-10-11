#ifndef MRZINFO_H
#define MRZINFO_H

#include <QString>

class MRZInfo
{
public:
    MRZInfo() = default;

    ~MRZInfo(){};

    bool isNull();

public:
    QString text;
    int x1, y1, x2, y2, x3, y3, x4, y4, xx1, yy1, xx2, yy2, xx3, yy3, xx4, yy4;
};

#endif // MRZINFO_H
