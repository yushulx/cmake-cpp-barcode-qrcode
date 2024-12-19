#include <iostream>
#include <vector>
#include <mutex>

#include "template.h"
#include "DynamsoftCaptureVisionRouter.h"
#include "DynamsoftUtility.h"
#include "Camera.h"
#include "CameraPreview.h"

using namespace dynamsoft::license;
using namespace dynamsoft::cvr;
using namespace dynamsoft::dbr;
using namespace dynamsoft::utility;
using namespace dynamsoft::basic_structures;

struct BarcodeResult
{
    std::string type;
    std::string value;
    int x1, y1, x2, y2, x3, y3, x4, y4;
    int frameId;
};

std::vector<BarcodeResult> barcodeResults;
std::mutex barcodeResultsMutex;

class MyCapturedResultReceiver : public CCapturedResultReceiver
{
    virtual void OnDecodedBarcodesReceived(CDecodedBarcodesResult *pResult) override
    {
        std::lock_guard<std::mutex> lock(barcodeResultsMutex);

        if (pResult->GetErrorCode() != EC_OK)
        {
            std::cout << "Error: " << pResult->GetErrorString() << std::endl;
        }
        else
        {
            auto tag = pResult->GetOriginalImageTag();
            if (tag)
                std::cout << "ImageID:" << tag->GetImageId() << std::endl;
            int count = pResult->GetItemsCount();

            barcodeResults.clear();
            for (int i = 0; i < count; i++)
            {
                const CBarcodeResultItem *barcodeResultItem = pResult->GetItem(i);
                if (barcodeResultItem != NULL)
                {
                    std::cout << "Result " << i + 1 << std::endl;
                    std::cout << "Barcode Format: " << barcodeResultItem->GetFormatString() << std::endl;
                    std::cout << "Barcode Text: " << barcodeResultItem->GetText() << std::endl;
                    CPoint *points = barcodeResultItem->GetLocation().points;

                    BarcodeResult result;
                    result.type = barcodeResultItem->GetFormatString();
                    result.value = barcodeResultItem->GetText();
                    result.frameId = tag->GetImageId();
                    result.x1 = points[0][0];
                    result.y1 = points[0][1];
                    result.x2 = points[1][0];
                    result.y2 = points[1][1];
                    result.x3 = points[2][0];
                    result.y3 = points[2][1];
                    result.x4 = points[3][0];
                    result.y4 = points[3][1];

                    barcodeResults.push_back(result);
                }
            }
        }

        std::cout << std::endl;
    }
};

class MyVideoFetcher : public CImageSourceAdapter
{
public:
    MyVideoFetcher() {};
    ~MyVideoFetcher() {};
    bool HasNextImageToFetch() const override
    {
        return true;
    }
    void MyAddImageToBuffer(const CImageData *img, bool bClone = true)
    {
        AddImageToBuffer(img, bClone);
    }
};

int main()
{
    int iRet = -1;
    char szErrorMsg[256];
    // Initialize license.
    // Request a trial from https://www.dynamsoft.com/customer/license/trialLicense/?product=dcv&package=cross-platform
    iRet = CLicenseManager::InitLicense("DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTE2NDk4Mjk3OTI2MzUiLCJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSIsInNlc3Npb25QYXNzd29yZCI6IndTcGR6Vm05WDJrcEQ5YUoifQ==", szErrorMsg, 256);
    if (iRet != EC_OK)
    {
        std::cout << szErrorMsg << std::endl;
    }
    int errorCode = 1;
    char errorMsg[512] = {0};

    CCaptureVisionRouter *cvr = new CCaptureVisionRouter;
    errorCode = cvr->InitSettings(jsonString.c_str(), errorMsg, 512);
    if (errorCode != EC_OK)
    {
        std::cout << "error:" << errorMsg << std::endl;
        return -1;
    }

    Camera camera;

    std::cout << "Capturing frames...\n";
    if (camera.Open(0))
    {
        // Create a window
        CameraWindow window(camera.frameWidth, camera.frameHeight, "Camera Stream");
        if (!window.Create())
        {
            std::cerr << "Failed to create window." << std::endl;
            return -1;
        }

        window.Show();

        // Start streaming frames
        CameraWindow::Color textColor = {255, 0, 0};

        while (window.WaitKey('q'))
        {
            // Capture a frame
            FrameData frame = camera.CaptureFrame();

            if (frame.rgbData)
            {
                // Display the frame
                window.ShowFrame(frame.rgbData, frame.width, frame.height);

                CImageData data(frame.size,
                                frame.rgbData,
                                frame.width,
                                frame.height,
                                frame.width * 3,
                                IPF_RGB_888,
                                0, 0);
                CCapturedResult *result = cvr->Capture(&data, "");

                CDecodedBarcodesResult *barcodeResult = result->GetDecodedBarcodesResult();
                if (barcodeResult)
                {
                    int count = barcodeResult->GetItemsCount();
                    for (int i = 0; i < count; i++)
                    {
                        const CBarcodeResultItem *barcodeResultItem = barcodeResult->GetItem(i);
                        CPoint *points = barcodeResultItem->GetLocation().points;

                        std::vector<std::pair<int, int>> corners = {
                            {points[0][0], points[0][1]},
                            {points[1][0], points[1][1]},
                            {points[2][0], points[2][1]},
                            {points[3][0], points[3][1]}};

                        window.DrawContour(corners);

                        window.DrawText(barcodeResultItem->GetText(), points[0][0], points[0][1], 24, textColor);
                    }
                }
            }

            camera.ReleaseFrame(frame);
        }

        camera.Release();
    }

    return 0;
}
