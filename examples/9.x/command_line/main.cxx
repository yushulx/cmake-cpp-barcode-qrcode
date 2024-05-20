#include <stdio.h>
#include "DynamsoftBarcodeReader.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <functional>

using namespace std;
using namespace dynamsoft::dbr;

#if !defined(_WIN32) && !defined(_WIN64)
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

class WorkerThread
{
public:
	std::mutex m;
	std::condition_variable cv;
	std::queue<std::function<void()>> tasks = {};
	volatile bool running;
	std::thread t;
	void *reader;
};

void run(WorkerThread *worker)
{
	while (worker->running)
	{
		std::function<void()> task;
		std::unique_lock<std::mutex> lk(worker->m);
		worker->cv.wait(lk, [&]
						{ return !worker->tasks.empty() || !worker->running; });
		if (!worker->running)
		{
			break;
		}
		task = std::move(worker->tasks.front());
		worker->tasks.pop();
		lk.unlock();

		task();
	}
}

void decode(WorkerThread *worker, const unsigned char *buffer, int size, int formats, int threadcount, char *config)
{
	std::thread::id thread_id = std::this_thread::get_id();

	// Load the configuration from a template file
	if (config)
	{
		char szErrorMsg[256];
		int ret = DBR_InitRuntimeSettingsWithString(worker->reader, config, CM_OVERWRITE, szErrorMsg, 256);
		if (ret)
			printf("Template status: %s\n\n", szErrorMsg);
	}

	// Update the parameters
	char sError[512];
	PublicRuntimeSettings *runtimeSettings = new PublicRuntimeSettings();
	DBR_GetRuntimeSettings(worker->reader, runtimeSettings);
	runtimeSettings->maxAlgorithmThreadCount = threadcount;
	runtimeSettings->barcodeFormatIds = formats;
	DBR_UpdateRuntimeSettings(worker->reader, runtimeSettings, sError, 512);
	delete runtimeSettings;

	// Read barcodes from file stream
	int starttime = gettime();
	int iRet = DBR_DecodeFileInMemory(worker->reader, buffer, (int)size, "");
	int endtime = gettime();
	int timecost = endtime - starttime;

	// Output barcode result
	if (iRet != DBR_OK && iRet != DBRERR_MAXICODE_LICENSE_INVALID && iRet != DBRERR_AZTEC_LICENSE_INVALID && iRet != DBRERR_LICENSE_EXPIRED && iRet != DBRERR_QR_LICENSE_INVALID && iRet != DBRERR_GS1_COMPOSITE_LICENSE_INVALID &&
		iRet != DBRERR_1D_LICENSE_INVALID && iRet != DBRERR_PDF417_LICENSE_INVALID && iRet != DBRERR_DATAMATRIX_LICENSE_INVALID && iRet != DBRERR_GS1_DATABAR_LICENSE_INVALID && iRet != DBRERR_PATCHCODE_LICENSE_INVALID)
	{
		printf("Failed to read barcode: %s\n", DBR_GetErrorString(iRet));
	}

	TextResultArray *paryResult = NULL;
	DBR_GetAllTextResults(worker->reader, &paryResult);

	if (paryResult->resultsCount == 0)
	{
		printf("No barcode found.\n");
		DBR_FreeTextResults(&paryResult);
		return;
	}

	printf("Thread id: %d. Total barcode(s) found: %d. Time cost: %d ms\n\n", thread_id, paryResult->resultsCount, timecost);

	for (int index = 0; index < paryResult->resultsCount; index++)
	{
		printf("Barcode %d:\n", index + 1);
		printf("    Type: %s\n", paryResult->results[index]->barcodeFormatString);
		printf("    Text: %s\n", paryResult->results[index]->barcodeText);
	}

	DBR_FreeTextResults(&paryResult);
}

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

int main(int argc, const char *argv[])
{
	const char *version = DBR_GetVersion();
	printf("DBR version: %s\n", version);

	const auto processor_count = std::thread::hardware_concurrency();
	printf("CPU threads: %d\n\n", processor_count);

	if (argc < 2)
	{
		printf("Usage: BarcodeReader [image-file] [optional: license-file] [optional: template-file] \n");
		return 0;
	}

	char *config = NULL;
	switch (argc)
	{
	case 4:
		config = read_file_text(argv[3]);
	case 3:
		string license;
		ifstream myfile(argv[2]);
		if (myfile.is_open())
		{
			myfile >> license;
			myfile.close();

			char errorMsgBuffer[512];
			// Click https://www.dynamsoft.com/customer/license/trialLicense/?product=dbr to get a trial license.
			DBR_InitLicense(license.c_str(), errorMsgBuffer, 512);
			printf("DBR_InitLicense: %s\n", errorMsgBuffer);
		}
	}

	int size = 0;
	unsigned char *buffer = read_file_binary(argv[1], &size);
	if (!buffer)
		return 0;

	WorkerThread *worker = new WorkerThread();
	worker->reader = DBR_CreateInstance();
	worker->running = true;
	worker->t = std::thread(&run, worker);

	// put tasks to the queue
	for (int i = 0; i < 5; i++)
	{
		std::unique_lock<std::mutex> lk(worker->m);
		if (worker->tasks.size() > 1)
		{
			std::queue<std::function<void()>> empty = {};
			std::swap(worker->tasks, empty);
		}

		std::function<void()> task_function = std::bind(decode, worker, buffer, size, BF_ALL, 1, config);
		worker->tasks.push(task_function);
		worker->cv.notify_one();
		lk.unlock();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	// terminate the thread
	worker->running = false;
	worker->cv.notify_one();
	worker->t.join();

	DBR_DestroyInstance(worker->reader);
	delete worker;
	worker = NULL;

	free(config);
	free(buffer);
	return 0;
}
