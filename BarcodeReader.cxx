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
		#if defined(WINDOWS)
		sprintf_s(ptr, 4, "%c%c ", HEXCHARS[ ( pSrc[i] & 0xF0 ) >> 4 ], HEXCHARS[ ( pSrc[i] & 0x0F ) >> 0 ]);
		#else
		snprintf(ptr, 4, "%c%c ", HEXCHARS[ ( pSrc[i] & 0xF0 ) >> 4 ], HEXCHARS[ ( pSrc[i] & 0x0F ) >> 0 ]);
		#endif
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
	#if defined(WINDOWS)
	const char* pszLicense = "t0068NQAAAGWe/zXkYmggvyFrd8PmfjplKakH67Upt9HvuRDIBAV6MZ4uODuL1ZUgSEAOygejsfwj6XRKI5iD1tLKZBRGo2c=";
	#elif defined(LINUX)
	const char* pszLicense = "t0068NQAAAIY/7KegDlZn7YiPdAj0cbA11n2CwuCEWnk2KYla55ozdfmoasjRIpHhl0EUZmko/zxfxFLH3FpLw694uihoCVM=";
	#elif defined(MACOS)
	const char* pszLicense = "t0068MgAAAIEpvKEnV9lYMDE/a86TqCU0y//dEIBdgDvyW3G2hl57K6lvDLGPHFajVA/6IECxNJKGM2n6gTv67ZwgNg65vwo=";
	#endif
	reader.InitLicense (pszLicense);

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
	#if defined(WINDOWS)
	char *pszTemp = (char*)malloc(4096);
	#endif
	if (iRet != DBR_OK && iRet != DBRERR_LICENSE_EXPIRED && iRet != DBRERR_QR_LICENSE_INVALID &&
		iRet != DBRERR_1D_LICENSE_INVALID && iRet != DBRERR_PDF417_LICENSE_INVALID && iRet != DBRERR_DATAMATRIX_LICENSE_INVALID)
	{
		#if defined(WINDOWS)
		sprintf_s(pszTemp, 4096, "Failed to read barcode: %s\r\n", DBR_GetErrorString(iRet));
		printf(pszTemp);
		free(pszTemp);
		#else 
		printf("Failed to read barcode: %s\r\n", DBR_GetErrorString(iRet));
		#endif
		
		return 0;
	}

	STextResultArray *paryResult = NULL;
	reader.GetAllTextResults(&paryResult);
	
	if (paryResult->nResultsCount == 0)
	{
		printf("No barcode found.\n");
		CBarcodeReader::FreeTextResults(&paryResult);
		return 0;
	}
	
	printf("Total barcode(s) found: %d. Total time spent: %d ms\n\n", paryResult->nResultsCount, fCostTime);
	for (int iIndex = 0; iIndex < paryResult->nResultsCount; iIndex++)
	{
		printf("Barcode %d:\n", iIndex + 1);
		printf("    Type: %s\n", paryResult->ppResults[iIndex]->pszBarcodeFormatString);
		printf("    Text: %s\n", paryResult->ppResults[iIndex]->pszBarcodeText);
	}	

	#if defined(WINDOWS)
	free(pszTemp);
	#endif
	CBarcodeReader::FreeTextResults(&paryResult);

	return 0;
}
