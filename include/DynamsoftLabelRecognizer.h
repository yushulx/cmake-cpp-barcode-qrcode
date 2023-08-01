#pragma once

#if !defined(_WIN32) && !defined(_WIN64)

#ifdef __EMSCRIPTEN__
#define DLR_API __attribute__((used))
#else
#define DLR_API __attribute__((visibility("default")))
#endif

#include <stddef.h>
#else
#ifdef DLR_EXPORTS
#define DLR_API __declspec(dllexport)
#else
#define DLR_API __declspec(dllimport)
#endif
#include <windows.h>
#endif

#include "DynamsoftCore.h"

#define DLR_VERSION                  "3.0.0.629"

/**Structures section*/

#pragma pack(push)
#pragma pack(1)

/**
* The SimplifiedLabelRecognizerSettings struct contains settings for label recognition. It is a sub-parameter of SimplifiedCaptureVisionSettings.
*/
typedef struct tagSimplifiedLabelRecognizerSettings 
{
	/**Set the grayscale transformation modes with an array of enumeration GrayscaleTransformationMode.*/
	GrayscaleTransformationMode grayscaleTransformationModes[8];

	/**Set the grayscale enhancement modes with an array of enumeration GrayscaleEnhancementMode.*/
	GrayscaleEnhancementMode grayscaleEnhancementModes[8];

	/**Specify a character model by its name.*/
	char characterModelName[64];

	/**Set the RegEx pattern of the text line string to filter out the unqualified results.*/
	char lineStringRegExPattern[1024];

	/**Set the maximum available threads count in one label recognition task.*/
	int maxThreadsInOneTask;

	/**Reserved for future use.*/
	char reserved[512];

}SimplifiedLabelRecognizerSettings;

#pragma pack(pop)

#ifdef __cplusplus

using namespace dynamsoft::basic_structures;
using namespace dynamsoft::intermediate_results;

namespace dynamsoft
{
	namespace dlr
	{

		/**
		* The `CCharacterResult` class represents the result of a character recognition process. It contains the characters recognized (high, medium, and low confidence), their respective confidences, and the location of the character in a quadrilateral shape.
		*
		*/
		class DLR_API CCharacterResult
		{
		public:
			/**
			 * The character with high confidence.
			 */
			char characterH;
			/**
			 * The character with medium confidence.
			 */
			char characterM;
			/**
			 * The character with low confidence.
			 */
			char characterL;
			/**
			 * The location of the character in a quadrilateral shape.
			 */
			CQuadrilateral location;
			/**
			 * The confidence of the character with high confidence.
			 */
			int characterHConfidence;
			/**
			 * The confidence of the character with medium confidence.
			 */
			int characterMConfidence;
			/**
			 * The confidence of the character with low confidence.
			 */
			int characterLConfidence;
		};

		namespace intermediate_results
		{
			/**
			* The `CLocalizedTextLineElement` class represents a localized text line element. It inherits from the `CRegionObjectElement` class.
			*
			*/
			class DLR_API CLocalizedTextLineElement : public CRegionObjectElement
			{
			public:
				/**
				 * Destructor
				 */
				virtual ~CLocalizedTextLineElement() {};

				/**
				* Gets the number of character quads in the text line.
				*
				* @return Returns the number of character quads in the text line.
				*
				*/
				virtual int GetCharacterQuadsCount() const = 0;

				/**
				* Gets the quadrilateral of a specific character in the text line.
				*
				* @param [in] index The index of the character.
				* @param [out] quad The quadrilateral of the character.
				*
				* @return Returns 0 if successful, otherwise returns a negative value.
				*
				*/
				virtual int GetCharacterQuad(int index, CQuadrilateral* quad) const = 0;

				/**
				* Gets the row number of the text line.
				*
				* @return Returns the row number of the text line.
				*
				*/
				virtual int GetRowNumber() const = 0;
			};

			/**
			* The `CRecognizedTextLineElement` class represents a line of recognized text in an image. It inherits from the `CRegionObjectElement` class.
			*
			*/
			class DLR_API CRecognizedTextLineElement : public CRegionObjectElement
			{
			public:
				/**
				 * Destructor
				 */
				virtual ~CRecognizedTextLineElement() {};

				/**
				* Gets the recognized text.
				*
				* @return Returns a pointer to the recognized text.
				*
				*/
				virtual const char* GetText() const = 0;

				/**
				* Gets the confidence level of the recognized text.
				*
				* @return Returns an integer value representing the confidence level of the recognized text.
				*
				*/
				virtual int GetConfidence() const = 0;

				/**
				* Gets the number of individual character recognition results in the line.
				*
				* @return Returns an integer value representing the number of individual character recognition results.
				*
				*/
				virtual int GetCharacterResultsCount() const = 0;

				/**
				* Gets the character recognition result at the specified index.
				*
				* @param [in] index The index of the character recognition result to retrieve.
				* @param [out] charResult A pointer to a CCharacterResult object to store the result in.
				*
				* @return Returns an integer value representing the success of the operation. Zero indicates success, while any other value indicates failure.
				*
				*/
				virtual int GetCharacterResult(int index, CCharacterResult* charResult) const = 0;

				/**
				* Gets the row number of the text line within the image.
				*
				* @return Returns an integer value representing the row number of the text line within the image.
				*
				*/
				virtual int GetRowNumber() const = 0;
			};

			/**
			* The `CLocalizedTextLinesUnit` class represents a unit that contains localized text lines. It inherits from the `CIntermediateResultUnit` class.
			*
			*/
			class DLR_API CLocalizedTextLinesUnit : public CIntermediateResultUnit
			{
			public:
				/**
				 * Destructor
				 */
				virtual ~CLocalizedTextLinesUnit() {};

				/**
				* Gets the number of localized text lines in the unit.
				*
				* @return Returns the number of localized text lines in the unit.
				*
				*/
				virtual int GetCount() const = 0;

				/**
				* Gets a pointer to a specific localized text line element.
				*
				* @param [in] index The index of the localized text line element to retrieve.
				*
				* @return Returns a const pointer to the localized text line element at the specified index.
				*
				*/
				virtual const CLocalizedTextLineElement* GetLocalizedTextLine(int index) const = 0;
			};

			/**
			* The `CRecognizedTextLinesUnit` class represents an intermediate result unit containing recognized text lines. It inherits from the `CIntermediateResultUnit` class.
			*
			*/
			class DLR_API CRecognizedTextLinesUnit : public CIntermediateResultUnit
			{
			public:
				/**
				 * Destructor
				 */
				virtual ~CRecognizedTextLinesUnit() {};

				/**
				* Gets the number of recognized text lines in the unit.
				*
				* @return Returns the number of recognized text lines in the unit.
				*
				*/
				virtual int GetCount() const = 0;

				/**
				* Gets a pointer to the CRecognizedTextLineElement object at the specified index.
				*
				* @param [in] index The index of the desired CRecognizedTextLineElement object.
				*
				* @return Returns a pointer to the CRecognizedTextLineElement object at the specified index.
				*
				*/
				virtual const CRecognizedTextLineElement* GetRecognizedTextLine(int index) const = 0;
			};
		}

		/**
		* The `CTextLineResultItem` class represents a text line result item recognized by a document layout analysis engine. It is derived from `CCapturedResultItem`.
		*
		*/
		class DLR_API CTextLineResultItem : public CCapturedResultItem
		{
		public:
			/**
			 * Destructor
			 */
			virtual ~CTextLineResultItem() {};

			/**
			* It is used to get the text content of the text line.
			*
			* @return Returns the text content of the text line.
			*
			*/
			virtual const char* GetText() const = 0;

			/**
			* It is used to get the location of the text line in the form of a quadrilateral.
			*
			* @return Returns the location of the text line in the form of a quadrilateral.
			*
			*/
			virtual CQuadrilateral GetLocation() const = 0;

			/**
			* It is used to get the confidence of the text line recognition result.
			*
			* @return Returns the confidence of the text line recognition result.
			*
			*/
			virtual int GetConfidence() const = 0;

			/**
			* It is used to get the count of character results in the text line.
			*
			* @return Returns the count of character results in the text line.
			*
			*/
			virtual int GetCharacterResultsCount() const = 0;

			/**
			* It is used to get the character result at the specified index.
			*
			* @param [in] index The index of the character result to get.
			* @param [out] charResult The character result at the specified index.
			*
			* @return Returns 0 if successful, otherwise returns a non-zero error code.
			*
			*/
			virtual int GetCharacterResult(int index, CCharacterResult* charResult) const = 0;

		};

		/**
		* The `CRecognizedTextLinesResult` class represents the result of a text recognition process. It provides access to information about the recognized text lines, the source image, and any errors that occurred during the recognition process.
		*
		*/
		class DLR_API CRecognizedTextLinesResult
		{
		public:
			/**
			 * Destructor
			 */
			virtual ~CRecognizedTextLinesResult() {};

			/**
			* Gets the hash ID of the source image.
			*
			* @return Returns a pointer to a null-terminated string containing the hash ID of the source image.
			*
			*/
			virtual const char* GetSourceImageHashId() const = 0;

			/**
			* Gets the tag of the source image.
			*
			* @return Returns a pointer to a CImageTag object representing the tag of the source image.
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
			* Gets the number of text line result items in the recognition result.
			*
			* @return Returns the number of text line result items in the recognition result.
			*
			*/
			virtual int GetCount() const = 0;

			/**
			* Gets the text line result item at the specified index.
			*
			* @param [in] index The zero-based index of the text line result item to retrieve.
			*
			* @return Returns a pointer to the CTextLineResultItem object at the specified index.
			*
			*/
			virtual const CTextLineResultItem* GetItem(int index) const = 0;

			/**
			 * Remove a specific item from the array in the recognition result.
			 *
			 * @param [in] item The specific item to remove.
			 *
			 * @return Returns value indicating whether the deletion was successful or not.
			 *
			 */
			virtual int RemoveItem(const CTextLineResultItem* item) = 0;

			/**
			 * Check if the item is present in the array.
			 *
			 * @param [in] item The specific item to check.
			 *
			 * @return Returns a bool value indicating whether the item is present in the array or not.
			 *
			 */
			virtual bool HasItem(const CTextLineResultItem* item) const = 0;

			/**
			* Gets the error code of the recognition result, if an error occurred.
			*
			* @return Returns the error code of the recognition result, or 0 if no error occurred.
			*
			*/
			virtual int GetErrorCode() const = 0;

			/**
			* Gets the error message of the recognition result, if an error occurred.
			*
			* @return Returns a pointer to a null-terminated string containing the error message of the recognition result, or a pointer to an empty string if no error occurred.
			*
			*/
			virtual const char* GetErrorString() const = 0;
		};

		/**
		 * The CLabelRecognizerModule class defines general functions in the label recognizer module.
		 */
		class DLR_API CLabelRecognizerModule
		{
		public:
			/**
			 * Returns the version of the label recognizer module.
			 *
			 * @return Returns a const char pointer representing the version of the label recognizer module.
			 */
			static const char* GetVersion();
		};

	}
}
#endif