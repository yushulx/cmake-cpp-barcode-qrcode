#include "mrzinfo.h"

bool MRZInfo::isNull()
{
    if (text.isEmpty())
        return true;
        
    return false;
}