#include <stdio.h>
#include <conio.h>

#include "DynamsoftBarcodeReader.h"
#include "BarcodeReaderConfig.h"

void ToHexString(char* pSrc, int iLen, char* pDest)
{
	const char HEXCHARS[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

	int i;
	char* ptr = pDest;

	for(i = 0; i < iLen; ++i)
	{
		sprintf_s(ptr, 4, "%c%c ", HEXCHARS[ ( pSrc[i] & 0xF0 ) >> 4 ], HEXCHARS[ ( pSrc[i] & 0x0F ) >> 0 ]);
		ptr += 3;
	}
}

int main(int argc, const char* argv[])
{
	fprintf(stdout, "Barcode Reader Version %d.%d\n",
	BarcodeReader_VERSION_MAJOR, BarcodeReader_VERSION_MINOR);

	if (argc < 2) {
        return 0;
	}
	
	int iFormat = BF_All;
	char pszBuffer[512] = {0};
	const char* pszImageFile = argv[1];
	int iMaxCount = 0x7FFFFFFF;
	int iIndex = 0;
	int iRet = -1;
	char * pszTemp = NULL;
	char * pszTemp1 = NULL;
	unsigned __int64 ullTimeBegin = 0;
	unsigned __int64 ullTimeEnd = 0;
	size_t iLen = 0;
	FILE* fp = NULL;
	int iExitFlag = 0;

	iMaxCount = 0x7FFFFFFF;
	iFormat = BF_All;

	// Set license
	CBarcodeReader reader;
	reader.InitLicense("t0068MgAAAAWh296J5PiGHBEz1VmKKA8BIEn718bOC8UijxGsOKXubl1lLkROxFBcgpHBlOAxDn7BXNR+oWTdTU6aJFHx37U=");

	//Set Property
	reader.SetBarcodeFormats(iFormat);
	reader.SetMaxBarcodesNumPerPage(iMaxCount);

	// Read barcode
	iRet = reader.DecodeFile(pszImageFile);
		
	// Output barcode result
	pszTemp = (char*)malloc(4096);
	if (iRet != DBR_OK && iRet != DBRERR_LICENSE_EXPIRED && iRet != DBRERR_QR_LICENSE_INVALID &&
		iRet != DBRERR_1D_LICENSE_INVALID && iRet != DBRERR_PDF417_LICENSE_INVALID && iRet != DBRERR_DATAMATRIX_LICENSE_INVALID)
	{
		sprintf_s(pszTemp, 4096, "Failed to read barcode: %s\r\n", DBR_GetErrorString(iRet));
		printf(pszTemp);
		free(pszTemp);
		return 0;
	}

	SBarcodeResultArray *paryResult = NULL;
	reader.GetBarcodes(&paryResult);
	
	if (paryResult->iBarcodeCount == 0)
	{
		sprintf_s(pszTemp, 4096, "No barcode found. Total time spent: %.3f seconds.\r\n", ((float)(ullTimeEnd - ullTimeBegin)/1000));
		printf(pszTemp);
		free(pszTemp);
		reader.FreeBarcodeResults(&paryResult);
		return 0;
	}
	
	sprintf_s(pszTemp, 4096, "Total barcode(s) found: %d. Total time spent: %.3f seconds\r\n\r\n", paryResult->iBarcodeCount, ((float)(ullTimeEnd - ullTimeBegin)/1000));
	printf(pszTemp);
	for (iIndex = 0; iIndex < paryResult->iBarcodeCount; iIndex++)
	{
		sprintf_s(pszTemp, 4096, "Barcode %d:\r\n", iIndex + 1);
		printf(pszTemp);
		sprintf_s(pszTemp, 4096, "    Page: %d\r\n", paryResult->ppBarcodes[iIndex]->iPageNum);
		printf(pszTemp);
		sprintf_s(pszTemp, 4096, "    Type: %s\r\n", paryResult->ppBarcodes[iIndex]->pBarcodeFormatString);
		printf(pszTemp);
		sprintf_s(pszTemp, 4096, "    Value: %s\r\n", paryResult->ppBarcodes[iIndex]->pBarcodeData);
		printf(pszTemp);

		pszTemp1 = (char*)malloc(paryResult->ppBarcodes[iIndex]->iBarcodeDataLength*3 + 1);
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
	}	

	free(pszTemp);
	reader.FreeBarcodeResults(&paryResult);

	return 0;
}
