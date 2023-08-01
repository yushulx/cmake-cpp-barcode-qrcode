#ifndef C_BRIDGING_H 
#define C_BRIDGING_H

#include <iostream>
#include <string>

#include "DynamsoftCaptureVisionRouter.h"

using namespace std;
using namespace dynamsoft::license;
using namespace dynamsoft::cvr;
using namespace dynamsoft::dbr;

#ifdef __cplusplus
extern "C" {
#endif

#define DLL_API __declspec(dllexport)

DLL_API void c_initLicense();

#ifdef __cplusplus
}
#endif

#endif 