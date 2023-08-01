#pragma once

#define DYNAMSOFT_CORE_VERSION "3.0.0.629"

/**Enumeration section*/

/**
* @enum ErrorCode
*
* Describes the error code that can be output by the library.
*/
typedef enum ErrorCode {
	/**Successful. */
	EC_OK = 0,

	/** -10000~-19999: Common error code. */
	/**Unknown error. */
	EC_UNKNOWN = -10000,

	/**Not enough memory to perform the operation. */
	EC_NO_MEMORY = -10001,

	/**Null pointer */
	EC_NULL_POINTER = -10002,

	/**License invalid*/
	EC_LICENSE_INVALID = -10003,

	/**License expired*/
	EC_LICENSE_EXPIRED = -10004,

	/**File not found*/
	EC_FILE_NOT_FOUND = -10005,

	/**The file type is not supported. */
	EC_FILE_TYPE_NOT_SUPPORTED = -10006,

	/**The BPP (Bits Per Pixel) is not supported. */
	EC_BPP_NOT_SUPPORTED = -10007,

	/**The index is invalid.*/
	EC_INDEX_INVALID = -10008,

	/**The input region value parameter is invalid.*/
	EC_CUSTOM_REGION_INVALID = -10010,

	/**Failed to read the image. */
	EC_IMAGE_READ_FAILED = -10012,

	/**Failed to read the TIFF image. */
	EC_TIFF_READ_FAILED = -10013,

	/**The DIB (Device-Independent Bitmaps) buffer is invalid. */
	EC_DIB_BUFFER_INVALID = -10018,

	/**Failed to read the PDF image. */
	EC_PDF_READ_FAILED = -10021,

	/**The PDF DLL is missing. */
	EC_PDF_DLL_MISSING = -10022,

	/**The page number is invalid. */
	EC_PAGE_NUMBER_INVALID = -10023,

	/**The custom size is invalid. */
	EC_CUSTOM_SIZE_INVALID = -10024,

	/** timeout. */
	EC_TIMEOUT = -10026,

	/**Json parse failed*/
	EC_JSON_PARSE_FAILED = -10030,

	/**Json type invalid*/
	EC_JSON_TYPE_INVALID = -10031,

	/**Json key invalid*/
	EC_JSON_KEY_INVALID = -10032,

	/**Json value invalid*/
	EC_JSON_VALUE_INVALID = -10033,

	/**Json name key missing*/
	EC_JSON_NAME_KEY_MISSING = -10034,

	/**The value of the key "Name" is duplicated.*/
	EC_JSON_NAME_VALUE_DUPLICATED = -10035,

	/**Template name invalid*/
	EC_TEMPLATE_NAME_INVALID = -10036,

	/**The name reference is invalid.*/
	EC_JSON_NAME_REFERENCE_INVALID = -10037,

	/**Parameter value invalid*/
	EC_PARAMETER_VALUE_INVALID = -10038,

	/**The domain of your current site does not match the domain bound in the current product key.*/
	EC_DOMAIN_NOT_MATCH = -10039,

	/**The reserved info does not match the reserved info bound in the current product key.*/
	EC_RESERVED_INFO_NOT_MATCH = -10040,

	/**The license key does not match the license content.*/
	EC_LICENSE_KEY_NOT_MATCH = -10043,

	/**Failed to request the license content.*/
	EC_REQUEST_FAILED = -10044,

	/**Failed to init the license.*/
	EC_LICENSE_INIT_FAILED = -10045,

	/**Failed to set mode's argument.*/
	EC_SET_MODE_ARGUMENT_ERROR = -10051,

	/**The license content is invalid.*/
	EC_LICENSE_CONTENT_INVALID = -10052,

	/**The license key is invalid.*/
	EC_LICENSE_KEY_INVALID = -10053,

	/**The license key has no remaining quota.*/
	EC_LICENSE_DEVICE_RUNS_OUT = -10054,

	/**Failed to get mode's argument.*/
	EC_GET_MODE_ARGUMENT_ERROR = -10055,

	/**The Intermediate Result Types license is invalid.*/
	EC_IRT_LICENSE_INVALID = -10056,

	/**Failed to save file.*/
	EC_FILE_SAVE_FAILED = -10058,

	/**The stage type is invalid.*/
	EC_STAGE_TYPE_INVALID = -10059,

	/**The image orientation is invalid.*/
	EC_IMAGE_ORIENTATION_INVALID = -10060,

	/**Complex template can't be converted to simplified settings.*/
	EC_CONVERT_COMPLEX_TEMPLATE_ERROR = -10061,

	/**Reject function call while capturing in progress.*/
	EC_CALL_REJECTED_WHEN_CAPTURING = -10062,

	/**The input image source was not found.*/
	EC_NO_IMAGE_SOURCE = -10063,

	/**Failed to read directory.*/
	EC_READ_DIRECTORY_FAILED = -10064,

	/**[Name] Module not found.*/
	/**Name: */
	/**DynamsoftBarcodeReader*/
	/**DynamsoftLabelRecognizer*/
	/**DynamsoftDocumentNormalizer*/
	EC_MODULE_NOT_FOUND = -10065,
	
	/**The api does not support multi-page files. Please use FileFetcher instead.*/
	EC_MULTI_PAGES_NOT_SUPPORTED = -10066,

	/** -20000~-29999: DLS license error code. */
	/**No license.*/
	EC_NO_LICENSE = -20000,

	/**The Handshake Code is invalid.*/
	EC_HANDSHAKE_CODE_INVALID = -20001,

	/**Failed to read or write license buffer. */
	EC_LICENSE_BUFFER_FAILED = -20002,

	/**Failed to synchronize license info with license server. */
	EC_LICENSE_SYNC_FAILED = -20003,

	/**Device dose not match with buffer. */
	EC_DEVICE_NOT_MATCH = -20004,

	/**Failed to bind device. */
	EC_BIND_DEVICE_FAILED = -20005,

	/**License Client dll is missing.*/
	EC_LICENSE_CLIENT_DLL_MISSING = -20007,

	/**Instance count is over limit.*/
	EC_INSTANCE_COUNT_OVER_LIMIT = -20008,

	/**Interface InitLicense has to be called before creating any SDK objects.*/
	EC_LICENSE_INIT_SEQUENCE_FAILED = -20009,

	/**Trial License*/
	EC_TRIAL_LICENSE = -20010,

	/**The license is not valid for current version*/
	EC_LICENSE_VERSION_NOT_MATCH = -20011,

	/**Failed to reach License Server.*/
	EC_FAILED_TO_REACH_DLS = -20200,


	/**-30000~-39999: DBR error code*/
	/**The barcode format is invalid.*/
	EC_BARCODE_FORMAT_INVALID = -30009,

	/**The QR Code license is invalid.*/
	EC_QR_LICENSE_INVALID = -30016,

	/**The 1D Barcode license is invalid.*/
	EC_1D_LICENSE_INVALID = -30017,

	/**The PDF417 license is invalid.*/
	EC_PDF417_LICENSE_INVALID = -30019,

	/**The DATAMATRIX license is invalid. */
	EC_DATAMATRIX_LICENSE_INVALID = -30020,

	/**The custom module size is invalid. */
	EC_CUSTOM_MODULESIZE_INVALID = -30025,

	/**The AZTEC license is invalid.*/
	EC_AZTEC_LICENSE_INVALID = -30041,

	/**The Patchcode license is invalid.*/
	EC_PATCHCODE_LICENSE_INVALID = -30046,

	/**The Postal code license is invalid.*/
	EC_POSTALCODE_LICENSE_INVALID = -30047,

	/**The DPM license is invalid.*/
	EC_DPM_LICENSE_INVALID = -30048,

	/**The frame decoding thread already exists.*/
	EC_FRAME_DECODING_THREAD_EXISTS = -30049,

	/**Failed to stop the frame decoding thread.*/
	EC_STOP_DECODING_THREAD_FAILED = -30050,

	/**The Maxicode license is invalid.*/
	EC_MAXICODE_LICENSE_INVALID = -30057,

	/**The GS1 Databar license is invalid.*/
	EC_GS1_DATABAR_LICENSE_INVALID = -30058,

	/**The GS1 Composite code license is invalid.*/
	EC_GS1_COMPOSITE_LICENSE_INVALID = -30059,

	/**The DotCode license is invalid.*/
	EC_DOTCODE_LICENSE_INVALID = -30061,

	/**The Pharmacode license is invalid.*/
	EC_PHARMACODE_LICENSE_INVALID = -30062,


	/**-40000~-49999: DLR error code*/
	/**Character Model file is not found*/
	EC_CHARACTER_MODEL_FILE_NOT_FOUND = -40100,


	/**-50000~-59999: DDN error code*/
	/*The quardrilateral is invalid*/
	EC_QUADRILATERAL_INVALID = -50057,


	/**-60000~-69999: DCE error code*/
	/**-70000~-79999: Panorama error code*/
	/**The panorama license is invalid.*/
	EC_PANORAMA_LICENSE_INVALID = -70060,

	/**-80000~-89999: Reserved error code*/
	/**-90000~-99999: DCP error code*/
	/*The resource path does not exist.*/
	EC_RESOURCE_PATH_NOT_EXIST = -90001,

	/*Failed to load resource.*/
	EC_RESOURCE_LOAD_FAILED = -90002,

	/*The code specification is not found.*/
	EC_CODE_SPECIFICATION_NOT_FOUND = -90003,

	/*The full code string is empty.*/
	EC_FULL_CODE_EMPTY = -90004,

	/*Failed to preprocess the full code string.*/
	EC_FULL_CODE_PREPROCESS_FAILED = -90005,

	/*The license for parsing South Africa Driver License is invalid.*/
	EC_ZA_DL_LICENSE_INVALID = -90006,

	/*The license for parsing North America DL/ID is invalid.*/
	EC_AAMVA_DL_ID_LICENSE_INVALID = -90007,

	/*The license for parsing Aadhaar is invalid.*/
	EC_AADHAAR_LICENSE_INVALID = -90008,

	/*The license for parsing Machine Readable Travel Documents is invalid.*/
	EC_MRTD_LICENSE_INVALID = -90009,

	/*The license for parsing Vehicle Identification Number is invalid.*/
	EC_VIN_LICENSE_INVALID = -90010,

	/*The license for parsing customized code type is invalid.*/
	EC_CUSTOMIZED_CODE_TYPE_LICENSE_INVALID = -90011

} ErrorCode;

/**
* @enum ImagePixelFormat
*
* Describes all the supported image pixel formats.
*/
typedef enum ImagePixelFormat
{
	/**0:Black, 1:White */
	IPF_BINARY,

	/**0:White, 1:Black */
	IPF_BINARYINVERTED,

	/**8bit gray */
	IPF_GRAYSCALED,

	/**NV21 */
	IPF_NV21,

	/**16bit with RGB channel order stored in memory from high to low address*/
	IPF_RGB_565,

	/**16bit with RGB channel order stored in memory from high to low address*/
	IPF_RGB_555,

	/**24bit with RGB channel order stored in memory from high to low address*/
	IPF_RGB_888,

	/**32bit with ARGB channel order stored in memory from high to low address*/
	IPF_ARGB_8888,

	/**48bit with RGB channel order stored in memory from high to low address*/
	IPF_RGB_161616,

	/**64bit with ARGB channel order stored in memory from high to low address*/
	IPF_ARGB_16161616,

	/**32bit with ABGR channel order stored in memory from high to low address*/
	IPF_ABGR_8888,

	/**64bit with ABGR channel order stored in memory from high to low address*/
	IPF_ABGR_16161616,

	/**24bit with BGR channel order stored in memory from high to low address*/
	IPF_BGR_888,

	/**0:Black, 255:White */
	IPF_BINARY_8,

	/**NV12 */
	IPF_NV12

} ImagePixelFormat;

/**
* @enum GrayscaleTransformationMode
*
* Describes the grayscale transformation mode.
*/
typedef enum GrayscaleTransformationMode
{
	/**Transforms to inverted grayscale. Recommended for light on dark images. */
	GTM_INVERTED = 0x01,

	/**Keeps the original grayscale. Recommended for dark on light images. */
	GTM_ORIGINAL = 0x02,

	/**Lets the library choose an algorithm automatically for grayscale transformation.*/
	GTM_AUTO = 0x04,

	/**Reserved setting for grayscale transformation mode.*/
#if defined(_WIN32) || defined(_WIN64)
	GTM_REV = 0x80000000,
#else
	GTM_REV = -2147483648,
#endif

	/**Skips grayscale transformation. */
	GTM_SKIP = 0x00

} GrayscaleTransformationMode;

/**
* @enum GrayscaleEnhancementMode
*
* Describes the grayscaleEnhancementMode.
*/
typedef enum GrayscaleEnhancementMode
{
	/**Not supported yet. */
	GEM_AUTO = 0x01,

	/**Takes the unpreprocessed image for following operations. */
	GEM_GENERAL = 0x02,

	/**Preprocesses the image using the gray equalization algorithm. Check @ref IPM for available argument settings.*/
	GEM_GRAY_EQUALIZE = 0x04,

	/**Preprocesses the image using the gray smoothing algorithm. Check @ref IPM for available argument settings.*/
	GEM_GRAY_SMOOTH = 0x08,

	/**Preprocesses the image using the sharpening and smoothing algorithm. Check @ref IPM for available argument settings.*/
	GEM_SHARPEN_SMOOTH = 0x10,

	/**Reserved setting for image preprocessing mode.*/
#if defined(_WIN32) || defined(_WIN64)
	GEM_REV = 0x80000000,
#else
	GEM_REV = -2147483648,
#endif

	/**Skips image preprocessing. */
	GEM_SKIP = 0x00
} GrayscaleEnhancementMode;

/**
* @enum PDFReadingMode
*
* Describes the PDF reading mode.
*/
typedef enum PDFReadingMode
{
	/** Outputs vector data found in the PDFs.*/
	PDFRM_VECTOR = 0x01,

	/**The default value.
	 * Outputs raster data found in the PDFs.
	 * Depending on the argument Resolution,
	 * the SDK may rasterize the PDF pages.
	 * Check the template for available argument settings.*/
	PDFRM_RASTER = 0x02,

	/**Reserved setting for PDF reading mode.*/
#if defined(_WIN32) || defined(_WIN64)
	PDFRM_REV = 0x80000000,
#else
	PDFRM_REV = -2147483648,
#endif
} PDFReadingMode;

/**
* @enum TargetType
*
* Describes the target types.
*/
typedef enum TargetType 
{
	/**The target type of the PDF file is "page". Only available for PDFReadingMode PDFRM_RASTER.*/
	TT_PAGE,

	/**The target type of the PDF file is "image".*/
	TT_IMAGE
} TargetType;

/**
* @enum CapturedResultItemType
*
* Describes all types of captured result item.
*/
typedef enum CapturedResultItemType
{
	/** The type of the CapturedResultItem is "raw image". */
	CRIT_RAW_IMAGE = 1,

	/** The type of the CapturedResultItem is "barcode". */
	CRIT_BARCODE = 2,

	/** The type of the CapturedResultItem is "text line". */
	CRIT_TEXT_LINE = 4,

	/** The type of the CapturedResultItem is "detected quad". */
	CRIT_DETECTED_QUAD = 8,

	/** The type of the CapturedResultItem is "normalized image". */
	CRIT_NORMALIZED_IMAGE = 16,

	/** The type of the CapturedResultItem is "parsed result". */
	CRIT_PARSED_RESULT = 32
} CapturedResultItemType;

/**
* @enum BufferOverflowProtectionMode
*
* Describes the protection modes when the buffer of ImageSourceAdapter is overflow.
*/
typedef enum BufferOverflowProtectionMode 
{
	/** New images are blocked when the buffer is full. */
	BOPM_BLOCK = 0x00,

	/** New images are appended at the end, and the oldest images are pushed out from the beginning if the buffer is full. */
	BOPM_APPEND = 0x01,

} BufferOverflowProtectionMode;

/**
* @enum ImageTagType
*
* Describes the type of the image tag, which is used to distinguish video frame and file images.
*/
typedef enum ImageTagType 
{
	/**The image is a file image.*/
	ITT_FILE_IMAGE,

	/**The image is a video frame.*/
	ITT_VIDEO_FRAME
} ImageTagType;

/**
* @enum VideoFrameQuality
*
* Describes the quality of video frames.
*/
typedef enum VideoFrameQuality 
{
	/**The frame quality is measured to be high.*/
	VFQ_HIGH,

	/**The frame quality is measured to be low.*/
	VFQ_LOW,

	/**The frame quality is unknown.*/
	VFQ_UNKNOWN
} VideoFrameQuality;

/**
* @enum CornerType
*
* Describes how the corner is formed by its sides.
*/
typedef enum CornerType 
{
	/**The sides of the corner is normally intersected.*/
	CT_NORMAL_INTERSECTED = 0,

	/**The sides of the corner is T-intersected.*/
	CT_T_INTERSECTED = 1,

	/**The sides of the corner is cross-intersected.*/
	CT_CROSS_INTERSECTED = 2,

	/**The sides are not intersected but they definitely make up a corner.*/
	CT_NOT_INTERSECTED = 3
} CornerType;

/**
* @enum SectionType
*
* Describes the section of the algorithm. 
* In the IntermediateResultReceiver, the SectionType indicate the algorithm section that produced the IntermediateResult.
*/
typedef enum SectionType
{
	ST_NULL,

	/**The result is output by "region prediction" section.*/
	ST_REGION_PREDETECTION,

	/**The result is output by "barcode localization" section.*/
	ST_BARCODE_LOCALIZATION,

	/**The result is output by "barcode decoding" section.*/
	ST_BARCODE_DECODING,

	/**The result is output by "text line localization" section.*/
	ST_TEXT_LINE_LOCALIZATION,

	/**The result is output by "text line recognition" section.*/
	ST_TEXT_LINE_RECOGNITION,

	/**The result is output by "document detection" section.*/
	ST_DOCUMENT_DETECTION,

	/**The result is output by "document normalization" section.*/
	ST_DOCUMENT_NORMALIZATION,
} SectionType;

/**
* @enum IntermediateResultUnitType
*
* IntermediateResultUnitType is used in each subclass of IntermediateResult to indicate the type of the result. 
* It is also used to declare which kinds IntermediateResult should be output by the library.
*/
enum IntermediateResultUnitType : unsigned long long
{
	/**No IntermediateResult type is specified.*/
	IRUT_NULL = 0,

	/**The type of the IntermediateResult is "colour image".*/
	IRUT_COLOUR_IMAGE = 1,

	/**The type of the IntermediateResult is "scaled down colour image".*/
	IRUT_SCALED_DOWN_COLOUR_IMAGE = 1 << 1,

	/**The type of the IntermediateResult is "grayscale image".*/
	IRUT_GRAYSCALE_IMAGE = 1 << 2,

	/**The type of the IntermediateResult is "transformed grayscale image".*/
	IRUT_TRANSFORMED_GRAYSCALE_IMAGE = 1 << 3,

	/**The type of the IntermediateResult is "enhanced grayscale image".*/
	IRUT_ENHANCED_GRAYSCALE_IMAGE = 1 << 4,

	/**The type of the IntermediateResult is "predected regions".*/
	IRUT_PREDETECTED_REGIONS = 1 << 5,

	/**The type of the IntermediateResult is "binary image".*/
	IRUT_BINARY_IMAGE = 1 << 6,

	/**The type of the IntermediateResult is "texture detection result".*/
	IRUT_TEXTURE_DETECTION_RESULT = 1 << 7,

	/**The type of the IntermediateResult is "texture removed grayscale image".*/
	IRUT_TEXTURE_REMOVED_GRAYSCALE_IMAGE = 1 << 8,

	/**The type of the IntermediateResult is "texture removed binary image".*/
	IRUT_TEXTURE_REMOVED_BINARY_IMAGE = 1 << 9,

	/**The type of the IntermediateResult is "contours".*/
	IRUT_CONTOURS = 1 << 10,

	/**The type of the IntermediateResult is "line segments".*/
	IRUT_LINE_SEGMENTS = 1 << 11,

	/**The type of the IntermediateResult is "text zones".*/
	IRUT_TEXT_ZONES = 1 << 12,

	/**The type of the IntermediateResult is "text removed binary image".*/
	IRUT_TEXT_REMOVED_BINARY_IMAGE = 1 << 13,

	/**The type of the IntermediateResult is "candidate barcode zones".*/
	IRUT_CANDIDATE_BARCODE_ZONES = 1 << 14,

	/**The type of the IntermediateResult is "localized barcodes".*/
	IRUT_LOCALIZED_BARCODES = 1 << 15,

	/**The type of the IntermediateResult is "scale up barcode image".*/
	IRUT_SCALED_UP_BARCODE_IMAGE = 1 << 16,

	/**The type of the IntermediateResult is "deformation resisted barcode image".*/
	IRUT_DEFORMATION_RESISTED_BARCODE_IMAGE = 1 << 17,

	/**The type of the IntermediateResult is "complemented barcode image".*/
	IRUT_COMPLEMENTED_BARCODE_IMAGE = 1 << 18,

	/**The type of the IntermediateResult is "decoded barcodes".*/
	IRUT_DECODED_BARCODES = 1 << 19,

	/**The type of the IntermediateResult is "long lines".*/
	IRUT_LONG_LINES = 1 << 20,

	/**The type of the IntermediateResult is "corners".*/
	IRUT_CORNERS = 1 << 21,

	/**The type of the IntermediateResult is "candidate quad edges".*/
	IRUT_CANDIDATE_QUAD_EDGES = 1 << 22,

	/**The type of the IntermediateResult is "detected quads".*/
	IRUT_DETECTED_QUADS = 1 << 23,

	/**The type of the IntermediateResult is "localized text lines".*/
	IRUT_LOCALIZED_TEXT_LINES = 1 << 24,

	/**The type of the IntermediateResult is "recognized text lines".*/
	IRUT_RECOGNIZED_TEXT_LINES = 1 << 25,

	/**The type of the IntermediateResult is "normalized image".*/
	IRUT_NORMALIZED_IMAGES = 1 << 26,

	/**The type of the IntermediateResult is "all".*/
	IRUT_ALL = 0x7FFFFFF
};

/**
* @enum RegionObjectElementType
*
* RegionObjectElementType is used to determine the particular type of the subclassed of RegionObjectElement.
*/
typedef enum RegionObjectElementType
{
	/**The type of subclass PredetectedRegionElement.*/
	ROET_PREDETECTED_REGION,

	/**The type of subclass LocalizedBarcodeElement.*/
	ROET_LOCALIZED_BARCODE,

	/**The type of subclass DecodedBarcodeElement.*/
	ROET_DECODED_BARCODE,

	/**The type of subclass LocalizedTextLineElement.*/
	ROET_LOCALIZED_TEXT_LINE,

	/**The type of subclass RecognizedTextLineElement.*/
	ROET_RECOGNIZED_TEXT_LINE,

	/**The type of subclass DetectedQuadElement.*/
	ROET_DETECTED_QUAD,

	/**The type of subclass NormalizedImageElement.*/
	ROET_NORMALIZED_IMAGE,

	/**The type of subclass SourceImageElement.*/
	ROET_SOURCE_IMAGE,

	/**The type of subclass TargetROIElement.*/
	ROET_TARGET_ROI,
} RegionObjectElementType;

/**
* @enum ImageCaptureDistanceMode
*
* Describes the shooting mode of the image. It is used in the overlap mode of Panorama.
*/
typedef enum ImageCaptureDistanceMode
{
	/**The image is taken by close-up shot camera.*/
	ICDM_NEAR,

	/**The image is taken by long shot camera.*/
	ICDM_FAR
} ImageCaptureDistanceMode;

/**
* @enum ColourChannelUsageType
*
* Describes how the color channel is used in the image.
*/
typedef enum ColourChannelUsageType
{
	/**Automatic color channel usage determination based on image pixel format and scene.*/
	CCUT_AUTO,

	/**Use all available color channels for processing.*/
	CCUT_FULL_CHANNEL,

	/**Use only the Y(luminance) channel for processing in images represented in the NV21 format.*/
	CCUT_Y_CHANNEL_ONLY,

	/**Use only the red channel for processing in RGB images.*/
	CCUT_RGB_R_CHANNEL_ONLY,

	/**Use only the green channel for processing in RGB images.*/
	CCUT_RGB_G_CHANNEL_ONLY,

	/**Use only the blue channel for processing in RGB images.*/
	CCUT_RGB_B_CHANNEL_ONLY

}ColourChannelUsageType;

/**Structures section*/
#pragma pack(push)
#pragma pack(1)

/**
* @struct IntermediateResultExtraInfo
*
* The IntermediateResultExtraInfo structure represents the extra information for generating an intermediate result unit.
*/
typedef struct IntermediateResultExtraInfo
{
	/**Specifies the name of the TargetROIDef object that generates the intermediate result.*/
	const char* targetROIDefName;

	/**Specifies the name of the task that generates the intermediate result.*/
	const char* taskName;

	/**Specifies whether the intermediate result is section-level result.*/
	bool isSectionLevelResult;

	/**Specifies the SectionType that generates the intermediate result.*/
	SectionType sectionType;

	/**Reserved for future use.*/
	char reserved[64];
}IntermediateResultExtraInfo;

#pragma pack(pop)


#if !defined(_WIN32) && !defined(_WIN64)
#define DS_API __attribute__((visibility("default")))
#include <stddef.h> 
#else
#if defined(ANDROID) || defined(__APPLE__) || defined(__linux__) || ((defined(RELEASE_LIB) || defined(DEBUG_LIB)) && !defined(MULTI_MODULE_FLAG))
#define DS_API
#else
#ifdef DS_EXPORTS
#define DS_API __declspec(dllexport)
#else
#define DS_API __declspec(dllimport)
#endif
#endif
#include <windows.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif	
	/**
	 * Gets error message by error code.
	 *
	 * @param [in] errorCode The error code.
	 *
	 * @return Returns the error message.
	 *
	 */
	DS_API  const char* DC_GetErrorString(int errorCode);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
namespace dynamsoft
{
	namespace dbr {
		class CDecodedBarcodesResult;
		namespace intermediate_results {
			class CCandidateBarcodeZonesUnit;
			class CLocalizedBarcodesUnit;
			class CScaledUpBarcodeImageUnit;
			class CDeformationResistedBarcodeImageUnit;
			class CComplementedBarcodeImageUnit;
			class CDecodedBarcodesUnit;
		}
	}

	namespace dlr {
		class CRecognizedTextLinesResult;
		namespace intermediate_results {
			class CLocalizedTextLinesUnit;
			class CRecognizedTextLinesUnit;
		}
	}

	namespace ddn {
		class CDetectedQuadsResult;
		class CNormalizedImagesResult;
		namespace intermediate_results {
			class CLongLinesUnit;
			class CCornersUnit;
			class CCandidateQuadEdgesUnit;
			class CDetectedQuadsUnit;
			class CNormalizedImagesUnit;
		}
	}

	namespace dcp {
		class CParsedResult;
	}

	namespace basic_structures
	{

#pragma pack(push)
#pragma pack(1)

		/**
		 * The CCoreModule class defines general functions in the core module.
		 */
		class DS_API CCoreModule
		{
		public:
			/**
			 * Returns the version of the core module.
			 *
			 * @return Returns a const char pointer representing the version of the core module.
			 */
			static const char* GetVersion();
		};

		/**
		* The CPoint class represents a point in 2D space. It contains an array of two integers, which represent the coordinates of the point.
		*/
		class DS_API CPoint
		{
		public:
			/**
			* The coordinate array of the point.
			*/
			int coordinate[2];

			/**
			* Transforms the coordinates of a point using a given transformation matrix.
			*/
			static CPoint TransformCoordinates(CPoint originalPoint, double transformationMatrix[9]);
		};

		/**
		* The CContour class represents a contour in 2D space. It contains an array of CPoint objects, which represent the vertices of the contour.
		*/
		class DS_API CContour
		{
		public:
			/**
			* Constructor
			*/
			CContour();

			/**
			* Destructor. It releases the memory of the point array.
			*/
			~CContour();

			/**
			* The number of points in the contour.
			*/
			int pointsCount;

			/**
			* The point array of the contour. The memory will be released by CContour.
			*/
			CPoint* points;
		};

		/**
		* The CLineSegment class represents a line segment in 2D space. It contains two CPoint objects, which represent the start point and end point of the line segment.
		*/
		class DS_API CLineSegment
		{
		public:
			/**
			* The start point of the line segment.
			*/
			CPoint startPoint;

			/**
			* The end point of the line segment.
			*/
			CPoint endPoint;
		};

		/**
		* CCorner is a structure in an image consisting of two line segments and intersection point. A Corner represents a point at which the image's brightness or color sharply changes.
		*/
		class DS_API CCorner
		{
		public:
			/**
			* The type of the corner.
			*/
			CornerType type;

			/**
			* The intersection point of the corner.
			*/
			CPoint intersection;

			/**
			* The first line connected to the corner.
			*/
			CLineSegment line1;

			/**
			* The second line connected to the corner.
			*/
			CLineSegment line2;
		};

		/**
		* CEdge is a structure composed of two Corner points in an image. 
		* A Corner represents a point at which the image's brightness or color sharply changes. Therefore, a CEdge is a line segment connecting two such points that have been identified as Corners.
		*/
		class DS_API CEdge
		{
		public:
			/**
			* The start corner point of the edge.
			*/
			CCorner startCorner;

			/**
			* The end corner point of the edge.
			*/
			CCorner endCorner;
		};

		/**
		* The CQuadrilateral class represents a quadrilateral shape in 2D space. It contains an array of four CPoint objects, which represent the vertices of the quadrilateral.
		*/
		class DS_API CQuadrilateral
		{
		public:
			/**
			* The point array of the quadrilateral.
			*/
			CPoint points[4];

			/**
			* Determines whether a point is inside the quadrilateral.
			*
			* @param [in] point The point to test.
			*
			* @return Returns true if the point inside the quadrilateral, false otherwise.
			*
			*/
			bool Contains(const CPoint* point) const;

			/**
			* Gets the area of the quadrilateral.
			*
			* @return Returns the area of the quadrilateral.
			*
			*/
			int GetArea() const;
		};

		/**
		* The CRect class represents a rectangle in 2D space. It contains four integer values that specify the top, left, right, and bottom edges of the rectangle.
		*/
		class DS_API CRect
		{
		public:
			/**
			* The top edge of the rectangle.
			*/
			int top;

			/**
			* The left edge of the rectangle.
			*/
			int left;

			/**
			* The right edge of the rectangle.
			*/
			int right;

			/**
			* The bottom edge of the rectangle.
			*/
			int bottom;
		};

		/**
		* The CImageTag class represents an image tag that can be attached to an image in a system. It contains information about the image, such as the image ID and the image capture distance mode.
		*/
		class DS_API CImageTag 
		{
		private:
			int imageId;
			ImageCaptureDistanceMode mode;
		public:
			CImageTag();
			/**
			* Destructor
			*/
			virtual ~CImageTag();

			/**
			* Gets the type of the image tag.
			*
			* @return Returns the type of the image tag.
			*
			*/
			virtual ImageTagType GetType() const = 0;

			/**
			* Creates a copy of the image tag.
			*
			* @return Returns a pointer to a copy of the image tag.
			*
			*/
			virtual CImageTag* Clone() const = 0;

			/**
			* Gets the ID of the image.
			*
			* @return Returns the ID of the image.
			*
			*/
			int GetImageId()const;

			/**
			* Sets the ID of the image.
			*
			* @param [in] imgId The ID of the image.
			*
			*/
			void SetImageId(int imgId);

			/**
			* Gets the capture distance mode of the image.
			*
			* @return Returns the capture distance mode of the image.
			*
			*/
			ImageCaptureDistanceMode GetImageCaptureDistanceMode()const;

			/**
			* Sets the capture distance mode of the image.
			*
			* @param [in] mode The capture distance mode of the image.
			*
			*/
			void SetImageCaptureDistanceMode(ImageCaptureDistanceMode mode);
		};

		/**
		* The CFileImageTag class represents an image tag that is associated with a file. It inherits from the CImageTag class and adds two attributes, a file path and a page number.
		*/
		class DS_API CFileImageTag : public CImageTag 
		{
		public:
			/**
			* The constructor of the CFileImageTag class.
			*
			* @param [in] _filePath The file path of the image tag.
			*
			* @param [in] _pageNumber The page number of the image tag.
			*
			*/
			CFileImageTag(const char* _filePath, int _pageNumber, int _totalPages);

			/**
			* The destructor of the CFileImageTag class. It frees the memory allocated for the file path.
			*/
			~CFileImageTag();

			/**
			* Gets the type of the image tag.
			*
			* @return Returns the type of the image tag.
			*
			*/
			ImageTagType GetType() const override;

			/**
			* Creates a copy of the image tag.
			*
			* @return Returns a pointer to a copy of the image tag.
			*
			*/
			CImageTag* Clone() const override;

			/**
			* Gets the file path of the image tag.
			*
			* @return Returns the file path of the image tag.
			*
			*/
			const char* GetFilePath()const;

			/**
			* Gets the page number of the image tag.
			*
			* @return Returns the page number of the image tag.
			*
			*/
			int GetPageNumber()const;
			/**
			* Gets the total pages of the image tag.
			*
			* @return Returns the total pages of the image tag.
			*
			*/
			int GetTotalPages()const;

		protected:
			const char* filePath;
			int pageNumber;
			int totalPages;
		private:
			CFileImageTag(const CFileImageTag&);
			CFileImageTag& operator=(const CFileImageTag&);
		};

		/**
		* The CVideoFrameTag class represents a video frame tag, which is a type of image tag that is used to store additional information about a video frame. It inherits from the CImageTag class and adds additional attributes and methods specific to video frames.
		*/
		class DS_API CVideoFrameTag :public CImageTag
		{
		protected:
			VideoFrameQuality quality;
			bool isCropped;
			CRect* cropRegion;
			int originalWidth;
			int originalHeight;

		public:
			/**
			* Gets the quality of the video frame.
			*
			* @return Returns the quality of the video frame.
			*
			*/
			VideoFrameQuality GetVideoFrameQuality()const;

			/**
			* Determines whether the video frame is cropped.
			*
			* @return Returns true if the video frame is cropped, false otherwise.
			*
			*/
			bool IsCropped()const;

			/**
			* Gets the crop region of the video frame.
			*
			* @return Returns a pointer to a CRect object that represents the crop region of the video frame. It may be NULL.
			*
			*/
			const CRect* GetCropRegion()const;

			/**
			* Gets the original width of the video frame.
			*
			* @return Returns the original width of the video frame.
			*
			*/
			int GetOriginalWidth()const;

			/**
			* Gets the original height of the video frame.
			*
			* @return Returns the original height of the video frame.
			*
			*/
			int GetOriginalHeight()const;

			/**
			* Gets the type of the image tag.
			*
			* @return Returns the type of the image tag.
			*
			*/
			ImageTagType GetType()const override;

			/**
			* Creates a copy of the image tag.
			*
			* @return Returns a pointer to a copy of the image tag.
			*
			*/
			CImageTag* Clone()const override;

			/**
			* The constructor of the CVideoFrameTag class.
			*
			* @param [in] quality The quality of the video frame.
			* @param [in] isCropped A boolean value indicating whether the video frame is cropped.
			* @param [in] cropRegion A pointer to a CRect object that represents the crop region of the video frame.
			* @param [in] originalWidth The original width of the video frame.
			* @param [in] originalHeight The original height of the video frame.
			*
			*/
			CVideoFrameTag(VideoFrameQuality quality, bool isCropped, const CRect* cropRegion,
				int originalWidth, int originalHeight);

			/**
			* The destructor of the CVideoFrameTag class.
			*/
			virtual ~CVideoFrameTag();

		};

		/**
		* The CImageData class represents image data, which contains the image bytes, width, height, stride, pixel format, orientation and a tag.
		*/
		class DS_API CImageData
		{
		protected:
			int bytesLength;
			unsigned char* bytes;
			int width;
			int height;
			int stride;
			ImagePixelFormat format;
			int orientation;
			CImageTag* tag;
		public:
			/**
			* Constructs an empty image data object.
			*/
			CImageData();

			/**
			* Constructs an image data object with the specified parameters.
			*
			* @param [in] _bytesLength The length of the image byte array.
			* @param [in] _bytes The image byte array.
			* @param [in] _width The width of the image.
			* @param [in] _height The height of the image.
			* @param [in] _stride The stride of the image.
			* @param [in] _format The pixel format of the image.
			* @param [in] _orientation The orientation of the image.
			* @param [in] _tag The tag of the image.
			*
			*/
			CImageData(int _bytesLength, const unsigned char* _bytes, int _width, int _height, int _stride,
				ImagePixelFormat _format, int _orientation = 0, const CImageTag* _tag = NULL);

			/**
			* Destructs the image data object and frees the allocated memory.
			*/
			virtual ~CImageData();

			/**
			* Gets the image byte array.
			*
			* @return Returns a pointer to the image byte array.
			*
			*/
			const unsigned char* const GetBytes() const;

			/**
			* Gets the length of the image byte array.
			*
			* @return Returns the length of the image byte array.
			*
			*/
			int GetBytesLength() const;

			/**
			* Gets the width of the image.
			*
			* @return Returns the width of the image.
			*
			*/
			int GetWidth() const;

			/**
			* Gets the height of the image.
			*
			* @return Returns the height of the image.
			*
			*/
			int GetHeight() const;

			/**
			* Gets the stride of the image.
			*
			* @return Returns the stride of the image.
			*
			*/
			int GetStride() const;

			/**
			* Gets the pixel format of the image.
			*
			* @return Returns the pixel format of the image.
			*
			*/
			ImagePixelFormat GetImagePixelFormat() const;

			/**
			* Gets the orientation of the image.
			*
			* @return Returns the orientation of the image.
			*
			*/
			int GetOrientation() const;

			/**
			* Gets the tag of the image.
			*
			* @return Returns a pointer to the tag of the image.
			*
			*/
			const CImageTag* GetImageTag()const;

			/**
			* Sets the tag of the image.
			*
			* @param [in] _tag The tag of the image.
			*
			*/
			void SetImageTag(const CImageTag* _tag);
			
		private:
			CImageData(const CImageData&);
			CImageData& operator=(const CImageData&);
		};

		/**
		* The CCapturedResultItem class represents an item in a captured result. It is an abstract base class with multiple subclasses, each representing a different type of captured item such as barcode, text line, detected quad, normalized image, raw image, parsed item, etc.
		*/
		class DS_API CCapturedResultItem
		{
		public:
			/**
			* Destructor
			*/
			virtual ~CCapturedResultItem() {};

			/**
			* Gets the type of the captured result item.
			*
			* @return Returns the type of the captured result item.
			*
			*/
			virtual CapturedResultItemType GetType() const = 0;

			/**
			* Gets a pointer to the referenced item in the captured result item.
			*
			* @return Returns a pointer to the referenced item in the captured result item. You are not required to release the memory pointed to by the returned pointer.
			*
			*/
			virtual const CCapturedResultItem* GetReferenceItem() const = 0;
		};

		/**
		* The CCapturedResult class represents the result of a capture operation on an image. Internally, CaptureResult stores an array that contains multiple items, each of which may be a barcode, text line, detected quad, normalized image, raw image, parsed item, etc.
		*/
		class DS_API CCapturedResult
		{
		public:
			/**
			* Destructor
			*/
			virtual ~CCapturedResult() {};

			/**
			* Gets the hash ID of the source image.
			*
			* @return Returns the hash ID of the source image as a null-terminated string. You are not required to release the memory pointed to by the returned pointer.
			*
			*/
			virtual const char* GetSourceImageHashId() const = 0;

			/**
			 * Gets a pointer to the CImageTag object containing the tag of the source image.
			 *
			 * @return Returns a pointer to the CImageTag object containing the tag of the source image. You are not required to release the memory pointed to by the returned pointer.
			 *
			 */
			virtual const CImageTag* GetSourceImageTag() const = 0;

			/**
			 * Get the rotation transformation matrix of the original image relative to the rotated image.
			 *
			 * @param [out] matrix A double array which represents the rotation transform matrix.
			 *
			 */
			virtual void GetRotationTransformMatrix(double matrix[9]) const = 0;

			/**
			 * Gets the number of items in the captured result.
			 *
			 * @return Returns the number of items in the captured result.
			 *
			 */
			virtual int GetCount() const = 0;

			/**
			 * Gets a pointer to the CCapturedResultItem object at the specified index.
			 *
			 * @param [in] index The index of the item to retrieve.
			 *
			 * @return Returns a pointer to the CCapturedResultItem object at the specified index.
			 *
			 */
			virtual const CCapturedResultItem* GetItem(int index) const = 0;

			/**
			 * Remove a specific item from the array in the captured result.
			 *
			 * @param [in] item The specific item to remove.
			 *
			 * @return Returns value indicating whether the deletion was successful or not.
			 *
			 */
			virtual int RemoveItem(const CCapturedResultItem* item) = 0;

			/**
			 * Check if the item is present in the array.
			 *
			 * @param [in] item The specific item to check.
			 *
			 * @return Returns a bool value indicating whether the item is present in the array or not.
			 *
			 */
			virtual bool HasItem(const CCapturedResultItem* item) const = 0;

			/**
			 * Gets the error code of the capture operation.
			 *
			 * @return Returns the error code of the capture operation.
			 *
			 */
			virtual int GetErrorCode() const = 0;

			/**
			 * Gets the error message of the capture operation as a null-terminated string.
			 *
			 * @return Returns the error message of the capture operation as a null-terminated string. You are not required to release the memory pointed to by the returned pointer.
			 *
			 */
			virtual const char* GetErrorString() const = 0;
		};

		/**
		* The `CRawImageResultItem` class represents a captured raw image result item. It is a derived class of `CCapturedResultItem` and provides an interface to get the image data.
		*/
		class DS_API CRawImageResultItem : public CCapturedResultItem
		{
		public:
			/**
			* Destructor
			*/
			virtual ~CRawImageResultItem() {};

			/**
			* Gets the image data for the CRawImageResultItem.
			*
			* @return Returns a const pointer to the CImageData object that contains the image data for the CRawImageResultItem.
			*
			*/
			virtual const CImageData* GetImageData() const = 0;
		};

		/**
		* The `CCapturedResultReceiver` class is responsible for receiving captured results. It contains several callback functions for different types of results, including raw image, decoded barcodes, recognized text lines, detected quads, normalized images, and parsed results.
		*/
		class DS_API CCapturedResultReceiver
		{
		protected:
			unsigned int observedResultItemTypes;
			const char* name;

		public:
			/**
			* Constructor.
			*/
			CCapturedResultReceiver();

			/**
			* Destructor.
			*/
			virtual ~CCapturedResultReceiver();

			/**
			* Gets the types of observed result items.
			*
			* @return Returns the types of observed result items.
			*
			*/
			unsigned int GetObservedResultItemTypes();

			/**
			* Gets the name of the captured result receiver.
			*
			* @return Returns the name of the captured result receiver.
			*
			*/
			const char* GetName() const;

			/**
			* Sets the name of the captured result receiver.
			*
			* @param [in] name The name of the captured result receiver.
			*
			*/
			void SetName(const char* name);

			/**
			* Callback function for all captured results. It will be called once for each captured result.
			*
			* @param [in] pResult The captured result.
			*
			*/
			virtual void OnCapturedResultReceived(const CCapturedResult* pResult);

			/**
			* Callback function for raw image results. It will be called once for each raw image result.
			*
			* @param [in] pResult The raw image result.
			*
			*/
			virtual void OnRawImageResultReceived(const CRawImageResultItem* pResult);

			/**
			* Callback function for decoded barcodes results. It will be called once for each decoded barcodes result.
			*
			* @param [in] pResult The decoded barcodes result.
			*
			*/
			virtual void OnDecodedBarcodesReceived(const dbr::CDecodedBarcodesResult* pResult);

			/**
			* Callback function for recognized text lines results. It will be called once for each recognized text lines result.
			*
			* @param [in] pResult The recognized text lines result.
			*
			*/
			virtual void OnRecognizedTextLinesReceived(const dlr::CRecognizedTextLinesResult* pResult);

			/**
			* Callback function for detected quads results. It will be called once for each detected quads result.
			*
			* @param [in] pResult The detected quads result.
			*
			*/
			virtual void OnDetectedQuadsReceived(const ddn::CDetectedQuadsResult* pResult);

			/**
			* Callback function for normalized images results. It will be called once for each normalized images result.
			*
			* @param [in] pResult The normalized images result.
			*
			*/
			virtual void OnNormalizedImagesReceived(const ddn::CNormalizedImagesResult* pResult);

			/**
			* Callback function for parsed results. It will be called once for each parsed result.
			*
			* @param [in] pResult The parsed result.
			*
			*/
			virtual void OnParsedResultsReceived(const dcp::CParsedResult* pResult);

		};

		/**
		* The `CCapturedResultFilter` class is responsible for filtering captured results. It contains several callback functions for different types of results, including raw image, decoded barcodes, recognized text lines, detected quads, normalized images, and parsed results.
		*/
		class DS_API CCapturedResultFilter
		{
		protected:
			unsigned int filteredResultItemTypes;
			const char* name;

		public:
			/**
			* Constructor.
			*/
			CCapturedResultFilter();

			/**
			* Destructor.
			*/
			virtual ~CCapturedResultFilter();

			/**
			* Gets the types of filtered result items.
			*
			* @return Returns the types of filtered result items.
			*
			*/
			unsigned int GetFilteredResultItemTypes();

			/**
			* Gets the name of the captured result filter.
			*
			* @return Returns the name of the captured result filter.
			*
			*/
			const char* GetName() const;

			/**
			* Sets the name of the captured result filter.
			*
			* @param [in] name The name of the captured result filter.
			*
			*/
			void SetName(const char* name);

			/**
			* Callback function for raw image results. It will be called once for each raw image result.
			*
			* @param [in] pResult The raw image result.
			*
			*/
			virtual void OnRawImageResultReceived(CRawImageResultItem* pResult);

			/**
			* Callback function for decoded barcodes results. It will be called once for each decoded barcodes result.
			*
			* @param [in] pResult The decoded barcodes result.
			*
			*/
			virtual void OnDecodedBarcodesReceived(dbr::CDecodedBarcodesResult* pResult);

			/**
			* Callback function for recognized text lines results. It will be called once for each recognized text lines result.
			*
			* @param [in] pResult The recognized text lines result.
			*
			*/
			virtual void OnRecognizedTextLinesReceived(dlr::CRecognizedTextLinesResult* pResult);

			/**
			* Callback function for detected quads results. It will be called once for each detected quads result.
			*
			* @param [in] pResult The detected quads result.
			*
			*/
			virtual void OnDetectedQuadsReceived(ddn::CDetectedQuadsResult* pResult);

			/**
			* Callback function for normalized images results. It will be called once for each normalized images result.
			*
			* @param [in] pResult The normalized images result.
			*
			*/
			virtual void OnNormalizedImagesReceived(ddn::CNormalizedImagesResult* pResult);

			/**
			* Callback function for parsed results. It will be called once for each parsed result.
			*
			* @param [in] pResult The parsed result.
			*
			*/
			virtual void OnParsedResultsReceived(dcp::CParsedResult* pResult);

		};


		/**
		* The CImageSourceAdapter class provides an interface for fetching and buffering images. It is an abstract class that needs to be implemented by a concrete class to provide actual functionality.
		*/
		class DS_API CImageSourceAdapter 
		{
		private:
			class CImageSourceAdapterInner;
			CImageSourceAdapter(const CImageSourceAdapter&);
			CImageSourceAdapter& operator=(const CImageSourceAdapter&);
			CImageSourceAdapterInner* m_inner;
		protected:
			
			/**
			* Adds an image to the buffer of the adapter.
			*
			* @param [in] img The image to add to the buffer.
			* @param [in] bClone Whether the image should be cloned before being added to the buffer.
			*
			*/
			void AddImageToBuffer(const CImageData* img, bool bClone = true);

		public:
			/**
			* Constructor
			*/
			CImageSourceAdapter();

			/**
			* Destructor
			*/
			virtual ~CImageSourceAdapter();
			
			/**
			* Determines whether there are more images left to fetch.
			*
			* @return Returns true if there are more images left to fetch, false otherwise. This function must be implemented in the subclass.
			*
			*/
			virtual bool HasNextImageToFetch()const = 0;
			
			/**
			* Starts fetching images.
			*/
			virtual void StartFetching();

			/**
			* Stops fetching images.
			*/
			virtual void StopFetching();
			
			/**
			* Returns a buffered image.
			*
			* @param [in] removeFromBuffer Whether the image should be removed from the buffer after it is returned.
			*
			* @return Returns a pointer to the image if it exists in the buffer, NULL otherwise.
			*
			*/
			virtual CImageData* GetImage();
			
			/**
			* Sets how many images are allowed to be buffered.
			*
			* @param [in] count The maximum number of images that can be buffered.
			*
			*/
			void SetMaxImageCount(int count);

			/**
			* Returns how many images can be buffered.
			*
			* @return Returns the maximum number of images that can be buffered.
			*
			*/
			int GetMaxImageCount()const;

			/**
			* Sets a mode that determines the action to take when there is a new incoming image and the buffer is full.
			*
			* @param [in] mode The buffer overflow protection mode to set.
			*
			*/
			void SetBufferOverflowProtectionMode(BufferOverflowProtectionMode mode);

			/**
			* Returns the current buffer overflow protection mode.
			*
			* @return Returns the current buffer overflow protection mode.
			*
			*/
			BufferOverflowProtectionMode GetBufferOverflowProtectionMode() const;

			/**
			* Determines whether the image is in the buffer or not.
			*
			* @param [in] imageId The ID of the image to check.
			*
			* @return Returns true if the image is in the buffer, false otherwise.
			*
			*/
			bool HasImage(int imageId)const;
			
			/**
			* Sets the next image to return.
			*
			* @param [in] imageId The ID of the next image to return.
			* @param [in] keepInBuffer Whether the image should be kept in the buffer after it is returned.
			*
			* @return Returns true if the image is in the buffer and is set as the next image to return, false otherwise.
			*
			*/
			bool SetNextImageToReturn(int imageId, bool keepInBuffer = true);

			/**
			* Returns the actual count of buffered images.
			*
			* @return Returns the actual count of buffered images.
			*
			*/
			int GetImageCount() const;

			/**
			* Determines whether the buffer is empty.
			*
			* @return Returns true if the buffer is empty, false otherwise.
			*
			*/
			bool IsBufferEmpty() const;

			/** 
			 * Clears the buffer.
			 */
			void ClearBuffer();
			
			/**
			 * Sets the usage type of a color channel in images.
			 */
			void SetColourChannelUsageType(ColourChannelUsageType type);

			/**
			* Gets the usage type of a color channel in images.
			*
			* @return Returns the usage type of a color channel in images.
			*
			*/
			ColourChannelUsageType GetColourChannelUsageType()const;
		};

		/**
		* The CPDFReadingParameter class represents the parameters for reading a PDF file. It contains the mode of PDF reading, the DPI (dots per inch) value, and the tarGetstype.
		*/
		class DS_API CPDFReadingParameter {
		public:
			/**
			* The mode of PDF reading.
			*/
			PDFReadingMode mode;

			/**
			* The DPI (dots per inch) value.
			*/
			int dpi;

			/**
			* The tarGetstype.
			*/
			TargetType type;
			
			CPDFReadingParameter() {
				mode = PDFRM_RASTER;
				dpi = 300;
				type = TT_PAGE;
			}
		};

		
#pragma pack(pop)
	}

	namespace intermediate_results {
		using namespace basic_structures;

		/**
		* The CRegionObjectElement class represents an element of a region object in 2D space. It is an abstract class that provides the interface for region object elements.
		*
		*/
		class DS_API CRegionObjectElement
		{
		public:
			/**
			* Destructor
			*/
			virtual ~CRegionObjectElement() {};

			/**
			* Get the location of the region object element.
			*
			* @return Returns a CQuadrilateral object which represents the location of the region object element.
			*
			*/
			virtual CQuadrilateral GetLocation() const = 0;

			/**
			* Get a pointer to a referenced region object element.
			*
			* @return Returns a const pointer to a referenced CRegionObjectElement object.
			*
			*/
			virtual const CRegionObjectElement* GetReferencedElement() const = 0;

			/**
			* Get the type of the region object element.
			*
			* @return Returns a RegionObjectElementType enum value which represents the type of the region object element.
			*
			*/
			virtual RegionObjectElementType GetElementType() const = 0;

		};

		/**
		* The CPredetectedRegionElement class represents a region element that has been pre-detected in an image. It is a subclass of the CRegionObjectElement.
		*
		*/
		class DS_API CPredetectedRegionElement : public CRegionObjectElement
		{
		public:
			/**
			* Destructor
			*/
			virtual ~CPredetectedRegionElement() {};

			/**
			* Gets the name of the detection mode used to detect this region element.
			*
			* @return Returns the name of the detection mode used to detect this region element.
			*
			*/
			virtual const char* GetModeName() const = 0;
		};

		/**
		* The CIntermediateResultUnit class represents an intermediate result unit used in image processing. It is an abstract base class with multiple subclasses, each representing a different type of unit such as pre-detected regions, localized barcodes, decoded barcodes, localized text lines, binary image, gray image, etc.
		*/
		class DS_API CIntermediateResultUnit
		{
		protected:
			const char* hashId;
			const char* sourceImageHashId;
			CImageTag* sourceImageTag;
			double transformMatrix[9];
			double rotationMatrix[9];

		public:
			/**
			* Constructor
			*/
			CIntermediateResultUnit();

			/**
			* Destructor
			*/
			virtual ~CIntermediateResultUnit();

			/**
			* Gets the hash ID of the intermediate result unit.
			*
			* @return Returns the hash ID of the unit.
			*
			*/
			const char* GetHashId() const;

			/**
			* Gets the hash ID of the source image.
			*
			* @return Returns the hash ID of the source image.
			*
			*/
			const char* GetSourceImageHashId() const;

			/**
			* Gets the image tag of the source image.
			*
			* @return Returns the image tag of the source image.
			*
			*/
			const CImageTag* GetSourceImageTag() const;

			/**
			* Gets the rotation transformation matrix of the original image relative to the rotated image.
			*
			* @param [out] matrix A double array which represents the rotation transform matrix.
			*
			*/
			void GetRotationTransformMatrix(double matrix[9]) const;

			/**
			* Gets the transformation matrix from local to source image coordinates.
			*
			* @param [out] matrix The transformation matrix.
			*
			*/
			void GetLocalToSourceImageTransformMatrix(double matrix[9]) const;

			/**
			* Gets the type of the intermediate result unit.
			*
			* @return Returns the type of the intermediate result unit.
			*
			*/
			virtual IntermediateResultUnitType GetType() const = 0;

			/**
			* Creates a copy of the intermediate result unit.
			*
			* @return Returns a copy of the intermediate result unit.
			*
			*/
			virtual CIntermediateResultUnit* Clone() const = 0;

			/**
			* Sets the hash ID of the intermediate result unit.
			*
			* @param [in] _hashId The hash ID to set.
			*
			*/
			void SetHashId(const char* _hashId);

			/**
			* Sets the hash ID of the source image.
			*
			* @param [in] _sourceImageHashId The hash ID to set.
			*
			*/
			void SetSourceImageHashId(const char* _sourceImageHashId);

			/**
			* Sets the image tag of the source image.
			*
			* @param [in] _tag The image tag to set.
			*
			*/
			void SetSourceImageTag(const CImageTag* _tag);

			/**
			* Sets the rotation transformation matrix of the original image relative to the rotated image.
			*
			* @param [in] _matrix A double array which represents the rotation transform matrix.
			*
			*/
			void SetRotationTransformMatrix(double _matrix[9]);

			/**
			* Sets the transformation matrix from local to source image coordinates.
			*
			* @param [out] _matrix The transformation matrix.
			*
			*/
			void SetLocalToSourceImageTransformMatrix(double _matrix[9]);

			/**
			* Increases the reference count of the intermediate result unit.
			*
			*/
			virtual void Retain() = 0;

			/**
			* Decreases the reference count of the intermediate result unit.
			*
			*/
			virtual void Release() = 0;
		};

		/**
		* The CIntermediateResult class represents a container containing a collection of CIntermediateResultUnit objects.
		*
		*/
		class DS_API CIntermediateResult
		{
		public:
			/**
			* Destructor
			*/
			virtual ~CIntermediateResult() {};

			/**
			* Gets the number of CIntermediateResultUnit objects in the collection.
			*
			* @return Returns the number of CIntermediateResultUnit objects in the collection.
			*
			*/
			virtual int GetCount() const = 0;

			/**
			* Gets a pointer to a specific CIntermediateResultUnit object in the collection.
			*
			* @param [in] index The index of the CIntermediateResultUnit object to retrieve.
			*
			* @return Returns a const pointer to the specified CIntermediateResultUnit object in the collection. You don't need to release the memory pointed to by the returned pointer.
			*
			*/
			virtual const CIntermediateResultUnit* GetIntermediateResultUnit(int index) const = 0;
		};

		/**
		* The `CColourImageUnit` class represents a unit that contains color image. It is derived from the `CIntermediateResultUnit` class.
		*
		*/
		class DS_API CColourImageUnit : public CIntermediateResultUnit
		{
		public:
			/**
			* Destructor
			*/
			virtual ~CColourImageUnit() {};

			/**
			* Gets the image data of the color image unit.
			*
			* @return Returns a pointer to the CImageData object that contains the image data of the color image unit. You are not required to release the memory pointed to by the returned pointer.
			*
			*/
			virtual const CImageData* GetImageData() const = 0;
		};

		/**
		* The CScaledDownColourImageUnit class represents an intermediate result unit that contains scaled down color image. It is derived from the CIntermediateResultUnit class.
		*/
		class DS_API CScaledDownColourImageUnit : public CIntermediateResultUnit
		{
		public:
			/**
			* Destructor
			*/
			virtual ~CScaledDownColourImageUnit() {};

			/**
			* Gets the image data of the unit.
			*
			* @return Returns a pointer to the CImageData object that contains the image data of the unit. You are not required to release the memory pointed to by the returned pointer.
			*
			*/
			virtual const CImageData* GetImageData() const = 0;
		};

		/**
		* The CGrayscaleImageUnit class represents a grayscale image unit. It is a subclass of CIntermediateResultUnit.
		*/
		class DS_API CGrayscaleImageUnit : public CIntermediateResultUnit
		{
		public:
			/**
			* Destructor
			*/
			virtual ~CGrayscaleImageUnit() {};

			/**
			* Gets the image data of the grayscale image.
			*
			* @return Returns a pointer to the CImageData object that contains the grayscale image. You are not required to release the memory pointed to by the returned pointer.
			*
			*/
			virtual const CImageData* GetImageData() const = 0;
		};

		/**
		* The CTransformedGrayscaleImageUnit class is a subclass of CIntermediateResultUnit that represents a transformed grayscale image. It may be the original grayscale image or the inverted image of the original grayscale image.
		*
		*/
		class DS_API CTransformedGrayscaleImageUnit : public CIntermediateResultUnit
		{
		public:
			/**
			* Destructor
			*/
			virtual ~CTransformedGrayscaleImageUnit() {};

			/**
			* Gets the image data of the transformed grayscale image. It may be the original grayscale image or the inverted image of the original grayscale image.
			*
			* @return Returns a const pointer to a CImageData object that represents the image data of the transformed grayscale image. You don't need to release the memory pointed to by the returned pointer.
			*
			*/
			virtual const CImageData* GetImageData() const = 0;
		};

		/**
		* The CPredetectedRegionsUnit class represents a unit that contains a collection of pre-detected regions. It inherits from the CIntermediateResultUnit class and stores the result of image color pre-detection.
		*/
		class DS_API CPredetectedRegionsUnit : public CIntermediateResultUnit
		{
		public:
			/**
			* Destructor
			*/
			virtual ~CPredetectedRegionsUnit() {};

			/**
			* Gets the number of pre-detected regions in the collection.
			*
			* @return Returns the number of pre-detected regions in the collection.
			*
			*/
			virtual int GetCount() const = 0;

			/**
			* Gets a pointer to a specific pre-detected region in the collection.
			*
			* @param [in] index The index of the pre-detected region to retrieve.
			*
			* @return Returns a const pointer to the specified pre-detected region in the collection. You don't need to release the memory pointed to by the returned pointer.
			*
			*/
			virtual const CPredetectedRegionElement* GetPredectedRegion(int index) const = 0;
		};

		/**
		* The CEnhancedGrayscaleImageUnit class represents an intermediate result unit that contains an enhanced grayscale image data. Gray enhancement methods include gray equalization, gray smoothing, gray sharpening and smoothing.
		*/
		class DS_API CEnhancedGrayscaleImageUnit : public CIntermediateResultUnit
		{
		public:
			/**
			* Destructor
			*/
			virtual ~CEnhancedGrayscaleImageUnit() {};

			/**
			* Gets the enhanced grayscale image data.
			*
			* @return Returns a const pointer to the CImageData object that contains the enhanced grayscale image data. You don't need to release the memory pointed to by the returned pointer.
			*/
			virtual const CImageData* GetImageData() const = 0;
		};

		/**
		* The CBinaryImageUnit class represents a binary image unit that inherits from CIntermediateResultUnit. It inherits from the CIntermediateResultUnit class and stores binary image data.
		*
		*/
		class DS_API CBinaryImageUnit : public CIntermediateResultUnit
		{
		public:
			/**
			* Destructor
			*/
			virtual ~CBinaryImageUnit() {};

			/**
			* Gets a pointer to the binary image data.
			*
			* @return Returns a pointer to the CImageData object containing the binary image data. You don't need to release the memory pointed to by the returned pointer.
			*
			*/
			virtual const CImageData* GetImageData() const = 0;
		};

		/**
		* The CTextureDetectionResultUnit class represents an intermediate result unit for texture detection. It is derived from the CIntermediateResultUnit class and contains the x-direction spacing and y-direction spacing of the texture stripes.
		*
		*/
		class DS_API CTextureDetectionResultUnit : public CIntermediateResultUnit
		{
		public:
			/**
			* Destructor
			*/
			virtual ~CTextureDetectionResultUnit() {};

			/**
			* Gets x-direction spacing of the texture stripes.
			*
			* @return Returns the x-direction spacing of the texture stripes.
			*
			*/
			virtual int GetXSpacing() = 0;

			/**
			* Gets y-direction spacing of the texture stripes.
			*
			* @return Returns the y-direction spacing of the texture stripes.
			*
			*/
			virtual int GetYSpacing() = 0;
		};

		/**
		* The CTextureRemovedGrayscaleImageUnit class represents an intermediate result unit that contains grayscale image data with textures removed.
		*
		*/
		class DS_API CTextureRemovedGrayscaleImageUnit : public CIntermediateResultUnit
		{
		public:
			/**
			* Destructor
			*/
			virtual ~CTextureRemovedGrayscaleImageUnit() {};

			/**
			* Gets the grayscale image data with textures removed.
			*
			* @return Returns a constant pointer to the grayscale image data with textures removed. You don't need to release the memory pointed to by the returned pointer.
			*
			*/
			virtual const CImageData* GetImageData() const = 0;
		};

		/**
		* The `CTextureRemovedBinaryImageUnit` class represents an intermediate result unit that stores binary image data with texture removed.
		*
		*/
		class DS_API CTextureRemovedBinaryImageUnit : public CIntermediateResultUnit
		{
		public:
			/**
			* Destructor
			*/
			virtual ~CTextureRemovedBinaryImageUnit() {};

			/**
			* Gets the image data of the binary image with texture removed.
			*
			* @return Returns a const pointer to CImageData object that represents the binary image with texture removed. You don't need to release the memory pointed to by the returned pointer.
			*
			*/
			virtual const CImageData* GetImageData() const = 0;
		};

		/**
		* The `CTextZonesUnit` class represents a unit that contains text zones. It is derived from `CIntermediateResultUnit` class and provides methods to retrieve the count and details of text zones.
		*
		*/
		class DS_API CTextZonesUnit : public CIntermediateResultUnit
		{
		public:
			/**
			* Destructor
			*/
			virtual ~CTextZonesUnit() {};

			/**
			* Gets the number of text zones in the unit.
			*
			* @return Returns the number of text zones in the unit.
			*
			*/
			virtual int GetCount() const = 0;

			/**
			* Gets the quadrilateral shape of the text zone at the specified index.
			*
			* @param [in] index The index of the text zone.
			* @param [in, out] quad A pointer to a CQuadrilateral object to receive the quadrilateral shape of the text zone.
			*
			* @return Returns 0 if the operation succeeds, or a nonzero error code if the operation fails.
			*
			*/
			virtual int GetTextZone(int index, CQuadrilateral* quad) const = 0;
		};

		/**
		* The CTextRemovedBinaryImageUnit class represents an intermediate result unit that contains a binary image with the text removed.
		*/
		class DS_API CTextRemovedBinaryImageUnit : public CIntermediateResultUnit
		{
		public:
			/**
			* Destructor
			*/
			virtual ~CTextRemovedBinaryImageUnit() {};

			/**
			* Gets the binary image data with the text removed.
			*
			* @return Returns a pointer to the CImageData object that contains the binary image data with the text removed. You don't need to release the memory pointed to by the returned pointer.
			*
			*/
			virtual const CImageData* GetImageData() const = 0;
		};


		/**
		* The CContoursUnit class represents a unit that contains contours as intermediate results. It is derived from the CIntermediateResultUnit class.
		*/
		class DS_API CContoursUnit : public CIntermediateResultUnit
		{
		public:
			/**
			* Destructor
			*/
			virtual ~CContoursUnit() {};

			/**
			* Gets the number of contours in the unit.
			*
			* @return Returns the number of contours in the unit.
			*
			*/
			virtual int GetCount() const = 0;

			/**
			* Gets the contour at the specified index.
			*
			* @param [in] index The index of the contour to get.
			* @param [in, out] contour A pointer to a CContour object that will be filled with the contour data.
			*
			* @return Returns 0 if successful, or an error code if the contour could not be retrieved.
			*
			* Note: The caller of this method is responsible for allocating memory for the `contour` pointer.
			*/
			virtual int GetContour(int index, CContour* contour) const = 0;
		};

		/**
		* The `CLineSegmentsUnit` class represents a collection of line segments in 2D space. It is a derived class of `CIntermediateResultUnit`.
		*
		*/
		class DS_API CLineSegmentsUnit : public CIntermediateResultUnit
		{
		public:
			/**
			* Destructor
			*/
			virtual ~CLineSegmentsUnit() {};

			/**
			* Gets the number of line segments in the collection.
			*
			* @return Returns the number of line segments in the collection.
			*
			*/
			virtual int GetCount() const = 0;

			/**
			* Gets the specified line segment from the collection.
			*
			* @param [in] index The index of the line segment to retrieve.
			*
			* @param [in, out] line The CLineSegment object to store the retrieved line segment.
			*
			* @return Returns 0 if the operation succeeds, or a negative value if an error occurs.
			*
			*/
			virtual int GetLineSegment(int index, CLineSegment* line) const = 0;
		};

		/**
		* The `CObservationParameters` class is used to set filter conditions for the CIntermediateReusltReceiver, so that only intermediate results meeting specific conditions will be called back.
		*
		*/
		class DS_API CObservationParameters
		{
		public:
			/**
			* Sets the types of intermediate result units that have been observed.
			*
			* @param [in] types The observed types of intermediate result units.
			*
			*/
			virtual void SetObservedResultUnitTypes(unsigned long long types) = 0;

			/**
			* Gets the types of intermediate result units that have been observed.
			*
			* @return Returns the observed types of intermediate result units.
			*
			*/
			virtual unsigned long long GetObservedResultUnitTypes() const = 0;

			/**
			* Determines whether the specified result unit type was observed.
			*
			* @param [in] type The specified result unit type.
			*
			* @return Returns a boolean value indicating whether the specified result unit type was observed.
			*
			*/
			virtual bool IsResultUnitTypeObserved(IntermediateResultUnitType type) const = 0;

			/**
			* Adds observed task name to be notified when relevant results are available.
			*
			* @param [in] taskName The specified task name.
			*
			*/
			virtual void AddObservedTask(const char* taskName) = 0;

			/**
			* Removes the observed task name so that intermediate results generated by the task are not notified.
			*
			* @param [in] taskName The specified task name.
			*
			*/
			virtual void RemoveObservedTask(const char* taskName) = 0;

			/**
			* Determines whether the specified task was observed.
			*
			* @param [in] taskName The specified task name.
			*
			* @return Returns a boolean value indicating whether the specified task was observed.
			*
			*/
			virtual bool IsTaskObserved(const char* taskName) const = 0;
		};

		/**
		* The `CIntermediateResultReceiver` class is responsible for receiving intermediate results of different types. 
		* It provides virtual functions for each type of result, which are called when the corresponding result is received.
		*/
		class DS_API CIntermediateResultReceiver
		{
		protected:
			CObservationParameters* parameters;

		public:
			/**
			* Constructor
			*/
			CIntermediateResultReceiver();

			/**
			* Destructor
			*/
			virtual ~CIntermediateResultReceiver();

			/**
			* Gets the observed parameters of the intermediate result receiver.
			*
			* @return Returns the object of CObservationParameters. The default parameters are to observe all intermediate result unit types and all tasks.
			*
			*/
			CObservationParameters* GetObservationParameters();

			/**
			* Called when a task result has been received.
			*
			* @param [in] pResult A pointer to the CIntermediateResult object that contains several result units.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnTaskResultsReceived(CIntermediateResult *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when predetected regions have been received.
			*
			* @param [in] pResult A pointer to the CPredetectedRegionsUnit object that contains the result.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnPredetectedRegionsReceived(CPredetectedRegionsUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when localized barcodes have been received.
			*
			* @param [in] pResult A pointer to the CLocalizedBarcodesUnit object that contains the result.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnLocalizedBarcodesReceived(dbr::intermediate_results::CLocalizedBarcodesUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when decoded barcodes have been received.
			*
			* @param [in] pResult A pointer to the CDecodedBarcodesUnit object that contains the result.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnDecodedBarcodesReceived(dbr::intermediate_results::CDecodedBarcodesUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when localized text lines have been received.
			*
			* @param [in] pResult A pointer to the CLocalizedTextLinesUnit object that contains the result.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnLocalizedTextLinesReceived(dlr::intermediate_results::CLocalizedTextLinesUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when recognized text lines have been received.
			*
			* @param [in] pResult A pointer to the CRecognizedTextLinesUnit object that contains the result.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnRecognizedTextLinesReceived(dlr::intermediate_results::CRecognizedTextLinesUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when detected quadrilaterals have been received.
			*
			* @param [in] pResult A pointer to the CDetectedQuadsUnit object that contains the result.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnDetectedQuadsReceived(ddn::intermediate_results::CDetectedQuadsUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when normalized images have been received.
			*
			* @param [in] pResult A pointer to the CNormalizedImagesUnit object that contains the result.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnNormalizedImagesReceived(ddn::intermediate_results::CNormalizedImagesUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when colour image units have been received.
			*
			* @param [in] pResult A pointer to the received colour image unit.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnColourImageUnitReceived(CColourImageUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when scaled-down colour image units have been received.
			*
			* @param [in] pResult A pointer to the received scaled-down colour image unit.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnScaledDownColourImageUnitReceived(CScaledDownColourImageUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when grayscale image units have been received.
			*
			* @param [in] pResult A pointer to the received grayscale image unit.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnGrayscaleImageUnitReceived(CGrayscaleImageUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when transformed grayscale image units have been received.
			*
			* @param [in] pResult A pointer to the received transformed grayscale image unit.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnTransformedGrayscaleImageUnitReceived(CTransformedGrayscaleImageUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when enhanced grayscale image units have been received.
			*
			* @param [in] pResult A pointer to the received enhanced grayscale image unit.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnEnhancedGrayscaleImageUnitReceived(CEnhancedGrayscaleImageUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when binary image units have been received.
			*
			* @param [in] pResult A pointer to the received binary image unit.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnBinaryImageUnitReceived(CBinaryImageUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when texture detection result units have been received.
			*
			* @param [in] pResult A pointer to the received texture detection result unit.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnTextureDetectionResultUnitReceived(CTextureDetectionResultUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when texture-removed grayscale image units have been received.
			*
			* @param [in] pResult A pointer to the received texture-removed grayscale image unit.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnTextureRemovedGrayscaleImageUnitReceived(CTextureRemovedGrayscaleImageUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when texture-removed binary image units have been received.
			*
			* @param [in] pResult A pointer to the received texture-removed binary image unit.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnTextureRemovedBinaryImageUnitReceived(CTextureRemovedBinaryImageUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when contours units have been received.
			*
			* @param [in] pResult A pointer to the received contours unit.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnContoursUnitReceived(CContoursUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when line segments units have been received.
			*
			* @param [in] pResult A pointer to the received line segments unit.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnLineSegmentsUnitReceived(CLineSegmentsUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when text zones units have been received.
			*
			* @param [in] pResult A pointer to the received text zones unit.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnTextZonesUnitReceived(CTextZonesUnit *pResult, const IntermediateResultExtraInfo* extraInfo);

			/**
			* Called when text-removed binary image units have been received.
			*
			* @param [in] pResult A pointer to the received text-removed binary image unit.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnTextRemovedBinaryImageUnitReceived(CTextRemovedBinaryImageUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when long lines units have been received.
			*
			* @param [in] pResult A pointer to the received long lines unit.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnLongLinesUnitReceived(ddn::intermediate_results::CLongLinesUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when corners units have been received.
			*
			* @param [in] pResult A pointer to the received corners unit.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnCornersUnitReceived(ddn::intermediate_results::CCornersUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when candidate quad edges units have been received.
			*
			* @param [in] pResult A pointer to the received candidate quad edges unit.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnCandidateQuadEdgesUnitReceived(ddn::intermediate_results::CCandidateQuadEdgesUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when candidate barcode zones units have been received.
			*
			* @param [in] pResult A pointer to the received candidate barcode zones unit.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnCandidateBarcodeZonesUnitReceived(dbr::intermediate_results::CCandidateBarcodeZonesUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when scaled up barcode image units have been received.
			*
			* @param [in] pResult A pointer to the received scaled up barcode image unit.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnScaledUpBarcodeImageUnitReceived(dbr::intermediate_results::CScaledUpBarcodeImageUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when deformation resisted barcode image units have been received.
			*
			* @param [in] pResult A pointer to the received deformation resisted barcode image unit.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnDeformationResistedBarcodeImageUnitReceived(dbr::intermediate_results::CDeformationResistedBarcodeImageUnit *pResult, const IntermediateResultExtraInfo* info);

			/**
			* Called when complemented barcode image units have been received.
			*
			* @param [in] pResult A pointer to the received complemented barcode image unit.
			* @param [in] info A pointer to the IntermediateResultExtraInfo object that contains the extra info of intermediate result.
			*
			*/
			virtual void OnComplementedBarcodeImageUnitReceived(dbr::intermediate_results::CComplementedBarcodeImageUnit *pResult, const IntermediateResultExtraInfo* info);


			virtual const char* GetEncryptedString();
		};

		/**
		* The CIntermediateResultManager class manages intermediate results generated during data capturing.
		*
		*/
		class DS_API CIntermediateResultManager
		{
		public:
			/**
			* Destructor
			*/
			virtual ~CIntermediateResultManager() {};

			/**
			* Adds an intermediate result receiver to the manager.
			*
			* @param [in] receiver The intermediate result receiver to add.
			*
			*/
			virtual int AddResultReceiver(CIntermediateResultReceiver* receiver) = 0;

			/**
			* Removes an intermediate result receiver from the manager.
			*
			* @param [in] receiver The intermediate result receiver to remove.
			*
			*/
			virtual int RemoveResultReceiver(CIntermediateResultReceiver* receiver) = 0;

			/**
			* Gets the raw image data using an image hash id.
			*
			* @param [in] imageHashId The hash id of the image to retrieve.
			*
			* @return Returns a pointer to the CImageData object containing the raw image data. You don't need to release the memory pointed to by the returned pointer.
			*
			*/
			virtual CImageData* GetRawImage(const char* imageHashId) = 0;
		};
	}
}

#endif
