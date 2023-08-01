#include <iostream>
#include "bridge.h"

extern "C"
{
    C_API int DBR_InitLicense(const char *pLicense)
    {
        int errorCode = 1;
        char errorMsg[512];

        // Initialize license.
        // You can request and extend a trial license from https://www.dynamsoft.com/customer/license/trialLicense?product=dbr

        errorCode = CLicenseManager::InitLicense(pLicense, errorMsg, 512);
        if (errorCode != EC_OK)
            cout << "License initialization error: " << errorMsg << endl;

        return errorCode;
    }

    C_API void *DBR_CreateInstance()
    {
        CCaptureVisionRouter *cvr = new CCaptureVisionRouter;
        return (void *)cvr;
    }

    C_API void DBR_DestroyInstance(void *barcodeReader)
    {
        if (barcodeReader != NULL)
        {
            delete (CCaptureVisionRouter *)barcodeReader;
        }
    }

    C_API BarcodeResults* DBR_DecodeFile(void *barcodeReader, const char *pFileName)
    {
        CCapturedResult *result = ((CCaptureVisionRouter *)barcodeReader)->Capture(pFileName, CPresetTemplate::PT_READ_BARCODES);
        int errorCode = result->GetErrorCode();
        if (result->GetErrorCode() != 0)
        {
            cout << "Error: " << result->GetErrorCode() << "," << result->GetErrorString() << endl;
        }

        int capturedResultItemCount = result->GetCount();
        BarcodeResults *barcodeResults = (BarcodeResults *)calloc(1, sizeof(BarcodeResults));
        barcodeResults->count = capturedResultItemCount;
        if (capturedResultItemCount > 0) 
        {
            barcodeResults->results = (BarcodeResult *)calloc(capturedResultItemCount, sizeof(BarcodeResult));
        }

        for (int j = 0; j < capturedResultItemCount; j++)
        {
            const CCapturedResultItem *capturedResultItem = result->GetItem(j);
            CapturedResultItemType type = capturedResultItem->GetType();
            if (type == CapturedResultItemType::CRIT_BARCODE)
            {
                const CBarcodeResultItem *barcodeResultItem = dynamic_cast<const CBarcodeResultItem *>(capturedResultItem);
                // cout << "Result " << j + 1 << endl;
                // cout << "Barcode Format: " << barcodeResultItem->GetFormatString() << endl;
                // cout << "Barcode Text: " << barcodeResultItem->GetText() << endl;
                char * barcodeFormatString = (char *)barcodeResultItem->GetFormatString();
                char * barcodeText = (char *)barcodeResultItem->GetText();
                barcodeResults->results[j].barcodeFormatString = (char *)malloc(strlen(barcodeFormatString) + 1);
                strcpy(barcodeResults->results[j].barcodeFormatString, barcodeFormatString);
                barcodeResults->results[j].barcodeText = (char *)malloc(strlen(barcodeText) + 1);
                strcpy(barcodeResults->results[j].barcodeText, barcodeText);
            }
        }

        return barcodeResults;
    }

    C_API void Free_Results(BarcodeResults* results)
    {
        if (results != NULL)
        {
            if (results->results != NULL)
            {
                for (int i = 0; i < results->count; i++)
                {
                    if (results->results[i].barcodeFormatString != NULL)
                    {
                        free(results->results[i].barcodeFormatString);
                    }
                    if (results->results[i].barcodeText != NULL)
                    {
                        free(results->results[i].barcodeText);
                    }
                }
                free(results->results);
            }
            free(results);
        }
    }
}