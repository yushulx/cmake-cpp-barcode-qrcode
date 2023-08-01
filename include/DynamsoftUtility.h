#pragma once
#if !defined(_WIN32) && !defined(_WIN64)
#define UTIL_API __attribute__((visibility("default")))
#include <stddef.h>
#else
#ifdef UTIL_EXPORTS
#define UTIL_API __declspec(dllexport)
#else
#define UTIL_API __declspec(dllimport)
#endif
#include <windows.h>
#endif


#include"DynamsoftCore.h"
#define DISA_VERSION "1.0.0.629"

#ifdef __cplusplus

using namespace dynamsoft::basic_structures;

namespace dynamsoft {
	namespace utility {

		class UTIL_API CUtilityModule
		{
		public:
			static const char* GetVersion();
		};
		/**
		* The CMultiFrameResultCrossFilter class is responsible for filtering captured results.It contains 
		* several callback functions for different types of results,including raw image,decoded barcodes, 
		* recognized text lines,detected quads,normalized images,and parsed results.
		*
		*/
		class UTIL_API CMultiFrameResultCrossFilter : public CCapturedResultFilter
		{
		private:
			class CMultiFrameResultCrossFilterInner;
			CMultiFrameResultCrossFilterInner* pInner;

		public:
			CMultiFrameResultCrossFilter();
			virtual ~CMultiFrameResultCrossFilter();

			/**
			* Enable result verification feature to improve the accuracy 
			* of video streaming recognition results.
			*
			* @param [in] resultItemTypes The or value of the captured result item types.
			* @param [in] enable Set whether to enable result verification.
			*
			*/
			void EnableResultVerification(int resultItemTypes, bool enable);

			/**
			* Determines whether the result verification feature is enabled for
			* the specific captured result item type.
			*
			* @param [in] type The specific captured result item type.
			* @return Returns a bool value indicating whether result verification is 
			* enabled for the specific captured result item type.
			*/
			bool IsResultVerificationEnabled(CapturedResultItemType type) const;

			/**
			* Enable duplicate filter feature to filter out the duplicate results in 
			* the period of duplicateForgetTime for video streaming recognition. The 
			* default value of duplicateForgetTime is 3000ms.
			*
			* CRIT_BARCODE:When the text and format are identical,it is considered as the same barcode.
			* CRIT_TEXT_LINE:When the text is exactly the same,it is considered as the same text line.
			* CRIT_DETECTED_QUAD:When the quadrilateral is approximately the same, it is considered as 
			* the same quadrilateral.
			*
			* @param [in] resultItemTypes The or value of the captured result item types.
			* @param [in] enable Set whether to enable result duplicate filter.
			*
			*/
			void EnableDuplicateFilter(int resultItemTypes, bool enable);

			/**
			* Determines whether the duplicate filter feature is enabled for the specific result item type.
			*
			* @param [in] type The specific captured result item type.
			* @return Returns a bool value indicating whether duplicate filter is enabled for the specific 
			* result item type.
			*
			*/
			bool IsDuplicateFilterEnabled(CapturedResultItemType type) const;

			/**
			* Sets the duplicate forget time for the specific captured result item types.The same captured result 
			* item will be returned only once during the period.
			*
			* CRIT_BARCODE:When the text and format are identical,it is considered as the same barcode.
			* CRIT_TEXT_LINE:When the text is exactly the same,it is considered as the same text line.
			* CRIT_DETECTED_QUAD:When the quadrilateral is approximately the same, it is considered as
			* the same quadrilateral.
			*
			* @param [in] resultItemTypes The or value of the captured result item types.
			* @param [in] time The duplicate forget time measured in milliseconds.
			*
			*/
			void SetDuplicateForgetTime(int resultItemTypes, int time);

			/**
			* Gets the duplicate forget time for a specific captured result item type.
			*
			* @param [in] type The specific captured result item type.
			* @return Returns the duplicate forget time for the specific captured result item type.
			*
			*/
			int GetDuplicateForgetTime(CapturedResultItemType type) const;

			virtual void OnRawImageResultReceived(CRawImageResultItem* pResult);

			virtual void OnDecodedBarcodesReceived(dbr::CDecodedBarcodesResult* pResult);

			virtual void OnRecognizedTextLinesReceived(dlr::CRecognizedTextLinesResult* pResult);

			virtual void OnDetectedQuadsReceived(ddn::CDetectedQuadsResult* pResult);

			virtual void OnNormalizedImagesReceived(ddn::CNormalizedImagesResult* pResult);

			virtual void OnParsedResultsReceived(dcp::CParsedResult* pResult);

		};

		/**
		* The CProactiveImageSourceAdapter class is an abstract base class that extends the 
		* CImageSourceAdapter class. It provides an interface for proactively fetching images in 
		* a separate thread.
		*/
		class UTIL_API CProactiveImageSourceAdapter :
			public CImageSourceAdapter 
		{
		private:
			class CProactiveImageSourceAdapterInner;
			CProactiveImageSourceAdapter(const CProactiveImageSourceAdapter&);
			CProactiveImageSourceAdapter& operator=(const CProactiveImageSourceAdapter&);
			CProactiveImageSourceAdapterInner* m_inner;

			void FetchImageToBuffer();

		protected:
			
			/**
			* This method needs to be implemented in the derived class. It is called in a loop in the Fetching thread to obtain images.
			*
			* @return Returns a pointer to the CImageData object representing the fetched image.
			*
			*/
			virtual CImageData* FetchImage() = 0;

		public:
			CProactiveImageSourceAdapter();
			~CProactiveImageSourceAdapter();
			
			bool HasNextImageToFetch()const override;

			/**
			* Sets the time interval for the ImageSource to wait before attempting to fetch another image to put in the buffer.
			*
			* @param [in] milliseconds Specifies the wait time in milliseconds. If set to -1, the ImageSource does not proactively fetch images.
			*
			*/
			void SetImageFetchInterval(int milliseconds);

			/**
			* Gets the time interval for the ImageSource to wait before attempting to fetch another image to put in the buffer.
			*
			* @return Returns the wait time in milliseconds. If the value is -1, the ImageSource does not proactively fetch images.
			*
			*/
			int GetImageFetchInterval()const;

			void StartFetching()override;

			void StopFetching()override;
		};

		/**
		* The CDirectoryFetcher class is a utility class that retrieves a list of files from a specified directory based on certain criteria. It inherits from the CProactiveImageSourceAdapter class.
		*/
		class UTIL_API CDirectoryFetcher : public CProactiveImageSourceAdapter 
		{			
		private:
			class DirectoryFetcherInner;
			DirectoryFetcherInner* m_directoryFetcherInner;

			CImageData* FetchImage()override;

		public:

			CDirectoryFetcher();

			~CDirectoryFetcher();

			/**
			* Sets the directory path and filter for the file search.
			*
			* @param [in] path The path of the directory to search.
			* @param [in] filter A string that specifies file extensions. For example: "*.BMP;*.JPG;*.GIF", or "*.*", etc.
			* @param [in] recursive Specifies whether to load files recursively.
			*
			* @return Returns an integer value that represents the success or failure of the operation.
			*
			*/
			int SetDirectory(const char* filePath, const char* filter = "*.bmp;*.jpg;*.jpeg;*.tif;*.png;*.tiff;*.gif;*.pdf", bool recursive = false);

			/**
			* Sets the parameters for reading PDF files.
			*
			* @param [in] para The parameter object for reading PDF files.
			*
			* @return Returns an integer value that represents the success or failure of the operation.
			*
			*/
			int SetPDFReadingParameter(const CPDFReadingParameter& para);

			bool HasNextImageToFetch()const override;

		};

		/**
		* The 'CFileFetcher' class is a utility class that partitions a multi-page image file into multiple independent 'ImageData' objects. It inherits 
		* from the 'CImageSourceAdapter' class.
		*/
		class UTIL_API CFileFetcher : public CImageSourceAdapter {
		public:
			CFileFetcher(const CPDFReadingParameter& pdfReadingParameter = CPDFReadingParameter());
			~CFileFetcher();
			/**
			  * Sets the file by path.
			  * @param [in] path The file path.
			  * @return Returns an integer value that represents the success or failure of the operation.
			*/
			int SetFile(const char* path);
			/**
			  * Sets the file using a file bytes.
			  * @param [in] pFileBytes The file bytes.
			  * @param [in] fileSieze The file bytes length.
			  * @return Returns an integer value that represents the success or failure of the operation.
			*/
			int SetFile(const unsigned char* pFileBytes, int fileSize);
			/**
			  * Sets the file using a CImageData object.
			  * @param [in] imageData The image data.
			  * @return Returns an integer value that represents the success or failure of the operation.
			*/
			int SetFile(const CImageData* imageData);
			/**
			  * Sets the parameters for reading PDF files.
			  * @param [in] para The parameter object for reading PDF files.
			  * @return Returns an integer value that represents the success or failure of the operation.
			*/
			int SetPDFReadingParameter(const CPDFReadingParameter& para);
			bool HasNextImageToFetch()const override;
			CImageData* GetImage()override;
		private:
			void* m_pFetcher;
		};

		/**
		* The CImageManager class is a utility class for managing and manipulating images. It provides functionality for saving images to files and drawing various shapes on images.
		*
		*/
		class UTIL_API CImageManager 
		{
		public:
			/**
			* Saves an image to a file.
			*
			* @param [in] pImageData A pointer to the image data to be saved.
			* @param [in] path The path to the file to save the image.
			* @param [in] overwrite A flag indicating whether to overwrite the file if it already exists. Defaults to true.
			*
			* @return Returns an integer indicating the success of the operation. 0 indicates success, while a non-zero value indicates an error occurred.
			*
			*/
			int SaveToFile(const CImageData* pImageData, const char* path, bool overwrite = true);

			/**
			* Draws various shapes on an image.
			*
			* @param [in] pImageData A pointer to the image data to draw on.
			* @param [in] quads[] An array of quadrilaterals to draw on the image.
			* @param [in] quadsCount The number of quadrilaterals in the array.
			* @param [in] color The color to use for drawing. Defaults to 0xFFFF0000 (red).
			* @param [in] thickness The thickness of the lines to draw. Defaults to 1.
			*
			* @return Returns a pointer to the modified image data.
			*
			*/
			CImageData* DrawOnImage(const CImageData* pImageData, CQuadrilateral quads[], int quadsCount, int color = 0xFFFF0000, int thickness = 1);
			CImageData* DrawOnImage(const CImageData* pImageData, CLineSegment lines[], int linesCount, int color = 0xFFFF0000, int thickness = 1);
			CImageData* DrawOnImage(const CImageData* pImageData, CContour contours[], int contoursCount, int color = 0xFFFF0000, int thickness = 1);
			CImageData* DrawOnImage(const CImageData* pImageData, CCorner corners[], int cornersCount, int color = 0xFFFF0000, int thickness = 1);
			CImageData* DrawOnImage(const CImageData* pImageData, CEdge edges[], int edgesCount, int color = 0xFFFF0000, int thickness = 1);

		};
	}
}

#endif // __cplusplus
