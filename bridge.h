#ifndef C_BRIDGING_H 
#define C_BRIDGING_H

#include <iostream>
#include <string>

#include "DynamsoftCaptureVisionRouter.h"

using namespace std;
using namespace dynamsoft::license;
using namespace dynamsoft::cvr;
using namespace dynamsoft::dbr;

#define C_API __declspec(dllexport)

typedef struct
{
	char* barcodeFormatString;
	char* barcodeText;
} BarcodeResult;

typedef struct
{
    int count;
    BarcodeResult* results;
} BarcodeResults;

#ifdef __cplusplus
extern "C" {
#endif

C_API int DBR_InitLicense(const char* pLicense);
C_API BarcodeResults* DBR_DecodeFile(void* barcodeReader, const char* pFileName);
C_API void* DBR_CreateInstance();
C_API void DBR_DestroyInstance(void* barcodeReader);
C_API void Free_Results(BarcodeResults* results);

#ifdef __cplusplus
}
#endif

#endif 