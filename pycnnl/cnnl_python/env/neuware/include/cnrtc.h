// ************************************************************************
// Copyright (C) [2021-2025] by Cambricon, Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// ************************************************************************

// ************************************************************************
// CNRTC: Cambricon Neuware Runtime Compilation Library
// ************************************************************************
#ifndef __CNRTC_H__
#define __CNRTC_H__

#if defined(__cplusplus)
extern "C" {
#endif

#define CNRTC_MAJOR_VERSION 0
#define CNRTC_MINOR_VERSION 5
#define CNRTC_PATCH_VERSION 0

// \brief   The enumerated type cnrtcStatus defines the return value of the functions.
typedef enum {
  CNRTC_SUCCESS = 0,
  CNRTC_VERSION_NO_SPACE_ERROR = 1,
  CNRTC_CREATE_CODE_ALREADY_EXIST_ERROR = 2,
  CNRTC_CREATE_CODE_SOURCE_NULL_ERROR = 3,
  CNRTC_DESTROY_CODE_DOUBLE_FREE_ERROR = 4,
  CNRTC_COMPILE_CODE_NO_CODE_ERROR = 5,
  CNRTC_COMPILE_CODE_PARAM_ERROR = 6,
  CNRTC_COMPILE_CODE_WRITE_PERMISSION_ERROR = 7,
  CNRTC_COMPILE_CODE_READ_PERMISSION_ERROR = 8,
  CNRTC_COMPILE_CODE_ENVIRONMENT_ERROR = 9,
  CNRTC_COMPILE_CODE_ERROR = 10,
  CNRTC_GET_BIN_NO_CODE_ERROR = 11,
  CNRTC_GET_BIN_NO_SPACE_ERROR = 12,
  CNRTC_GET_BIN_SIZE_NO_CODE_ERROR = 13,
  CNRTC_GET_BIN_SIZE_NO_SPACE_ERROR = 14,
  CNRTC_GET_LOG_NO_CODE_ERROR = 15,
  CNRTC_GET_LOG_NO_SPACE_ERROR = 16,
  CNRTC_GET_LOG_SIZE_NO_CODE_ERROR = 17,
  CNRTC_GET_LOG_SIZE_NO_SPACE_ERROR = 18,
  CNRTC_NO_CODE_ERROR = 19,
  CNRTC_NO_OUTPUT_SPACE_ERROR = 20,
  CNRTC_NO_FATBIN_OPTION_ERROR = 21
} cnrtcStatus;

// \brief   The enumerated type cnrtcCodeType defines the language CNRTC supports.
typedef enum {
  CNRTC_CODE_BANGC = 0,
  CNRTC_CODE_MLISA = 1
} cnrtcCodeType;

// \brief   cnrtcTransStatusToString converts cnrtcStatus to string.
// \param   stat[in]: The enum cnrtcStatus value.
// \return  The string form of cnrtcStatus.
const char* cnrtcTransStatusToString(cnrtcStatus stat);

// \brief   cnrtcVersion returns CNRTC version number (major and minor).
// \param   major[out]: CNRTC major version number.
// \param   minor[out]: CNRTC minor version number.
// \return  cnrtcStatus: CNRTC_SUCCESS if success and
//          CNRTC_VERSION_NO_SPACE_ERROR if major or minor has no space.
cnrtcStatus cnrtcVersion(int *major, int *minor);

// \brief   cnrtcCode is the main functional subject of CNRTC,
//          it's an abstraction of the BANGC or MLISA source code.
typedef struct _cnrtcCode *cnrtcCode;

// \brief   cnrtcCreateCode creates cnrtcCode object.
//          This API only supports BANGC source code but
//          cnrtcCreateCodeV2() supports BANGC and MLISA source code.
// \param   code[in]: cnrtcCode object.
// \param   srcCode[in]: BANGC source code.
// \param   name[in]: Reserved parameter, don't use.
// \param   headerNum[in]: Reserved parameter, don't use.
// \param   headers[in]: Reserved parameter, don't use.
// \param   includeNames[in]: Reserved parameter, don't use.
// \return  cnrtcStatus: CNRTC_SUCCESS if success,
//          CNRTC_CREATE_CODE_ALREADY_EXIST_ERROR if cnrtcCode has already existed and
//          CNRTC_CREATE_CODE_SOURCE_NULL_ERROR if srcCode is NULL.
cnrtcStatus cnrtcCreateCode(cnrtcCode* code,
                            const char* srcCode,
                            const char* name,
                            int headerNum,
                            const char** headers,
                            const char** includeNames);

// \brief   cnrtcCreateCodeV2 creates cnrtcCode object.
// \param   code[in]: cnrtcCode object.
// \param   srcCode[in]: BANGC or MLISA source code.
// \param   codeType[in]: Any value in cnrtcCodeType.
// \param   name[in]: Reserved parameter, don't use.
// \param   headerNum[in]: Reserved parameter, don't use.
// \param   headers[in]: Reserved parameter, don't use.
// \param   includeNames[in]: Reserved parameter, don't use.
// \return  cnrtcStatus: CNRTC_SUCCESS if success,
//          CNRTC_CREATE_CODE_ALREADY_EXIST_ERROR if cnrtcCode has already existed and
//          CNRTC_CREATE_CODE_SOURCE_NULL_ERROR if srcCode is NULL.
cnrtcStatus cnrtcCreateCodeV2(cnrtcCode* code,
                              const char* srcCode,
                              cnrtcCodeType codeType,
                              const char* name,
                              int headerNum,
                              const char** headers,
                              const char** includeNames);

// \brief   cnrtcDestroyCode destroys cnrtcCode object.
// \param   code[in]: cnrtcCode object.
// \return  cnrtcStatus: CNRTC_SUCCESS if success and
//          CNRTC_DESTROY_CODE_DOUBLE_FREE_ERROR if cnrtcCode has not existed.
cnrtcStatus cnrtcDestroyCode(cnrtcCode* code);

// \brief   cnrtcCompileCode compiles source code in the cnrtcCode object.
// \param   code[in]: cnrtcCode object.
// \param   numOptions[in]: The number of compilation options.
// \param   options[in]: The compilation options.
// \return  cnrtcStatus: CNRTC_SUCCESS if success,
//          CNRTC_COMPILE_CODE_NO_CODE_ERROR if cnrtcCode has not existed,
//          CNRTC_COMPILE_CODE_PARAM_ERROR if compilation options is wrong,
//          CNRTC_COMPILE_CODE_WRITE_PERMISSION_ERROR if can't get system write permission,
//          CNRTC_COMPILE_CODE_READ_PERMISSION_ERROR if can't get system read permission,
//          CNRTC_COMPILE_CODE_ENVIRONMENT_ERROR if system environment is abnormal and
//          CNRTC_COMPILE_CODE_ERROR if source code has compilation error.
cnrtcStatus cnrtcCompileCode(cnrtcCode code, int numOptions, const char** options);

// \brief   cnrtcGetFatBinary gets compilation output cnFatBinary.
//          Before calling this API, the cnrtcCompileCode() must contain
//          "--bang-fatbin-only" compilation option (for BANGC) or
//          "--fatbin" compilation option(for MLISA).
// \param   code[in]: cnrtcCode object.
// \param   bin[out]: The memory space of output cnFatBinary.
// \return  cnrtcStatus: CNRTC_SUCCESS if success,
//          CNRTC_GET_BIN_NO_CODE_ERROR if cnrtcCode has not existed,
//          CNRTC_GET_BIN_NO_SPACE_ERROR if the memory space has not been allocated and
//          CNRTC_NO_FATBIN_OPTION_ERROR if there is no "--bang-fatbin-only" or "--fatbin"
//          compilation option in cnrtcCompileCode() params.
cnrtcStatus cnrtcGetFatBinary(cnrtcCode code, void* bin);

// \brief   cnrtcGetFatBinarySize gets the size of compilation output cnFatBinary.
//          Before calling this API, the cnrtcCompileCode() must contain
//          "--bang-fatbin-only" compilation option (for BANGC) or
//          "--fatbin" compilation option(for MLISA).
// \param   code[in]: cnrtcCode object.
// \param   binSize[out]: The size of output cnFatBinary.
// \return  cnrtcStatus: CNRTC_SUCCESS if success,
//          CNRTC_GET_BIN_SIZE_NO_CODE_ERROR if cnrtcCode has not existed,
//          CNRTC_GET_BIN_SIZE_NO_SPACE_ERROR if the memory space of binSize has not been allocated
//          and CNRTC_NO_FATBIN_OPTION_ERROR if there is no "--bang-fatbin-only" or "--fatbin"
//          compilation option in cnrtcCompileCode() params.
cnrtcStatus cnrtcGetFatBinarySize(cnrtcCode code, unsigned int* binSize);

// \brief   cnrtcGetCompilationOutput gets the compilation output.
// \param   code[in]: cnrtcCode object.
// \param   output[out]: The memory space of output.
// \return  cnrtcStatus: CNRTC_SUCCESS if success,
//          CNRTC_NO_CODE_ERROR if cnrtcCode has not existed and
//          CNRTC_NO_OUTPUT_SPACE_ERROR if the output memory space has not been allocated.
cnrtcStatus cnrtcGetCompilationOutput(cnrtcCode code, void* output);

// \brief   cnrtcGetCompilationOutputSize gets the size of compilation output.
// \param   code[in]: cnrtcCode object.
// \param   outputSize[out]: The size of output.
// \return  cnrtcStatus: CNRTC_SUCCESS if success,
//          CNRTC_NO_CODE_ERROR if cnrtcCode has not existed and
//          CNRTC_NO_OUTPUT_SPACE_ERROR if the memory space of outputSize has not been allocated.
cnrtcStatus cnrtcGetCompilationOutputSize(cnrtcCode code, unsigned int* outputSize);

// \brief   cnrtcGetCompilationLog gets the compilation error log.
// \param   code[in]: cnrtcCode object.
// \param   log[out]: The memory space of error log.
// \return  cnrtcStatus: CNRTC_SUCCESS if success,
//          CNRTC_GET_LOG_NO_CODE_ERROR if cnrtcCode has not existed and
//          CNRTC_GET_LOG_NO_SPACE_ERROR if the memory space has not been allocated.
cnrtcStatus cnrtcGetCompilationLog(cnrtcCode code, char* log);

// \brief   cnrtcGetCompilationLogSize gets the size of compilation error log.
// \param   code[in]: cnrtcCode object.
// \param   logSize[out]: The size of error log.
// \return  cnrtcStatus: CNRTC_SUCCESS if success,
//          CNRTC_GET_LOG_SIZE_NO_CODE_ERROR if cnrtcCode has not existed and
//          CNRTC_GET_LOG_SIZE_NO_SPACE_ERROR if the memory space of logSize has not
//          been allocated.
cnrtcStatus cnrtcGetCompilationLogSize(cnrtcCode code, unsigned int* logSize);

#if defined(__cplusplus)
}
#endif

#endif  // __CNRTC_H__
