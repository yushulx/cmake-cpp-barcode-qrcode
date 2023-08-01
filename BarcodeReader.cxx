#include "bridge.h"

#include <iostream>

int main()
{
    DBR_InitLicense("DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTE2NDk4Mjk3OTI2MzUiLCJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSIsInNlc3Npb25QYXNzd29yZCI6IndTcGR6Vm05WDJrcEQ5YUoifQ==");
    void* barcodeReader = DBR_CreateInstance();

    BarcodeResults *barcodeResults = DBR_DecodeFile(barcodeReader, "../images/UPC-E.jpg");

    if (barcodeResults) {
        for (int i = 0; i < barcodeResults->count; i++) {
            std::cout << "Barcode Format: " << barcodeResults->results[i].barcodeFormatString << std::endl;
            std::cout << "Barcode Text: " << barcodeResults->results[i].barcodeText << std::endl;
        }

        Free_Results(barcodeResults);
    }

    DBR_DestroyInstance(barcodeReader);
    return 0;
}