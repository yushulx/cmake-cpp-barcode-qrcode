#include <stdio.h>
#include "DynamsoftBarcodeReader.h"
#include "BarcodeReaderConfig.h"
#include <iostream>
#include <fstream>
#include <thread>

#if defined(LINUX) || defined(MACOS)
	#include <sys/time.h>

int DS_GetTime() 
{
	struct timeval time; 
	gettimeofday(&time, NULL);
	return (int)(time.tv_sec * 1000 * 1000 +  time.tv_usec) / 1000;
}						
#else
int DS_GetTime() 
{
	return (int)(GetTickCount());
}
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
	const auto processor_count = std::thread::hardware_concurrency();
	std::cout << "CPU threads: " << processor_count << std::endl;
	fprintf(stdout, "Barcode Reader Version %d.%d\n",
	BarcodeReader_VERSION_MAJOR, BarcodeReader_VERSION_MINOR);

	if (argc < 2) {
		printf("Usage: BarcodeReaderDemo [ImageFilePath]\n");
        return 0;
	}
	
	const char* pszImageFile = argv[1];
	FILE *fp = fopen(pszImageFile, "rb"); 
    size_t size;
    unsigned char *buffer;
	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		size = ftell(fp);
	}
	else {
		return -1;
	}

	rewind(fp);
	buffer = ( unsigned char *)malloc(sizeof( unsigned char) * size);
	if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

	size_t result = fread(buffer, 1, size, fp);
	if (result != size) {fputs ("Reading error",stderr); exit (3);}

	int iRet = 0, fCostTime;

	// Set license
	CBarcodeReader reader;
	const char* pszLicense = "t0068NQAAAGLzp+bAPrZGSCvAFAG0h2+WxZMKkOkYkr6MX6nBwBxH+ex87pm+k9Cowzp4mLRpRCnwGpR2xlsUlr7nBQNdRDM=";
	reader.InitLicense (pszLicense);

	int minimum_thread_count = 1;
	int minimum_time_cost = 0;

	char sError[256];
	reader.InitRuntimeSettingsWithString("{\"ImageParameter\":{\"Name\":\"BestCoverage\",\"MaxAlgorithmThreadCount\": 4, \"DeblurLevel\":9,\"ExpectedBarcodesCount\":512,\"ScaleDownThreshold\":100000,\"LocalizationModes\":[{\"Mode\":\"LM_CONNECTED_BLOCKS\"},{\"Mode\":\"LM_SCAN_DIRECTLY\"},{\"Mode\":\"LM_STATISTICS\"},{\"Mode\":\"LM_LINES\"},{\"Mode\":\"LM_STATISTICS_MARKS\"}],\"GrayscaleTransformationModes\":[{\"Mode\":\"GTM_ORIGINAL\"},{\"Mode\":\"GTM_INVERTED\"}]}}",CM_OVERWRITE,sError,256);
	
	for (int i = 1; i <= (int)processor_count; i++) 
	{
		char sError[512];
		PublicRuntimeSettings* runtimeSettings = new PublicRuntimeSettings();
		reader.GetRuntimeSettings(runtimeSettings);
		runtimeSettings->maxAlgorithmThreadCount = i;
		//turn on the DPM mode
		runtimeSettings->furtherModes.dpmCodeReadingModes[0] = DPMCRM_GENERAL;
		runtimeSettings->localizationModes[0] = LM_STATISTICS_MARKS;
		//update the runtime settings
		reader.UpdateRuntimeSettings(runtimeSettings, sError, 512);
		delete runtimeSettings;

		// Read barcode
		int starttime = DS_GetTime();
		// iRet = reader.DecodeFile(pszImageFile, "");
		iRet = reader.DecodeFileInMemory(buffer, (int)size, "");
		int endtime = DS_GetTime();
		fCostTime = endtime - starttime;
			
		// Output barcode result
		if (iRet != DBR_OK && iRet != DBRERR_MAXICODE_LICENSE_INVALID && iRet != DBRERR_AZTEC_LICENSE_INVALID && iRet != DBRERR_LICENSE_EXPIRED && iRet != DBRERR_QR_LICENSE_INVALID && iRet != DBRERR_GS1_COMPOSITE_LICENSE_INVALID &&
			iRet != DBRERR_1D_LICENSE_INVALID && iRet != DBRERR_PDF417_LICENSE_INVALID && iRet != DBRERR_DATAMATRIX_LICENSE_INVALID && iRet != DBRERR_GS1_DATABAR_LICENSE_INVALID && iRet != DBRERR_PATCHCODE_LICENSE_INVALID)
		{
			printf("Failed to read barcode: %s\n", CBarcodeReader::GetErrorString(iRet));
			// return 0;
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

		if (i == 1) 
		{
			minimum_thread_count = i;
			minimum_time_cost = fCostTime;
		}
		else 
		{
			if (fCostTime < minimum_time_cost)
			{
				minimum_time_cost = fCostTime;
				minimum_thread_count = i;
			}
		}
	}
	
	printf("Best performance: Thread count = %d, time cost = %d\n", minimum_thread_count, minimum_time_cost);
	fclose(fp);
	return 0;
}
