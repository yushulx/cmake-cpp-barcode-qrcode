#pragma once

#if !defined(_WIN32) && !defined(_WIN64)

#ifdef __EMSCRIPTEN__
#define DDN_API __attribute__((used))
#else
#define DDN_API __attribute__((visibility("default")))
#include <stddef.h>
#endif

#else
#ifdef DDN_EXPORTS
#define DDN_API __declspec(dllexport)
#else
#define DDN_API 
#endif
#include <windows.h>
#endif
#include "DynamsoftCore.h"

#define DDN_VERSION                  "2.0.0.629"


#ifdef __cplusplus

using namespace dynamsoft::basic_structures;
using namespace dynamsoft::intermediate_results;

namespace dynamsoft
{
	namespace ddn
	{
		namespace intermediate_results
		{
			/**
			 * The `CDetectedQuadElement` class stores an intermediate result whose type is detected quad.
			 */
			class DDN_API CDetectedQuadElement : public CRegionObjectElement
			{
			public:
				/**
				 * Destructor
				 */
				virtual ~CDetectedQuadElement() {};

				/**
				 * Gets the confidence as document boundary of current object.
				 *
				 * @return The confidence as document boundary of current object.
				 *
				 */
				virtual int GetConfidenceAsDocumentBoundary() const = 0;
			};

			/**
			 * The `CNormalizedImageElement` class stores an intermediate result whose type is normalized image.
			 */
			class DDN_API CNormalizedImageElement : public CRegionObjectElement
			{
			public:
				/**
				 * Destructor
				 */
				virtual ~CNormalizedImageElement() {};

				/**
				 * Gets the ImageData of current object.
				 *
				 * @return The image data.
				 *
				 * @see [CImageData]()
				 *
				 */
				virtual const CImageData* GetImageData() const = 0;
			};

			/**
			 * The `CLongLinesUnit` class represents an intermediate result unit whose type is long lines.
			 */
			class DDN_API CLongLinesUnit : public CIntermediateResultUnit
			{
			public:
				/**
				 * Destructor
				 */
				virtual ~CLongLinesUnit() {};

				/**
				 * Gets the count of LongLine objects in current object.
				 *
				 * @return The count of LongLine objects in current object.
				 */
				virtual int GetCount() const = 0;

				/**
				 * Gets a LongLine object from current object by specifying an index.
				 *
				 * @param [in] index The index of the LongLine object.
				 *
				 * @param [out] line The LongLine object got by the specific index.
				 *
				 * @return Returns the error code.
				 *
				 * @see [CLineSegment]()
				 * @see [ErrorCode]()
				 */
				virtual int GetLongLine(int index, CLineSegment* line) const = 0;
			};

			/**
			 * The `CCornersUnit` class represents an intermediate result unit whose type is corners.
			 */
			class DDN_API CCornersUnit : public CIntermediateResultUnit
			{
			public:
				/**
				 * Destructor
				 */
				virtual ~CCornersUnit() {};

				/**
				 * Gets the count of Corner objects in current object.
				 *
				 * @return The count of Corner objects in current object.
				 */
				virtual int GetCount() const = 0;

				/**
				 * Gets a Corner object from current object by specifying a index.
				 *
				 * @param [in] index The index of the Corner object.
				 * @param [in, out] corner The Corner object got by the specific index.
				 *
				 * @return Returns the error code.
				 *
				 * @see CCorner
				 * @see ErrorCode
				 */
				virtual int GetCorner(int index, CCorner* corner) const = 0;
			};

			/**
			 * The `CCandidateQuadEdgesUnit` class represents an intermediate result unit whose type is candidate quad edges.
			 */
			class DDN_API CCandidateQuadEdgesUnit : public CIntermediateResultUnit
			{
			public:
				/**
				 * Destructor
				 */
				virtual ~CCandidateQuadEdgesUnit() {};

				/**
				 * Gets the count of CandidateQuadEdge objects in current object.
				 *
				 * @return The count of CandidateQuadEdge objects in current object.
				 */
				virtual int GetCount() const = 0;

				/**
				 * Gets a CandidateQuadEdge object from current object by specifying a index.
				 *
				 * @param [in] index The index of the CandidateQuadEdge object.
				 * @param [in, out] edge The CandidateQuadEdge object got by the specific index.
				 * @return Returns the error code.
				 */
				virtual int GetCandidateQuadEdge(int index, CEdge* edge) const = 0;
			};

			/**
			 * The `CDetectedQuadsUnit` class represents an intermediate result unit whose type is detected quads.
			 */
			class DDN_API CDetectedQuadsUnit : public CIntermediateResultUnit
			{
			public:
				/**
				 * Destructor
				 */
				virtual ~CDetectedQuadsUnit() {};

				/**
				 * Gets the count of DetectedQuad objects in current object.
				 *
				 * @return Returns the count of DetectedQuad objects in current object.
				 *
				 */
				virtual int GetCount() const = 0;

				/**
				 * Gets a DetectedQuad object from current object by specifying a index.
				 *
				 * @param index The index of the DetectedQuad object.
				 *
				 * @return Returns the DetectedQuad object got by the specific index.
				 *
				 * @see CDetectedQuadElement
				 */
				virtual const CDetectedQuadElement* GetDetectedQuad(int index) const = 0;
			};

			/**
			 * The `CNormalizedImagesUnit` class represents an intermediate result unit whose type is normalized images.
			 */
			class DDN_API CNormalizedImagesUnit : public CIntermediateResultUnit
			{
			public:
				/**
				 * Destructor
				 */
				virtual ~CNormalizedImagesUnit() {};

				/**
				 * Gets the count of CNormalizedImageElement objects in current object.
				 *
				 * @return Returns the count of CNormalizedImageElement objects in current object.
				 *
				 */
				virtual int GetCount() const = 0;

				/**
				 * Gets a NormalizedImage object from current object by specifying a index.
				 *
				 * @param index The index of the NormalizedImage object.
				 *
				 * @return Returns the NormalizedImage object got by the specific index.
				 *
				 * @see CNormalizedImageElement
				 */
				virtual const CNormalizedImageElement* GetNormalizedImage(int index) const = 0;
			};
		}

		/**
		 * The `CDetectedQuadResultItem` class represents an item that stores the detection result of a quadrilateral object. It inherits from the `CCapturedResultItem` class.
		 *
		 */
		class DDN_API CDetectedQuadResultItem : public CCapturedResultItem
		{
		public:
			/**
			 * Destructor
			 */
			virtual ~CDetectedQuadResultItem() {};

			/**
			 * Gets the location of current object.
			 *
			 * @return Return Value: The location of current object.
			 *
			 * @see CQuadrilateral
			 */
			virtual CQuadrilateral GetLocation() const = 0;

			/**
			 * Gets the confidence of current object as a document boundary.
			 *
			 * @return Return Value: The confidence as document boundary of the detected quad result.
			 *
			 */
			virtual int GetConfidenceAsDocumentBoundary() const = 0;

		};

		/**
		 * The `CNormalizedImageResultItem` class stores a captured result item whose type is normalized image.
		 *
		 */
		class DDN_API CNormalizedImageResultItem : public CCapturedResultItem
		{
		public:
			/**
			 * Destructor
			 */
			virtual ~CNormalizedImageResultItem() {};

			/**
			 * Gets the ImageData of current object.
			 *
			 * @return The image data.
			 *
			 * @see CImageData
			 *
			 */
			virtual const CImageData* GetImageData() const = 0;

			/**
			 * Gets the location of current object.
			 *
			 * @return Return Value: The location of current object.
			 *
			 * @see CQuadrilateral
			 */
			virtual CQuadrilateral GetLocation() const = 0;

		};

		/**
		 * The `CDetectedQuadsResult` class stores a collection of captured result items whose type is detected quads.
		 *
		 */
		class DDN_API CDetectedQuadsResult
		{
		public:
			/**
			 * Destructor
			 */
			virtual ~CDetectedQuadsResult() {}

			/**
			 * Gets the hash ID of the source image.
			 *
			 * @return Returns a pointer to a null-terminated string that represents the hash ID of the source image.
			 *
			 */
			virtual const char* GetSourceImageHashId()const = 0;

			/**
			 * Gets the tag of the source image.
			 *
			 * @return Returns a pointer to a CImageTag object that represents the tag of the source image.
			 *
			 * @see CImageTag
			 *
			 */
			virtual const CImageTag* GetSourceImageTag()const = 0;

			/**
			 * Get the rotation transformation matrix of the original image relative to the rotated image.
			 *
			 * @param [out] matrix A double array which represents the rotation transform matrix.
			 *
			 */
			virtual void GetRotationTransformMatrix(double matrix[9]) const = 0;

			/**
			 * Gets the number of detected quadrilaterals.
			 *
			 * @return Returns the number of detected quadrilaterals.
			 *
			 */
			virtual int GetCount()const = 0;

			/**
			 * Gets the detected quadrilateral item at a specified index.
			 *
			 * @param [in] index The index of the detected quadrilateral to retrieve.
			 *
			 * @return Returns a pointer to a CDetectedQuadResultItem object that represents the detected quadrilateral at the specified index.
			 *
			 * @see CDetectedQuadResultItem
			 *
			 */
			virtual const CDetectedQuadResultItem* GetItem(int index)const = 0;

			/**
			 * Remove a specific item from the array in the detected quads.
			 *
			 * @param [in] item The specific item to remove.
			 *
			 * @return Returns value indicating whether the deletion was successful or not.
			 *
			 */
			virtual int RemoveItem(const CDetectedQuadResultItem* item) = 0;

			/**
			 * Check if the item is present in the array.
			 *
			 * @param [in] item The specific item to check.
			 *
			 * @return Returns a bool value indicating whether the item is present in the array or not.
			 *
			 */
			virtual bool HasItem(const CDetectedQuadResultItem* item) const = 0;

			/**
			 * Gets the error code of the detection operation.
			 *
			 * @return Returns the error code.
			 *
			 * @see ErrorCode
			 *
			 */
			virtual int GetErrorCode()const = 0;

			/**
			 * Gets the error message of the detection operation.
			 *
			 * @return Returns a pointer to a null-terminated string that represents the error message.
			 *
			 */
			virtual const char* GetErrorString()const = 0;
		};

		/**
		 * The `CNormalizedImagesResult` class stores a collection of captured result items whose type is normalized image.
		 *
		 */
		class DDN_API CNormalizedImagesResult
		{
		public:
			/**
			 * Destructor
			 */
			virtual ~CNormalizedImagesResult() {};

			/**
			 * Gets the hash ID of the source image that was normalized.
			 *
			 * @return Returns the hash ID of the source image that was normalized.
			 *
			 */
			virtual const char* GetSourceImageHashId()const = 0;

			/**
			 * Gets the tag of the source image that was normalized.
			 *
			 * @return Returns a pointer to the tag of the source image that was normalized.
			 *
			 * @see CImageTag
			 *
			 */
			virtual const CImageTag* GetSourceImageTag()const = 0;

			/**
			 * Get the rotation transformation matrix of the original image relative to the rotated image.
			 *
			 * @param [out] matrix A double array which represents the rotation transform matrix.
			 *
			 */
			virtual void GetRotationTransformMatrix(double matrix[9]) const = 0;

			/**
			 * Gets the number of normalized images in the result.
			 *
			 * @return Returns the number of normalized images in the result.
			 *
			 */
			virtual int GetCount()const = 0;

			/**
			 * Gets a specific normalized image from the result.
			 *
			 * @param [in] index The index of the normalized image to get.
			 *
			 * @return Returns a pointer to the normalized image at the specified index. If the index is out of range, returns nullptr.
			 *
			 * @see CNormalizedImageResultItem
			 *
			 */
			virtual const CNormalizedImageResultItem* GetItem(int index)const = 0;

			/**
			 * Remove a specific item from the array in the normalized images.
			 *
			 * @param [in] item The specific item to remove.
			 *
			 * @return Returns value indicating whether the deletion was successful or not.
			 *
			 */
			virtual int RemoveItem(const CNormalizedImageResultItem* item) = 0;

			/**
			 * Check if the item is present in the array.
			 *
			 * @param [in] item The specific item to check.
			 *
			 * @return Returns a bool value indicating whether the item is present in the array or not.
			 *
			 */
			virtual bool HasItem(const CNormalizedImageResultItem* item) const = 0;

			/**
			 * Gets the error code of the operation.
			 *
			 * @return Returns the error code of the operation. A non-zero value indicates an error occurred.
			 *
			 * @see ErrorCode
			 *
			 */
			virtual int GetErrorCode()const = 0;

			/**
			 * Gets the error message of the operation.
			 *
			 * @return Returns the error message of the operation.
			 *
			 */
			virtual const char* GetErrorString()const = 0;
		};

		/**
		 * The CDocumentNormalizerModule class defines general functions in the document normalizer module.
		 */
		class DDN_API CDocumentNormalizerModule
		{
		public:
			/**
			 * Returns the version of the document normalizer module.
			 *
			 * @return Returns a const char pointer representing the version of the document normalizer module.
			 */
			static const char* GetVersion();
		};
		
	}
}
#endif
