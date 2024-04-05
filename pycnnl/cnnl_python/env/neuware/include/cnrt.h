/*************************************************************************
 * Copyright (C) [2019] by Cambricon, Inc.
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *************************************************************************/

/************************************************************************
 *
 *  @file cnrt.h
 *
 *  @brief CNRT APIs provide programmable interfaces for users to develop
 *  their-owned programs, which include Device management, Context
 *  management, Memory management of both sides (devices and hosts), etc.
 *
 **************************************************************************/

#ifndef __CNRT_H
#define __CNRT_H

/************************************************************************
 *  Include files
 ************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif /*__cplusplus*/

#define CNRT_MAJOR_VERSION 6
#define CNRT_MINOR_VERSION 0
#define CNRT_PATCH_VERSION 2

#ifndef CNRT_VERSION
#define CNRT_VERSION \
  (CNRT_MAJOR_VERSION * 10000 + CNRT_MINOR_VERSION * 100 + CNRT_PATCH_VERSION)
#endif

/************************************************************************
 *  Definitions
 ************************************************************************/
/*!
 *  @brief Describes the return values of CNRT APIs.
 */
typedef enum {
  cnrtSuccess = 0,
  /*!< The API call returns with no errors. */
  cnrtErrorNotReady = 1,
  /*!< This indicates that the Device or resource requested is busy now. */
  cnrtErrorInit = 100002,
  /*!< This indicates that initialization of CNRT fails. */
  cnrtErrorNoDevice = 100004,
  /*!< This indicates that no Device is found. */
  cnrtErrorDeviceInvalid = 100005,
  /*!< This indicates that the Device ordinal passed to the API is out of range [0, cnrtGetDeviceCount() - 1]. */
  cnrtErrorArgsInvalid = 100006,
  /*!< This indicates that one of the parameters passed to the API is invalid or out of range. */
  cnrtErrorSys = 100007,
  /*!< This indicates that it fails to call system function. */
  cnrtErrorSysNoMem = 100010,
  /*!< This indicates that there is no sufficient host memory. */
  cnrtErrorInvalidResourceHandle = 100014,
  /*!< This indicates that resource handle passed to the API call is invalid. */
  cnrtErrorIllegalState = 100015,
  /*!< This indicates that a resource required by the API call is not in a valid state to
    perform the request operation. */
  cnrtErrorNotSupport = 100050,
  /*!< This indicates that the feature is not supported now. */
  cnrtErrorOpsNotPermitted = 100051,
  /*!< This indicates that the attempted operation is not permitted. */
  cnrtErrorQueue = 100060,
  /*!< This indicates that it fails to get the default Queue. */
  cnrtErrorNoMem = 100100,
  /*!< This indicates that there is no sufficient MLU Device memory. */
  cnrtErrorNoKernel = 101312,
  /*!< This indicates that CNCC has not registered the kernel to CNRT. */
  cnrtErrorNoModule = 101315,
  /*!< This indicates that CNCC has not registered the module to CNRT or fails to load the module. */

  cnrtErrorQueueCaptureUnsupported = 100360,
  /*!< This indicates that the operation is not permitted when the Queue is capturing. */

  cnrtErrorQueueCaptureInvalidated = 100361,
  /*!< This indicates that the current capture sequence on the Queue has been invalidated
    due to previous error. */

  cnrtErrorQueueCaptureWrongThread = 100362,
  /*!< This indicates that the current capture sequence on the Queue does not begin with
   ::cnrtQueueCaptureModeRelaxed mode, and ends in a different thread. */

  cnrtErrorQueueCaptureMerged = 100363,
  /*<! This indicates that two independent capture sequences are merged. */

  cnrtErrorQueueCaptureUnjoined = 100364,
  /*<! This indicates that the capture sequence contains at least a fork that is not joined
       to the primary Queue. */

  cnrtErrorQueueCaptureIsolation = 100365,
  /*<! This indicates that a Queue in capture sequence is trying to create a dependency
       which crosses the Queue capture boundary. */

  cnrtErrorQueueCaptureUnmatched = 100366,
  /*<! This indicates that the Queue in capture sequence is not the initially captured one. */

  cnrtErrorTaskTopoEntityUpdateFailure = 100400,
  /*!< This indicates that the Task Topo update is not performed because it includes
    changes which violate constraints specific to Task Topo entity update. */

  cnrtErrorSetOnActiveProcess = 632002,
  /*!< This indicates that it fails to set Device flag because the process is still active. */
  cnrtErrorDevice = 632006,
  /*!< This indicates that current resource is not from the current Device. */
  cnrtErrorNoAttribute = 632009,
  /*!< This indicates that the attribute queried does not exist. */
  cnrtErrorMemcpyDirectionInvalid = 632013,
  /*!< This indicates that the direction of memory copying passed to the API is not in ::cnrtMemTransDir_t. */
  cnrtErrorBusy = 632014,
  /*!< Deprecated, this indicates that the Device or resource is busy.*/
  cnrtErrorCndrvFuncCall = 632015,
  /*!< This indicates that it fails to call driver API. */
  cnrtErrorCndevFuncCall = 632017,
  /*!< This indicates that it fails to call CNDev API. */
  cnrtErrorNoCnrtContext = 632019,
  /*!< This indicates that no CNRT Context is found. */
  cnrtErrorCndrvFuncNotFound = 632020,
  /*!< This indicates that driver API is not found. */
  cnrtErrorUnknown = 999991,
  /*!< Unknown error. */
  cnrtErrorMax
  /*!< The last one. */
} cnrtRet_t;

/**< Execution modes of tasks on MLU Device. */
/*! @brief
 *
 *  Describes the number of cores used
 *  for computation on the MLU Devices.
 */
typedef enum {
  cnrtFuncTypeBlock = 1,
  /*!< One MLU core is used to execute tasks. */
  cnrtFuncTypeBlock0 = cnrtFuncTypeBlock,
  /*!< The IP core 0 is used to execute tasks. */
  cnrtFuncTypeBlock1 = cnrtFuncTypeBlock0 + 1,
  /*!< The IP heterogeneous core 1 is used to execute tasks. */
  cnrtFuncTypeUnion1 = 4,
  /*!< Four MLU cores are used to execute tasks. */
  cnrtFuncTypeUnion2 = 8,
  /*!< Eight MLU cores are used to execute tasks. */
  cnrtFuncTypeUnion4 = 16,
  /*!< 16 MLU cores are used to execute tasks. */
  cnrtFuncTypeUnion8 = 32,
  /*!< 32 MLU cores are used to execute tasks. */
  cnrtFuncTypeUnion16 = 64,
  /*!< 64 MLU cores are used to execute tasks. */
  cnrtFuncTypeMutable = -1,
  /*!< Not used now. */
  cnrtJobTypeBlock = cnrtFuncTypeBlock,
  /*!< One MLU core is used to execute tasks.
   *   This is only used for tensor dimension mutable function.*/
  cnrtJobTypeUnion1 = cnrtFuncTypeUnion1,
  /*!< Four MLU cores are used to execute tasks.
   *   This is only used for tensor dimension mutable function.*/
  cnrtJobTypeUnion2 = cnrtFuncTypeUnion2,
  /*!< Eight MLU cores are used to execute tasks.
   *   This is only used for tensor dimension mutable function.*/
  cnrtJobTypeUnion4 = cnrtFuncTypeUnion4,
  /*!< 16 MLU cores are used to execute tasks.
   *   This is only used for tensor dimension mutable function.*/
} cnrtFunctionType_t;

typedef cnrtFunctionType_t cnrtJobType_t;

/*!
 *  @brief
 *
 *  Describes the attributes of the MLU Device.
 */
typedef enum {
  cnrtAttrComputeCapabilityMajor = 0x01,
  /*!< Major compute capability of the MLU Device. */
  cnrtAttrComputeCapabilityMinor = 0x02,
  /*!< Minor compute capability of the MLU Device. */
  cnrtAttrSparseComputingSupported = 0x03,
  /*!< 1: The Device supports sparse computing; 0: The Device does not. */
  cnrtAttrFP16ComputingSupported = 0x04,
  /*!< 1: The Device supports FP16; 0: The Device does not. */
  cnrtAttrINT4ComputingSupported = 0x05,
  /*!< 1: The Device supports INT4; 0: The Device does not. */
  cnrtAttrINT8ComputingSupported = 0x06,
  /*!< 1: The Device supports INT8; 0: The Device does not. */
  cnrtAttrBF16ComputingSupported = 0x07,
  /*!< 1: The Device supports BF16; 0: The Device does not. */
  cnrtAttrTF32ComputingSupported = 0x08,
  /*!< 1: The Device supports TF32; 0: The Device does not. */
  cnrtAttrQueueSize = 0x101,
  /*!< The maximum number of Queues. */
  cnrtAttrNotifierSize = 0x102,
  /*!< The maximum number of Notifiers. */
  cnrtAttrSupportQueuePriorities = 0x103,
  /*!< 1: The Device supports setting Queue priorities; 0: The Device does not. */
  cnrtAttrTinyCoreSupported = 0x104,
  /*!< 1: The Device supports using tiny core to accelerate collective inter-Device or intra-Device communication; 0: The Device does not. */
  cnrtAttrCodecJPEGSupported = 0x105,
  /*!< 1: The Device supports hardware JPEG Codec acceleration; 0: The Device does not. */
  cnrtAttrCodecH264Supported = 0x107,
  /*!< 1: The Device supports hardware video H.264 Codec acceleration; 0: The Device does not. */
  cnrtAttrCodecH265Supported = 0x108,
  /*!< 1: The Device supports hardware video H.265 Codec acceleration; 0: The Device does not. */
  cnrtAttrMaxDimX = 0x201,
  /*!< The maximum block dimension X. */
  cnrtAttrMaxDimY = 0x202,
  /*!< The maximum block dimension Y. */
  cnrtAttrMaxDimZ = 0x203,
  /*!< The maximum block dimension Z. */
  cnrtAttrMaxClusterCountPerUnionTask = 0x204,
  /*!< The maximum number of clusters per union task. */
  cnrtAttrClusterCount = 0x205,
  /*!< The maximum number of clusters of the MLU Device. */
  cnrtAttrMcorePerCluster = 0x206,
  /*!< The maximum number of MLU cores of each cluster. */
  cnrtAttrMaxQuadrantCount = 0x207,
  /*!< The maximum count of quadrants per Device, intra-quadrant clusters have the best unified memory access performance. */
  cnrtAttrMaxUnionTypePerQuadrant = 0x208,
  /*!< The maximum union task types that can maintain unified memory access intra-quadrant. */
  cnrtAttrMaxClusterPerUnionLimitTask = 0x209,
  /*!< The maximum number of clusters per union limitation task. */
  cnrtAttrISAVersion = 0x20a,
  /*!< ISA version of current MLU Device in the form of three-digit number. */
  cnrtAttrIsMultipleTensorProcessor = 0x20b,
  /*!< 1: The Device adopts multi-tensor-processor architecture; 0: The Device does not. */
  cnrtAttrMaxL2CacheSize = 0x301,
  /*!< The size of L2 cache in bytes. */
  cnrtAttrNramSizePerMcore =
      0x302, /*!< The maximum nram memory available of each MLU core in bytes. */
  cnrtAttrWramSizePerMcore = 0x303,
  /*!< The maximum wram memory available of each MLU core in bytes. */
  cnrtAttrTotalConstMemorySize = 0x304,
  /*!< Memory available on Device for __mlu_const__ variables in a Cambricon BANG C kernel in megabytes. */
  cnrtAttrLmemSizePerMcore = 0x305,
  /*!< The maximum local Memory available of each core in MB. */
  cnrtAttrSramSizePerMcore = 0x306,
  /*!< The maximum sram Memory available of each MLU core in bytes. */
  cnrtAttrGlobalMemoryNodeCount = 0x307,
  /*!< The number of NUMA nodes on Device. */
  cnrtAttrCacheSize = 0x309,
  /*!< The size of system cache in bytes. */
  cnrtAttrMaxPersistingL2CacheSize = 0x309,
  /*!< The maximum L2 persisting cache size in bytes. */
  cnrtAttrEccEnable = 0x401,
  /*!< 1: the Device supports ECC; 0: the Device does not. */
  cnrtAttrIpuClockRate = 0x402,
  /*!< Cluster clock frequency in kilohertz. */
  cnrtAttrMemClockRate = 0x403,
  /*!< Memory clock frequency in kilohertz. */
  cnrtAttrGmemBusWidth = 0x404,
  /*!< Global memory bus width in bits. */
  cnrtAttrTotalMemSize = 0x405,
  /*!< The maximum available memory in MB. */
  cnrtAttrPciBusID = 0x406,
  /*!< PCI bus identifier of the MLU Device. */
  cnrtAttrPciDeviceID = 0x407,
  /*!< PCI device identifier of the MLU Device. */
  cnrtAttrPciDomainID = 0x408,
  /*!< PCI domain ID of the MLU Device. */

  /*!< Not supported yet. */
  cnrtAttrCanMapHostMemory,
  /*!< 1: The Device supports mapping host memory to MLU; 0: The Device does not. */
  cnrtAttrCanSetQueueSize,
  /*!< 1: The Device supports setting the maximum Queue size; 0: The Device does not. */
  cnrtAttrCanSetNotifierSize,
  /*!< 1: The Device supports setting the maximum Notifier size; 0: The Device does not. */
  cnrtAttrConcurrentKernels,
  /*!< 1: The Device supports multiple kernels within the same Context simultaneously; 0: The Device does not. */
  cnrtAttrSupportUnifiedAddr,
  /*!< 1: The Device supports sharing a unified address space with the host; 0: The Device does not. */
  cnrtAttrSupportManagedMem,
  /*!< 1: The Device supports allocating managed memory; 0: The Device does not. */
  cnrtAttrSupportNativeAtomic,
  /*!< 1: The link between the Device and the host supports native atomic operations; 0: The link between the Device and the host does not. */
  cnrtAttrSupportPageableMemAccess,
  /*!< 1: The Device supports accessing pageable memory coherently; 0: The Device does not. */
  cnrtAttrCanUseHostPointer,
  /*!< 1: The Device can access host registered memory at the same virtual address as the CPU; 0: The Device can not. */
  cnrtAttrSupportHostRegsiter,
  /*!< 1: The Device supports host memory registration via cnrtHostRegister; 0: The Device does not. */
  cnrtAttrMaxNum,
  /*!< The last one. */
} cnrtDeviceAttr_t;

/*!
 *  @brief
 *
 *  Describes the P2P attributes of the MLU Device.
 */
typedef enum {
  cnrtDevP2PAttrAccessSupported = 0,
  /*!< P2P access is enabled. */
  cnrtDevP2PAttrNativeAtomicSupported,
  /*!< Native atomic operation between the Device and host is supported. */
  cnrtDevP2PAttrMaxNum,
  /*!< The last one. */
} cnrtDeviceP2PAttr_t;

/*!
 *  @brief Describes the limits of the MLU Device.
 *  @deprecated This type is deleted in CNToolkit V3.0.0.
 */
typedef enum {
  cnrtDevLimitStackSize = 0,
  /*!< MLU stack size can be used for each MLU core. */
  cnrtDevLimitPrintfFifoSize,
  /*!< MLU printf FIFO size. */
  cnrtDevLimitMaxNum,
  /*!< The last one. */
} cnrtDeviceLimit_t;

/*!
 * @brief Describes the Device configuration types.
 */
typedef enum {
  cnrtDeviceConfigReserved = 0,
  /*!< Reserved. */
  cnrtDeviceConfigPrintfFifoNum = 1,
  /*!< The record number of Printf Fifo per MLU core. */
  cnrtDeviceConfigMaxPersistingL2CacheSize = 2,
  /*!< The maximum persisting L2 cache size in bytes */
  cnrtDeviceConfigMaxNum,
  /*!< The maximum number of Device configuration enums. */
} cnrtDeviceConfig_t;

/*!
 *  @brief
 *
 *  Describes the Device flags used for the
 *  current process execution on the current Device.
 *
 *  The ::cnrtGetDeviceFlag API is used to retrieve the flags set.
 *
 */
typedef enum {
  cnrtDeviceScheduleSpin = 0,
  /*!< CPU actively spins when waiting for the Device execution result. */
  cnrtDeviceScheduleBlock = 1,
  /*!< CPU thread is blocked on a synchronization primitive when
   *   waiting for the Device execution results. */
  cnrtDeviceScheduleYield = 2,
  /*!< CPU thread yields when waiting for the Device execution results. */
  cnrtDeviceScheduleAuto = 3,
  /*!< Automatic scheduling. */
  cnrtDeviceFlagsMaxNum
  /*!< The last one. */
} cnrtDeviceFlags_t;

/*! @brief
 *
 * Describes the direction of data copying.
 */
typedef enum {
  cnrtMemcpyHostToDev = 0,
  /*!< Host to Device. */
  cnrtMemcpyDevToDev,
  /*!< Data copy in a single Device. */
  cnrtMemcpyDevToHost,
  /*!< Device to host. */
  cnrtMemcpyHostToHost,
  /*!< Host to host. */
  cnrtMemcpyPeerToPeer,
  /*!< P2P in two different Devices. */
  cnrtMemcpyNoDirection,
  /*!< Data copy without a specified direction. */
} cnrtMemTransDir_t;

/*! @brief
 *
 * Describes the range attributes.
 * Not used now.
 */
typedef enum {
  cnrtMemRangeAttributePreferredLocation = 0,
  /*!< The preferred location of the range. */
  cnrtMemRangeAttributeAccessedBy,
  /*!< Memory range set for the specified Device. */
} cnrtMemRangeAttribute_t;

/*! @brief
 *
 * Describes memory types.
 */
typedef enum {
  cnrtMemTypeUnregistered = 0,
  /*!< Unregistered memory. */
  cnrtMemTypeHost,
  /*!< Host memory. */
  cnrtMemTypeDevice,
  /*!< Device memory. */
} cnrtMemType_t;

/*! @brief
 *
 * Describes UVA cache modes.
 */
typedef enum {
  cnrtUvaNotSupport = -1,
  /*!< Current platform or driver version does not support cnrtUvaCacheMode_t. */
  cnrtUvaUnknown = 0,
  /*!< Unregistered cache mode. */
  cnrtUvaUnCached,
  /*!< Non-cacheable UVA. */
  cnrtUvaCached,
  /*!< Cacheable UVA. */
} cnrtUvaCacheMode_t;

/*! @brief
 *
 * Describes properties of allocated memory.
 * Not used now.
 */
typedef enum {
  cnrtHostAllocDefault = 0,
  /*!< Default host allocation type which is equal to host memory allocated by ::cnrtHostMalloc. */
  cnrtHostAllocMapped,
  /*!< Maps the host memory directly into MLU address. */
} cnrtHostAllocFlags_t;

/*! @brief
 *
 * Describes the pointer attributes.
 */
typedef struct {
  cnrtMemType_t type;
  /*!< Memory type. */
  int device;
  /*!< Device ordinal which the pointer is allocated from. */
  size_t size;
  /*!< Size in bytes of the pointer from ::cnrtMalloc. */
  void *devicePointer;
  /*!< Device pointer related to the pointer. */
  void *hostPointer;
  /*!< Host pointer related to the pointer. */
  cnrtUvaCacheMode_t cacheMode;
  /*!< Cache mode of the host pointer. */
  void *deviceBasePointer;
  /*!< The base address of the Device pointer. */
} cnrtPointerAttributes_t;

/*! @brief
 *
 * Describes the properties of the MLU Device.
 */
typedef struct {
  char name[256];
  /*!< MLU Device name. */
} cnrtDeviceProp_t;

/*!< Parameter for API call. */
/*!
 *
 * @brief
 *
 * Describes grid dimensions used for task execution.
 *
 */
typedef struct {
  unsigned int x;
  /*!< The X axis. The value of X equals to: the number of tasks
   *   to run on each core multiplies 4.
   */
  unsigned int y;
  /*!< The Y axis. Each task is to run ``y*z`` times.*/
  unsigned int z;
  /*!< The Z axis. Each task is to run ``y*z`` times.*/
} cnrtDim3_t;

/*!
 * @brief The offset of the address.
 */
typedef struct {
  size_t x;
  /*!< The offset in the X direction.*/
  size_t y;
  /*!< The offset in the Y direction.*/
  size_t z;
  /*!< The offset in the Z direction.*/
} cnrtPos_t;

/*!
 * @brief The pitch (alignment) of the address. None of the parameters can be 0.
 */
typedef struct {
  size_t pitch;
  /*!< The pitch of the memory. It cannot be less than the p->extent.width, or greater than 4MB.*/
  void *ptr;
  /*!< The pointer of the memory. The same as the p->dst.*/
  size_t xsize;
  /*!< The memory X size. It is not in use currently, which is set to p->extent.width.*/
  size_t ysize;
  /*!< The memory Y size. It cannot be less than the p->extent.height, or greater than 4MB.*/
} cnrtPitchedPtr_t;

/*!
 * @brief The extent (size) of the address. None of the parameters can be 0.
 */
typedef struct {
  size_t depth;
  /*!< The depth of the memory.*/
  size_t height;
  /*!< The height of the memory. It cannot be greater than 1MB.*/
  size_t width;
  /*!< The width of the memory. It cannot be greater than 1MB.*/
} cnrtExtent_t;

/*!
 * @brief The configuration parameters of 3D memory copy.
 */
typedef struct cnrtMemcpy3dParam_st {
  void *dst;
  /*!< The destination address.*/
  cnrtPos_t dstPos;
  /*!< The destination address position.*/
  cnrtPitchedPtr_t dstPtr;
  /*!< The pitch of the destination address.*/
  cnrtExtent_t extent;
  /*!< The extent of the memory.*/
  cnrtMemTransDir_t dir;
  /*!< Data copy direction.*/
  void *src;
  /*!< The source address.*/
  cnrtPos_t srcPos;
  /*!< The source address position.*/
  cnrtPitchedPtr_t srcPtr;
  /*!< The pitch of the source address.*/
} cnrtMemcpy3dParam_t;

/*! @brief
 *
 * Describes the data types supported by CNRT.
 */
typedef enum cnrtDataType {
  cnrtInvalid = 0x0,
  /*!< Invalid data. */
  cnrtFloat16 = 0x12,
  /*!< 16-bit floating-point data. */
  cnrtFloat32 = 0x13,
  /*!< 32-bit floating-point data. */
  cnrtFloat64 = 0x14,
  /*!< 64-bit floating-point data. */
  cnrtInt4 = 0x20,
  /* new element */
  cnrtInt8 = 0x21,
  /*!< 8-bit integer. */
  cnrtInt16 = 0x22,
  /*!< 16-bit integer. */
  cnrtInt32 = 0x23,
  /*!< 32-bit integer. */
  cnrtInt64 = 0x24,
  /*!< 64-bit integer. */
  cnrtAuto = 0x25,
  /*!< Automatic bit-width integer, it changes among int8, int16, etc. */
  cnrtUInt8 = 0x31,
  /*!< 8-bit unsigned integer. */
  cnrtUInt16 = 0x32,
  /*!< 16-bit unsigned integer. */
  cnrtUInt32 = 0x33,
  /*!< 32-bit unsigned integer. */
  cnrtFix8 = 0x41,
  /*!< 8-bit fixed-point data. */
  cnrtQuant8 = 0x51,
  /*!< 8-bit data. */
  cnrtBool = 0x61,
  /*!< Boolean type. */
} cnrtDataType_t;

/*! @brief
 *
 * Describes the data types supported by CNRT.
 */
typedef enum cnrtDataType_V2 {
  cnrtUnknown = 0,
  /*!< Invalid data. */
  cnrtDouble = 0x1,
  /*!< 64-bit floating-point data. */
  cnrtFloat = 0x2,
  /*!< 32-bit floating-point data. */
  cnrtHalf = 0x3,
  /*!< 16-bit floating-point data. */
  cnrtBfloat = 0x4,
  /*!< BF16 data type. */
  cnrtUlonglong = 0x11,
  /*!< 64-bit unsigned integer. */
  cnrtUint = 0x12,
  /*!< 32-bit unsigned integer. */
  cnrtUshort = 0x13,
  /*!< 16-bit unsigned integer. */
  cnrtUchar = 0x14,
  /*!< 8-bit unsigned integer. */
  cnrtLonglong = 0x21,
  /*!< 64-bit integer. */
  cnrtInt = 0x22,
  /*!< 32-bit integer. */
  cnrtShort = 0x23,
  /*!< 16-bit integer. */
  cnrtChar = 0x24,
  /*!< 8-bit integer. */
  cnrtBoolean = 0x31,
  /*!< Boolean type. */
} cnrtDataType_V2_t;

/*! @brief
 *
 * Describes the rounding mode supported by CNRT.
 */
typedef enum cnrtRoundingMode {
  cnrtRounding_rn = 0,
  /*!< Converts an input number in round-to-nearest-even mode.*/
  cnrtRounding_rz = 1,
  /*!< Converts an input number in round-to-zero mode. */
  cnrtRounding_rd = 2,
  /*!< Converts an input number in round-down mode. */
  cnrtRounding_ru = 3,
  /*!< Converts an input number in round-up mode. */
  cnrtRounding_ro = 4,
  /*!< Converts an input number in round-off-zero mode. */
  cnrtRounding_rm = 5,
  /*!< Converts an input number in round-to-math mode. */
  cnrtRounding_max
  /*!< The last one. */
} cnrtRoundingMode_t;

/*!
 *
 *  @brief
 *
 *  A semi-internal struct describing the parameters to be quantized. */
struct cnrtQuantizedParam;

/*! A pointer to the struct of the parameters that are quantized. */
typedef struct cnrtQuantizedParam *cnrtQuantizedParam_t;

/*! The IPC memory handle. Pointer to void by default. */
typedef void *cnrtIpcMemHandle;

/*!
 *  @struct CNqueue_st
 *  @brief
 *
 *  Describes Queue types.
 *
 */
struct cnrtQueue;

#define cnrtQueue CNqueue_st
/*! @brief
 *
 *  A pointer to the ::cnrtQueue struct holding the information about a Queue.
 *
 *  The ::cnrtQueueCreate and ::cnrtQueueDestroy APIs are used to create
 *  and destroy an instance of cnrtQueue_t respectively.
 *
 * @note
 * - This struct CNqueue_st is the same as struct cnrtQueue, which is defined in
 *   the versions before v5.1.1. After version v5.1.2, CNqueue_st is used to avoid
 *   compile warning when called mixedly with CNDrv.
 * - A definition from cnrtQueue to CNqueue_st is used to keep compatibility.
 *
 */
typedef struct cnrtQueue *cnrtQueue_t;

/*!
 *  @struct CNnotifier_st
 *  @brief
 *
 *  Describes Notifier types.
 *
 */
struct cnrtNotifier;

#define cnrtNotifier CNnotifier_st
/*! A pointer to the ::cnrtNotifier struct holding the information
 *  about a Notifier.
 *
 *  The ::cnrtNotifierCreate and ::cnrtNotifierDestroy APIs are
 *  used to create and destroy an instance of cnrtNotifier_t respectively.
 *
 * @note
 * - This struct CNnotifier_st is the same as struct cnrtNotifier, which is defined in
 *   the versions before v5.1.1. After version v5.1.2, CNnotifier_st is used to avoid
 *   compile warning when called mixedly with CNDrv.
 * - A definition from cnrtNotifier to CNnotifier_st is used to keep compatibility.
 *
 */
typedef struct cnrtNotifier *cnrtNotifier_t;

/*!
 * @brief The flags of Notifier, which are used by ::cnrtNotifierCreateWithFlags.
 */
typedef enum cnrtNotifierFlags {
  CNRT_NOTIFIER_DEFAULT = 0x0, /*!< The default Notifier creation flag. */
  CNRT_NOTIFIER_DISABLE_TIMING =
      0x2, /*!< The Notifier will not record global timestamp to reduce overhead, but it can record hardware timestamp. */
} cnrtNotifierFlags_t;

/*! @brief
 *
 * Describes the cache operation types.
 */
typedef enum {
  CNRT_FLUSH_CACHE = 1,
  /*!< Flushes dcache of the host CPU. */
  CNRT_INVALID_CACHE = 2,
  /*!< Invalidates dcache of the host CPU, which is currently reserved. */
} cnrtCacheOps_t;

/*!
 * @brief Specifies performance hint for hitProp and missProp with ::cnrtAccessPolicyWindow.
 */
typedef enum cnrtAccessProperty {
  cnrtAccessPolicyNormal = 0,
  /*!< Normal cache persistance. */
  cnrtAccessPolicyStreaming = 1,
  /*!< Streaming access is likely to persist in cache. */
  cnrtAccessPolicyPersisting = 2,
  /*!< Persisting access is more likely to persist in cache. */
} cnrtAccessProperty_t;

/*!
 * @brief Specifies an access policy for a window.
 *
 * A contiguous extent of memory beginning at ``baseAddr`` and ending at ``baseAddr`` + ``numBytes``.
 * The regions and ration specifications are fitted to the capabilities of the architecture.
 */
typedef struct cnrtAccessPolicyWindow {
  void *baseAddr;
  /*!< Starting address of access policy window. */
  size_t numBytes;
  /*!< Size in bytes of access policy window. MLU driver may restrict the maximum size and alignment. */
  float hitRatio;
  /*!< hitRatio specifies percentage of cache lines assigned hitProp, the rest are assigned missProp.
       Valid range is [0, 1.0]. */
  enum cnrtAccessProperty hitProp;
  /*!< The access property set for cache hit in ::cnrtAccessProperty. */
  enum cnrtAccessProperty missProp;
  /*!< The access property set for cache miss in ::cnrtAccessProperty.
       It must be either ::cnrtAccessPolicyNormal or ::cnrtAccessPolicyStreaming. */
} cnrtAccessPolicyWindow_t;

/*!
 * @brief \n The Queue attribute union, which is used with ::cnrtQueueGetAttribute() and ::cnrtQueueSetAttribute().
 */
typedef union cnrtQueueAttrValue {
  cnrtAccessPolicyWindow_t accessPolicyWindow;
  /*!< Queue attribute value for ::cnrtAccessPolicyWindow. */
} cnrtQueueAttrValue_t;

/*!
 * @brief Queue attributes.
 */
typedef enum cnrtQueueAttrID {
  cnrtQueueAttributeAccessPolicyWindow = 1,
  /*!< Queue attribute ID used to change and query ::cnrtAccessPolicyWindow. */
} cnrtQueueAttrID_t;

/*! @brief
 *
 *  A pointer to the ::cnrtTaskTopo_t struct holding the information about a
 *  Task Topo.
 *
 */
typedef struct CNtaskTopo_st *cnrtTaskTopo_t;

/*! @brief
 *
 *  A pointer to the ::cnrtTaskTopoNode_t struct holding the information about a
 *  node of a Task Topo.
 *
 */
typedef struct CNtaskTopoNode_st *cnrtTaskTopoNode_t;

/*!
 * @brief Queue capture statuses.
 */
typedef enum cnrtQueueCaptureStatus {
  cnrtQueueCaptureStatusNone = 0,        /*!< Queue is not capturing. */
  cnrtQueueCaptureStatusActive = 1,      /*!< Queue is actively capturing. */
  cnrtQueueCaptureStatusInvalidated = 2, /*!< Queue is partly capturing sequence
                                              that has been invalidated, but not terminated. */
} cnrtQueueCaptureStatus_t;

/*!
 * @brief Queue capture modes.
 *
 * When a Queue is capturing, it may affect potentially unsafe APIs.
 *
 * The potentially unsafe APIs refer to memory allocation and queue synchronization
 * related APIs, such as ::cnrtQueueSync(), ::cnrtQueueQuery() and ::cnrtMalloc(), etc,
 * which may cause unexpected result per called when any Queue is capturing.
 *
 * ::cnrtQueueCaptureModeThreadLocal is not supported yet.
 */
typedef enum cnrtQueueCaptureMode {
  cnrtQueueCaptureModeGlobal = 0,
  /*!< If any Queue is actively capturing under ::cnrtQueueCaptureModeGlobal mode, all the
       potentially unsafe APIs are prohibited from calling. */
  cnrtQueueCaptureModeThreadLocal = 1,
  /*!< If any Queue is actively capturing under ::cnrtQueueCaptureModeThreadLocal mode, all
       the potentially unsafe APIs in local thread will be prohibited from calling. */
  cnrtQueueCaptureModeRelaxed = 2,
  /*!< If there are only Queue captures activated under ::cnrtQueueCaptureModeRelaxed mode,
       no potentially unsafe APIs will be prohibited from calling. */
} cnrtQueueCaptureMode_t;

/*!
 * @brief Flags for ::cnrtQueueUpdateCaptureDependencies().
 */
typedef enum cnrtUpdateQueueCaptureDependenciesFlags {
  cnrtQueueAddCaptureDependencies = 0,
  /*!< Adds new nodes to the dependency set. */
  cnrtQueueSetCaptureDependencies = 1,
  /*!< Replaces dependency set with new nodes. */
} cnrtUpdateQueueCaptureDependenciesFlags_t;

/*! @brief
 *
 * CNRT host function.
 */
typedef void (*cnrtHostFn_t)(void *usreData);

/************************************************************************
 * Function prototype declaration
 ************************************************************************/

/************************************************************************
 * Device management
 ************************************************************************/
//Group: Device Management
/**
 * @brief Retrieves the information about the Device.
 * @details Retrieves the ``device`` attributes of ``attr`` in ``pValue``.
 *          See the supported ``attr`` in ::cnrtDeviceAttr_t.
 * @param[out] pValue The pointer to Device attribute value.
 * @param[in]  attr Device attribute to retrieve.
 * @param[in]  device Device ordinal to retrieve.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoDevice
 * @note
 * - None.
 * @example
 * @code{.cpp}
    int main () {
      int ordinal = -1;
      cnrtGetDevice(&ordinal);
      int value = 0;
      cnrtDeviceGetAttribute(&value, cnrtAttrClusterCount, ordinal);
      printf("device: %d, cnrtAttrClusterCount: %d.\n", ordinal, value);

      return 0;
    }
 * @endcode
 */
cnrtRet_t cnrtDeviceGetAttribute(int *pValue, cnrtDeviceAttr_t attr,
                                 int device);
//Group: Device Management
/**
 * @brief Retrieves the information about the MLU Device.
 * @details Retrieves the ``prop`` properties of ordinal ``device``.
 *          See details in ::cnrtDeviceProp_t.
 * @param[out] prop Pointer to the returned struct ::cnrtDeviceProp_t.
 * @param[in]  device Device ordinal to retrieve.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoDevice
 * @note
 * - None.
 * @example
 * @code{.cpp}
    int main () {
      int ordinal = -1;
      cnrtGetDevice(&ordinal);
      cnrtDeviceProp_t prop;
      cnrtGetDeviceProperties(&prop, ordinal);
      printf("device: %d, device name: %s.\n", ordinal, prop.name);

      return 0;
    }
 * @endcode
 */
cnrtRet_t cnrtGetDeviceProperties(cnrtDeviceProp_t *prop, int device);
//Group: Device Management
/**
 * @brief Retrieves which Device is currently being used.
 * @details Retrieves the current MLU Device ordinal being used in ``pOrdinal``.
 * @param[out] pOrdinal Pointer to the Device ordinal being used.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoDevice
 * @note
 * - None.
 * @example
 * - See example in ::cnrtGetDeviceProperties.
 */
cnrtRet_t cnrtGetDevice(int *pOrdinal);
//Group: Device Management
/**
 * @brief Sets the Device to be used.
 * @details Sets the currently used MLU Device to ``ordinal`` for the calling
 *          host thread.
 * @param[in] ordinal The Device ordinal to be used.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoDevice
 * @note
 * - The Device ``ordinal`` ranges in [0, cnrtGetDeviceCount() - 1].
 * - All the Device memory allocated by ::cnrtMalloc after the API is called will
 *   be physically on the Device ``ordinal``. All the host memory allocated by ::cnrtHostMalloc
 *   will be associated with Device ``ordinal``. All the Queues and Notifiers will be
 *   associated with Device ``ordinal``. All the kernel launches will be executed on the Device ``ordinal``.
 * @example
 * - See example in ::cnrtMemcpyPeer.
 */
cnrtRet_t cnrtSetDevice(int ordinal);
//Group: Device Management
/**
 * @brief Retrieves the number of MLU Devices.
 * @details Retrieves in ``pCount`` the number of MLU Devices in current system.
 * @param[out] pCount Pointer to the number of MLU Devices.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - See example in ::cnrtMemcpyPeer.
 */
cnrtRet_t cnrtGetDeviceCount(unsigned int *pCount);
//Group: Device Management
/**
 * @brief Destroys all Device resources and resets all state on the current
 *        Device in the current process.
 * @details Releases all the allocated resources on the current Device in the current process.
 *          If ::cnrtDeviceReset is called, any subsequent API call to this Device will
 *          reinitialize the current Device.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorNoDevice,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - Once this API is called, the Device will be initialized immediately.
 *   So synchronize the host threads, otherwise coredump may occur.
 * @example
 * @code{.cpp}
    int main () {
      size_t size = sizeof(size_t) * N;
      void *d = NULL;
      cnrtMalloc((void **)&d, size);
      cnrtDeviceReset();

      if (cnrtSuccess == cnrtFree(d)) {
        printf("device reset failed.\n");
        return -1;
      }

      return 0;
    }
 * @endcode
 */
cnrtRet_t cnrtDeviceReset(void);
//Group: Device Management
/**
 * @brief Waits for the current Device in the current process to complete
 *        all the preceding tasks.
 * @details Blocks any further executions on the host until all the operations in the Queues
 *          in the current process on the current MLU Device are completed absolutely.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - None.
 * @example
 * - See example in ::cnrtGetLastError.
 */
cnrtRet_t cnrtSyncDevice(void);
//Group: Device Management
/**
 * @brief Retrieves the Device flags used for the current process executions on
 *        the current Device. See ::cnrtSetDeviceFlag() for flag values.
 * @details Returns in ``pFlags`` how CPU interacts with the OS scheduler when
 *          waiting for the Device execution result.
 * @param[out] pFlags Pointer to the flags specifies whether the
 *        CPU thread yields or spins when waiting for the Device execution result.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoDevice,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - None.
 * @example
 * - See example in ::cnrtSetDeviceFlag.
 */
cnrtRet_t cnrtGetDeviceFlag(uint32_t *pFlags);
//Group: Device Management
/**
 * @brief Sets flags used for the current process executions on the current Device.
 * @details After initializing the current Device, this API specifies whether the
 *          CPU thread yields or spins when waiting for the Device execution result in the ``flags``.
 * The flags of input parameters determine the CPU thread scheduler patterns, which include:
 * - cnrtDeviceScheduleSpin: Allows to spin actively when waiting for results from Device. This pattern decreases latency but may lower the performance of CPU threads and high CPU usage.
 * - cnrtDeviceScheduleBlock: The thread is blocked with low CPU usage, and enters sleep mode.
 * - cnrtDeviceScheduleYield: Allows to yield current thread when waiting for results from Device. This pattern may increase latency but increase the performance of CPU threads.
 * - cnrtDeviceScheduleAuto: Automatic scheduling. According to the device number and the number of processors in the system, choose the mode cnrtDeviceScheduleSpin or cnrtDeviceScheduleBlock.
 * @param[in] flags Options of how CPU interacts with the OS scheduler when
 *        waiting for the Device execution result. See supported flags in ::cnrtDeviceFlags_t.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorNoDevice,
 * ::cnrtErrorCndrvFuncCall,
 * ::cnrtErrorSetOnActiveProcess
 * @note
 * - This API should be called when Shared Context is inactive, and before calling
 *   ::cnrtMalloc, ::cnrtQueueCreate etc. For more details about
 *   Shared Context, see "Cambricon CNRT Upgrade Guide".

 * @example
 * @code{.cpp}
    int main () {
      unsigned int flag = 0xFFFFFFFF;
      cnrtGetDeviceFlag(&flag);
      printf("default device flag: %d.\n", flag);

      unsigned int setFlag = (unsigned int)cnrtDeviceScheduleBlock;
      cnrtSetDeviceFlag(setFlag);
      cnrtGetDeviceFlag(&flag);
      printf("device flag after set flag: %d.\n", flag);

      return 0;
    }
 * @endcode
 */
cnrtRet_t cnrtSetDeviceFlag(uint32_t flags);
//Group: Device Management
/**
 * @brief Gets Device resource configurations.
 * @details Returns in ``pValue`` the current value of the configuration ``type``.
 *
 * @param[out] pValue  Returned value of configuration type.
 * @param[in]  type    Configuration type.
 *
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorCndrvFuncCall
 *
 * @note
 * - None.
 *
 * @example
 * @code{.cpp}
   int main() {
     int64_t value;
     cnrtRet_t res = cnrtDeviceSetConfig(cnrtDeviceConfigPrintfFifoNum, 4096);
     assert(res == cnrtSuccess);
     res = cnrtDeviceGetConfig(&value, cnrtDeviceConfigPrintfFifoNum);
     assert(res == cnrtSuccess && value == 4096);
   }
 * @endcode
 */
cnrtRet_t cnrtDeviceGetConfig(int64_t *pValue, cnrtDeviceConfig_t type);
//Group: Device Management
/**
 * @brief Sets Device resource configurations.
 * @details Sets ``type`` to ``value`` to update the current configuration maintained
 *          by the Device.
 *          The ``value`` may be rounded up or down to the nearest legal value.
 *
 * @param[in] type    Configuration type to set.
 * @param[in] value   Value of configuration type.
 *
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorCndrvFuncCall
 *
 * @note
 * - None.
 * @example
 * - See example in ::cnrtDeviceGetConfig().
 */
cnrtRet_t cnrtDeviceSetConfig(cnrtDeviceConfig_t type, int64_t value);
//Group: Device Management
/**
 * @brief Retrieves the inter-process memory handle for an allocated host or
 *        MLU Device memory within the same process.
 * @details Returns the inter-process memory handle ``handle`` with the given host
 *          or MLU Device memory pointed by ``ptr`` within the same process.
 *          The host or MLU Device memory must be allocated by the ::cnrtHostMalloc or ::cnrtMalloc.
 * @param[out] handle Pointer to the unique inter-process handle for the host
 *                    or MLU Device memory to share.
 * @param[in] ptr Base pointer to the allocated host or MLU Device memory.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - None.
 * @example
 * @code{.cpp}
    int main () {
      int fd[2];
      if (pipe(fd) < 0) {
        printf("pipe fd failed.\n");
        return -1;
      }

      size_t size = 0x10000000;
      void *d_a = NULL;
      cnrtIpcMemHandle handle;
      pid_t pid = fork();

      if (pid == 0) {
        close(fd[1]);
        void *address = NULL;
        if (!read(fd[0], &handle, sizeof(handle))) {
          printf("read err.\n");
          return;
        }

        // Map the inter-process memory handle exported from another process
        cnrtMapMemHandle((void **)&address, handle, 0);
        cnrtMemset(address, 2, size);
        cnrtUnMapMemHandle(address);
        printf("child process dev addr[%p] mem handle[%p]\n", address, handle);
        exit(EXIT_SUCCESS);
      } else {
        cnrtMalloc((void **)&d_a, size);
        cnrtMemset(d_a, 1, size);

        // Acquire an inter-process memory handle
        cnrtAcquireMemHandle(&handle, d_a);
        printf("parent process d_a[%p] mem handle[%p]\n", d_a, handle);
        close(fd[0]);
        if (!write(fd[1], &handle, sizeof(handle))) {
          printf("write err.\n");
          return;
        }
        int status = -1;
        if (waitpid(pid, &status, 0) < 0) {
          printf("%s, waitpid error.\n", __func__);
          exit(EXIT_FAILURE);
        }
        EXPECT_EQ(WEXITSTATUS(status), EXIT_SUCCESS);
        EXPECT_NE(WIFEXITED(status), 0);
        char *h_a = (char *)malloc(size);
        cnrtMemcpy((void *)h_a, (void *)d_a, size, cnrtMemcpyNoDirection);
        for (size_t i = 0; i < size; i++) {
          if (2 != h_a[i]) {
            printf("data copy error.\n");
            break;
          }
        }
      }

      return 0;
    }
 * @endcode
 */
cnrtRet_t cnrtAcquireMemHandle(cnrtIpcMemHandle *handle, void *ptr);
//Group: Device Management
/**
 * @brief Maps an inter-process memory handle exported from another process and
 *        returns a Device pointer usable in the local process.
 * @details Maps an inter-process memory handle ``handle`` shared by another process into
 *          the memory address space of the current MLU Device or host. Returns the
 *          host or MLU Device memory pointer pointed by ``memPtr`` used in the local process.
 * @param[out] ptr Pointer to the host or MLU Device memory.
 * @param[in]  handle The inter-process memory handle shared by another process.
 * @param[in]  flags Flags used in this operation. Currently it only supports value 0.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - None.
 * @example
 * - See example in ::cnrtAcquireMemHandle.
 */
cnrtRet_t cnrtMapMemHandle(void **ptr, cnrtIpcMemHandle handle, int flags);
//Group: Device Management
/**
 * @brief Attempts to close memory mapped with ::cnrtMapMemHandle.
 * @details Unmaps the mapping between the memory address space of the current Device or host
 *          pointed by ``ptr`` and the inter-process memory handle shared by another process.
 *          The mapping relation is created by ::cnrtMapMemHandle.
 * @param[in] ptr Pointer to the host or MLU Device memory.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - None.
 * @example
 * - See example in ::cnrtAcquireMemHandle.
 */
cnrtRet_t cnrtUnMapMemHandle(void *ptr);
//Group: Device Management
/**
 * @brief Queries if an MLU Device is capable of directly accessing data
 *        on another MLU Device.
 * @details Returns in ``canAccess`` if an MLU Device ``ordinal`` can access data
 *          on another MLU Device ``peerOrdinal``. If ``ordinal`` can access
 *          data on another MLU Device ``peerOrdinal``, *canAccess is 1,
 *          otherwise it is 0.
 * @param[out] canAccess Pointer to the return value 1 or 0. If ``ordinal`` is
 *             able to access memories on another MLU Device ``peerOrdinal``,
 *             the return value is 1, otherwise the return value is 0.
 * @param[in] ordinal The ordinal of the Device if it can directly access
 *            memories on another Device. Call ::cnrtGetDeviceCount
 *            to get the total number of devices in the system. The Device
 *            ID is in the range [0, ::cnrtGetDeviceCount() – 1].
 * @param[in] peerOrdinal The ordinal of the Device on which memories can be
 *            directly accessed. Call ::cnrtGetDeviceCount
 *            to get the total number of devices in the system. The ID of the
 *            Device is in the range [0, ::cnrtGetDeviceCount() – 1].
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorDeviceInvalid,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - None.
 * @example
 * - See example in ::cnrtMemcpyPeer.
 */
cnrtRet_t cnrtGetPeerAccessibility(unsigned int *canAccess, int ordinal,
                                   int peerOrdinal);
//Group: Device Management
/**
 * @brief Retrieves the PCI bus ID for the required Device.
 * @details Returns a string ``pciBusId`` of the ``device`` with a specified ``len``.
 * @param[out] pciBusId Pointer to the identifier for the Device with the
 *                      format [domain]:[bus]:[device].[function]. The ``domain``, ``bus``,
 *                      ``device``, ``function`` will be shown as hexadecimal values.
 * @param[in] len The specified maximum length of string.
 * @param[in] device The Device ordinal.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorDeviceInvalid,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - None.
 * @example
 * - See example in ::cnrtDeviceGetByPCIBusId API.
 */
cnrtRet_t cnrtDeviceGetPCIBusId(char *pciBusId, int len, int device);
//Group: Device Management
/**
 * @brief Retrieves a pointer to Device.
 * @details Returns in the ``device`` by giving a PCI bus ID ``pciBusId``.
 * @param[out] device Pointer to the Device ordinal.
 * @param[in]  pciBusId String in one of the following forms : [domain]:[bus]:[device].[function][domain]:[bus]:[device][bus]:[device].[function]
 *                      where ``domain``, ``bus``, ``device`` and ``function`` are all hexadecimal values.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorDeviceInvalid,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - None.
 * @example
 * @code{.cpp}
    int main () {
      unsigned int count = 0;
      cnrtGetDeviceCount(&count);
      char str[100];
      int device = -1, ordinal = -1;
      for (unsigned int i = 0; i < count; i++) {
        cnrtSetDevice(i);
        cnrtDeviceGetPCIBusId(str, 100, i);
        cnrtDeviceGetByPCIBusId(&device, str);
        cnrtGetDevice(&ordinal);
        if (device != ordinal) {
          printf("Error: not the same device ordinal.\n");
        }
      }
      return 0;
    }
 * @endcode
 */
cnrtRet_t cnrtDeviceGetByPCIBusId(int *device, const char *pciBusId);
//Group: Device Management
/**
 * @brief Retrieves numerical values that correspond to the least and greatest
 *        Queue priorities.
 * @details Returns in ``*pMinPriority`` and ``*pMaxPriority`` the numerical
 *          values that correspond to the least and greatest Queue priorities
 *          respectively. Queue priorities follow a convention where lower numbers
 *          imply greater priorities. The range of meaningful Queue priorities is
 *          given by [``*pMinPriority``, ``*pMaxPriority``]. If the user
 *          attempts to create a Queue with a priority value that is out of the
 *          meaningful range as specfied by this API, the priority is automatically
 *          clamped down or up to either ``*pMinPriority`` or ``*pMaxPriority``
 *          respectively. Please see ::cnrtQueueCreateWithPriority for details on
 *          creating a priority Queue.
 * @param[out] pMinPriority Pointer to an integer in which the numerical value
 *             for least Queue priority is returned.
 * @param[out] pMaxPriority Pointer to an integer in which the numerical value
 *             for greatest Queue priority is returned.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - None.

 * @example
 * - See example in ::cnrtQueueCreateWithPriority API.
 */
cnrtRet_t cnrtDeviceGetQueuePriorityRange(int *pMinPriority, int *pMaxPriority);

// Group: Device Management
/**
 * @brief Resets all persisting cache lines in cache normal status.
 *
 * @details Resets all persisting cache lines for current Device.
 *          This function takes effect immediately once it is returned.
 *
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorNotSupport
 *
 * @note
 * - None.

 * @example
 * - None.
 */
cnrtRet_t cnrtDeviceResetPersistingL2Cache(void);

/************************************************************************
 * Execution control
 ************************************************************************/
//Group: Execution Control Management
/**
 * @brief Enqueues a host function call in a Queue.
 * @details
 * This API is an asynchronous interface and ::cnrtSuccess does not
 * represent the completion of host function execution.
 * Call ::cnrtQueueQuery() or ::cnrtQueueSync() to confirm whether the host function call in the Queue has been executed.
 * The host function call must not perform any synchronization that may depend on other CN tasks not mandated
 * to run earlier.
 * Without a mandated order, host function is executed (in independent Queues) in undefined order
 * and may be serialized.
 *
 * @param[in] queue    Enqueued queue.
 * @param[in] fn       The CPU function to call once preceding queue
 *                     operations are complete.
 * @param[in] userData User-specified data to be passed to the function.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorInit,
 * ::cnrtErrorCndrvFuncCall
 *
 * @note
 *  - The host function call must not make any CNRT or driver API call.
 *    Attempting to use CNRT and driver API may result in ::cnrtErrorCndrvFuncCall.
 *
 *
 * @example
 * @code{.cpp}
    // test.mlu
    void hostFunc1(void *args) {
      printf("%s: %p\n", __func__, args);
    }
    void hostFunc2(void *args) {
      printf("%s: %p\n", __func__, args);
    }
    __mlu_global__ kernel() {
      printf("%s\n", __func__);
    }

    int main() {
      void *arg1 = 0x1;
      void *arg2 = 0x2;

      // nullptr for default queue also works
      cnrtQueue_t queue;
      cnrtQueueCreate(&queue);

      // ...
      kernel<<<dim, cnrtFuncTypeBlock, queue>>>();

      cnrtInvokeHostFunc(queue, hostFunc1, arg1);
      cnrtInvokeHostFunc(queue, hostFunc2, arg2);
      cnrtQueueSync(queue);

      // print out:
      // kernel
      // hostFunc1: 1
      // hostFunc2: 2

      // ...
    }
 * @endcode
 */
cnrtRet_t cnrtInvokeHostFunc(cnrtQueue_t queue, cnrtHostFn_t fn,
                             void *userData);

/************************************************************************
 * Memory management
 ************************************************************************/
//Group: Memory Management
/**
 * @brief Allocates memory on the current Device.
 * @details Allocates the ``bytes`` size of current MLU Device memory, and
 *          returns a pointer ``pPtr`` to the allocated memory.
 * @param[out] pPtr Pointer to allocated MLU memory.
 * @param[in]  bytes Requested memory size in bytes.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorNoMem,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - Call ::cnrtFree to release the allocated memory, otherwise memory leak may occur.

 * @example
 * @code{.cpp}
    int main () {
      // Specify the memory size
      size_t size = sizeof(size_t) * N;
      // Allocate page-locked memory. For more information about the advantages of using the cnrtHostMalloc,
      // see cnrtHostMalloc description.
      void *h = NULL;
      cnrtHostMalloc((void **)&h, size);

      // Initialize host memory allocated before
      ...

      // Allocate device memory
      void *d = NULL;
      cnrtMalloc((void **)&d, size);

      // Copy data from host to device
      cnrtMemcpy(d, h, size, cnrtMemcpyHostToDev);
      // Copy data from device to host
      cnrtMemcpy(h, d, size, cnrtMemcpyDevToHost);

      // Free resource
      cnrtFreeHost(h);
      cnrtFree(d);

      return 0;
    }
 * @endcode
 */
cnrtRet_t cnrtMalloc(void **pPtr, size_t bytes);
//Group: Memory Management
/**
 * @brief Frees the memory on the Device.
 * @details Frees the MLU Device memory pointed by ``ptr``, which must have been
 *          returned by a previous call to ::cnrtMalloc. Otherwise, if
 *          ::cnrtFree(``ptr``) has already been called before, an error is returned.
 *          If ``ptr`` is 0, no operation is performed.
 * @param[in] ptr Pointer to the Device memory to be freed.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - None.

 * @example
 * - See example in ::cnrtMalloc.
 */
cnrtRet_t cnrtFree(void *ptr);
//Group: Memory Management
/**
 * @brief Allocates page-locked memory on the host.
 * @details Allocates size of ``bytes`` of page-locked host memory, and
 *          returns a pointer ``pPtr`` to the allocated memory.
 *          The memory ranges allocated with this API can be tracked by the driver
 *          so that the API calls such as ::cnrtMemcpy are accelerated automatically.
 *          In comparison with pageable memory requested by the system Malloc function,
 *          the page-locked memory has a better read and write performance. However,
 *          allocating large amount of page-locked memory with this API may lead to
 *          lower performance due to reduction of available amount of memory for paging.
 *          So for best practice, it is recommended to use this API to allocate staging areas for data
 *          exchange between host and the MLU Device.
 * @param[out] pPtr Pointer to the allocated host memory.
 * @param[in]  bytes The size requested to allocate.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorNoMem,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - Call ::cnrtFreeHost to release the allocated host memory,
 *   otherwise the memory leak may occur.

 * @example
 * - See example in ::cnrtMalloc API.
 */
cnrtRet_t cnrtHostMalloc(void **pPtr, size_t bytes);
//Group: Memory Management
/**
 * @brief Frees the page-locked memory.
 * @details Frees the host memory pointed by ``ptr``, this API is only used to
 *          free the host memory that is allocated by the ::cnrtHostMalloc.
 * @param[in] ptr Pointer to free the host memory.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - None.

 * @example
 * - See example in ::cnrtMalloc API.
 */
cnrtRet_t cnrtFreeHost(void *ptr);
//Group: Memory Management
/**
 * @brief Copies data from source address to destination address.
 * @details Synchronously copies the size of ``bytes`` bytes of data from the source address
 *          pointed by ``src`` to the destination address pointed by ``dst`` with the copy
 *          direction ``dir``. The ``dir`` must be one of ::cnrtMemcpyHostToDev,
 *          ::cnrtMemcpyDevToDev, ::cnrtMemcpyDevToHost, ::cnrtMemcpyHostToHost,
 *          ::cnrtMemcpyPeerToPeer, and ::cnrtMemcpyNoDirection, in ::cnrtMemTransDir_t.
 * @param[in] dst Pointer to the destination address.
 * @param[in] src Pointer to the source address.
 * @param[in] bytes The memory size in bytes to be copied.
 * @param[in] dir Data copying direction.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorMemcpyDirectionInvalid,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - This API is used to copy data synchronously. To copy data asynchronously,
 *   call ::cnrtMemcpyAsync.

 * @example
 * - See example in ::cnrtMalloc API.
 */
cnrtRet_t cnrtMemcpy(void *dst, void *src, size_t bytes, cnrtMemTransDir_t dir);
//Group: Memory Management
/**
 * @brief Uses 2D to copy data from source address to destination address.
 * @details Synchronously reads ``spitch * width`` bytes of data
 *          from the source address pointed by ``src``, and writes it to the
 *          ``dpitch * width`` bytes of destination address pointed by ``dst``
 *          with the copy direction ``dir``. The ``dir`` must be in
 *         ::cnrtMemTransDir_t. The ``dir`` must be cnrtMemcpyDevToDev
 *          or cnrtMemcpyNoDirection.
 * @param[in] dst Pointer to the destination address.
 * @param[in] dpitch The pitch of the destination memory. It cannot be
 *  less than the width, or greater than 4MB.
 * @param[in] src Pointer to the source address.
 * @param[in] spitch The pitch of the source memory. It cannot be
 *  less than the width, or greater than 4MB.
 * @param[in] width The width of the memory to be copied. It cannot be
 *  greater than 1MB.
 * @param[in] height The height of the memory to be copied. It cannot be
 *  greater than 1MB.
 * @param[in] direction Data copy direction. It must be
 *  cnrtMemcpyDevToDev or cnrtMemcpyNoDirection.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorMemcpyDirectionInvalid,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - It only supports CE platform currently.
 * - None of the parameters can be 0. The size (width * height) of
 *   the data transfer cannot be greater than 16MB.

 * @example
 * @code{.cpp}
   // ...
   // Specify the memory size
   size_t size = dpitch * spitch;

   // Allocate device memory of the source memory
   void *src = NULL;
   cnrtMalloc((void **)&src, size);

   // Initialize src memory allocated before
   ...

   // Allocate device memory of the destination memory
   void *dst = NULL;
   cnrtMalloc((void **)&dst, size);

   // Initialize param of dpitch, spitch, width, height
   ...

   // Use 2D to copy data from src to dst
   cnrtMemcpy2D(dst, dpitch, src, spitch, width, height, cnrtMemcpyDevToDev);

   // Free resource
   cnrtFree(src);
   cnrtFree(dst);
   // ...
 * @endcode
 */
cnrtRet_t cnrtMemcpy2D(void *dst, size_t dpitch, const void *src, size_t spitch,
                       size_t width, size_t height,
                       cnrtMemTransDir_t direction);
//Group: Memory Management
/**
 * @brief Uses 3D to copy data from source address to destination address.
 * @details Synchronously reads ``src_size`` bytes of data from the
 *          source address pointed by ``p->src`` or ``p->srcPtr.ptr`` , and
 *          writes it to the ``dst_size`` bytes of data from the
 *          destination address pointed by ``p->dst`` or ``p->dstPtr.ptr`` .
 *          The ``src_size`` is configured by ``p->extent`` and ``p->srcPtr`` ,
 *          the ``dst_size`` is configured by ``p->extent`` and ``p->dstPtr`` .
 *          The copy direction ``direction`` must be in ::cnrtMemTransDir_t.
 *          The ``direction`` must be cnrtMemcpyDevToDev or cnrtMemcpyNoDirection.
 * @param[in] p Pointer to the 3D memory copy parameter.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorMemcpyDirectionInvalid,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - It only supports CE platform currently.
 * - The size (p->extent.width * p->extent.height * pst->extent.depth) of
 *   the data transfer cannot be greater than 16MB.

 * @example
 * @code{.cpp}
   // ...
   cnrtMemcpy3dParam_t *p;
   p = (cnrtMemcpy3dParam_t *)malloc(sizeof(*p));

   // Initialize 3D param of p
   ...

   // Specify the memory size
   size_t size = dstPtr.pitch * srcPtr.pitch * extent.depth;

   // Allocate device memory of the source memory
   void *src = NULL;
   cnrtMalloc((void **)&src, size);

   // Initialize src memory allocated before
   ...

   // Allocate device memory of the destination memory
   void *dst = NULL;
   cnrtMalloc((void **)&dst, size);

   p->dstPtr.ptr = dst;
   p->srcPtr.ptr = src;

   // Use 3D to copy data from src to dst
   cnrtMemcpy3D(p);

   // Free resource
   cnrtFree(src);
   cnrtFree(dst);
   free(p);
   // ...
 * @endcode
 */
cnrtRet_t cnrtMemcpy3D(const cnrtMemcpy3dParam_t *p);
//Group: Memory Management
/**
 * @brief Copies data from source address to destination address asynchronously.
 * @details Asynchronously copies the size of ``bytes`` bytes of data from the source address
 *          pointed by ``src`` to the destination address pointed by ``dst`` with the copy
 *          direction ``dir``. The ``dir`` must be one of ::cnrtMemcpyHostToDev,
 *          ::cnrtMemcpyDevToDev, ::cnrtMemcpyDevToHost, ::cnrtMemcpyHostToHost,
 *          ::cnrtMemcpyPeerToPeer, and ::cnrtMemcpyNoDirection, in ::cnrtMemTransDir_t.
 * @param[in] dst Pointer to the destination address.
 * @param[in] src Pointer to the source address.
 * @param[in] bytes The memory size to be copied in bytes.
 * @param[in] dir Data copying direction.
 * @param[in] queue The Queue handle created by calling the ::cnrtQueueCreate.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorMemcpyDirectionInvalid,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - This API is used to copy data asynchronously. To copy data synchronously,
 *   call ::cnrtMemcpy.

 * @example
 * @code{.cpp}
    int main () {
      // Prepare input and output
      size_t size = sizeof(size_t) * N;
      char *h0 = NULL;
      char *h1 = NULL;
      cnrtHostMalloc((void **)&h0, size);
      cnrtHostMalloc((void **)&h1, size);
      memset(h0, 'a', size);

      void *d = NULL;
      cnrtMalloc((void **)&d, size);

      // Create queue
      cnrtQueue_t queue;
      cnrtQueueCreate(&queue);

      // Memcpy Async
      cnrtMemcpyAsync(d, h0, size, queue, cnrtMemcpyHostToDev);
      cnrtMemcpyAsync(h1, d, size, queue. cnrtMemcpyDevToHost);
      cnrtQueueSync(queue);

      // Free resource
      cnrtQueueDestroy(queue);
      cnrtFreeHost(h0);
      cnrtFreeHost(h1);
      cnrtFree(d);

      return 0;
    }
 * @endcode
 */
cnrtRet_t cnrtMemcpyAsync(void *dst, void *src, size_t bytes, cnrtQueue_t queue,
                          cnrtMemTransDir_t dir);
//Group: Memory Management
/**
 * @brief Copies data between two Devices.
 * @details Synchronously copies ``bytes`` of data from the address pointed by ``src``
 *          in source Device ordinal ``srcDev`` to the address pointed by ``dst`` in
 *          destination Device ordinal ``dstDev``.
 * @param[in] dst Pointer to the destination address.
 * @param[in] dstDev The destination Device ordinal.
 * @param[in] src Pointer to the source address.
 * @param[in] srcDev The source Device ordinal.
 * @param[in] bytes The memory size to be copied in bytes.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorDeviceInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorMemcpyDirectionInvalid,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - Devices support peer-to-peer communications. If the two MLU Devices
 *   are not peerable, it may be hardware problems.
 * - The two Devices must be peerable when calling ::cnrtMemcpyPeer to copy data. Call
 *   ::cnrtGetPeerAccessibility to check if the two Devices are peerable.

 * @example
 * @code{.cpp}
    int main () {
      unsigned int count = 0;
      cnrtGetDeviceCount(&count);
      if (count < 2) {
        printf("Warning: Two or more MLU Devices are required for Peer-to-Peer.\n");
        return 0;
      }

      // To simplify sample code, it is supposed that srcDev is 0, and dstDev is 1
      int srcDev = 0;
      int dstDev = 1;

      int canAccess = -1;
      cnrtGetPeerAccessibility(&canAccess, srcDev, dstDev);
      if (canAccess != 1) {
          printf("Error: There is no p2p accessibility MLU Devices in the current system.\n");
          return -1;
      }

      cnrtSetDevice(srcDev);
      char *src = NULL;
      cnrtMalloc((void **)&src, size);
      cnrtMemset(src, 'a', size);

      cnrtSetDevice(dstDev);
      char *dst = NULL;
      cnrtMalloc((void **)&dst, size);

      cnrtMemcpyPeer(dst, dstDev, src, srcDev, size);

      // Free resource
      cnrtFree((void *)src);
      cnrtFree((void *)dst);

      return 0;
    }
 * @endcode
 */
cnrtRet_t cnrtMemcpyPeer(void *dst, int dstDev, void *src, int srcDev,
                         size_t bytes);
//Group: Memory Management
/**
 * @brief Copies data between two Devices asynchronously.
 * @details Asynchronously copies ``bytes`` of data from the address pointed by ``src``
 *          in source Device ordinal ``srcDev`` to the address pointed by ``dst`` in
 *          destination Device ordinal ``dstDev``.
 * @param[in] dst Pointer to the destination address.
 * @param[in] dstDev The destination Device ordinal.
 * @param[in] src Pointer to the source address.
 * @param[in] srcDev The source Device ordinal.
 * @param[in] queue The Queue handle created by calling ::cnrtQueueCreate.
 * @param[in] bytes The memory size to be copied in bytes.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorDeviceInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorMemcpyDirectionInvalid,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - This API is used to copy data asynchronously. To copy data synchronously,
 *   call ::cnrtMemcpyPeer.
 * - Devices support peer-to-peer communications. If the two MLU Devices
 *   are not peerable, it may be hardware problems.
 * - The two Devices must be peerable when calling ::cnrtMemcpyPeerAsync to copy data. Call
 *   ::cnrtGetPeerAccessibility to check if the two Devices are peerable.
 * @example
 * @code{.cpp}
    int main () {
      unsigned int count = 0;
      cnrtGetDeviceCount(&count);
      if (count < 2) {
        printf("Warning: Two or more MLU Devices are required for Peer-to-Peer.\n");
        return 0;
      }

      // To simplify sample code, suppose sdev is 0, ddev is 1
      int srcDev = 0;
      int dstDev = 1;

      int canAccess = -1;
      cnrtGetPeerAccessibility(&canAccess, srcDev, dstDev);
      if (canAccess != 1) {
          printf("Error: There is no P2P accessibility MLU Devices in the current system.\n");
          return -1;
      }

      cnrtSetDevice(srcDev);
      char *src = NULL;
      cnrtMalloc((void **)&src, size);

      cnrtQueue_t queue;
      cnrtQueueCreate(&queue);
      cnrtMemsetAsync(src, 'a', size, queue);

      cnrtSetDevice(dstDev);
      char *dst = NULL;
      cnrtMalloc((void **)&dst, size);

      cnrtMemcpyPeer(dst, dstDev, src, srcDev, size, queue);
      cnrtQueueSync(queue);

      // Free resource
      cnrtFree((void *)src);
      cnrtFree((void *)dst);
      cnrtQueueDestroy(queue);

      return 0;
    }
 * @endcode
 */
cnrtRet_t cnrtMemcpyPeerAsync(void *dst, int dstDev, void *src, int srcDev,
                              size_t bytes, cnrtQueue_t queue);
//Group: Memory Management
/**
 * @brief Gets the free and total Device memory.
 * @details Returns in ``free`` and ``total`` respectively, the free and total
 *          amount of memory available for allocation by the Device.
 * @param[out] free Pointer to the free memory in bytes.
 * @param[out] total Pointer to the total memory in bytes.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - None.
 * @example
 * @code{.cpp}
    int main () {
      size_t available, total;
      cnrtMemGetInfo(&available, &total);
      printf("free: %#lx, total: %#lx.\n", available, total);
      return 0;
    }
 * @endcode
 */
cnrtRet_t cnrtMemGetInfo(size_t *free, size_t *total);
//Group: Memory Management
/**
 * @brief Initializes or sets Device memory to a value.
 * @details Synchronously fills the first ``bytes`` of the memory area pointed
 *          to by ``ptr`` with constant byte value ``value``.
 * @param[in] ptr Pointer to the Device address to be set.
 * @param[in] value The value to set.
 * @param[in] bytes Size in bytes to set.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - This API is used to copy data synchronously. To copy data asynchronously,
 *   call ::cnrtMemsetAsync.
 * @example
 * - See example in ::cnrtMalloc API.
 */
cnrtRet_t cnrtMemset(void *ptr, int value, size_t bytes);
//Group: Memory Management
/**
 * @brief Initializes or sets Device memory to a value.
 * @details Asynchronously fills the first ``bytes`` of the memory area pointed
 *          to by ``ptr`` with constant byte value ``value``.
 * @param[in] ptr Pointer to the Device address to be set.
 * @param[in] value The value to set.
 * @param[in] bytes Size in bytes to set.
 * @param[in] queue The queue.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - This API is used to set data asynchronously. To copy data synchronously,
 *   call ::cnrtMemset.
 * @example
 * - See example in ::cnrtMemcpyAsync API.
 */
cnrtRet_t cnrtMemsetAsync(void *ptr, int value, size_t bytes,
                          cnrtQueue_t queue);
//Group: Memory Management
/**
 * @brief Gets the attributes of a specified pointer.
 * @details Gets attributes of ``ptr`` in ``attr``. See "Cambricon BANG C/C++ Programming Guide" for details.
 * @param[out] attr Pointer to ::cnrtPointerAttributes_t.
 * @param[in] ptr A specified pointer.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorNotSupport,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - None.
 * @example
 * @code{.cpp}
    int main () {
      cnrtPointerAttributes_t attributes;
      size_t size = sizeof(size_t) * N;
      void *dev_addr = NULL, *cpu_addr = NULL;

      cnrtMalloc(&dev_addr, size);
      cnrtMmap(dev_addr, &cpu_addr, size);

      // UVA without offset
      cnrtPointerGetAttributes(&attributes, cpu_addr);
      if (attributes.devicePointer != dev_addr) {
        printf("cnrtPointerGetAttributes failed.\n");
        return -1;
      }

      // UVA with offset
      cnrtPointerGetAttributes(&attributes, (void *)((unsigned long)cpu_addr + 0x100));
      if (attributes.devicePointer != (void *)((unsigned long)dev_addr + 0x100)) {
        printf("cnrtPointerGetAttributes failed.\n");
        return -1;
      }

      cnrtMunmap(cpu_addr, size);
      cnrtFree(dev_addr);

      return 0;
    }
 * @endcode
 */
cnrtRet_t cnrtPointerGetAttributes(cnrtPointerAttributes_t *attr,
                                   const void *ptr);

/************************************************************************
 * Notify management
 ************************************************************************/
//Group: Notifier Management
/**
 * @brief Creates a Notifier for the current Device.
 * @details Returns a pointer
 *          ``notifier`` to the newly created Notifier. For more information about Notifier,
 *          see "Cambricon BANG C/C++ Programming Guide".
 * @param[out] pNotifier Pointer to the newly created Notifier.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - Call ::cnrtNotifierDestroy to release the Notifier memory;
 *   otherwise the memory leaks may occur.
 * - To learn more about Queue life cycle management, see
 *   "Cambricon Driver API Developer Guide".
 * @example
 * - See example in ::cnrtNotifierElapsedTime.
 */
cnrtRet_t cnrtNotifierCreate(cnrtNotifier_t *pNotifier);
//Group: Notifier Management
/**
 * @brief Creates a Notifier with flags for the current Device.
 * @details Returns a pointer
 *          ``notifier`` to the newly created Notifier. The flags that can be specified include
 *          ::CNRT_NOTIFIER_DEFAULT,
 *          ::CNRT_NOTIFIER_DISABLE_TIMING.
 *          For more information about Notifier, see "Cambricon BANG C/C++ Programming Guide".
 *
 * @param[out] pNotifier Pointer to the newly created Notifier.
 * @param[in]   flags Notifier creation flags.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - Call cnrtNotifierDestroyto release the Notifier memory;
 *   otherwise the memory leaks may occur.
 * - To learn more about Queue life cycle management, see
 *   "Cambricon Driver API Developer Guide".
 * @example
 * - See example in ::cnrtNotifierElapsedTime.
 */
cnrtRet_t cnrtNotifierCreateWithFlags(cnrtNotifier_t *pNotifier,
                                      unsigned int flags);
//Group: Notifier Management
/**
 * @brief Destroys a Notifier that is created by ::cnrtNotifierCreate.
 * @details Destroys a Notifier pointed by ``notifier``. For more information about Notifier,
 *          see "Cambricon BANG C/C++ Programming Guide".
 * @param[in] notifier Notifier that is created by ::cnrtNotifierCreate.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - If a Notifier is placed into a Queue, but it is not completed when the ::cnrtNotifierDestroy
 *   API is called, the ::cnrtNotifierDestroy API will return immediately; but
 *   the resources associated with this Notifier will be released automatically only after
 *   the Notifier is completed.
 * @example
 * - See example in ::cnrtNotifierElapsedTime.
 *
 *
 */
cnrtRet_t cnrtNotifierDestroy(cnrtNotifier_t notifier);
//Group: Notifier Management
/**
 * @brief Computes the software time duration between the starting and ending of Notifiers.
 * @details Computes the software time duration between the starting Notifier ``start``
 *          and the ending Notifier ``end``. This API is used to measure the
 *          execution time of all the tasks between the starting Notifier and
 *          ending Notifier. The measurement that can be used to improve the performance.
 * @param[in] start The handle of the starting Notifier created by the
 *                  ::cnrtNotifierCreate API.
 * @param[in] end The handle of ending Notifier created by the ::cnrtNotifierCreate
 *                API.
 * @param[out] ms The software time duration between the starting and ending of Notifiers in ms.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorBusy,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - Call ::cnrtPlaceNotifier to place the starting and ending
 *   Notifiers into the Queue respectively first.
 *   Otherwise, ::cnrtErrorCndrvFuncCall is returned.
 * - If the ::cnrtNotifierElapsedTime API is called before the starting Notifier
 *   or ending Notifier is placed into the Queue, ::cnrtErrorCndrvFuncCall is
 *   returned.
 * @example
 * @code{.cpp}
    int main () {
      int ret;

      // Create notifier
      cnrtNotifier_t notifier_s;
      cnrtNotifier_t notifier_e;
      cnrtNotifier_t notifier_dis_tim;
      cnrtNotifierCreate(&notifier_s);
      cnrtNotifierCreate(&notifier_e);
      //we can not call cnrtNotifierElapsedTime if specify CNRT_NOTIFIER_DISABLE_TIMING.
      cnrtNotifierCreateWithFlags(&notifier_dis_tim, CNRT_NOTIFIER_DISABLE_TIMING);

      // Create queue
      cnrtQueue_t queue;
      cnrtQueueCreate(&queue);

      size_t size = 0x1000000;
      char *host_mem = (char *)malloc(size);
      void *dev_mem = NULL;
      cnrtMalloc(&dev_mem, size);

      // Place notifier into a queue
      cnrtPlaceNotifier(notifier_s, queue);
      // Push a task into queue between the two notifiers
      cnrtMemcpyAsync(dev_mem, host_mem, size, queue, cnrtMemcpyHostToDev);
      cnrtPlaceNotifier(notifier_e, queue);
      cnrtPlaceNotifier(notifier_dis_tim, queue);

      cnrtQueueSync(queue);

      // Query notifier
      cnrtQueryNotifier(notifier_s);
      cnrtQueryNotifier(notifier_e);
      cnrtQueryNotifier(notifier_dis_tim);

      // Wait for notifier
      cnrtWaitNotifier(notifier_s);
      cnrtWaitNotifier(notifier_e);
      cnrtWaitNotifier(notifier_dis_tim);

      // Compute the software duration
      float ms;
      cnrtNotifierElapsedTime(notifier_s, notifier_e, &ms);
      printf("software time consuming between the two notifier is %f\n", ms);

      cnrtNotifierDestroy(notifier_s);
      cnrtNotifierDestroy(notifier_e);
      cnrtNotifierDestroy(notifier_dis_tim);

      cnrtQueueDestroy(queue);
      cnrtFree(dev_mem);
      free(host_mem);

      return 0;
    }
 * @endcode
 */
cnrtRet_t cnrtNotifierElapsedTime(cnrtNotifier_t start, cnrtNotifier_t end,
                                  float *ms);
//Group: Notifier Management
/**
 * @brief Queries the status of all the preceding tasks before a Notifier in a Queue.
 * @details Queries the status of all the preceding tasks before the ``notifier`` in a Queue.
 *          Returns ::cnrtSuccess if all the preceding tasks before the ``notifier`` in
 *          the Queue are completed. Returns ::cnrtErrorBusy if the preceding tasks before
 *          the ``notifier`` are still executing.
 * @param[in] notifier The handle of the Notifier to query.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorBusy,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - When querying the status of all the preceding tasks before the Notifier, if calling the
 *   ::cnrtPlaceNotifier API again on the same Notifier, the query will be based on the
 *   most recent call by the ::cnrtPlaceNotifier API. So all the existing status recorded
 *   for the previous call will be overwritten.
 * @example
 * - See example in ::cnrtNotifierElapsedTime API.
 */
cnrtRet_t cnrtQueryNotifier(cnrtNotifier_t notifier);
//Group: Notifier Management
/**
 * @brief Places a Notifier into a specified Queue.
 * @details Places a ``notifier`` into a specified ``queue``. The Notifier can be
 *          used to measure the execution time of all the tasks.
 * @param[in] notifier The handle of the Notifier to be placed into the Queue.
 *                     Create the Notifier by calling the
 *                     ::cnrtNotifierCreate API.
 * @param[in] queue The Queue in which the Notifier is placed. Create
 *                  the Queue by calling ::cnrtQueueCreate.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - None.
 * @example
 * - See example in ::cnrtNotifierElapsedTime API.
 */
cnrtRet_t cnrtPlaceNotifier(cnrtNotifier_t notifier, cnrtQueue_t queue);
//Group: Notifier Management
/**
 * @brief Waits for a Notifier to be completed.
 * @details Waits for a ``notifier`` in the Queue to be completed before executing all
 *          future tasks in this Queue. The ``notifier`` is the most recent one called by
 *          the ::cnrtPlaceNotifier API in the Queue. Returns ::cnrtSuccess
 *          if the Notifier is completed.
 * @param[in] notifier The handle of the Notifier to be waited for.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - If ::cnrtPlaceNotifier has not been called on the Notifier before
 *   calling this API, cnrtSuccess is returned.
 * - This API is used for synchronization in a single Queue. To synchronize across
 *   Queues, use ::cnrtQueueWaitNotifier.
 * @example
 * - See example in ::cnrtNotifierElapsedTime.
 */
cnrtRet_t cnrtWaitNotifier(cnrtNotifier_t notifier);

/************************************************************************
 * Queue management
 ************************************************************************/
//Group: Queue Management
/**
 * @brief Creates a Queue.
 * @details Creates a Queue on the current Device, and returns a pointer
 * pQueue to the newly created Queue.
 * Define how the Queues are synchronized with ::cnrtSetDeviceFlag.
 * By default ::cnrtDeviceScheduleSpin is used. Call
 * ::cnrtGetDeviceFlag to query the current behavior.
 * - ::cnrtDeviceScheduleSpin CPU actively spins when waiting for the Device
 *   execution result. For this option, the latency may be lower, but it may
 *   decrease the performance of CPU threads if the tasks are executed in parallel
 *   with MLU. This value is used by default.
 * - ::cnrtDeviceScheduleBlock CPU thread is blocked on a synchronization
 *   primitive when waiting for the Device execution result.
 * - ::cnrtDeviceScheduleYield CPU thread yields when waiting for the Device
 *   execution results. For this option, the latency may be higher, but it can
 *   increase the performance of CPU threads if the tasks are executed in parallel
 *   with the Device.
 * @param[out] pQueue Pointer to the newly created Queue.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - Call ::cnrtQueueDestroy to release the Queue resources;
 *   otherwise, the memory leaks may occur.
 * - To learn more about Queue lifecycle management, please see
 *   "Cambricon Driver API Developer Guide".
 * @example
 * - See example in ::cnrtQueueSync.
 */
cnrtRet_t cnrtQueueCreate(cnrtQueue_t *pQueue);
//Group: Queue Management
/**
 * @brief Creates a Queue with the specified priority.
 * @details Creates a Queue on the current Device with the specified
 *          priority, and returns a pointer ``pQueue`` to the newly created Queue.
 *          Define how the Queues are synchronized with
 *          ::cnrtSetDeviceFlag, please see description in ::cnrtQueueCreate.
 * @param[out] pQueue Pointer to the newly created Queue.
 * @param[in] flags Flag used in this operation, which is reserved for further use.
 *            It is recommended to set this parameter to 0.
 * @param[in] priority Priority of the Queue. Lower numbers represent higher priorities.
 *            See ::cnrtDeviceGetQueuePriorityRange for more information about
 *            the meaningful Queue priorities that can be passed.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - ::cnrtDeviceGetQueuePriorityRange can be called to query the range of
 *   meaningful numerical priorities. If the specified priority is out of the
 *   legal range returned by ::cnrtDeviceGetQueuePriorityRange, it will automatically
 *   be clamped to the lowest or the highest number in the legal range.
 * - Call ::cnrtQueueDestroy to release the Queue resources;
 *   otherwise, the memory leaks may occur.
 * @example
 * @code{.cpp}
    int main () {
      void *dev_mem0 = NULL;
      void *dev_mem1 = NULL;
      cnrtMalloc(&dev_mem0, size);
      cnrtMalloc(&dev_mem1, size);

      int least_priority;
      int greatest_priority;

      cnrtDeviceGetQueuePriorityRange(&least_priority, &greatest_priority);

      // Create a queue
      cnrtQueue_t queue;
      cnrtQueueCreateWithPriority(&queue, 0, greatest_priority);

      // Allocate memory on device and host
      size_t size = 0x1000000;
      char *host_mem0 = NULL;
      char *host_mem1 = NULL;
      host_mem0 = (char *)malloc(size);
      host_mem1 = (char *)malloc(size);

      // Copy data asynchronously in two queues
      cnrtMemcpyAsync(dev_mem0, host_mem0, size, queue, cnrtMemcpyHostToDev);
      cnrtMemcpyAsync(host_mem1, dev_mem1, size, queue, cnrtMemcpyDevToHost);

      // Query the status of a queue.
      printf("before sync queue, %d\n", cnrtQueueQuery(queue));
      cnrtQueueSync(queue);
      printf("after sync queue, %d\n", cnrtQueueQuery(queue));

      // Release resources
      cnrtQueueDestroy(queue);

      cnrtFree(dev_mem0);
      cnrtFree(dev_mem1);

      free(host_mem0);
      free(host_mem1);

      return 0;
    }
 * @endcode
 */

cnrtRet_t cnrtQueueCreateWithPriority(cnrtQueue_t *pQueue, unsigned int flags,
                                      int priority);
//Group: Queue Management
/**
 * @brief Destroys a Queue.
 * @details Destroys a ``queue`` that is created by ::cnrtQueueCreate.
 *          If the Queue is still executing operations when ::cnrtQueueDestroy
 *          is called, this API will return immediately, but the resources associated with
 *          the Queue are released automatically after all the operations in the Queue are
 *          completed.
 * @param[in] queue The Queue to be destroyed.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - None.
 * @example
 * - See example in ::cnrtQueueSync.
 */
cnrtRet_t cnrtQueueDestroy(cnrtQueue_t queue);
//Group: Queue Management
/**
 * @brief Queries if a Queue is completed.
 * @details Returns the status of the ``queue``. If all the operations in the
 *          Queue are completed, ::cnrtSuccess is returned. If the operations in
 *          the Queue are still being executed, ::cnrtErrorBusy is returned.
 * @param[in] queue The Queue to query.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorBusy,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - If ``queue`` is set to NULL, the default Queue will be used.
 * @example
 * @code{.cpp}
    int main () {
      // Create a queue
      cnrtQueue_t queue;
      cnrtQueueCreate(&queue);

      // Allocate memory on device and host
      size_t size = 0x1000000;
      char *host_mem0 = NULL;
      char *host_mem1 = NULL;
      host_mem0 = (char *)malloc(size);
      host_mem1 = (char *)malloc(size);
      void *dev_mem0 = NULL;
      void *dev_mem1 = NULL;
      cnrtMalloc(&dev_mem0, size);
      cnrtMalloc(&dev_mem1, size);

      // Copy data asynchronously in two queues
      cnrtMemcpyAsync(dev_mem0, host_mem0, size, queue, cnrtMemcpyHostToDev);
      cnrtMemcpyAsync(host_mem1, dev_mem1, size, queue, cnrtMemcpyDevToHost);

      // Query the status of a queue.
      printf("before sync queue, %d\n", cnrtQueueQuery(queue));
      cnrtQueueSync(queue);
      printf("after sync queue, %d\n", cnrtQueueQuery(queue));

      // Release resources
      cnrtQueueDestroy(queue);

      cnrtFree(dev_mem0);
      cnrtFree(dev_mem1);

      free(host_mem0);
      free(host_mem1);

      return 0;
    }
 * @endcode
 */
cnrtRet_t cnrtQueueQuery(cnrtQueue_t queue);
//Group: Queue Management
/**
 * @brief Waits for Queue operations to be completed.
 * @details Blocks further executions in CPU thread until all the tasks
 *          in the Queue on the current MLU Device are completed.
 * @param[in] queue The Queue to be waited for.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - If ``queue`` is set to NULL, the default Queue will be used.
 * - This API may also return ::cnrtErrorQueue from previous and asynchronous
 *   operations.
 * @example
 * @code{.cpp}
    int main () {
      // Create a notifier
      cnrtNotifier_t notifier;
      cnrtNotifierCreate(&notifier);

      // Create a queue
      cnrtQueue_t queue_0;
      cnrtQueue_t queue_1;
      cnrtQueueCreate(&queue_0);
      cnrtQueueCreate(&queue_1);

      // Allocate memory on device and host
      size_t size = 0x100000;
      char *host_mem0 = NULL;
      char *host_mem1 = NULL;
      host_mem0 = (char *)malloc(size);
      host_mem1 = (char *)malloc(size);
      void *dev_mem0 = NULL;
      void *dev_mem1 = NULL;
      cnrtMalloc(&dev_mem0, size);
      cnrtMalloc(&dev_mem1, size);

      // Copy data asynchronously in two queues
      cnrtMemcpyAsync(dev_mem0, host_mem0, size, queue_0, cnrtMemcpyHostToDev);
      cnrtMemcpyAsync(host_mem1, dev_mem1, size, queue_1, cnrtMemcpyDevToHost);
      // Put a notifier into a queue
      cnrtPlaceNotifier(notifier, queue_0);

      // Synchronize two queues
      cnrtQueueWaitNotifier(notifier, queue_1, 0);

      // Wait until all tasks are completed
      cnrtQueueSync(queue_0);
      cnrtQueueSync(queue_1);

      // Release resources
      cnrtQueueDestroy(queue_0);
      cnrtQueueDestroy(queue_1);
      cnrtNotifierDestroy(notifier);

      cnrtFree(dev_mem0);
      cnrtFree(dev_mem1);
      free(host_mem0);
      free(host_mem1);

      return 0;
    }
 * @endcode
 */
cnrtRet_t cnrtQueueSync(cnrtQueue_t queue);
//Group: Queue Management
/**
 * @brief Waits for a Notifier to be completed before the specified Queue does
 *        any further executions.
 * @details Blocks all future tasks in the ``queue`` until the ``notifier`` is completed.
 *          The Queue only waits for the completion of the most recent host call of
 *          ::cnrtPlaceNotifier on the Notifier. This API is used to synchronize the
 *          Queue efficiently on the Device.
 * @param[in] notifier The Notifier to be waited for.
 * @param[in] queue The Queue to wait.
 * @param[in] flag Flag used in this operation, which is reserved for further use.
 *             It is recommended to set this parameter to 0.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - If ``queue``is set to NULL, the default Queue will be used.
 * - This API is used for synchronization across Queues. To synchronize in
 *   a single Queue, use ::cnrtWaitNotifier.
 * @example
 * - See example in ::cnrtQueueSync.
 */
cnrtRet_t cnrtQueueWaitNotifier(cnrtNotifier_t notifier, cnrtQueue_t queue,
                                unsigned int flag);

// Group: Queue Management
/**
 * @brief Sets the Queue attribute.
 *
 * @details Sets the attributes corresponding to ``attr_id`` for ``queue`` from corresponding
 *          attribute of ``value``.
 *
 * @param[in] queue    The Queue handle to be set.
 * @param[in] attr_id  Attribute ID.
 * @param[in] value    The attribute value to set.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorNotSupport,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorCndrvFuncCall
 *
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtQueueSetAttribute(cnrtQueue_t queue, cnrtQueueAttrID_t attr_id,
                                const cnrtQueueAttrValue_t *value);

// Group: Queue Management
/**
 * @brief Queries the Queue attribute.
 *
 * @details Queries the attributes corresponding to ``attr_id`` for ``queue``, and stores it in corresponding
 *          member of ``value``.
 *
 * @param[in] queue      The Queue handle to query.
 * @param[in] attr_id    Attribute ID.
 * @param[out] value_out The room to store the attribute value.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorNotSupport,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorCndrvFuncCall
 *
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtQueueGetAttribute(cnrtQueue_t queue, cnrtQueueAttrID_t attr_id,
                                cnrtQueueAttrValue_t *value_out);

// Group: Queue Management
/**
 * @brief Copies Queue attributes from source Queue to destination Queue.
 *
 * @details Copies attributes from source Queue ``src`` to destination Queue ``dst``.
 *
 * @param[in] dst   The destination Queue.
 * @param[in] src   The source Queue.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorCndrvFuncCall
 *
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtQueueCopyAttributes(cnrtQueue_t dst, cnrtQueue_t src);

// Group: Queue Management
/**
 * @brief Begins capture on a Queue.
 *
 * @details When the ``queue`` is capturing, all the tasks pushed to this Queue will not be executed
 *          but instead captured into a Task Topo.
 *          Call ::cnrtQueueIsCapturing() to query whether the Queue is capturing.
 *          Call ::cnrtQueueGetCaptureInfo() to query the unique ID representing the sequence number
 *          of the capturing and other information.
 *
 * @param[in] queue  The Queue to begin capture for.
 * @param[in] mode   The capture mode.
 *
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorIllegalState
 *
 * @note
 * - If ``mode`` is not ::cnrtQueueCaptureModeRelaxed, ::cnrtQueueEndCapture() must be called on this
 *   ``queue`` from the same thread.
 * - Pass to ``queue`` with NULL as a default Queue is not allowed to begin capturing.
 * - The capture must be ended on the same Queue as it is started.
 *
 *
 * @example
 * @code{.cpp}
   int main() {
     cnrtTaskTopo_t topo;
     cnrtTaskTopoEntity_t entity;
     uint64_t id; // the capture sequence unique id.
     const cnrtTaskTopoNode_t *dependencies;
     size_t numDependencies;
     cnrtQueue_t queue;
     cnrtQueueCaptureStatus_t status;
     cnrtTaskTopoNode_t node0, node1;
     cnrtTaskTopoNodeType_t type;

     cnrtRet_t ret = cnrtQueueCreate(&queue);
     if (ret != cnrtSuccess) return ret;

     ret = cnrtQueueBeginCapture(queue, cnrtQueueCaptureModeRelaxed);
     if (ret != cnrtSuccess) return ret;

     ret = cnrtQueueIsCapturing(queue, &status);
     if (ret != cnrtSuccess || status != cnrtQueueCaptureStatusActive) return ret;

     // Capture the kernel task.
     cnrtDim3_t dim = {1, 1, 1};
     kernel<<<dim, cnrtFuncTypeBlock, queue>>>();

     ret = cnrtQueueGetCaptureInfo(queue, &status, &id, &topo,
                                   &dependencies, &numDependencies);
     if (ret != cnrtSuccess) return ret;
     assert(numDependencies == 1);
     node0 = dependencies[0];
     ret = cnrtTaskTopoNodeGetType(dependencies[0], type);
     assert(ret == cnrtSuccess);
     assert(cnrtTaskTopoNodeTypeKernel == type);

     // Capture the host function task.
     cnrtInvokeHostFunc(queue, [](void *args) {//...}, nullptr);

     ret = cnrtQueueGetCaptureInfo(queue, &status, &id, &topo,
                                   &dependencies, &numDependencies);
     if (ret != cnrtSuccess) return ret;

     // Nodes in topo are {kernel_node -> host_node}
     node1 = dependencies[0];
     assert(status == cnrtQueueCaptureStatusActive);
     assert(numDependencies == 1);
     ret = cnrtTaskTopoNodeGetType(node1, &type);
     assert(ret == cnrtSuccess);
     assert(type == cnrtTaskTopoNodeTypeHost);

     cnrtTaskTopoNode_t updated_deps[2] = {node0, node1};
     ret = cnrtQueueUpdateCaptureDependencies(queue, updated_deps, 2,
                                              cnrtQueueSetCaptureDependencies);
     if (ret != cnrtSuccess) return ret;

     ret = cnrtQueueGetCaptureInfo(queue, &status, &id, &topo,
                                   &dependencies, &numDependencies);
     if (ret != cnrtSuccess) return ret;
     assert(numDependencies == 2);
     assert((dependencies[0] == node0 && dependencies[1] == node1) ||
            (dependencies[0] == node1 && dependencies[1] == node0));

     // Invoke more asynchronous tasks
     // ...

     ret = cnrtQueueEndCapture(queue, &topo);
     if (ret != cnrtSuccess) return ret;

     ret = cnrtTaskTopoInstantiate(&entity, topo, nullptr, nullptr, 0);
     if (ret != cnrtSuccess) return ret;

     // Invoke TaskTopo, real time to invoke tasks
     ret = cnrtTaskTopoEntityInvoke(entity, queue);
     if (ret != cnrtSuccess) return ret;

     // ...
   }
 * @endcode
 */
cnrtRet_t cnrtQueueBeginCapture(cnrtQueue_t queue,
                                enum cnrtQueueCaptureMode mode);

// Group: Queue Management
/**
 * @brief Ends a Queue capture, and returns the captured Task Topo.
 *
 * @details Ends a Queue capture sequence that is begun with ::cnrtQueueBeginCapture() and returns
 *          the captured Task Topo in ``pTaskTopo``.
 *          If the Queue is not in capture status, the API call returns ::cnrtErrorIllegalState.
 *
 * @param[in] queue The Queue in which to end capturing.
 * @param[out] pTaskTopo The captured Task Topo.
 *
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorIllegalState,
 * ::cnrtErrorQueueCaptureInvalidated
 *
 * @note
 * - If the Queue is not capturing under ::cnrtQueueCaptureModeRelaxed, ::cnrtQueueEndCapture()
 *   must be called on this ``queue`` from the same thread.
 * - If the capture is invalidated, then the NULL Task Topo will be returned.
 * - Capture must have been begun on ``queue`` via ::cnrtQueueBeginCapture().
 *
 *
 * @example
 * - See example in ::cnrtQueueBeginCapture().
 */
cnrtRet_t cnrtQueueEndCapture(cnrtQueue_t queue, cnrtTaskTopo_t *pTaskTopo);

// Group: Queue Management
/**
 * @brief Queries a Queue's capture status.
 *
 * @details Returns the ``queue`` capture status via ``pStatus``.
 *          If the ``queue`` is not in capture status, ::cnrtQueueCaptureStatusNone is returned.
 *          If the ``queue`` is in capture status but the capture sequence has been invalidated due to
 *          previous error, ::cnrtQueueCaptureStatusInvalidated is returned, and otherwise
 *          ::cnrtQueueCaptureStatusActive is returned.
 *
 * @param[in] queue    The Queue to query.
 * @param[out] pStatus Returns the capture status.
 *
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 *
 * @note
 * - None.
 *
 *
 * @example
 * - See example in ::cnrtQueueBeginCapture().
 */
cnrtRet_t cnrtQueueIsCapturing(cnrtQueue_t queue,
                               enum cnrtQueueCaptureStatus *pStatus);

// Group: Queue Management
/**
 * @brief Queries a Queue's capture information.
 *
 * @details Returns detailed information if the ``queue`` is in active capture status.
 *          The parameters ``idOut``, ``pTaskTopo``, ``pDependenciesOut``, ``pNumDependencies``
 *          are optional parameters, which can be NULL, and return nothing.
 *
 * @param[in] queue              The Queue to query.
 * @param[out] pStatus           Returns capture status.
 * @param[out] idOut             Returns the unique sequence number of current capturing.
 * @param[out] pTaskTopo         Returns current captured Task Topo.
 * @param[out] pDependenciesOut  Returns a pointer to store an array of dependency nodes.
 * @param[out] pNumDependencies  Returns the count of dependency nodes.
 *
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 *
 * @note
 * - None.
 *
 * @example
 * - See example in ::cnrtQueueBeginCapture().
 */
cnrtRet_t cnrtQueueGetCaptureInfo(cnrtQueue_t queue,
                                  enum cnrtQueueCaptureStatus *pStatus,
                                  uint64_t *idOut, cnrtTaskTopo_t *pTaskTopo,
                                  const cnrtTaskTopoNode_t **pDependenciesOut,
                                  size_t *pNumDependencies);

// Group: Queue Management
/**
 * @brief Updates the set of dependencies in a capturing Queue.
 *
 * @details Modifies the dependency set of capturing ``queue``. The dependency set is
 *          the set of nodes that the next captured node in the ``queue`` will depend on.
 *
 * @param[in] queue            The Queue in capture status.
 * @param[in] dependencies     The array of dependency nodes to modify the capturing sequence dependencies.
 * @param[in] numDependencies  The node count of the ``dependencies``.
 * @param[in] flags            Modification flag. Valid flags are ::cnrtQueueAddCaptureDependencies and
 *                             ::cnrtQueueSetCaptureDependencies.
 *
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorIllegalState,
 * ::cnrtErrorQueueCaptureInvalidated,
 * ::cnrtErrorSysNoMem
 *
 * @note
 * - None.
 *
 * @example
 * - See example in ::cnrtQueueBeginCapture().
 */
cnrtRet_t cnrtQueueUpdateCaptureDependencies(cnrtQueue_t queue,
                                             cnrtTaskTopoNode_t *dependencies,
                                             size_t numDependencies,
                                             unsigned int flags);

//Group: Notifier Management
/**
 * @brief Computes the hardware time duration between the starting and ending of Notifiers.
 *
 * @details Computes the hardware time duration between the starting Notifier ``start``
 *          and the ending Notifier ``end``. This API is used to measure the
 *          execution time of all the tasks between the starting Notifier and
 *          ending Notifier. The measurement that can be used to improve the performance.
 *
 * @param[in]  start The handle of the starting Notifier created by the
 *                   ::cnrtNotifierCreate API.
 * @param[in]  end   The handle of ending Notifier created by the ::cnrtNotifierCreate
 *                   API.
 * @param[out] us    The hardware time duration between the starting and ending of
 *                   Notifiers in microsecond.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorBusy,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - Call ::cnrtPlaceNotifier to place the starting and ending
 *   Notifiers into the Queue respectively first.
 *   Otherwise, ::cnrtErrorCndrvFuncCall is returned.
 * - If the ::cnrtNotifierDuration API is called before the starting Notifier
 *   or ending Notifier is placed into the Queue, ::cnrtErrorCndrvFuncCall is
 *   returned.
 *
 *
 * @example
 * @code{.cpp}
    int main () {
      // Create notifier
      cnrtNotifier_t notifier_s;
      cnrtNotifier_t notifier_e;
      cnrtNotifierCreate(&notifier_s);
      cnrtNotifierCreate(&notifier_e);

      // Create queue
      cnrtQueue_t queue;
      cnrtQueueCreate(&queue);

      size_t size = 0x1000000;
      char *host_mem = (char *)malloc(size);
      void *dev_mem = NULL;
      cnrtMalloc(&dev_mem, size);

      // Place notifier into a queue
      cnrtPlaceNotifier(notifier_s, queue);
      // Push a task into queue between the two notifiers
      cnrtMemcpyAsync(dev_mem, host_mem, size, queue, cnrtMemcpyHostToDev);
      cnrtPlaceNotifier(notifier_e, queue);

      cnrtQueueSync(queue);

      // Query notifier
      cnrtQueryNotifier(notifier_s);
      cnrtQueryNotifier(notifier_e);

      // Wait for notifier
      cnrtWaitNotifier(notifier_s);
      cnrtWaitNotifier(notifier_e);

      // Compute the hardware duration
      float us;
      cnrtNotifierDuration(notifier_s, notifier_e, &us);
      printf("hardware time consuming between the two notifier is %f\n", us);

      cnrtNotifierDestroy(notifier_s);
      cnrtNotifierDestroy(notifier_e);

      cnrtQueueDestroy(queue);
      cnrtFree(dev_mem);
      free(host_mem);

      return 0;
    }
 * @endcode
 *
 */
cnrtRet_t cnrtNotifierDuration(cnrtNotifier_t start, cnrtNotifier_t end,
                               float *us);

/************************************************************************
 * version management
 ************************************************************************/
//Group: Version Management
/**
 * @brief Retrieves the version of the current driver.
 * @details Returns the major version in ``major``, minor version in ``minor``,
 *          and patch version in ``patch`` of the current driver.
 * @param[out] major Pointer to the major of version.
 * @param[out] minor Pointer to the minor of version.
 * @param[out] patch Pointer to the patch of version.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - None.
 * @example
 * @code{.cpp}
    int main () {
      int major, minor, patch;
      cnrtDriverGetVersion(&major, &minor, &patch);
      printf("driver version is %d.%d.%d\n", major, minor, patch);

      return 0;
    }
 * @endcode
 */
cnrtRet_t cnrtDriverGetVersion(int *major, int *minor, int *patch);
//Group: Version Management
/**
 * @brief Retrieves the version of the current CNRT.
 * @details Returns the major version in ``major``, minor version in ``minor``,
 *          and patch version in ``patch`` of the current CNRT instance.
 * @param[out] major Pointer to the major of version.
 * @param[out] minor Pointer to the minor of version.
 * @param[out] patch Pointer to the patch of version.
 * @return
 * ::cnrtSuccess
 * @note
 * - None.

 * @example
 * @code{.cpp}
    int main () {
      int major, minor, patch;
      cnrtGetLibVersion(&major, &minor, &patch);
      printf("cnrt version is %d.%d.%d\n", major, minor, patch);

      return 0;
    }
 * @endcode
 */
cnrtRet_t cnrtGetLibVersion(int *major, int *minor, int *patch);

/************************************************************************
 * error management
 ************************************************************************/
//Group: Error Handling Management
/**
 * @brief Retrieves the error name of an error code.
 * @details Returns the string containing the name of an error code in the enum.
 * @param[in] error The error code to convert to string.
 * @return A pointer to string of the error code.
 * @note
 * - None.
 * @example
 * - See example in ::cnrtGetLastError API.
*/
const char *cnrtGetErrorName(cnrtRet_t error);
//Group: Error Handling Management
/**
 * @brief Retrieves the error message of an error code.
 * @details Returns the description string for an error code.
 * @param[in] error The error code to convert to string.
 * @return A pointer to string message according to the error code.
 * @note
 * - None.
 * @example
 * - See example in ::cnrtGetLastError API.
*/
const char *cnrtGetErrorStr(cnrtRet_t error);
//Group: Error Handling Management
/**
 * @brief Retrieves the last error from CNRT API call.
 * @details Returns the last error code returned from the CNRT API call in the
 *          same host thread.
 * @return
 * ::cnrtSuccess,
   ::cnrtErrorInit,
   ::cnrtErrorSetOnActiveProcess,
   ::cnrtErrorArgsInvalid,
   ::cnrtErrorNoMem,
   ::cnrtErrorNoDevice,
   ::cnrtErrorDevice,
   ::cnrtErrorSys,
   ::cnrtErrorNotReady,
   ::cnrtErrorNoAttribute,
   ::cnrtErrorNoKernel,
   ::cnrtErrorNoModule,
   ::cnrtErrorQueue,
   ::cnrtErrorMemcpyDirectionInvalid,
   ::cnrtErrorBusy,
   ::cnrtErrorCndrvFuncCall,
   ::cnrtErrorNotSupport,
   ::cnrtErrorCndevFuncCall,
   ::cnrtErrorDeviceInvalid,
   ::cnrtErrorNoCnrtContext,
   ::cnrtErrorCndrvFuncNotFound
 * @note
 * - Once ::cnrtGetLastError is called, the error code will be reset to ::cnrtSuccess.

 * @example
 * @code{.cpp}
    // __mlu_global__ function must be written in a single file named *.mlu
    __mlu_global__ void bangKernelAdd(int *a, int *b, unsigned int size) {
      for (int i = 0; i < size; i++) {
        b[i] += a[i];
      }
    }
    void hostAdd(int *x, int *y, unsigned int size,
                  cnrtDim3_t dim, cnrtFunctionType_t type, cnrtQueue_t queue) {
      bangKernelAdd<<<dim, type, queue>>>(x, y, size);
    }

    // Hybrid programming
    int main () {
      int a, b;
      uint32_t seed = 0x123;
      a = (int)rand_r(&seed) % 10000;
      b = (int)rand_r(&seed) % 10000;

      cnrtDim3_t dim;
      dim.x = 1;
      dim.y = 1;
      dim.z = 1;
      cnrtFunctionType_t type = cnrtFuncTypeBlock;

      // Ensure the origin host thread error code is cnrtSuccess.
      cnrtGetLastError();
      cnrtQueue_t queue;
      cnrtQueueCreate(&queue);

      int *k_a, *k_b;
      cnrtMalloc((void **)&k_a, sizeof(int));
      cnrtMalloc((void **)&k_b, sizeof(int));
      cnrtMemcpy(k_a, &a, sizeof(int), cnrtMemcpyHostToDev);
      cnrtMemcpy(k_b, &b, sizeof(int), cnrtMemcpyHostToDev);

      // Launch kernel
      hostAdd(k_a, k_b, 1, dim, type, queue);
      cnrtRet_t ret = cnrtPeekAtLastError();
      printf("cnrtGetErrorName: %s\n", cnrtGetErrorName(ret));
      printf("cnrtGetErrorStr: %s\n", cnrtGetErrorStr(cnrtGetLastError()));
      cnrtSyncDevice();

      // Free resource
      cnrtFree(k_a);
      cnrtFree(k_b);
      cnrtQueueDestroy(queue);

      return 0;
    }
 * @endcode
 */
cnrtRet_t cnrtGetLastError(void);
//Group: Error Handling Management
/**
 * @brief Retrieves the last error from the CNRT API call without resetting.
 * @details Returns the last error code returned from the CNRT API call.
 * @return
 * ::cnrtSuccess,
   ::cnrtErrorInit,
   ::cnrtErrorSetOnActiveProcess,
   ::cnrtErrorArgsInvalid,
   ::cnrtErrorNoMem,
   ::cnrtErrorNoDevice,
   ::cnrtErrorDevice,
   ::cnrtErrorSys,
   ::cnrtErrorNotReady,
   ::cnrtErrorNoAttribute,
   ::cnrtErrorNoKernel,
   ::cnrtErrorNoModule,
   ::cnrtErrorQueue,
   ::cnrtErrorMemcpyDirectionInvalid,
   ::cnrtErrorBusy,
   ::cnrtErrorCndrvFuncCall,
   ::cnrtErrorNotSupport,
   ::cnrtErrorCndevFuncCall,
   ::cnrtErrorDeviceInvalid,
   ::cnrtErrorNoCnrtContext,
   ::cnrtErrorCndrvFuncNotFound,
   ::cnrtErrorInvalidResourceHandle
 * @note
 * - The error code will not be reset to ::cnrtSuccess after calling ::cnrtPeekAtLastError.

 * @example
 * - See example in ::cnrtGetLastError.
*/
cnrtRet_t cnrtPeekAtLastError(void);

/************************************************************************
 * utility management
 ************************************************************************/
//Group: Utility Management
/**
 * @brief Creates and sets the quantization parameters used for casting data types.
 * @details Creates the quantization parameters ``pos``, ``scale``, and ``offset``, and sets the
 *          values to these parameters. Returns in ``param`` the quantization parameters used for casting
 *          data types. For more information about quantization, see "Cambricon BANG C/C++ Programming Guide".
 * @param[out] param Pointer to the quantization parameters defined in ::cnrtQuantizedParam_t.
 * @param[in]  pos The position factor used in quantization.
 * @param[in]  scale The scale factor used in quantization.
 * @param[in]  offset The offset factor used in quantization.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - After this API is called, the output pointer ``param`` is used in the ::cnrtCastDataType
 *   or cnrtTransOrderAndCast API to cast data type.
 * - The ::cnrtDestroyQuantizedParam API should be called to release the memory space when
 *   ``param`` is no longer needed.
 */
cnrtRet_t cnrtCreateQuantizedParam(cnrtQuantizedParam_t *param, int pos,
                                   float scale, int offset);
//Group: Utility Management
/**
 * @brief Creates and sets the quantization parameters used for casting data types. This API
 *        is used to quantize data by channel.
 * @details Creates quantization parameters ``poses``, ``scales`` and ``offsets``, and sets the
 *          values to these parameters. Returns in ``param`` the quantization parameters defined in
 *          ::cnrtQuantizedParam_t used for casting data type.
 *          This API is used to quantize filter data
 *          by channel. The data is divided into groups based on the number of elements of the channel
 *          dimension and quantized filter data for each group. The ::cnrtCreateQuantizedParam API
 *          quantizes data without division, and is usually for input or output data.
 *          Compared with the ::cnrtCreateQuantizedParam API, this API has a higher precision quantization.
 *          For more information about quantization, see "Cambricon BANG C/C++ Programming Guide".
 * @param[out] param Pointer to the quantization parameters defined in ::cnrtQuantizedParam_t.
 * @param[in]  poses The position factor used in quantization.
 * @param[in]  scales The scale factor used in quantization.
 * @param[in]  offsets The offset factor used in quantization.
 * @param[in]  dimNum The number of dimensions of the filter data to be quantized.
 * @param[in]  dimValues The number of elements for each dimension of the filter data to be quantized.
 * @param[in]  channelDim The dimension index of the channel in the filter data layout.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorSys
 * @note
 * - After this API is called, the output pointer ``param`` is used in the ::cnrtCastDataType
 *   or cnrtTransOrderAndCast API to cast data type.
 * - The ::cnrtDestroyQuantizedParam API should be called to release the memory space when
 *   ``param`` is no longer needed.
 * - This API is to set parameters for quantization by channel, so the number of ``scales``,
 *   ``poses``, ``offsets`` should be the same as that of channel elements.
 */
cnrtRet_t cnrtCreateQuantizedParamByChannel(cnrtQuantizedParam_t *param,
                                            int *poses, float *scales,
                                            float *offsets, int dimNum,
                                            int *dimValues, int channelDim);
//Group: Utility Management
/**
 * @brief Releases the memory resources of the quantization parameters.
 * @details Destroys the quantization parameters ``param`` and cleans up the parameter resources.
 * @param[in] param Pointer to the quantization parameters defined in ::cnrtQuantizedParam_t.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorSys
 * @note
 * - None.
 */
cnrtRet_t cnrtDestroyQuantizedParam(cnrtQuantizedParam_t param);
//Group: Utility Management
/**
 * @brief Converts the data into another data type.
 * @details Converts data pointed by ``src`` in ``srcDataType`` data type into the
 *          ``dstDataType`` data type with data quantization if the quantization parameter ``param`` is
 *          not set to NULL. Returns the converted data in ``dst``.
 * @param[out] dst Pointer to the converted output data.
 * @param[in] src Pointer to the input data to be converted.
 * @param[in] srcDataType The data type of the input data to be converted. The data type is
 *            defined in ::cnrtDataType_t.
 * @param[in]  dstDataType The data type of the data to be converted. The data type is defined
 *             in ::cnrtDataType_t.
 * @param[in] count The number of data to be converted.
 * @param[in] param Pointer to the quantization parameters defined in ::cnrtQuantizedParam_t.
 *            Create and set quantization parameters via the ::cnrtCreateQuantizedParam or
 *            ::cnrtCreateQuantizedParamByChannel API. To ignore quantizing data, set this
 *            parameter to NULL.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - If the input pointer ``param`` is set to NULL, the data will not be quantized.
 *   The supported combinations of the data types are as follows. The data types are shown in
 *   the following order:
 *    ``srcDataType``-``dstDataType``
 *   Supported combinations:
 *    float32-float16, float32-uint8, int64-float16, float16-float32, float16-uint8,
 *    uint8-float32, uint8-float16, float32-float32
 *    in int64-float16 case, int64 is first converted to float,and then the float data is converted.
 * - If the input pointer ``param`` is not set to NULL, the data will be quantized.
 *   The supported combinations of tensor data types are as follows. The data types are shown in the
 *   following order:
 *    ``srcDataType``-``dstDataType``
 *   Supported combinations:
 *    float32-float16, float32-int16, float32-int8, float32-int32, int32-float32,
 *    float16-int16, int16-float32, int8-float32, float32-float32
 */
cnrtRet_t cnrtCastDataType(void *src, cnrtDataType_t srcDataType, void *dst,
                           cnrtDataType_t dstDataType, int count,
                           cnrtQuantizedParam_t param);
//Group: Utility Management
/**
 * @brief Converts the input data into another data type in specified rounding mode.
 * @details Converts data pointed by ``src`` in ``srcDataType`` data type into the
 *          ``dstDataType`` data type with data quantization if the quantization parameter ``param`` is
 *          not set to NULL. Returns the converted data in ``dst``.
 * @param[out] dst Pointer to the converted output data.
 * @param[in] src Pointer to the input data to be converted.
 * @param[in] srcDataType The data type of the input data to be converted. The data type is
 *           defined in ::cnrtDataType_t.
 * @param[in]  dstDataType The data type of the data to be converted. The data type is defined
 *             in ::cnrtDataType_t.
 * @param[in] count The number of data to be converted.
 * @param[in] param Pointer to the quantization parameters defined in ::cnrtQuantizedParam_t.
 *            Create and set quantization parameters via the ::cnrtCreateQuantizedParam or
 *            ::cnrtCreateQuantizedParamByChannel API. To ignore quantizing data, set this
 *            parameter to NULL.
 * @param[in] roundingMode The rounding mode for data type conversion.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - If the input value ``count`` is zero, the API will return ``cnrtSuccess`` .
 * - If the input pointer ``param`` is set to NULL, the data will not be quantized.
 *   The supported combinations of the data types are as follows. The data types are shown in
 *   the following order:
 *    ``srcDataType``-``dstDataType``
 *   Supported combinations:
 *    double->half, double->bfloat,
 *    float->half, float->int64, float->uint32, float->int32, float->int16,
 *    float->uint8, float->int8, float->bool,
 *    bfloat->float, bfloat->uint64, bfloat->uint32, bfloat->uint16, bfloat->int64,
 *    bfloat->int32,
 *    half->float, half->int64, half->uint32, half->int32, half->int16,
 *    half->uint16, half->uint8, half->int8,
 *    uint64->half, uint64->bfloat,
 *    int64->half, int64->bfloat,
 *    uint32->half, uint32->bfloat,
 *    int32->half, int32->bfloat,
 *    uint16->half, uint16->bfloat,
 *    int16->half, int16->bfloat, int16->float,
 *    uint8->half, uint8->bfloat, uint8->float,
 *    int8->half, int8->bfloat, int8->float,
 * - If the input pointer ``param`` is not set to NULL, the data will be quantized.
 *   The supported combinations of tensor data types are as follows. The data types are shown in the
 *   following order:
 *    ``srcDataType``-``dstDataType``
 *   Supported combinations:
 *    float->half, float->int16, float->int8, float->int32, int32->float,
 *    half->int16, int16->float, int8->float
 */
cnrtRet_t cnrtCastDataType_V2(void *src, cnrtDataType_V2_t srcDataType,
                              void *dst, cnrtDataType_V2_t dstDataType,
                              int count, cnrtQuantizedParam_t param,
                              cnrtRoundingMode_t roundingMode);
//Group: Utility Management
/**
 * @brief Reshapes the input filter data.
 * @details Reshapes the filter data from source memory address pointed
 *          by ``dst`` to destination memory address pointed by ``src`` with the
 *          source data shape src[NHWC] and data type ``type`` that is specified
 *          in ``cnrtDataType_t`` enum.
 * @param[out] dst The destination address.
 * @param[in]  src The source address.
 * @param[in]  n The batch size.
 * @param[in]  h The height.
 * @param[in]  w The width.
 * @param[in]  c The channel.
 * @param[in]  type The data type of the source and destination data.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * @note
 * - None.
 * @example
 * - None.
 */
extern cnrtRet_t cnrtFilterReshape(void *dst, void *src, int n, int h, int w,
                                   int c, cnrtDataType_t type);
//Group: Memory Management
/**
 * @brief Flushes or invalidates cache on the host.
 * @details This API ensures cache consistency if the ``hostPtr`` is cached.
 *          Specify the operation on cache with ::cnrtCacheOps_t enum ``ops``.
 *          Currently, only the flush operation is supported.
 * @param[in] ptr Reserved for checking the Device address legality.
 * @param[in] hostPtr Host memory address to do cache operation..
 * @param[in] size The number of bytes to do cache operation.
 * @param[in] ops The operation type on cache.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - This API first makes ``hostPtr`` be aligned to cache line, the ``size`` may
 *   change to be aligned to cache line. The cache line now is 64-byte in driver.
 * @example
 * - See example in ::cnrtMmapCached.
 */
cnrtRet_t cnrtMcacheOperation(void *ptr, void *hostPtr, size_t size,
                              cnrtCacheOps_t ops);
//Group: Memory Management
/**
 * @brief Maps the range of Device memory into the user-mode uncached virtual address.
 * @details Maps memory address of the Device address pointer "ptr" into the
 *          user-mode address, and returns the uncached host memory address pointer "pHostPtr".
 * @param[in] ptr Device address to map.
 * @param[out] pHostPtr Pointer to the host memory address to be mapped into.
 * @param[in] size The size of the memory in bytes to be mapped into.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - The output parameter ``pHostPtr`` is a pointer to uncached host address, it is not necessary to
 *   ensure cache consistency, but this may impact performance.
 * @example
 * @code{.cpp}
    int main () {
      void *addr = NULL;
      void *host = NULL;
      size_t size = 0x100000;

      cnrtMalloc(&addr, size);
      cnrtMmap(addr, &host, size);

      memset(host, 'a', size);

      void *host1 = NULL;
      cnrtMmap(addr, &host1, size);
      memset(host1, 'b', size);

      void *cmp = malloc(size);
      cnrtMemcpy(cmp, addr, size, cnrtMemcpyNoDirection);

      if (memcmp(cmp, host1, size)) printf("memcmp failed!\n");

      free(cmp);
      cnrtMunmap(host1, size);
      cnrtFree(addr);

      return 0;
    }
 * @endcode
 */
cnrtRet_t cnrtMmap(void *ptr, void **pHostPtr, size_t size);
//Group: Memory Management
/**
 * @brief Maps the range of Device memory address into the cached host address space.
 * @details Maps memory address of the Device address pointer "ptr" into the
 *          host memory space, and returns the cached host address pointer "pHostPtr".
 * @param[in] ptr Device address to map.
 * @param[out] pHostPtr Pointer to the host address to be mapped into.
 * @param[in] size The size of the memory in bytes to be mapped into.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - The output parameter ``pHostPtr`` is a pointer to cached host address, so
 *   a cache flush operation is required  to ensure cache consistency.
 * @example
 * @code{.cpp}
    int main () {
      void *addr = NULL;
      void *host = NULL;
      size_t size = 0x100000;

      cnrtMalloc(&addr, size);
      cnrtMmapCached(addr, &host, size);
      memset(host, 'a', size);
      cnrtMcacheOperation(addr, host, size, CNRT_FLUSH_CACHE);

      void *host1 = NULL;
      cnrtMmapCached(addr, &host1, size);
      memset(host1, 'b', size);
      cnrtMcacheOperation(addr, host, size, CNRT_FLUSH_CACHE);

      void *cmp = malloc(size);
      cnrtMemcpy(cmp, addr, size, cnrtMemcpyNoDirection);

      if (memcmp(cmp, host1, size)) printf("memcmp failed!\n");

      free(cmp);
      cnrtMunmap(host1, size);
      cnrtFree(addr);

      return 0;
    }
 * @endcode
 */
cnrtRet_t cnrtMmapCached(void *ptr, void **pHostPtr, size_t size);
//Group: Memory Management
/**
 * @brief Unmaps the host address.
 * @details Unmaps the mapped host address and Device memory address.
 *          The mapping is created by ::cnrtMmap or ::cnrtMmapCached.
 * @param[in] hostPtr Host address to be unmapped.
 * @param[in] size The size of the host address to be unmapped.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorNoCnrtContext,
 * ::cnrtErrorCndrvFuncCall
 * @note
 * - None.
 * @example
 * - See example in ::cnrtMmapCached.
 */
cnrtRet_t cnrtMunmap(void *hostPtr, size_t size);
//Group: Task Topo Management
/**
 * @brief Creates a Task Topo.
 * @details Creates a new Task Topo, and returns a pointer ``pTaskTopo``
 *          to the newly created Task Topo.
 * @param[out] pTaskTopo Pointer to the newly created Task Topo.
 * @param[in]  flags Task Topo creation flags, which must be 0.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorSysNoMem
 * @note
 * - None.
 * @example
 * @code{.cpp}
    int main () {
      cnrtTaskTopo_t topo;
      cnrtRet_t res = cnrtTaskTopoCreate(&topo, 0);
      assert(res = cnrtSuccess);
    }
 * @endcode
 */
cnrtRet_t cnrtTaskTopoCreate(cnrtTaskTopo_t *pTaskTopo, unsigned int flags);
//Group: Task Topo Management
/**
 * @brief Destroys a Task Topo.
 * @details Destroys the Task Topo specified by ``taskTopo`` and cleans up
 *          all of its nodes.
 * @param[in]  taskTopo The Task Topo to be destroyed.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoDestroy(cnrtTaskTopo_t taskTopo);
//Group: Task Topo Management
/**
 * @brief Clones a Task Topo.
 * @details Creates a copy of ``originalTaskTopo`` and returns it in ``pTaskTopo``.
 *          All parameters are copied into the cloned Task Topo.
 * @param[out] pTaskTopoClone Pointer to the newly created cloned Task Topo.
 * @param[in]  originalTaskTopo The Task Topo to clone.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorSysNoMem
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoClone(cnrtTaskTopo_t *pTaskTopoClone,
                            cnrtTaskTopo_t originalTaskTopo);
//Group: Task Topo Management
/**
 * @brief Finds the corresponding node in cloned Task Topo.
 * @details Returns the node in ``clonedTaskTopo`` corresponding to ``originalNode``
 *          in the original Task Topo.
 * @param[out] pNode Pointer to the cloned node.
 * @param[in]  originalNode The original node.
 * @param[in]  clonedTaskTopo The cloned Task Topo to query.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoNodeFindInClone(cnrtTaskTopoNode_t *pNode,
                                      cnrtTaskTopoNode_t originalNode,
                                      cnrtTaskTopo_t clonedTaskTopo);
//Group: Task Topo Management
/**
 * @brief Removes a node from the Task Topo.
 * @details Removes ``node`` from its Task Topo. This operation also severs
 *          dependencies of other nodes on ``node`` and vice versa.
 * @param[in] node Node to be removed.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoDestroyNode(cnrtTaskTopoNode_t node);
//Group: Task Topo Management
/**
 * @brief Returns dependency edges of a Task Topo.
 * @details Returns a list of dependency edges of the Task Topo. Edges are
 *          returned via corresponding indices in ``from`` and ``to``,
 *          the node in ``to[i]`` has a dependency on the node in ``from[i]``.
 *          ``from`` and ``to`` may both be NULL, in which case this API only
 *          returns the number of edges in ``numEdges``, otherwise, ``numEdges``
 *          entries will be filled in. If ``numEdges`` is higher than the actual
 *          number of edges, the remaining entries in ``from`` and ``to`` will
 *          be set to NULL, and the number of edges actually returned will be
 *          written to ``numEdges``.
 * @param[in]  taskTopo Task Topo to get the edges from.
 * @param[out] from Location to return the edge of a source node.
 * @param[out] to Location to return the edge of a destination node.
 * @param[in,out] numEdges See the description above for details.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - ``from`` and ``to`` must be both NULL or neither NULL, otherwise
 *   ::cnrtErrorArgsInvalid will be returned.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoGetEdges(cnrtTaskTopo_t taskTopo,
                               cnrtTaskTopoNode_t *from, cnrtTaskTopoNode_t *to,
                               size_t *numEdges);
//Group: Task Topo Management
/**
 * @brief Returns nodes of a Task Topo.
 * @details Returns a list of nodes of a Task Topo. ``pNode`` may be NULL, in
 *          which case this API will return the number of nodes in ``numNodes``.
 *          Otherwise, ``numNodes`` entries will be filled in. If ``numNodes``
 *          is higher than the actual number of nodes, the remaining entries in
 *          ``pNode`` will be set to NULL, and the number of nodes actually
 *          obtained will be returned in ``numNodes``.
 * @param[in]  taskTopo Task Topo to query.
 * @param[out] pNode The array to store the returned nodes.
 * @param[in,out] numNodes See the description above for details.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoGetNodes(cnrtTaskTopo_t taskTopo,
                               cnrtTaskTopoNode_t *pNode, size_t *numNodes);
//Group: Task Topo Management
/**
 * @brief Returns root nodes of a Task Topo.
 * @details Returns a list of root nodes of a Task Topo. ``pRootNode`` may be
 *          NULL, in which case this API will return the number of nodes in
 *          ``numRootNodes``. Otherwise, ``numRootNodes`` entries will be filled
 *          in. If ``numRootNodes`` is higher than the actual number of nodes,
 *          the remaining entries in ``pRootNode`` will be set to NULL, and the
 *          number of nodes actually obtained will be returned in ``pRootNode``.
 * @param[in]  taskTopo Task Topo to query.
 * @param[out] pRootNode The array to store the returned root nodes.
 * @param[in,out] numRootNodes See the description above for details.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoGetRootNodes(cnrtTaskTopo_t taskTopo,
                                   cnrtTaskTopoNode_t *pRootNode,
                                   size_t *numRootNodes);
//Group: Task Topo Management
/**
 * @brief Adds dependency edges to a Task Topo.
 * @details The number of dependencies to be added is defined by ``numDependencies``.
 *          Elements in ``from`` and ``to`` at corresponding indices define a dependency.
 *          Each node in ``from`` and ``to`` must belong to ``taskTopo``
 * @param[in] taskTopo The Task Topo to add dependency edges to.
 * @param[in] from Array of nodes that provide the dependencies.
 * @param[in] to Array of dependent nodes.
 * @param[in] numDependencies The number of dependencies to be added.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoAddDependencies(cnrtTaskTopo_t taskTopo,
                                      const cnrtTaskTopoNode_t *from,
                                      const cnrtTaskTopoNode_t *to,
                                      size_t numDependencies);
//Group: Task Topo Management
/**
 * @brief Removes dependency edges from a Task Topo.
 * @details The number of dependencies to be removed is defined by ``numDependencies``.
 *          Elements in ``from`` and ``to`` at corresponding indices define a dependency.
 *          Each node in ``from`` and ``to`` must belong to ``taskTopo``
 * @param[in] taskTopo The Task Topo to remove dependency edges from.
 * @param[in] from Array of nodes that provide the dependencies.
 * @param[in] to Array of dependent nodes.
 * @param[in] numDependencies The number of dependencies to be removed.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoRemoveDependencies(cnrtTaskTopo_t taskTopo,
                                         const cnrtTaskTopoNode_t *from,
                                         const cnrtTaskTopoNode_t *to,
                                         size_t numDependencies);
//Group: Task Topo Management
/**
 * @brief Returns a node's dependencies.
 * @details Returns a list of dependencies of ``node``. ``pDependencies`` may be
 *          NULL, in which case this API will return the number of dependencies in
 *          ``numDependencies``. Otherwise, ``numDependencies`` entries will be
 *          filled in. If ``numDependencies`` is higher than the actual number of
 *          dependencies, the remaining entries in ``pDependencies`` will be set
 *          to NULL, and the number of nodes actually obtained will be returned
 *          in ``numDependencies``.
 * @param[in]     node The node to query.
 * @param[out]    pDependencies The array to store returned dependency of a node.
 * @param[in,out] numDependencies See the description above for details.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoNodeGetDependencies(cnrtTaskTopoNode_t node,
                                          cnrtTaskTopoNode_t *pDependencies,
                                          size_t *numDependencies);
//Group: Task Topo Management
/**
 * @brief Returns a node's dependent nodes.
 * @details Returns a list of dependent nodes of ``node``. ``pDependentNodes`` may be
 *          NULL, in which case this API will return the number of dependent nodes in
 *          ``numDependentNodes``. Otherwise, ``numDependentNodes`` entries will be
 *          filled in. If ``numDependentNodes`` is higher than the actual number of
 *          dependent nodes, the remaining entries in ``pDependentNodes`` will be set
 *          to NULL, and the number of nodes actually obtained will be returned
 *          in ``pDependentNodes``.
 * @param[in]     node The node to query.
 * @param[out]    pDependentNodes The array to store returned dependent nodes of a node.
 * @param[in,out] numDependentNodes See the description above for details.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoNodeGetDependentNodes(cnrtTaskTopoNode_t node,
                                            cnrtTaskTopoNode_t *pDependentNodes,
                                            size_t *numDependentNodes);

/*! @brief
 *
 *  A pointer to the ::cnrtUserObject_t struct holding the information about a
 *  user object.
 *
 */
typedef struct CNuserObject_st *cnrtUserObject_t;
//Group: Task Topo Management
/**
 * @brief Creates a user object.
 * @details Creates a user object with the specified destructor callback and
 *          initial reference count. The initial references are owned by the caller.
 *          Destructor callbacks cannot make CNRT or CNDrv API calls and should
 *          avoid blocking behavior.
 * @param[out] object_out Location to return the user object handle.
 * @param[in]  ptr The pointer to pass the destroy function.
 * @param[in]  destroy Callback to free the user object when it is no longer in use.
 * @param[in]  initialRefcount The initial reference count to create the object with, which is typically 1.
 * @param[in]  flags Currently it is required to pass 1. This indicates that the
 *             destroy callback cannot be waited on by any CNRT or driver API.
 *             Users requiring synchronization of the callback should signal its
 *             completion manually.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorSysNoMem
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtUserObjectCreate(cnrtUserObject_t *object_out, void *ptr,
                               cnrtHostFn_t destroy,
                               unsigned int initialRefcount,
                               unsigned int flags);
//Group: Task Topo Management
/**
 * @brief Acquires a reference for a user object.
 * @details Acquires new references for a user object. The new references are
 *          owned by the caller.
 * @param[in]  object The user object to acquire a reference for.
 * @param[in]  count The number of reference to acquire, which is typically 1.
 *             The value must be nonzero and not larger than ``INT_MAX``.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorSysNoMem
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtUserObjectAcquire(cnrtUserObject_t object, unsigned int count);

//Group: Task Topo Management
/**
 * @brief Releases a reference for a user object.
 * @details Releases user object references owned by the caller. The user object's
 *          destructor is invoked if the reference count reaches zero. It is undefined
 *          behavior to release references not owned by the caller, or to use object
 *          handle after all references are released.
 * @param[in]  object The user object to release a reference for.
 * @param[in]  count The number of reference to release, which is typically 1.
 *             The value must be nonzero and not larger than ``INT_MAX``.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorSysNoMem
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtUserObjectRelease(cnrtUserObject_t object, unsigned int count);
/**
 * @brief Flags for acquiring user object references for Task Topo.
 */
typedef enum cnrtUserObjectAcquireflags {
  cnrtTaskTopoUserObjectMove = 0x1,
  /*!< Transfers references from the caller rather than creating new references. */
} cnrtUserObjectAcquireflags_t;
//Group: Task Topo Management
/**
 * @brief Acquires a reference for a user object from a Task Topo.
 * @details Creates or moves user object references that will be owned by a Task Topo.
 * @param[in] taskTopo  The Task Topo to associate the reference with.
 * @param[in] object The user object to acquire a reference for.
 * @param[in] count  The number of references to add to the Task Topo, which is typically 1.
 *                 The value must be nonzero and not larger than ``INT_MAX``.
 * @param[in] flags  The optional flag ::cnrtTaskTopoUserObjectMove transfers references
 *                   from the caller, rather than creating new references,
 *                   which are created by passing 0.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorSysNoMem
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoAcquireUserObject(cnrtTaskTopo_t taskTopo,
                                        cnrtUserObject_t object,
                                        unsigned int count, unsigned int flags);
//Group: Task Topo Management
/**
 * @brief Releases a reference for a user object from a Task Topo.
 * @details Releases user object references owned by a Task Topo.
 * @param[in] taskTopo The Task Topo that will release the reference.
 * @param[in] object The user object to release a reference for.
 * @param[in] count The number of references to release, which is typically 1.
 *            The value must be nonzero and not larger than ``INT_MAX``.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorSysNoMem
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoReleaseUserObject(cnrtTaskTopo_t taskTopo,
                                        cnrtUserObject_t object,
                                        unsigned int count);
// Group: Task Topo Management
/**
 * @brief Creates an empty node and adds it to a Task Topo.
 * @details Creates a new node which performs no operation, and adds it to ``taskTopo`` with
 *          ``numDependencies`` dependencies specified via ``dependencies``. A handle to the
 *          new node will be returned in ``pNode``. ``numDependencies`` can be 0, in which
 *          case the node will be placed at the root of the Task Topo. ``dependencies`` may
 *          not have any duplicate entries.
 *
 *          An empty node performs no operation during the execution, but it can be transitive
 *          ordering. For example, for a phased execution Task Topo with 2 groups of nodes, one
 *          group has m nodes, and the other has n nodes,  m+n dependency edges are needed with
 *          an empty node, while m*n dependency edges are needed without an empty node.
 * @param[out] pNode The value of the granularity returned.
 * @param[in]  taskTopo The properties determine the granularity.
 * @param[in]  dependencies The option to determine the granularity returned.
 * @param[in]  numDependencies The number of dependencies.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorSysNoMem
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoAddEmptyNode(cnrtTaskTopoNode_t *pNode,
                                   cnrtTaskTopo_t taskTopo,
                                   const cnrtTaskTopoNode_t *dependencies,
                                   size_t numDependencies);
/**
 * @brief Host node parameters.
 */
typedef struct cnrtHostNodeParams_st {
  cnrtHostFn_t fn; /*!< The function to call when the node is being executed. */
  void *userData;  /*!< The argument to be passed to the function. */
} cnrtHostNodeParams_t;

// Group: Task Topo Management
/**
 * @brief Creates a host execution node and adds it to a Task Topo.
 * @details Creates a new host function node and adds it to ``taskTopo`` with
 *          ``numDependencies`` dependencies specified via ``dependencies``
 *          and arguments specified in ``nodeParams``. ``numDependencies`` can
 *          be 0, in which case the node will be placed at the root of the Task Topo.
 *          ``dependencies`` may not have any duplicate entries. A handle to the new
 *          node will be returned in ``pNode``. When the Task Topo is invoked, the
 *          node will invoke the specified CPU function.
 * @param[out] pNode Returns newly created node.
 * @param[in] taskTopo The Task Topo to add the node to.
 * @param[in] dependencies Dependencies of the node.
 * @param[in] numDependencies The number of dependencies.
 * @param[in] nodeParams Parameters for the host node.
 *
 * @returns
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorSysNoMem
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoAddHostNode(cnrtTaskTopoNode_t *pNode,
                                  cnrtTaskTopo_t taskTopo,
                                  const cnrtTaskTopoNode_t *dependencies,
                                  size_t numDependencies,
                                  const cnrtHostNodeParams_t *nodeParams);
// Group: Task Topo Management
/**
 * @brief Returns the parameters of a host node.
 * @param[in]  node Node to get the parameters for.
 * @param[out] nodeParams Pointer to return the parameters.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoHostNodeGetParams(cnrtTaskTopoNode_t node,
                                        cnrtHostNodeParams_t *nodeParams);

// Group: Task Topo Management
/**
 * @brief Sets the parameters of a host node.
 * @details Sets the parameters of host node ``node`` to ``nodeParams``.
 * @param[in] node Node to set the parameters for.
 * @param[in] nodeParams Parameters to copy.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoHostNodeSetParams(cnrtTaskTopoNode_t node,
                                        const cnrtHostNodeParams_t *nodeParams);
/**
 * @brief Kernel node parameters.
 */
typedef struct cnrtKernelNodeParams_st {
  void *func;
  /*!< The kernel to invoke. */
  cnrtDim3_t dim;
  /*!< The grid dimensions. */
  cnrtFunctionType_t type;
  /*!< The union type of kernel. */
  unsigned int reserve;
  /*!< Reverse parameter. */
  void **kernelParams;
  /*!< The array of pointers to kernel parameters. */
  void **extra;
  /*!< Extra options, such as packaged parameters. */
} cnrtKernelNodeParams_t;
// Group: Task Topo Management
/**
 * @brief Creates a kernel execution node and adds it to a Task Topo.
 * @details Creates a new kernel execution node and adds it to ``taskTopo`` with
 *          ``numDependencies`` dependencies specified via ``dependencies`` and
 *          arguments specified in ``nodeParams``. ``numDependencies`` can be 0,
 *          in which case the node will be placed at the root of the Task Topo.
 *          ``dependencies`` may not have any duplicate entries. A handle to the
 *          new node will be returned in ``pNode``.
 * @param[out] pNode Returns newly created node.
 * @param[in] taskTopo The Task Topo to add the node to.
 * @param[in] dependencies Dependencies of the node.
 * @param[in] numDependencies The number of dependencies.
 * @param[in] nodeParams Parameters for kernel node.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorSysNoMem
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoAddKernelNode(cnrtTaskTopoNode_t *pNode,
                                    cnrtTaskTopo_t taskTopo,
                                    const cnrtTaskTopoNode_t *dependencies,
                                    size_t numDependencies,
                                    const cnrtKernelNodeParams_t *nodeParams);
// Group: Task Topo Management
/**
 * @brief Returns the parameters of a kernel node.
 * @details Returns the parameters of kernel node ``node`` in ``nodeParams``.
 *          The ``extra`` array returned in ``nodeParams``, as well as the
 *          argument values it points to, are owned by the node.
 *
 *          This memory remains valid until the node is destroyed or its parameters
 *          are modified, and should not be modified directly. Use ::cnrtTaskTopoKernelNodeSetParams
 *          to update the parameters of this node.
 * @param[in] node Node to get the parameters for.
 * @param[out] nodeParams Pointer to return the parameters.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoKernelNodeGetParams(cnrtTaskTopoNode_t node,
                                          cnrtKernelNodeParams_t *nodeParams);

// Group: Task Topo Management
/**
 * @brief Sets the parameters of a kernel node.
 * @details Sets the parameters of kernel node ``node`` to ``nodeParams``.
 * @param[in] node Node to set the parameters for.
 * @param[in] nodeParams Parameters to copy.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorSysNoMem
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoKernelNodeSetParams(
    cnrtTaskTopoNode_t node, const cnrtKernelNodeParams_t *nodeParams);

// Group: Task Topo Management
/**
 * @brief Creates a memcpy node and adds it to a Task Topo
 * @details Creates a new memcpy node and adds it to ``taskTopo`` with ``numDependencies``
 *          dependencies specified via ``dependencies``. ``numDependencies`` can be 0,
 *          in which case the node will be placed at the root of the Task Topo.
 *          ``dependencies`` may not have any duplicate entries. A handle to the new
 *          node will be returned in ``pNode``.
 *
 *          When the Task Topo is invoked, the node will perform the memcpy described
 *          by ``copyParams``.
 *
 *          See ::cnrtMemcpy3D() for the description of the structure and its restrictions.
 *
 *          Currently, memcpy node only supports 1D memcpy, and does not support host to host memory copy.
 *          Here is the restriction of ``copyParams`` on setting 1D memcpy node:
 * @code
 *   #define N copy_size
 *
 *   cnrtMemcpy3dParam_t memcpy_param = {0};
 *
 *   memcpy_param.dstPtr.pitch = N;
 *   memcpy_param.dstPtr.ysize = 0x1;
 *
 *   memcpy_param.extent.depth = 0x1;
 *   memcpy_param.extent.height = 0x1;
 *   memcpy_param.extent.width = N;
 *
 *   memcpy_param.srcPtr.pitch = N;
 *   memcpy_param.srcPtr.ysize = 0x1;
 *
 *   memcpy_param.src = src_addr;
 *   memcpy_param.dst = dst_addr;
 * @endcode
 * Ignores other params when setting 1D memcpy node.
 *
 * @param[out] pNode Returns newly created node.
 * @param[in] taskTopo The Task Topo to add the node to.
 * @param[in] dependencies Dependencies of the node.
 * @param[in] numDependencies The number of dependencies.
 * @param[in] copyParams Parameters for the memory copy.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorSysNoMem
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoAddMemcpyNode(cnrtTaskTopoNode_t *pNode,
                                    cnrtTaskTopo_t taskTopo,
                                    const cnrtTaskTopoNode_t *dependencies,
                                    size_t numDependencies,
                                    const cnrtMemcpy3dParam_t *copyParams);

// Group: Task Topo Management
/**
 * @brief Returns the parameters of a memcpy node.
 * @details Returns the parameters of memcpy node ``node`` in ``nodeParams``.
 * @param[in] node Node to get the parameters for.
 * @param[out] nodeParams Pointer to return the parameters.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoMemcpyNodeGetParams(cnrtTaskTopoNode_t node,
                                          cnrtMemcpy3dParam_t *nodeParams);

// Group: Task Topo Management
/**
 * @brief Sets the parameters of a memcpy node.
 * @details Sets the parameters of memcpy node ``node`` to ``nodeParams``.
 * The restrictions of ``nodeParams`` are the same as ::cnrtTaskTopoAddMemcpyNode().
 * @param[in] node Node to set the parameters for.
 * @param[in] nodeParams Parameters to copy.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoMemcpyNodeSetParams(
    cnrtTaskTopoNode_t node, const cnrtMemcpy3dParam_t *nodeParams);
/**
 * @brief Memset node parameters.
 */
typedef struct cnrtMemsetParams {
  void *dst;
  /*!< Destination device pointer. */
  size_t pitch;
  /*!< Pitch of destination device pointer, which will be ignored if the height is 1. */
  unsigned int value;
  /*!< Value to be set. */
  unsigned int elementSize;
  /*!< The size of each element in bytes, which must be 1, 2, or 4. */
  size_t width;
  /*!< Width of the row in elements. */
  size_t height;
  /*!< Number of rows. */
} cnrtMemsetParams_t;
// Group: Task Topo Management
/**
 * @brief Creates a memset node and adds it to a Task Topo.
 * @details Creates a new memset node and adds it to ``pNode`` with ``numDependencies``
 *          dependencies specified via ``dependencies``. ``numDependencies`` can be 0,
 *          in which case the node will be placed at the root of the Task Topo.
 *          ``dependencies`` may not have any duplicate entries.  A handle to the new
 *          node will be returned in ``pNode``.
 *
 *          The element size must be 1, 2, or 4 bytes. When the Task Topo is invoked,
 *          the node will perform the memset described by ``copyParams``.
 *
 *          Currently, memset node only supports 1D memset. Sets ``height`` 1 to represent 1D memset.
 * @param[out] pNode Returns newly created node.
 * @param[in] taskTopo The Task Topo to add the node to.
 * @param[in] dependencies Dependencies of the node.
 * @param[in] numDependencies The number of dependencies.
 * @param[in] copyParams Parameters for the memory set.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorSysNoMem
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoAddMemsetNode(cnrtTaskTopoNode_t *pNode,
                                    cnrtTaskTopo_t taskTopo,
                                    const cnrtTaskTopoNode_t *dependencies,
                                    size_t numDependencies,
                                    const cnrtMemsetParams_t *copyParams);

// Group: Task Topo Management
/**
 * @brief Returns the parameters of a memset node.
 * @details Returns the parameters of memset node ``node`` in ``nodeParams``.
 * @param[in] node Node to get the parameters for.
 * @param[out] nodeParams Pointer to return the parameters.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoMemsetNodeGetParams(cnrtTaskTopoNode_t node,
                                          cnrtMemsetParams_t *nodeParams);

// Group: Task Topo Management
/**
 * @brief Sets the parameters of a memset node.
 * @details Sets the parameters of memset node ``node`` to ``nodeParams``.
 * @param[in] node Node to set the parameters for.
 * @param[in] nodeParams Parameters to copy.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoMemsetNodeSetParams(cnrtTaskTopoNode_t node,
                                          const cnrtMemsetParams_t *nodeParams);

// Group: Task Topo Management
/**
 * @brief Creates a child Task Topo node and adds it to a Task Topo.
 * @details Creates a new node which executes an embedded Task Topo, and adds it
 *          to ``taskTopo`` with ``numDependencies`` dependencies specified via
 *          ``dependencies``. ``numDependencies`` can be 0, in which case the node
 *          will be placed at the root of the Task Topo. ``dependencies`` may not
 *          have any duplicate entries.A handle to the new node will be returned
 *          in ``pNode``. The node executes an embedded child Task Topo. The child
 *          Task Topo is cloned in this call.
 * @param[out] pNode Returns newly created node.
 * @param[in] taskTopo The Task Topo to add the node to.
 * @param[in] dependencies Dependencies of the node.
 * @param[in] numDependencies The number of dependencies.
 * @param[in] hChildTopo The Task Topo to clone into this node.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorSysNoMem
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoAddChildTopoNode(cnrtTaskTopoNode_t *pNode,
                                       cnrtTaskTopo_t taskTopo,
                                       const cnrtTaskTopoNode_t *dependencies,
                                       size_t numDependencies,
                                       cnrtTaskTopo_t hChildTopo);

// Group: Task Topo Management
/**
 * @brief Gets a handle to the embedded Task Topo of a child Task Topo node.
 * @details This call does not clone the Task Topo. Changes to the Task Topo will
 *          be reflected in the node, and the node retains ownership of the Task Topo.
 * @param[in] node Node to get the embedded Task Topo for.
 * @param[out] pTaskTopo Location to store a handle to the Task Topo.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoChildTopoNodeGetTopo(cnrtTaskTopoNode_t node,
                                           cnrtTaskTopo_t *pTaskTopo);

typedef struct CNtaskTopoEntity_st *cnrtTaskTopoEntity_t;
// Group: Task Topo Management
/**
 * @brief Creates an executable Task Topo from a Task Topo.
 * @details Instantiates ``taskTopo`` as an executable Task Topo. The Task Topo is
 *          validated for any structural constraints or intra-node constraints which
 *          were not previously validated. If instantiation is successful, a handle
 *          to the instantiated Task Topo is returned in ``entity``.
 *
 *          If there are any errors, diagnostic information may be returned in
 *          ``errorNode`` and ``logBuffer``. This is the primary way to inspect
 *          instantiation errors. The output will be null terminated unless the
 *          diagnostics overflow the buffer. In this case, they will be truncated,
 *          and the last byte can be inspected to determine if truncation occurred.
 * @param[out] entity Returns instantiated Task Topo.
 * @param[in] taskTopo Task Topo to instantiate.
 * @param[out] pErrorNode In case of an instantiation error, this may be modified to
 *                indicate a node contributing to the error.
 * @param[out] logBuffer A character buffer to store diagnostic messages.
 * @param[in] bufferSize Size of the log buffer in bytes.
 *
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorSysNoMem
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoInstantiate(cnrtTaskTopoEntity_t *entity,
                                  cnrtTaskTopo_t taskTopo,
                                  cnrtTaskTopoNode_t *pErrorNode,
                                  char *logBuffer, size_t bufferSize);

// Group: Task Topo Management
/**
 * @brief Destroys an executable Task Topo.
 * @details Destroys the executable Task Topo specified by ``entity``, as well as
 *          all of its executable nodes. If the executable Task Topo is being
 *          executed, it will not be terminated by this API, while asynchronously
 *          released on completion of the Task Topo execution.
 * @param[in] entity Executable Task Topo to destroy.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoEntityDestroy(cnrtTaskTopoEntity_t entity);

// Group: Task Topo Management
/**
 * @brief Invokes an executable Task Topo in a Queue.
 * @details Executes ``entity`` in ``queue``. Only one instance of ``entity`` may
 *          be executed at a time. For each invoke, the entity will be ordered
 *          after both the previously invoked entity ``entity`` and the task
 *          previously invoked to a Queue ``queue``. To execute a Task Topo
 *          concurrently, it must be instantiated multiple times into multiple
 *          executable Task Topo.
 * @param[in] entity Executable Task Topo to invoke.
 * @param[in] queue Queue in which to invoke the Task Topo.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorSysNoMem
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoEntityInvoke(cnrtTaskTopoEntity_t entity,
                                   cnrtQueue_t queue);
/**
 * @brief Task Topo node types.
 */
typedef enum cnrtTaskTopoNodeType {
  cnrtTaskTopoNodeTypeEmpty = 0,
  /*!< Empty node. */
  cnrtTaskTopoNodeTypeKernel = 1,
  /*!< Kernel node. */
  cnrtTaskTopoNodeTypeHost = 2,
  /*!< Host function node. */
  cnrtTaskTopoNodeTypeMemcpy = 3,
  /*!< Memcpy node. */
  cnrtTaskTopoNodeTypeMemset = 4,
  /*!< Memset node. */
  cnrtTaskTopoNodeTypeTaskTopo = 5,
  /*!< Child Task Topo node. */
} cnrtTaskTopoNodeType_t;
// Group: Task Topo Management
/**
 * @brief Returns the node type.
 * @param[in]  node    The node to query.
 * @param[out] pType   Pointer to return the node type.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoNodeGetType(cnrtTaskTopoNode_t node,
                                  cnrtTaskTopoNodeType_t *pType);
/**
 * @brief Task Topo kernel node attributes.
 */
typedef enum cnrtKernelNodeAttr {
  cnrtKernelNodeAttributeAccessPolicyWindow = 1,
  /*!< Identifier for ::cnrtKernelNodeAttrValue::accessPolicyWindow.*/
} cnrtKernelNodeAttr_t;

/**
 * @brief \n Task Topo kernel node attribute value union, which is used by
 *        ::cnrtTaskTopoKernelNodeSetAttribute and ::cnrtTaskTopoKernelNodeGetAttribute.
 */
typedef union cnrtKernelNodeAttrValue {
  cnrtAccessPolicyWindow_t accessPolicyWindow;
  /*!<Kernel node attribute value for ::cnrtAccessPolicyWindow_t.*/
} cnrtKernelNodeAttrValue_t;

/**
 * @brief Task Topo entity update error result.
 */
typedef enum cnrtTaskTopoEntityUpdateResult {
  cnrtTaskTopoEntityUpdateSuccess = 0x0,
  /*!< The update succeeds. */
  cnrtTaskTopoEntityUpdateError = 0x1,
  /*!< The update fails for an unexpected reason. */
  cnrtTaskTopoEntityUpdateErrorTopologyChanged = 0x2,
  /*!< The update fails because the topology changes. */
  cnrtTaskTopoEntityUpdateErrorNodeTypeChanged = 0x3,
  /*!< The update fails because a node type changes. */
  cnrtTaskTopoEntityUpdateErrorParametersChanged = 0x4,
  /*!< The update fails because the parameters change in a way that is not supported. */
  cnrtTaskTopoEntityUpdateErrorNotSupported = 0x5,
  /*!< The update fails because something about the node is not supported. */
  cnrtTaskTopoEntityUpdateErrorUnsupportedFunctionChange = 0x6,
  /*!< The update fails because the function of a kernel node changed in an unsupported way. */
  cnrtTaskTopoEntityUpdateErrorAttributesChanged = 0x7
  /*!< The update fails because the node attributes changed in a way that is not supported. */
} cnrtTaskTopoEntityUpdateResult_t;

/**
 * @brief The additional write flags to create DOT file.
 */
typedef enum cnrtTaskTopoDebugDotFlags {
  cnrtTaskTopoDebugDotFlagsVerbose = (1 << 0),
  /*!< Outputs all debug data as if every debug flag is enabled. */
  cnrtTaskTopoDebugDotFlagsRuntimeTypes = (1 << 1),
  /*!< Uses runtime structures for output. */
  cnrtTaskTopoDebugDotFlagsHandles = (1 << 2),
  /*!< Adds handles to output. */
  cnrtTaskTopoDebugDotFlagsKernelNodeParams = (1 << 3),
  /*!< Adds cnrtKernelNodeParams_t values to output. */
  cnrtTaskTopoDebugDotFlagsMemcpyNodeParams = (1 << 4),
  /*!< Adds cnrtMemcpy3dParam_t values to output. .*/
  cnrtTaskTopoDebugDotFlagsMemsetNodeParams = (1 << 5),
  /*!< Adds cnrtMemsetParams_t values to output .*/
  cnrtTaskTopoDebugDotFlagsHostNodeParams = (1 << 6),
  /*!< Adds cnrtHostNodeParams_t values to output. */
  cnrtTaskTopoDebugDotFlagsKernelNodeAttribute = (1 << 7),
  /*!< Adds cnrtKernelNodeAttrValue_t values to output .*/
} cnrtTaskTopoDebugDotFlags_t;

// Group: Task Topo Management
/**
 * @brief Writes a DOT file describing Task Topo struct.
 * @param[in] taskTopo    The Task Topo to create DOT file from.
 * @param[in] path        The path to write the DOT file to.
 * @param[in] flags       Flags from ::cnrtTaskTopoDebugDotFlags_t for specifying
 *                        the additional node information to write.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorSysNoMem,
 * ::cnrtErrorSys
 */
cnrtRet_t cnrtTaskTopoDebugDotPrint(cnrtTaskTopo_t taskTopo, const char *path,
                                    unsigned int flags);

// Group: Task Topo Management
/**
 * @brief Queries the Task Topo kernel node attribute.
 * @details Queries the attribute corresponding to ``attrId`` from ``node``,
 *          and stores it in corresponding member of ``valueOut``.
 * @param[in]  node       The node to query.
 * @param[in]  attrId     Attribute ID.
 * @param[out] valueOut   The room to store the attribute value.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - The type of ``node`` must be ::cnrtTaskTopoNodeTypeKernel.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoKernelNodeGetAttribute(
    cnrtTaskTopoNode_t node, cnrtKernelNodeAttr_t attrId,
    cnrtKernelNodeAttrValue_t *valueOut);
// Group: Task Topo Management
/**
 * @brief Sets the Task Topo kernel node attribute.
 * @details Sets the attribute corresponding to ``attrId`` for ``node`` from
 *          corresponding attribute of ``value``.
 * @param[in] node       The node to set attribute for.
 * @param[in] attrId     Attribute ID.
 * @param[in] value      The attribute value to set.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - The type of ``node`` must be ::cnrtTaskTopoNodeTypeKernel.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoKernelNodeSetAttribute(
    cnrtTaskTopoNode_t node, cnrtKernelNodeAttr_t attrId,
    const cnrtKernelNodeAttrValue_t *value);

// Group: Task Topo Management
/**
 * @brief Copies Task Topo kernel node attributes from source node to the destination node.
 * @param[in] dst The destination node.
 * @param[in] src The source node.
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - Both nodes must belong to the same Task Topo.
 * - The type of both nodes must be ::cnrtTaskTopoNodeTypeKernel.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoKernelNodeCopyAttributes(cnrtTaskTopoNode_t dst,
                                               cnrtTaskTopoNode_t src);
// Group: Task Topo Management
/**
 * @brief Sets the parameters for a host node in the given Task Topo ``entity``.
 * @details The host node is identified by the corresponding ``node`` in the
 *          non-executable Task Topo, from which the executable Task Topo is instantiated.
 *          Changes to to-and-from hNode edges are ignored.
 *          The changes only affect future launches of ``entity``. Already enqueued
 *          or running launches of ``entity`` are not affected by this call. ``node`` cannot
 *          be modified by this call either.
 *
 * @param[in] entity The executable Task Topo in which to set the specified node.
 * @param[in] node Host node of the Task Topo which is used to instantiate entity.
 * @param[in] nodeParams The updated parameters to set.
 *
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoEntityHostNodeSetParams(
    cnrtTaskTopoEntity_t entity, cnrtTaskTopoNode_t node,
    const cnrtHostNodeParams_t *nodeParams);

// Group: Task Topo Management
/**
 * @brief Sets the parameters for a kernel node in the Task Topo ``entity``.
 * @details The kernel node is identified by the corresponding ``node`` in the
 *          non-executable Task Topo, from which the executable Task Topo entity is instantiated.
 *          Changes to to-and-from hNode edges are ignored.
 *
 *          ``node`` must not have been removed from the original Task Topo entity.
 *          The ``func`` field of ``nodeParams`` cannot be modified and must match the
 *          original value. All other values can be modified.
 *
 *          The changes only affect future launches of ``entity``. Already
 *          enqueued or running launches of ``entity`` are not affected by this call.
 *          ``node`` cannot be modified by this call either.
 *
 * @param[in] entity The executable Task Topo entity in which to set the specified node.
 * @param[in] node Kernel node of the Task Topo from which Task Topo entity is instantiated.
 * @param[in] nodeParams The updated parameters to set.
 *
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoEntityKernelNodeSetParams(
    cnrtTaskTopoEntity_t entity, cnrtTaskTopoNode_t node,
    const cnrtKernelNodeParams_t *nodeParams);

// Group: Task Topo Management
/**
 * @brief Sets the parameters for a memcpy node in the given Task Topo entity ``entity``.
 * @details The memcpy node is identified by the corresponding ``node`` in the
 *          non-executable Task Topo, from which the executable Task Topo entity is instantiated.
 *          Changes to to-and-from hNode edges are ignored.
 *
 *          If origin memcpy node is DtoH or HtoD, the device memory must be allocated
 *          from the same Context as the original memory. If origin memcpy node is DtoD,
 *          the source memory must be allocated from the same Context as the original source memory.
 *          Both the instantiation-time memory operands and the memory operands in ``nodeParams`` must be
 *          1-dimensional. Zero-length operations are not supported. The restrictions of ``nodeParams`` are
 *          the same as ::cnrtTaskTopoAddMemcpyNode().
 *
 *          The changes only affect future launches of ``entity``.  Already enqueued
 *          or running launches of ``entity`` are not affected by this call. ``node`` cannot be modified
 *          by this call.
 *
 *          Returns ::cnrtErrorArgsInvalid if the memory operands' mappings change; or
 *          either the original or new memory operands are multidimensional.
 *
 * @param[in] entity The executable Task Topo entity in which to set the specified node.
 * @param[in] node Memcpy node of the Task Topo which is used to instantiate Task Topo entity.
 * @param[in] nodeParams The updated parameters to set.
 *
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoEntityMemcpyNodeSetParams(
    cnrtTaskTopoEntity_t entity, cnrtTaskTopoNode_t node,
    const cnrtMemcpy3dParam_t *nodeParams);

// Group: Task Topo Management
/**
 * @brief Sets the parameters for a memset node in the given Task Topo ``entity``.
 * @details The memset node is identified by the corresponding ``node`` in the
 *          non-executable Task Topo, from which the executable Task Topo entity is instantiated.
 *          Changes to to-and-from hNode edges are ignored.
 *
 *          The destination memory in ``nodeParams`` must be allocated from the same
 *          Context as the original destination memory. Both the instantiation-time
 *          memory operand and the memory operand in ``nodeParams`` must be 1-dimensional.
 *          Zero-length operations are not supported.
 *
 *          The changes only affect future launches of ``entity``.  Already enqueued
 *          or running launches of ``entity`` are not affected by this call. ``node``
 *          cannot be modified by this call either.
 *
 *          Returns cnrtErrorArgsInvalid if the memory operand's mappings changes; or
 *          either the original or new memory operand are multidimensional.
 *
 * @param[in] entity The executable Task Topo entity in which to set the specified node.
 * @param[in] node Memset node of the Task Topo which is used to instantiate Task Topo entity.
 * @param[in] nodeParams The updated parameters to set.
 *
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoEntityMemsetNodeSetParams(
    cnrtTaskTopoEntity_t entity, cnrtTaskTopoNode_t node,
    const cnrtMemsetParams_t *nodeParams);

// Group: Task Topo Management
/**
 * @brief Updates node parameters in the child Task Topo node in the given Task Topo ``entity``.
 * @details The child node is identified by the corresponding ``node`` in the
 *          non-executable Task Topo, from which the executable Task Topo entity is instantiated.
 *          Changes to to-and-from hNode edges are ignored.
 *
 *          The topology of ``childTopo``, as well as the node insertion order, must match that
 *          of the Task Topo contained in ``node``.  See ::cnrtTaskTopoEntityUpdate() for a list of
 *          restrictions on what can be updated in Task Topo entity. The update is recursive, so child Topo
 *          nodes contained within the top level child Task Topo will also be updated.
 *
 *          The changes only affect future launches of ``entity``. Already enqueued
 *          or running launches of ``entity`` are not affected by this call. ``node`` cannot be
 *          modified by this call either.
 *
 * @param[in] entity The executable Task Topo entity in which to set the specified node.
 * @param[in] node Child node of the Task Topo which is used to instantiate Task Topo entity.
 * @param[in] childTopo The child Task Topo supplying the updated parameters.
 *
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid
 * @note
 * - None.
 * @example
 * - None.
 */
cnrtRet_t cnrtTaskTopoEntityChildTopoNodeSetParams(cnrtTaskTopoEntity_t entity,
                                                   cnrtTaskTopoNode_t node,
                                                   cnrtTaskTopo_t childTopo);

// Group: Task Topo Management
/**
 * @brief Checks whether an executable Task Topo entity can be updated with a Task Topo
 *        and perform the update if possible.
 * @details Updates the node parameters in the instantiated Task Topo entity
 *          specified by ``entity`` with the node parameters in a topologically identical
 *          Task Topo specified by ``topo``.
 *
 * Limitations:
 *
 * - Kernel node restrictions:
 *   - The owning Context of the function cannot be changed.
 * - Memset nodes restrictions:
 *   - The device(s) to which the operand(s) is allocated/mapped cannot be changed.
 *   - The memory must be allocated from the same Context as the original memory.
 *   - Only 1D memset is supported now.
 *   - Zero-length operations are not supported.
 * - Memcpy node restrictions:
 *   - If memcpy is DtoH or HtoD, the device memory must be allocated from the same
 *     Context as the original memory.
 *   - If memcpy is DtoD, the source memory must be allocated from the same Context as
 *     the original source memory.
 *   - Only 1D memcpy is supported now.
 *   - Zero-length operations are not supported.
 *
 * ::cnrtTaskTopoEntityUpdate() sets ``updateResult_out`` to
 * cnrtTaskTopoEntityUpdateErrorTopologyChanged under the following conditions:
 *
 * - The count of nodes directly in ``entity`` and ``node`` differ, in which case ``updateResult_out``
 *   is NULL.
 * - A node is deleted in ``node`` but not its pair from ``entity``, in which case ``updateResult_out``
 *   is NULL.
 * - A node is deleted in ``entity`` but not its pair from ``node``, in which case ``updateResult_out``
 *   is the pairless node from ``node``.
 * - The dependent nodes of a pair differ, in which case ``updateResult_out`` is the node from ``topo``.
 *
 * ::cnrtTaskTopoEntityUpdate() sets ``updateResult_out`` to:
 * - cnrtTaskTopoEntityUpdateError if an invalid value is passed.
 * - cnrtTaskTopoEntityUpdateErrorTopologyChanged if the Task Topo topology is changed.
 * - cnrtTaskTopoEntityUpdateErrorNodeTypeChanged if the type of a node is changed, in which
 *   case ``updateResult_out`` is set to the node from ``topo``.
 * - cnrtTaskTopoEntityUpdateErrorUnsupportedFunctionChange if the function changes in an
 *   unsupported way (see note above), in which case ``pErrorNode_out`` is set to the node from ``topo``.
 * - cnrtTaskTopoEntityUpdateErrorParametersChanged if any parameter of a node is changed in a
 *   way that is not supported, in which case ``pErrorNode_out`` is set to the node from ``topo``.
 * - cnrtTaskTopoEntityUpdateErrorAttributesChanged if any attribute of a node is changed in a
 *   way that is not supported, in which case ``pErrorNode_out`` is set to the node from ``topo``.
 * - cnrtTaskTopoEntityUpdateErrorNotSupported if something about a node is unsupported, in
 *   which case ``pErrorNode_out`` is set to the node from ``topo``.
 *
 * If ``updateResult_out`` isn't set in one of the situations described above, the update check
 * passes and ::cnrtTaskTopoEntityUpdate() updates ``entity`` to match the contents of ``topo``. If an
 * error happens during the update,``updateResult_out`` will be set to
 * cnrtTaskTopoEntityUpdateError; otherwise, ``updateResult_out`` is set to cnrtTaskTopoEntityUpdateSuccess.
 *
 * ::cnrtTaskTopoEntityUpdate() returns cnrtSuccess when the update is performed successfully. It
 * returns cnrtErrorTaskTopoEntityUpdateFailure if the Task Topo entity update is not
 * performed because it includes changes which violate constraints specific to instantiated Task
 * Topo entity update.
 *
 * @param[in] entity The instantiated Task Topo entity to be updated.
 * @param[in] topo The Task Topo containing the updated parameters.
 * @param[out] pErrorNode_out The node which causes the permissibility check to forbid the update, if any.
 * @param[out] updateResult_out Whether the Task Topo update is permitted, and what the reason is if it is forbidden.
 *
 * @return
 * ::cnrtSuccess,
 * ::cnrtErrorArgsInvalid,
 * ::cnrtErrorTaskTopoEntityUpdateFailure
 * @note
 * - The API may add further restrictions in future releases. The return code should always be
 *   checked.
 * @example
 * - None.

 */
cnrtRet_t cnrtTaskTopoEntityUpdate(
    cnrtTaskTopoEntity_t entity, cnrtTaskTopo_t topo,
    cnrtTaskTopoNode_t *pErrorNode_out,
    cnrtTaskTopoEntityUpdateResult_t *updateResult_out);

/*!
 * @brief
 *
 * Describes the return values of CNRT APIs.
 */
#define CNRT_RET_SUCCESS                     cnrtSuccess
#define CNRT_RET_WARNING_FAKE_DEVICE         ((cnrtRet_t)1)
#define CNRT_RET_ERR_NOT_READY               ((cnrtRet_t)632006)
#define CNRT_RET_ERR_INVALID                 ((cnrtRet_t)632007)
#define CNRT_RET_ERR_NOMEM                   ((cnrtRet_t)632008)
#define CNRT_RET_ERR_NODEV                   ((cnrtRet_t)632009)
#define CNRT_RET_ERR_SYS                     ((cnrtRet_t)632011)
#define CNRT_RET_ERR_ACCES                   ((cnrtRet_t)632012)
#define CNRT_RET_ERR_ACCESS                  ((cnrtRet_t)632012)
#define CNRT_RET_ERR_FAULT                   ((cnrtRet_t)632013)
#define CNRT_RET_ERR_BUSY                    ((cnrtRet_t)632014)
#define CNRT_RET_ERR_NORES                   ((cnrtRet_t)632019)
#define CNRT_RET_ERR_UNSUPPORTED             ((cnrtRet_t)632020)
#define CNRT_RET_ERR_INVALID_POINTER         ((cnrtRet_t)632021)
#define CNRT_RET_ERR_NO_EXIST                ((cnrtRet_t)632022)
#define CNRT_RET_ERR_BROKEN                  ((cnrtRet_t)632023)
#define CNRT_RET_ERR_INIT                    ((cnrtRet_t)632024)
#define CNRT_RET_ERR_QUEUE                   ((cnrtRet_t)632025)
#define CNRT_RET_ERR_OUT_RANGE               ((cnrtRet_t)632026)
#define CNRT_RET_ERR_FUNC_CALL               ((cnrtRet_t)632028)
#define CNRT_RET_ERR_UNHANDLED               ((cnrtRet_t)632029)
#define CNRT_RET_ERR_INVALID_TYPE            ((cnrtRet_t)632030)
#define CNRT_RET_ERR_INVALID_OP              ((cnrtRet_t)632031)
#define CNRT_RET_ERR_RESHAPE                 ((cnrtRet_t)632035)
#define CNRT_RET_ERR_MEMCPY                  ((cnrtRet_t)632036)
#define CNRT_RET_ERR_ENCRYPT                 ((cnrtRet_t)632037)
#define CNRT_RET_ERR_INVALID_DATADESC        ((cnrtRet_t)632038)
#define CNRT_RET_ERR_MAP                     ((cnrtRet_t)632039)
#define CNRT_RET_ERR_UNMAP                   ((cnrtRet_t)632040)
#define CNRT_RET_ERR_CACHE                   ((cnrtRet_t)632041)
#define CNRT_RET_ERR_FIND_DEV_ADDR           ((cnrtRet_t)632042)
#define CNRT_RET_ERR_KERNEL_VERSION_TOO_HIGH ((cnrtRet_t)632043)
#define CNRT_RET_ERR_CNDRV_FUNC_CALL         ((cnrtRet_t)632046)
#define CNRT_RET_ERR_CNDEV_FUNC_CALL         ((cnrtRet_t)632047)
#define CNRT_RET_ERR_IO                      ((cnrtRet_t)632048)
#define CNRT_RET_ERR_TIMEOUT                 ((cnrtRet_t)632049)
#define CNRT_RET_ERR_NOSYS                   ((cnrtRet_t)632050)
#define CNRT_RET_ERR_AGAIN                   ((cnrtRet_t)632051)
#define CNRT_RET_ERR_EXIST                   ((cnrtRet_t)632052)
#define CNRT_RET_ERR_MATH_OVERFLOW           ((cnrtRet_t)632053)
#define CNRT_RET_ERR_MLU                     ((cnrtRet_t)632054)
#define CNRT_RET_ERR_ONCHIP_CORE             ((cnrtRet_t)632055)
#define CNRT_RET_ERR_GET_MEM_RANGE           ((cnrtRet_t)632056)
#define CNRT_RET_ERR_GET_MEM_INFO            ((cnrtRet_t)632057)
#define CNRT_RET_ERR_EVENT                   ((cnrtRet_t)632058)
#define CNRT_RET_ERR_NOTIFIER                ((cnrtRet_t)632059)
#define CNRT_RET_ERR_GET_IMP_DEV             ((cnrtRet_t)632060)
#define CNRT_RET_ERR_LOAD_MODULE             ((cnrtRet_t)632061)
#define CNRT_RET_ERR_UNKNOWN                 ((cnrtRet_t)999991)
#define CNRT_RET_ERR_MAX                     ((cnrtRet_t)999992)
/*!
 *  @brief
 *
 *  Describes the queue flag used for the
 *  current process execution on the current Device.
 *
 *  The ::cnrtSetDeviceFlag function is used to set the flag.
 *  The ::cnrtGetDeviceFlag function is used to retrieve the flag set.
 *
 */
#define CNRT_QUEUE_SYNC_SPIN  ((cnrtDeviceFlags_t)0)
#define CNRT_QUEUE_SYNC_BLOCK ((cnrtDeviceFlags_t)1)
#define CNRT_QUEUE_SYNC_YIELD ((cnrtDeviceFlags_t)2)

/**< Execution modes of tasks on MLU. */
/*! @brief
 *
 *  Describes the number of cores used
 *  for computation on the MLU Devices.
 */
#define CNRT_FUNC_TYPE_BLOCK   ((cnrtFunctionType_t)1)
#define CNRT_FUNC_TYPE_BLOCK0  ((cnrtFunctionType_t)1)
#define CNRT_FUNC_TYPE_BLOCK1  ((cnrtFunctionType_t)2)
#define CNRT_FUNC_TYPE_UNION1  ((cnrtFunctionType_t)4)
#define CNRT_FUNC_TYPE_UNION2  ((cnrtFunctionType_t)8)
#define CNRT_FUNC_TYPE_UNION4  ((cnrtFunctionType_t)16)
#define CNRT_FUNC_TYPE_UNION8  ((cnrtFunctionType_t)32)
#define CNRT_FUNC_TYPE_UNION16 ((cnrtFunctionType_t)64)
#define CNRT_FUNC_TYPE_MUTABLE ((cnrtFunctionType_t)-1)
#define CNRT_JOB_TYPE_BLOCK    ((cnrtFunctionType_t)CNRT_FUNC_TYPE_BLOCK)
#define CNRT_JOB_TYPE_UNION1   ((cnrtFunctionType_t)CNRT_FUNC_TYPE_UNION1)
#define CNRT_JOB_TYPE_UNION2   ((cnrtFunctionType_t)CNRT_FUNC_TYPE_UNION2)
#define CNRT_JOB_TYPE_UNION4   ((cnrtFunctionType_t)CNRT_FUNC_TYPE_UNION4)
/*! @brief
 *
 * Describes the direction of data copy.
 */
#define CNRT_MEM_TRANS_DIR_HOST2DEV  ((cnrtMemTransDir_t)0)
#define CNRT_MEM_TRANS_DIR_DEV2DEV   ((cnrtMemTransDir_t)1)
#define CNRT_MEM_TRANS_DIR_DEV2HOST  ((cnrtMemTransDir_t)2)
#define CNRT_MEM_TRANS_DIR_HOST2HOST ((cnrtMemTransDir_t)3)
#define CNRT_MEM_TRANS_DIR_PEER2PEER ((cnrtMemTransDir_t)4)
#define CNRT_MEM_TRANS_DIR_NODIR     ((cnrtMemTransDir_t)5)

/**< Data type and data order.*/
/*! @brief
 *
 * Describes the data types supported by CNRT.
 */
#define CNRT_INVALID ((cnrtDataType_t)0x0)
#define CNRT_FLOAT16 ((cnrtDataType_t)0x12)
#define CNRT_FLOAT32 ((cnrtDataType_t)0x13)
#define CNRT_FLOAT64 ((cnrtDataType_t)0x14)
#define CNRT_INT4    ((cnrtDataType_t)0x20)
#define CNRT_INT8    ((cnrtDataType_t)0x21)
#define CNRT_INT16   ((cnrtDataType_t)0x22)
#define CNRT_INT32   ((cnrtDataType_t)0x23)
#define CNRT_INT64   ((cnrtDataType_t)0x24)
#define CNRT_AUTO    ((cnrtDataType_t)0x25)
#define CNRT_UINT8   ((cnrtDataType_t)0x31)
#define CNRT_UINT16  ((cnrtDataType_t)0x32)
#define CNRT_UINT32  ((cnrtDataType_t)0x33)
#define CNRT_FIX8    ((cnrtDataType_t)0x41)
#define CNRT_QUANT8  ((cnrtDataType_t)0x51)
#define CNRT_BOOL    ((cnrtDataType_t)0x61)

#define CNRT_CHECK(val)                                                       \
  do {                                                                        \
    cnrtRet_t ret = val;                                                      \
    if (ret) {                                                                \
      printf("[%s:%d] CNRT error, code=%d(%s) \"%s\" \n", __FILE__, __LINE__, \
             (unsigned int)ret, cnrtGetErrorStr(ret), #val);                  \
      exit(-1);                                                               \
    }                                                                         \
  } while (0)

#ifndef __DOXYGEN_ONLY__
/** Not documenting @{ */

// clang-format off

#if defined(__GNUC__)
#if defined(__clang__) || (!defined(__PGIC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)))
#pragma GCC diagnostic push
#endif
#if defined(__clang__) || (!defined(__PGIC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2)))
#pragma GCC diagnostic ignored "-Wunused-function"
#endif
#elif defined(_MSC_VER)
#pragma warning(push)
#pragma waring(disable: 4820)
#endif

#if defined(__GNUC__)
#if defined(__clang__) || (!defined(__PGIC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)))
#pragma GCC diagnostic pop
#endif
#elif defined(_MSC_VER)
#pragma warning(pop)
#endif

// clang-format on

/** @} */
#endif

#if defined(__cplusplus)
}
#endif /*__cplusplus*/

#endif /*__CNRT_H*/
