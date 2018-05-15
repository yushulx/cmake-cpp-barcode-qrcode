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

	// Set license
	CBarcodeReader reader;
	#if defined(WINDOWS)
	const char* pszLicense = "t0068MgAAAGhyhnDz09eHhPRZ5MRe3ak0VO/TZmolcIp39SoQ8LtsgZhzAj5khTx+OFsXgz+HIz+MNaC7VA69MM1N26gNlZA=";
	#elif defined(LINUX)
	const char* pszLicense = "t0068MgAAAH/7UYLqUWdzq7Wdmqm1jmbYWWzWq9PkQs0HktHgYFVw1SrAPy724d6eENC3ZMYRtDB53yq5TGl8uEXCNDwV4dg=";
	#elif defined(MACOS)
	const char* pszLicense = "t0068MgAAAIEpvKEnV9lYMDE/a86TqCU0y//dEIBdgDvyW3G2hl57K6lvDLGPHFajVA/6IECxNJKGM2n6gTv67ZwgNg65vwo=";
	#endif
	reader.InitLicense (pszLicense);

	// Load settings
	char szErrorMsg[256];
	char basePath[255] = "";
    _fullpath(basePath, argv[0], sizeof(basePath));
	// Get the directory
	int iLast = 0;
	for (int i = 0; ; i++) {
		char tmp = basePath[i];
		if (tmp == '\\')
		{
			iLast = i;
		}
		else if (tmp == '\0')
		{
			break;
		}
	}

	char templatePath[1024];
	strncpy_s(templatePath, basePath, iLast);

	// Get the full path
	const char* pszSettingFile = "\\templates\\default.settings.json";
	strcat_s (templatePath, pszSettingFile);

	int iRet = reader.LoadSettingsFromFile(templatePath, szErrorMsg, 256);
	if(iRet != DBR_OK)
	{
		printf("Error code: %d. Error message: %s\n", iRet, szErrorMsg);
		return -1;
	}

	// Read barcode
	#if defined(WINDOWS)
	unsigned __int64 ullTimeBegin = GetTickCount();
	iRet = reader.DecodeFile(pszImageFile, "CUSTOM");
	unsigned __int64 ullTimeEnd = GetTickCount();
	#else
	struct timeval begin, end;
	float fCostTime = 0;
	gettimeofday(&begin, NULL);
	iRet = reader.DecodeFile(pszImageFile);
	gettimeofday(&end, NULL);
	fCostTime = (float)((end.tv_sec * 1000 * 1000 +  end.tv_usec) - (begin.tv_sec * 1000 * 1000 + begin.tv_usec))/(1000 * 1000);
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
		#if defined(WINDOWS)
		sprintf_s(pszTemp, 4096, "No barcode found. Total time spent: %.3f seconds.\r\n", ((float)(ullTimeEnd - ullTimeBegin)/1000));
		printf(pszTemp);
		free(pszTemp);
		#else 
		printf("No barcode found. Total time spent: %.3f seconds.\n", fCostTime);
		#endif
		CBarcodeReader::FreeTextResults(&paryResult);
		return 0;
	}
	
	#if defined(WINDOWS)
	sprintf_s(pszTemp, 4096, "Total barcode(s) found: %d. Total time spent: %.3f seconds\r\n\r\n", paryResult->nResultsCount, ((float)(ullTimeEnd - ullTimeBegin)/1000));
	printf(pszTemp);
	#else 
	printf("Total barcode(s) found: %d. Total time spent: %.3f seconds\n\n", paryResult->iBarcodeCount, fCostTime);
	#endif
	for (int iIndex = 0; iIndex < paryResult->nResultsCount; iIndex++)
	{
		#if defined(WINDOWS)
		sprintf_s(pszTemp, 4096, "Barcode %d:\r\n", iIndex + 1);
		printf(pszTemp);
		sprintf_s(pszTemp, 4096, "    Type: %s\r\n", paryResult->ppResults[iIndex]->pszBarcodeFormatString);
		printf(pszTemp);
		sprintf_s(pszTemp, 4096, "    Value: %s\r\n", paryResult->ppResults[iIndex]->pszBarcodeText);
		printf(pszTemp);

		char *pszTemp1 = (char*)malloc(paryResult->ppResults[iIndex]->nBarcodeBytesLength*3 + 1);
		ToHexString(paryResult->ppResults[iIndex]->pBarcodeBytes, paryResult->ppResults[iIndex]->nBarcodeBytesLength, pszTemp1);
		sprintf_s(pszTemp, 4096, "    Hex Data: %s\r\n", pszTemp1);
		printf(pszTemp);
		free(pszTemp1);

		#else
		printf("Barcode %d:\n", iIndex + 1);
		printf("    Page: %d\n", paryResult->ppBarcodes[iIndex]->iPageNum);
		printf("    Type: %s\n", paryResult->ppBarcodes[iIndex]->pBarcodeFormatString);
		printf("    Text: %s\n", paryResult->ppBarcodes[iIndex]->pBarcodeText);
		printf("    Region: {Left: %d, Top: %d, Width: %d, Height: %d}\n\n", 
			paryResult->ppBarcodes[iIndex]->iLeft, paryResult->ppBarcodes[iIndex]->iTop, 
			paryResult->ppBarcodes[iIndex]->iWidth, paryResult->ppBarcodes[iIndex]->iHeight);
		#endif
	}	

	#if defined(WINDOWS)
	free(pszTemp);
	#endif
	CBarcodeReader::FreeTextResults(&paryResult);

	return 0;
}
