#pragma once

#if !defined(_WIN32) && !defined(_WIN64)
#define DLR_API __attribute__((visibility("default")))
#include <stddef.h>
#else
#ifdef DLR_EXPORTS
#define DLR_API __declspec(dllexport)
#else
#define DLR_API 
#endif
#include <windows.h>
#endif

#include "DynamsoftCore.h"


#define DLR_VERSION                  "2.2.10.0616"

/**Recognition timeout*/
#define DLRERR_RECOGNITION_TIMEOUT		-10026

/**Character Model file is not found*/
#define DLRERR_CHARACTER_MODEL_FILE_NOT_FOUND -10100


/**
* @enum LocalizationSourceType
*
* Describes localization source type.
*
*/
typedef enum LocalizationSourceType
{
	/**Define the reference region using the manually specified location.*/
	LST_MANUAL_SPECIFICATION = 0x01,
	
	/**Define the reference region using the result(s) of region predetection process.*/
	LST_PREDETECTED_REGION = 0x02,

	/**Define the reference region using the barcode info.*/
	LST_BARCODE = 0x04
}LocalizationSourceType;



#pragma pack(push)
#pragma pack(1)


/**
* @struct DLR_DictionaryCorrectionThreshold
*
* Stores the dictionary correction threshold.
*/
typedef struct tagDLRDictionaryCorrectionThreshold
{
	int minWordLength;
	int maxWordLength;
	int threshold;
}DLR_DictionaryCorrectionThreshold;

/**
* @struct DLR_Region
*
* Stores the region info.
*
*/
typedef struct tagDLRReferenceRegion
{
	/**The source type used to localize the reference region(s).
	*
	* @par Value range:
	* 	    A value of the LocalizationSourceType Enumeration items.
	* @par Default value:
	* 	    LST_MANUAL_SPECIFICATION
	* @sa DLRLocalizationSourceType
	*
	*/
	LocalizationSourceType localizationSourceType;

	/**Four vertexes in a clockwise direction of a quadrilateral. Index 0 represents the left-most vertex.
	*
	* @par Remarks:
	*     It works only when localizationSourceType is settings to DLR_LST_MANUAL_SPECIFICATION.
	*     The library will localize reference region(s) based on the quadrilateral set by current setting.
	*
	*/
	Quadrilateral location;

	/**Whether or not to use percentage to measure the coordinate.
	*
	* @par Value range:
	* 	    [0, 1]
	* @par Default value:
	* 	    1
	* @par Remarks:
	*     It works only when localizationSourceType is settings to DLR_LST_MANUAL_SPECIFICATION.
	*     0: not by percentage
	*     1: by percentage
	*     When it's set to 1, the values of points indicate percentage (from 0 to 100); Otherwise, they indicate coordinates in pixel.
	*
	*/
	int regionMeasuredByPercentage;

	/**The index of a specific region predetection mode in the regionPredetectionModes parameter.
	*
	* @par Value range:
	* 	    [-1, 0x7fffffff]
	* @par Default value:
	* 	    -1
	* @par Remarks:
	*     It works only when localizationSourceType is settings to DLR_LST_PREDETECTED_REGION.
	*     The library will localize reference region(s) based on the detected regions from the specified region predetection mode.
	*
	*/
	int regionPredetectionModesIndex;

	/**The formats of the barcode in BarcodeFormat group 1.
	*
	* @par Value range:
	* 	    A combined value of BarcodeFormat Enumeration items.
	* @par Default value:
	* 	    DLR_BF_ALL
	* @par Remarks:
	*     Barcode formats in BarcodeFormat group 1 can be combined.
	*     It works only when localizationSourceType is settings to LST_BARCODE.
	*     The library will localize reference region(s) based on the barcodes whose format meets current setting.
	*
	*/
	int barcodeFormatIds;

	/**The formats of the barcode in BarcodeFormat group 2.
	*
	* @par Value range:
	* 	    A combined value of BarcodeFormat_2 Enumeration items.
	* @par Default value:
	* 	    DLR_BF2_NULL
	* @par Remarks:
	*     Barcode formats in BarcodeFormat group 2 can be combined.
	*     It works only when localizationSourceType is settings to LST_BARCODE.
	*     The library will localize reference region(s) based on the barcodes whose format meets current setting.
	*
	*/
	int barcodeFormatIds_2;

	/**The regular express pattern of barcode text.
	*
	* @par Remarks:
	*     It works only when localizationSourceType is settings to DLR_LST_BARCODE.
	*     The library will localize reference region(s) based on the barcodes whose format meets current setting.
	*
	*/
	char barcodeTextRegExPattern[64];

	/**Resered memory for struct. The length of this array indicates the size of the memory reserved for this struct.*/
	char reserved[64];
}DLR_ReferenceRegion;

/**
* Stores the FurtherModes.
*
*/
typedef struct tagDLRFurtherModes
{
	/**Sets the mode and priority for converting a colour image to a grayscale image.
	*
	* @par Value range:
	* 	    Each array item can be any one of the ColourConversionMode Enumeration items.
	* @par Default value:
	* 	    [CICM_GENERAL,CICM_SKIP,CICM_SKIP,CICM_SKIP,CICM_SKIP,CICM_SKIP,CICM_SKIP,CICM_SKIP]
	* @par Remarks:
	*     The array index represents the priority of the item. The smaller index is, the higher priority is.
	* @sa ColourConversionMode
	*/
	ColourConversionMode colourConversionModes[8];

	/**Sets the mode and priority for the grayscale image conversion.
	*
	* @par Value range:
	* 	    Each array item can be any one of the DLRGrayscaleTransformationMode Enumeration items.
	* @par Default value:
	* 	    [GTM_ORIGINAL,GTM_SKIP,GTM_SKIP,GTM_SKIP,GTM_SKIP,GTM_SKIP,GTM_SKIP,GTM_SKIP]
	* @par Remarks:
	*     The array index represents the priority of the item. The smaller index is, the higher priority is.
	* @sa GrayscaleTransformationMode
	*/
	GrayscaleTransformationMode grayscaleTransformationModes[8];

	/**Sets the region pre-detection mode for barcodes search.
	*
	* @par Value range:
	* 	    Each array item can be any one of the RegionPredetectionMode Enumeration items
	* @par Default value:
	* 	    [RPM_GENERAL,RPM_SKIP,RPM_SKIP,RPM_SKIP,RPM_SKIP,RPM_SKIP,RPM_SKIP,RPM_SKIP]
	* @par Remarks:
	*     The array index represents the priority of the item. The smaller index is, the higher priority is.
	*     If the image is large and the barcode on the image is very small, it is recommended to enable region predetection to speed up the localization process and recognition accuracy.
	* @sa RegionPredetectionMode
	*/
	RegionPredetectionMode regionPredetectionModes[8];

	/**Sets the mode and priority for image preprocessing algorithms.
	*
	* @par Value range:
	* 	    Each array item can be any one of the GrayscaleEnhancementMode Enumeration items.
	* @par Default value:
	* 	    [GEM_GENERAL,GEM_SKIP,GEM_SKIP,GEM_SKIP,GEM_SKIP,GEM_SKIP,GEM_SKIP,GEM_SKIP]
	* @par Remarks:
	*     The array index represents the priority of the item. The smaller index is, the higher priority is.
	* @sa GrayscaleEnhancementMode
	*/
	GrayscaleEnhancementMode grayscaleEnhancementModes[8];

	/**Sets the mode and priority for texture detection.
	*
	* @par Value range:
	* 	    Each array item can be any one of the TextureDetectionMode Enumeration items
	* @par Default value:
	* 	    [TDM_GENERAL_WIDTH_CONCENTRATION,TDM_SKIP,TDM_SKIP,TDM_SKIP,TDM_SKIP,TDM_SKIP,TDM_SKIP,TDM_SKIP]
	* @par Remarks:
	*     The array index represents the priority of the item. The smaller index is, the higher priority is.
	* @sa TextureDetectionMode
	*/
	TextureDetectionMode textureDetectionModes[8];

	/**Reserved memory for struct. The length of this array indicates the size of the memory reserved for this struct.
	*
	*/
	char reserved[128];
}DLR_FurtherModes;

/**
* @struct DLR_RuntimeSettings
*
* Defines a struct to configure the runtime settings. These settings control the recognition process.
*
*/
typedef struct tagDLRRuntimeSettings
{
	/**Sets the number of the threads the algorithm will use to recognize label.
	*
	* @par Value range:
	* 	  [1, 4]
	* @par Default value:
	* 	  4
	* @par Remarks:
	*     To keep a balance between speed and quality, the library concurrently runs four different threads by default.
	*
	*/
	int maxThreadCount;

	/**Sets the name of the CharacterModel.
	*
	* @par Value range:
	*     ["Letter", "NumberLetter", "NumberUppercase", "Number"] or other customized character model name.
	*
	*/
	char characterModelName[64];


	/**Sets the reference region to search for text.*/
	DLR_ReferenceRegion referenceRegion;

	/**Sets the text area relative to the reference region.*/
	Quadrilateral textArea;

	/**Sets the dictionnary path.*/
	char dictionaryPath[256];

	/**Sets the dictionary correction threshold.*/
	DLR_DictionaryCorrectionThreshold dictionaryCorrectionThreshold;

	/**Sets the mode and priority for binarization.
	*
	* @par Value range:
	* 	    Each array item can be any one of the BinarizationMode Enumeration items.
	* @par Default value:
	* 	    [BM_LOCAL_BLOCK,BM_SKIP,BM_SKIP,BM_SKIP,BM_SKIP,BM_SKIP,BM_SKIP,BM_SKIP]
	* @par Remarks:
	*     The array index represents the priority of the item. The smaller index is, the higher priority is.
	* @sa BinarizationMode
	*/
	BinarizationMode binarizationModes[8];

	/**Sets further modes.*/
	DLR_FurtherModes furtherModes;
	/**Sets the maximum amount of time (in milliseconds) .
	*
	* @par Value range:
	* 	    [0, 0x7fffffff]
	* @par Default value:
	* 	    10000
	* @par Remarks:
	*	    If you want to stop reading after a certain period of time, you can use this parameter to set a timeout.
	*/
	int timeout;

	/**Reserved memory for the struct.*/
	char reserved[60];
}DLR_RuntimeSettings;

/**
* @struct DLR_CharacterResult
*
* Stores character result.
*
*/
typedef struct tagDLRCharacterResult
{
	/**The recognized character with highest confidence.*/
	char characterH;

	/**The recognized character with middle confidence.*/
	char characterM;

	/**The recognized character with lowest confidence.*/
	char characterL;

	/**The location of current character.*/
	Quadrilateral location;

	/**The confidence of the recognized character with highest confidence.*/
	int characterHConfidence;

	/**The confidence of the recognized character with middle confidence.*/
	int characterMConfidence;

	/**The confidence of the recognized character with lowest confidence.*/
	int characterLConfidence;

	/**Reserved memory for the struct.*/
	char reserved[32];
}DLR_CharacterResult, *PDLR_CharacterResult;

/**
* @struct DLRLineResult
*
* Stores line result.
*
*/
typedef struct tagLineResult
{
	/**The name of the line specification used to recognize current line result.*/
	const char* lineSpecificationName;

	/**The recognized text, ends by '\0'.*/
	const char* text;

	/**The character model used to recognize the text.*/
	const char* characterModelName;

	/**The localization of current line.*/
	Quadrilateral location;

	/**The confidence of the result.*/
	int confidence;

	/**The character result count.*/
	int characterResultsCount;

	/**The character results array.*/
	PDLR_CharacterResult* characterResults;

	/**Reserved memory for the struct.*/
	char reserved[64];
}DLR_LineResult, *PDLR_LineResult;

/**
* @struct DLR_Result
*
* Stores result.
*
*/
typedef struct tagDLRResult
{
	/**The name of the reference region used to recognize current result.*/
	const char* referenceRegionName;

	/**The name of the text area used to recognize current result.*/
	const char* textAreaName;

	/**The localization result.*/
	Quadrilateral location;

	/**The confidence of the result.*/
	int confidence;

	/**The line result count.*/
	int lineResultsCount;

	/**The line results array.*/
	PDLR_LineResult* lineResults;

	/**Page number.*/
	int pageNumber;

	/**Reserved memory for the struct.*/
	char reserved[60];
}DLR_Result, *PDLR_Result;

/**
* @struct DLR_ResultArray
*
* Stores result array.
*
*/
typedef struct tagDLRResultArray
{
	/**The recognized results array.*/
	PDLR_Result* results;

	/**The total count of recognized results.*/
	int resultsCount;
}DLR_ResultArray;


#pragma pack(pop)

#ifdef __cplusplus
extern "C" {
#endif

	/**
	* Returns the error info string.
	*
	* @param [in] errorCode The error code.
	*
	* @return The error message.
	*
	*/
	DLR_API const char* DLR_GetErrorString(const int errorCode);

	/**
	* Returns the version info of the SDK.
	*
	* @return The version info string.
	*
	*/
	DLR_API const char* DLR_GetVersion();

	/**
	* Creates a Dynamsoft DLR instance.
	*
	* @return An DLR instance. If failed, return NULL.
	*
	*/
	DLR_API void* DLR_CreateInstance();

	/**
	* Destorys an instance of Dynamsoft DLR instance.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	*
	*/
	DLR_API void DLR_DestroyInstance(void* recognizer);

	/**
	* Reads product key and activates the SDK. 
	*
	* @param [in] pLicense The product key.
	* 			   
	* @return Returns error code. Returns 0 if the function operates successfully. You can call 
	* 		   DLR_GetErrorString() to get detailed error message.
	*/
	DLR_API int DLR_InitLicense(const char* pLicense, char errorMsgBuffer[], const int errorMsgBufferLen);

	/**
	* Gets current settings and save it into a struct.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	* @param [in, out] pSettings The struct of runtime settings.
	* 
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   DLR_GetErrorString() to get detailed error message.
	*/
	DLR_API int DLR_GetRuntimeSettings(void* recognizer, DLR_RuntimeSettings* pSettings);

	/**
	* Updates runtime settings with a given struct.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	* @param [in] pSettings The struct of runtime settings.
	* @param [in, out] errorMsgBuffer The buffer is allocated by caller and the recommended length is 256. The error message will be copied to the buffer.
	* @param [in] errorMsgBufferLen The length of the allocated buffer.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can check errorMsgBuffer to get detailed error message.
	*/
	DLR_API int DLR_UpdateRuntimeSettings(void* recognizer, DLR_RuntimeSettings* pSettings, char errorMsgBuffer[], const int errorMsgBufferLen);


	/**
	* Initializes runtime settings with the settings in a given JSON string.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	* @param [in] content A JSON string that represents the content of the settings.
	* @param [in,out] errorMsgBuffer (Optional) The buffer is allocated by caller and the recommended length
	* 				  is 256. The error message will be copied to the buffer.
	* @param [in] errorMsgBufferLen (Optional) The length of the allocated buffer.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   GetErrorString() to get detailed error message.
	*
	*/
	DLR_API	int DLR_UpdateRuntimeSettingsFromString(void* recognizer, const char* content, char errorMsgBuffer[], int errorMsgBufferLen);

	/**
	* Reset runtime settings.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	*
	*/
	DLR_API int DLR_ResetRuntimeSettings(void* recognizer);

	/**
	* Sets the optional argument for a specified mode in Modes parameters.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	* @param [in] pModesName The mode parameter name to set argument.
	* @param [in] index The array index of mode parameter to indicate a specific mode.
	* @param [in] pArgumentName The name of the argument to set.
	* @param [in] pArgumentValue The value of the argument to set.
	* @param [in,out] errorMsgBuffer The buffer is allocated by the caller and the recommended length is 256. The error message will be copied to the buffer.
	* @param [in] errorMsgBufferLen The length of the allocated buffer.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can check errorMsgBuffer to get detailed error message.
	*
	*/
	DLR_API int DLR_SetModeArgument(void *recognizer, const char *pModesName, const int index, const char *pArgumentName, const char *pArgumentValue, char errorMsgBuffer[], const int errorMsgBufferLen);

	/**
	* Gets the optional argument for a specified mode in Modes parameters.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	* @param [in] pModesName The mode parameter name to get argument.
	* @param [in] index The array index of mode parameter to indicate a specific mode.
	* @param [in] pArgumentName The name of the argument to get.
	* @param [in,out] valueBuffer The buffer is allocated by caller and the recommended length is 480. The argument value would be copied to the buffer.
	* @param [in] valueBufferLen The length of allocated buffer.
	* @param [in,out] errorMsgBuffer The buffer is allocated by the caller and the recommended length is 256. The error message will be copied to the buffer.
	* @param [in] errorMsgBufferLen The length of the allocated buffer.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can check errorMsgBuffer to get detailed error message.
	*
	*/
	DLR_API int DLR_GetModeArgument(void *recognizer, const char *pModesName, const int index, const char *pArgumentName, char valueBuffer[], const int valueBufferLen, char errorMsgBuffer[], const int errorMsgBufferLen);

	/**
	*
	* Get all template settings' names;
	*
	*/
	DLR_API int DLR_GetAllTemplateSettingsNames(void* recognizer, char(*names)[64], int arrLen);

	/**
	* Clear template settings.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	*
	*/
	DLR_API int DLR_ClearAppendedSettings(void* recognizer);

	/**
	* Appends DLRParameter settings in a string to the SDK object.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance. 
	* @param [in] content A json string that represents the content of the settings.
	* @param [in, out] errorMsgBuffer The buffer is allocated by caller and the recommended length is 256. The error message will be copied to the buffer.
	* @param [in] errorMsgBufferLen The length of the allocated buffer.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can check errorMsgBuffer to get detailed error message.
	*
	*/
	DLR_API int DLR_AppendSettingsFromString(void* recognizer, const char* content, char errorMsgBuffer[], const int errorMsgBufferLen);

	/**
	* Appends DLRParameter settings in a file to the SDK object.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	* @param [in] filePath The settings file path.
	* @param [in, out] errorMsgBuffer The buffer is allocated by caller and the recommended length is 256. The error message will be copied to the buffer.
	* @param [in] errorMsgBufferLen The length of the allocated buffer.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can check errorMsgBuffer to get detailed error message.
	*
	*/
	DLR_API int DLR_AppendSettingsFromFile(void* recognizer, const char* filePath, char errorMsgBuffer[], const int errorMsgBufferLen);

	/**
	* Output DLRParameter settings into a file(JSON file).
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	* @param [in] outputFilePath The output file path which stores settings.
	* @param [in] templateName The name of the template which is to be output.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   DLR_GetErrorString() to get detailed error message.
	*/
	DLR_API int DLR_OutputSettingsToFile(void* recognizer, const char* outputFilePath, const char* templateName);

	/**
	* Output DLRParameter settings into a file(JSON file).
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	* @param [in,out] content The output string which stores the contents of current settings.
	* @param [in] contentLen The length of output string.
	* @param [in] templateName The name of the template which is to be output.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   DLR_GetErrorString() to get detailed error message.
	*/
	DLR_API int DLR_OutputSettingsToString(void* recognizer, char content[], const int contentLen, const char* templateName);

	/**
	* Recognizes text from memory buffer containing image pixels in defined format.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	* @param [in] pImageDate A struct of DLRImageData that represents an image.
	* @param [in] templateName The template name.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   DLR_GetErrorString() to get detailed error message.
	*
	*/
	DLR_API int DLR_RecognizeByBuffer(void* recognizer, const ImageData* pImageData, const char* templateName);

	/**
	* Recognizes text from a specified image file.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	* @param [in] fileName A string defining the file name.
	* @param [in] templateName The template name.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   DLR_GetErrorString() to get detailed error message.
	*
	*/
	DLR_API int DLR_RecognizeByFile(void* recognizer, const char* fileName, const char* templateName);

	/**
	* Recognizes text from a specified image file in memory.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	* @param [in] pFileBytes The image file bytes in memory.
	* @param [in] fileSize The length of the file bytes in memory.
	* @param [in] templateName The template name.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   DLR_GetErrorString() to get detailed error message.
	*
	*/
	DLR_API int DLR_RecognizeFileInMemory(void* recognizer, const unsigned char* pFileBytes, int fileSize, const char* templateName);

	/**
	* Get all recognized results.
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	* @param[in, out] pResults The results are allocated by our SDK and should be freed by calling the function DLR_FreeDLRResults.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		   DLR_GetErrorString() to get detailed error message.
	*
	*/
	DLR_API int DLR_GetAllResults(void* recognizer, DLR_ResultArray** pResults);

	/**
	* Free memory allocated for recognized results.
	*
	* @param[in] pResults Recognized results.
	*
	*/
	DLR_API void DLR_FreeResults(DLR_ResultArray** pResults);

	/**
	* Updates reference region which is defined with source type DLR_LST_BARCODE
	*
	* @param [in] recognizer Handle of Dynamsoft DLR instance.
	* @param [in] barcodeResults The barcode results used to localize reference region.
	* @param [in] templateName The template name. A template name is the value of key LabelRecognitionParameter.Name defined in JSON formatted settings.
	*                          If no template name is specified, current runtime settings will be used.
	*
	* @return Returns error code. Returns 0 if the function operates successfully. You can call
	* 		  DLR_GetErrorString() to get detailed error message.
	*/
	DLR_API int DLR_UpdateReferenceRegionFromBarcodeResults(void* recognizer, BarcodeResultArray* barcodeResults, const char * templateName);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

class LabelRecognizerInner;

namespace dynamsoft
{
	namespace dlr
	{

		class DLR_API CLabelRecognizer
		{
		protected:
			LabelRecognizerInner * m_DLRInner;

		public:
			CLabelRecognizer();

			~CLabelRecognizer();

			/**
			* Returns the error info string.
			*
			* @param [in] errorCode The error code.
			*
			* @return The error message.
			*
			*/
			static const char* GetErrorString(const int errorCode);

			/**
			* Returns the version info of the SDK.
			*
			* @return The version info string.
			*
			*/
			static const char* GetVersion();

			/**
			* Reads product key and activates the SDK.
			*
			* @param [in] pLicense The product key.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		   DLR_GetErrorString() to get detailed error message.
			*/
			static int InitLicense(const char* pLicense, char errorMsgBuffer[]=NULL, const int errorMsgBufferLen=0);

			/**
			* Gets current settings and save it into a struct.
			*
			* @param [in, out] pSettings The struct of runtime settings.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		   DLR_GetErrorString() to get detailed error message.
			*/
			int GetRuntimeSettings(DLR_RuntimeSettings* pSettings);

			/**
			* Updates runtime settings with a given struct.
			*
			* @param [in] pSettings The struct of runtime settings.
			* @param [in, out] errorMsgBuffer The buffer is allocated by caller and the recommended length is 256. The error message will be copied to the buffer.
			* @param [in] errorMsgBufferLen The length of the allocated buffer.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can check errorMsgBuffer to get detailed error message.
			*
			*/
			int UpdateRuntimeSettings(DLR_RuntimeSettings* pSettings, char errorMsgBuffer[] = NULL, const int errorMsgBufferLen = 0);

			/**
			* Initializes runtime settings with the settings in a given JSON string.
			*
			* @param [in] content A JSON string that represents the content of the settings.
			* @param [in,out] errorMsgBuffer (Optional) The buffer is allocated by caller and the recommended length
			* 				  is 256. The error message will be copied to the buffer.
			* @param [in] errorMsgBufferLen (Optional) The length of the allocated buffer.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		   GetErrorString() to get detailed error message.
			*
			*/
			int UpdateRuntimeSettingsFromString(const char* content, char errorMsgBuffer[] = NULL, int errorMsgBufferLen = 0);
			/**
			* Reset runtime settings.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		   DLR_GetErrorString() to get detailed error message.
			*
			*/
			int ResetRuntimeSettings();

			/**
			* Sets the optional argument for a specified mode in Modes parameters.
			*
			* @param [in] pModesName The mode parameter name to set argument.
			* @param [in] index The array index of mode parameter to indicate a specific mode.
			* @param [in] pArgumentName The name of the argument to set.
			* @param [in] pArgumentValue The value of the argument to set.
			* @param [in,out] errorMsgBuffer The buffer is allocated by the caller and the recommended length is 256. The error message will be copied to the buffer.
			* @param [in] errorMsgBufferLen The length of the allocated buffer.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can check errorMsgBuffer to get detailed error message.
			*
			*/
			int SetModeArgument(const char *pModesName, const int index, const char *pArgumentName, const char *pArgumentValue, char errorMsgBuffer[] = NULL, const int errorMsgBufferLen = 0);

			/**
			* Gets the optional argument for a specified mode in Modes parameters.
			*
			* @param [in] pModesName The mode parameter name to get argument.
			* @param [in] index The array index of mode parameter to indicate a specific mode.
			* @param [in] pArgumentName The name of the argument to get.
			* @param [in,out] valueBuffer The buffer is allocated by caller and the recommended length is 480. The argument value would be copied to the buffer.
			* @param [in] valueBufferLen The length of allocated buffer.
			* @param [in,out] errorMsgBuffer The buffer is allocated by the caller and the recommended length is 256. The error message will be copied to the buffer.
			* @param [in] errorMsgBufferLen The length of the allocated buffer.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can check errorMsgBuffer to get detailed error message.
			*
			*/
			int GetModeArgument(const char *pModesName, const int index, const char *pArgumentName, char valueBuffer[], const int valueBufferLen, char errorMsgBuffer[] = NULL, const int errorMsgBufferLen = 0);


			int GetAllTemplateSettingsNames(char(*names)[64], int arrLen);

			/**
			* Clear template settings.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		   DLR_GetErrorString() to get detailed error message.
			*
			*/
			int ClearAppendedSettings();

			/**
			* Appends DLRParameter settings in a string to the SDK object.
			*
			* @param [in] content A json string that represents the content of the settings.
			* @param [in, out] errorMsgBuffer The buffer is allocated by caller and the recommended length is 256. The error message will be copied to the buffer.
			* @param [in] errorMsgBufferLen The length of the allocated buffer.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can check errorMsgBuffer to get detailed error message.
			*
			*/
			int AppendSettingsFromString(const char* content, char errorMsgBuffer[]=NULL, const int errorMsgBufferLen=0);

			/**
			* Appends DLRParameter settings in a file to the SDK object.
			*
			* @param [in] filePath The settings file path.
			* @param [in, out] errorMsgBuffer The buffer is allocated by caller and the recommended length is 256. The error message will be copied to the buffer.
			* @param [in] errorMsgBufferLen The length of the allocated buffer.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can check errorMsgBuffer to get detailed error message.
			*
			*/
			int AppendSettingsFromFile(const char* filePath, char errorMsgBuffer[]=NULL, const int errorMsgBufferLen=0);

			/**
			* Output DLRParameter settings into a file(JSON file).
			*
			* @param [in] outputFilePath The output file path which stores settings.
			* @param [in] templateName The name of the template which is to be output.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		   DLR_GetErrorString() to get detailed error message.
			*
			*/
			int OutputSettingsToFile(const char* outputFilePath, const char* templateName);

			/**
			* Output DLRParameter settings into a file(JSON file).
			*
			* @param [in,out] content The output string which stores the contents of current settings.
			* @param [in] contentLen The length of output string.
			* @param [in] templateName The name of the template which is to be output.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		   DLR_GetErrorString() to get detailed error message.
			*/
			int OutputSettingsToString(char content[], const int contentLen, const char* templateName);

			/**
			* Recognizes text from memory buffer containing image pixels in defined format.
			*
			* @param [in] pImageDate A struct of DLRImageData that represents an image.
			* @param [in] templateName The template name.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		   DLR_GetErrorString() to get detailed error message.
			*
			*/
			int RecognizeByBuffer(const ImageData* pImageData, const char* templateName);

			/**
			* Recognizes text from a specified image file.
			*
			* @param [in] fileName A string defining the file name.
			* @param [in] templateName The template name.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		   DLR_GetErrorString() to get detailed error message.
			*
			*/
			int RecognizeByFile(const char* fileName, const char* templateName);

			/**
			* Recognizes text from a specified image file in memory.
			*
			* @param [in] pFileBytes The image file bytes in memory.
			* @param [in] fileSize The length of the file bytes in memory.
			* @param [in] templateName The template name.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		   DLR_GetErrorString() to get detailed error message.
			*
			*/
			int RecognizeFileInMemory(const unsigned char* pFileBytes, int fileSize, const char* templateName);

			/**
			* Get all recognized results.
			*
			* @param[in, out] pResults The results are allocated by our SDK and should be freed by calling the function DLR_FreeDLRResults.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		   DLR_GetErrorString() to get detailed error message.
			*
			*/
			int GetAllResults(DLR_ResultArray** pResults);

			/**
			* Free memory allocated for recognized results.
			*
			* @param[in] pResults Recognized results.
			*
			*/
			static void FreeResults(DLR_ResultArray** pResults);

			/**
			* Updates reference region which is defined with source type DLR_LST_BARCODE
			*
			* @param [in] barcodeResults The barcode results used to localize reference region.
			* @param [in] templateName The template name. A template name is the value of key LabelRecognizerParameter.Name defined in JSON formatted settings.
			*                          If no template name is specified, current runtime settings will be used.
			*
			* @return Returns error code. Returns 0 if the function operates successfully. You can call
			* 		  GetErrorString() to get detailed error message.
			*/
			int UpdateReferenceRegionFromBarcodeResults(const BarcodeResultArray* barcodeResults, const char * templateName);

		private:
			CLabelRecognizer(const CLabelRecognizer& r);
			CLabelRecognizer& operator=(const CLabelRecognizer& r);
		};
	}
}
#endif