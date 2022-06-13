#include <stdio.h>
#include "DynamsoftBarcodeReader.h"
#include <iostream>
#include <fstream>
#include <thread>

using namespace std;
using namespace dynamsoft::dbr;

#if defined(LINUX) || defined(MACOS)
#include <sys/time.h>

int gettime()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (int)(time.tv_sec * 1000 * 1000 + time.tv_usec) / 1000;
}
#else
int gettime()
{
	return (int)(GetTickCount());
}
#endif

char *read_file_text(const char *filename)
{
	FILE *fp = fopen(filename, "r");
	size_t size;
	char *text = NULL;
	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		size = ftell(fp);
	}
	else
	{
		cout << "Fail to open file" << endl;
		return NULL;
	}

	rewind(fp);
	text = (char *)calloc((size + 1), sizeof(char));
	if (text == NULL)
	{
		fputs("Memory error", stderr);
		return NULL;
	}

	char c;
	char *tmp = text;
	do
	{
		c = fgetc(fp);
		*tmp = c;
		tmp++;
	} while (c != EOF);
	fclose(fp);
	return text;
}

unsigned char *read_file_binary(const char *filename, int *out_size)
{
	FILE *fp = fopen(filename, "rb");
	size_t size;
	unsigned char *buffer = NULL;
	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		size = ftell(fp);
	}
	else
	{
		cout << "Fail to open file" << endl;
		return NULL;
	}

	rewind(fp);
	buffer = (unsigned char *)malloc(sizeof(unsigned char) * size);
	if (buffer == NULL)
	{
		fputs("Memory error", stderr);
		return NULL;
	}

	size_t result = fread(buffer, 1, size, fp);
	*out_size = size;
	if (result != size)
	{
		fputs("Reading error", stderr);
		return NULL;
	}
	fclose(fp);
	return buffer;
}

int barcode_decoding(const unsigned char *buffer, int size, int formats, int threadcount, char *config)
{
	std::thread::id thread_id = std::this_thread::get_id();
	// Initialize Dynamsoft Barcode Reader
	void *reader = DBR_CreateInstance();
	const char *version = DBR_GetVersion();
	printf("DBR version: %s\n", version);

	// Load the configuration from a template file
	if (config)
	{
		char szErrorMsg[256];
		int ret = DBR_InitRuntimeSettingsWithString(reader, config, CM_OVERWRITE, szErrorMsg, 256);
		if (ret)
			printf("Template status: %s\n\n", szErrorMsg);
	}

	// Update the parameters
	char sError[512];
	PublicRuntimeSettings *runtimeSettings = new PublicRuntimeSettings();
	DBR_GetRuntimeSettings(reader, runtimeSettings);
	runtimeSettings->maxAlgorithmThreadCount = threadcount;
	runtimeSettings->barcodeFormatIds = formats;
	DBR_UpdateRuntimeSettings(reader, runtimeSettings, sError, 512);
	delete runtimeSettings;

	// Read barcodes from file stream
	int starttime = gettime();
	int iRet = DBR_DecodeFileInMemory(reader, buffer, (int)size, "");
	int endtime = gettime();
	int timecost = endtime - starttime;

	// Output barcode result
	if (iRet != DBR_OK && iRet != DBRERR_MAXICODE_LICENSE_INVALID && iRet != DBRERR_AZTEC_LICENSE_INVALID && iRet != DBRERR_LICENSE_EXPIRED && iRet != DBRERR_QR_LICENSE_INVALID && iRet != DBRERR_GS1_COMPOSITE_LICENSE_INVALID &&
		iRet != DBRERR_1D_LICENSE_INVALID && iRet != DBRERR_PDF417_LICENSE_INVALID && iRet != DBRERR_DATAMATRIX_LICENSE_INVALID && iRet != DBRERR_GS1_DATABAR_LICENSE_INVALID && iRet != DBRERR_PATCHCODE_LICENSE_INVALID)
	{
		printf("Failed to read barcode: %s\n", DBR_GetErrorString(iRet));
		// return 0;
	}

	TextResultArray *paryResult = NULL;
	DBR_GetAllTextResults(reader, &paryResult);

	if (paryResult->resultsCount == 0)
	{
		printf("No barcode found.\n");
		DBR_FreeTextResults(&paryResult);
		return -1;
	}

	printf("Thread id: %d. Total barcode(s) found: %d. Time cost: %d ms\n\n", thread_id, paryResult->resultsCount, timecost);

	for (int index = 0; index < paryResult->resultsCount; index++)
	{
		printf("Barcode %d:\n", index + 1);
		printf("    Type: %s\n", paryResult->results[index]->barcodeFormatString);
		printf("    Text: %s\n", paryResult->results[index]->barcodeText);
	}

	DBR_FreeTextResults(&paryResult);

	DBR_DestroyInstance(reader);
	return timecost;
}

void ToHexString(unsigned char *pSrc, int iLen, char *pDest)
{
	const char HEXCHARS[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

	int i;
	char *ptr = pDest;

	for (i = 0; i < iLen; ++i)
	{
		snprintf(ptr, 4, "%c%c ", HEXCHARS[(pSrc[i] & 0xF0) >> 4], HEXCHARS[(pSrc[i] & 0x0F) >> 0]);
		ptr += 3;
	}
}

void multi_thread_performance(int processor_count, unsigned char *buffer, int size, int formats, char *config)
{
	int minimum_count = 1, minimum_timecost = 0;
	for (int i = 0; i < processor_count; i++)
	{
		printf("Thread count: %d. ", i + 1);
		int timecost = barcode_decoding(buffer, size, formats, i, config);
		if (i == 0)
		{
			minimum_count = 1;
			if (timecost > 0)
			{
				minimum_timecost = timecost;
			}
		}
		else
		{
			if (timecost < minimum_timecost)
			{
				minimum_count = i + 1;
				minimum_timecost = timecost;
			}
		}
	}
	printf("Multi-thread best performance: thread_count = %d, timecost = %d \n\n", minimum_count, minimum_timecost);
}

int main(int argc, const char *argv[])
{
	const auto processor_count = std::thread::hardware_concurrency();
	printf("CPU threads: %d\n\n", processor_count);

	if (argc < 2)
	{
		printf("Usage: BarcodeReader [image-file] [optional: license-file] [optional: template-file] \n");
		return 0;
	}

	char *license = NULL;
	char *config = NULL;
	switch (argc)
	{
	case 4:
		config = read_file_text(argv[3]);
	case 3:
		license = read_file_text(argv[2]);
	}

	int size = 0;
	unsigned char *buffer = read_file_binary(argv[1], &size);
	if (!buffer)
		return 0;

	if (license)
	{
		char errorMsgBuffer[512];
		// Click https://www.dynamsoft.com/customer/license/trialLicense/?product=dbr to get a trial license.
		DBR_InitLicense(license, errorMsgBuffer, 512);
		printf("DBR_InitLicense: %s\n", errorMsgBuffer);
	}

	// Call decoding methods on the main thread
	printf("---------------- Single thread decoding performance ----------------\n\n");
	printf("---------------- Decoding barcodes on main thread ----------------\n\n");
	// barcode_decoding(buffer, size, BF_ONED, 1, config);
	// barcode_decoding(buffer, size, BF_CODE_39, 1, config);

	// barcode_decoding(buffer, size, BF_QR_CODE, 1, config);
	// barcode_decoding(buffer, size, BF_PDF417, 1, config);
	// barcode_decoding(buffer, size, BF_DATAMATRIX, 1, config);
	// barcode_decoding(buffer, size, BF_DATAMATRIX | BF_QR_CODE | BF_PDF417, 1, config);
	// barcode_decoding(buffer, size, BF_ALL, 1, config);

	// Call decoding methods on worker threads
	printf("---------------- Decoding barcodes on worker threads ----------------\n\n");
	int starttime = gettime();
	// thread t1(barcode_decoding, buffer, size, BF_ONED);
	// thread t2(barcode_decoding, buffer, size, BF_QR_CODE, 1, config);
	// thread t3(barcode_decoding, buffer, size, BF_PDF417, 1, config);
	// thread t4(barcode_decoding, buffer, size, BF_DATAMATRIX, 1, config);
	// t1.join();
	// t2.join();
	// t3.join();
	// t4.join();
	int endtime = gettime();
	printf("Thread time cost: %d ms\n\n", (endtime - starttime));

	printf("---------------- Multi thread decoding performance ----------------\n\n");
	// 1D
	// printf("-------------------------------- 1D --------------------------------\n\n");
	// multi_thread_performance((int)processor_count, buffer, size, BF_ONED, config);
	// QR
	// printf("-------------------------------- QR --------------------------------\n\n");
	// multi_thread_performance((int)processor_count, buffer, size, BF_QR_CODE, config);
	// All
	printf("-------------------------------- All --------------------------------\n\n");
	multi_thread_performance((int)processor_count, buffer, size, BF_ALL, config);

	free(license);
	free(config);
	free(buffer);
	return 0;
}
