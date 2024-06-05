#include "bridge.h"
#include <cstring>
#include <cstdlib>

Barcode *create_barcode(const char *type, const char *value, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    Barcode *barcode = (Barcode *)std::malloc(sizeof(Barcode));
    barcode->barcode_type = strdup(type);
    barcode->barcode_value = strdup(value);
    barcode->x1 = x1;
    barcode->y1 = y1;
    barcode->x2 = x2;
    barcode->y2 = y2;
    barcode->x3 = x3;
    barcode->y3 = y3;
    barcode->x4 = x4;
    barcode->y4 = y4;
    return barcode;
}

void free_barcode(BarcodeResults *results)
{
    for (int i = 0; i < results->count; i++)
    {
        std::free((void *)results->barcodes[i].barcode_type);
        std::free((void *)results->barcodes[i].barcode_value);
    }
    std::free(results->barcodes);
    std::free(results);
}

int init_license(const char *license)
{
    char errorMsgBuffer[512];
    // Click https://www.dynamsoft.com/customer/license/trialLicense/?product=dbr to get a trial license.
    int ret = DBR_InitLicense(license, errorMsgBuffer, 512);
    return ret;
}

BarcodeResults *decode_barcode_file(void *instance, const char *filename)
{
    char errorMsgBuffer[512];
    TextResultArray *pResults = NULL;
    BarcodeResults *all_barcodes = NULL;
    int ret = DBR_DecodeFile(instance, filename, "");
    DBR_GetAllTextResults(instance, &pResults);
    if (pResults->resultsCount > 0)
    {
        all_barcodes = (BarcodeResults *)std::malloc(sizeof(BarcodeResults));
        all_barcodes->count = pResults->resultsCount;
        all_barcodes->barcodes = (Barcode *)std::malloc(sizeof(Barcode) * pResults->resultsCount);
        for (int iIndex = 0; iIndex < pResults->resultsCount; iIndex++)
        {
            LocalizationResult *localizationResult = pResults->results[iIndex]->localizationResult;
            Barcode *barcode = create_barcode(pResults->results[iIndex]->barcodeFormatString, pResults->results[iIndex]->barcodeText,
                                              localizationResult->x1, localizationResult->y1, localizationResult->x2, localizationResult->y2,
                                              localizationResult->x3, localizationResult->y3, localizationResult->x4, localizationResult->y4);
            all_barcodes->barcodes[iIndex] = *barcode;
        }
    }

    DBR_FreeTextResults(&pResults);
    return all_barcodes;
}