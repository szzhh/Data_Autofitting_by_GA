//
// MATLAB Compiler: 7.1 (R2019b)
// Date: Sun Dec  6 12:09:36 2020
// Arguments: "-B""macro_default""-C""-W""cpplib:draw""-T""link:lib""draw.m"
//

#ifndef draw_h
#define draw_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" { // sbcheck:ok:extern_c
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_draw_C_API 
#define LIB_draw_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_draw_C_API 
bool MW_CALL_CONV drawInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_draw_C_API 
bool MW_CALL_CONV drawInitialize(void);

extern LIB_draw_C_API 
void MW_CALL_CONV drawTerminate(void);

extern LIB_draw_C_API 
void MW_CALL_CONV drawPrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_draw_C_API 
bool MW_CALL_CONV mlxDraw(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#ifdef __cplusplus
}
#endif


/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__MINGW64__)

#ifdef EXPORTING_draw
#define PUBLIC_draw_CPP_API __declspec(dllexport)
#else
#define PUBLIC_draw_CPP_API __declspec(dllimport)
#endif

#define LIB_draw_CPP_API PUBLIC_draw_CPP_API

#else

#if !defined(LIB_draw_CPP_API)
#if defined(LIB_draw_C_API)
#define LIB_draw_CPP_API LIB_draw_C_API
#else
#define LIB_draw_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_draw_CPP_API void MW_CALL_CONV draw(const mwArray& Z);

/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */
#endif

#endif
