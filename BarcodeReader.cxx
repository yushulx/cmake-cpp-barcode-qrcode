#include <stdio.h>
#include "DynamsoftBarcodeReader.h"
#include "BarcodeReaderConfig.h"

#if defined(LINUX) || defined(MACOS)
#include <sys/time.h>
#endif

void ToHexString(char* pSrc, int iLen, char* pDest)
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
	int iFormat = BF_All;
	int iMaxCount = 0x7FFFFFFF;

	// Set license
	CBarcodeReader reader;
	#if defined(WINDOWS)
	const char* pszLicense = "t0068MgAAAAWh296J5PiGHBEz1VmKKA8BIEn718bOC8UijxGsOKXubl1lLkROxFBcgpHBlOAxDn7BXNR+oWTdTU6aJFHx37U=";
	#elif defined(LINUX)
	const char* pszLicense = "t0068MgAAAH/7UYLqUWdzq7Wdmqm1jmbYWWzWq9PkQs0HktHgYFVw1SrAPy724d6eENC3ZMYRtDB53yq5TGl8uEXCNDwV4dg=";
	#elif defined(MACOS)
	const char* pszLicense = "t0068MgAAAIEpvKEnV9lYMDE/a86TqCU0y//dEIBdgDvyW3G2hl57K6lvDLGPHFajVA/6IECxNJKGM2n6gTv67ZwgNg65vwo=";
	#endif
	reader.InitLicense(pszLicense);

	//Set Property
	reader.SetBarcodeFormats(iFormat);
	reader.SetMaxBarcodesNumPerPage(iMaxCount);

	// Read barcode
	#if defined(WINDOWS)
	unsigned __int64 ullTimeBegin = GetTickCount();
	int iRet = reader.DecodeFile(pszImageFile);
	unsigned __int64 ullTimeEnd = GetTickCount();
	#else
	struct timeval begin, end;
	float fCostTime = 0;
	gettimeofday(&begin, NULL);
	int iRet = reader.DecodeFile(pszImageFile);
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

	SBarcodeResultArray *paryResult = NULL;
	reader.GetBarcodes(&paryResult);
	
	if (paryResult->iBarcodeCount == 0)
	{
		#if defined(WINDOWS)
		sprintf_s(pszTemp, 4096, "No barcode found. Total time spent: %.3f seconds.\r\n", ((float)(ullTimeEnd - ullTimeBegin)/1000));
		printf(pszTemp);
		free(pszTemp);
		#else 
		printf("No barcode found. Total time spent: %.3f seconds.\n", fCostTime);
		#endif
		reader.FreeBarcodeResults(&paryResult);
		return 0;
	}
	
	#if defined(WINDOWS)
	sprintf_s(pszTemp, 4096, "Total barcode(s) found: %d. Total time spent: %.3f seconds\r\n\r\n", paryResult->iBarcodeCount, ((float)(ullTimeEnd - ullTimeBegin)/1000));
	printf(pszTemp);
	#else 
	printf("Total barcode(s) found: %d. Total time spent: %.3f seconds\n\n", paryResult->iBarcodeCount, fCostTime);
	#endif
	for (int iIndex = 0; iIndex < paryResult->iBarcodeCount; iIndex++)
	{
		#if defined(WINDOWS)
		sprintf_s(pszTemp, 4096, "Barcode %d:\r\n", iIndex + 1);
		printf(pszTemp);
		sprintf_s(pszTemp, 4096, "    Page: %d\r\n", paryResult->ppBarcodes[iIndex]->iPageNum);
		printf(pszTemp);
		sprintf_s(pszTemp, 4096, "    Type: %s\r\n", paryResult->ppBarcodes[iIndex]->pBarcodeFormatString);
		printf(pszTemp);
		sprintf_s(pszTemp, 4096, "    Value: %s\r\n", paryResult->ppBarcodes[iIndex]->pBarcodeData);
		printf(pszTemp);

		char *pszTemp1 = (char*)malloc(paryResult->ppBarcodes[iIndex]->iBarcodeDataLength*3 + 1);
		ToHexString(paryResult->ppBarcodes[iIndex]->pBarcodeData, paryResult->ppBarcodes[iIndex]->iBarcodeDataLength, pszTemp1);
		sprintf_s(pszTemp, 4096, "    Hex Data: %s\r\n", pszTemp1);
		printf(pszTemp);
		free(pszTemp1);

		sprintf_s(pszTemp, 4096, "    Region: {Left: %d, Top: %d, Width: %d, Height: %d}\r\n",
			paryResult->ppBarcodes[iIndex]->iLeft, paryResult->ppBarcodes[iIndex]->iTop, 
			paryResult->ppBarcodes[iIndex]->iWidth, paryResult->ppBarcodes[iIndex]->iHeight);
		printf(pszTemp);

		sprintf_s(pszTemp, 4096, "    Module Size: %d\r\n", paryResult->ppBarcodes[iIndex]->iModuleSize);
		printf(pszTemp);
		sprintf_s(pszTemp, 4096, "    Angle: %d\r\n\r\n", paryResult->ppBarcodes[iIndex]->iAngle);
		printf(pszTemp);
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
	reader.FreeBarcodeResults(&paryResult);

	return 0;
}
