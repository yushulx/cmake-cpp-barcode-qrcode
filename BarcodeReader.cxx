#include <stdio.h>
#include "DynamsoftBarcodeReader.h"
#include "BarcodeReaderConfig.h"

#if defined(LINUX) || defined(MACOS)
#include <sys/time.h>
#endif

void ToHexString(unsigned char* pSrc, int iLen, char* pDest)
{
	const char HEXCHARS[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

	int i;
	char* ptr = pDest;

	for(i = 0; i < iLen; ++i)
	{
		snprintf(ptr, 4, "%c%c ", HEXCHARS[ ( pSrc[i] & 0xF0 ) >> 4 ], HEXCHARS[ ( pSrc[i] & 0x0F ) >> 0 ]);
		ptr += 3;
	}
}

int main(int argc, const char* argv[])
{
	fprintf(stdout, "Barcode Reader Version %d.%d\n",
	BarcodeReader_VERSION_MAJOR, BarcodeReader_VERSION_MINOR);

	if (argc < 2) {
		printf("Usage: BarcodeReaderDemo [ImageFilePath]\n");
        return 0;
	}
	
	const char* pszImageFile = argv[1];
	int iRet = 0, fCostTime;

	// Set license
	CBarcodeReader reader;
	const char* pszLicense = "LICENSE-KEY";
	reader.InitLicense (pszLicense);

	// DPM settings
	char sError[512];
	PublicRuntimeSettings* runtimeSettings = new PublicRuntimeSettings();
	reader.GetRuntimeSettings(runtimeSettings);
	//turn on the DPM mode
	runtimeSettings->furtherModes.dpmCodeReadingModes[0] = DPMCRM_GENERAL;
	runtimeSettings->localizationModes[0] = LM_STATISTICS_MARKS;
	//update the runtime settings
	reader.UpdateRuntimeSettings(runtimeSettings, sError, 512);

	// Read barcode
	#if defined(WINDOWS)
	unsigned __int64 ullTimeBegin = GetTickCount();
	iRet = reader.DecodeFile(pszImageFile, "");
	unsigned __int64 ullTimeEnd = GetTickCount();
	fCostTime = (int)(ullTimeEnd - ullTimeBegin);
	#else
	struct timeval begin, end;
	gettimeofday(&begin, NULL);
	iRet = reader.DecodeFile(pszImageFile, "");
	gettimeofday(&end, NULL);
	fCostTime = (int)((end.tv_sec * 1000 * 1000 +  end.tv_usec) - (begin.tv_sec * 1000 * 1000 + begin.tv_usec))/1000;
	#endif
		
	// Output barcode result
	if (iRet != DBR_OK && iRet != DBRERR_MAXICODE_LICENSE_INVALID && iRet != DBRERR_AZTEC_LICENSE_INVALID && iRet != DBRERR_LICENSE_EXPIRED && iRet != DBRERR_QR_LICENSE_INVALID && iRet != DBRERR_GS1_COMPOSITE_LICENSE_INVALID &&
		iRet != DBRERR_1D_LICENSE_INVALID && iRet != DBRERR_PDF417_LICENSE_INVALID && iRet != DBRERR_DATAMATRIX_LICENSE_INVALID && iRet != DBRERR_GS1_DATABAR_LICENSE_INVALID && iRet != DBRERR_PATCHCODE_LICENSE_INVALID)
	{
		printf("Failed to read barcode: %s\n", CBarcodeReader::GetErrorString(iRet));
		return 0;
	}

	TextResultArray *paryResult = NULL;
	reader.GetAllTextResults(&paryResult);
		
	if (paryResult->resultsCount == 0)
	{
		printf("No barcode found.\n");
		CBarcodeReader::FreeTextResults(&paryResult);
		return 0;
	}
	
	printf("Total barcode(s) found: %d. Total time spent: %d ms\n\n", paryResult->resultsCount, fCostTime);
	for (int iIndex = 0; iIndex < paryResult->resultsCount; iIndex++)
	{
		printf("Barcode %d:\n", iIndex + 1);
		printf("    Type: %s\n", paryResult->results[iIndex]->barcodeFormatString);
		printf("    Text: %s\n", paryResult->results[iIndex]->barcodeText);
	}	

	CBarcodeReader::FreeTextResults(&paryResult);
	return 0;
}
