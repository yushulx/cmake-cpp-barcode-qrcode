/*
 *	DynamsoftBarcodeReader.h
 *	Dynamsoft Barcode Reader C/C++ API header file.
 *
 *	Copyright 2017 Dynamsoft Corporation. All rights reserved.
 */

#ifndef __DYNAMSOFT_BARCODE_READER_H__
#define __DYNAMSOFT_BARCODE_READER_H__

#if !defined(_WIN32) && !defined(_WIN64)
#define DBR_API __attribute__((visibility("default")))
typedef signed char BOOL;
typedef void* HANDLE;
#else
	#ifdef DBR_EXPORTS
		#define DBR_API __declspec(dllexport)
	#else
		#define DBR_API 
	#endif
#include <windows.h>
#endif

//1. Error Code definition
#define DBR_OK									0
#define DBRERR_UNKNOWN						-10000
#define DBRERR_NOMEMORY						-10001	
#define DBRERR_NULL_POINTER					-10002	
#define DBRERR_LICENSE_INVALID				-10003	
#define DBRERR_LICENSE_EXPIRED				-10004	
#define DBRERR_FILE_NOT_FOUND				-10005	
#define DBRERR_FILETYPE_NOT_SUPPORT			-10006	
#define DBRERR_BPP_NOT_SUPPORT				-10007	
#define DBRERR_INDEX_INVALID				-10008
#define DBRERR_BARCODE_FORMAT_INVALID		-10009
#define DBRERR_CUSTOM_REGION_INVALID		-10010
#define DBRERR_MAX_BARCODE_NUMBER_INVALID	-10011
#define DBRERR_IMAGE_READ_FAIL				-10012
#define DBRERR_TIFF_READ_FAIL				-10013
#define DBRERR_QR_LICENSE_INVALID			-10016
#define DBRERR_1D_LICENSE_INVALID			-10017
#define DBRERR_INVALID_DIB_BUFFER			-10018
#define DBRERR_PDF417_LICENSE_INVALID		-10019
#define DBRERR_DATAMATRIX_LICENSE_INVALID	-10020
#define DBRERR_PDF_READ_FAIL				-10021
#define	DBRERR_PDF_DLL_MISS					-10022
#define DBRERR_PAGE_NUMBER_INVALID			-10023
#define DBRERR_CUSTOM_SIZE_INVALID			-10024
#define DBRERR_CUSTOM_MODULESIZE_INVALID	-10025
#define DBRERR_RECOGNITION_TIMEOUT			-10026

//3. Enums
typedef enum 
{
	BF_All = 0,
	BF_OneD = 0x3FF,
	
	BF_CODE_39 = 0x1,
	BF_CODE_128 = 0x2,
	BF_CODE_93 = 0x4,
	BF_CODABAR = 0x8,
	BF_ITF = 0x10,
	BF_EAN_13 = 0x20,
	BF_EAN_8 = 0x40,
	BF_UPC_A = 0x80,
	BF_UPC_E = 0x100,
	BF_INDUSTRIAL_25 = 0x200,

	BF_PDF417 = 0x2000000,
	BF_QR_CODE = 0x4000000,
	BF_DATAMATRIX = 0x8000000
}BarcodeFormat;

typedef enum 
{
	ICD_Unknown,
	ICD_Scanner,
	ICD_Camera,
	ICD_Fax
}ImageCaptureDevice;

typedef enum 
{
	BCM_DarkOnLight = 0,
	BCM_LightOnDark = 1,
	BCM_DarkAndLight = 2
}BarcodeColorMode;

typedef enum 
{
	SRS_Left,
	SRS_Top,
	SRS_Right,
	SRS_Bottom
}ScanRegionSide;

typedef enum 
{
	BOT_Horizontal,
	BOT_Vertical
}BarcodeOrientationType;

typedef enum 
{
	BTE_Default = 0,
	BTE_SHIFT_JIS_932 = 932,
	BTE_GB2312_936 = 936,
	BTE_KOREAN_949 = 949,
	BTE_BIG5_950 = 950,
	BTE_UTF16 = 1200,
	BTE_UTF16BE = 1201,
	BTE_UTF8 = 65001
}BarcodeTextEncoding;

typedef enum 
{
	IPF_Binary,			//0:Black, 1:White
	IPF_BinaryInverted,	//0:White, 1:Black
	IPF_GrayScaled,		//8bit gray
	IPF_NV21,			//NV21:
	IPF_RGB_565,		//16bit
	IPF_RGB_555,		//16bit
	IPF_RGB_888,		//24bit
	IPF_ARGB_8888,		//32bit
}ImagePixelFormat;

//4. Structs
#pragma pack(push)
#pragma pack(1)
typedef struct tagSBarcodeResult
{
	BarcodeFormat emBarcodeFormat;
	char* pBarcodeData;
	int iBarcodeDataLength;
	int iLeft;
	int iTop;
	int iWidth;
	int iHeight;
	int iX1;
	int iY1;
	int iX2;
	int iY2;
	int iX3;
	int iY3;
	int iX4;
	int iY4;
	int iPageNum;
	wchar_t* pBarcodeText;
	int iAngle;
	int iModuleSize;
	BOOL bIsUnrecognized;
	const char* pBarcodeFormatString;
} SBarcodeResult;

typedef struct tagSBarcodeResultArray
{
	int iBarcodeCount;
	SBarcodeResult **ppBarcodes;
} SBarcodeResultArray;
#pragma pack(pop)

//5. C Functions
#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

	DBR_API void*  DBR_CreateInstance();	
	DBR_API void DBR_DestroyInstance(void*  hBarcode);
	
	DBR_API int  DBR_InitLicenseEx(void*  hBarcode, const char* pLicense);
	
	DBR_API void DBR_SetBarcodeFormats(void*  hBarcode, int iFormat);
	DBR_API int  DBR_GetBarcodeFormats(void*  hBarcode);
	
	DBR_API void DBR_SetMaxBarcodesNumPerPage(void*  hBarcode, int nCount);
	DBR_API int  DBR_GetMaxBarcodesNumPerPage(void*  hBarcode);

	DBR_API void DBR_SetImageCaptureDevice(void*  hBarcode, ImageCaptureDevice emDevice);
	DBR_API ImageCaptureDevice DBR_GetImageCaptureDevice(void*  hBarcode);

	DBR_API void DBR_SetUseOneDDeblur(void*  hBarcode, BOOL bFlag);
	DBR_API BOOL DBR_GetUseOneDDeblur(void*  hBarcode);
	
	DBR_API void DBR_SetBarcodeColorMode(void*  hBarcode, BarcodeColorMode eMode);
	DBR_API BarcodeColorMode DBR_GetBarcodeColorMode(void*  hBarcode);

	DBR_API void DBR_SetTimeoutPerPage(void*  hBarcode, int iMilliSeconds);
	DBR_API int  DBR_GetTimeoutPerPage(void*  hBarcode);

	DBR_API void DBR_SetBarcodeTextEncoding(void* hBarcode, BarcodeTextEncoding emEncoding);
	DBR_API BarcodeTextEncoding DBR_GetBarcodeTextEncoding(void* hBarcode);

	DBR_API void DBR_SetReturnUnrecognizedBarcode(void*  hBarcode, BOOL bFlag);
	DBR_API BOOL DBR_GetReturnUnrecognizedBarcode(void*  hBarcode);

	DBR_API int  DBR_AddPage(void* hBarcode, int iPage);
	DBR_API int  DBR_GetPageCount(void* hBarcode);
	DBR_API int  DBR_GetPage(void* hBarcode, int iIndex, int* piPage);
	DBR_API void DBR_ClearAllPages(void* hBarcode);

	DBR_API int  DBR_AddRegion(void* hBarcode, int iLeft, int iTop, int iRight, int iBottom, BOOL bByPercentage);
	DBR_API int  DBR_AddRegion2(void* hBarcode, ScanRegionSide emSide, int iPercentage);
	DBR_API int  DBR_GetRegionCount(void* hBarcode);
	DBR_API int  DBR_GetRegion(void* hBarcode, int iIndex, int *piLeft, int* piTop, int* piRight, int* piBottom, BOOL* pbByPercentage);
	DBR_API void DBR_ClearAllRegions(void* hBarcode);

	DBR_API int  DBR_AddWidthRange(void* hBarcode, int iMinWidth, int iMaxWidth);
	DBR_API int  DBR_GetWidthRangeCount(void* hBarcode);
	DBR_API int  DBR_GetWidthRange(void* hBarcode, int iIndex, int* piMinWidth, int* piMaxWidth);
	DBR_API void DBR_ClearAllWidthRanges(void* hBarcode);

	DBR_API int  DBR_AddHeightRange(void* hBarcode, int iMinHeight, int iMaxHeight);
	DBR_API int  DBR_GetHeightRangeCount(void* hBarcode);
	DBR_API int  DBR_GetHeightRange(void* hBarcode, int iIndex, int* piMinHeight, int* piMaxHeight);
	DBR_API void DBR_ClearAllHeightRanges(void* hBarcode);

	DBR_API int  DBR_AddModuleSizeRange(void* hBarcode, int iMinModuleSize, int iMaxModuleSize);
	DBR_API int  DBR_GetModuleSizeRangeCount(void* hBarcode);
	DBR_API int  DBR_GetModuleSizeRange(void* hBarcode, int iIndex, int* piMinModuleSize, int* piMaxModuleSize);
	DBR_API void DBR_ClearAllModuleSizeRanges(void* hBarcode);	

	DBR_API void DBR_AddAngleRange(void* hBarcode, int iFromAngle, int iToAngle);
	DBR_API void DBR_AddAngle(void* hBarcode, BarcodeOrientationType emType);
	DBR_API int  DBR_GetAngleRangeCount(void* hBarcode);
	DBR_API int  DBR_GetAngleRange(void* hBarcode, int iIndex, int* piFromAngle, int* piToAngle);
	DBR_API void DBR_ClearAllAngleRanges(void* hBarcode);

	DBR_API BOOL DBR_LoadSetting(void* hBarcode, const char* pJsonSetting);

	DBR_API int  DBR_DecodeFileEx(void*  hBarcode, const char* pFileName, SBarcodeResultArray **ppResults);
	DBR_API int  DBR_DecodeBufferEx(void*  hBarcode, unsigned char* pBuffer, int iWidth, int iHeight, int iStride, ImagePixelFormat format, SBarcodeResultArray **ppResults);
	DBR_API int  DBR_DecodeStreamEx(void*  hBarcode, unsigned char* pFileStream, int iFileSize, SBarcodeResultArray **ppResults);
	DBR_API int  DBR_DecodeBase64StringEx(void*  hBarcode, const char* pBase64String, SBarcodeResultArray **ppResults);

	DBR_API int  DBR_DecodeDIBEx(void*  hBarcode, HANDLE  hDIB, SBarcodeResultArray **ppResults);	
	DBR_API int  DBR_FreeBarcodeResults(SBarcodeResultArray **ppResults);
	DBR_API const char* DBR_GetErrorString(int iErrorCode);
	DBR_API const char* DBR_GetVersion();

#ifdef __cplusplus
}
#endif  /* __cplusplus */


//6. C++ class
#ifdef __cplusplus

class BarcodeReaderInner;

class DBR_API CBarcodeReader
{
private:
	BarcodeReaderInner* m_pBarcodeReader;

public:
	CBarcodeReader();
	~CBarcodeReader();

	int InitLicense(const char* pLicense);

	int DecodeFile(const char* pFileName);
	int DecodeBufferEx(unsigned char* pBuffer, int iWidth, int iHeight, int iStride, ImagePixelFormat format);
	int DecodeStream(unsigned char* pFileStream, int iFileSize);
	int DecodeBase64String(const char* pBase64String);

	int DecodeDIB(HANDLE hDIB);

	int GetBarcodes(SBarcodeResultArray** ppResults);
	static void FreeBarcodeResults(SBarcodeResultArray **ppResults);

	void SetBarcodeFormats(int iFormat);
	int  GetBarcodeFormats();

	void SetMaxBarcodesNumPerPage(int nCount);
	int  GetMaxBarcodesNumPerPage();

	void SetImageCaptureDevice(ImageCaptureDevice emDevice);
	ImageCaptureDevice GetImageCaptureDevice();

	void SetUseOneDDeblur(BOOL bFlag);
	BOOL GetUseOneDDeblur();

	void SetBarcodeColorMode(BarcodeColorMode eMode);
	BarcodeColorMode GetBarcodeColorMode();

	void SetTimeoutPerPage(int iMilliSeconds);
	int  GetTimeoutPerPage();

	void SetBarcodeTextEncoding(BarcodeTextEncoding emMode);
	BarcodeTextEncoding GetBarcodeTextEncoding();

	void SetReturnUnrecognizedBarcode(BOOL bFlag);
	BOOL GetReturnUnrecognizedBarcode();

	int  AddPage(int iPage);
	int  GetPageCount();
	int  GetPage(int iIndex, int* piPage);
	void ClearAllPages();

	int  AddRegion(int iLeft, int iTop, int iRight, int iBottom, BOOL bByPercentage);
	int  AddRegion(ScanRegionSide emSide, int iPercentage);
	int  GetRegionCount();
	int  GetRegion(int iIndex, int *piLeft, int* piTop, int* piRight, int* piBottom, BOOL* pbByPercentage);
	void ClearAllRegions();

	int  AddWidthRange(int iMinWidth, int iMaxWidth);
	int  GetWidthRangeCount();
	int  GetWidthRange(int iIndex, int *piMinWidth, int* piMaxWdith);
	void ClearAllWidthRanges();

	int  AddHeightRange(int iMinHeight, int iMaxHeight);
	int  GetHeightRangeCount();
	int  GetHeightRange(int iIndex, int* piMinHeight, int* piMaxHeight);
	void ClearAllHeightRanges();

	int  AddModuleSizeRange(int iMinModuleSize, int iMaxModuleSize);
	int  GetModuleSizeRangeCount();
	int  GetModuleSizeRange(int iIndex, int *piMinModuleSize, int* piMaxModuleSize);
	void ClearAllModuleSizeRanges();

	void AddAngleRange(int iFromAngle, int iToAngle);
	void AddAngle(BarcodeOrientationType emType);
	int  GetAngleRangeCount();
	int  GetAngleRange(int iIndex, int* piFromAngle, int* piToAngle);
	void ClearAllAngleRanges();

	BOOL LoadSetting(const char* pJsonSetting);

private:
	CBarcodeReader(const CBarcodeReader& r);
	CBarcodeReader& operator = (const CBarcodeReader& r);
};
#endif  /* __cplusplus */

#endif