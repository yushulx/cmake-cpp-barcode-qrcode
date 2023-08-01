#include "bridge.h"

#include <iostream>

int main()
{
    std::cout << "Version: " << DBR_GetVersion() << std::endl;
    char errorMsgBuffer[512];
    int errorCode = DBR_InitLicense("DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTE2NDk4Mjk3OTI2MzUiLCJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSIsInNlc3Npb25QYXNzd29yZCI6IndTcGR6Vm05WDJrcEQ5YUoifQ==", errorMsgBuffer, 512);
    std::cout << "InitLicense errorCode: " << errorCode << std::endl;

    void* barcodeReader = DBR_CreateInstance();

    errorCode = DBR_DecodeFile(barcodeReader, "../images/UPC-E.jpg", "");

    if (errorCode != 0) {
        std::cout << "Failed to read barcode: " << errorCode << std::endl;
        DBR_DestroyInstance(barcodeReader);
        return -1;
    }
    
    TextResultArray *paryResult = NULL;
    DBR_GetAllTextResults(barcodeReader, &paryResult);

    std::cout << "Barcode count: " << paryResult->resultsCount << std::endl;

    for (int index = 0; index < paryResult->resultsCount; index++)
	{
		printf("Barcode %d:\n", index + 1);
		printf("    Type: %s\n", paryResult->results[index].barcodeFormatString);
		printf("    Text: %s\n", paryResult->results[index].barcodeText);
	}

	DBR_FreeTextResults(&paryResult);
    DBR_DestroyInstance(barcodeReader);
    return 0;
}