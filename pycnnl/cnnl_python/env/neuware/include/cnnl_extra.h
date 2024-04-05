/*************************************************************************
 * Copyright (C) [2019-2022] by Cambricon, Inc.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *************************************************************************/
#ifndef CNNL_EXTRA_H_
#define CNNL_EXTRA_H_

/******************************************************************************
 * CNNL_EXTRA: CNNL Extra Library
 ******************************************************************************/

#define CNNL_EXTRA_MAJOR 0
#define CNNL_EXTRA_MINOR 18
#define CNNL_EXTRA_PATCHLEVEL 0

#include "cnnl.h"

#ifndef CNNL_WIN_API
#ifdef _WIN32
#define CNNL_WIN_API __stdcall
#else
#define CNNL_WIN_API
#endif
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/******************************************************************************
 * Cambricon CNNL Data Structure: Detection Output
 ******************************************************************************/
/*!
 * @brief An enum.
 *
 * Enumeration variables describe the modes that are used in the
 * implementation of the detection output op.
 *
 */
typedef enum {
  CNNL_DETECTION_OUTPUT_SSD        = 0, /*!< The SSD kernel is implemented.*/
  CNNL_DETECTION_OUTPUT_YOLOV2     = 1, /*!< The YOLOv2 kernel is implemented.*/
  CNNL_DETECTION_OUTPUT_YOLOV3     = 2, /*!< The YOLOv3 kernel is implemented.*/
  CNNL_DETECTION_OUTPUT_FASTERRCNN = 3, /*!< The FasterRCNN kernel is implemented.*/
  CNNL_DETECTION_OUTPUT_YOLOV4 = 4, /*!< The YOLOV4 kernel is implemented.*/
  CNNL_DETECTION_OUTPUT_YOLOV5 = 5, /*!< The YOLOV5 kernel is implemented.*/
  CNNL_DETECTION_OUTPUT_REFINEDET = 6, /*!< The REFINEDET kernel is implemented.*/
  CNNL_DETECTION_OUTPUT_RETINANET = 7, /*!< The RETINANET kernel is implemented.*/
} cnnlDetectionOutputAlgo_t;

/******************************************************************************
 * Cambricon CNNL Transformer Layernorm position
 ******************************************************************************/
//! @brief An enum.
/*! Enumeration variables describe the position of layernorm for transformer. */
typedef enum {
  CNNL_TRANSFORMER_NO_LAYERNORM = 0,  /*!< Without layernorm.*/
  CNNL_TRANSFORMER_PRE_LAYERNORM,  /*!< Layernorm in front of operation.*/
  CNNL_TRANSFORMER_POST_LAYERNORM,  /*!< Layernorm in back of operation.*/
} cnnlTransformerLayernormMode_t;

/******************************************************************************
 * Cambricon CNNL Transformer Layernorm And Residual Structure
 ******************************************************************************/
//! @brief An enum.
/*! Enumeration variables describe the structure of layernorm and residual
 * for the building block of transformer network. */
typedef enum {
  CNNL_TRANSFORMER_NO_LAYERNORM_NO_RESIDUAL = 0,
  /*!< Perform the operation without layernorm and residual.
       Structure is as follows:
       @verbatim
        [----(op)----]
       @endverbatim */
  CNNL_TRANSFORMER_NO_LAYERNORM_WITH_RESIDUAL = 1,
  /*!< Perform the operation without layernorm and with residual.
       Structure is as follows:
       @verbatim
                        -------------
                       |             |
                  [---------(op)----(+)----]
       @endverbatim */
  CNNL_TRANSFORMER_PRE_LAYERNORM_NO_RESIDUAL = 2,
  /*!< Perform layernorm before the operation and without residual.
       Structure is as follows:
       @verbatim
        [----(ln)----(op)----]
       @endverbatim */
  CNNL_TRANSFORMER_POST_LAYERNORM_NO_RESIDUAL = 3,
  /*!< Perform layernorm after the operation and without residual.
       Structure is as follows:
       @verbatim
        [----(op)----(ln)----]
       @endverbatim */
  CNNL_TRANSFORMER_PRE_LAYERNORM_INSIDE_RESIDUAL = 4,
  /*!< Perform layernorm before the operation and layernorm inside residual structure.
       Structure is as follows:
       @verbatim
                        ---------------------
                       |                     |
                  [---------(ln)----(op)----(+)----]
       @endverbatim */
  CNNL_TRANSFORMER_PRE_LAYERNORM_OUTSIDE_RESIDUAL = 5,
  /*!< Perform layernorm before operation and layernorm outside residual structure.
       Structure is as follows:
       @verbatim
                                -------------
                               |             |
                  [----(ln)---------(op)----(+)----]
       @endverbatim */
  CNNL_TRANSFORMER_POST_LAYERNORM_INSIDE_RESIDUAL = 6,
  /*!< Perform layernorm after the operation and layernorm inside residual structure.
       Structure is as follows:
       @verbatim
                        ---------------------
                       |                     |
                  [---------(op)----(ln)----(+)----]
       @endverbatim */
  CNNL_TRANSFORMER_POST_LAYERNORM_OUTSIDE_RESIDUAL = 7,
  /*!< Perform layernorm before the operation and layernorm outside residual structure.
       Structure is as follows:
       @verbatim
                        -------------
                       |             |
                  [---------(op)----(+)----(ln)----]
       @endverbatim */
} cnnlTransformerLayernormResidualStructure_t;

/******************************************************************************
 * Cambricon CNNL Transformer Encoder Output Mode
 ******************************************************************************/
//! @brief An enum.
/*! Enumeration variables describe the output mode for the transformer_encoder_output. */
typedef enum {
  CNNL_TRANSFORMER_ENCOUT_NOT_DATAFORMAT = 0,
  /*!< Calculate the outputs (float/half), and set layout of out_K/out_V to [batch, head,
    * token, head_size]. */
  CNNL_TRANSFORMER_ENCOUT_DATAFORMAT_FPOUT = 1,
   /*!< Calculate the outputs (float/half), and tile out_K and transpose out_V. */
  CNNL_TRANSFORMER_ENCOUT_DATAFORMAT_FPOUT_CALCPOS = 2,
  /*!< Calculate the outputs (float/half) and the quantified position and scale of output,
   * and tile out_K and transpose out_V. */
  CNNL_TRANSFORMER_ENCOUT_DATAFORMAT_OFFLINE_QUANT = 3,
  /*!< Calculate the outputs (int16/int8) with offline quantified position and scale, and
   * tile out_K and transpose out_V.*/
  CNNL_TRANSFORMER_ENCOUT_DATAFORMAT_ONLINE_QUANT = 4,
  /*!< Calculate the outputs (int16/int8) with online quantified position and scale, and
   * tile out_K and transpose out_V. */
} cnnlTransformerEncOutMode_t;

/******************************************************************************
 * Cambricon CNNL Transformer data order mode for layout
 ******************************************************************************/
//! @brief An enum.
/*! Enumeration variables describe the data order of filter matrix. */
typedef enum {
  CNNL_TRANSFORMER_MATRIX_ORDER_ROW = 0, /*!< Row is first place in matrix.*/
  CNNL_TRANSFORMER_MATRIX_ORDER_COL,  /*!< Col is first place in matrix.*/
} cnnlTransformerMatrixOrder_t;

/******************************************************************************
 * Cambricon CNNL ROI code type
 ******************************************************************************/
//! @brief An enum.
/*! Enumeration variables describe the code type of region of interest. */
typedef enum {
  CNNL_ROI_CORNER = 0,
  /*!< The origin of roi is in the corner of the image.
   *   The order of roi elements is [roi_x_start, roi_y_start, roi_x_end, roi_y_end].*/
  CNNL_ROI_CORNER_BATCHID = 1,
  /*!< The origin of roi is in the corner of the image.
   *   The order of roi elements is [roi_x_start, roi_y_start, roi_x_end, roi_y_end, batch_id].*/
  CNNL_ROI_BATCHID_CORNER = 2,
  /*!< The origin of roi is in the corner of the image.
   *   The order of roi elements is [batch_id, roi_x_start, roi_y_start, roi_x_end, roi_y_end].*/
  CNNL_ROI_CENTER = 3,
  /*!< The origin of roi is in the center of the image.
   *   The order of roi elements is [roi_x_start, roi_y_start, roi_x_end, roi_y_end].*/
  CNNL_ROI_CENTER_BATCHID = 4,
  /*!< The origin of roi is in the center of the image.
   *   The order of roi elements is [roi_x_start, roi_y_start, roi_x_end, roi_y_end, batch_id].*/
  CNNL_ROI_BATCHID_CENTER = 5,
  /*!< The origin of roi is in the center of the image.
   *   The order of roi elements is [batch_id, roi_x_start, roi_y_start, roi_x_end, roi_y_end].*/
  CNNL_ROI_CORNER_SCORE = 6,
  /*!< The origin of roi is in the corner of the image.
   *   The order of roi elements is [roi_x_start, roi_y_start, roi_x_end, roi_y_end, score].*/
  CNNL_ROI_SCORE_CORNER = 7,
  /*!< The origin of roi is in the corner of the image.
   *   The order of roi elements is [score, roi_x_start, roi_y_start, roi_x_end, roi_y_end].*/
  CNNL_ROI_CENTER_SCORE = 8,
  /*!< The origin of roi is in the center of the image.
   *   The order of roi elements is [roi_x_start, roi_y_start, roi_x_end, roi_y_end, score].*/
  CNNL_ROI_SCORE_CENTER = 9,
  /*!< The origin of roi is in the center of the image.
   *   The order of roi elements is [score, roi_x_start, roi_y_start, roi_x_end, roi_y_end].*/
} cnnlRoiLayoutType_t;

/******************************************************************************
 * Cambricon CNNL NMS type
 ******************************************************************************/
//! @brief An enum.
/*! Enumeration variables describe the NMS (Non-Max Suppression) modes.*/
typedef enum {
  CNNL_DEFAULT_NMS = 0,
  /*!< The multi-label traditional NMS mode is selected.
   *   The Intersection over Union (IoU) is used to compare the thresh.*/
  CNNL_GREEDY_NMS  = 1,
  /*!< The multi-label greedy NMS mode is selected.
   *   The calculation formula is : IoU - pow(d/c, beta).
   *   The d denotes to the square of the distance between two center points of box.
   *   The c denotes to the square of the minimum diagonal length of circumscribed
   *   rectangle of two boxes.
   *   The beta equals to 0.6.*/
  CNNL_DIOU_NMS  = 2,
  /*!< The multi-label Distance-IoU (DIoU) NMS mode is selected.
   *   The calculation formula is : IoU - pow(d/c, beta).
   *   The d denotes to the square of the distance between two center points of box.
   *   The c denotes to the square of the minimum diagonal length of circumscribed
   *   rectangle of two box.
   *   The beta is index part of the ratio of d to c.*/
  CNNL_DEFAULT_SINGLE_LABEL_NMS = 3,
  /*!< The single label traditional NMS type is selected. The loss function Intersection
   *   to Union (IoU) is used to compare the thresh.*/
} cnnlNmsType_t;

/******************************************************************************
 * Cambricon CNNL OP: detection output
 ******************************************************************************/
/*! The descriptor of detection output function that holds algorithms, input/output shapes, and
 * NMS parameters. */
typedef struct cnnlDetectionOutputStruct *cnnlDetectionOutputDescriptor_t;

// Group:Detection Output
/*!
 *  @brief A function.
 *
 *  This function is used to create a detection output descriptor, which contains the SSD,
 *  REFINEDET, RETINANET, YOLOV2/3/4/5 and Faster-RCNN detection output algorithm parameters.
 *
 *  @param[in] detection_output_desc
 *    Input.  A pointer to the struct of detection_output descriptor.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *      - desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlCreateDetectionOutputDescriptor(cnnlDetectionOutputDescriptor_t *detection_output_desc);

// Group:Detection Output
/*!
 *  @brief A function.
 *
 *  This function is used to set Yolov3 detection output descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  1. Call ::cnnlCreateDetectionOutputDescriptor before using this function.
 *
 *  2. Call ::cnnlDestroyDetectionOutputDescriptor when ::cnnlDetectionOutputDescriptor_t no longer
 *  needed.
 *
 *  @param[in] desc
 *    Input.  A pointer to the object of detection_output descriptor.
 *  @param[in] mode
 *    Input.  Algorithm of detection_output descriptor. Must be CNNL_DETECTION_OUTPUT_YOLOV3.
 *  @param[in] num_batch
 *    Input.  The number of batch for each feature map. Can be any positive integer as long as input
 *            tensor size is less than 2GB.
 *  @param[in] num_input
 *    Input.  The number of input feature maps. Must belong to [1, 7].
 *  @param[in] num_anchor.
 *    Input.  The number of anchors, assuming same for all input feature maps.
 *            Must belong to [1, 8].
 *  @param[in] num_class.
 *    Input.  The number of possible classes of each detected object.
 *            Can be any positive integer as long as input tensor size is less than 2GB.
 *  @param[in] num_entry
 *    Input.  The number of description dimensions for every predicted point in all the feature
 *            maps. Must be 5, where 5 entries represent x, y, w, h, objectness information.
 *  @param[in] num_keep
 *    Input.  The largest possible number of bounding boxes. Must belong to [1, 2048].
 *  @param[in] height_image
 *    Input.  The height of detection network input image. Must be greater than 0.
 *  @param[in] width_image
 *    Input.  The width of detection network input image. Must be greater than 0.
 *  @param[in] thresh_confidence
 *    Input.  The minimal threshold for marking a box as an object. Must belong to [0, 1].
 *  @param[in] thresh_nms
 *    Input.  The minimal threshold for marking and eliminating a duplicate box.
 *            Must belong to [0, 1].
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions are met:
 *    - desc is NULL.
 *    - mode is not CNNL_DETECTION_OUTPUT_YOLOV3.
 *    - parameters do not meet requirements.
 */

cnnlStatus_t CNNL_WIN_API
cnnlSetYolov3DetectionOutputDescriptor(cnnlDetectionOutputDescriptor_t desc,
                                       cnnlDetectionOutputAlgo_t mode,
                                       int num_batch,
                                       int num_input,
                                       int num_anchor,
                                       int num_class,
                                       int num_entry,
                                       int num_keep,
                                       int height_image,
                                       int width_image,
                                       float thresh_confidence,
                                       float thresh_nms);

// Group:Detection Output
/*!
 *  @brief A function.
 *
 *  This function is used to set Yolov3 detection output descriptor with parameters.
 *  Compared with ::cnnlSetYolov3DetectionOutputDescriptor, this function allows
 *  user to set clip which indicates whether to enable clipping boxes, to set
 *  scale_x_y which is used to scale boxes' center, and to set unnormalize_scale_h
 *  and unnormalize_scale_w which are used to scale boxes' size.
 *
 *  **API Dependency**
 *
 *  1. Call ::cnnlCreateDetectionOutputDescriptor() before using this function.
 *
 *  2. Call ::cnnlDestroyDetectionOutputDescriptor() when cnnlDetectionOutputDescriptor_t is no
 *  longer needed.
 *
 *  @param[in] desc
 *    Input.  A pointer to the struct of detection output descriptor.
 *  @param[in] mode
 *    Input.  Algorithm of detection output operation. Must be CNNL_DETECTION_OUTPUT_YOLOV3.
 *  @param[in] num_batch
 *    Input.  The number of batch for each feature map. Can be any positive integer as long as input
 *            tensor size is less than 2GB.
 *  @param[in] num_input
 *    Input.  The number of input feature maps. Must belong to [1, 7].
 *  @param[in] num_anchor.
 *    Input.  The number of anchors, assuming same for all input feature maps.
 *            Must belong to [1, 8].
 *  @param[in] num_class.
 *    Input.  The number of possible classes of each detected object.
 *            Can be any positive integer as long as input tensor size is less than 2GB.
 *  @param[in] num_entry
 *    Input.  The number of description dimensions for every predicted point in all the feature
 *            maps. Must be 5, where 5 entries represent x, y, w, h and objectness information.
 *  @param[in] num_keep
 *    Input.  The largest possible number of bounding boxes. Must belong to [1, 2048].
 *  @param[in] height_image
 *    Input.  The height of detection network input image. Must be greater than 0.
 *  @param[in] width_image
 *    Input.  The width of detection network input image. Must be greater than 0.
 *  @param[in] clip
 *    Input.  Whether or not to clip when decoding, 0: disable, 1: enable.
 *  @param[in] scale_x_y
 *    Input.  The scale factor for scaling boxes center when decoding. Must be greater than 0.
 *  @param[in] unnormalize_scale_h
 *    Input.  The scale factor for scaling boxes height. Must be greater than or equal to 1.
 *  @param[in] unnormalize_scale_w
 *    Input.  The scale factor for scaling boxes width. Must be greater than or equal to 1.
 *  @param[in] thresh_confidence
 *    Input.  The minimal threshold for marking a box as an object. Must belong to [0, 1].
 *  @param[in] thresh_nms
 *    Input.  The minimal threshold for marking and eliminating a duplicate box.
 *            Must belong to [0, 1].
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions are met:
 *    - desc is NULL.
 *    - mode is not CNNL_DETECTION_OUTPUT_YOLOV3.
 *    - parameters do not meet requirements.
 */

cnnlStatus_t CNNL_WIN_API
cnnlSetYolov3DetectionOutputDescriptor_v2(cnnlDetectionOutputDescriptor_t desc,
                                          const cnnlDetectionOutputAlgo_t mode,
                                          const int num_batch,
                                          const int num_input,
                                          const int num_anchor,
                                          const int num_class,
                                          const int num_entry,
                                          const int num_keep,
                                          const int height_image,
                                          const int width_image,
                                          const int clip,
                                          const float scale_x_y,
                                          const float unnormalize_scale_h,
                                          const float unnormalize_scale_w,
                                          const float thresh_confidence,
                                          const float thresh_nms);

// Group:Detection Output
/*!
 *  @brief A function.
 *
 *  This function is used to set Yolov4 detection output descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  1. Call cnnlCreateDetectionOutputDescriptor() before using this function.
 *
 *  2. Call cnnlDestroyDetectionOutputDescriptor() when cnnlDetectionOutputDescriptor_t no longer
 *  needed.
 *
 *  @param[in] desc
 *    Input.  A pointer to the object of detection_output descriptor.
 *  @param[in] mode
 *    Input.  Algorithm of detection_output descriptor. Must be CNNL_DETECTION_OUTPUT_YOLOV4.
 *  @param[in] num_batch
 *    Input.  The number of batch for each feature map. Can be any positive integer as long as input
 *            tensor size is less than 2GB.
 *  @param[in] num_input
 *    Input.  The number of input feature maps. Must belong to [1, 7].
 *  @param[in] num_anchor
 *    Input.  The number of anchors, assuming same for all input feature maps.
 *            Must belong to [1, 8].
 *  @param[in] num_class
 *    Input.  The number of possible classes of each detected object.
 *            Can be any positive integer as long as input tensor size is less than 2GB.
 *  @param[in] num_entry
 *    Input.  The number of description dimensions for every predicted point in all the feature
 *            maps. Must be 5, where 5 entries represent x, y, w, h, objectness information.
 *  @param[in] num_keep
 *    Input.  The largest possible number of bounding boxes. Must belong to [1, 2048].
 *  @param[in] height_image
 *    Input.  The height of detection network input image. Must be greater than 0.
 *  @param[in] width_image
 *    Input.  The width of detection network input image. Must be greater than 0.
 *  @param[in] thresh_confidence
 *    Input.  The minimal threshold for marking a box as an object. Must belong to [0, 1].
 *  @param[in] thresh_nms
 *    Input.  The minimal threshold for marking and eliminating a duplicate box.
 *            Must belong to [0, 1].
 *  @param[in] scale_x_y_ptr
 *    Input.  The pointer of the scaling factor of each input data. The size equals to num_input.
 *  @param[in] beta
 *    Input.  The index part of the pow(d/c, beta) in the CNNL_GREEDY_NMS and
 *            CNNL_DIOU_NMS mode, where d denotes to the square of the distance
 *            between two center points of box, and c denotes to the square of
 *            the minimum diagonal length of circumscribed rectangle of two boxes.
 *            In the CNNL_GREEDY_NMS mode, beta is always equal to 0.6.
 *  @param[in] nms_type
 *    Input.  The enumeration of NMS mode.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions are met:
 *    - desc is NULL.
 *    - mode is not CNNL_DETECTION_OUTPUT_YOLOV4.
 *    - parameters do not meet requirements.
 */

cnnlStatus_t CNNL_WIN_API
cnnlSetYolov4DetectionOutputDescriptor(cnnlDetectionOutputDescriptor_t desc,
                                       cnnlDetectionOutputAlgo_t mode,
                                       int num_batch,
                                       int num_input,
                                       int num_anchor,
                                       int num_class,
                                       int num_entry,
                                       int num_keep,
                                       int height_image,
                                       int width_image,
                                       float thresh_confidence,
                                       float thresh_nms,
                                       const float *scale_x_y_ptr,
                                       float beta,
                                       cnnlNmsType_t nms_type);

// Group:Detection Output
/*!
 *  @brief A function.
 *
 *  This function is used to set Yolov5 detection output descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  1. Call ::cnnlCreateDetectionOutputDescriptor before using this function.
 *
 *  2. Call ::cnnlDestroyDetectionOutputDescriptor when ::cnnlDetectionOutputDescriptor_t no longer
 *  needed.
 *
 *  @param[in] desc
 *    Input.  A pointer to the object of detection_output descriptor.
 *  @param[in] mode
 *    Input.  Algorithm of detection_output descriptor. Must be CNNL_DETECTION_OUTPUT_YOLOV5.
 *  @param[in] num_batch
 *    Input.  The number of batch for each feature map. Can be any positive integer as long as input
 *            tensor size is less than 2GB.
 *  @param[in] num_input
 *    Input.  The number of input feature maps. Must belong to [1, 7].
 *  @param[in] num_anchor
 *    Input.  The number of anchors, assuming same for all input feature maps.
 *            Must belong to [1, 8].
 *  @param[in] num_class
 *    Input.  The number of possible classes of each detected object.
 *            Can be any positive integer as long as input tensor size is less than 2GB.
 *  @param[in] num_entry
 *    Input.  The number of description dimensions for every predicted point in all the feature
 *            maps. Must be 5, where 5 entries represent x, y, w, h, objectness information.
 *  @param[in] num_keep
 *    Input.  The largest possible number of bounding boxes. Must belong to [1, 2048].
 *  @param[in] height_image
 *    Input.  The height of detection network input image. Must be greater than 0.
 *  @param[in] width_image
 *    Input.  The width of detection network input image. Must be greater than 0.
 *  @param[in] thresh_confidence
 *    Input.  The minimal threshold for marking a box as an object. Must belong to [0, 1].
 *  @param[in] thresh_nms
 *    Input.  The minimal threshold for marking and eliminating a duplicate box.
 *            Must belong to [0, 1].
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions are met:
 *    - desc is NULL.
 *    - mode is not CNNL_DETECTION_OUTPUT_YOLOV5.
 *    - parameters do not meet requirements.
 */

cnnlStatus_t CNNL_WIN_API
cnnlSetYolov5DetectionOutputDescriptor(cnnlDetectionOutputDescriptor_t desc,
                                       cnnlDetectionOutputAlgo_t mode,
                                       int num_batch,
                                       int num_input,
                                       int num_anchor,
                                       int num_class,
                                       int num_entry,
                                       int num_keep,
                                       int height_image,
                                       int width_image,
                                       float thresh_confidence,
                                       float thresh_nms);

// Group:Detection Output
/*!
 *  @brief A function.
 *
 *  This function is used to set Yolov2 detection output descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  1. Call ::cnnlCreateDetectionOutputDescriptor before using this function.
 *
 *  2. Call ::cnnlDestroyDetectionOutputDescriptor when ::cnnlDetectionOutputDescriptor_t no longer
 *  needed.
 *
 *  @param[in]  detection_output_desc
 *    Input.  A pointer to the object of detection_output descriptor.
 *  @param[in]  mode
 *    Input.  Algorithm of detection_output descriptor. Must be CNNL_DETECTION_OUTPUT_YOLOV2.
 *  @param[in] num_class
 *    Input.  The number of possible classes of each detected object.
 *            Can be any positive integer as long as input tensor size is less than 2GB.
 *  @param[in] num_anchor
 *    Input.  The number of anchors, assuming same for all input feature maps.
 *            Must belong to [1, 8].
 *  @param[in] num_coords
 *    Input. The coordinates numbers of a bounding box. Must be 4.
 *  @param[in] num_batch
 *    Input.  The number of batch for each feature map. Can be any positive integer as long as input
 *            tensor size is less than 2GB.
 *  @param[in] confidence_thresh
 *    Input.  The minimal threshold for marking a box as an object. Must belong to [0, 1].
 *  @param[in] nms_thresh
 *    Input.  The minimal threshold for marking and eliminating a duplicate box.
 *            Must belong to [0, 1].
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions are met:
 *    - detection_output_desc is NULL.
 *    - mode is not CNNL_DETECTION_OUTPUT_YOLOV2.
 *    - parameters do not meet requirements.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetYolov2DetectionOutputDescriptor(cnnlDetectionOutputDescriptor_t detection_output_desc,
                                       cnnlDetectionOutputAlgo_t mode,
                                       int num_class,
                                       int num_anchor,
                                       int num_coords,
                                       int num_batch,
                                       float confidence_thresh,
                                       float nms_thresh);

// Group:Detection Output
/*!
 *  @brief A function.
 *
 *  This function is used to assign ssd detection output descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  The dependence is as follows:
 *
 *  1. Call ::cnnlCreateDetectionOutputDescriptor before using this function.
 *
 *  2. Call ::cnnlDestroyDetectionOutputDescriptor when ::cnnlDetectionOutputDescriptor_t is no
 *  longer needed.
 *
 *  @param[in]  detection_output_desc
 *    Input.  A pointer to the object of detection_output descriptor.
 *  @param[in]  mode
 *    Input.  Algorithm of detection output operation. Must be CNNL_DETECTION_OUTPUT_SSD.
 *  @param[in]  num_input
 *    Input.  The number of input tensor. Must be 2.
 *  @param[in]  num_batch
 *    Input.  The number of batch for each feature map. Can be any positive integer as long as input
 *            tensor size is less than 2GB.
 *  @param[in]  num_class
 *    Input.  The number of possible classes of each detected object.
 *            Can be any positive integer as long as input tensor size is less than 2GB.
 *  @param[in]  num_box
 *    Input.  The number of candidate bounding boxes. Can be any positive integer
 *            as long as input tensor size is less than 2GB.
 *  @param[in]  share_location
 *    Input.  Whether or not to share boxes' coordinates among different classes,
 *            0: not to share, 1: share.
 *  @param[in]  background_label_id
 *    Input.  The label ID of background. Must belong to [0, num_class - 1].
 *  @param[in]  code_type
 *    Input.  The type for decode.
 *    - 0: CodeType_CORNER.
 *    - 1: CodeType_CENTER_SIZE.
 *    - 2: CodeType_CORNER_SIZE.
 *  @param[in]  variance_encoded_in_target
 *    Input.  Whether or not to use variance when decoding, 0: not to use, 1: use.
 *  @param[in]  clip
 *    Input.  Whether or not to clip when decoding, 0: disable, 1: enable.
 *  @param[in]  num_topk
 *    Input.  The value of topK. Determine the number of boxes kept before NMS step.
 *  @param[in]  num_keep
 *    Input.  The largest possible number of bounding boxes. Must belong to [1, 2048].
 *  @param[in]  thresh_confidence
 *    Input.  The minimal threshold for marking a box as an object. Must belong to [0, 1].
 *  @param[in]  thresh_nms
 *    Input.  The minimal threshold for marking and eliminating a duplicate box.
 *            Must belong to [0, 1].
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions are met:
 *    - desc is NULL.
 *    - mode is not CNNL_DETECTION_OUTPUT_SSD.
 *    - parameters do not meet requirements.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetSsdDetectionOutputDescriptor(cnnlDetectionOutputDescriptor_t detection_output_desc,
                                    cnnlDetectionOutputAlgo_t mode,
                                    const int num_input,
                                    const int num_batch,
                                    const int num_class,
                                    const int num_box,
                                    const int share_location,
                                    const int background_label_id,
                                    const int code_type,
                                    const int variance_encoded_in_target,
                                    const int clip,
                                    const int num_topk,
                                    const int num_keep,
                                    const float thresh_confidence,
                                    const float thresh_nms);

// Group:Detection Output
/*!
 *  @brief A function.
 *
 *  This function is used to assign ssd detection output descriptor with parameters. Compared with
 *  ::cnnlSetSsdDetectionOutputDescriptor, ::cnnlSetSsdDetectionOutputDescriptor_v2 allows users
 *  to set the decaying factor \p eta and the minimal adaptive threshold \p min_thresh_nms during
 *  NMS.
 *
 *  **API Dependency**
 *
 *  The dependence is as follows:
 *
 *  1. Call ::cnnlCreateDetectionOutputDescriptor before using this function.
 *
 *  2. Call ::cnnlDestroyDetectionOutputDescriptor when ::cnnlDetectionOutputDescriptor_t is no
 *  longer needed.
 *
 *  @param[in]  detection_output_desc
 *    Input.  A pointer to the object of detection_output descriptor.
 *  @param[in]  mode
 *    Input.  Algorithm of detection output operation. Must be CNNL_DETECTION_OUTPUT_SSD.
 *  @param[in]  num_input
 *    Input.  The number of input tensor. Must be 2.
 *  @param[in]  num_batch
 *    Input.  The number of batch for each feature map. Can be any positive integer as long as input
 *            tensor size is less than 2GB.
 *  @param[in]  num_class
 *    Input.  The number of possible classes of each detected object.
 *            Can be any positive integer as long as input tensor size is less than 2GB.
 *  @param[in]  num_box
 *    Input.  The number of candidate bounding boxes. Can be any positive integer
 *            as long as input tensor size is less than 2GB.
 *  @param[in]  share_location
 *    Input.  Whether or not to share boxes' coordinates among different classes,
 *            0: not to share, 1: share.
 *  @param[in]  background_label_id
 *    Input.  The label ID of background. Must belong to [0, num_class - 1].
 *  @param[in]  code_type
 *    Input.  The type for decoding.
 *    - 0: CodeType_CORNER.
 *    - 1: CodeType_CENTER_SIZE.
 *    - 2: CodeType_CORNER_SIZE.
 *  @param[in]  variance_encoded_in_target
 *    Input.  Whether or not to use variance when decoding, 0: not to use, 1: use.
 *  @param[in]  clip
 *    Input.  Whether or not to clip when decoding, 0: disable, 1: enable.
 *  @param[in]  num_topk
 *    Input.  The value of topK. Determine the number of box kept before NMS step.
 *  @param[in]  num_keep
 *    Input.  The largest possible number of bounding boxes. Must belong to [1, 2048].
 *  @param[in]  thresh_confidence
 *    Input.  The minimal threshold for marking a box as an object. Must belong to [0, 1].
 *  @param[in]  thresh_nms
 *    Input.  The minimal threshold for marking and eliminating a duplicate box.
 *            Must belong to [0, 1].
 *  @param[in]  eta
 *    Input.  The decaying factor used to adaptively update thresh_nms during nms.
 *            Must belong to (0, 1].
 *  @param[in]  min_thresh_nms
 *    Input.  When thresh_nms updated by eta is smaller than or equal to min_thresh_nms, thresh_nms
 *            will no longer be updated.
 *            Must belong to [0, 1].
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions are met:
 *    - desc is NULL.
 *    - mode is not CNNL_DETECTION_OUTPUT_SSD.
 *    - parameters do not meet requirements.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetSsdDetectionOutputDescriptor_v2(cnnlDetectionOutputDescriptor_t detection_output_desc,
                                       cnnlDetectionOutputAlgo_t mode,
                                       const int num_input,
                                       const int num_batch,
                                       const int num_class,
                                       const int num_box,
                                       const int share_location,
                                       const int background_label_id,
                                       const int code_type,
                                       const int variance_encoded_in_target,
                                       const int clip,
                                       const int num_topk,
                                       const int num_keep,
                                       const float thresh_confidence,
                                       const float thresh_nms,
                                       const float eta,
                                       const float min_thresh_nms);
// Group:Detection Output
/*!
 *  @brief A function.
 *
 *  This function is used to assign retinanet detection output descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  The dependence is as follow:
 *
 *  1. Call ::cnnlCreateDetectionOutputDescriptor before using this function.
 *
 *  2. Call ::cnnlDestroyDetectionOutputDescriptor when ::cnnlDetectionOutputDescriptor_t is no
 *  longer needed.
 *
 *  @param[in]  detection_output_desc
 *    Input.  A pointer to the object of detection_output descriptor.
 *  @param[in]  mode
 *    Input.  Algorithm of detection_output descriptor. Must be CNNL_DETECTION_OUTPUT_RETINANET.
 *  @param[in]  num_input
 *    Input.  The number of input tensor. Must be 10.
 *  @param[in]  num_class
 *    Input.  The number of possible classes of each detected object. Must be 80.
 *  @param[in]  num_anchor
 *    Input.  The number of possible anchors of each detected object. Must be 9.
 *  @param[in]  num_topk
 *    Input.  The value of topK. Determine the number of boxes kept before NMS step.
 *            Must belong to (0, 1000].
 *  @param[in]  thresh_confidence
 *    Input.  The minimal threshold for marking a box as an object. Must belong to (0, 1).
 *  @param[in]  thresh_nms
 *    Input.  The minimal threshold for marking and eliminating a duplicate box.
 *            Must belong to (0, 1).
 *  @param[in]  num_detection
 *    Input.  The largest possible number of bounding boxes. Must belong to (0, num_topk].
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions are met:
 *    - desc is NULL.
 *    - mode is not CNNL_DETECTION_OUTPUT_RETINANET.
 *    - parameters do not meet requirements.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetRetinaDetectionOutputDescriptor(cnnlDetectionOutputDescriptor_t detection_output_desc,
                                       cnnlDetectionOutputAlgo_t mode,
                                       const int num_input,
                                       const int num_class,
                                       const int num_anchor,
                                       const int num_topk,
                                       const float thresh_confidence,
                                       const float thresh_nms,
                                       const int num_detection);

// Group:Detection Output
/*!
 *  @brief A function.
 *
 *  This function is used to assign refinedet detection output descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  The dependence is as follows:
 *
 *  1. Call ::cnnlCreateDetectionOutputDescriptor before using this function.
 *
 *  2. Call ::cnnlDestroyDetectionOutputDescriptor when ::cnnlDetectionOutputDescriptor_t is no
 *  longer needed.
 *
 *  @param[in]  detection_output_desc
 *    Input.  A pointer to the object of detection_output descriptor.
 *  @param[in]  mode
 *    Input.  Detection output algorithm used, must be CNNL_DETECTION_OUTPUT_REFINEDET.
 *  @param[in]  num_input
 *    Input.  The number of input tensor. Must be 4.
 *  @param[in]  num_batch
 *    Input.  The number of batch for each feature map. Can be any positive integer as long as input
 *            tensor size is less than 2GB.
 *  @param[in]  num_class
 *    Input.  The number of possible classes of each detected object.
 *            Can be any positive integer as long as input tensor size is less than 2GB.
 *  @param[in]  num_box
 *    Input.  The number of candidate bounding boxes. Can be any positive integer
 *            as long as input tensor size is less than 2GB.
 *  @param[in]  share_location
 *    Input.  Whether or not to share boxes' coordinates among different classes,
 *            0: not to share, 1: share.
 *  @param[in]  background_label_id
 *    Input.  The label ID of background. Must belong to [0, num_class - 1].
 *  @param[in]  code_type
 *    Input.  The type for decoding.
 *    - 0: CodeType_CORNER.
 *    - 1: CodeType_CENTER_SIZE.
 *    - 2: CodeType_CORNER_SIZE.
 *  @param[in]  variance_encoded_in_target
 *    Input.  Whether or not to use variance when decoding, 0: not to use, 1: use.
 *  @param[in]  clip
 *    Input.  Whether or not to clip when decoding, 0: disable, 1: enable.
 *  @param[in]  num_topk
 *    Input.  The value of topK. Determine the number of boxes kept before NMS step.
 *  @param[in]  num_keep
 *    Input.  The largest possible number of bounding boxes. Must belong to [1, 2048].
 *  @param[in]  thresh_confidence
 *    Input.  The minimal threshold for marking a box as an object. Must belong to [0, 1].
 *  @param[in]  thresh_nms
 *    Input.  The minimal threshold for marking and eliminating a duplicate box.
 *            Must belong to [0, 1].
 *  @param[in]  object_score
 *    Input.  The minimal threshold for background label and object label. Must belong to [0, 1].
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions are met:
 *    - desc is NULL.
 *    - mode is not CNNL_DETECTION_OUTPUT_REFINEDET.
 *    - parameters do not meet requirements.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetRefinedetDetectionOutputDescriptor(cnnlDetectionOutputDescriptor_t detection_output_desc,
                                          cnnlDetectionOutputAlgo_t mode,
                                          const int num_input,
                                          const int num_batch,
                                          const int num_class,
                                          const int num_box,
                                          const int share_location,
                                          const int background_label_id,
                                          const int code_type,
                                          const int variance_encoded_in_target,
                                          const int clip,
                                          const int num_topk,
                                          const int num_keep,
                                          const float thresh_confidence,
                                          const float thresh_nms,
                                          const float object_score);

// Group:Detection Output
/*!
 *  @brief A function.
 *
 *  This function is used to assign refinedet detection output descriptor with parameters. Compared
 *  with ::cnnlSetRefinedetDetectionOutputDescriptor,
 *  ::cnnlSetRefinedetDetectionOutputDescriptor_v2 allows users to set the decaying factor \p eta
 *  and the minimal adaptive threshold \p min_thresh_nms during NMS.
 *
 *  **API Dependency**
 *
 *  The dependence is as follows:
 *
 *  1. Call ::cnnlCreateDetectionOutputDescriptor before using this function.
 *
 *  2. Call ::cnnlDestroyDetectionOutputDescriptor when ::cnnlDetectionOutputDescriptor_t no longer
 *  needed.
 *
 *  @param[in]  detection_output_desc
 *    Input.  A pointer to the object of detection_output descriptor.
 *  @param[in]  mode
 *    Input.  Detection output algorithm used, must be CNNL_DETECTION_OUTPUT_REFINEDET.
 *  @param[in]  num_input
 *    Input.  The number of input tensor. Must be 4.
 *  @param[in]  num_batch
 *    Input.  The number of batch for each feature map. Can be any positive integer as long as input
 *            tensor size is less than 2GB.
 *  @param[in]  num_class
 *    Input.  The number of possible classes of each detected object.
 *            Can be any positive integer as long as input tensor size is less than 2GB.
 *  @param[in]  num_box
 *    Input.  The number of candidate bounding boxes. Can be any positive integer
 *            as long as input tensor size is less than 2GB.
 *  @param[in]  share_location
 *    Input.  Whether or not to share boxes' coordinates among different classes,
 *            0: not to share, 1: share.
 *  @param[in]  background_label_id
 *    Input.  The label ID of background. Must belong to [0, num_class - 1].
 *  @param[in]  code_type
 *    Input.  The type for decoding.
 *    - 0: CodeType_CORNER.
 *    - 1: CodeType_CENTER_SIZE.
 *    - 2: CodeType_CORNER_SIZE.
 *  @param[in]  variance_encoded_in_target
 *    Input.  Whether or not to use variance when decoding, 0: not to use, 1: use.
 *  @param[in]  clip
 *    Input.  Whether or not to clip when decoding, 0: disable, 1: enable.
 *  @param[in]  num_topk
 *    Input.  The value of topK. Determine the number of boxes kept before NMS step.
 *  @param[in]  num_keep
 *    Input.  The largest possible number of bounding boxes. Must belong to [1, 2048].
 *  @param[in]  thresh_confidence
 *    Input.  The minimal threshold for marking a box as an object. Must belong to [0, 1].
 *  @param[in]  thresh_nms
 *    Input.  The minimal threshold for marking and eliminating a duplicate box.
 *            Must belong to [0, 1].
 *  @param[in]  eta
 *    Input.  The decaying factor used to adaptively update thresh_nms during nms.
 *            Must belong to (0, 1].
 *  @param[in]  min_thresh_nms
 *    Input.  When thresh_nms updated by eta is smaller than or equal to min_thresh_nms, thresh_nms
 *            will no longer be updated.
 *            Must belong to [0, 1].
 *  @param[in]  object_score
 *    Input.  The minimal threshold for background label and object label. Must belong to [0, 1].
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions are met:
 *    - desc is NULL.
 *    - mode is not CNNL_DETECTION_OUTPUT_REFINEDET.
 *    - parameters do not meet requirements.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetRefinedetDetectionOutputDescriptor_v2(cnnlDetectionOutputDescriptor_t detection_output_desc,
                                             cnnlDetectionOutputAlgo_t mode,
                                             const int num_input,
                                             const int num_batch,
                                             const int num_class,
                                             const int num_box,
                                             const int share_location,
                                             const int background_label_id,
                                             const int code_type,
                                             const int variance_encoded_in_target,
                                             const int clip,
                                             const int num_topk,
                                             const int num_keep,
                                             const float thresh_confidence,
                                             const float thresh_nms,
                                             const float eta,
                                             const float min_thresh_nms,
                                             const float object_score);

// Group:Detection Output
/*!
 *  @brief A function.
 *
 *  This function is used to set FasterRCNN detection output descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  1. Call ::cnnlCreateDetectionOutputDescriptor before using this function.
 *
 *  2. Call ::cnnlDestroyDetectionOutputDescriptor when ::cnnlDetectionOutputDescriptor_t no longer
 *  needed.
 *
 *  @param[in,out] detection_output_desc
 *    Input.  A pointer to the object of detection_output descriptor.
 *  @param[in] algo
 *    Input.  Algorithm of detection_output descriptor. Must be CNNL_DETECTION_OUTPUT_FASTERRCNN.
 *  @param[in] num_input
 *    Input.  The number of input tensor. Must be 3.
 *  @param[in] num_batch
 *    Input.  The number of batch for each feature map. Can be any positive integer as long as input
 *            tensor size is less than 2GB.
 *  @param[in] num_box
 *    Input.  The number of possible classes of each detected object. Can be any positive integer
 *            as long as input tensor size is less than 2GB.
 *  @param[in] num_class
 *    Input.  The number of possible classes of each detected object.
 *            Can be any positive integer as long as input tensor size is less than 2GB.
 *  @param[in] height_image
 *    Input.  The height of detection network input image. Must be greater than 0.
 *  @param[in] width_image
 *    Input.  The width of detection network input image. Must be greater than 0.
 *  @param[in] scale
 *    Input.  The scale of rois. Must be greater than 0.
 *  @param[in] thresh_nms
 *    Input.  The minimal threshold for marking and eliminating a duplicate box.
 *            Must belong to [0, 1].
 *  @param[in] thresh_confidence
 *    Input.  The minimal threshold for marking a box as an object. Must belong to [0, 1].
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions are met:
 *    - detection_output_desc is NULL.
 *    - mode is not CNNL_DETECTION_OUTPUT_FASTERRCNN.
 *    - parameters do not meet requirements.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetFasterRCNNDetectionOutputDescriptor(cnnlDetectionOutputDescriptor_t detection_output_desc,
                                           cnnlDetectionOutputAlgo_t algo,
                                           int num_input,
                                           int num_batch,
                                           int num_box,
                                           int num_class,
                                           int height_image,
                                           int width_image,
                                           float scale,
                                           float thresh_nms,
                                           float thresh_confidence);

// Group:Detection Output
/*!
 *  @brief A function.
 *
 *  This function is used to destroy detection output descriptor, which contains the SSD,
 *  REFINEDET，RETINANET, YOLOV2, YOLOV3 Faster-RCNN, YOLOV4, and YOLOV5.
 *
 *  **API Dependency**
 *
 *  This function must be used if you call the ::cnnlCreateDetectionOutputDescriptor function.
 *
 *  @param[in] detection_output_desc
 *    Input.  A pointer to the struct of detection output descriptor.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_EXECUTION_FAILED
 *    One of the following conditions are met:
 *      - detection_output_desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlDestroyDetectionOutputDescriptor(cnnlDetectionOutputDescriptor_t detection_output_desc);

// Group:Detection Output
/*!
 *  @brief A function
 *
 *  This function is used to create an operation of detection output. The detection output operator
 *  followed the object detect convolution input network backbone, and the pipeline
 *  includes decode, filter, nms and topk (if need output topk bbx with score). Users can choose the
 *  different mode to use different detection output operation. Currently the detection output mode
 *  supports SSD, REFINEDET, RETINANET, Yolov2, Yolov3 and Faster-RCNN. More detection output modes
 *  will be supported in the future.
 *
 *  **DataType**
 *
 *    - input: float, half.
 *
 *    - output: float, half.
 *
 *    - bias: float, half.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as follow:
 *
 *    1.The function named ::cnnlCreateDetectionOutputDescriptor needs to be called before this
 *
 *    function.
 *
 *    2.The function like ::cnnlSetYolov3DetectionOutputDescriptor(depends on the used algorithm)
 *
 *      needs to be called before this function.
 *
 *    3.The function named ::cnnlDestroyDetectionOutputDescriptor needs to be called after this
 *
 *    function.
 *
 *  @param[in] handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           detection_output operation.
 *  @param[in] detection_output_desc
 *    Input. Struct with information of detection output parameter.
 *  @param[in] input_desc
 *    Input. Pointer to the host memory that stores an array of cnnlTensorDescriptors which holds
 *    dimension, datatype, and layout of input tensors. The meaning of tensor descriptors
 *    vary based on different ::cnnlDetectionOutputAlgo_t:
 *    - SSD: input_desc contains 2 elements. The first tensor means bbox prediction. When
 *    share_location = 1, the shape of tensor must be [num_batch, 4, num_box]. When
 *    share_location = 0, the shape of tensor can be [num_batch, num_class * 4, num_box] or
 *    [num_batch, num_class, 4, num_box]. The second tensor means bbox class confidence. The
 *    shape of tensor must be [num_batch, num_class, num_box].
 *    See ::cnnlSetSsdDetectionOutputDescriptor for detailed parameter limitation.
 *    - YOLOV2: input_desc contains 1 element. The tensor means bbox coordinates and class
 *    prediction. The shape of tensor must be [num_batch, H, W, num_channel], where
 *    num_channel = num_anchor * (num_classes + 5). H must be equal to W.
 *    See ::cnnlSetYolov2DetectionOutputDescriptor for detailed parameter limitation.
 *    - YOLOV3/4/5: input_desc contains \p input_num elements. All tensors share the same
 *    physical meaning, that is, bbox coordinates and class prediction. The shape of tensors
 *    follow the pattern [num_batch, H, W, num_channel]. All tensor must have the same
 *    \p num_batch and \p num_channel, where num_channel = num_anchor * (num_classes + 5).
 *    This operation assumes all input tensors have same \p num_anchor.
 *    See ::cnnlSetYolov3DetectionOutputDescriptor, ::cnnlSetYolov4DetectionOutputDescriptor,
 *    or ::cnnlSetYolov5DetectionOutputDescriptor for detailed parameter limitation.
 *    - FASTERRCNN: input_desc contains 3 elements. The first tensor means bbox predition.
 *    The shape of tensor must be [num_batch, num_class, 4, num_box]. The second tensor means
 *    class prediction. The shape of tensor must be [num_batch, num_class, 1, num_box]. The
 *    third tensor means region of interest(roi). The shape of tensor must be
 *    [num_batch, 1, 5, num_box], where the 5 entries mean x1, y1, x2, y2, and placeholder.
 *    (x1, y1) and (x2, y2) represent the top-left and bottom-right points of a bbox. The
 *    fifth value is currently not used.
 *    See ::cnnlSetFasterRCNNDetectionOutputDescriptor for detailed parameter limitation.
 *    - REFINEDET: input_desc contains 4 elements. The first two tensors are the same as
 *    input_desc of SSD mode. The third tensor means anchor refine module(arm) location
 *    prediction. When share_location = 1, the shape of tensor must be
 *    [num_batch, 4, num_box]. When share_location = 0, the shape of tensor can be
 *    [num_batch, num_class, 4, num_box] or [num_batch, num_class * 4, num_box],
 *    but the number of dimension must be equal to that of the first tensor.
 *    The fourth tensor means arm confidence prediction. The shape of tensor must be
 *    [num_batch, 2, num_box]. See ::cnnlSetRefinedetDetectionOutputDescriptor for detailed
 *    parameter limitation.
 *    - RETINANET: input_desc contains 3 elements. The first tensor is the class prediction.
 *    The shape of this tensor must be [num_batch, num_anchor * num_class, H, W].
 *    H * W must be smaller than 17920.
 *    The second tensor is the bbox coordinates. The shape of this tensor must be
 *    [num_batch, num_anchor * (x1, y1, x2, y2), H, W], (x1, y1, x2, y2) represents
 *    the top-left and bottom-right coordinates of a bbox. The third tensor is the anchor
 *    tensor, which is used as the bias_desc.
 *    See ::cnnlSetRetinaDetectionOutputDescriptor for detailed parameter limitation.
 *  @param[in] input
 *    Input. Pointer to the host memory that stores an array of pointers to the device memory. The
 *           order of elements in \p input pointer must be consistent with the order of
 *           cnnlTensorDescriptors in the \p input_desc pointer.
 *  @param[in] bias_desc
 *    Input. Descriptor of bias tensor, including anchor height and width. The shape of
 *    bias tensor varies based on different ::cnnlDetectionOutputAlgo_t:
 *    - SSD: bias tensor represents prior box, which maintains constant for different batch.
 *    The shape of tensor must be [2, 4, num_box].
 *    - YOLOV2: bias tensor represents chimeric anchor and coordinates data. The shape of
 *    tensor must be [4, num_anchor, H, W]. where 4 entries represents x-coordinate,
 *    y-coordinate, anchor width, anchor height. The data is generated as follows:
 *      let anchor_data.shape() = [num_anchor, 2], where 2 entries represents width and
 *      height. Then:
          @verbatim
          for (aidx: 0 ~ num_anchor - 1)
            for (hidx: 0 ~ H - 1)
              for (widx: 0 ~ W - 1)
                bias_data[0][aidx][hidx][widx] = widx
                bias_data[1][aidx][hidx][widx] = hidx
                bias_data[2][aidx][hidx][widx] = anchor_data[aidx][0]
                bias_data[3][aidx][hidx][widx] = anchor_data[aidx][1]
          @endverbatim
 *    - YOLOV3/4/5: bias tensor represents anchor data, which maintains constant for
 *    differnet batch. The shape of tensor can be [num_input, num_anchor, 2] or
 *    [num_input * num_anchor * 2], where 2 entries represents width and height.
 *    - FASTERRCNN: bias tensor not used. Pass NULL to this parameter.
 *    - REFINEDET: Same with SSD.
 *    - RETINANET: bias tensor represents anchor box. The shape is
 *    [5, anchor_num, (x1, y1, x2, y2)], where (x1, y1, x2, y2) represents
 *    the top-left and bottom-right coordinates of a bbox.
 *  @param[in] bias
 *    Input. MLU tensor, a pointer to device anchor data. Pass NULL to this parameter when mode is
 *           CNNL_DETECTION_OUTPUT_FASTERRCNN.
 *  @param[in] workspace
 *    Input. A pointer to workspace buffer.
 *  @param[in] workspace_size
 *    Input. The size of workspace.
 *  @param[out] output_desc
 *    Input. Descriptor of output tensor, including dimension, datatype and layout. The shape of
 *    tensor can be [num_batch, num_element, max_possible_num_box](YOLOV2 only) or
 *    [num_batch, num_element * max_possible_num_box](YOLOV2 only) or
 *    [num_batch, max_possible_num_box, num_element](others) or
 *    [num_batch, max_possible_num_box * num_element](others), where num_element equals 6 for
 *    CNNL_DETECTION_OUTPUT_FASTERRCNN mode, 7 for others, and where
 *    max_possible_num_box equals:
 *    - SSD: the smaller one between \p num_keep and \p num_box.
 *    - YOLOV2: \p 256.
 *    - YOLOV2/3/4: the smaller one between \p num_keep and
 *    sum(h[i] * w[i] * num_anchor * num_class), where hi/wi represent the height and width
 *    of input tensor.
 *    - FASTERRCNN: \p num_box * \p num_class.
 *    - REFINEDET:  the smaller one between \p num_keep and \p num_box.
 *    - RETINANET: \p num_detection
 *    Valid bbox will be stored at the beginning of corresponding device memory of every
 *    batch. If number of valid bbox is less than max_possible_num_box, the remaining device
 *    memory maintains uninitialized. User can use valid bbox number stored in output_size
 *    pointer to gather data of valid bbox. 7 entries represent
 *    [batch_id, class_id, score, x1, y1, x2, y2], where (x1, y1) and (x2, y2) represent the
 *    top-left and bottom-right point of a bbox. Result of CNNL_DETECTION_OUTPUT_FASTERRCNN
 *    mode does not have \p batch_id.
 *  @param[out] output
 *    Input. MLU tensor, a pointer to device output data.
 *  @param[out] output_size
 *    Input. 1-D MLU tensor, a pointer to device output size. It stores [batch] number of
 *           UINT32-type values, representing the actual number of bounding boxes after detection
 *           output operation for every batch of input.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions must be met:
 *    - Handle is NULL.
 *    - input is NULL.
 *    - output is NULL.
 *    - parameters exceed limitation.
 */
cnnlStatus_t CNNL_WIN_API
cnnlDetectionOutput(cnnlHandle_t handle,
                    const cnnlDetectionOutputDescriptor_t detection_output_desc,
                    const cnnlTensorDescriptor_t input_desc[],
                    void **input,
                    const cnnlTensorDescriptor_t bias_desc,
                    void *bias,
                    void *workspace,
                    size_t workspace_size,
                    const cnnlTensorDescriptor_t output_desc,
                    void *output,
                    void *output_size);

// Group:Detection Output
/*!
 *  @brief A function
 *
 *  This function is used to create an operation of detection output. The detection output operator
 *  followed the object detect convolution input network backbone, and the pipeline
 *  includes decode, filter, nms and topk (if need output topk bbx with score). Users can choose the
 *  different mode to use different detection output operation. Currently the detection output mode
 *  supports SSD, REFINEDET, RETINANET, Yolov2, Yolov3 and Faster-RCNN. More detection output modes
 *  will be supported in the future.
 *
 *  Compared with ::cnnlDetectionOutput, this function allows users to pass output_size_desc to
 *  indicate the number of elements stored in \p output_size tensor.
 *
 *  **DataType**
 *
 *    - input: float, half.
 *
 *    - output: float, half.
 *
 *    - bias: float, half.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as follow:
 *
 *    1.The function named ::cnnlCreateDetectionOutputDescriptor needs to be called before this
 *
 *    function.
 *
 *    2.The function like ::cnnlSetYolov3DetectionOutputDescriptor(depends on the used algorithm)
 *
 *      needs to be called before this function.
 *
 *    3.The function named ::cnnlDestroyDetectionOutputDescriptor needs to be called after this
 *
 *    function.
 *
 *  @param[in] handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           detection_output operation.
 *  @param[in] detection_output_desc
 *    Input. Struct with information of detection output parameter.
 *  @param[in] input_desc
 *    Input. Pointer to the host memory that stores an array of cnnlTensorDescriptors which holds
 *    dimension, datatype, and layout of input tensors. The meaning of tensor descriptors
 *    vary based on different ::cnnlDetectionOutputAlgo_t:
 *    - SSD: input_desc contains 2 elements. The first tensor means bbox prediction. When
 *    share_location = 1, the shape of tensor must be [num_batch, 4, num_box]. When
 *    share_location = 0, the shape of tensor can be [num_batch, num_class * 4, num_box] or
 *    [num_batch, num_class, 4, num_box]. The second tensor means bbox class confidence. The
 *    shape of tensor must be [num_batch, num_class, num_box].
 *    See ::cnnlSetSsdDetectionOutputDescriptor for detailed parameter limitation.
 *    - YOLOV2: input_desc contains 1 element. The tensor means bbox coordinates and class
 *    prediction. The shape of tensor must be [num_batch, H, W, num_channel], where
 *    num_channel = num_anchor * (num_classes + 5). H must be equal to W.
 *    See ::cnnlSetYolov2DetectionOutputDescriptor for detailed parameter limitation.
 *    - YOLOV3/4/5: input_desc contains \p input_num elements. All tensors share the same
 *    physical meaning, that is, bbox coordinates and class prediction. The shape of tensors
 *    follow the pattern [num_batch, H, W, num_channel]. All tensor must have the same
 *    \p num_batch and \p num_channel, where num_channel = num_anchor * (num_classes + 5).
 *    This operation assumes all input tensors have same \p num_anchor.
 *    See ::cnnlSetYolov3DetectionOutputDescriptor, ::cnnlSetYolov4DetectionOutputDescriptor,
 *    or ::cnnlSetYolov5DetectionOutputDescriptor for detailed parameter limitation.
 *    - FASTERRCNN: input_desc contains 3 elements. The first tensor means bbox predition.
 *    The shape of tensor must be [num_batch, num_class, 4, num_box]. The second tensor means
 *    class prediction. The shape of tensor must be [num_batch, num_class, 1, num_box]. The
 *    third tensor means region of interest(roi). The shape of tensor must be
 *    [num_batch, 1, 5, num_box], where the 5 entries mean x1, y1, x2, y2, and placeholder.
 *    (x1, y1) and (x2, y2) represent the top-left and bottom-right points of a bbox. The
 *    fifth value is currently not used.
 *    See ::cnnlSetFasterRCNNDetectionOutputDescriptor for detailed parameter limitation.
 *    - REFINEDET: input_desc contains 4 elements. The first two tensors are the same as
 *    input_desc of SSD mode. The third tensor means anchor refine module(arm) location
 *    prediction. When share_location = 1, the shape of tensor must be
 *    [num_batch, 4, num_box]. When share_location = 0, the shape of tensor can be
 *    [num_batch, num_class, 4, num_box] or [num_batch, num_class * 4, num_box],
 *    but the number of dimension must be equal to that of the first tensor.
 *    The fourth tensor means arm confidence prediction. The shape of tensor must be
 *    [num_batch, 2, num_box]. See ::cnnlSetRefinedetDetectionOutputDescriptor for detailed
 *    parameter limitation.
 *    - RETINANET: input_desc contains 3 elements. The first tensor is the class prediction.
 *    The shape of this tensor must be [num_batch, num_anchor * num_class, H, W].
 *    H * W must be smaller than 17920.
 *    The second tensor is the bbox coordinates. The shape of this tensor must be
 *    [num_batch, num_anchor * (x1, y1, x2, y2), H, W], (x1, y1, x2, y2) represents
 *    the top-left and bottom-right coordinates of a bbox. The third tensor is the anchor
 *    tensor, which is used as the bias_desc.
 *    See ::cnnlSetRetinaDetectionOutputDescriptor for detailed parameter limitation.
 *  @param[in] input
 *    Input. Pointer to the host memory that stores an array of pointers to the device memory. The
 *           order of elements in \p input pointer must be consistent with the order of
 *           cnnlTensorDescriptors in the \p input_desc pointer.
 *  @param[in] bias_desc
 *    Input. Descriptor of bias tensor, including anchor height and width. The shape of
 *    bias tensor varies based on different ::cnnlDetectionOutputAlgo_t:
 *    - SSD: bias tensor represents prior box, which maintains constant for different batch.
 *    The shape of tensor must be [2, 4, num_box].
 *    - YOLOV2: bias tensor represents chimeric anchor and coordinates data. The shape of
 *    tensor must be [4, num_anchor, H, W]. where 4 entries represents x-coordinate,
 *    y-coordinate, anchor width, anchor height. The data is generated as follows:
 *      let anchor_data.shape() = [num_anchor, 2], where 2 entries represents width and
 *      height. Then:
          @verbatim
          for (aidx: 0 ~ num_anchor - 1)
            for (hidx: 0 ~ H - 1)
              for (widx: 0 ~ W - 1)
                bias_data[0][aidx][hidx][widx] = widx
                bias_data[1][aidx][hidx][widx] = hidx
                bias_data[2][aidx][hidx][widx] = anchor_data[aidx][0]
                bias_data[3][aidx][hidx][widx] = anchor_data[aidx][1]
          @endverbatim
 *    - YOLOV3/4/5: bias tensor represents anchor data, which maintains constant for
 *    differnet batch. The shape of tensor can be [num_input, num_anchor, 2] or
 *    [num_input * num_anchor * 2], where 2 entries represents width and height.
 *    - FASTERRCNN: bias tensor not used. Pass NULL to this parameter.
 *    - REFINEDET: Same with SSD.
 *    - RETINANET: bias tensor represents anchor box. The shape is
 *    [5, anchor_num, (x1, y1, x2, y2)], where (x1, y1, x2, y2) represents
 *    the top-left and bottom-right coordinates of a bbox.
 *  @param[in] bias
 *    Input. MLU tensor, a pointer to device anchor data. Pass NULL to this parameter when mode is
 *           CNNL_DETECTION_OUTPUT_FASTERRCNN.
 *  @param[in] workspace
 *    Input. A pointer to workspace buffer.
 *  @param[in] workspace_size
 *    Input. The size of workspace.
 *  @param[out] output_desc
 *    Output. Descriptor of output tensor, including dimension, datatype and layout. The shape of
 *    tensor can be [num_batch, num_element, max_possible_num_box](YOLOV2 only) or
 *    [num_batch, num_element * max_possible_num_box](YOLOV2 only) or
 *    [num_batch, max_possible_num_box, num_element](others) or
 *    [num_batch, max_possible_num_box * num_element](others), where num_element equals 6 for
 *    CNNL_DETECTION_OUTPUT_FASTERRCNN mode, 7 for others, and where
 *    max_possible_num_box equals:
 *    - SSD: the smaller one between \p num_keep and \p num_box.
 *    - YOLOV2: \p 256.
 *    - YOLOV2/3/4: the smaller one between \p num_keep and
 *    sum(h[i] * w[i] * num_anchor * num_class), where hi/wi represent the height and width
 *    of input tensor.
 *    - FASTERRCNN: \p num_box * \p num_class.
 *    - REFINEDET:  the smaller one between \p num_keep and \p num_box.
 *    - RETINANET: \p num_detection
 *    Valid bbox will be stored at the beginning of corresponding device memory of every
 *    batch. If number of valid bbox is less than max_possible_num_box, the remaining device
 *    memory maintains uninitialized. User can use valid bbox number stored in output_size
 *    pointer to gather data of valid bbox. 7 entries represent
 *    [batch_id, class_id, score, x1, y1, x2, y2], where (x1, y1) and (x2, y2) represent the
 *    top-left and bottom-right point of a bbox. Result of CNNL_DETECTION_OUTPUT_FASTERRCNN
 *    mode does not have \p batch_id.
 *  @param[out] output
 *    Input. MLU tensor, a pointer to device output data.
 *  @param[out] output_size_desc
 *    Output. Descriptor of output_size tensor, including dimension, datatype and layout. The shape
 *    of tensor can be [num_batch] or [1](only for SSD). The data type must be INT32. When num_batch
 *    is greater than 1 but shape of output_size is [1], all results of different batch will be
 *    merged and the value stored in output_size will be the sum of the result number of all
 *    batches.
 *  @param[out] output_size
 *    Input. 1-D MLU tensor, a pointer to device output size. It stores [batch] number of
 *           UINT32-type values, representing the actual number of bounding boxes after detection
 *           output operation for every batch of input.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions must be met:
 *    - Handle is NULL.
 *    - input is NULL.
 *    - output is NULL.
 *    - parameters exceed limitation.
 */
cnnlStatus_t CNNL_WIN_API
cnnlDetectionOutput_v2(cnnlHandle_t handle,
                       const cnnlDetectionOutputDescriptor_t detection_output_desc,
                       const cnnlTensorDescriptor_t input_desc[],
                       void **input,
                       const cnnlTensorDescriptor_t bias_desc,
                       void *bias,
                       void *workspace,
                       size_t workspace_size,
                       const cnnlTensorDescriptor_t output_desc,
                       void *output,
                       const cnnlTensorDescriptor_t output_size_desc,
                       void *output_size);

// Group:Detection Output
/*!
 *  @brief A function.
 *  This function is used to get extra space size that needed in detection output operation.
 *
 *  **Scale Limitation**
 *
 *  len_input must be greater than 0.
 *
 *  @param[in]  handle
 *    Input.  Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *            detection_output operation.
 *  @param[in]  desc
 *    Input.  Parameter description of detection output operator.
 *  @param[in]  input_desc
 *    Input.  Tensor descriptor of input.
 *  @param[in]  mode
 *    Input.  Detection output algorithm used.
 *  @param[out] size
 *    Output. Size of workspace.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions are met:
 *    - handle is NULL.
 *    - desc is NULL.
 *    - mode does not belong to any of cnnlDetectionOutputAlgo_t definition.
 *    - input_desc is NULL.
 *    - input_desc valid elements is NULL.
 *    - size is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlGetDetectionOutputWorkspaceSize(cnnlHandle_t handle,
                                    const cnnlDetectionOutputDescriptor_t desc,
                                    const cnnlTensorDescriptor_t *input_desc,
                                    cnnlDetectionOutputAlgo_t mode,
                                    size_t *size);

/******************************************************************************
 * Cambricon CNNL OP: Proposal
 ******************************************************************************/
/*! The descriptor of Proposal function the holds proposal parameters. */
typedef struct cnnlProposalStruct *cnnlProposalDescriptor_t;

// Group:Proposal
/*!
 * @brief A function generates proposal boxes from scores and bounding box
 * prediction from region proposal network.
 *
 * **Datatype**
 *
 *  - input: float, half.
 *
 *  - output: float, half.
 *
 * **Attention:**
 *
 *  - Datatype of input and output must be the same.
 *
 * **Scale Limitation**
 *
 *  According to proposal op, the parameters must satisfy following conditions:
 *
 *  batch > 0, height > 0, width > 0, anchor_num > 0.
 *
 *  im_h > 0, im_w > 0, im_min_h >= 0, im_min_w >= 0, top_thresh > 0.
 *
 *  nms_num is limited in (0, 2000].
 *
 *  anchor_num * width * height must be smaller than 10^6.
 *
 *  @param[in] handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           proposal operation.
 *  @param[out] new_box_desc
 *    Input. A descriptor of new_box, each contains dimension of
 *    [batch_size, 5, 1, nms_num].
 *  @param[out] new_box
 *    Output. A pointer to device new proposal boxes.
 *  @param[in] bbox_pred_desc
 *    Input. A descriptor of bbox_pred, each contains dimension of
 *    [batch_size, 4, 1, anchor_num * width * height].
 *  @param[in] bbox_pred
 *    Input. A pointer to device bounding box predictions.
 *  @param[in] scores_desc
 *    Input. A descriptor of scores, each contains dimension of
 *    [batch_size, 2, 1, anchor_num * width * height].
 *  @param[in] scores
 *    Input. A pointer to device foreground and background scores of boxes.
 *  @param[in] anchors_desc
 *    Input. A descriptor of anchors, each contains dimension of
 *    [1, 4, 1, anchor_num * width * height].
 *  @param[in] anchors
 *    Input. A pointer to device anchor boxes.
 *  @param[in] workspace
 *    Input.  A pointer to the MLU memory that is used as an extra workspace.
 *  @param[in] workspace_size
 *    Input. The size of extra space.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions must be met:
 *    - Handle is NULL.
 *    - new_box is NULL.
 *    - bbox_pred is NULL.
 *    - scores is NULL.
 *    - anchors is NULL.
 *
 */
cnnlStatus_t CNNL_WIN_API cnnlProposal(cnnlHandle_t handle,
                                       const cnnlProposalDescriptor_t proposal_desc,
                                       const cnnlTensorDescriptor_t new_box_desc,
                                       const void *new_box,
                                       const cnnlTensorDescriptor_t bbox_pred_desc,
                                       const void *bbox_pred,
                                       const cnnlTensorDescriptor_t scores_desc,
                                       const void *scores,
                                       const cnnlTensorDescriptor_t anchors_desc,
                                       const void *anchors,
                                       const void *workspace,
                                       const size_t workspace_size);

// Group:Proposal
/*!
 *  @brief A function.
 *
 *  This function is used to create a proposal descriptor, which contains
 *  the proposal parameters.
 *
 *  @param[in] proposal_desc
 *    Input. A pointer to the struct of the proposal descriptor.
 *  @retval CNNL_STATUS_SUCCESS
 *    This function ended normally.
 *  @retval CNNL_STATUS_ALLOC_FAILED
 *    The function malloc memory space failed.
 */
cnnlStatus_t CNNL_WIN_API cnnlCreateProposalDescriptor(cnnlProposalDescriptor_t *desc);

// Group:Proposal
/*!
 *  @brief A function.
 *
 *  This function destroys a proposal descriptor that was created by
 *  cnnlCreateProposalDescriptor.
 *
 *  @param[in] proposal_desc
 *    Input. A proposal descriptor created by cnnlCreateProposalDescriptor.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One the following conditions are met:
 *      - The value of proposal_desc was NULL.
 */
cnnlStatus_t CNNL_WIN_API cnnlDestroyProposalDescriptor(cnnlProposalDescriptor_t proposal_desc);

// Group:Proposal
/*!
 *  @brief A function.
 *
 *  This function is used to assign proposal descriptor with parameters.
 *  **API Dependency **
 *    The dependence is as follow:
 *      1.The function named cnnlGetProposalWorkspaceSize() needs to be called
 *        before this function.
 *      2.The function named cnnlCreateProposalDescriptor() needs to be
 *        called before this function.
 *      3.The function named cnnlDestroyProposalDescriptor() needs to be
 *        called after this function.
 *
 *  @param[in] proposal_desc
 *    Input. A proposal descriptor create by cnnlCreateProposalDescriptor.
 *  @param[in] batch_size
 *    Input. Number of input batchs.
 *  @param[in] height
 *    Input. Height of feature map.
 *  @param[in] width
 *    Input. Width of the feature map.
 *  @param[in] anchor_num
 *    Input. Number of anchors of every point in the feature map.
 *  @param[in] nms_num
 *    Input. Number of boxes to be select in nms process.
 *  @param[in] top_thresh
 *    Input. Number of boxes selected in TopK process.
 *  @param[in] im_min_h
 *    Input. The minimum size of height for boxes selected.
 *  @param[in] im_min_w
 *    Input. The minimum size of width for boxes selected.
 *  @param[in] nms_scale
 *    Input. The scaling rate of boxes when computing areas of box in nms process. Not used
 *  @param[in] stride
 *    Input. Stride in computing anchor. Not used.
 *  @param[in] nms_thresh
 *    Input. Threshold of IOU in nms process.
 *  @param[in] im_h
 *    Input. Height of input images for network.
 *  @param[in] im_w
 *    Input. Width of input images for network.
 *  @param[in] scale
 *    Input. The scaling rate of the size of input images. Not used
 *  @param[in] fix8
 *    Input. Type of input. Not used.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *      - The value of proposal_desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API cnnlSetProposalDescriptor(cnnlProposalDescriptor_t proposal_desc,
                                                    const int batch_size,
                                                    const int height,
                                                    const int width,
                                                    const int anchor_num,
                                                    const int nms_num,
                                                    const int top_thresh,
                                                    const float im_min_h,
                                                    const float im_min_w,
                                                    const float nms_scale,
                                                    const float stride,
                                                    const float nms_thresh,
                                                    const float im_h,
                                                    const float im_w,
                                                    const float scale,
                                                    const int fix8);

// Group:Proposal
/*!
 *  @brief A function.
 *  This function is used to get extra space size that needed in proposal operation.
 *
 *  @param[in]  proposal_desc
 *    Input.  Parameter description of proposal operator.
 *  @param[out] size
 *    Output. Size of workspace.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions is met:
 *    - Proposal_desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlGetProposalWorkspaceSize(const cnnlProposalDescriptor_t proposal_desc,
                             size_t *size);

/******************************************************************************
 * Cambricon CNNL OP: ProposalFpn
 ******************************************************************************/
/*! The descriptor of ProposalFpn function that holds proposalFpn parameters, which are
 *  nms_num, topk_num, im_min_h, im_min_w, nms_scale, nms_thresh, to_remove, im_h, im_w,
 *  level and nms_across_level.
 *
 *  You need to call the cnnlCreateProposalFpnDescriptor function
 *  to create a descriptor, and call the cnnlSetProposalFpnDescriptor
 *  function to set the tensor information to the descriptor.
 *  Also, you need to destroy the proposal_fpn descriptor at the end with the
 *  cnnlDestroyProposalFpnDescriptor function*/
typedef struct cnnlProposalFpnStruct *cnnlProposalFpnDescriptor_t;

// Group:Proposal
/*!
 * @brief A function
 *
 * This function generates proposal boxes from scores and bounding box
 * predictions in feature pyramid networks. Now it supports only MLU370.
 *
 * **Datatype**
 *
 *  - input: float, half.
 *
 *  - output: float, half.
 *
 * **Attention:**
 *
 *  - Data types of input and output must be the same.
 *
 * **Scale Limitation**
 *
 *  - The parameters of the proposalFpn operation must satisfy following conditions:
 *
 *    - batch > 0, height > 0, width > 0, anchor_num > 0, nms_num > 0,
 *      im_h > 0, im_w > 0, im_min_h > 0, im_min_w > 0, level > 1.
 *
 *    - The value of nms_num should be in the range of [50, 2000].
 *
 *    - The value of topk_num should be in the range of [0, nms_num].
 *
 *    - The width and height should be in the range of [64, 2560].
 *
 *    - The value of nms_thresh should be in the range of (0, 1).
 *
 *  **API Dependency**
 *
 *  You need to call the cnnlCreateProposalFpnDescriptor() and cnnlSetProposalFpnDescriptor()
 *  and cnnlGetProposalFpnWorkspaceSize() functions before calling this function.
 *
 *  You need to call the cnnlDestroyProposalFpnDescriptor() function after calling this function.
 *
 *  @param[in] handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           proposalFpn operation.
 *  @param[in] new_box_desc
 *    Input. The descriptor of new_box, including dimension of
 *    [batch_size, topk_num, 4] and data type of (float, half).
 *  @param[out] new_box
 *    Output. Pointer to the MLU memory that stores the new_box tensor.
*  @param[in] new_score_desc
 *    Input. The descriptor of new_score, including dimension of
 *    [batch_size, topk_num, 1] and data type of (float, half).
 *  @param[out] new_score
 *    Output. Pointer to the MLU memory that stores the new scores tensor.
 *  @param[in] bbox_pred0_desc
 *    Input. The descriptor of the bbox_pred of level-0, including dimension of
 *    [batch_size, Hi, Wi, anchor_num, 4] and data type of (float, half).
 *  @param[in] bbox_pred_0
 *    Input. Pointer to the MLU memory that stores the bounding box predictions tensor.
 *  @param[in] bbox_pred1_desc
 *    Input. The descriptor of the bbox_pred of level-1, including dimension of
 *    [batch_size, Hi, Wi, anchor_num, 4] and data type of (float, half).
 *  @param[in] bbox_pred_1
 *    Input. Pointer to the MLU memory that stores the bounding box predictions tensor.
 *  @param[in] bbox_pred2_desc
 *    Input. The descriptor of the bbox_pred of level-2, including dimension of
 *    [batch_size, Hi, Wi, anchor_num, 4] and data type of (float, half).
 *  @param[in] bbox_pred_2
 *    Input. Pointer to the MLU memory that stores the bounding box predictions tensor.
 *  @param[in] bbox_pred3_desc
 *    Input. The descriptor of the bbox_pred of level-3, including dimension of
 *    [batch_size, Hi, Wi, anchor_num, 4] and data type of (float, half).
 *  @param[in] bbox_pred_3
 *    Input. Pointer to the MLU memory that stores the bounding box predictions tensor.
 *  @param[in] bbox_pred4_desc
 *    Input. The descriptor of the bbox_pred of level-4, including dimension of
 *    [batch_size, Hi, Wi, anchor_num, 4] and data type of (float, half).
 *  @param[in] bbox_pred_4
 *    Input. Pointer to the MLU memory that stores the bounding box predictions tensor.
 *  @param[in] scores0_desc
 *    Input. The descriptor of the scores of level-0, including dimension of
 *    [batch_size, Hi, Wi, anchor_num, 1] and data type of (float, half).
 *  @param[in] scores_0
 *    Input. Pointer to the MLU memory that stores the foreground and background scores tensor.
 *  @param[in] scores1_desc
 *    Input. The descriptor of the scores of level-1, including dimension of
 *    [batch_size, Hi, Wi, anchor_num, 1] and data type of (float, half).
 *  @param[in] scores_1
 *    Input. Pointer to the MLU memory that stores the foreground and background scores tensor.
 *  @param[in] scores2_desc
 *    Input. The descriptor of the scores of level-2, including dimension of
 *    [batch_size, Hi, Wi, anchor_num, 1] and data type of (float, half).
 *  @param[in] scores_2
 *    Input. Pointer to the MLU memory that stores the foreground and background scores tensor.
 *  @param[in] scores3_desc
 *    Input. The descriptor of the scores of level-3, including dimension of
 *    [batch_size, Hi, Wi, anchor_num, 1] and data type of (float, half).
 *  @param[in] scores_3
 *    Input. Pointer to the MLU memory that stores the foreground and background scores tensor.
 *  @param[in] scores4_desc
 *    Input. The descriptor of the scores of level-4, including dimension of
 *    [batch_size, Hi, Wi, anchor_num, 1] and data type of (float, half).
 *  @param[in] scores_4
 *    Input. Pointer to the MLU memory that stores the foreground and background scores tensor.
 *  @param[in] anchors_desc
 *    Input. The descriptor of anchors, including dimension of the accumulation of several
 *    dimensions, which is the height * width * anchor_num of every level, which is represent by
 *    X. The dimension is [X, 4], and the data type is (float, half).
 *  @param[in] anchors
 *    Input. Pointer to the MLU memory that stores the anchor boxes tensor.
 *  @param[in] workspace
 *    Input.  The pointer to the MLU memory that is used as an extra workspace.
 *  @param[in] workspace_size
 *    Input. The size of extra space.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions must be met:
 *    - Handle is NULL.
 *    - new_box is NULL.
 *    - bbox_pred is NULL.
 *    - scores is NULL.
 *    - anchors is NULL.
 */
cnnlStatus_t CNNL_WIN_API cnnlProposalFpn(cnnlHandle_t handle,
                                          const cnnlProposalFpnDescriptor_t proposal_fpn_desc,
                                          const cnnlTensorDescriptor_t new_box_desc,
                                          const void *new_box,
                                          const cnnlTensorDescriptor_t new_score_desc,
                                          const void *new_score,
                                          const cnnlTensorDescriptor_t bbox_pred0_desc,
                                          const void *bbox_pred_0,
                                          const cnnlTensorDescriptor_t bbox_pred1_desc,
                                          const void *bbox_pred_1,
                                          const cnnlTensorDescriptor_t bbox_pred2_desc,
                                          const void *bbox_pred_2,
                                          const cnnlTensorDescriptor_t bbox_pred3_desc,
                                          const void *bbox_pred_3,
                                          const cnnlTensorDescriptor_t bbox_pred4_desc,
                                          const void *bbox_pred_4,
                                          const cnnlTensorDescriptor_t scores0_desc,
                                          const void *scores_0,
                                          const cnnlTensorDescriptor_t scores1_desc,
                                          const void *scores_1,
                                          const cnnlTensorDescriptor_t scores2_desc,
                                          const void *scores_2,
                                          const cnnlTensorDescriptor_t scores3_desc,
                                          const void *scores_3,
                                          const cnnlTensorDescriptor_t scores4_desc,
                                          const void *scores_4,
                                          const cnnlTensorDescriptor_t anchors_desc,
                                          const void *anchors,
                                          const void *workspace,
                                          const size_t workspace_size);

// Group:Proposal
/*!
 *  @brief A function.
 *
 *  This function is used to create a proposalFpn descriptor, which contains
 *  the proposalFpn parameters, which are nms_num, topk_num, im_min_h, im_min_w,
 *  nms_scale, nms_thresh, to_remove, im_h, im_w, level and nms_across_level.
 *
 *  @param[in] proposal_fpn_desc
 *    Input. A pointer to the struct of the proposalFpn descriptor.
 *  @retval CNNL_STATUS_SUCCESS
 *    This function ended normally.
 *  @retval CNNL_STATUS_ALLOC_FAILED
 *    The function malloc memory space failed.
 */
cnnlStatus_t CNNL_WIN_API
cnnlCreateProposalFpnDescriptor(cnnlProposalFpnDescriptor_t *proposal_fpn_desc);

// Group:Proposal
/*!
 *  @brief A function.
 *
 *  This function is used to destroy a proposalFpn descriptor that was created by
 *  cnnlCreateProposalFpnDescriptor.
 *
 *  @param[in] proposal_fpn_desc
 *    Input. A proposalFpn descriptor created by ::cnnlCreateProposalFpnDescriptor.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One the following conditions are met:
 *      - The value of proposal_fpn_desc was NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlDestroyProposalFpnDescriptor(cnnlProposalFpnDescriptor_t proposal_fpn_desc);

// Group:Proposal
/*!
 *  @brief A function.
 *
 *  This function is used to assign proposalFpn descriptor with parameters.
 *
 *  **API Dependency **
 *
 *  You need to call the cnnlGetProposalFpnWorkspaceSize() and cnnlCreateProposalFpnDescriptor()
 *  functions before calling this function.
 *
 *  You need to call the cnnlDestroyProposalFpnDescriptor() function after calling this function.
 *
 *  @param[in] proposal_fpn_desc
 *    Input. A proposal descriptor create by cnnlCreateProposalFpnDescriptor.
 *  @param[in] nms_num
 *    Input. Number of boxes to be selected in nms process.
 *  @param[in] topk_num
 *    Input. Number of boxes selected in TopK process.
 *  @param[in] im_min_h
 *    Input. The minimum size of height for boxes selected.
 *  @param[in] im_min_w
 *    Input. The minimum size of width for boxes selected.
 *  @param[in] nms_scale
 *    Input. The scaling rate of boxes when computing areas of box in nms process.
 *           This parameter is reserved for future use, now it must be 1.0.
 *  @param[in] nms_thresh
 *    Input. Threshold of IOU in nms process.
 *  @param[in] to_remove
 *    Input. The parameter is used to calculate height and width with the formula
 *           width = x1 - x2 + to_remove and height = y1 - y2 + to_remove. It is ether 0 or 1.
 *  @param[in] im_h
 *    Input. Height of input images for network.
 *  @param[in] im_w
 *    Input. Width of input images for network.
 *  @param[in] level
 *    Input. The number of feature map. It must be 5.
 *  @param[in] nms_across_level
 *    Input. A boolean value indicating that the function do NMS level by level or
 *           all levels together.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *      - The value of proposal_fpn_desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetProposalFpnDescriptor(cnnlProposalFpnDescriptor_t proposal_fpn_desc,
                             const int nms_num,
                             const int topk_num,
                             const float im_min_h,
                             const float im_min_w,
                             const float nms_scale,
                             const float nms_thresh,
                             const float to_remove,
                             const int im_h,
                             const int im_w,
                             const int level,
                             const bool nms_across_level);

// Group:Proposal
/*!
 *  @brief A function.
 *  This function is used to get extra space size that needed in proposalFpn operation.
 *
 *  @param[in]  proposal_fpn_desc
 *    Input.  The description of proposalFpn operator.
 *  @param[out] size
 *    Output. Size of workspace.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions is met:
 *    - proposal_fpn_desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlGetProposalFpnWorkspaceSize(const cnnlProposalFpnDescriptor_t proposal_fpn_desc, size_t *size);

/******************************************************************************
 * Cambricon CNNL OP: Roipool
 ******************************************************************************/
/*! The descriptor of the roipool operation that holds roipool information
 *  including the rois_offset, spatial_scale, rois_type, algo, num_input,
 *  output_dim, group_size.
 *
 *  You need to call the ::cnnlCreateRoipoolDescriptor funtion to create a
 *  descriptor, and according to the parameter 'algo' to call the
 *  ::cnnlSetRoipoolDescriptor() or ::cnnlSetPsRoipoolDescriptor()
 *  to set the information of the roipool operation to the descriptor. Also, you need
 *  to destroy the Cambricon CNNL context at the end with the ::cnnlDestroyRoipoolDescriptor
 *  function.
 */
typedef struct cnnlRoipoolStruct *cnnlRoipoolDescriptor_t;

/*!
 * @brief An enum.
 *
 * Enumeration variables describe the modes that are used in the
 * implementation of the roipool and psroipool op.
 *
 */
typedef enum {
  CNNL_ROIPOOL   = 0, /*!< The Roipool kernel is implemented.*/
  CNNL_PSROIPOOL = 1, /*!< The PsRoipool kernel is implemented.*/
} cnnlRoipoolAlgo_t;

// Group:Roipool
/*!
 *  @brief A function
 *
 *  This function is used to generate fixed size feature map for each Roi(Regions of Interest).
 *
 *  **DataType**
 *
 *     - input_data: half, float
 *
 *     - input_rois: half, float
 *
 *     - output_data: half, float.
 *
 *  **Attention:**
 *
 *    - DataType of input_data, input_rois, and output_data must be the same.
 *    - The roipool and ps_roipool input data only support CNNL_LAYOUT_NHWC.
 *    - The layout of the input data of ps_roipool must be [batch_size, height, width,[output_dim,group_size,group_size]].
 *    - The roipool and ps_roipool roi number of each batch must be the same.
 *    - The input_rois_desc only has two dims. The CNNL_LAYOUT_NCHW is used to denote the input_rois date layout
 *      [rois_num, rois_offset], or CNNL_LAYOUT_NHWC layout is used to denote the input_rois date layout
 *      [rois_offset, rois_num].
 *
 *  **API Dependency**
 *
 *  Some functions needed to be called before this function are as follows:
 *    1.The function named cnnlCreateRoipoolDescriptor() needs to be called before this function.
 *    2.The function named cnnlSetRoipoolDescriptor()/cnnlSetPsRoipoolDescriptor() needs to be called before this function.
 *
 *  @param[in] handle
 *    Input.  Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *            roipool operation.
 *  @param[in] roipool_desc
 *    Input.  A descriptor of roipool parameter.
 *  @param[in] input_data_desc
 *    Input.  Pointer to the host memory that stores an array of cnnlTensorDescriptors which holds dimension, data type, and layout
 *            of input_data tensors. The meaning of tensor descriptor varies based on different cnnlRoipoolAlgo_t:
 *            1. CNNL_ROIPOOL: input_data_desc contains 1 element, the shape of tensor must be [batch,height,width,channel],
 *               data type (include half, float), data layout only supports NHWC.
 *            2. CNNL_PSROIPOOL: input_data_desc contains 1 element, the shape of tensor must be [batch,height,width,channel],
 *               data type (include half, float), data layout only supports NHWC.
 *  @param[in] input_data
 *    Input.  Pointer to the host memory that stores an array of pointers to the device memory of input_data. The element order of this input_data
 *            array must be consistent with the element order of the cnnlTensorDescriptors array.
 *  @param[in] input_rois_desc
 *    Input.  Pointer to the host memory that stores an array of cnnlTensorDescriptors which holds dimension, data type, and layout
 *            of input_rois tensors. The meaning of tensor descriptor varies based on different cnnlRoipoolAlgo_t:
 *            1. CNNL_ROIPOOL: input_rois_desc contains multiple elements (the number of the elements equals to the batch size).
 *               The rois layout supports CNNL_LAYOUT_NCHW([rois_num, rois_offset]) and CNNL_LAYOUT_NHWC([rois_offset, rois_num]),
 *               and data type (include half, float) must be same with that of input_data_desc.
 *            2. CNNL_PSROIPOOL: input_rois_desc contains 1 element. The rois layout supports CNNL_LAYOUT_NCHW([rois_num, rois_offset])
 *               and CNNL_LAYOUT_NHWC([rois_offset, rois_num]), and data type (include half, float) must be same with that of input_data_desc.
 *  @param[in] input_rois
 *    Input.  Pointer to the host memory that stores an array of pointers to the device memory of input_rois. The element order of this input_rois
 *            array must be consistent with the element order of the cnnlTensorDescriptors array.
 *  @param[in] workspace
 *    Input.  A pointer to the MLU memory that is used as an extra workspace.
 *  @param[in] workspace_size
 *    Input. The size of extra space.
 *  @param[in] output_data_desc
 *    Input.  A descriptor of output tensor, contain dimension of [total_rois_num,height,width,channel],
 *            data type (include half, float).
 *  @param[out] output_data
 *    Output.  A pointer to device output data.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions is met:
 *    For CNNL_ROIPOOL:
 *      - Handle is NULL.
 *      - The input_data_desc is NULL.
 *      - The input_data is NULL.
 *      - The input_rois_desc is NULL.
 *      - The input_rois is NULL.
 *      - The roipool_desc is NULL.
 *      - The output_data_desc is NULL.
 *      - The output_data is NULL.
 *      - The rois_offset is not equal to 5.
 *      - The layout type of input data is not equal to CNNL_LAYOUT_NHWC.
 *      - The layout type of input rois in not equal to CNNL_LAYOUT_NHWC or CNNL_LAYOUT_NCHW.
 *      - The input data type is not CNNL_DTYPE_FLOAT or CNNL_DTYPE_HALF.
 *      - The input rois type is not CNNL_DTYPE_FLOAT or CNNL_DTYPE_HALF.
 *      - The output data type is not CNNL_DTYPE_FLOAT or CNNL_DTYPE_HALF.
 *      - The input data type is not equal to input rois type or input data type is not equal to
 *        output data type.
 *    For CNNL_PSROIPOOL:
 *      - Handle is NULL.
 *      - The input_data_desc is NULL.
 *      - The input_data is NULL.
 *      - The input_rois_desc is NULL.
 *      - The input_rois is NULL.
 *      - The roipool_desc is NULL.
 *      - The output_data_desc is NULL.
 *      - The output_data is NULL.
 *      - The layout type of input data is not CNNL_LAYOUT_NHWC.
 *      - The layout type of input rois in not equal to CNNL_LAYOUT_NHWC or CNNL_LAYOUT_NCHW.
 *      - The group_size is not equal to pooled_height.
 *      - The pooled_height is not equal to pooled_width.
 *      - The group_size is smaller than 1.
 *      - The output_dim is smaller than 1.
 *      - The rois_offset is not equal to 5.
 *      - The input data type is not CNNL_DTYPE_FLOAT or CNNL_DTYPE_HALF.
 *      - The input rois type is not CNNL_DTYPE_FLOAT or CNNL_DTYPE_HALF.
 *      - The output data type is not CNNL_DTYPE_FLOAT or CNNL_DTYPE_HALF.
 *      - The input data type is not equal to input rois type or input data type is not equal to
 *        output data type.
 */
cnnlStatus_t CNNL_WIN_API cnnlRoipool(cnnlHandle_t handle,
                                      cnnlRoipoolDescriptor_t roipool_desc,
                                      const cnnlTensorDescriptor_t input_data_desc[],
                                      const void *const input_data[],
                                      const cnnlTensorDescriptor_t input_rois_desc[],
                                      const void *const input_rois[],
                                      void *workspace,
                                      size_t workspace_size,
                                      const cnnlTensorDescriptor_t output_data_desc,
                                      void *output_data);

// Group:Roipool
/*!
 *  @brief A function.
 *
 *  This function is used to create a roipool descriptor.
 *  @param[in] desc
 *    Input.  A pointer to the struct of roipool descriptor.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_ALLOC_FAILED
 *    one of the following conditions is met:
 *      - The desc is allocated failed.
 */
cnnlStatus_t CNNL_WIN_API cnnlCreateRoipoolDescriptor(cnnlRoipoolDescriptor_t *desc);

// Group:Roipool
/*!
 *  @brief A function.
 *
 *  This function is used to destroy a roipool descriptor.
 *
 *  **Attention**
 *
 *  This function must be called after calling roipool operation to prevent a host memory leak.
 *
 *  @param[in] desc
 *    Input.  A pointer to the struct of roipool descriptor.
 *  @retval CNNL_STATUS_SUCCESS
 *    - The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    - The desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API cnnlDestroyRoipoolDescriptor(cnnlRoipoolDescriptor_t desc);

// Group:Roipool
/*!
 *  @brief A function.
 *
 *  This function is used to set a roipool descriptor.
 *
 *  **API Dependency **
 *
 *    The dependence is as follow:
 *      1.The function named cnnlCreateRoipoolDescriptor() needs to be called before this function.
 *      2.The function named cnnlDestroyRoipoolDescriptor() needs to be called after this function.
 *
 *  @param[in] desc
 *    Input.  The description of the roipool that holds algo, spatial_scale and rois_type.
 *  @param[in] algo
 *    Input.  Algorithm of roipool descriptor.
 *  @param[in] spatial_scale
 *    Input.  The spatial scale of each regions of interest.
 *  @param[in] rois_type
 *    Input.  The mode selection for regions of interest. The rois_type only support
 *            CNNL_ROI_BATCHID_CONRER and CNNL_ROI_CORNER_BATCHID.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions is met:
 *      - The value of desc is NULL.
 *      - The algo is not equal to CNNL_ROIPOOL.
 *      - The spatial_scale is smaller or equal than 0.
 *      - The rois_type is not equal to CNNL_ROI_BATCHID_CONRER or CNNL_ROI_CORNER_BATCHID.
 */
cnnlStatus_t CNNL_WIN_API cnnlSetRoipoolDescriptor(cnnlRoipoolDescriptor_t desc,
                                                   const cnnlRoipoolAlgo_t algo,
                                                   const float spatial_scale,
                                                   const cnnlRoiLayoutType_t rois_type);

// Group:Roipool
/*!
 *  @brief A function.
 *
 *  This function is used to set a ps_roipool descriptor.
 *
 *  **API Dependency **
 *
 *    The dependence is as follow:
 *      1.The function named cnnlCreateRoipoolDescriptor() needs to be called before this function.
 *      2.The function named cnnlDestroyRoipoolDescriptor() needs to be called after this function.
 *
 *  @param[in] desc
 *    Input.  A pointer to the struct of roipool descriptor.
 *  @param[in] algo
 *    Input.  Algorithm of roipool descriptor.
 *  @param[in] output_dim
 *    Input.  The channel dimension of output tensor.
 *  @param[in] group_size
 *    Input.  The pooled height/width of output tensor. This operation assumes that
 *            pooled height = pooled width.
 *  @param[in] spatial_scale
 *    Input.  The scaling factor that maps input coordinates into the box coordinates.
 *  @param[in] rois_type
 *    Input.  The mode selection for regions of interest. The rois_type must be
 *            CNNL_ROI_CORNER_BATCHID or CNNL_ROI_CORNER_BATCHID.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions is met:
 *      - The value of desc is NULL.
 *      - The algo is not equal to CNNL_PSROIPOOL.
 *      - The output_dim is smaller than 1.
 *      - The group_size is smaller than 1.
 *      - The spatial_scale is smaller or equal to 0.
 *      - The rois_type is not equal to CNNL_ROI_CORNER_BATCHID or CNNL_ROI_BATCHID_CORNER.
 */
cnnlStatus_t CNNL_WIN_API cnnlSetPsRoipoolDescriptor(cnnlRoipoolDescriptor_t desc,
                                                     const cnnlRoipoolAlgo_t algo,
                                                     const int output_dim,
                                                     const int group_size,
                                                     const float spatial_scale,
                                                     const cnnlRoiLayoutType_t rois_type);

// Group:Roipool
/*!
 *  @brief A function.
 *  This function is used to get extra space size that needed in roipool operation.
 *
 *  @param[in]  handle
 *    Input.  Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *            roipool operation.
 *  @param[in]  desc
 *    Input.  Parameter description of roipool operator.
 *  @param[in]  input_desc
 *    Input.  Tensor descriptor of input.
 *  @param[in]  algo
 *    Input.  Roipool algorithm used.
 *  @param[out] size
 *    Output. Size of workspace.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions is met:
 *    - The handle is NULL.
 *    - The input_desc is NULL.
 *    - The current algo is not support.
 */
cnnlStatus_t CNNL_WIN_API
cnnlGetRoipoolWorkspaceSize(cnnlHandle_t handle,
                            const cnnlRoipoolDescriptor_t desc,
                            const cnnlTensorDescriptor_t input_desc[],
                            cnnlRoipoolAlgo_t algo,
                            size_t *size);

/******************************************************************************
 * Cambricon CNNL OP: BertPre
 ******************************************************************************/
// Group:BertPre
/*!
 *  @brief A function.
 *
 *  the pre process network.
 *
 *  **Formula**
 *
 *  This operation contains follow steps:
 *
 *  1. Look up word embedding table with input ids.
 *
 *  2. Look up segment embedding table with token type ids. (optional)
 *
 *  3. Look up position embedding table. (optional)
 *
 *  4. embedding = word embedding + segment embedding + position embedding.
 *
 *  5. output = layernorm(embedding). (optional)
 *
 *  **DataType**
 *
 *   - input_ids: int.
 *
 *   - token_type_ids: int.
 *
 *   - word_embedding_table: float, half.
 *
 *   - segment_embedding_table_desc: float, half.
 *
 *   - position_embedding_table_desc: float, half.
 *
 *   - layernorm scale: float, half.
 *
 *   - layernorm bias: float, half.
 *
 *   - output: float, half.
 *
 *  **Attention: **
 *
 *   - DataType of word_embedding_table, segment_embedding_table_desc,
 *     position_embedding_table_desc must be same.
 *
 *  **Scale Limitation**
 *
 *    According to bert, the parameters must satisfy the following conditions:
 *
 *    - The number of dimensions of all tensors must match.
 *
 *    - batch_num and seq_len has no limit. batch_num and seq_len must be greater than 0.
 *
 *    - hidden_size must be divisible by 64.
 *
 *  **Performance Optimization**
 *
 *    Use U4.
 *
 *  **Example**
 *
 *    Dimension of input_ids: [batch_num, seq_len]
 *
 *    Dimension of token_type_ids: [batch_num, seq_len]
 *
 *    Dimension of word_embedding_table: [vocab_size, hidden_size]
 *
 *    Dimension of segment_embedding_table: [segment_size, hidden_size]
 *
 *    Dimension of position_embedding_table: [position_size, hidden_size]
 *
 *    Dimension of layernorm_scale: [hidden_size]
 *
 *    Dimension of layernorm_bias: [hidden_size]
 *
 *    Then we will get the output:
 *
 *    Dimension of output: [batch_num, seq_len, hidden_size]
 *
 *  @param[in]  handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the bert_pre
 *           operation.
 *  @param[in]  input_ids_desc
 *    Input. Descriptor of input ids, containing dimension and the layout of input.
 *  @param[in]  input_ids
 *    Input. Device pointer points to input_ids space.
 *  @param[in]  token_type_ids_desc
 *    Input. Descriptor of token type ids, containing dimension and the layout of input.
 *  @param[in]  token_type_ids
 *    Input. Device pointer points to token_type_ids space.
 *  @param[in]  word_embedding_table_desc
 *    Input. Descriptor of vocabulaire, containing dimension and the layout of input.
 *  @param[in]  word_embedding_table
 *    Input. Device pointer points to vocabulaire scape.
 *  @param[in]  segment_embedding_table_desc
 *    Input. Descriptor of segment embedding table, containing dimension and the layout of input.
 *  @param[in]  segment_embedding_table
 *    Input. Device pointer points to segment embedding table space.
 *  @param[in]  position_embedding_table_desc
 *    Input. Descriptor of position embedding table, containing dimension and the layout of input.
 *  @param[in]  position_embedding_table
 *    Input. Device pointer points to position embedding table space.
 *  @param[in]  layernorm_scale_desc
 *    Input. Descriptor of layernorm_scale, containing dimension and the layout of input.
 *  @param[in]  layernorm_scale
 *    Input. Device pointer points to layernorm_scale space.
 *  @param[in]  layernorm_bias_desc
 *    Input. Descriptor of layernorm_bias, containing dimension and the layout of input.
 *  @param[in]  layernorm_bias
 *    Input. Device pointer points to layernorm_bias space.
 *  @param[in]  use_segment_embedding
 *    Input. Whether to use segment embedding.
 *  @param[in]  use_position_embedding
 *    Input. Whether to use position embedding.
 *  @param[in]  use_layernorm
 *    Input. Whether to use layernorm before output.
 *  @param[out]  output_desc
 *    Input. Descriptor of output, containing dimension and the layout of output.
 *  @param[out]  output
 *    Input. Device pointer points to output space.
 *  @retval CNNL_STATUS_SUCCESS = 0
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM = 3
 *    One or more of the following conditions are encountered:
 *    - handle is NULL.
 *    - pointer is NULL.
 *    - parameters do not meet scale limitation.
 *  @retval CNNL_STATUS_ARCH_MISMATCH
 *    One or more of the following conditions are encountered:
 *    - This function is run on the hardware platform that is not supported.
 */
cnnlStatus_t CNNL_WIN_API
cnnlBertPre(cnnlHandle_t handle,
            const cnnlTensorDescriptor_t input_ids_desc,
            const void *input_ids,
            const cnnlTensorDescriptor_t token_type_ids_desc,
            const void *token_type_ids,
            const cnnlTensorDescriptor_t word_embedding_table_desc,
            const void *word_embedding_table,
            const cnnlTensorDescriptor_t segment_embedding_table_desc,
            const void *segment_embedding_table,
            const cnnlTensorDescriptor_t position_embedding_table_desc,
            const void *position_embedding_table,
            const cnnlTensorDescriptor_t layernorm_scale_desc,
            const void *layernorm_scale,
            const cnnlTensorDescriptor_t layernorm_bias_desc,
            const void *layernorm_bias,
            bool use_segment_embedding,
            bool use_position_embedding,
            bool use_layernorm,
            cnnlTensorDescriptor_t output_desc,
            void *output);

/*! The descriptor of the bertpre operation that holds bertpre information
 *  including the data type of embedding addition, the data type of computing
 *  layernorm and esp of layernorm.
 *
 *  You need to call the ::cnnlCreateBertPreDescriptor function to create a descriptor,
 *  and call the ::cnnlSetBertPreDescriptor function to set the information of the ffn
 *  operation to the descriptor. Also, you need to destroy the Cambricon CNNL context at the end
 *  with the ::cnnlDestroyBertPreDescriptor function.
 */
typedef struct cnnlBertPreStruct *cnnlBertPreDescriptor_t;

// Group:BertPre
/*!
 *  @brief A function.
 *
 *  This function is used to create a descriptor for a bertpre operation and allocate memory for it.
 *
 *  @param[in]  desc
 *    Input. Descriptor of bertpre operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_ALLOC_FAILED
 *    The function failed to allocate memory space.
 */
cnnlStatus_t CNNL_WIN_API
cnnlCreateBertPreDescriptor(cnnlBertPreDescriptor_t *desc);

// Group:BertPre
/*!
 *  @brief A function.
 *
 *  This function is used to destroy the descriptor of a bertpre operation and free memory for it.
 *
 *  @param[in]  desc
 *    Input. Descriptor of bertpre operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlDestroyBertPreDescriptor(cnnlBertPreDescriptor_t desc);

// Group:BertPre
/*!
 *  @brief A function.
 *
 *  This function is used to assign a bertpre descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  After creating a descriptor with cnnlCreateBertPreDescriptor(), users need
 *  to use cnnlSetBertPreDescriptor() to set its parameters.
 *
 *  @param[in]  desc
 *    Input. Descriptor of bertpre operation.
 *  @param[in]  addition_compute_dtype
 *    Input. The data type of computing accumulation for embedding.
 *  @param[in]  layernorm_compute_dtype
 *    Input. The data type of computing layernorm.
 *  @param[in]  layernorm_eps
 *    Input. The eps value of layernorm.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetBertPreDescriptor(cnnlBertPreDescriptor_t desc,
                         const cnnlDataType_t addition_compute_dtype,
                         const cnnlDataType_t layernorm_compute_dtype,
                         const float layernorm_eps);

// Group:BertPre
/*!
 *  @brief A function.
 *
 *  The bertpre layer in bert network, which can complete the input embedding of network.
 *  For example, users can use this function to finish token embedding, segment embedding,
 *  position embedding and add them together to get the embedding output, and can also
 *  choose whether to use layernorm for output. The difference from cnnlBertPre() is that
 *  users can choose the order and look up table method of different embeddings.
 *
 *  **Formula**
 *
 *  This operation contains follow steps:
 *
 *  1. table1 embedding
 *
 *    table1_embedding = embedding(table1, index1, batch_num, seq_len)
 *
 *  2. table2 embedding[optional]
 *
 *    table2_embedding = embedding(table2, index2, batch_num, seq_len)
 *
 *  3. table3 embedding[optional]
 *
 *    table3_embedding = embedding(table3, index3, batch_num, seq_len)
 *
 *  4. addition
 *
 *    embedding_output = table1_embedding + table2_embedding + table3_embedding
 *
 *  5. layernorm[optional]
 *
 *    output = layernorm(embedding_output)
 *
 *  **DataType**
 *
 *  - table1: float, half
 *
 *  - index1: int32
 *
 *  - table2: float, half
 *
 *  - index2: int32
 *
 *  - table3: float, half
 *
 *  - index3: int32
 *
 *  - layernorm scale: float, half
 *
 *  - layernorm bias: float, half
 *
 *  - output: float, half
 *
 *  **Attention: **
 *
 *  - The cnnlBertPre_v2 is used to look up table1, table2 and table3, embedding
 *    and add them in turn.
 *
 *  - The data types of table1, table2, table3, layernorm scale, layernorm bias and output
 *    must be same.
 *
 *  - The layouts of index1, index2 and index3 must be same, which is two-dimensional.
 *
 *  - The layouts of table1, table2 and table3 must be same, which is two-dimensional.
 *
 *  - The layouts of layernorm scale and layernorm bias must be same, which is one-dimensional.
 *
 *  - The layouts of output is three-dimensional.
 *
 *  - The hidden_size must divisible by 64.
 *
 *  - The layernorm_scale_desc, layernorm_scale, layernorm_bias_desc, layernorm_bias
 *    must be all NULL or not, which means whether to use layernorm or not.
 *
 *  - The index1, index2 and index3 can be NULL, when it is NULL, the function uses the ID of
 *    the current token to loop up table, otherwise uses the value of index to look up table.
 *
 *  - The table2 and table3 can be NULL or not respectively. When it is not NULL, we will not
 *    look up this table and embedding.
 *
 *  - The addition_compute_dtype and addition_compute_dtype must be float or half, when data
 *    type of table is float, addition_compute_dtype and addition_compute_dtype is invalid.
 *
 *  **Performance Optimization**
 *
 *  When the hidden_size pad to 64, the performance is better.
 *
 *  **Example**
 *
 *  Dimension of index1: [batch_num, seq_len]
 *
 *  Dimension of table1: [table1, hidden_size]
 *
 *  Dimension of index2: [batch_num, seq_len]
 *
 *  Dimension of table2: [table2, hidden_size]
 *
 *  Dimension of index3: [batch_num, seq_len]
 *
 *  Dimension of table3: [table3, hidden_size]
 *
 *  Dimension of layernorm_scale: [hidden_size]
 *
 *  Dimension of layernorm_bias: [hidden_size]
 *
 *  Then we will get the output:
 *
 *  Dimension of output: [batch_num, seq_len, hidden_size]
 *
 *  **API Dependency**
 *
 *  You need to call the cnnlCreateBertPreDescriptor() and cnnlSetBertPreDescriptor()
 *  functions before calling this function.
 *
 *  You need to call the cnnlDestroyBertPreDescriptor() function after calling this function.
 *
 *  @param[in]  handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           bertpre operation.
 *  @param[in]  desc
 *    Input. A struct with parameters of bertpre operation.
 *  @param[in]  index1_desc
 *    Input. Descriptor of index1, containing dimension, datatype and layout of index1.
 *  @param[in]  index1
 *    Input. Device pointer points to index1 space.
 *  @param[in]  table1_desc
 *    Input. Descriptor of table1, containing dimension, datatype and layout of table1.
 *  @param[in]  table1
 *    Input. Device pointer points to table1 space.
 *  @param[in]  index2_desc
 *    Input. Descriptor of index2, containing dimension, datatype and layout of index2.
 *  @param[in]  index2
 *    Input. Device pointer points to index2 space.
 *  @param[in]  table2_desc
 *    Input. Descriptor of table2, containing dimension, datatype and layout of table2.
 *  @param[in]  table2
 *    Input. Device pointer points to table2 space.
 *  @param[in]  index3_desc
 *    Input. Descriptor of index3, containing dimension, datatype and layout of index3.
 *  @param[in]  index3
 *    Input. Device pointer points to index3 space.
 *  @param[in]  table3_desc
 *    Input. Descriptor of table3, containing dimension, datatype and layout of table3.
 *  @param[in]  table3
 *    Input. Device pointer points to table3 space.
 *  @param[in]  layernorm_scale_desc
 *    Input. Descriptor of layernorm_scale, containing dimension, datatype and layout
 *           of layernorm_scale.
 *  @param[in]  layernorm_scale
 *    Input. Device pointer points to layernorm_scale space.
 *  @param[in]  layernorm_bias_desc
 *    Input. Descriptor of layernorm_bias, containing dimension, datatype and layout
 *           of layernorm_bias.
 *  @param[in]  layernorm_bias
 *    Input. Device pointer points to layernorm_bias space.
 *  @param[out]  output_desc
 *    Input. Descriptor of output, containing dimension, datatype and layout of output.
 *  @param[out]  output
 *    Input. Device pointer points to output space.
 *  @retval CNNL_STATUS_SUCCESS = 0
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM = 3
 *    One or more of the following conditions are encountered:
 *    - handle is NULL.
 *    - pointer is NULL.
 *    - parameters do not meet scale limitation.
 *  @retval CNNL_STATUS_ARCH_MISMATCH
 *    One or more of the following conditions are encountered:
 *    - This function is run on the hardware platform that is not supported.
 */
cnnlStatus_t CNNL_WIN_API
cnnlBertPre_v2(cnnlHandle_t handle,
               const cnnlBertPreDescriptor_t desc,
               const cnnlTensorDescriptor_t index1_desc,
               const void *index1,
               const cnnlTensorDescriptor_t table1_desc,
               const void *table1,
               const cnnlTensorDescriptor_t index2_desc,
               const void *index2,
               const cnnlTensorDescriptor_t table2_desc,
               const void *table2,
               const cnnlTensorDescriptor_t index3_desc,
               const void *index3,
               const cnnlTensorDescriptor_t table3_desc,
               const void *table3,
               const cnnlTensorDescriptor_t layernorm_scale_desc,
               const void *layernorm_scale,
               const cnnlTensorDescriptor_t layernorm_bias_desc,
               const void *layernorm_bias,
               cnnlTensorDescriptor_t output_desc,
               void *output);

/******************************************************************************
 * Cambricon CNNL OP: BertPost
 ******************************************************************************/
// Group:BertPost
/*!
 *  @brief A function.
 *  This function is used to get extra space size that needed in bert_post
 *  operation.
 *
 *  @param[in]  input_desc
 *    Input. Descriptor of input, containing dimension and the layout of input.
 *  @param[out] size
 *    Output. Size of workspace.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The input_desc is not is not initialized.
 *    - The size is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlGetBertPostWorkspaceSize(const cnnlTensorDescriptor_t input_desc,
                             size_t *size);

// Group:BertPost
/*!
 *  @brief A function.
 *
 *  This operation implements the post processor in bert.
 *
 *  **Formula**
 *
 *  This operation contains follow steps:
 *
 *    1. X = input[:, 0, :].reshape((batch_size, hidden_size)).
 *
 *    2. T1 = tanh(matmul(X, inner_filter) + inner_bias).
 *
 *    3. T2 = matmul(T1, outer_filter) + outer_bias
 *
 *    4. if is_softmax = true:
 *         output = softmax(T2, axis=1)
 *       else:
 *         output = T2
 *
 *  **Example**
 *
 *    Dimension of input: [batch_size, seq_len, hidden_size]
 *
 *    Dimension of inner_filter: [inner_size, hidden_size]
 *
 *    Dimension of outer_filter: [outer_size, inner_size]
 *
 *    Dimension of inner_bias: [inner_size]
 *
 *    Dimension of outer_bias: [outer_size]
 *
 *    Dimension of output: [batch_size, outer_size]
 *
 *  **DataType**
 *
 *   - input: float, half.
 *   - filter: int16, int8, half.
 *   - bias: float, half.
 *   - output: float, half.
 *
 *  **Attention**
 *
 *    The type of filter is recommended to be int16.
 *    If the type of filter is int8, the precision of output
 *    may not be guaranteed.
 *
 *  **Scale Limitation**
 *
 *    - batch_size and seq_len has no limit.
 *      batch_size and seq_len must be greater than 0.
 *
 *    - hidden_size only support 512, 768, 1024.
 *
 *    - inner_size only support 512, 768, 1024.
 *
 *    - the hidden_size and inner_size could be freely combined,
 *      such as (512, 768), (768, 512).
 *
 *    - outer_size: 2 <= outer_size <= 64.
 *
 *  **Performance Optimization**
 *
 *    When the dimension of input meet batch_size*seq_len = 512*n(n=1,2,3..) , the performance is best.
 *
 *  **API Dependency**
 *
 *   You need to call the cnnlGetBertPostWorkspaceSize() function before calling this
 *   function.
 *
 *  @param[in]  handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the bert_post
 *           operation.
 *  @param[in]  input_desc
 *    Input. A descriptor of input tensor.
 *  @param[in]  input
 *    Input.An MLU tensor, a pointer to the input data on device.
 *  @param[in]  inner_filter_desc
 *    Input. A descriptor of inner_filter tensor.
 *  @param[in]  inner_filter
 *    Input. An MLU tensor, a pointer to the inner_filter data on device.
 *  @param[in]  outer_filter_desc
 *    Input. A descriptor of outer_filter tensor.
 *  @param[in]  outer_filter
 *    Input. An MLU tensor, a pointer to the outer_filter data on device.
 *  @param[in]  inner_bias_desc
 *    Input. A descriptor of inner_bias tensor.
 *  @param[in]  inner_bias
 *    Input. An MLU tensor, a pointer to the inner_bias data on device.
 *  @param[in]  outer_bias_desc
 *    Input. A descriptor of outer_bias tensor.
 *  @param[in]  outer_bias
 *    Input. An MLU tensor, a pointer to the outer_bias data on device.
 *  @param[in]  is_softmax
 *    Input. Control if do softmax on the output.
 *  @param[in]  workspace
 *    Input. A pointer to the extra space on device.
 *  @param[in]  workspace_size
 *    Input. The size of extra space.
 *  @param[out]  output_desc
 *    Output. A descriptor of output tensor.
 *  @param[out]  output
 *    Output. An MLU tensor, a pointer-array to output data on device.
 *  @retval  CNNL_STATUS_SUCCESS = 0
 *    The function ends normally.
 *  @retval  CNNL_STATUS_BAD_PARAM = 3
 *    One or more of the following conditions are satisfied:
 *    - Handle is NULL.
 *    - Input is NULL.
 *    - Output is NULL.
 *    - Dims are invalid.
 */
cnnlStatus_t CNNL_WIN_API cnnlBertPost(cnnlHandle_t handle,
                                       const cnnlTensorDescriptor_t input_desc,
                                       const void *input,
                                       const cnnlTensorDescriptor_t inner_filter_desc,
                                       const void *inner_filter,
                                       const cnnlTensorDescriptor_t outer_filter_desc,
                                       const void *outer_filter,
                                       const cnnlTensorDescriptor_t inner_bias_desc,
                                       const void *inner_bias,
                                       const cnnlTensorDescriptor_t outer_bias_desc,
                                       const void *outer_bias,
                                       const bool is_softmax,
                                       void *workspace,
                                       size_t workspace_size,
                                       const cnnlTensorDescriptor_t output_desc,
                                       void *output);

// Group:BertPost
/*!
 *  @brief A function.
 *
 *  This operation implements post process in the base case of BERT.
 *
 *  **Formula**
 *  - See "cnnlBertBaseCasedPost" in "Cambricon CNNL Extra User Guide" for details.
 *
 *  @par Example
    @verbatim
     Dimension of input: [batch_size, seq_len, hidden_size]

     Dimension of filter: [outer_size, hidden_size]

     Dimension of bias: [outer_size]

     Dimension of output: [batch_size, outer_size]

     Dimension of layernorm_output: [batch_size, seq_len, hidden_size]
    @endverbatim
 *
 *  **DataType**
 *   - input: float, half.
 *   - filter: half.
 *   - bias: float, half.
 *   - layernorm_scale: float, half.
 *   - layernorm_bias: float, half.
 *   - output: float, half.
 *   - layernorm_output: float, half.
 *   - The data type of input, bias, layernorm_scale, layernorm_bias, output and
 *     layernorm_output must be the same.
 *
 *  **Attention**
 *
 *    - The \p layernorm_mode only supports CNNL_TRANSFORMER_PRE_LAYERNORM.
 *
 *  **Scale Limitation**
 *
 *    - batch_size and seq_len must be greater than 0.
 *
 *    - hidden_size only supports 512, 768, 1024.
 *
 *    - outer_size only supports 512, 768, 1024.
 *
 *    - This function supports any combinations of hidden_size and outer_size.
 *
 *  **Performance Optimization**
 *
 *    When the dimension of input meets batch_size*seq_len = 512*n(n=1,2,3..) , the performance is best.
 *
 *  @param[in]  handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the bert_post
 *    operation.
 *  @param[in]  input_desc
 *    Input. A descriptor of input tensor.
 *  @param[in]  input
 *    Input.  Pointer to the MLU memory that stores the input data.
 *  @param[in]  filter_desc
 *    Input. A descriptor of filter tensor.
 *  @param[in]  filter
 *    Input. Pointer to the MLU memory that stores the filter data used in the Fully Connected operation.
 *  @param[in]  bias_desc
 *    Input. A descriptor of bias tensor. A nullptr means no bias.
 *  @param[in]  bias
 *    Input. Pointer to the MLU memory that stores the bias data.
 *    The bias is not used in the operation if this parameter is set to nullptr.
 *  @param[in]  layernorm_mode
 *    Input. The LayerNorm mode. Only supports CNNL_TRANSFORMER_PRE_LAYERNORM.
 *  @param[in]  layernorm_scale_desc
 *    Input. Descriptor of layernorm_scale, containing dimension and layout of Layernorm scale.
 *  @param[in]  layernorm_scale
 *    Input. Pointer to the MLU memory that stores the scale data used in the LayerNorm operation.
 *  @param[in]  layernorm_bias_desc
 *    Input. Descriptor of layernorm_bias, containing dimension and layout of Layernorm bias.
 *  @param[in]  layernorm_bias
 *    Input. Pointer to the MLU memory that stores the bias data used in the LayerNorm operation.
 *  @param[in]  output_desc
 *    Input. A descriptor of output tensor.
 *  @param[out]  output
 *    Output. Pointer to the MLU memory that stores an array of output data.
 *  @param[in]  layernorm_output_desc
 *    Input. A descriptor of layernorm_output tensor.
 *  @param[out]  layernorm_output
 *    Output. Pointer to the MLU memory that stores an array of LayerNorm output data.
 *  @retval  CNNL_STATUS_SUCCESS = 0
 *    The function ends normally.
 *  @retval  CNNL_STATUS_BAD_PARAM = 3
 *    One or more of the following conditions are satisfied:
 *    - Handle is NULL.
 *    - Input is NULL.
 *    - Output is NULL.
 *    - Dims are invalid.
 */
cnnlStatus_t CNNL_WIN_API cnnlBertBaseCasedPost(cnnlHandle_t handle,
                                                const cnnlTensorDescriptor_t input_desc,
                                                const void *input,
                                                const cnnlTensorDescriptor_t filter_desc,
                                                const void *filter,
                                                const cnnlTensorDescriptor_t bias_desc,
                                                const void *bias,
                                                const cnnlTransformerLayernormMode_t layernorm_mode,
                                                const cnnlTensorDescriptor_t layernorm_scale_desc,
                                                const void *layernorm_scale,
                                                const cnnlTensorDescriptor_t layernorm_bias_desc,
                                                const void *layernorm_bias,
                                                const cnnlTensorDescriptor_t output_desc,
                                                void *output,
                                                const cnnlTensorDescriptor_t layernorm_output_desc,
                                                void *layernorm_output);

/******************************************************************************
 * Cambricon CNNL OP: transformer_enc_dec_attn
 ******************************************************************************/
/*! The descriptor of enc-dec-attn function that holds transformer-network parameters. including
 * head_num, head_sizes, ln_res_mode, and quantify-params.*/
typedef struct cnnlTransformerEncDecAttnStruct *cnnlTransformerEncDecAttnDescriptor_t;

// Group:Transformer Enc Dec Attn
/*!
 *  @brief A function.
 *
 *  This function executes the encoder-decoder-attention in
 *  TransformerDecoderLayer.
 *
 *  **Formula**
 *
 *  This operation contains three steps:
 *
 *  1. Generate Q
 *
 *    Compute query from input tensor.
 *
 *    query = mlp(input_tensor, attr_kernel_Q)
 *
 *  2. Q x K batch_dot, softmax and QK x V batch_dot
 *
 *    Compute QxK batch_dot for all heads.
 *
 *    for head_id in (0, head_num)
 *
 *      QK = batch_dot(query_in_head, key_in_head)
 *
 *      QK = softmax(QK)
 *
 *      QKV = batch_dot(QK, value_in_head)
 *
 *  3. Generate output
 *
 *    Compute output from QKV.
 *
 *    output = mlp(QKV, attout_kernel)
 *
 *  **DataType**
 *
 *    When encout_mode is not CNNL_TRANSFORMER_ENCOUT_NOT_DATAFORMAT:
 *
 *      - input: float, half
 *      - filter:
 *          int16 (in MLU270 and MLU370)
 *          float, half (only in MLU370)
 *      - bias: float, half
 *      - output: float, half
 *
 *    When encout_mode is CNNL_TRANSFORMER_ENCOUT_NOT_DATAFORMAT:
 *
 *    For MLU270, MLU220, MLU290:
 *      - input: float, half
 *      - key: float, half
 *      - value: float, half
 *      - filter: int16
 *      - bias: float, half
 *      - output: float, half
 *
 *    For MLU370:
 *      - input: float, half
 *      - key: float, half
 *      - value: float, half
 *      - filter: float, half
 *      - bias: float, half
 *      - output: float, half
 *
 *  **Attention**
 *
 *  Encout_mode in cnnlTransformerEncDecAttnDescriptor_t is the output mode of
 *  transformer_encoder_output.
 *
 *  When encout_mode is CNNL_TRANSFORMER_ENCOUT_NOT_DATAFORMAT, this op will
 *  call enc_dec_attn kernel with cache, enc_output_key and enc_output_value is
 *  handled as input, they should share the same data type with input.
 *
 *  When encout_mode is not CNNL_TRANSFORMER_ENCOUT_NOT_DATAFORMAT, this op will
 *  call enc_dec_attn kernel without cache, enc_output_key and enc_output_value is
 *  handled as filter, they should share the same data type with attr_kernel_query
 *  and attout_kernel.
 *
 *  When encout_mode is not CNNL_TRANSFORMER_ENCOUT_NOT_DATAFORMAT, filter type
 *  must be int16 or int8 in MLU270.
 *
 *  DataType of enc_dec_attn_out, input_tensor, attr_bias_query, enc_output_mask,
 *  attout_bias, layernorm_scale and layernorm_bias must be the same.
 *
 *  If filter type is int8, precision of output is not guaranteed.
 *
 *  **Scale Limitation**
 *
 *  When encout_mode is not CNNL_TRANSFORMER_ENCOUT_NOT_DATAFORMAT:
 *
 *  According to the definition of transformer_enc_dec_attn, the parameters must
 *  satisfy the following conditions:
 *
 *  1. Batch_size and dec_seq_len has no limit.
 *
 *  2. Max_seq_len must be less than or equal to 1024 when filter type is int8
 *  or int16, and less than or equal to 512 when filter type is half or float.
 *
 *  3. Head_size_qk and head_size_v only support 64.
 *
 *  4. Head_num supports 4, 8, 12, 16.
 *
 *  5. Sizeof(float) * batch_size * max_seq_len_pad * hidden_size and
 *  sizeof(float) * batch_size * dec_seq_len_pad * hidden_size is limited in the
 *  value range of int type.
 *
 *  When encout_mode is CNNL_TRANSFORMER_ENCOUT_NOT_DATAFORMAT:
 *
 *  The parameters must satisfy the following conditions:
 *
 *  1. Batch_size should be equal to or less than 128.
 *
 *  2. Max_seq_len should be equal to or less than 512 in MLU270. equal to or
 *  less than 512 in MLU370. It should be equal to or less than 128 if head_num is 4 and
 *  head_size is in [65, 128] in MLU370. Max_seq_len should not be padded.
 *
 *  3. Head_num supports 8, 12, 16 in MLU270, and supports 4, 8, 12, 16 in MLU370.
 *
 *  4. Head_size_qk and head_size_v is in [1, 64] if head_num is 4, 8, 12, 16, and
 *  head_size_qk and head_size_v should be equal to or less than 128 if head_num is 4 and
 *  filter type is float or half. If filter type is int8 or int16, head_size_qk and
 *  head_size_v can only be set to 64.
 *
 *  5. Dec_seq_len would be treated as beam_size and should be equal to or less than
 *  12 in MLU270, and it would be treated as beam_size and should be equal to or less
 *  than 32 in MLU370.
 *
 *  6.  layernorm_res_mode can be set to CNNL_TRANSFORMER_NO_LAYERNORM_WITH_RESIDUAL,
 *  CNNL_TRANSFORMER_PRE_LAYERNORM_INSIDE_RESIDUAL and
 *  CNNL_TRANSFORMER_POST_LAYERNORM_OUTSIDE_RESIDUAL in MLU270.
 *
 *  7.  layernorm_res_mode can be set to CNNL_TRANSFORMER_NO_LAYERNORM_WITH_RESIDUAL,
 *  CNNL_TRANSFORMER_NO_LAYERNORM_NO_RESIDUAL and
 *  CNNL_TRANSFORMER_PRE_LAYERNORM_INSIDE_RESIDUAL in MLU370.

 *  **Performance Optimization**
 *
 *  When head_num is 12, batch_size is a multiple of 8, data_type and filters_type are half,
 *  dec_seq_len and max_seq_len are smaller than 128, encout_mode is not
 *  CNNL_TRANSFORMER_ENCOUT_NOT_DATAFORMAT, the performance is best on MLU370.
 *
 *  **Example**
 *
 *  When encout_mode is not CNNL_TRANSFORMER_ENCOUT_NOT_DATAFORMAT:
 *
 *    Dimension of enc_dec_attn_out: [batch_size, dec_seq_len, hidden_size]
 *
 *    Dimension of input_tensor: [batch_size, dec_seq_len, hidden_size]
 *
 *    Dimension of attr_kernel_query: [hidden_size, hidden_size]
 *
 *    Dimension of attr_bias_query: [hidden_size]
 *
 *    Dimension of enc_output_key: [batch_size, head_num, max_seq_len_pad, head_size]
 *
 *    Dimension of enc_output_value: [batch_size, head_num, head_size, max_seq_len_pad]
 *
 *    Dimension of enc_output_mask: [batch_size, max_seq_len]
 *
 *    Dimension of attout_kernel: [hidden_size, hidden_size]
 *
 *    Dimension of attout_bias: [hidden_size]
 *
 *    Dimension of layernorm_scale: [hidden_size]
 *
 *    Dimension of layernorm_bias: [hidden_size]
 *
 *  When encout_mode is CNNL_TRANSFORMER_ENCOUT_NOT_DATAFORMAT:
 *
 *    Dimension of enc_dec_attn_out: [batch_size, dec_seq_len, hidden_size]
 *
 *    Dimension of input_tensor: [batch_size, dec_seq_len, hidden_size]
 *
 *    Dimension of attr_kernel_query: [hidden_size, hidden_size]
 *
 *    Dimension of attr_bias_query: [hidden_size]
 *
 *    Dimension of enc_output_key: [batch_size, head_num, max_seq_len, head_size]
 *
 *    Dimension of enc_output_value: [batch_size, head_num, max_seq_len, head_size]
 *
 *    Dimension of enc_output_mask: [batch_size, max_seq_len]
 *
 *    Dimension of attout_kernel: [hidden_size, hidden_size]
 *
 *    Dimension of attout_bias: [hidden_size]
 *
 *    Dimension of layernorm_scale: [hidden_size]
 *
 *    Dimension of layernorm_bias: [hidden_size]
 *
 *
 *  **Reference**
 *
 *    papers.nips.cc/paper/7181-attention-is-all-you-need.pdf
 *
 *  **API Dependency**
 *
 *   You need to call the cnnlCreateTransformerEncDecAttnDescriptor(),
 *   cnnlSetTransformerEncDecAttnDescriptor()
 *   (or cnnlSetNoQuantifyTransformerEncDecAttnDescriptor() when filter data type
 *   is half/float) and
 *   cnnlGetTransformerEncDecAttnWorkspaceSize() functions before calling this
 *   function.
 *
 *   You need to call the cnnlDestroyTransformerEncDecAttnDescriptor() function
 *   after calling this function
 *
 *  @param[in] handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           transformer_enc_dec_attn operation.
 *  @param[in] transformer_enc_dec_attn_desc
 *    Input. A struct with param of transformer_enc_dec_attn op.
 *  @param[in] input_tensor_desc
 *    Input. Descriptor of input_tensor, which contains dimension of
 *           [batch_size, dec_seq_len, hidden_size].
 *  @param[in] input_tensor
 *    Input. Device pointer points to input_tensor space.
 *  @param[in] attr_kernel_query_desc
 *    Input. Descriptor of attr_kernel_query_desc, which contains dimension of
 *           [hidden_size, hidden_size].
 *  @param[in] attr_kernel_query
 *    Input. Device pointer points to attr_kernel_query space.
 *  @param[in] attr_bias_query_desc
 *    Input. Descriptor of attr_bias_query_desc, which contains dimension of
 *           [hidden_size].
 *  @param[in] attr_bias_query
 *    Input. Device pointer points to attr_bias_query space.
 *  @param[in] enc_output_key_desc
 *    Input. Descriptor of enc_output_key_desc, which contains dimension of
 *           [batch_size, head_num, max_seq_len_pad, head_size] if encout_mode
 *           is not CNNL_TRANSFORMER_ENCOUT_NOT_DATAFORMAT else
 *           [batch_size, head_num, max_seq_len, head_size].
 *  @param[in] enc_output_key
 *    Input. Device pointer points to enc_output_key space.
 *  @param[in] enc_output_value_desc
 *    Input. Descriptor of enc_output_value_desc, which contains dimension of
 *           [batch_size, head_num, max_seq_len_pad, head_size] if encout_mode
 *           is not CNNL_TRANSFORMER_ENCOUT_NOT_DATAFORMAT else
 *           [batch_size, head_num, max_seq_len, head_size].
 *  @param[in] enc_output_value
 *    Input. Device pointer points to enc_output_value space.
 *  @param[in] enc_output_mask_desc
 *    Input. Descriptor of enc_output_mask_desc, which contains dimension of
 *           [batch_size, 1, ..., max_seq_len] (can have arbitrary number of 1 between the first
 *            dim "batch_size" and the last dim "max_seq_len", including 0) or
 *           [batch_size, head_num, dec_seq_len, max_seq_len](only supported when encout_mode is
 *           not CNNL_TRANSFORMER_ENCOUT_NOT_DATAFORMAT.
 *  @param[in] enc_output_mask
 *    Input. Device pointer points to enc_output_mask space.
 *  @param[in] attout_kernel_desc
 *    Input. Descriptor of attout_kernel_desc, which contains dimension of
 *           [hidden_size, hidden_size].
 *  @param[in] attout_kernel
 *    Input. Device pointer points to attout_kernel space.
 *  @param[in] attout_bias_desc
 *    Input. Descriptor of attout_bias_desc, which contains dimension of
 *           [hidden_size].
 *  @param[in] attout_bias
 *    Input. Device pointer points to attout_bias space.
 *  @param[in] layernorm_scale_desc
 *    Input. Descriptor of layernorm_scale_desc, which contains dimension of
 *           [hidden_size].
 *  @param[in] layernorm_scale
 *    Input. Device pointer points to layernorm_scale space.
 *  @param[in] layernorm_bias_desc
 *    Input. Descriptor of layernorm_bias_desc, which contains dimension of
 *           [hidden_size].
 *  @param[in] layernorm_bias
 *    Input. Device pointer points to layernorm_bias space.
 *  @param[in]  workspace
 *    Input. The pointer to data address of workspace.
 *  @param[in]  workspace_size
 *    Input. The value of workspace_size.
 *  @param[in] enc_dec_attn_out_desc
 *    Input. Descriptor of enc_dec_attn_out, which contains dimension of
 *           [batch_size, dec_seq_len, hidden_size].
 *  @param[out] enc_dec_attn_out
 *    Output. Device pointer points to enc_dec_attn_out space.
 *
 *  @retval CNNL_STATUS_SUCCESS = 0
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM = 3
 *    One or more of following conditions are encountered:
 *    - handle is NULL.
 *    - pointer is NULL.
 *    - parameters do not meet scale limitation.
 *  @retval CNNL_STATUS_ARCH_MISMATCH
 *    One or more of following conditions are encountered:
 *    - This function is run on the hardware platform that is not supported.
 */
cnnlStatus_t CNNL_WIN_API
cnnlTransformerEncDecAttn(
    cnnlHandle_t handle,
    const cnnlTransformerEncDecAttnDescriptor_t transformer_enc_dec_attn_desc,
    const cnnlTensorDescriptor_t input_tensor_desc,
    const void* input_tensor,
    const cnnlTensorDescriptor_t attr_kernel_query_desc,
    const void* attr_kernel_query,
    const cnnlTensorDescriptor_t attr_bias_query_desc,
    const void* attr_bias_query,
    const cnnlTensorDescriptor_t enc_output_key_desc,
    const void* enc_output_key,
    const cnnlTensorDescriptor_t enc_output_value_desc,
    const void* enc_output_value,
    const cnnlTensorDescriptor_t enc_output_mask_desc,
    const void* enc_output_mask,
    const cnnlTensorDescriptor_t attout_kernel_desc,
    const void* attout_kernel,
    const cnnlTensorDescriptor_t attout_bias_desc,
    const void* attout_bias,
    const cnnlTensorDescriptor_t layernorm_scale_desc,
    const void* layernorm_scale,
    const cnnlTensorDescriptor_t layernorm_bias_desc,
    const void* layernorm_bias,
    void *workspace,
    size_t workspace_size,
    const cnnlTensorDescriptor_t enc_dec_attn_out_desc,
    const void* enc_dec_attn_out);

// Group:Transformer Enc Dec Attn
/*!
 *  @brief A function.
 *
 *  This function is used to create TransformerEncDecAttn descriptor.
 *
 *  @param[in] transformer_enc_dec_attn_desc
 *    Input. A pointer of transformer_enc_dec_attn operation to allocate memory.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_ALLOC_FAILED
 *    The function malloc memory space failed.
 */
cnnlStatus_t CNNL_WIN_API
cnnlCreateTransformerEncDecAttnDescriptor(
    cnnlTransformerEncDecAttnDescriptor_t* transformer_enc_dec_attn_desc);

// Group:Transformer Enc Dec Attn
/*!
 *  @brief A function.
 *
 *  This function is used to destroy TransformerEncDecAttn descriptor.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *  1.cnnlCreateTransformerEncDecAttnDescriptor().
 *
 *  @param[in] transformer_enc_dec_attn_desc
 *    Input. A struct of transformer_enc_dec_attn operation to free memory.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of transformer_enc_dec_attn_desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlDestroyTransformerEncDecAttnDescriptor(
    cnnlTransformerEncDecAttnDescriptor_t transformer_enc_dec_attn_desc);

// Group:Transformer Enc Dec Attn
/*!
 *  @brief A function.
 *
 *  This function is used to assign TransformerEncDecAttn descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *  1.cnnlCreateTransformerEncDecAttnDescriptor().
 *
 *  **Scale Limitation**
 *
 *  According to the definition of transformer_enc_dec_attn, the parameters must
 *  satisfy the following conditions:
 *
 *  Batch_size and dec_seq_len has no limit. Head_size_qk and head_size_v only
 *  support 64. Head_num supports 4, 8, 12, 16. Max_seq_len must be less than
 *  or equal to 1024 when filter type is int8 or int16, and less than or equal
 *  to 512 when filter type is half or float.
 *
 *  @param[in] transformer_enc_dec_attn_desc
 *    Input. A struct with param of transformer_enc_dec_attn op.
 *  @param[in]  head_num
 *    Input. The number of heads in self attention.
 *  @param[in]  head_size_qk
 *    Input. The size of one head in self attention for query and key.
 *  @param[in]  head_size_v
 *    Input. The size of one head in self attention for value.
 *  @param[in]  max_seq_len
 *    Input. Sequence length in transformer encoder.
 *  @param[in]  query_factor
 *    Input. Parameter indicates scale multiplication to query.
 *  @param[in]  ln_res_mode
 *    Input. The layernorm and residual structure.
 *  @param[in] enable_online_quantify
 *    Input. The flag of whether to enable the online quantify.
 *  @param[in] use_quantify_scale
 *    Input. The flag of whether to use scale in quantifization.
 *  @param[in] query_input_pos
 *    Input. The query input quantify position.
 *  @param[in]  query_input_scale
 *    Input. The query input quantify scale.
 *  @param[in] query_out_pos
 *    Input. The query output quantify position.
 *  @param[in]  query_out_scale
 *    Input. The query output quantify scale.
 *  @param[in] softmax_out_pos
 *    Input. The softmax output quantify position.
 *  @param[in]  softmax_out_scale
 *    Input. The softmax output quantify scale.
 *  @param[in] qkv_out_pos
 *    Input. The qkv batchdot output quantify position.
 *  @param[in]  qkv_out_scale
 *    Input. The qkv batchdotoutput quantify scale.
 *  @param[in]  use_bias
 *    Input. Whether to use bias when compute query and attention output.
 *  @param[in] encout_mode
 *    Input. Output mode of TransformerEncoderOutput.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of transformer_enc_dec_attn_desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetTransformerEncDecAttnDescriptor(
    cnnlTransformerEncDecAttnDescriptor_t transformer_enc_dec_attn_desc,
    const int head_num,
    const int head_size_qk,
    const int head_size_v,
    const int max_seq_len,
    const float query_factor,
    const cnnlTransformerLayernormResidualStructure_t ln_res_mode,
    const bool enable_online_quantify,
    const bool use_quantify_scale,
    const int16_t query_input_pos,
    const float query_input_scale,
    const int16_t query_out_pos,
    const float query_out_scale,
    const int16_t softmax_out_pos,
    const float softmax_out_scale,
    const int16_t qkv_out_pos,
    const float qkv_out_scale,
    const bool use_bias,
    const cnnlTransformerEncOutMode_t encout_mode);

// Group:Transformer Enc Dec Attn
/*!
 *  @brief A function.
 *
 *  This function is used to assign TransformerEncDecAttn descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *  1.cnnlCreateTransformerEncDecAttnDescriptor().
 *
 *  **Scale Limitation**
 *
 *  According to the definition of transformer_enc_dec_attn, the parameters must
 *  satisfy the following conditions:
 *
 *  Batch_size and dec_seq_len has no limit. Head_size_qk and head_size_v only
 *  support 64. Head_num supports 4, 8, 12, 16. Max_seq_len must be less than
 *  or equal to 1024 when filter type is int8 or int16, and less than or equal
 *  to 512 when filter type is half or float.
 *
 *  @param[in] transformer_enc_dec_attn_desc
 *    Input. A struct with param of transformer_enc_dec_attn op.
 *  @param[in]  head_num
 *    Input. The number of heads in self attention.
 *  @param[in]  head_size_qk
 *    Input. The size of one head in self attention for query and key.
 *  @param[in]  head_size_v
 *    Input. The size of one head in self attention for value.
 *  @param[in]  max_seq_len
 *    Input. Sequence length in transformer encoder.
 *  @param[in]  query_factor
 *    Input. Parameter indicates scale multiplication to query.
 *  @param[in]  ln_res_mode
 *    Input. The layernorm and residual structure.
 *  @param[in]  use_bias
 *    Input. Whether to use bias when compute query and attention output.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of transformer_enc_dec_attn_desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetNoQuantifyTransformerEncDecAttnDescriptor(
    cnnlTransformerEncDecAttnDescriptor_t transformer_enc_dec_attn_desc,
    const int head_num,
    const int head_size_qk,
    const int head_size_v,
    const int max_seq_len,
    const float query_factor,
    const cnnlTransformerLayernormResidualStructure_t ln_res_mode,
    const bool use_bias,
    const cnnlTransformerEncOutMode_t encout_mode);

// Group:Transformer Enc Dec Attn
/*!
 *  @brief A function.
 *  This function is used to get extra space size that needed in transformer
 *  enc_dec_attn operation.
 *
 *  @param[in] transformer_enc_dec_attn_desc
 *    Input. A struct with param of transformer_enc_dec_attn op.
 *  @param[in] input_tensor_desc
 *    Input. Descriptor of input_tensor, which contains dimension of
 *           [batch_size, dec_seq_len, hidden_size].
 *  @param[in] enc_output_key_desc
 *    Input. Descriptor of enc_output_key_desc, which contains dimension of
 *           [batch_size, head_num, max_seq_len_pad, head_size].
 *  @param[out] size
 *    Output. Size of workspace.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of transformer_enc_dec_attn_desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlGetTransformerEncDecAttnWorkspaceSize(
    const cnnlTransformerEncDecAttnDescriptor_t transformer_enc_dec_attn_desc,
    const cnnlTensorDescriptor_t input_tensor_desc,
    const cnnlTensorDescriptor_t enc_output_key_desc,
    size_t *size);

// Group:Transformer Enc Dec Attn
/*!
 *  @brief A function.
 *  This function is used to layout attr_kernel_query and attout_kernel.
 *
 * @param[in] attr_kernel_query_input_desc
 *    Input. Descriptor of attr_kernel_query_input_desc, which contains dimension of
 *           [hidden_size, hidden_size].
 *  @param[in] attr_kernel_query_input
 *    Input. Device pointer points to attr_kernel_query_input space.
 *  @param[in] attout_kernel_input_desc
 *    Input. Descriptor of attout_kernel_input_desc, which contains dimension of
 *           [hidden_size, hidden_size].
 *  @param[in] attout_kernel_input
 *    Input. Device pointer points to attout_kernel space.
 * @param[in] attr_kernel_query_output_desc
 *    Input. Descriptor of attr_kernel_query_output_desc, which contains dimension of
 *           [hidden_size, hidden_size].
 *  @param[out] attr_kernel_query_output
 *    Input. Device pointer points to attr_kernel_query_output space.
 *  @param[in] attout_kernel_output_desc
 *    Input. Descriptor of attout_kernel_output_desc, which contains dimension of
 *           [hidden_size, hidden_size].
 *  @param[out] attout_kernel_output
 *    Input. Device pointer points to attout_kernel space.
 *  @param[in] order
 *    Input. The data order of filter matrix.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - pointer is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlReformatTransformerEncDecAttnFilter(
    const cnnlTensorDescriptor_t attr_kernel_query_input_desc,
    const void* attr_kernel_query_input,
    const cnnlTensorDescriptor_t attout_kernel_input_desc,
    const void* attout_kernel_input,
    const cnnlTensorDescriptor_t attr_kernel_query_output_desc,
    const void* attr_kernel_query_output,
    const cnnlTensorDescriptor_t attout_kernel_output_desc,
    const void* attout_kernel_output,
    cnnlTransformerMatrixOrder_t order);

/******************************************************************************
 * Cambricon CNNL OP: TransformerFFN
 ******************************************************************************/
/*! The descriptor of the transformer ffn operation that holds ffn information
 *  including the number of input active_mode, layernorm_mode, enable_online_quantify,
 *  use_quantify_scale, use_residual, enable_reshape_filters, inter_quantify_pos,
 *  inter_quantify_scale hidden_size, filter_size.
 *
 *  You need to call the ::cnnlCreateTransformerFFNDescriptor function
 *  to create a descriptor, and call the ::cnnlSetTransformerFFNDescriptor or
 *  ::cnnlSetTransformerFFNDescriptor_v2 function to set the information of
 *  the ffn operation to the descriptor. Also, you need to
 *  destroy the Cambricon CNNL context at the end with the ::cnnlDestroyTransformerFFNDescriptor
 *  function.
 */
typedef struct cnnlTransformerFFNStruct *cnnlTransformerFFNDescriptor_t;

// Group:Transformer FFN
/*!
 *  @brief A function.
 *
 *  the ffn layer in transformer network.
 *
 *  **Formula**
 *
 *  This operation contains follow steps:
 *
 *  1. fc
 *
 *    intermediate = fc(input, inner_filters, inner_bias)
 *
 *  2. activation
 *
 *    intermediate = active(intermediate)
 *
 *  3. fc
 *
 *    output = fc(intermediate, outer_filters, outer_bias)
 *
 *  4. layernorm
 *
 *    no layernorm: output = ffn(input).
 *
 *    pre layernorm: output = ffn(layernorm(input)) + input.
 *
 *    post layernorm: output = layernorm(ffn(input) + input).
 *
 *  **DataType**
 *
 *  - input: float, half.
 *
 *  - inner filters: int16, int8, half, float.
 *
 *  - inner bias: float, half.
 *
 *  - outer filters: int16, int8, half, float.
 *
 *  - outer bias: float, half.
 *
 *  - layernorm scale: float, half.
 *
 *  - layernorm bias: float, half.
 *
 *  - output: float, half.
 *
 *  **Attention: **
 *
 *    - The data type of inner_filters must be same with outer_filters.
 *
 *    - The data type of input, output, inner_bias, outer_bias, layernorm_scale,
 *      and layernorm_bias must be the same.
 *
 *    - The data type of input, output, inner_filters and outer_filters must be same in MLU300 series.
 *
 *    - Reshape filters on device is not supported, set enable_reshape_filters = false.
 *
 *    - Layernorm and Residual Structure does not support CNNL_TRANSFORMER_POST_LAYERNORM_INSIDE_RESIDUAL.
 *      Only transformer base, bert base, bert large and scama support CNNL_TRANSFORMER_PRE_LAYERNORM_OUTSIDE_RESIDUAL.
 *
 *    - When datatype of inner_filters and outer_filters is int8, following conditions must be meet:
 *      FFN is used for bert base and bert large, input datatype is half, enable_online_quantify == false,
 *      layernorm_structure == CNNL_TRANSFORMER_PRE_LAYERNORM_OUTSIDE_RESIDUAL, post_scale == 1.0,
 *      active_mode != CNNL_ACTIVATION_SWISH and device must be 370-X4.
 *      Note that int8 datatype of filters is used to cooperate with quantitative perception training,
 *      means that only inference process may has accuracy risks.
 *
 *
 *  **Scale Limitation**
 *
 *    According to the definition of transformer_ffn, the parameters must satisfy
 *    the following conditions:
 *
 *    - The number of dimensions of all tensors must match.
 *
 *    - batch_num and seq_len has no limit. batch_num and seq_len must be greater than 0.
 *
 *    - filters_size = hidden_size * filter_size * sizeof(filters_dt):
 *    - 0 < filters_size <= 16MB.
 *    - 0 < filters_size <= 2MB: hidden_size is divisible by 64 and filter_size is divisible by 256.
 *    - 2MB < filters_size <= 4MB: hidden_size is divisible by 128 and filter_size is divisible by 512.
 *    - 4MB < filters_size <= 16MB: hidden_size is divisible by 256 and filter_size is divisible by 1024.
 *
 *    If enable_inner_layernormal of \b desc is set to true, following requirements must be satisfied:
 *    - PAD_UP(hidden_size, 256) * PAD_UP(filter_size, 256) * sizeof(data type) <= 4MB
 *    - Data types of input, filters and output must be the same, either float or half.
 *    - Dimension of layernorm_scale and layernorm_bias must be [hidden_size + filter_size], where [0:hidden_size]
 *      contains scale and bias for pre or post layernormal, and [hidden_size:-1] contains scale and bias for
 *      inner layernormal. If pre/post layernormal is disabled, data in [0:hidden_size] is ignored.
 *
 *  **Performance Optimization**
 *
 *    When hidden_size * filter_size is small
 *    (hidden_size * filter_size / 4 * sizeof(filters_data type) <= 512 * 1024),
 *    the performance is the best.
 *
 *  **Example**
 *
 *    Dimension of input: [batch_num, seq_len, hidden_size]
 *
 *    Dimension of inner_filters: [hidden_size, filter_size]
 *
 *    Dimension of inner_bias: [filter_size]
 *
 *    Dimension of outer_filters: [filter_size, hidden_size]
 *
 *    Dimension of outer_bias: [hidden_size]
 *
 *    Dimension of layernorm_scale: [hidden_size] or [hidden_size + filter_size] when enable_inner_layernormal is set to true.
 *
 *    Dimension of layernorm_bias: [hidden_size] or [hidden_size + filter_size] when enable_inner_layernormal is set to true.
 *
 *    Then we will get the output:
 *
 *    Dimension of output: [batch_num, seq_len, hidden_size]
 *
 *  **API Dependency**
 *
 *   You need to call the cnnlCreateTransformerFFNDescriptor(), and
 *   cnnlGetTransformerFFNWorkspaceSize() functions before calling this function.
 *
 *   You need to call the cnnlDestroyTransformerFFNDescriptor() function after
 *   calling this function
 *
 *  @param[in]  handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           transformer_ffn operation.
 *  @param[in] desc
 *    Input. A struct with parameters of transformer.
 *  @param[in]  input_desc
 *    Input. Descriptor of input, containing dimension and the layout of input.
 *  @param[in]  input
 *    Input. Device pointer points to input space.
 *  @param[in]  inner_filters_desc
 *    Input. Descriptor of inner_filters, containing dimension and the layout of
 *           inner_filters.
 *  @param[in]  inner_filters
 *    Input. Device pointer points to inner_filters space.
 *  @param[in]  inner_bias_desc
 *    Input. Descriptor of inner_bias, containing dimension and the layout of
 *           inner_bias.
 *  @param[in]  inner_bias
 *    Input. Device pointer points to inner_bias space.
 *  @param[in]  outer_filters_desc
 *    Input. Descriptor of outer_filters, containing dimension and the layout of
 *           outer_filters.
 *  @param[in]  outer_filters
 *    Input. Device pointer points to outer_filters space.
 *  @param[in]  outer_bias_desc
 *    Input. Descriptor of outer_bias, containing dimension and the layout of
 *           outer_bias.
 *  @param[in]  outer_bias
 *    Input. Device pointer points to outer_bias space.
 *  @param[in]  layernorm_scale_desc
 *    Input. Descriptor of layernorm_scale, containing dimension and the layout
 *           of layernorm_scale.
 *  @param[in]  layernorm_scale
 *    Input. Device pointer points to layernorm_scale space.
 *  @param[in]  layernorm_bias_desc
 *    Input. Descriptor of layernorm_bias, containing dimension and the layout
 *           of layernorm_bias.
 *  @param[in]  layernorm_bias
 *    Input. Device pointer points to layernorm_bias space.
 *  @param[out]  output_desc
 *    Input. Descriptor of output, containing dimension and the layout of output.
 *  @param[out]  output
 *    Input. Device pointer points to output space.
 *  @retval CNNL_STATUS_SUCCESS = 0
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM = 3
 *    One or more of the following conditions are encountered:
 *    - handle is NULL.
 *    - pointer is NULL.
 *    - parameters do not meet scale limitation.
 *  @retval CNNL_STATUS_ARCH_MISMATCH
 *    One or more of the following conditions are encountered:
 *    - This function is run on the hardware platform that is not supported.
 */
cnnlStatus_t CNNL_WIN_API
cnnlTransformerFFN(cnnlHandle_t handle,
                   const cnnlTransformerFFNDescriptor_t desc,
                   const cnnlTensorDescriptor_t input_desc,
                   const void *input,
                   const cnnlTensorDescriptor_t inner_filters_desc,
                   const void *inner_filters,
                   const cnnlTensorDescriptor_t inner_bias_desc,
                   const void *inner_bias,
                   const cnnlTensorDescriptor_t outer_filters_desc,
                   const void *outer_filters,
                   const cnnlTensorDescriptor_t outer_bias_desc,
                   const void *outer_bias,
                   const cnnlTensorDescriptor_t layernorm_scale_desc,
                   const void *layernorm_scale,
                   const cnnlTensorDescriptor_t layernorm_bias_desc,
                   const void *layernorm_bias,
                   void *workspace,
                   size_t workspace_size,
                   cnnlTensorDescriptor_t output_desc,
                   void *output);

// Group:Transformer FFN
/*!
 *  @brief A function.
 *
 *  This function is used to create a descriptor of transformerfnn and malloc
 *  memory for it.
 *
 *  @param[in]  desc
 *    Input. Description of transformerfnn operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_ALLOC_FAILED
 *    The function malloc memory space failed.
 */
cnnlStatus_t CNNL_WIN_API
cnnlCreateTransformerFFNDescriptor(cnnlTransformerFFNDescriptor_t *desc);

// Group:Transformer FFN
/*!
 *  @brief A function.
 *
 *  This function is used to destroy a descriptor of transformerfnn and free
 * memory for it.
 *
 *  @param[in]  desc
 *    Input. Description of transformerfnn operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlDestroyTransformerFFNDescriptor(cnnlTransformerFFNDescriptor_t desc);

// Group:Transformer FFN
/*!
 *  @brief A function.
 *
 *  This function is used to assign transformerffn descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *     Users need handle transformer descriptor, use
 *     cnnlCreateTransformerFFNDescriptor() to create descriptor and use
 *     cnnlSetTransformerFFNDescriptor() to set its parameters.
 *
 *  @param[in]  desc
 *    Input. Description of transformer operation.
 *  @param[in]  active_mode
 *    Input. Activation mode of ffn layer, support relu and gelu.
 *  @param[in]  layernorm_structure
 *    Input. The layernorm and residual structure.
 *  @param[in]  enable_online_quantify
 *    Input. The flag of enable the online quantify.
 *    When enable_online_quantify = true, input and intermediate data quantify
 *    online.
 *  @param[in]  use_quantify_scale
 *    Input. Whether to use quantify scale.
 *  @param[in]  enable_reshape_filters
 *    Input. When enable_reshape_filters = true, inner filters and outer filters
 *    will be reshaped on device.
 *  @param[in]  inter_quantify_pos
 *    Input. The intermediate result quantify position.
 *    It's valid when online_quantify = false.
 *  @param[in]  inter_quantify_scale
 *    Input. The intermediate result quantify scale.
 *    It's valid when online_quantify = false.
 *  @param[in]  hidden_size
 *    Input. The size of embedding.
 *  @param[in]  filter_size
 *    Input. The size of filter.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetTransformerFFNDescriptor(
    cnnlTransformerFFNDescriptor_t desc,
    const cnnlActivationMode_t active_mode,
    const cnnlTransformerLayernormResidualStructure_t layernorm_structure,
    const bool enable_online_quantify,
    const bool use_quantify_scale,
    const bool enable_reshape_filters,
    const int16_t inter_quantify_pos,
    const float inter_quantify_scale,
    const int hidden_size,
    const int filter_size);

// Group:Transformer FFN
/*!
 *  @brief A function.
 *
 *  This function is used to assign transformerffn descriptor with parameters.
 *  Comparing with cnnlSetTransformerFFNDescriptor, this function allows user to
 *  specify more active modes and supports to set scale parameters which are used
 *  to multiply after the second fully connect layer.
 *
 *  **API Dependency**
 *
 *  Before using this function, users need to invoke ::cnnlCreateTransformerFFNDescriptor()
 *  to create the descriptor.
 *
 *  @param[in]  desc
 *    Input. Descriptor of TransformerFFN operation.
 *  @param[in]  active_mode
 *    Input. Activation mode of ffn layer. It supports relu, gelu and swish.
 *  @param[in]  layernorm_structure
 *    Input. The layernorm and residual structure.
 *  @param[in]  enable_online_quantify
 *    Input. An boolean value indicating whether to enable online quantization.
 *    When enable_online_quantify = true, input and intermediate data quantify
 *    online.
 *  @param[in]  use_quantify_scale
 *    Input. Whether to use quantization scale.
 *  @param[in]  enable_reshape_filters
 *    Input. When enable_reshape_filters = true, inner filters and outer filters
 *    will be reshaped on device.
 *  @param[in]  inter_quantify_pos
 *    Input. The intermediate result quantization position.
 *    It's valid when enable_online_quantify = false.
 *  @param[in]  inter_quantify_scale
 *    Input. The intermediate result quantization scale.
 *    It's valid when enable_online_quantify = false.
 *  @param[in]  hidden_size
 *    Input. The size of embedding.
 *  @param[in]  filter_size
 *    Input. The size of filter.
 *  @param[in]  post_scale.
 *    Input. The parameter used to multiply after the second fully connection layer.
 *    Default is 1.0.
 *  @param[in]  active_coef.
 *    Input. The coefficient used in the swish activation. Default is 1.0.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    Two of the following conditions are met:
 *    - The value of desc is NULL.
 *    - The value of post scale is 0.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetTransformerFFNDescriptor_v2(
    cnnlTransformerFFNDescriptor_t desc,
    const cnnlActivationMode_t active_mode,
    const cnnlTransformerLayernormResidualStructure_t layernorm_structure,
    const bool enable_online_quantify,
    const bool use_quantify_scale,
    const bool enable_reshape_filters,
    const int16_t inter_quantify_pos,
    const float inter_quantify_scale,
    const int hidden_size,
    const int filter_size,
    const float post_scale,
    const float active_coef);

// Group:Transformer FFN
/*!
 *  @brief A function.
 *
 *  This function is used to enable or disable inner layernormal of transformerffn.
 *  If this function is never called, inner layernormal is disabled by default.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *     Users need handle transformer descriptor, use
 *     cnnlCreateTransformerFFNDescriptor() to create descriptor and use
 *     cnnlSetTransformerFFNDescriptor() or cnnlSetTransformerFFNDescriptor_v2()
 *     to set its parameters.
 *
 *  @param[in]  desc
 *    Input. Description of transformer operation.
 *  @param[in]  enable_inner_layernormal
 *    Input. Whether to add another layer normalization layer between 2 fully connect layers.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 *
 *  @note
 *  - If \b enable_inner_layernormal is set to true, following requirements must be satisfied:
 *    - hidden_size = 256
 *    - filter_size = 1024
 *    - Data types of input, filters and output must be HALF.
 * */
cnnlStatus_t CNNL_WIN_API
cnnlSetTransformerFFNDescriptorInnerLayernormalMode(
    cnnlTransformerFFNDescriptor_t desc,
    bool enable_inner_layernormal
);

// Group:Transformer FFN
/*!
 *  @brief A function.
 *
 *  This function is used to set precision mode of transformerffn. If this function is
 *  never called, compute with the data type of \b input by default.
 *
 *  @param[in]  desc
 *    Input. Descriptor of transformer operation.
 *  @param[in]  use_hp_active
 *    Input. A boolean value indicates whether to use high precision activation function.
 *  @param[in]  compute_dtype
 *    Input. The data type used in the computing.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 *
 *  @note
 *  - This function only supports transformer base, bert base, and bert large.
 *  - The data type of filters must be half or float.
 *  - When the data type of filters is float, the data type used in the computing must be float.
 *  - When the data type of filters and the data type used in the computing are both half,
 *    post layernorm is not allowed.
 * */
cnnlStatus_t CNNL_WIN_API
cnnlSetTransformerFFNPrecisionMode(
    cnnlTransformerFFNDescriptor_t desc,
    const bool use_hp_active,
    const cnnlDataType_t compute_dtype
);

// Group:Transformer FFN
/*!
 *  @brief A function.
 *  This function is used to get extra space size that needed in transformer
 *  ffn operation.
 *
 *  **API Dependency**
 *
 *  You need to call the cnnlCreateTransformerFFNDescriptor(), and
 *  cnnlSetTransformerFFNDescriptor() or cnnlSetTransformerFFNDescriptor_v2()
 *  functions before calling this function.
 *
 *  You need to call the cnnlDestroyTransformerFFNDescriptor() function after
 *  calling this function
 *
 *  @param[in]  handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           transformer_ffn operation.
 *  @param[in]  desc
 *    Input. Parameter description of transformer.
 *  @param[in]  input_desc
 *    Input. Descriptor of input, containing dimension and the layout of input.
 *  @param[in]  output_desc
 *    Input. Descriptor of output, containing dimension and the layout of output.
 *  @param[in]  inner_filters_desc
 *    Input. Descriptor of inner_filters, containing dimension and the layout of
 *           inner_filters.
 *  @param[in]  outer_filters_desc
 *    Input. Descriptor of outer_filters, containing dimension and the layout of
 *           outer_filters.
 *  @param[out] size
 *    Output. Size of workspace.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlGetTransformerFFNWorkspaceSize(cnnlHandle_t handle,
                                   const cnnlTransformerFFNDescriptor_t desc,
                                   const cnnlTensorDescriptor_t input_desc,
                                   const cnnlTensorDescriptor_t output_desc,
                                   const cnnlTensorDescriptor_t inner_filters_desc,
                                   const cnnlTensorDescriptor_t outer_filters_desc,
                                   size_t *size);

// Group:Transformer FFN
/*!
 *  @brief A function.
 *  This function is used to reshape filters for lt.
 *
 *  **API Dependency**
 *
 *  You need to call the cnnlGetTransformerFFNFilterDescriptor() to alloc host space
 *  for inner and outer filters after reformat.
 *
 *  @param[in]  device_type
 *    Input. The variables describing the MLU device information used for the
 *           host reorder.
 *  @param[in]  inner_filters_desc
 *    Input. Descriptor of input inner filters, containing dimension and the
 *           layout of inner filters.
 *  @param[in]  inner_filters_order
 *    Input. Order type of inner filters.
 *  @param[in]  inner_filters_input_host
 *    Input. Host pointer points to inner filters space.
 *  @param[in]  outer_filters_desc
 *    Input. Descriptor of input outer filters, containing dimension and the
 *           layout of outer_filters.
 *  @param[in]  outer_filters_order
 *    Input. Order type of outer filters.
 *  @param[in]  outer_filters_input_host
 *    Input. Host pointer points to outer filters space.
 *  @param[out]  inner_filters_output_host
 *    Input. Host pointer points to new inner filters space.
 *  @param[out]  outer_filters_output_host
 *    Input. Host pointer points to new outer filters space.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlReformatTransformerFFNFilter(cnnlDeviceType_t device_type,
                                 const cnnlTensorDescriptor_t inner_filters_desc,
                                 const cnnlTransformerMatrixOrder_t inner_filters_order,
                                 const void *inner_filters_input_host,
                                 const cnnlTensorDescriptor_t outer_filters_desc,
                                 const cnnlTransformerMatrixOrder_t outer_filters_order,
                                 const void *outer_filters_input_host,
                                 void *inner_filters_output_host,
                                 void *outer_filters_output_host);

// Group:Transformer FFN
/*!
 *  @brief A function.
 *  This function is used to get inner and outer filters space size after reformat
 *  ffn filter that needed in transformer ffn operation.
 *
 *  **API Dependency**
 *
 *  You need to call the cnnlCreateTransformerFFNDescriptor(), and
 *  cnnlSetTransformerFFNDescriptor() or cnnlSetTransformerFFNDescriptor_v2()
 *  functions before calling this function.
 *
 *  You need to call the cnnlDestroyTransformerFFNDescriptor() function after
 *  calling this function
 *
 *  @param[in]  device_type
 *    Input. The variables describing the MLU device information used for the
 *           host reorder.
 *  @param[in]  inner_filters_desc
 *    Input. Descriptor of inner_filters, containing dimension and the layout of
 *           inner_filters.
 *  @param[in]  inner_filters_order
 *    Input. Order type of inner filters.
 *  @param[in]  outer_filters_desc
 *    Input. Descriptor of outer_filters, containing dimension and the layout of
 *           outer_filters.
 *  @param[in]  outer_filters_order
 *    Input. Order type of outer filters.
 *  @param[out]  inner_filters_output_desc
 *    Input. Descriptor of output inner filters, containing dimension and the
 *           layout of inner filters.
 *  @param[out]  outer_filters_output_desc
 *    Input. Descriptor of output outer filters, containing dimension and the
 *           layout of outer_filters.
 *  @param[out] inner_filters_size
 *    Output. Size of inner filters space.
 *  @param[out] outer_filters_size
 *    Output. Size of outer filters space.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlGetTransformerFFNFilterDescriptor(cnnlDeviceType_t device_type,
                                      const cnnlTensorDescriptor_t inner_filters_desc,
                                      const cnnlTransformerMatrixOrder_t inner_filters_order,
                                      const cnnlTensorDescriptor_t outer_filters_desc,
                                      const cnnlTransformerMatrixOrder_t outer_filters_order,
                                      cnnlTensorDescriptor_t inner_filters_output_desc,
                                      cnnlTensorDescriptor_t outer_filters_output_desc);

// Group:Transformer FFN
/*!
 *  @brief A function.
 *
 *  This function is used to assign transformerffn descriptor with parameters in
 *  the quantization scenario.
 *
 *  **API Dependency**
 *
 *  Before calling this function, users need to use cnnlCreateTransformerFFNDescriptor()
 *  to create the descriptor.
 *
 *  @param[in]  desc
 *    Input. Descriptor of transformerffn operation.
 *  @param[in]  active_mode
 *    Input. Activation mode of ffn layer, which supports relu and gelu.
 *  @param[in]  layernorm_structure
 *    Input. The layernorm and residual structure.
 *  @param[in]  enable_online_quantify
 *    Input. A boolean value indicates whether to enable online quantization.
 *    When enable_online_quantify = true, input and intermediate data are quantized
 *    online.
 *  @param[in]  enable_reshape_filters
 *    Input. A boolean value indicates whether to reshape filters on device.
 *  @param[in]  use_quantify_scale
 *    Input. A boolean value indicates whether to use the quantization scaling factor.
 *  @param[in]  use_quantify_offset
 *    Input. A boolean value indicates whether to use the quantization offset.
 *  @param[in]  use_hp_active
 *    Input. A boolean value indicates whether to use high precision activation function.
 *  @param[in]  residual_input_quant
 *    Input. A boolean value indicates whether to quantify the residual input.
 *  @param[in]  local_input_quant
 *    Input. A boolean value indicates whether to quantize the local input.
 *  @param[in]  use_fc1_aftergemm_quant_params
 *    Input. A boolean value indicates whether to use fc1_aftergemm_position and
 *    fc1_aftergemm_scale when dequantizing fc1.
 *  @param[in]  use_fc2_aftergemm_quant_params
 *    Input. A boolean value indicates whether to use fc2_aftergemm_position and
 *    fc2_aftergemm_scale when dequantizing fc2.
 *  @param[in]  quant_per_tensor
 *    Input. A boolean value indicates whether to quantize the filters of ffn by tensor.
 *    If this parameter is true, quantization is done  by tensor, otherwise by channel.
 *  @param[in]  layernorm_eps
 *    Input. The epsilon value of layernorm.
 *  @param[in]  post_scale.
 *    Input. The parameter used to multiply after the second fully connection layer.
 *    Default is 1.0.
 *  @param[in]  active_coef.
 *    Input. The coefficient used in the swish activation. Default is 1.0.
 *  @param[in]  hidden_size
 *    Input. The size of embedding.
 *  @param[in]  filter_size
 *    Input. The size of filter.
 *  @param[in]  compute_dtype
 *    Input. The data type used in the computing.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetTransformerFFNQATDescriptor(
    cnnlTransformerFFNDescriptor_t desc,
    const cnnlActivationMode_t active_mode,
    const cnnlTransformerLayernormResidualStructure_t layernorm_structure,
    const bool enable_online_quantify,
    const bool enable_reshape_filters,
    const bool use_quantify_scale,
    const bool use_quantify_offset,
    const bool use_hp_active,
    const bool residual_input_quant,
    const bool local_input_quant,
    const bool use_fc1_aftergemm_quant_params,
    const bool use_fc2_aftergemm_quant_params,
    const bool quant_per_tensor,
    const float layernorm_eps,
    const float post_scale,
    const float active_coef,
    const int hidden_size,
    const int filter_size,
    const cnnlDataType_t compute_dtype);

// Group:Transformer FFN
/*!
 *  @brief A function.
 *
 *  This function is used to assign transformerffn descriptor with
 *  quantization parameters in the quantization scenario.
 *
 *  **API Dependency**
 *
 *  Before calling this function, users need to use cnnlCreateTransformerFFNDescriptor()
 *  to create the descriptor.
 *
 *  @param[in]  desc
 *    Input. Descriptor of transformerffn operation.
 *  @param[in]  fc1_output_position
 *    Input. The quantization position of the fc1 output.
 *  @param[in]  fc1_output_scale
 *    Input. The quantization scaling factor of the fc1 output.
 *  @param[in]  fc1_output_offset
 *    Input. The quantization offset of the fc1 output.
 *  @param[in]  local_input_position
 *    Input. The quantization position of the local input.
 *  @param[in]  local_input_scale
 *    Input. The quantization scaling factor of the local output.
 *  @param[in]  local_input_offset
 *    Input. The quantization offset of the local output.
 *  @param[in]  fc1_aftergemm_position
 *    Input. The quantization position of the fc1 aftergemm.
 *  @param[in]  fc1_aftergemm_scale
 *    Input. The quantization scaling factor of the fc1 aftergemm.
 *  @param[in]  fc1_aftergemm_offset
 *    Input. The quantization offset of the fc1 aftergemm.
 *  @param[in]  fc2_aftergemm_position
 *    Input. The quantization position of the fc2 aftergemm.
 *  @param[in]  fc2_aftergemm_scale
 *    Input. The quantization scaling factor of the fc2 aftergemm.
 *  @param[in]  fc2_aftergemm_offset
 *    Input. The quantization offset of the fc2 aftergemm.
 *  @param[in]  inner_filters_position
 *    Input. Device pointer points to the quantization positions of the inner filters.
 *  @param[in]  inner_filters_scale
 *    Input. Device pointer points to the quantization scaling factors of the inner filters.
 *  @param[in]  inner_filters_offset
 *    Input. Device pointer points to the quantization offsets of the inner filters.
 *  @param[in]  outer_filters_position
 *    Input. Device pointer points to the quantization positions of the outer filters.
 *  @param[in]  outer_filters_scale
 *    Input. Device pointer points to the quantization scaling factors of the outer filters.
 *  @param[in]  outer_filters_offset
 *    Input. Device pointer points to the quantization offsets of the outer filters.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetTransformerFFNQATQuantifyParams(
    cnnlTransformerFFNDescriptor_t desc,
    const int fc1_output_position,
    const float fc1_output_scale,
    const int fc1_output_offset,
    const int local_input_position,
    const float local_input_scale,
    const int local_input_offset,
    const int fc1_aftergemm_position,
    const float fc1_aftergemm_scale,
    const int fc1_aftergemm_offset,
    const int fc2_aftergemm_position,
    const float fc2_aftergemm_scale,
    const int fc2_aftergemm_offset,
    const void *inner_filters_positions,
    const void *inner_filters_scales,
    const void *inner_filters_offsets,
    const void *outer_filters_positions,
    const void *outer_filters_scales,
    const void *outer_filters_offsets);

/******************************************************************************
 * Cambricon CNNL Transformer self attention mask mode
 ******************************************************************************/
//! @brief An enum.
/*! Enumeration variables describe the mode of mask for transformer self attention. */
typedef enum {
  CNNL_TRANSFORMER_SELF_ATTN_NO_MASK = 0,
  /*!< Performs self_attn without softmax masking.*/

  CNNL_TRANSFORMER_SELF_ATTN_DECODER_MASK = 1,
  /*!< Performs self-attn with softmax masking in decoder,
  dimension of mask: [seq_len, seq_len]. */

  CNNL_TRANSFORMER_SELF_ATTN_ENCODER_MASK = 2,
  /*!< Performs self_attn with softmax masking in encoder,
  dimension of mask: [batch_size, seq_len]. */

  CNNL_TRANSFORMER_SELF_ATTN_MIX_MASK = 3,
  /*!< Performs self_attn with softmax masking in mix mode,
  dimension of mask: [batch_size, seq_len, seq_len]. */

  CNNL_TRANSFORMER_SELF_ATTN_SELF_GEN_ENCODER_MASK = 4,
  /*!< Performs self_attn with softmax masking in self gen encoder mode,
  dimension of mask: [batch_size]. */

  CNNL_TRANSFORMER_SELF_ATTN_SELF_PACK_MODE = 5,
  /*!< Peforms self_attn with softmax masking in pack mode,
  dimension of valid_token: [batch_size]. */
} cnnlTransformerSelfAttnMaskMode_t;

 /******************************************************************************
 * Cambricon CNNL OP: TransformerSelfAttn
 ******************************************************************************/
/*! The descriptor of self_attn function that holds transformer-network parameters, including
 *  layernorm_mode, mask_mode, quant_flag, use_residual, use_bias, quant_params, head_num,
 *  head_size_qk, head_size_v.
 *
 *  You need to call the cnnlCreateTransformerSelfAttnDescriptor function
 *  to create a descriptor, and call the cnnlSetTransformerSelfAttnDescriptor
 *  function to set the tensor information to the descriptor.
 *  Also, you need to destroy the self_attn descriptor at the end with the
 *  cnnlDestroyTransformerSelfAttnDescriptor function*/
typedef struct cnnlTransformerSelfAttnStruct *cnnlTransformerSelfAttnDescriptor_t;

// Group:Transformer Self Attn
/* transformer self-attention start */
/*!
 *  @brief A function.
 *
 *  This function executes the encoder attention in TransformerEncoderLayer and
 *  executes the cached decoder attention in TransformerDecoderLayer.
 *
 *  **Formula**
 *
 *  This operation contains three steps:
 *
 *  1. Generate QKV
 *
 *    Compute query key and value from input tensor.
 *
 *    query = mlp(input_tensor, attr_kernel_Q)
 *
 *    key = mlp(input_tensor, attr_kernel_K)
 *
 *    value = mlp(input_tensor, attr_kernel_V)
 *
 *  2. Q x K batch_dot, softmax and QK x V batch_dot
 *
 *    Compute QxK batch_dot for all heads.
 *
 *    for head_id in (0, head_num)
 *
 *      QK = batch_dot(query_in_head, key_in_head)
 *
 *      QK = softmax(QK)
 *
 *      QKV = batch_dot(QK, value_in_head)
 *
 *  3. Generate output
 *
 *    Compute output from QKV.
 *
 *    output = mlp(QKV, attout_kernel)
 *
 *  **DataType**
 *
 *    When using encoder attention:
 *
 *    For MLU270:
 *      - input: float, half
 *      - filter: int16, int8
 *      - bias: float, half
 *      - output: float, half
 *
 *    For MLU370:
 *      - input: float, half
 *      - filter: float, half, int16, int8
 *      - bias: float, half
 *      - output: float, half
 *
 *    When using cached decoder attention:
 *
 *    For MLU270:
 *      - input: float, half
 *      - filter: int16, int8
 *      - bias: float, half
 *      - output: float, half
 *
 *    For MLU370:
 *      - input: float, half
 *      - filter: float, half, int16, int8
 *      - bias: float, half
 *      - output: float, half
 *
 *  **Attention**
 *
 *    If \b curr_idx is NULL, the operation computes encoder attention;
 *    if \b curr_idx is not NULL, the operation computes cached decoder attention.
 *
 *    When using encoder attention:
 *
 *    - \b Input and \b output cannot be homologous operand.
 *
 *    - The content of \b input is not modified by self_attn layer.
 *
 *    - Data type of \b input, \b output, \b qbias, \b kbias, \b vbias, \b outbias, \b norm_scale,
 *      \b norm_bias and \b mask_vec must be the same and data type must be half or float.
 *
 *    - Data type of \b qfilter, \b kfilter, \b vfilter and \b outfilter must be the same, in MLU270 data type must be int16 or int8
 *      and in MLU370 data type must be int16, int8, half or float.
 *
 *    - Data type of \b valid_token must be int32.
 *
 *    - If filter type is int8, precision of output is not guaranteed.
 *
 *    When using cached decoder attention:
 *
 *    - \b Input and \b output cannot be homologous operand.
 *
 *    - The content of \b input is not modified by self_attn layer.
 *
 *    - Data type of \b input, \b output, \b qbias, \b kbias, \b vbias, \b outbias, \b norm_scale
 *      and \b norm_bias must be the same and data type must be half or float.
 *
 *    - Data type of \b key_cache and \b value_cache must be the same and data type must be half or float.
 *
 *    - Data type of \b qfilter, \b kfilter, \b vfilter and \b outfilter must be the same,
 *      in MLU270 data type must be int16 or int8 and in MLU370 data type must be int16, int8, half or float.
 *
 *    - Data type of \b best_beams_cache must be int8.
 *
 *    - Data type of \b curr_idx must be int32.
 *
 *    - Cached decoder attention has two modes, MLU270 mode and MLU370 mode.
 *      - In MLU270 mode, the shape of \b key_cache and \b value_cache must be
 *        [batch_size, beam_size, head_num, max_decode_length, head_size].
 *      - In MLU370 mode, the shape of \b key_cache and \b value_cache must be
 *        [batch_size, beam_size, max_decode_length, hidden_size].
 *
 *    - For cached decoder attention, tensors \b best_beams_cache, \b curr_idx,
 *      \b key_cache and \b value_cache are required and tensor \b mask_vec is not used.
 *
 *    - MLU270 mode and MLU370 mode have different scale limitations.
 *
 *    - Cached MLU370 mode requires 8 clusters and does not support post layernormal computations.
 *
 *    - If filter type is int8, precision of output is not guaranteed.
 *
 *  **Scale Limitation**
 *
 *    MLU270 or filter type is int8 or int16:
 *
 *    When using encoder attention:
 *
 *    - When use CNNL_TRANSFORMER_SELF_ATTN_PACK_MODE \b Batch_size only support 1, others has no limits.
 *
 *    - \b Head_num support 8, 12, 16.
 *
 *    - \b Head_size_qk and \b head_size_v only supports 64.
 *
 *    - \b Hidden_size = head_num * head_size_v.
 *
 *    - \b In_channel = Hidden_size.
 *
 *    - When \b head_num is 8, \b seq_len must be in the range [1, 512].
 *
 *    - When \b head_num is 12, use CNNL_TRANSFORMER_SELF_ATTN_PACK_MODE \b max_seq_len
 *      must be in the range [1, 384], others \b seq_len must be in the range [1, 384].
 *
 *    - When \b head_num is 16, \b seq_len must be in the range [1, 128].
 *
 *    - \b Layernorm_res_mode must be:
 *      - CNNL_TRANSFORMER_NO_LAYERNORM_NO_RESIDUAL.
 *      - CNNL_TRANSFORMER_NO_LAYERNORM_WITH_RESIDUAL.
 *      - CNNL_TRANSFORMER_PRE_LAYERNORM_NO_RESIDUAL.
 *      - CNNL_TRANSFORMER_POST_LAYERNORM_NO_RESIDUAL.
 *      - CNNL_TRANSFORMER_PRE_LAYERNORM_INSIDE_RESIDUAL.
 *      - CNNL_TRANSFORMER_POST_LAYERNORM_OUTSIDE_RESIDUAL.
 *      The following additional functions are supported:
 *      - \b Head_num 12, filter type is int8, 8 clusters and
 *        \b mask_mode is CNNL_TRANSFORMER_SELF_ATTN_ENCODER_MASK
 *        or CNNL_TRANSFORMER_SELF_ATTN_PACK_MODE
 *        supports CNNL_TRANSFORMER_PRE_LAYERNORM_OUTSIDE_RESIDUAL.
 *
 *    - \b Mask_mode support:
 *      - CNNL_TRANSFORMER_SELF_ATTN_NO_MASK.
 *      - CNNL_TRANSFORMER_SELF_ATTN_ENCODER_MASK.
 *      The following additional functions are supported:
 *      - \b Head_num 8 supports CNNL_TRANSFORMER_SELF_ATTN_DECODER_MASK.
 *      - \b Head_num 12 supports CNNL_TRANSFORMER_SELF_ATTN_MIX_MASK.
 *
 *    When using cached decoder attention:
 *
 *    - \b Batch_size must be in the range [1, 64].
 *
 *    - \b Beam_size must be in the range [1, 12].
 *
 *    - \b Max_decode_length must be in the range [1, 256].
 *
 *    - \b Head_num only supports 8.
 *
 *    - \b Head_size_qk and \b head_size_v only supports 64.
 *
 *    - \b Hidden_size = head_num * head_size_v.
 *
 *    - \b In_channel = Hidden_size.
 *
 *    - \b Ngroup must be in the range [1, max_decode_length] and less than 6.
 *
 *    - \b Curr_idx must be in the range [0, max_decode_length).
 *
 *    - \b Layernorm_res_mode must be:
 *      - CNNL_TRANSFORMER_NO_LAYERNORM_WITH_RESIDUAL.
 *      - CNNL_TRANSFORMER_PRE_LAYERNORM_INSIDE_RESIDUAL.
 *      - CNNL_TRANSFORMER_POST_LAYERNORM_OUTSIDE_RESIDUAL.

 *    MLU370 and filter type is fp16 or fp32:
 *
 *    When using encoder attention:
 *
 *    - \b Batch_size has no limits.
 *
 *    - \b Seq_len must be in the range [1, 512].
 *
 *    - \b Head_num must be in the range [1, 16].
 *
 *    - \b Head_size_qk and \b head_size_v must be in the range [16, 64].
 *
 *    - \b Hidden_size = head_num * head_size_v.
 *
 *    - \b In_channel = Hidden_size.
 *
 *    - \b Layernorm_res_mode support:
 *      - CNNL_TRANSFORMER_NO_LAYERNORM_NO_RESIDUAL.
 *      - CNNL_TRANSFORMER_NO_LAYERNORM_WITH_RESIDUAL.
 *      - CNNL_TRANSFORMER_PRE_LAYERNORM_NO_RESIDUAL.
 *      - CNNL_TRANSFORMER_POST_LAYERNORM_NO_RESIDUAL.
 *      - CNNL_TRANSFORMER_PRE_LAYERNORM_INSIDE_RESIDUAL.
 *      - CNNL_TRANSFORMER_PRE_LAYERNORM_OUTSIDE_RESIDUAL.
 *      - CNNL_TRANSFORMER_POST_LAYERNORM_OUTSIDE_RESIDUAL.
 *
 *    - \b Mask_mode support:
 *      - CNNL_TRANSFORMER_SELF_ATTN_NO_MASK.
 *      - CNNL_TRANSFORMER_SELF_ATTN_ENCODER_MASK.
 *      - CNNL_TRANSFORMER_SELF_ATTN_SELF_GEN_ENCODER_MASK.
 *      The following additional functions are supported:
 *      - \b Head_num 4 and filter type is fp16, supports CNNL_TRANSFORMER_SELF_ATTN_MIX_MASK.
 *
 *    - If Head_size_qk and head_size_v are in the range [65, 129), the following rules should be met:
 *
 *      - \b Batch_size has no limits.
 *
 *      - \b Seq_len must be in the range [1, 512].
 *
 *      - \b Head_num must be in the range [1, 16].
 *
 *      - \b Hidden_size = head_num * head_size_v.
 *
 *      - \b In_channel = hidden_size.
 *
 *      - \b Compute_type must be CNNL_DTYPE_HALF.
 *
 *      - \b Layernorm_res_mode supports:
 *        - CNNL_TRANSFORMER_NO_LAYERNORM_NO_RESIDUAL.
 *        - CNNL_TRANSFORMER_NO_LAYERNORM_WITH_RESIDUAL.
 *        - CNNL_TRANSFORMER_PRE_LAYERNORM_NO_RESIDUAL.
 *        - CNNL_TRANSFORMER_POST_LAYERNORM_NO_RESIDUAL.
 *        - CNNL_TRANSFORMER_PRE_LAYERNORM_INSIDE_RESIDUAL.
 *        - CNNL_TRANSFORMER_PRE_LAYERNORM_OUTSIDE_RESIDUAL.
 *        - CNNL_TRANSFORMER_POST_LAYERNORM_OUTSIDE_RESIDUAL.
 *
 *      - \b Mask_mode supports:
 *        - CNNL_TRANSFORMER_SELF_ATTN_NO_MASK.
 *        - CNNL_TRANSFORMER_SELF_ATTN_ENCODER_MASK.
 *        - CNNL_TRANSFORMER_SELF_ATTN_SELF_GEN_ENCODER_MASK.
 *
 *    - If Head_size_qk and head_size_v = 80 is deployed, the following rules should be met:
 *
 *      - \b Batch_size has no limits.
 *
 *      - \b Seq_len must be in the range [1, 128].
 *
 *      - \b Head_num must be 4.
 *
 *      - \b Hidden_size = head_num * head_size_v.
 *
 *      - \b In_channel supports 320, 560 or 880.
 *
 *      - \b Layernorm_res_mode supports:
 *        - CNNL_TRANSFORMER_PRE_LAYERNORM_NO_RESIDUAL.
 *        - CNNL_TRANSFORMER_PRE_LAYERNORM_INSIDE_RESIDUAL.
 *
 *      - \b Mask_mode supports:
 *        - CNNL_TRANSFORMER_SELF_ATTN_ENCODER_MASK.
 *        - CNNL_TRANSFORMER_SELF_ATTN_MIX_MASK.
 *
 *    - If CNNL_TRANSFORMER_SELF_ATTN_PACK_MODE is deployed, the following rules should be met:
 *
 *      - \b Batch_size must be 1.
 *
 *      - \b Max_seq_len must be in the range [1, 384].
 *
 *      - \b Head_num must be 12.
 *
 *      - \b Head_size_qk and head_size_v must be 64.
 *
 *      - \b Hidden_size = head_num * head_size_v.
 *
 *      - \b In_channel = hidden_size.
 *
 *      - \b Layernorm_res_mode supports CNNL_TRANSFORMER_PRE_LAYERNORM_OUTSIDE_RESIDUAL.
 *
 *      - \b input: float, half.
 *
 *      - \b weight: float, half, int8.
 *
 *    When using cached decoder attention:
 *
 *    - \b Batch_size has no limits.
 *
 *    - \b Beam_size must be in the range [1, 32].
 *
 *    - \b Max_decode_length must be in the range [1, 513].
 *
 *    - \b Head_size_qk and \b head_size_v must be equal, only support 32 and 64.
 *
 *    - \b Head_num must be 8 when \b head_size_qk is 64, and must be 16 when \b head_size_qk is 32.
 *
 *    - \b Hidden_size = head_num * head_size_v.
 *
 *    - \b In_channel = head_num * Head_size_qk.
 *
 *    - \b Ngroup must be in the range [1, max_decode_length] and less than 6.
 *
 *    - \b Curr_idx must be in the range [0, max_decode_length).
 *
 *    - \b Layernorm_res_mode must be:
 *      - CNNL_TRANSFORMER_NO_LAYERNORM_WITH_RESIDUAL.
 *      - CNNL_TRANSFORMER_PRE_LAYERNORM_INSIDE_RESIDUAL.
 *
 *  **Performance Optimization**
 *
 *    For encoder attention, the performance is best when batch_size dot seq_len is less than 1024,
 *    seq_len less than 128, data types of input/filter are half
 *
 *    For cached decoder attention, the performance is the best when batch >= 16, data types of
 *    input/cache/filter are half, and max_decode_length is 129.
 *
 *  **Example**
 *
 *    When using \b encoder \b attention:
 *    @verbatim
 *    hidden_size : head_num * head_size_v
 *
 *    Dimension of input: [batch_size, seq_len, in_channel]
 *
 *    Dimension of qfilter: [hidden_size, in_channel]
 *
 *    Dimension of kfilter: [hidden_size, in_channel]
 *
 *    Dimension of vfilter: [hidden_size, in_channel]
 *
 *    Dimension of outfilter: [hidden_size, hidden_size]
 *
 *    Dimension of qbias: [hidden_size]
 *
 *    Dimension of kbias: [hidden_size]
 *
 *    Dimension of vbias: [hidden_size]
 *
 *    Dimension of outbias: [hidden_size]
 *
 *    Dimension of norm_scale: [in_channel]
 *
 *    Dimension of norm_bias: [in_channel]
 *
 *    When mask_mode is CNNL_TRANSFORMER_SELF_ATTN_DECODER_MASK
 *    Dimension of mask_vec: [seq_len, seq_len]
 *    When mask_mode is CNNL_TRANSFORMER_SELF_ATTN_ENCODER_MASK
 *    Dimension of mask_vec: [batch_size, seq_len]
 *    When mask_mode is CNNL_TRANSFORMER_SELF_ATTN_MIX_MASK
 *    Dimension of mask_vec: [batch_size, seq_len, seq_len]
 *    When mask_mode is CNNL_TRANSFORMER_SELF_ATTN_SELF_GEN_ENCODER_MASK
 *    Dimension of valid_token: [batch_size]
 *
 *    Then we will get the output:
 *
 *    output: [batch_size, seq_len, hidden_size]
 *    @endverbatim
 *
 *    When using \b encoder \b attention pack mode:
 *    @verbatim
 *    hidden_size : head_num * head_size_v
 *
 *    for i in batch_size: total_seq_len = total_seq_len + valid_token[i]
 *
 *    Dimension of input: [1, total_seq_len, in_channel]
 *
 *    Dimension of qfilter: [hidden_size, in_channel]
 *
 *    Dimension of kfilter: [hidden_size, in_channel]
 *
 *    Dimension of vfilter: [hidden_size, in_channel]
 *
 *    Dimension of outfilter: [hidden_size, hidden_size]
 *
 *    Dimension of qbias: [hidden_size]
 *
 *    Dimension of kbias: [hidden_size]
 *
 *    Dimension of vbias: [hidden_size]
 *
 *    Dimension of outbias: [hidden_size]
 *
 *    Dimension of norm_scale: [in_channel]
 *
 *    Dimension of norm_bias: [in_channel]
 *
 *    When mask_mode is CNNL_TRANSFORMER_SELF_ATTN_PACK_MODE
 *    Dimension of valid_token: [batch_size]
 *
 *    Then we will get the output:
 *
 *    output: [1, total_seq_len, hidden_size]
 *    @endverbatim
 *
 *    When using \b cached \b decoder \b attention:
 *    @verbatim
 *    hidden_size : head_num * head_size_v
 *
 *    Dimension of input: [batch_size, beam_size, in_channel]
 *
 *    Dimension of qfilter: [hidden_size, in_channel]
 *
 *    Dimension of kfilter: [hidden_size, in_channel]
 *
 *    Dimension of vfilter: [hidden_size, in_channel]
 *
 *    Dimension of outfilter: [hidden_size, hidden_size]
 *
 *    Dimension of qbias: [hidden_size]
 *
 *    Dimension of kbias: [hidden_size]
 *
 *    Dimension of vbias: [hidden_size]
 *
 *    Dimension of outbias: [hidden_size]
 *
 *    Dimension of norm_scale: [hidden_size]
 *
 *    Dimension of norm_bias: [hidden_size]
 *
 *    Dimension of curr_idx: [1]
 *
 *    Dimension of key_cache: In MLU270 mode [batch_size, beam_size, head_num, max_decode_length, head_size]
 *                            In MLU370 mode [batch_size, beam_size, max_decode_length, hidden_size]
 *
 *    Dimension of value_cache: In MLU270 mode [batch_size, beam_size, head_num, max_decode_length, head_size]
 *                              In MLU370 mode [batch_size, beam_size, max_decode_length, hidden_size]
 *
 *    Dimension of best_beams_cache: [batch_size, ngroup, beam_size]
 *
 *    Then we will get the output:
 *
 *    output: [batch_size, beam_size, hidden_size]
 *    @endverbatim
 *
 *  **Reference**
 *
 *    papers.nips.cc/paper/7181-attention-is-all-you-need.pdf
 *
 *  **API Dependency**
 *
 *    You need to call the cnnlCreateTransformerSelfAttnDescriptor() to
 *    create descriptor and use cnnlSetTransformerSelfAttnDescriptor()
 *    to set its parameters before calling this function.
 *
 *    You need to call the cnnlDestroyTransformerSelfAttnDescriptor()
 *    function after calling this function.
 *
 *  @param[in]  handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           transformer_self_attn operation.
 *  @param[in] self_attn_desc
 *    Input. A struct with parameters of transformer self_attn layer.
 *  @param[in]  desc_input
 *    Input. Descriptor of input, containing dimension of [batch_size, seq_len, in_channel].
 *  @param[in]  input
 *    Input. Device pointer points to input space.
 *  @param[in]  desc_qfilter
 *    Input. Descriptor of query filter, containing dimension of [hidden_size, in_channel].
 *  @param[in]  qfilter
 *    Input. Device pointer points to query filter space, the combined filter is
 *           arranged in the order of [query_filters].
 *  @param[in]  desc_kfilter
 *    Input. Descriptor of key filter, containing dimension of [hidden_size, in_channel].
 *  @param[in]  kfilter
 *    Input. Device pointer points to key filter space, the combined filter is
 *           arranged in the order of [key_filters].
 *  @param[in]  desc_vfilter
 *    Input. Descriptor of value filter, containing dimension of [hidden_size, in_channel].
 *  @param[in]  vfilter
 *    Input. Device pointer points to value filter space, the combined filter is
 *           arranged in the order of [value_filters].
 *  @param[in]  desc_qbias
 *    Input. Descriptor of query bias, containing dimension of [hidden_size].
 *           This descriptor is optional.
 *  @param[in]  qbias
 *    Input. Device pointer points to query bias space, the combined bias is
 *           arranged in the order of [query_bias].
 *           This device pointer is optional.
 *  @param[in]  desc_kbias
 *    Input. Descriptor of key bias, containing dimension of [hidden_size].
 *           This descriptor is optional.
 *  @param[in]  kbias
 *    Input. Device pointer points to key bias space, the combined bias is
 *           arranged in the order of [key_bias].
 *           This device pointer is optional.
 *  @param[in]  desc_vbias
 *    Input. Descriptor of value bias, containing dimension of [hidden_size].
 *           This descriptor is optional.
 *  @param[in]  vbias
 *    Input. Device pointer points to value bias space, the combined bias is
 *           arranged in the order of [value_bias].
 *           This device pointer is optional.
 *  @param[in]  desc_outfilter
 *    Input. Descriptor of filter of out fullyconnected layer,
 *           containing dimension of [hidden_size, hidden_size].
 *  @param[in]  outfilter
 *    Input. Device pointer points to out fc filter space.
 *  @param[in]  desc_outbias
 *    Input. Descriptor of bias of out fullyconnected layer,
 *           containing dimension of [hidden_size].
 *           This descriptor is optional.
 *  @param[in]  outbias
 *    Input. Device pointer points to out fc bias space.
 *           This device pointer is optional.
 *  @param[in]  desc_mask
 *    Input. Descriptor of mask vector, containing data type, dimensions and layout.
 *           This descriptor is optional.
 *  @param[in]  mask_vec
 *    Input. Device pointer points to encoder mask space.
 *           This device pointer is optional.
 *  @param[in]  desc_valid_token
 *    Input. Descriptor of valid_token, its data type must be INT32 and shape must be [batch_size].
 *           This descriptor is optional.
 *  @param[in]  valid_token
 *    Input. Device pointer points to valid token space. Indicates every batch_size valid token num
 *           for self gen encoder mask or pack mode. This device pointer is optional.
 *  @param[in]  desc_norm_scale
 *    Input. Descriptor of norm_scale vector, containing dimension of [in_channel].
 *           This descriptor is optional.
 *  @param[in]  norm_scale
 *    Input. Device pointer points to nrom_scale space, dimensions depends on
 *           output dimensions. This device pointer is optional.
 *  @param[in]  desc_norm_bias
 *    Input. Descriptor of norm_bias vector, containing dimension of [in_channel].
 *           This descriptor is optional.
 *  @param[in]  norm_bias
 *    Input. Device pointer points to nrom_bias space, dimensions depends on
 *           output dimensions. This device pointer is optional.
 *  @param[in] curr_idx_desc
 *    Input. Descriptor of loop index tensor, containing data type, dimensions and
 *           layout. Its data type must be INT32 and shape must be [1].
 *           This descriptor is optional.
 *  @param[in,out] curr_idx
 *    Input and Output. Device pointer points to loop index tensor space.
 *           Indicates the number of frames that decoder has already processed.
 *           This device pointer is optional.
 *  @param[in] key_cache_desc
 *    Input. Descriptor of key_cache tensor, containing data type, dimensions and
 *           layout. Shape must be [batch_size, beam_size, head_num, max_decode_length, head_size]
 *           or [batch_size, beam_size, max_decode_length, hidden_size].
 *           This descriptor is optional.
 *  @param[in,out] key_cache
 *    Input and Output. Device pointer points to key_cache tensor space.
 *           The value stored in cache will be updated during the operation.
 *           This device pointer is optional.
 *  @param[in] value_cache_desc
 *    Input. Descriptor of value_cache tensor, containing data type, dimensions and layout.
 *           Decoder: shape must be [batch_size, beam_size, head_num, max_decode_length, head_size]
 *           or [batch_size, beam_size, max_decode_length, hidden_size].
 *           Encoder: shape must be [batch_size, seq_len, hidden_size].
 *           This descriptor is optional.
 *  @param[in,out] value_cache
 *    Input and Output. Device pointer points to value_cache tensor space.
 *           The value stored in cache will be updated during the operation.
 *           This device pointer is optional.
 *  @param[in] best_beams_cache_desc
 *    Input. Descriptor of best_beams_cache tensor, containing data type, dimensions and
 *           layout. Shape must be [batch_size, ngroup, beam_size].
 *           This descriptor is optional.
 *  @param[in,out] best_beams_cache
 *    Input and Output. Device pointer points to best_beams_cache tensor space. It is a state
 *           inferred from beam search result, to restore historical K/V cache correctly.
 *           If this is the first frame of decoder, this cache must be initialized with zero
 *           before calling this operation. The value stored in cache will be updated during
 *           the operation. This device pointer is optional.
 *  @param[in]  workspace
 *    Input. The pointer to data address of workspace.
 *  @param[in]  workspace_size
 *    Input. The value of workspace_size.
 *  @param[out]  desc_output
 *    Input. Descriptor of output, containing data type, dimensions and layout,
 *    the three dimensions is valid. Shape must be [batch_size, seq_len, hidden_size].
 *  @param[out]  output
 *    Input. Device pointer points to output space.
 *  @retval CNNL_STATUS_SUCCESS = 0
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM = 3
 *    One or more of the following conditions are encountered:
 *    - handle is NULL.
 *    - pointer is NULL.
 *    - parameters are invalid.
 *  @retval CNNL_STATUS_ARCH_MISMATCH
 *    One or more of the following conditions are encountered:
 *    - This function is run on the hardware platform that is not supported.
 */
cnnlStatus_t CNNL_WIN_API
cnnlTransformerSelfAttn(cnnlHandle_t handle,
                        const cnnlTransformerSelfAttnDescriptor_t self_attn_desc,
                        const cnnlTensorDescriptor_t desc_input,
                        const void *input,
                        const cnnlTensorDescriptor_t desc_qfilter,
                        const void *qfilter,
                        const cnnlTensorDescriptor_t desc_kfilter,
                        const void *kfilter,
                        const cnnlTensorDescriptor_t desc_vfilter,
                        const void *vfilter,
                        const cnnlTensorDescriptor_t desc_qbias,
                        const void *qbias,
                        const cnnlTensorDescriptor_t desc_kbias,
                        const void *kbias,
                        const cnnlTensorDescriptor_t desc_vbias,
                        const void *vbias,
                        const cnnlTensorDescriptor_t desc_outFilter,
                        const void *outfilter,
                        const cnnlTensorDescriptor_t desc_outbias,
                        const void *outbias,
                        const cnnlTensorDescriptor_t desc_mask,
                        const void *mask_vec,
                        const cnnlTensorDescriptor_t desc_valid_token,
                        const void *valid_token,
                        const cnnlTensorDescriptor_t desc_norm_scale,
                        const void *norm_scale,
                        const cnnlTensorDescriptor_t desc_norm_bias,
                        const void *norm_bias,
                        const cnnlTensorDescriptor_t desc_curr_idx,
                        void *curr_idx,
                        const cnnlTensorDescriptor_t desc_key_cache,
                        void *key_cache,
                        const cnnlTensorDescriptor_t desc_value_cache,
                        void *value_cache,
                        const cnnlTensorDescriptor_t desc_best_beams_cache,
                        void *best_beams_cache,
                        void *workspace,
                        size_t workspace_size,
                        const cnnlTensorDescriptor_t desc_output,
                        const void *output);

// Group:Transformer Self Attn
/*!
 *  @brief A function.
 *
 *  This function is used to create a descriptor of TransformerSelfAttn
 *  and allocate memory for it.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *  After calling this function, you can call the cnnlSetTransformerSelfAttnDescriptor
 *  function to initialize and set the information to the SelfAttn descriptor.
 *  You need to call the cnnlDestroyTransformerSelfAttnDescriptor function
 *  to destroy the descriptor.
 *
 *  @param[in]  self_attn_desc
 *    Input. Descriptor of TransformerSelfAttn operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_ALLOC_FAILED
 *    The function allocate memory space failed.
 */
cnnlStatus_t CNNL_WIN_API
cnnlCreateTransformerSelfAttnDescriptor(
  cnnlTransformerSelfAttnDescriptor_t *self_attn_desc);

// Group:Transformer Self Attn
/*!
 *  @brief A function.
 *
 *  This function is used to destroy a descriptor of TransformerSelfAttn
 *  and free memory for it.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *  You need to call this function after calling the cnnlTransformerSelfAttn function.
 *
 *  @param[in]  self_attn_desc
 *    Input. Descriptor of TransformerSelfAttn operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of self_attn_desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlDestroyTransformerSelfAttnDescriptor(
  cnnlTransformerSelfAttnDescriptor_t self_attn_desc);

// Group:Transformer Self Attn
/*!
 *  @brief A function.
 *
 *  This function is used to assign TransformerSelfAttn descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *  When handling transformer descriptor, users need to use
 *  cnnlCreateTransformerSelfAttnDescriptor() to create descriptor
 *  and use cnnlSetTransformerSelfAttnDescriptor() to set its parameters.
 *
 *  @param[out] self_attn_desc
 *    Output. Descriptor of TransformerSelfAttn operation.
 *  @param[in]  head_num
 *    Input. The number of heads in self attention.
 *  @param[in]  head_size_qk
 *    Input. The size of one head in self attention for query and key.
 *  @param[in]  head_size_v
 *    Input. The size of one head in self attention for value.
 *  @param[in]  hidden_size
 *    Input. The size of feature for one token.
 *  @param[in]  query_factor
 *    Input. Parameter indicates scaling coefficient multiplication to query.
 *  @param[in]  query_out_pos
 *    Input. The query quantization position.
 *  @param[in]  query_out_scale
 *    Input. The query quantization scaling coefficient.
 *  @param[in]  key_out_pos
 *    Input. The key quantization position.
 *  @param[in]  key_out_scale
 *    Input. The key quantization scaling coefficient.
 *  @param[in]  value_out_pos
 *    Input. The value quantization position.
 *  @param[in]  value_out_scale
 *    Input. The value quantization scaling coefficient.
 *  @param[in]  qkv_out_pos
 *    Input. The zout quantization position.
 *  @param[in]  qkv_out_scale
 *    Input. The zout quantization scaling coefficient.
 *  @param[in]  layernorm_res_mode
 *    Input. The indicator of layernorm res mode, including:
 *           - CNNL_TRANSFORMER_NO_LAYERNORM_NO_RESIDUAL: no layernorm calculation and no res calculation in this operation.
 *           - CNNL_TRANSFORMER_NO_LAYERNORM_WITH_RESIDUAL: no layernorm calculation and do residual calculation in this operation.
 *           - CNNL_TRANSFORMER_PRE_LAYERNORM_NO_RESIDUAL: do layernorm for input before QKV calculation and no residual calculation in this operation.
 *           - CNNL_TRANSFORMER_POST_LAYERNORM_NO_RESIDUAL: do layernorm for output after fc calculation and no residual calculation in this operation.
 *           - CNNL_TRANSFORMER_PRE_LAYERNORM_INSIDE_RESIDUAL: do layernorm for input before QKV calculation and do inside residual calculation in this operation.
 *           - CNNL_TRANSFORMER_PRE_LAYERNORM_OUTSIDE_RESIDUAL: do layernorm for input before QKV calculation and do outside residual calculation in this operation.
 *           - CNNL_TRANSFORMER_POST_LAYERNORM_OUTSIDE_RESIDUAL: do layernorm for output after fc calculation and do outside residual calculation in this operation.
 *  @param[in]  mask_mode
 *    Input. The incicator of mask adding mode, including:
 *           - CNNL_TRANSFORMER_SELF_ATTN_NO_MASK: no mask adding after QK matmul.
 *           - CNNL_TRANSFORMER_SELF_ATTN_DECODER_MASK: add mask with shape [batch_size, seq_len] after QK matmul.
 *           - CNNL_TRANSFORMER_SELF_ATTN_ENCODER_MASK: add mask with shape [seq_len, seq_len] after QK matmul.
 *           - CNNL_TRANSFORMER_SELF_ATTN_MIX_MASK: add mask with shape [batch_size, seq_len, seq_len] after QK matmul.
 *           - CNNL_TRANSFORMER_SELF_ATTN_SELF_GEN_ENCODER_MASK: self gen mask with shape [batch_size, seq_len] after QK matmul.
 *           - CNNL_TRANSFORMER_SELF_ATTN_PACK_MODE: no mask after QK matmul.
 *  @param[in]  enable_input_online_quantify
 *    Input. A boolean value indicates whether to enable online quantization of input.
 *           Quantization information must be provided when it is false.
 *  @param[in]  enable_qkv_online_quantify
 *    Input. A boolean value indicates whether to enable online quantization of query, key adn value.
 *           Quantization information must be provided when it is false.
 *  @param[in]  enable_qkv_out_online_quantify
 *    Input. A boolean value indicates whether to enable online quantization of qkv.
 *           Quantization information must be provided when it is false.
 *  @param[in]  use_quantify_scale
 *    Input. A boolean value indicates whether to use scale in quantifization.
 *  @param[in]  use_bias
 *    Input. A boolean value indicates whether to use bias when computing query, key, value and attention output.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions is met:.
 *    - The value of self_attn_desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetTransformerSelfAttnDescriptor(
            cnnlTransformerSelfAttnDescriptor_t self_attn_desc,
            const int head_num,
            const int head_size_qk,
            const int head_size_v,
            const int hidden_size,
            const float query_factor,
            const int16_t query_out_pos,
            const float query_out_scale,
            const int16_t key_out_pos,
            const float key_out_scale,
            const int16_t value_out_pos,
            const float value_out_scale,
            const int16_t qkv_out_pos,
            const float qkv_out_scale,
            const cnnlTransformerLayernormResidualStructure_t layernorm_res_mode,
            const cnnlTransformerSelfAttnMaskMode_t mask_mode,
            const bool enable_input_online_quantify,
            const bool enable_qkv_online_quantify,
            const bool enable_qkv_out_online_quantify,
            const bool use_quantify_scale,
            const bool use_bias);

// Group:Transformer Self Attn
/*!
 *  @brief A function.
 *
 *  This function is used to assign TransformerSelfAttn descriptor with
 *  enable_encoder_key_output and enable_encoder_value_output.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *  When handling transformer descriptor, users need to use
 *  cnnlCreateTransformerSelfAttnDescriptor() to create descriptor
 *  and use cnnlSetTransformerSelfAttnEncoderKeyValueOutputMode() to set its parameters.
 *
 *  @param[out] self_attn_desc
 *    Output. Descriptor of TransformerSelfAttn operation.
 *  @param[in]  enable_encoder_key_output
 *    Input. A boolean value indicates whether to enable encoder key output. This parameter is not supported yet.
 *  @param[in]  enable_encoder_value_output
 *    Input. A boolean value indicates whether to enable encoder value output.
 *    When this parameter is true, head_num can be only set to 4.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_INVALIDPARAM
 *    - The value of self_attn_desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetTransformerSelfAttnEncoderKeyValueOutputMode(
            cnnlTransformerSelfAttnDescriptor_t self_attn_desc,
            const bool enable_encoder_key_output,
            const bool enable_encoder_value_output);

// Group:Transformer Self Attn
/*!
 *  @brief A function.
 *
 *  This function is used to assign TransformerSelfAttn descriptor with
 *  softmax_out_pos and softmax_out_scale.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *  When handling transformer descriptor, users need to use
 *  cnnlCreateTransformerSelfAttnDescriptor() to create descriptor
 *  and use cnnlSetTransformerSelfAttnSoftmaxOutPosAndScale() to set its parameters.
 *
 *  @param[out] self_attn_desc
 *    Output. Descriptor of TransformerSelfAttn operation.
 *  @param[in] softmax_out_pos
 *    Input. The position of softmax output quantization in the per tensor mode.
 *  @param[in]  softmax_out_scale
 *    Input. The scaling coefficient of softmax output quantization in the per tensor mode.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_INVALIDPARAM
 *    - The value of self_attn_desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetTransformerSelfAttnSoftmaxOutPosAndScale(
            cnnlTransformerSelfAttnDescriptor_t self_attn_desc,
            const int softmax_out_pos,
            const float softmax_out_scale);

// Group:Transformer Self Attn
/*!
 *  @brief A function.
 *
 *  This function is used to assign TransformerSelfAttn descriptor with max_seq_len.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *  When handling transformer descriptor, users need to use
 *  cnnlCreateTransformerSelfAttnDescriptor() to create descriptor
 *  and use cnnlSetTransformerSelfAttnPackModeMaxToken() to set its parameters.
 *
 *  @param[out] self_attn_desc
 *    Output. Descriptor of TransformerSelfAttn operation.
 *  @param[in] max_seq_len
 *    Input. The current dataset longest seq_len in pack mode.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_INVALIDPARAM
 *    - The value of self_attn_desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetTransformerSelfAttnPackModeMaxToken(
            cnnlTransformerSelfAttnDescriptor_t self_attn_desc,
            const int max_seq_len);

// Group:Transformer Self Attn
/*!
 *  @brief A function.
 *  This function is used to get extra space size that needed in
 *  TransformerSelfAttn operation.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *  Use cnnlCreateTransformerSelfAttnDescriptor() to create descriptor
 *  and use cnnlSetTransformerSelfAttnDescriptor() to set its parameters.
 *
 *  @param[in]  self_attn_desc
 *    Input.  Descriptor of TransformerSelfAttn operation.
 *  @param[in]  input_desc
 *    Input. Descriptor of input, containing dimension and the layout of input.
 *  @param[out] size
 *    Output. Size of workspace.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of self_attn_desc or size is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlGetTransformerSelfAttnWorkspaceSize(
  const cnnlTransformerSelfAttnDescriptor_t self_attn_desc,
  const cnnlTensorDescriptor_t input_desc,
  size_t *size);

// Group:Transformer Self Attn
/*!
 *  @brief A function.
 *
 *  This function is used to assign TransformerSelfAttn descriptor with scaled_after_q_dot_k paramater.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *  When handling transformer descriptor, users need to use
 *  cnnlCreateTransformerSelfAttnDescriptor() to create descriptor
 *  and use cnnlSetTransformerSelfAttnFactorPosition() to set its parameters.
 *
 *  @param[out] self_attn_desc
 *    Output. Descriptor of TransformerSelfAttn operation.
 *  @param[in] scaled_after_q_dot_k
 *    Input.  A boolean value indcates whether to scale the result of q_dot_k.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_INVALIDPARAM
 *    - The value of self_attn_desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetTransformerSelfAttnFactorPosition(
            cnnlTransformerSelfAttnDescriptor_t self_attn_desc,
            bool scaled_after_q_dot_k);

// Group:Transformer Self Attn
/*!
 *  @brief A function.
 *
 *  This function is used to assign TransformerSelfAttn with parameters in the quantization scenario.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *  When handling transformer descriptor, users need to use
 *  cnnlCreateTransformerSelfAttnDescriptor() to create descriptor
 *  and use cnnlSetTransformerSelfAttnDescriptor() to set its parameters.
 *
 *  @param[out] self_attn_desc
 *    Output. Descriptor of TransformerSelfAttn operation.
 *  @param[in]  head_num
 *    Input. The number of heads in self attention.
 *  @param[in]  head_size_qk
 *    Input. The size of one head in self attention for query and key.
 *  @param[in]  head_size_v
 *    Input. The size of one head in self attention for value.
 *  @param[in]  hidden_size
 *    Input. The size of feature for one token.
 *  @param[in]  query_factor
 *    Input. The scaling coefficient multiplied to query or q_dot_k.
 *  @param[in]  layernorm_eps
 *    Input. The eps value of layernorm.
 *  @param[in]  use_bias
 *    Input. A boolean value indicates whether to use bias when computing query, key, value and attention output.
 *  @param[in]  use_hp_active
 *    Input. A boolean value indicates whether to use high-precision for activation. There are the following rules:
 *           - COMPUTE_DTYPE = FLOAT, use_hp_active = true, use spss activation.
 *           - COMPUTE_DTYPE = FLOAT, use_hp_active = false, use float activation table.
 *           - COMPUTE_DTYPE = HALF, use_hp_active = true, use spss activation.
 *           - COMPUTE_DTYPE = HALF, use_hp_active = false, use half activation table.
 *  @param[in]  attention_output_quant
 *    Input. A boolean value indicates whether to quantize the output of attention before adding residual.
 *           The quantification is performed by converting the data type of the output of attention from
 *           float to int8 to float or from half to int8 to half.
 *  @param[in]  residual_input_quant
 *    Input. A boolean value indicates whether to quantize the input of residual before adding residual.
 *           The quantification is performed by converting the data type of the input of residual from
 *           float to int8 to float or from half to int8 to half.
 *  @param[in]  use_query_aftergemm_quant
 *    Input. A boolean value indicates whether to use query_aftergemm_pos and query_aftergemm_scale when dequantizing query.
 *  @param[in]  use_key_aftergemm_quant
 *    Input. A boolean value indicates whether to use key_aftergemm_pos and key_aftergemm_scale when dequantizing key.
 *  @param[in]  use_value_aftergemm_quant
 *    Input. A boolean value indicates whether to use value_aftergemm_pos and value_aftergemm_scale when dequantizing value.
 *  @param[in]  use_qk_aftergemm_quant
 *    Input. A boolean value indicates whether to use qk_aftergemm_pos and qk_aftergemm_scale when dequantizing q_dot_k.
 *  @param[in]  use_qkv_aftergemm_quant
 *    Input. A boolean value indicates whether to use qkv_aftergemm_pos and qkv_aftergemm_scale when dequantizing qk_dot_v.
 *  @param[in]  use_o_aftergemm_quant
 *    Input. A boolean value indicates whether to use o_aftergemm_pos and o_aftergemm_scale when dequantizing output.
 *  @param[in]  quant_per_tensor
 *    Input. A boolean value indicates whether to use per tensor mode for quantization.
 *           - Per tensor mode(default) : Converts a float tensor to quantized tensor with the given position and scale.
 *           - Per channel mode : Converts a float tensor to per channel quantized tensor with given positions and scales.
 *  @param[in]  use_quantify_scale
 *    Input. A boolean value indicates whether to use scaling coefficient in quantization.
 *  @param[in]  use_offset_scale
 *    Input. A boolean value indicates whether to use offset in quantization.
 *  @param[in]  online_quantify
 *    Input. A boolean value indicates whether to enable online quantization.
 *           Quantization information must be provided when it is false.
 *  @param[in]  compute_dtype
 *    Input. The data type used in the computing, which includes half and float.
 *  @param[in]  layernorm_res_mode
 *    Input. The implementation mode of layernorm and residual in the TransformerSelfAttn.
 *           See ::cnnlTransformerLayernormResidualStructure_t for details.
 *  @param[in]  mask_mode
 *    Input. The mask mode used in the TransformerSelfAttn. See ::cnnlTransformerSelfAttnMaskMode_t for details.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions is met:
 *    - The value of self_attn_desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetTransformerSelfAttnQATParameters(
        cnnlTransformerSelfAttnDescriptor_t self_attn_desc,
        const int head_num,
        const int head_size_qk,
        const int head_size_v,
        const int hidden_size,
        const float query_factor,
        const float layernorm_eps,
        const bool use_bias,
        const bool use_hp_active,
        const bool attention_output_quant,
        const bool residual_input_quant,
        const bool use_query_aftergemm_quant,
        const bool use_key_aftergemm_quant,
        const bool use_value_aftergemm_quant,
        const bool use_qk_aftergemm_quant,
        const bool use_qkv_aftergemm_quant,
        const bool use_o_aftergemm_quant,
        const bool quant_per_tensor,
        const bool use_quantify_scale,
        const bool use_quantify_offset,
        const bool online_quantify,
        const cnnlDataType_t compute_dtype,
        const cnnlTransformerLayernormResidualStructure_t layernorm_res_mode,
        const cnnlTransformerSelfAttnMaskMode_t mask_mode);

// Group:Transformer Self Attn
/*!
 *  @brief A function.
 *
 *  This function is used to assign TransformerSelfAttn descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *  When handling transformer descriptor, users need to use
 *  cnnlCreateTransformerSelfAttnDescriptor() to create descriptor
 *  and use cnnlSetTransformerSelfAttnDescriptor() to set its parameters.
 *
 *  @param[out] self_attn_desc
 *    Output. Descriptor of TransformerSelfAttn operation.
 *  @param[in]  qfilter_pos
 *    Input. The position of qfilter quantization in the per channel mode.
 *  @param[in]  qfilter_scale
 *    Input. The scaling coefficient of qfilter quantization in the per channel mode.
 *  @param[in]  qfilter_offset
 *    Input. The offset of qfilter quantization in the per channel mode.
 *  @param[in]  kfilter_pos
 *    Input. The position of kfilter quantization in the per channel mode.
 *  @param[in]  kfilter_scale
 *    Input. The scaling coefficient of kfilter quantization in the per channel mode.
 *  @param[in]  kfilter_offset
 *    Input. The offset of kfilter quantization in the per channel mode.
 *  @param[in]  vfilter_pos
 *    Input. The position of vfilter quantization in the per channel mode.
 *  @param[in]  vfilter_scale
 *    Input. The scaling coefficient of vfilter quantization in the per channel mode.
 *  @param[in]  vfilter_offset
 *    Input. The offset of vfilter quantization in the per channel mode.
 *  @param[in]  ofilter_pos
 *    Input. The position of ofilter quantization in the per channel mode.
 *  @param[in]  ofilter_scale
 *    Input. The scaling coefficient of ofilter quantization in the per channel mode.
 *  @param[in]  ofilter_offset
 *    Input. The offset of ofilter quantization in the per channel mode.
 *  @param[in]  query_out_pos
 *    Input. The position of query quantization in the per tensor mode.
 *  @param[in]  query_out_scale
 *    Input. The scaling coefficient of query quantization in the per tensor mode.
 *  @param[in]  query_out_offset
 *    Input. The offset of query quantization in the per tensor mode.
 *  @param[in]  key_out_pos
 *    Input. The position of key quantization in the per tensor mode.
 *  @param[in]  key_out_scale
 *    Input. The scaling coefficient of key quantization in the per tensor mode.
 *  @param[in]  key_out_offset
 *    Input. The offset of key quantization in the per tensor mode.
 *  @param[in]  value_out_pos
 *    Input. The position of value quantization in the per tensor mode.
 *  @param[in]  value_out_scale
 *    Input. The scaling coefficient of value quantization in the per tensor mode.
 *  @param[in]  value_out_offset
 *    Input. The offset of value quantization in the per tensor mode.
 *  @param[in] softmax_out_pos
 *    Input. The position of softmax output quantization in the per tensor mode.
 *  @param[in]  softmax_out_scale
 *    Input. The scaling coefficient of softmax output quantization in the per tensor mode.
 *  @param[in]  softmax_out_offset
 *    Input. The offset of softmax output quantization in the per tensor mode.
 *  @param[in]  qkv_out_pos
 *    Input. The position of qk_dot_v quantization in the per tensor mode.
 *  @param[in]  qkv_out_scale
 *    Input. The scaling coefficient of qk_dot_v quantization in the per tensor mode.
 *  @param[in]  qkv_out_offset
 *    Input. The offset of qk_dot_v quantization in the per tensor mode.
 *  @param[in]  o_out_pos
 *    Input. The position of output quantization in the per tensor mode.
 *  @param[in]  o_out_scale
 *    Input. The scaling coefficient of output quantization in the per tensor mode.
 *  @param[in]  o_out_offset
 *    Input. The offset of output quantization in the per tensor mode.
 *  @param[in]  query_aftergemm_pos
 *    Input. The position of query dequantization that will be performed with the after_gemm
 *           dequantization parameter after matrix multiplication.
 *  @param[in]  query_aftergemm_scale
 *    Input. The scaling coefficient of query dequantization that will be performed with the after_gemm
 *           dequantization parameter after matrix multiplication.
 *  @param[in]  query_aftergemm_offset
 *    Input. The offset of query dequantization that will be performed with the after_gemm
 *           dequantization parameter after matrix multiplication.
 *  @param[in]  key_aftergemm_pos
 *    Input. The position of key dequantization that will be performed with the after_gemm
 *           dequantization parameter after matrix multiplication.
 *  @param[in]  key_aftergemm_scale
 *    Input. The scaling coefficient of key dequantization that will be performed with the after_gemm
 *           dequantization parameter after matrix multiplication.
 *  @param[in]  key_aftergemm_offset
 *    Input. The offset of key dequantization that will be performed with the after_gemm
 *           dequantization parameter after matrix multiplication.
 *  @param[in]  value_aftergemm_pos
 *    Input. The position of value dequantization that will be performed with the after_gemm
 *           dequantization parameter after matrix multiplication.
 *  @param[in]  value_aftergemm_scale
 *    Input. The scaling coefficient of value dequantization that will be performed with the after_gemm
 *           dequantization parameter after matrix multiplication.
 *  @param[in]  value_aftergemm_offset
 *    Input. The offset of value dequantization that will be performed with the after_gemm
 *           dequantization parameter after matrix multiplication.
 *  @param[in]  qk_aftergemm_pos
 *    Input. The position of q_dot_k dequantization that will be performed with the after_gemm
 *           dequantization parameter after matrix multiplication.
 *  @param[in]  qk_aftergemm_scale
 *    Input. The scaling coefficient of q_dot_k dequantization that will be performed with the after_gemm
 *           dequantization parameter after matrix multiplication.
 *  @param[in]  qk_aftergemm_offset
 *    Input. The offset of q_dot_k dequantization that will be performed with the after_gemm
 *           dequantization parameter after matrix multiplication.
 *  @param[in]  qkv_aftergemm_pos
 *    Input. The position of qk_dot_v dequantization that will be performed with the after_gemm
 *           dequantization parameter after matrix multiplication.
 *  @param[in]  qkv_aftergemm_scale
 *    Input. The scaling coefficient of qk_dot_v dequantization that will be performed with the after_gemm
 *           dequantization parameter after matrix multiplication.
 *  @param[in]  qkv_aftergemm_offset
 *    Input. The offset of qk_dot_v dequantization that will be performed with the after_gemm
 *           dequantization parameter after matrix multiplication.
 *  @param[in]  o_aftergemm_pos
 *    Input. The position of output dequantization that will be performed with the after_gemm
 *           dequantization parameter after matrix multiplication.
 *  @param[in]  o_aftergemm_scale
 *    Input. The scaling coefficient of output dequantization that will be performed with the after_gemm
 *           dequantization parameter after matrix multiplication.
 *  @param[in]  o_aftergemm_offset
 *    Input. The offset of output dequantization that will be performed with the after_gemm
 *           dequantization parameter after matrix multiplication.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions is met:.
 *    - The value of self_attn_desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetTransformerSelfAttnQATQuantifyParams(
  const cnnlTransformerSelfAttnDescriptor_t self_attn_desc,
  const void *qfilter_pos,
  const void *qfilter_scale,
  const void *qfilter_offset,
  const void *kfilter_pos,
  const void *kfilter_scale,
  const void *kfilter_offset,
  const void *vfilter_pos,
  const void *vfilter_scale,
  const void *vfilter_offset,
  const void *ofilter_pos,
  const void *ofilter_scale,
  const void *ofilter_offset,
  const int16_t query_out_pos,
  const float query_out_scale,
  const int16_t query_out_offset,
  const int16_t key_out_pos,
  const float key_out_scale,
  const int16_t key_out_offset,
  const int16_t value_out_pos,
  const float value_out_scale,
  const int16_t value_out_offset,
  const int16_t softmax_out_pos,
  const float softmax_out_scale,
  const int16_t softmax_out_offset,
  const int16_t qkv_out_pos,
  const float qkv_out_scale,
  const int16_t qkv_out_offset,
  const int16_t o_out_pos,
  const float o_out_scale,
  const int16_t o_out_offset,
  const int16_t query_aftergemm_pos,
  const float query_aftergemm_scale,
  const int16_t query_aftergemm_offset,
  const int16_t key_aftergemm_pos,
  const float key_aftergemm_scale,
  const int16_t key_aftergemm_offset,
  const int16_t value_aftergemm_pos,
  const float value_aftergemm_scale,
  const int16_t value_aftergemm_offset,
  const int16_t qk_aftergemm_pos,
  const float qk_aftergemm_scale,
  const int16_t qk_aftergemm_offset,
  const int16_t qkv_aftergemm_pos,
  const float qkv_aftergemm_scale,
  const int16_t qkv_aftergemm_offset,
  const int16_t o_aftergemm_pos,
  const float o_aftergemm_scale,
  const int16_t o_aftergemm_offset);

// Group:Transformer Self Attn
/*!
 *  @brief A function.
 *
 *  This function is used to set the data type used in the computation of TransformerSelfAttn.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *  When handling transformer descriptor, users need to use
 *  cnnlCreateTransformerSelfAttnDescriptor() to create descriptor
 *  and use cnnlSetTransformerSelfAttnDescriptor() to set its parameters.
 *
 *  @param[out] self_attn_desc
 *    Output. Descriptor of TransformerSelfAttn operation.
 *  @param[in]  use_hp_active
 *    Input. A boolean value indicates whether to use high-precision for activation. There are the following rules:
 *           - COMPUTE_DTYPE = FLOAT, use_hp_active = true, use spss activation.
 *           - COMPUTE_DTYPE = FLOAT, use_hp_active = false, use float activation table.
 *           - COMPUTE_DTYPE = HALF, use_hp_active = true, use spss activation.
 *           - COMPUTE_DTYPE = HALF, use_hp_active = false, use half activation table.
 *  @param[in]  compute_dtype
 *    Input. The data type used in the computing, which includes half and float.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions is met:
 *    - The value of self_attn_desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetTransformerSelfAttnComputeType(
        cnnlTransformerSelfAttnDescriptor_t self_attn_desc,
        const bool use_hp_active,
        const cnnlDataType_t compute_dtype);

/******************************************************************************
 * Cambricon CNNL OP: TransformerEncoderOutput
 ******************************************************************************/
/*! The descriptor of Transformer EncoderOutput */
typedef struct cnnlTransformerEncOutputStruct *cnnlTransformerEncoderOutputDescriptor_t;

// Group:Transformer Encoder Output
/*!
 *  @brief A function.
 *
 *  This function is used to create a descriptor of transformer encoder output,
 *  which contains layernorm mode, output mode, input online quantify indicator, use bias or not,
 *  decoder layer number, and encoder/decoder information(including head_num/size).
 *
 *  @param[in]  desc
 *    Input. Description of transformer encoder_output operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_ALLOC_FAILED
 *    The function fails to malloc memory for desc.
 */
cnnlStatus_t CNNL_WIN_API
cnnlCreateTransformerEncoderOutputDescriptor(cnnlTransformerEncoderOutputDescriptor_t *desc);

// Group:Transformer Encoder Output
/*!
 *  @brief A function.
 *
 *  This function is used to destroy a descriptor of transformer encoder output.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as follow:
 *
 *  1.cnnlCreateTransformerEncoderOutputDescriptor().
 *
 *  @param[in]  desc
 *    Input. Description of transformer encoder_output operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlDestroyTransformerEncoderOutputDescriptor(cnnlTransformerEncoderOutputDescriptor_t desc);

// Group:Transformer Encoder Output
/*!
 *  @brief A function.
 *
 *  This function is used to assign transformer encoder output descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before and after this function. The dependence is as follow:
 *
 *   - The function named cnnlCreateTransformerEncoderOutputDescriptor() needs to be called before
 *     this function.
 *
 *   - The function named cnnlDestroyTransformerEncoderOutputDescriptor() needs to be called after
 *     this function.
 *
 *  @param[in]  desc
 *    Input. Description of transformer encoder output operation.
 *  @param[in]  layernorm_mode
 *    Input. The layernorm position.
 *    - CNNL_TRANSFORMER_NO_LAYERNORM: without layernorm.
 *    - CNNL_TRANSFORMER_PRE_LAYERNORM: layernorm in front of EncoderOutput.
 *  @param[in]  output_mode
 *    Input. The output mode.
 *    - CNNL_TRANSFORMER_ENCOUT_NOT_DATAFORMAT: calculate float/half outputs.
 *    - CNNL_TRANSFORMER_ENCOUT_DATAFORMAT_FPOUT: calculate float/half outputs, and tile out_K
 *      and transpose out_V.
 *    - CNNL_TRANSFORMER_ENCOUT_DATAFORMAT_FPOUT_CALCPOS: calculate float/half outputs with tiling
 *      out_K and transposing out_V, and calculate quant_param of outputs as well.
 *    - CNNL_TRANSFORMER_ENCOUT_DATAFORMAT_OFFLINE_QUANT: calculate int16 outputs with tiling
 *      out_K and transposing out_V, which use offline quantified position and scale.
 *    - CNNL_TRANSFORMER_ENCOUT_DATAFORMAT_ONLINE_QUANT: calculate int16 outputs with tiling out_K
 *       and transposing out_V, and calculate online quantified position and scale.
 *  @param[in]  use_bias
 *    Input. Whether to use bias.
 *  @param[in]  decoder_layer_num
 *    Input. Layer number of decoder, which falls in the range of [1, 6].
 *  @param[in]  head_num
 *    Input. Head number mutil_head_attention.
 *  @param[in]  head_size
 *    Input. Head size.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetTransformerEncoderOutputDescriptor(cnnlTransformerEncoderOutputDescriptor_t desc,
                                          const cnnlTransformerLayernormMode_t layernorm_mode,
                                          const cnnlTransformerEncOutMode_t output_mode,
                                          const bool use_bias,
                                          const bool input_online_quantify,
                                          const int decoder_layer_num,
                                          const int head_num,
                                          const int head_size);

// Group:Transformer Encoder Output
/*!
 *  @brief A function.
 *
 *  This function forwards transformer encoder output operation on MLU device.
 *
 *  The transformer encoder output function initializes K/V matrices shared by
 *
 *  different layers of decoder based on the results of encoder. Since decoding
 *
 *  process will be repeated until the termimate-token is reached, K/V matrices
 *
 *  used by enc-dec-attn can be pre-computed before the decoding process, i.e.,
 *
 *  by this encoder output operation.
 *
 *  **Formula**
 *
 *  This operation contains the following steps:
 *
 *  1. Pre-Layernorm if layernorm_mode = CNNL_TRANSFORMER_PRE_LAYERNORM.
 *
 *    input_normed = layernorm(input, beta, gamma) or just input.
 *
 *  2. Compute K/V matrices.
 *
 *    For decoder_layer_num layers of decoder:
 *
 *      K = fc(input_normed, filter_k) + bias_k.
 *
 *      V = fc(input_normed, filter_v) + bias_v.
 *
 *  3. Reformat K/V matrices if output_mode >= 1.
 *
 *    From original shape [batch head seg_num token_seg head_size]:
 *
 *      K: transpose to [batch head token_seg seg_num head_size].
 *
 *      V: transpose to [batch head head_size seg_num token_seg].
 *
 *    Where seg_num = token / token_seg + 1(if remainder is non-zero).
 *
 *    If token >= 64, token_seg = 64, else token_seg = token.
 *
 *  **Example**
 *
 *  For Input: [32 160 256] ([Batch Token Ci]).
 *
 *      filter: [3 256 256] ([Decoder_layer_num Co Ci]).
 *
 *      Bias: [3 256] ([Decoder_layer_num Co]).
 *
 *  Get Original output: [3 32 head_num 160 head_size] for K/V respectively.
 *
 *  If output_mode >= 1, for each K/V:
 *
 *    160 = 64 * 2 + 32.
 *
 *    [32 head_num 160 head_size] -> [32 head_num 3 64 head_size] with 0-padding.
 *
 *    K: [3 32 head_num 64 head_size] -> [3 32 head_num 64 head_size].
 *
 *    V: [3 32 head_num 64 head_size] -> [3 32 head_num head_size 64].
 *
 *  4. Use quantifyparams when output_mode >= 2.
 *
 *    Calculate online-quantifyparams if output_mode = CNNL_TRANSFORMER_ENCOUT_DATAFORMAT_FPOUT_CALCPOS.
 *       pos, scale = computeQuantifyParams(K/V_normed).
 *
 *    offline-quantify if output_mode = CNNL_TRANSFORMER_ENCOUT_DATAFORMAT_OFFLINE_QUANT.
 *       K/V_normed_quantified = quantify(K/V_normed, pos, scale).
 *
 *    Online-quantify if output_mode = CNNL_TRANSFORMER_ENCOUT_DATAFORMAT_ONLINE_QUANT.
 *       pos, scale = computeQuantifyParams(K/V_normed).
 *       K/V_normed_quantified = quantify(K/V_normed, pos, scale).
 *
 *  **DataType**
 *
 *  On MLU270 and MLU370:
 *
 *   - input: float, half, int16.
 *   - filter: int16, half.
 *   - bias: float, half.
 *   - output: float, half, int16.
 *
 *  **Scale Limitation**
 *
 *   - Scale Limitation if output_mode >= 1
 *
 *     1. head_num supports 8 or 16.
 *
 *     2. head_size must be 64.
 *
 *     3. Ci = Co = head_num * head_size.
 *
 *     4. Token supports [1, 512].
 *
 *     5. Decoder_layer_num supports [1, 6]
 *
 *   - Scale Limitation if output_mode == 0
 *
 *     1. head_num supports 4, 8, 12 or 16.
 *
 *     2. head_size supports 32, 64 or 96.
 *
 *     3. Ci = Co = head_num * head_size.
 *
 *     4. Token supports [1, 1024].
 *
 *     5. Decoder_layer_num supports [1, 128].
 *
 *  **Performance Optimization**
 *
 *    When the dimension of input meet N*T = 512*n(n=1,2,3..) , the performance is best.
 *
 *  @param[in]  handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           transformer_encoder_output operation.
 *  @param[in]  desc_encoder_output
 *    Input. A descriptor of transformer_encoder_output.
 *  @param[in]  input_desc
 *    Input. A descriptor of input tensor.
 *  @param[in]  input
 *    Input. An MLU tensor, a pointer to the input data on device.
 *  @param[in]  filter_k_desc
 *    Input. An array of cnnlTensorDescriptors which holds dimension, data type,
 *    and layout of filter_k tensor. The number of desc must be decoder_layer_num, and the shape of
 *    filter is [head_num * head_size, Ci].
 *  @param[in]  filter_k
 *    Input. Pointer to the host memory that stores an array of pointers to the device memory of
 *    filter_k tensors. The element order of this filter array must be consistent with the element
 *    order of the cnnlTensorDescriptors array.
 *  @param[in]  filter_v_desc
 *    Input. An array of cnnlTensorDescriptors which holds dimension, data type,
 *    and layout of filter_v tensor. The number of desc must be decoder_layer_num, and the shape of
 *    filter is [head_num * head_size, Ci].
 *  @param[in]  filter_v
 *    Input. Pointer to the host memory that stores an array of pointers to the device memory of
 *    filter_v tensors. The element order of this filter array must be consistent with the element
 *    order of the cnnlTensorDescriptors array.
 *  @param[in]  bias_k_desc
 *    Input. An array of cnnlTensorDescriptors which holds dimension, data type, and layout of
 *    bias_k tensor. The number of desc must be decoder_layer_num, and the shape of bias is
 *    [head_num * head_size].
 *  @param[in]  bias_k
 *    Input. Pointer to the host memory that stores an array of pointers to the device memory of
 *    bias_k tensors. The element order of this bias array must be consistent with the element
 *    order of the cnnlTensorDescriptors array.
 *  @param[in]  bias_v_desc
 *    Input. An array of cnnlTensorDescriptors which holds dimension, data type, and layout of
 *    bias_v tensor. The number of desc must be decoder_layer_num, and the shape of bias is
 *    [head_num * head_size].
 *  @param[in]  bias_v
 *    Input. Pointer to the host memory that stores an array of pointers to the device memory of
 *     bias_v tensors. The element order of this bias array must be consistent with the element
 *    order of the cnnlTensorDescriptors array.
 *  @param[in]  gamma_desc
 *    Input. A descriptor of gamma tensor used in layernorm.
 *  @param[in]  gamma
 *    Input. An MLU tensor, a pointer to the gamma data on device.
 *  @param[in]  beta_desc
 *    Input. A descriptor of beta tensor used in layernorm.
 *  @param[in]  beta
 *    Input. An MLU tensor, a pointer to the beta data on device.
 *  @param[out]  output_k_desc
 *    Output. An array of cnnlTensorDescriptors which holds dimension, data type, and layout of
 *    output_k tensors. The number of desc must be decoder_layer_num. If output_mode = 0, the shape
 *    of each output_k is [batch, head_num, token, head_size], else the shape is [batch, head_num,
 *    token_seg, seg_num, head_size].
 *  @param[out]  output_k
 *    Output. Pointer to the host memory that stores an array of pointers to the device memory of
 *    output tensors. The element order of this output_k array must be consistent with the element
 *    order of the cnnlTensorDescriptors array.
 *  @param[out]  outpos_k_desc
 *    Output. An array of cnnlTensorDescriptors which holds dimension, data type, and layout of
 *    outpos_k tensors. The number of desc must be decoder_layer_num. The shape of each outpos_k
 *    is [1]. Set nullptr when output_mode < 2.
 *  @param[out]  outpos_k
 *    Output. Pointer to the host memory that stores an array of pointers to the device memory of
 *    outpos tensors. The element order of this outpos_k array must be consistent with the element
 *    order of the cnnlTensorDescriptors array. Set nullptr when output_mode < 2.
 *  @param[out]  outscale_k_desc
 *    Output. An array of cnnlTensorDescriptors which holds dimension, data type, and layout of
 *    outscale_k tensors. The number of desc must be decoder_layer_num. The shape of each
 *    outscale_k is [1]. Set nullptr when output_mode < 2.
 *  @param[out]  outscale_k
 *    Output. Pointer to the host memory that stores an array of pointers to the device memory of
 *    outscale tensors. The element order of this outscale array must be consistent with the element
 *    order of the cnnlTensorDescriptors array. Set nullptr when output_mode < 2.
 *  @param[out]  output_v_desc
 *   Output. An array of cnnlTensorDescriptors which holds dimension, data type, and layout of
 *   output_k tensors. The number of desc must be decoder_layer_num. If output_mode = 0, the shape
 *   of each output_v is [batch, head_num, token, head_size], else the shape is [batch, head_num,
 *   head_size, ceil(token/64)*64].
 *  @param[out]  output_v
 *   Output. Pointer to the host memory that stores an array of pointers to the device memory of
 *   output tensors. The element order of this output_v array must be consistent with the element
 *   order of the cnnlTensorDescriptors array.
 *  @param[out]  outpos_v_desc
 *   Output. An array of cnnlTensorDescriptors which holds dimension, data type, and layout of
 *   outpos_k tensors. The number of desc must be decoder_layer_num. The shape of each outpos_v
 *   is [1]. Set nullptr when output_mode < 2.
 *  @param[out]  outpos_v
 *   Output. Pointer to the host memory that stores an array of pointers to the device memory of
 *   outpos tensors. The element order of this outpos_v array must be consistent with the element
 *   order of the cnnlTensorDescriptors array. Set nullptr when output_mode < 2.
 *  @param[out]  outscale_v_desc
 *   Output. An array of cnnlTensorDescriptors which holds dimension, data type, and layout of
 *   outscale_k tensors. The number of desc must be decoder_layer_num. The shape of each
 *   outscale_v is [1]. Set nullptr when output_mode < 2.
 *  @param[out]  outscale_v
 *   Output. Pointer to the host memory that stores an array of pointers to the device memory of
 *   outscale tensors. The element order of this outscale_v array must be consistent with the
 *   element order of the cnnlTensorDescriptors array. Set nullptr when output_mode < 2.
 *
 *  @retval  CNNL_STATUS_SUCCESS = 0
 *    The function ends normally.
 *  @retval  CNNL_STATUS_BAD_PARAM = 3
 *    One or more of the following conditions are satisfied:
 *    - Handle is NULL.
 *    - Input is NULL.
 *    - Output is NULL.
 *    - filter is NULL.
 *    - Layernorm_gamma or layernorm beta is NULL when layernorm_mode > 0.
 *    - Dims are invalid.
 */
cnnlStatus_t CNNL_WIN_API
cnnlTransformerEncoderOutput(cnnlHandle_t handle,
                             const cnnlTransformerEncoderOutputDescriptor_t encoder_output_desc,
                             const cnnlTensorDescriptor_t input_desc,
                             const void *input,
                             const cnnlTensorDescriptor_t filter_k_desc[],
                             void **filter_k,
                             const cnnlTensorDescriptor_t filter_v_desc[],
                             void **filter_v,
                             const cnnlTensorDescriptor_t bias_k_desc[],
                             void **bias_k,
                             const cnnlTensorDescriptor_t bias_v_desc[],
                             void **bias_v,
                             const cnnlTensorDescriptor_t gamma_desc,
                             const void *gamma,
                             const cnnlTensorDescriptor_t beta_desc,
                             const void *beta,
                             const cnnlTensorDescriptor_t output_k_desc[],
                             void **output_k,
                             const cnnlTensorDescriptor_t outpos_k_desc[],
                             void **outpos_k,
                             const cnnlTensorDescriptor_t outscale_k_desc[],
                             void **outscale_k,
                             const cnnlTensorDescriptor_t output_v_desc[],
                             void **output_v,
                             const cnnlTensorDescriptor_t outpos_v_desc[],
                             void **outpos_v,
                             const cnnlTensorDescriptor_t outscale_v_desc[],
                             void **outscale_v,
                             void *workspace,
                             size_t workspace_size);

// Group:Transformer Encoder Output
/*!
 *  @brief A function.
 *  This function retrieves extra space size that needed in TransformerEncoderOutput operation.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as follow:
 *
 *  1.cnnlCreateTransformerEncoderOutputDescriptor().
 *
 *  2.cnnlSetTransformerEncoderOutputDescriptor().
 *
 *  @param[in] handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           TransformerEncoderOutput operations.
 *  @param[in] desc
 *    Input. A descriptor of transformer_encoder_output.
 *  @param[out] size
 *    Output. Extra space size that needed in TransformerEncoderOutput operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions are met:
 *    - The handle is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlGetTransformerEncoderOutputWorkspaceSize(cnnlHandle_t handle,
                                             const cnnlTransformerEncoderOutputDescriptor_t desc,
                                             size_t *size);
/******************************************************************************
 * Cambricon CNNL OP: TransformerBeamRearrange
 ******************************************************************************/
// Group:Transformer Beam Rearrange
/*!
 * @brief Implements in-place beam rearrange of cached decoder key/value according to beam search result.
 *
 * It also records historical result of beam search to restore the correct order of decoder cache.
 * For example, when the shape of each cache is [batch, beam, head_num, seq_len, head_size]:
   @verbatim
   1. Rearrange each cache according to best_beams
   for i in range(0, layer_num * 2):
     for batch in range(0, batch_size):
       for beam in range(0, beam_size):
         decoder_states[i, batch, beam, :, 0:nframe-2, :] = decoder_states[i, batch, best_beam[batch, beam], :, 0:nframe-2, :]

   2. Store best_beams to best_beams_cache
   best_beams_cache[:, nframe-1] = best_beam
   @endverbatim
 *
 * @param[in]  handle
 *   Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and
 *   queues in the operation. For detailed information, see cnnlHandle_t.
 * @param[in]  workspace
 *   Input. The pointer to data address of workspace, which is allocated by users
 *   to store pointers in \b caches_array.
 * @param[in]  best_beam_desc
 *   Input.  Descriptor of \b best_beam. Shape must be [batch_size, beam_size] and data type
 *   must be INT8.
 * @param[in]  best_beam
 *   Input.  Device pointer points to best_beam space.
 *   \b best_beam is provided by the beam search operation, storing the top beam_size indices
 *   of last frame.
 * @param[in]  nframe_desc
 *   Input.  Descriptor of \b nframe. Shape must be [1], and data type must be INT32.
 * @param[in]  nframe
 *   Input.  Device pointer points to nframe space. Indicates current frame index.
 * @param[in]  single_cache_desc
 *   Input. Descriptor of each cache. Its data type must be float or half. Shape must be
 *   [batch_size, beam_size, head_num, max_decode_length, head_size] or
 *   [batch_size, beam_size, max_decode_length, hidden_size], where hidden_size equals to
 *   head_num * head_size.
 * @param[in,out]  caches_array
 *   Input & Output. Pointer to the host memory that stores an array of pointers to the device memory.
 *   It must contain \b caches_num elements, where each pointer points
 *   to the data address of one cache tensor. All tensors must have the same shape and data type as
 *   \b single_cache_desc described.
 *   After each frame, they are rearranged in the beam_size dimension
 *   according to \b best_beams_cache.
 * @param[in]  caches_num
 *   Input. An integer indicating how many caches need to be rearranged. Usually it equals to
 *   decoder_layer_num * 2.
 * @param[in]  best_beams_cache_desc
 *   Input. Descriptor of \b best_beams_cache. Shape must be [batch_size, ngroup, beam_size] and
 *   data type must be INT8.
 * @param[out]  best_beams_cache
 *   Output. Device pointer points to best_beams_cache space holding
 *   the previous beam indicies of each group to concat groups in correct order.
 * @par Return
 * - CNNL_STATUS_SUCCESS, CNNL_STATUS_BAD_PARAM
 *
 * @par Reference
 * - https://github.com/tensorflow/models/blob/r1.13.0/official/transformer/model/beam_search.py
 *
 * @par Data Type
 * - \b best_beam and \b best_beams_cache: int8.
 * - \b nframe: int32.
 * - \b decoder_states: float or half.
 *
 * @par Scale Limitation
 * - The dimensions of tensors must meet following requirements:
 *   * 1 <= batch_size.
 *   * 1 <= beam_size <= 16.
 *   * 1 <= max_decode_length <= 1024.
 *   * 1 <= caches_num <= 1024.
 *   * 1 <= head_num <= 32.
 *   * 1 <= head_size <= 128.
 *   * 1 <= ngroup <= max_decode_length, and ngroup <= 60.
 *   * 1 <= \b nframe <= max_decode_length, since value of \b nframe is already
 *     incremented by beam search operation.
 *   * Size of decoder_states must be no larger than 2GB.
 *
 * @note
 * - In order to avoid large memory copy of decoder_states, beam rearrange does not really move
 * memory like above expression. Each layer of cache is divided into ngroup groups in dimension
 * of max_decode_length and each time only the current group is rearranged. Other groups' beam
 * position are recorded into \b best_beams_cache like a linked list. From \b best_beams_cache,
 * other operations like self_attn are able to restore the correct decoder_states.
 *
 * @par Example
 * - None.
 */
cnnlStatus_t CNNL_WIN_API
cnnlTransformerBeamRearrangeWithSplitedCache(cnnlHandle_t handle,
                             void *workspace,
                             const cnnlTensorDescriptor_t best_beam_desc,
                             const void *best_beam,
                             const cnnlTensorDescriptor_t nframe_desc,
                             const void *nframe,
                             const cnnlTensorDescriptor_t single_cache_desc,
                             void **caches_array,
                             int caches_num,
                             const cnnlTensorDescriptor_t best_beams_cache_desc,
                             void *best_beams_cache);

// Group:Transformer Beam Rearrange
/*!
 *  @brief
 *  This function is used to get extra space size that needed in transformer
 *  beam rearrange operation.
 *
 *  @param[in]  handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and
 *    queues in the operation. For detailed information, see cnnlHandle_t.
 *  @param[in]  caches_num
 *    Input. An integer indicating how many caches need to be rearranged. Usually it equals to
 *    decoder_layer_num * 2.
 *  @param[out] size_workspace
 *    Output. Size of workspace.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of size_workspace is NULL.
 *    - The value of caches_num is invalid.
 */
cnnlStatus_t CNNL_WIN_API
cnnlGetTransformerBeamRearrangeWorkspaceSize(cnnlHandle_t handle,
                                             int caches_num,
                                             size_t *size_workspace);

// Group:Transformer Beam Rearrange
/*!
 *  @brief Implements in-place beam rearrange of cached decoder key/value according to beam search result.
 *
 *  It also records history result of beam search to restore the correct order of decoder cache.
 *  For example, when the shape of each cache is [batch, beam, head_num, seq_len, head_size]:
   @verbatim
   1. Rearrange each cache according to best_beams
   for i in range(0, layer_num * 2):
     for batch in range(0, batch_size):
       for beam in range(0, beam_size):
         decoder_states[i, batch, beam, :, 0:nframe-2, :] = decoder_states[i, batch, best_beam[batch, beam], :, 0:nframe-2, :]

   2. Store best_beams to best_beams_cache
   best_beams_cache[:, nframe-1] = best_beam
   @endverbatim
 *
 *  @param[in]  handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and
 *    queues in the operation. For detailed information, see cnnlHandle_t.
 *  @param[in]  best_beam_desc
 *    Input.  Descriptor of \b best_beam. Shape must be [batch_size, beam_size] and data type
 *    must be INT8.
 *  @param[in]  best_beam
 *    Input.  Device pointer points to best_beam space.
 *    \b best_beam is provided by the beam search operation, stores the top beam_size indicies
 *    of last frame.
 *  @param[in]  nframe_desc
 *    Input.  Descriptor of \b nframe. Shape must be [1], and data type must be INT32.
 *  @param[in]  nframe
 *    Input.  Device pointer points to nframe space. Indicates current frame index.
 *  @param[in]  decoder_states_desc
 *    Input. Descriptor of \b decoder_states. Its data type must be float or half. Shape must be
 *    [layer_num * 2, batch_size, beam_size, head_num, max_decode_length, head_size] or
 *    [layer_num * 2, batch_size, beam_size, max_decode_length, hidden_size], where hidden_size equals to
 *    head_num * head_size.
 *  @param[out]  decoder_states
 *    Input & Output. Device pointer points to decoder_states space.
 *    It is combination of history buffers of key and value
 *    in all decoder self attention layers.
 *    After each frame, they are rearranged in the beam_size dimension
 *    according to \b best_beams_cache.
 *  @param[in]  best_beams_cache_desc
 *    Input. Descriptor of \b best_beams_cache. Shape must be [batch_size, ngroup, beam_size] and
 *    data type must be INT8.
 *  @param[out]  best_beams_cache
 *    Output. Device pointer points to best_beams_cache space holding
 *    the previous beam indicies of each group to concat groups in correct order.
 *  @par Return
 *  - CNNL_STATUS_SUCCESS, CNNL_STATUS_BAD_PARAM
 *
 *  @par Reference
 *  - https://github.com/tensorflow/models/blob/r1.13.0/official/transformer/model/beam_search.py
 *
 *  @par Data Type
 *  - \b best_beam and \b best_beams_cache: int8.
 *  - \b nframe: int32.
 *  - \b decoder_states: float or half.
 *
 *  @par Scale Limitation
 *  - The dimensions of tensors must meet following requirements:
 *    - 1 <= batch_size.
 *    - 1 <= beam_size <= 16.
 *    - 1 <= max_decode_length <= 1024.
 *    - 1 <= head_num <= 32.
 *    - 1 <= head_size <= 128.
 *    - 1 <= ngroup <= max_decode_length, and ngroup <= 60.
 *    - 1 <= value of \b nframe <= max_decode_length, since value of \b nframe is already
 *      incremented by beam search operation.
 *    - Size of decoder_states must be no larger than 2GB.
 *
 *  @note
 *  - In order to avoid large memory copy of decoder_state, beam rearrange does not really move
 *  memory like above expression. Each layer of cache is divided into ngroup groups in dimension
 *  of max_decode_length and each time only the current group is rearranged. Other groups's beam
 *  position are recorded into \b best_beams_cache like a linked list. From \b best_beams_cache
 *  we are able to restore the correct decoder_state.
 *
 *  @par Requirements
 *  - None.
 *  @par Example
 *  - None.
 */
cnnlStatus_t CNNL_WIN_API
cnnlTransformerBeamRearrange(cnnlHandle_t handle,
                             const cnnlTensorDescriptor_t best_beam_desc,
                             const void *best_beam,
                             const cnnlTensorDescriptor_t nframe_desc,
                             const void *nframe,
                             const cnnlTensorDescriptor_t decoder_states_desc,
                             void *decoder_states,
                             const cnnlTensorDescriptor_t best_beams_cache_desc,
                             void *best_beams_cache);

/******************************************************************************
 * Cambricon CNNL OP: Ivfpq - Precise Search
 ******************************************************************************/
// Group:Ivfpq
/*!
 *  @brief A function
 *
 *  This function is one part of the IVFPQ (Invert File System Product Quantization) algorithm.
 *  IVFPQ is used to search and select the nearest feature vectors from the database based on query
 *  vectors. It contains three sub-operators: coarse search, residual-computing and precise search.
 *  This function implements the precise search algorithm on MLU.
 *
 *  **Formula**
 *
 *  This operation contains the following steps:
 *
 *  1. Generate look-up table.
 *
 *    Compute L2-distance between input queries and input codebook, then store the distance as the
 *    look-up table:
 *
 *      look_up_table = computeL2Distance(queries, codebook).
 *
 *  2. Search and find nearest k-features from codes.
 *
 *    In previous step of IVFPQ training, original database is quantified into [codes] based on
 *    [codebook]. [codes] consists of [nlist] Level 1 cluster centroids. Coarse searching selects
 *    the most relevant [nprobe] centroids from the [codes], using the input [query].
 *    This operation computes the distance between [query] and features related to those selected
 *    centroids, and output the ids and distances of the nearest k-features from [ntotal] features.
 *
 *      topk_output = searchAndTopk(look_up_table, codes)
 *
 *  **DataType**
 *
 *    - input: float(query), float(codebook), uint8(codes), int32(nlist_size).
 *    - input: int32(nlist_id_size), int32(input_ids), int32(nlist_offset_in).
 *    - input: int32(nlist_id_offset_in), int32(nprobe_id)
 *    - output: float(topk_output), int32(topk_output_ids).
 *
 *  **Scale Limitation**
 *
 *    - ntotal represents the number of features in codes, must be no larger than
 *      (pow(2,30) - 1) / 32.
 *    - nlist represents the number of segments that codes is divided into during training, must be
 *      no larger than [ntotal].
 *    - codebook_desc->dims[0] represents the number of cluster centroids, must be 256.
 *    - codebook_desc->dims[1] represents the length of one feature vector, must be 256.
 *    - codes_desc->dims[0] represents the number of segment of one feature vector, must be 32.
 *    - nprobe_id_desc->dims[1] represents [nprobe], must be dividable by 16 and must be same for
 *      different batch of query.
 *
 *  **Attention*
 *
 *    - ntotal = sum(nlist_id_size[i]), 0 <= i <= nlist - 1
 *    - nlist_size[i] = 32 * nlist_id_size[i], 0 <= i <= nlist - 1
 *    - nlist_offset_in[i] = 32 * nlist_id_offset_in[i], 0 <= i <= nlist - 1
 *
 *  **Reference**
 *
 *  http://github.com/facebookresearch/faiss
 *
 *  @param[in] handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           IVFPQ operation.
 *  @param[in] query_desc
 *    Input. Descriptor of query, the dimension is [batch, nprobe, 256].
 *  @param[in] query
 *    Input. An MLU tensor, a pointer to device query data. Query stores all input features after
 *           residual-computing.
 *  @param[in] codebook_desc
 *    Input. Descriptor of codebook, the dimension is [256, 256].
 *  @param[in] codebook
 *    Input. An MLU tensor, a pointer to device codebook data. Codebook stores all level-2 cluster
 *           centroids.
 *  @param[in] nlist_size_desc
 *    Input. Descriptor of nlist size, the dimension is [nlist].
 *  @param[in] nlist_size
 *    Input. An MLU tensor, a pointer to device nlist_size data. nlist_size stores the size of every
 *           nlist segment.
 *  @param[in] nlist_id_size_desc
 *    Input. Descriptor of nlist id size, the dimension is [nlist].
 *  @param[in] nlist_id_size
 *    Input. An MLU tensor, a pointer to device nlist id size data. nlist_id_size stores the size of
 *           every nlist id segment.
 *  @param[in] codes_desc
 *    Input. Descriptor of codes, the dimension is [32 * ntotal].
 *  @param[in] codes
 *    Input. An MLU tensor, a pointer to device codes data. Codes is the database which contains all
 *           feature vectors to search. codes is divided into [nlist] segments with different sizes
 *           during training. nlist_size is defined to store the size of every codes segments.
 *  @param[in] codes_id_desc
 *    Input. Descriptor of codes id, the dimension is [ntotal].
 *  @param[in] codes_id
 *    Input. An MLU tensor, a pointer to device codes id data. codes_id stores the index of every
 *           code feature in the original database. Each feature has a unique id. codes_id is also
 *           divided into [nlist] segments according to the partition of codes. nlist_id_size is
 *           defined to store the size of every codes_id segments.
 *  @param[in] nlist_offset_in_desc
 *    Input. Descriptor of nlist offset of codes, the dimension is [nlist].
 *  @param[in] nlist_offset_in
 *    Input. An MLU tensor, a pointer to device nlist offset data. nlist_offset_in stores the offset
 *           of every nlist segment with respect to the beginning of codes.
 *  @param[in] nlist_id_offset_in_desc
 *    Input. Descriptor of nlist id offset of codes, the dimension is [nlist].
 *  @param[in] nlist_id_offset_in
 *    Input. An MLU tensor, a pointer to device nlist id offset data. nlist_id_offset_in stores the
 *           offset of every nlist id segment with respect to the beginning of codes_id.
 *  @param[in] nprobe_id_desc
 *    Input. Descriptor of nprobe id, the dimension is [batch * nprobe].
 *  @param[in] nprobe_id
 *    Input. An MLU tensor, a pointer to device nprobe id data. nprobe_id stores the ids of selected
 *           segments from codes_id.
 *  @param[out] topk_output_desc
 *    Output. Descriptor of topk output, the dimension is [batch * topk].
 *  @param[out] topk_output
 *    Output. An MLU tensor, a pointer to device topk output data. topk_output stores the nearest
 *            topk distances with respect to queries.
 *  @param[out] topk_output_ids_desc
 *    Output. Descriptor of topk output ids, the dimension is [batch * topk].
 *  @param[out] topk_output_ids
 *    Output. An MLU tensor, a pointer to device topk output ids data. topk_output_ids store the
 *            indexes of topk nearest features from codes_id.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions must be met:
 *    - handle is NULL.
 *    - query_desc is NULL.
 *    - query is NULL.
 *    - codebook_desc is NULL.
 *    - codebook is NULL.
 *    - nlist_size_desc is NULL.
 *    - nlist_size is NULL.
 *    - nlist_id_size_desc is NULL.
 *    - nlist_id_size is NULL.
 *    - codes_desc is NULL.
 *    - codes is NULL.
 *    - input_ids_desc is NULL.
 *    - input_ids is NULL.
 *    - nlist_offset_in_desc is NULL.
 *    - nlist_offset_in is NULL.
 *    - nlist_id_offset_in_desc is NULL.
 *    - nlist_id_offset_in is NULL.
 *    - nprobe_id_desc is NULL.
 *    - nprobe_id is NULL.
 *    - topk_output_desc is NULL.
 *    - topk_output is NULL.
 *    - topk_output_ids_desc is NULL.
 *    - topk_output_ids is NULL.
 *    - tensor dim does not match.
 *  @retval CNNL_STATUS_NOT_SUPPORTED
 *    - MLU device does not support Union4-type tasks.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 */
cnnlStatus_t CNNL_WIN_API
cnnlIvfProductQuantization(cnnlHandle_t handle,
                           const cnnlTensorDescriptor_t query_desc,
                           const void *query,
                           const cnnlTensorDescriptor_t codebook_desc,
                           const void *codebook,
                           const cnnlTensorDescriptor_t nlist_size_desc,
                           const void *nlist_size,
                           const cnnlTensorDescriptor_t nlist_id_size_desc,
                           const void *nlist_id_size,
                           const cnnlTensorDescriptor_t codes_desc,
                           const void *codes,
                           const cnnlTensorDescriptor_t codes_id_desc,
                           const void *codes_id,
                           const cnnlTensorDescriptor_t nlist_offset_in_desc,
                           const void *nlist_offset_in,
                           const cnnlTensorDescriptor_t nlist_id_offset_in_desc,
                           const void *nlist_id_offset_in,
                           const cnnlTensorDescriptor_t nprobe_id_desc,
                           const void *nprobe_id,
                           const cnnlTensorDescriptor_t topk_output_desc,
                           void *topk_output,
                           const cnnlTensorDescriptor_t topk_output_ids_desc,
                           void *topk_output_ids);

/******************************************************************************
 * Cambricon CNNL OP: Roialign
 ******************************************************************************/
/*! The descriptor of Roialign*/
/*! The descriptor of the roialign operations that holds operation information
 * including the num_level, pooled_height, pooled_width, sampling_ratio, canonical_scale
 * canonical_leval, img_h, img_w, pool_mode, roi_type.
 *
 *  You need to call the ::cnnlCreateRoialignDescriptor function to create a
 *  descriptor, and call the ::cnnlSetRoialignDescriptor function to set the
 *  information of the operation to the descriptor. Also, you need to destroy
 *  the Cambricon CNNL context at the end with the ::cnnlDestroyRoialignDescriptor function.
 */
typedef struct cnnlRoialignStruct *cnnlRoialignDescriptor_t;

// Group:Roialign
/*!
 *  @brief A function.
 *
 *  The roialign operation supporting feature pyramid network.
 *
 *  **Formula**
 *
 *    Given following input tensors:
 *    input_rois: (batch_size)(num_rois, roi_offset)
 *    inputs(level)(batch_size, level_h, level_w, channels)
 *
 *    1. for multi level feature maps, compute roi(roi_1, roi_2, roi_3, roi_4) iterate through num_rois rois,
 *       get which level current roi belongs to.
 *    level = level_map(canonical_level, canonical_scale, finest_scale, rois)
 *    spatial_scale = spatial_scales[level]
 *    input = inputs[level]
 *
 *    2. get the roi coordinates.
 *    offset = aligned ? -0.5 : 0
 *    roi_coord.w_start = roi_x1 * spatial_scale + offset
 *    roi_coord.h_start = roi_y1 * spatial_scale + offset
 *    roi_coord.w_end = roi_x2 * spatial_scale + offset
 *    roi_coord.h_end = roi_y2 * spatial_scale + offset
 *
 *    3. get the bins according to output feature map.
 *    bins_coord(pooled_height, pooled_width, 4) = bin(roi_coord, pooled_height, pooled_width)
 *    bin.x_min = roi_coord.x + (roi_coord.w / pooled_width) * pooled_width_index
 *    bin.y_min = roi_coord.y + (roi_coord.h / pooled_height) * pooled_height_index
 *
 *    4. sample 4 point for every bin.
 *    sample_coord(pooled_height, pooled_width, 4) = sample(bins_coord, sampling_ratio)
 *    sample.x = bin.x_min + ((sample_width_index + 0.5) * (roi_coord.w / pooled_width) / sampling_ratio);
 *    sample.y = bin.y_min + ((sample_height_index + 0.5) * (roi_coord.h / pooled_height) / sampling_ratio);
 *
 *    5. get every sample point data with bilinear interpolatation.
 *    sample_value(pooled_height, pooled_width, 4, channels) = bilinear(sample_coord, input)
 *    sample.value = inter_1 * w1 + inter_2 * w2 + inter_3 * w3 + inter_4 * w4;
 *
 *    6. get bin data with avgpool.
 *    bin_value(pooled_height, pooled_width, cahnnels) = avgpool(sample_value)
 *
 *    We can get the following output tensor:
 *    output: (total_rois_num, pooled_height, pooled_width, cahnnels)
 *
 *  **DataType**
 *
 *    - input: float, half.
 *
 *    - input_rois: float, half.
 *
 *    - output: float, half.
 *
 *  **Attention**
 *
 *    - The input layout must be NHWC.
 *
 *    - The input rois layout must be ARRAY for fpn roialign and must be NHWC or NCHW for roialign.
 *
 *    - The output layout must be NHWC.
 *
 *    - The data type of input, input_rois and output must be same.
 *
 *  **Scale Limitation**
 *
 *    According to the definition of roialign, the parameters must satisfy
 *    the following conditions:
 *
 *    - The num_level must be between 1 and 10.
 *
 *    - The batch_size must be 1 for fpn roialign and must be between 1 and 1024
 *      for roialign and multi-level roialign.
 *
 *    - The sampling_ratio must be 2 for fpn roialign.
 *
 *    - The canonical_scale must be 224.
 *
 *    - The canonical_level must be 4.
 *
 *    - The finest_scale must be greater than 0 for multi-level roialign.
 *
 *    - The channels must be between 1 and 2048, and must be divisible by 64 for
 *      multi-level roialign.
 *
 *    - The pooled_height and pooled_width must be between 1 and 512.
 *
 *    - The img_h and img_w must be between 1 and 4096.
 *
 *    - The img_h(img_w) must be greater than any height(width) of input size.
 *
 *    - The pool_mode must be CNNL_POOLING_AVERAGE_COUNT_EXCLUDE_PADDING.
 *
 *    - The rois_type must be CNNL_ROI_CENTER for fpn roialgin.
 *
 *    - The rois_type must be CNNL_ROI_CORNER_SCORE and CNNL_ROI_SCORE_CORNER for roialign.
 *
 *    - The rois_type must be CNNL_ROI_BATCHID_CORNER for multi-level roialign.
 *
 *    - The compute_dtype must be CNNL_DTYPE_FLOAT or CNNL_DTYPE_HALF.
 *
 *    - For multi-level roialign, the compute_dtype must be CNNL_DTYPE_FLOAT when
 *      the data type of input is float.
 *
 *  **Performance Optimization**
 *
 *    When the channels meet channels % 64 = 0, the performance is the best.
 *
 *  **Example**
 *
 *    Dimension of every input: [batch_size, height, width, channels]
 *
 *    Dimension of every input_rois: [num_rois, roi_offset]
 *
 *    Then we will get the output:
 *
 *    Dimension of output: [total_num_rois, pooled_height, pooled_width, channels]
 *
 *  **API Dependency**
 *
 *   You need to call the cnnlCreateRoialignDescriptor() and cnnlGetRoialignWorkspaceSize()
 *   functions before calling this function.
 *
 *   You need to call the cnnlDestroyRoialignDescriptor() function after calling this function.
 *
 *  @param[in]  handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           roialign operation.
 *  @param[in]  desc
 *    Input. A struct with parameters of roialign.
 *  @param[in]  input_desc
 *    Input. Pointer to the host memory that stores an array of tensor descriptors which holds dimension,
 *           datatype, and layout of different level feature map tensor. The shape of tensor must be
 *           [batch_size, level_h, level_w, channels].
 *  @param[in]  input
 *    Input. Pointer to the host memory that stores elements of a 1-D array pointing to different
 *           level feature map tensors on device. The element order of this input array must be
 *           consistent with element order of the cnnlTensorDescriptors array.
 *  @param[in]  input_rois_desc
 *    Input. Pointer to the host memory that stores an array of tensor descriptors which holds dimension,
 *           datatype, and layout of different batch rois information tensor. The shape of tensor vary
 *           based on different task and layout of tensor:
 *           1.fpn roialign: The layout must be ARRAY and the shape of the tensor must be [roi_num, 4].
 *           2.roialign: When the layout is NCHW, the shape of tensor must be [roi_num, param_num].
 *           When the layout is NHWC, the shape of tensor must be [param_num, roi_num].
 *           The number and order of roi vary based on different rois_type:
 *           1.CNNL_ROI_CORNER:         The shape must be [roi_x_start, roi_y_start, roi_x_end, roi_y_end].
 *           2.CNNL_ROI_CORNER_BATCHID: The shape must be [roi_x_start, roi_y_start, roi_x_end, roi_y_end, batch_id].
 *           3.CNNL_ROI_BATCHID_CORNER: The shape must be [batch_id, roi_x_start, roi_y_start, roi_x_end, roi_y_end].
 *           4.CNNL_ROI_CENTER:         The shape must be [roi_x_start, roi_y_start, roi_x_end, roi_y_end].
 *           5.CNNL_ROI_CENTER_BATCHID: The shape must be [roi_x_start, roi_y_start, roi_x_end, roi_y_end, batch_id].
 *           6.CNNL_ROI_BATCHID_CENTER: The shape must be [batch_id, roi_x_start, roi_y_start, roi_x_end, roi_y_end].
 *           7.CNNL_ROI_CORNER_SCORE:   The shape must be [roi_x_start, roi_y_start, roi_x_end, roi_y_end, score].
 *           8.CNNL_ROI_SCORE_CORNER:   The shape must be [score, roi_x_start, roi_y_start, roi_x_end, roi_y_end].
 *           9.CNNL_ROI_CENTER_SCORE:   The shape must be [roi_x_start, roi_y_start, roi_x_end, roi_y_end, score].
 *           10.CNNL_ROI_SCORE_CENTER:  The shape must be [score, roi_x_start, roi_y_start, roi_x_end, roi_y_end].
 *           Note that for fpn roialign, rois_type must be CNNL_ROI_CENTER. for roialign, rois_type must be
 *           CNNL_ROI_CORNER_SCORE or CNNL_ROI_SCORE_CORNER.
 *  @param[in]  input_rois
 *    Input. Pointer to the host memory that stores elements of a 1-D array pointing to different batch rois
 *           information tensors on device. The element order of this input array must be consistent
 *           with element order of the cnnlTensorDescriptors array.
 *  @param[in]  workspace
 *    Input. The pointer to data address of workspace.
 *  @param[in]  workspace_size
 *    Input. The value of workspace_size.
 *  @param[in]  output_desc
 *    Input. Pointer to the host memory that stores a tensor descriptor which holds dimension,
 *           datatype, and layout of output tensor. The shape of tensor must be [total_rois_num,
 *           pooled_height, pooled_width, cahnnels].
 *  @param[out] output
 *    Output. Device pointer points to output space.
 *  @retval CNNL_STATUS_SUCCESS = 0
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM = 3
 *    One or more of the following conditions are encountered:
 *    - handle is NULL.
 *    - pointer is NULL.
 *    - parameters do not meet scale limitation.
 *  @retval CNNL_STATUS_ARCH_MISMATCH
 *    One or more of the following conditions are encountered:
 *    - This function is run on the hardware platform that is not supported.
 */
cnnlStatus_t CNNL_WIN_API
cnnlRoialign(cnnlHandle_t handle,
             const cnnlRoialignDescriptor_t roialign_desc,
             const cnnlTensorDescriptor_t input_desc[],
             const void *const input[],
             const cnnlTensorDescriptor_t input_rois_desc[],
             const void *const input_rois[],
             void *workspace,
             size_t workspace_size,
             cnnlTensorDescriptor_t output_desc,
             void *output);

// Group:Roialign
/*!
 *  @brief A function.
 *
 *  This function is used to create a descriptor of roialign and malloc memory for it.
 *
 *  @param[in]  desc
 *    Input. Description of roialign operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_ALLOC_FAILED
 *    The function malloc memory space failed.
 */
cnnlStatus_t CNNL_WIN_API
cnnlCreateRoialignDescriptor(cnnlRoialignDescriptor_t *desc);

// Group:Roialign
/*!
 *  @brief A function.
 *
 *  This function is used to destroy a descriptor of roialign and free memory for it.
 *
 *  @param[in]  desc
 *    Input. Description of roialign operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlDestroyRoialignDescriptor(cnnlRoialignDescriptor_t desc);

// Group:Roialign
/*!
 *  @brief A function.
 *
 *  This function is used to assign fpn roialign descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *     Users need handle roialign descriptor, use
 *     cnnlCreateRoialignDescriptor() to create descriptor and use
 *     cnnlSetRoialignDescriptor() to set its parameters.
 *
 *  @param[in]  desc
 *    Input. Description of roialign operation.
 *  @param[in]  num_level
 *    Input. The number of feature maps.
 *  @param[in]  pooled_height
 *    Input. The height of output feature map.
 *  @param[in]  pooled_width
 *    Input. The width of output feature map.
 *  @param[in]  sampling_ratio
 *    Input. The sample ratio of every bin.
 *  @param[in]  canonical_scale
 *    Input. The scale param to compute which feature does the current roi belong to.
 *  @param[in]  canonical_leval
 *    Input. The level param to compute which feature does the current roi belong to.
 *  @param[in]  img_h
 *    Input. The height of input image.
 *  @param[in]  img_w
 *    Input. The width of input image.
 *  @param[in]  pool_mode
 *    Input. The mode of pooling, now we only support
 *           CNNL_POOLING_AVERAGE_COUNT_EXCLUDE_PADDING.
 *  @param[in]  roi_type
 *    Input. The mode selection for regions of interest, now we only support
 *           CNNL_ROI_CORNER.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetRoialignDescriptor(cnnlRoialignDescriptor_t desc,
                          const int num_level,
                          const int pooled_height,
                          const int pooled_width,
                          const int sampling_ratio,
                          const int canonical_scale,
                          const int canonical_level,
                          const int img_h,
                          const int img_w,
                          const cnnlPoolingMode_t pool_mode,
                          const cnnlRoiLayoutType_t rois_type);

// Group:Roialign
/*!
 *  @brief A function.
 *
 *  This function is used to assign roialign descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *     Users need handle roialign descriptor, use
 *     cnnlCreateRoialignDescriptor() to create descriptor and use
 *     cnnlSetRoialignDescriptorV2() to set its parameters.
 *
 *  @param[in]  desc
 *    Input. Description of roialign operation.
 *  @param[in]  sampling_ratio
 *    Input. The sample ratio of every bin.
 *  @param[in]  spatial_scale
 *    Input. The spatial scale for roi.
 *  @param[in]  pool_mode
 *    Input. The mode of pooling, now we only support
 *    CNNL_POOLING_AVERAGE_COUNT_EXCLUDE_PADDING.
 *  @param[in]  roi_type
 *    Input. The mode selection for regions of interest, now we only support
 *    CNNL_ROI_CORNER_SCORE or CNNL_ROI_SCORE_CORNER.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetRoialignDescriptorV2(cnnlRoialignDescriptor_t desc,
                            const int sampling_ratio,
                            const float spatial_scale,
                            const cnnlPoolingMode_t pool_mode,
                            const cnnlRoiLayoutType_t rois_type);

// Group:Roialign
/*!
 *  @brief A function.
 *
 *  This function is used to assign multi-level roialign descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  Before calling this function, users need to use cnnlCreateRoialignDescriptor()
 *  to create the descriptor.
 *
 *  @param[in]  desc
 *    Input. Descriptor of roialign operation.
 *  @param[in]  num_level
 *    Input. The number of feature maps. It is must be between 1 and 10.
 *  @param[in]  sampling_ratio
 *    Input. The sample ratio of every bin.
 *  @param[in]  finest_scale
 *    Input. The scale parameter to compute which feature does the current roi
 *    belong to. It must be greater than 0.
 *  @param[in]  roi_scale_factor
 *    Input. The scaling factor of the roi on the feature map. It must be greater
 *    than or equal to 0 .
 *  @param[in]  aligned
 *    Input. A boolean value indicates whether to subtract 0.5 when calculating
 *    the roi coordinates.
 *  @param[in]  pool_mode
 *    Input. The mode of pooling. Currently only
 *    ::CNNL_POOLING_AVERAGE_COUNT_EXCLUDE_PADDING is supported.
 *  @param[in]  roi_type
 *    Input. The mode selection for regions of interest. Currently only
 *    ::CNNL_ROI_BATCHID_CORNER is supported.
 *  @param[in]  compute_dtype
 *    Input. The data type used in computing bilinear interpolatation.
 *  @param[in]  featmap_strides[]
 *    Input. An array of stride parameter to calculate spatial_scale for every
 *    level feature map.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetMultiLevelRoialignDescriptor(cnnlRoialignDescriptor_t desc,
                                    const int num_level,
                                    const int sampling_ratio,
                                    const int finest_scale,
                                    const float roi_scale_factor,
                                    const bool aligned,
                                    const cnnlPoolingMode_t pool_mode,
                                    const cnnlRoiLayoutType_t rois_type,
                                    const cnnlDataType_t compute_dtype,
                                    float featmap_strides[]);

// Group:Roialign
/*!
 *  @brief A function.
 *  This function is used to get extra space size that needed in roialign operation.
 *
 *  @param[in]  handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           roialign operation.
 *  @param[in]  input_desc
 *    Input. Pointer to the host memory that stores an array of tensor descriptors which holds dimension,
 *           datatype, and layout of different level feature map tensor. The shape of tensor must be
 *           [batch_size, level_h, level_w, channels].
 *  @param[in]  output_desc
 *    Input. Pointer to the host memory that stores a tensor descriptor which holds dimension,
 *           datatype, and layout of output tensor. The shape of tensor must be [total_rois_num,
 *           pooled_height, pooled_width, cahnnels].
 *  @param[out] size
 *    Output. Size of workspace.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of input_desc or output_desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlGetRoialignWorkspaceSize(cnnlHandle_t handle,
                             const cnnlTensorDescriptor_t input_desc[],
                             const cnnlTensorDescriptor_t output_desc,
                             size_t *size);

/******************************************************************************
* Cambricon CNNL OP: TransformerFcTopk
******************************************************************************/
//! @brief An enum.
/*! Enumeration variables describe the fctopk mode. */
typedef enum {
  CNNL_TRANSFORMER_BEAM_TOPK_SOFTMAX = 0,
  /*!< Performs softmax before performing beam topk.*/

  CNNL_TRANSFORMER_SOFTMAX_BEAM_TOPK = 1,
  /*!< Performs softmax after performing beam topk.*/

  CNNL_TRANSFORMER_BATCH_TOPK_SOFTMAX = 2,
  /*!< Performs softmax before performing batch topk.*/

  CNNL_TRANSFORMER_SOFTMAX_BATCH_TOPK = 3,
  /*!< Performs softmax after performing batch topk.*/
} cnnlTransformerFcTopkMode_t;

//! @brief An enum.
/*! Enumeration variables describe the softmax mode.*/
typedef enum {
  CNNL_TRANSFORMER_SOFTMAX = 0,
  /*!< Performs softmax operation.*/

  CNNL_TRANSFORMER_LOG_SOFTMAX = 1,
  /*!< Performs log softmax operation. */
} cnnlTransformerSoftmaxMode_t;


/*! The descriptor of fctopk operator that holds four beam_size,
 *  hidden_size, dict_len, k layernorm and fc_type.
 *
 *  You need to call the cnnlCreateTransformerFcTopkDescriptor function
 *  to create a descriptor, and call the cnnlSetTransformerFcTopkDescriptor
 *  function to set the tensor information to the descriptor.
 *  Also, you need to destroy the fctopk descriptor at the end with the
 *  cnnlDestroyTransformerFcTopkDescriptor function*/
typedef struct cnnlTransformerFcTopkStruct *cnnlTransformerFcTopkDescriptor_t;

// Group:Transformer Fc Topk
/* transformer fc-topk of encoder operation start */
/*!
 *  @brief A function.
 *
 *  The fc-topk layer in transformer decoder network,
 *  realize fully connected and topk function.
 *
 *  **Formula**
 *
 *  This operation contains three steps:
 *
 *  1. Generate fc_out
 *
 *    Compute fc_out from input tensor.
 *
 *    fc_out = mlp(input_tensor, attr_kernel)
 *
 *  2. Generate topk
 *
 *    Compute topk from fc_out.
 *
 *    output_value = topk(fc_out)
 *
 *    output_index = topk_index(fc_out)
 *
 *  3. Softmax for output_value
 *
 *    output_value = softmax(output_value)
 *
 *  **DataType**
 *
 *    MLU270:
 *
 *    - input: float, half.
 *
 *    - filter: int16.
 *
 *    - output: float(topk_value), float(topk_index).
 *
 *    MLU370:
 *
 *    - input: half, float.
 *
 *    - filter: half, float.
 *
 *    - output: float(topk_value), float(topk_index).
 *
 *  **Attention: **
 *
 *    - DataType of input, layernorm_bias must be the same.
 *
 *    - DataType of fc_type, bias and accumulated_logits must be the same.
 *
 *    - Input and output cannot be homologous operand.
 *
 *    - The content of input is not modified by fc-topk layer.
 *
 *    - MLU270 the type of filter is recommended to be int16.
 *      If the type of filter is int8, the precision of output
 *      is not guaranteed.
 *
 *    - MLU370 the type of input must be same as the type of filter.
 *
 *  **Data Layout**
 *
 *    The supported data layout of the input tensor, filter tensor, bias tensor,
 *    layernorm tensor and output tensor must CNNL_LAYOUT_ARRAY.
 *
 *  **Scale Limitation**
 *
 *    According to the definition of transformer decoder fc-topk, the
 *    parameters should satisfy the following conditions:
 *
 *    MLU270:
 *
 *    - Batch_size is not limited as long as memory is large enough,
 *      beam_size must be in the range [2, 12], k must be in the range [2, 12],
 *      hidden_size must be 512 or 1024, dict_len must be in the range [3072, 90000].
 *
 *    MLU370(filters_type: half) and when fctopk mode is CNNL_TRANSFORMER_SOFTMAX_BATCH_TOPK:
 *
 *    - Batch_size must be in the range [1, 128], beam_size must be in the range [1, 16],
 *      k must be in the range [2, 16], hidden_size must be 512 or 768 or 1024 and
 *      dict_len must be in the range [256, 90000].

 *    MLU370(filters_type: half) and when fctopk mode is CNNL_TRANSFORMER_BEAM_TOPK_SOFTMAX:
 *
 *    - Batch_size must be in the range [1, 64], beam_size must be in the range [1, 12],
 *      k must be in the range [2, 12], hidden_size must be 512 or 768 or 1024 and
 *      dict_len must be in the range [256, 90000].
 *
 *    MLU370(filters_type: float) and when fctopk mode is CNNL_TRANSFORMER_SOFTMAX_BATCH_TOPK:
 *
 *    - Batch_size must be in the range [1, 128], beam_size must be in the range [1, 16],
 *      k must be in the range [2, 16], hidden_size must be 512 or 768 or 1024 and
 *      dict_len must be in the range [256, 90000].
 *
 *    MLU370(filters_type: float) and when fctopk mode is CNNL_TRANSFORMER_BEAM_TOPK_SOFTMAX:
 *
 *    - Batch_size * beam_size must be in the range [1, 32],
 *      k must be in the range [2, 12], hidden_size must be less than 1536 and
 *      hidden_size % 128 = 0 and dict_len must be in the range [64, 18000].
 *
 *  **Performance Optimization**
 *
 *    When batch_size multiplies beam_size less than 64, the performance is the best.
 *
 *  **Example**
 *
 *    input: a tensor of [batch_size, beam_size, hidden_size]
 *
 *    filter: a tensor of [dict_len, hidden_size]
 *
 *    layernorm_scale: a tensor of [hidden_size]
 *
 *    layernorm_bias: a tensor of [hidden_size]
 *
 *    Then we will get the output:
 *
 *    output_value: a tensor of [batch_size, beam_size, k]
 *
 *    output_index: a tensor of [batch_size, beam_size, k]
 *
 *  **Reference**
 *
 *    http://github.com/master/FasterTransformer
 *
 *  **API Dependency**
 *
 *    You need to call the cnnlCreateTransformerFcTopkDescriptor() to
 *    create descriptor and use cnnlSetTransformerFcTopkDescriptor()
 *    to set its parameters before calling this function.
 *
 *    You need to call the cnnlDestroyTransformerFcTopkDescriptor()
 *    function after calling this function.
 *
 *  @param[in]  handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           transformer_fc_topk operation.
 *  @param[in]  desc
 *    Input. A struct with parameters of transformer fc_topk layer.
 *  @param[in]  input_desc
 *    Input. Descriptor of input, containing data type, dimensions, layout and
 *    quantization information, support multiple dimensions and
 *    the lowest three dimensions is valid.
 *  @param[in]  input
 *    Input. Device pointer points to input space.
 *  @param[in]  filter_desc
 *    Input. Descriptor of filter, containing data type, dimensions, layout
 *    and quantization information, support multiple dimensions and
 *    the lowest two dimensions is valid.
 *  @param[in]  filter
 *    Input. Device pointer points to filter space.
 *  @param[in]  desc_bias
 *    Input. Descriptor of bias, containing data type, dimensions and layout.
 *  @param[in]  bias
 *    Input. Device pointer points to bias space.
 *  @param[in]  accumulated_logits_desc
 *    Input. Descriptor of accumulated_logits vector, containing dimension
 *    of [batch_size, beam_size], used for point accumulation.
 *  @param[in]  accumulated_logits
 *    Input. Device pointer points to accumulated_logits space.
 *  @param[in]  desc_norm_scale
 *    Input. Descriptor of norm_scale vector, containing dimension of [hidden_size],
 *    used for layernorm scale.
 *  @param[in]  norm_scale
 *    Input. Device pointer points to nrom_scale space, dimensions depending on
 *    output dimensions.
 *  @param[in]  desc_norm_bias
 *    Input. Descriptor of norm_bias vector, containing dimension of [hidden_size],
 *    used for layernorm bias.
 *  @param[in]  norm_bias
 *    Input. Device pointer points to nrom_bias space, dimensions depending on
 *    output dimensions.
 *  @param[in]  workspace
 *    Input. The pointer to data address of workspace, which is extra alloced by users
 *    for store fullyconnected data.
 *  @param[in]  workspace_size
 *    Input. The value of workspace_size(bytes).
 *  @param[in] output_value_desc
 *    Input. Descriptor of output_value, containing data type, dimensions and layout,
 *    support multiple dimensions and the lowest three dimensions is valid.
 *  @param[out] output_value
 *    Input. Device pointer points to output space, dimensions depending on
 *    output dimensions.
 *  @param[in] output_index_desc
 *    Input. Descriptor of output_index, containing data type, dimensions and layout,
 *    support multiple dimensions and the lowest three dimensions is valid.
 *  @param[out] output_index
 *    Input. Device pointer points to output space, dimensions depending on
 *    output dimensions.
 *  @retval CNNL_STATUS_SUCCESS = 0
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM = 3
 *    One or more of the following conditions are encountered:
 *    - handle is NULL.
 *    - pointer is NULL.
 *    - parameters do not meet scale limitation.
 *  @retval CNNL_STATUS_ARCH_MISMATCH
 *    One or more of the following conditions are encountered:
 *    - This function is run on the hardware platform that is not supported.
 */

cnnlStatus_t CNNL_WIN_API cnnlTransformerFcTopk(cnnlHandle_t handle,
                                     const cnnlTransformerFcTopkDescriptor_t desc,
                                     const cnnlTensorDescriptor_t input_desc,
                                     const void *input,
                                     const cnnlTensorDescriptor_t filter_desc,
                                     const void *filter,
                                     const cnnlTensorDescriptor_t bias_desc,
                                     const void *bias,
                                     const cnnlTensorDescriptor_t accumulated_logits_desc,
                                     const void *accumulated_logits,
                                     const cnnlTensorDescriptor_t desc_norm_scale,
                                     const void *norm_scale,
                                     const cnnlTensorDescriptor_t desc_norm_bias,
                                     const void *norm_bias,
                                     void *workspace,
                                     size_t workspace_size,
                                     const cnnlTensorDescriptor_t output_value_desc,
                                     void *output_value,
                                     const cnnlTensorDescriptor_t output_index_desc,
                                     void *output_index);

// Group:Transformer Fc Topk
/*!
 *  @brief A function.
 *
 *  This function is used to create a descriptor of TransformerFcTopk
 *  and allocate memory for it.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *  After calling this function, you can call the cnnlSetTransformerFcTopkDescriptor
 *  function to initialize and set the information to the fctopk descriptor.
 *  You need to call the cnnlDestroyTransformerFcTopkDescriptor function
 *  to destroy the descriptor.
 *
 *  @param[out]  desc
 *    Input. Description of TransformerFcTopk operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_ALLOC_FAILED
 *    The function allocate memory space failed.
 */
cnnlStatus_t CNNL_WIN_API
cnnlCreateTransformerFcTopkDescriptor(cnnlTransformerFcTopkDescriptor_t *desc);

// Group:Transformer Fc Topk
/*!
 *  @brief A function.
 *
 *  This function is used to destroy a descriptor of TransformerFcTopk
 *  and free memory for it.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *  You need to call this function after calling the cnnlTransformerFcTopk function.
 *
 *  @param[in]  desc
 *    Input. Description of TransformerFcTopk operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlDestroyTransformerFcTopkDescriptor(cnnlTransformerFcTopkDescriptor_t desc);

// Group:Transformer Fc Topk
/*!
 *  @brief A function.
 *
 *  This function is used to assign TransformerFcTopk descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *  Users need handle transformer descriptor, use
 *  cnnlCreateTransformerFcTopkDescriptor() to create descriptor
 *  and use cnnlSetTransformerFcTopkDescriptor() to set its parameters.
 *
 *  @param[out] desc
 *    Output. Description of TransformerFcTopk operation.
 *  @param[in]  layernorm
 *    Input. Bool type indicates whether to enable normalization of input.
 *  @param[in]  input_online_quantify
 *    Input. Bool type indicates whether to enable quantize of input.
 *  @param[in]  fc_type
 *    Input. Descriptor fullyconnected output data type(half, float).
 *  @param[in]  fctopk_mode
 *    Input. Descriptor fctopk mode, containing CNNL_TRANSFORMER_BEAM_TOPK_SOFTMAX
 *    or CNNL_TRANSFORMER_SOFTMAX_BATCH_TOPK.
 *  @param[in]  softmax_mode
 *    Input. Descriptor softmax mode, containing CNNL_TRANSFORMER_SOFTMAX
 *    or CNNL_TRANSFORMER_LOG_SOFTMAX.
 *  @retval CNNL_STATUS_SUCCESS
 *    The object was set successfully.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetTransformerFcTopkDescriptor(
        const cnnlTransformerFcTopkDescriptor_t desc,
        const bool layernorm,
        const bool input_online_quantify,
        cnnlDataType_t fc_type,
        cnnlTransformerFcTopkMode_t fctopk_mode,
        cnnlTransformerSoftmaxMode_t softmax_mode);

// Group:Transformer Fc Topk
/*!
 *  @brief A function.
 *  This function is used to get extra space size that needed in transformer
 *  fc_topk operation.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *  Use cnnlCreateTransformerFcTopkDescriptor() to create descriptor
 *  and use cnnlSetTransformerFcTopkDescriptor() to set its parameters.
 *
 *  @param[in]  desc
 *    Input.  Parameter description of transformer_fc_topk.
 *  @param[in]  input_desc
 *    Input. Descriptor of input, containing dimension and the layout of input.
 *  @param[out] size
 *    Output. Size of workspace.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc or size is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlGetTransformerFcTopkWorkspaceSize(const cnnlTransformerFcTopkDescriptor_t desc,
                                      const cnnlTensorDescriptor_t input_desc,
                                      const cnnlTensorDescriptor_t filter_desc,
                                      size_t *size);

/******************************************************************************
 * Cambricon CNNL OP: TransformerBeamSearch
 ******************************************************************************/

/*! Descriptor of TransformerBeamSearch.
 * Use cnnlCreateTransformerBeamSearchDescriptor(), cnnlSetTransformerBeamSearchDescriptor(),
 * cnnlSetTransformerBeamSearchDescriptorV2(), cnnlDestroyTransformerBeamSearchDescriptor()
 * to create, set, and destroy the descriptor.
 */
typedef struct cnnlTransformerBeamSearchStruct *cnnlTransformerBeamSearchDescriptor_t;

// Group:Transformer Beam Search
/*!
 *  @brief Creates a descriptor of TransformerBeamSearch and allocates host memory for it.
 *
 *  @param[out]  desc
 *    Output. Description of TransformerBeamSearch operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_ALLOC_FAILED
 *    The function failed to allocate memory.
 */
cnnlStatus_t CNNL_WIN_API
cnnlCreateTransformerBeamSearchDescriptor(cnnlTransformerBeamSearchDescriptor_t *desc);

// Group:Transformer Beam Search
/*!
 *  @brief Destroys a descriptor of TransformerBeamSearch and frees memory for it.
 *
 *  @param[in]  desc
 *    Input. Description of TransformerBeamSearch operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    \b desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlDestroyTransformerBeamSearchDescriptor(cnnlTransformerBeamSearchDescriptor_t desc);

// Group:Transformer Beam Search
/*!
 *  @brief Sets a TransformerBeamSearch descriptor with values.
 *    To set topk mode and softmax mode, call cnnlSetTransformerBeamSearchDescriptorV2.
 *
 *  @param[out]  desc
 *    Output. Description of TransformerBeamSearch operation.
 *  @param[in]  k
 *    Input. A factor of FC-Topk operation. For each batch, FC-Topk outputs \b k * beam
 *    possible tokens. Currently only supports 2.
 *  @param[in]  alpha
 *    Input. The constant used to calculate length_normalization.
 *  @param[in]  eos_index
 *    Input. Index of EOS token in the embedding vocabulary.
 *  @param[in]  vocab_length
 *    Input. Length of embedding vocabulary.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    The value of one or more parameters are invalid.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetTransformerBeamSearchDescriptor(cnnlTransformerBeamSearchDescriptor_t desc,
                                       int k,
                                       float alpha,
                                       int eos_index,
                                       int vocab_length);

// Group:Transformer Beam Search
/*!
 *  @brief Sets a TransformerBeamSearch descriptor with values.
 *    Compares with cnnlSetTransformerBeamSearchDescriptor, this function allows user to specify
 *    topk mode and softmax mode explicitly.
 *
 *  @param[out]  desc
 *    Output. Description of TransformerBeamSearch operation.
 *  @param[in]  k
 *    Input. A factor of FC-Topk operation. For each batch, FC-Topk outputs \b k * beam
 *    possible tokens. Currently only supports 2.
 *  @param[in]  alpha
 *    Input. The constant used to calculate length_normalization.
 *  @param[in]  eos_index
 *    Input. Index of EOS token in the embedding vocabulary.
 *  @param[in]  vocab_length
 *    Input. Length of embedding vocabulary.
 *  @param[in]  fctopk_mode
 *    Input. Mode of FcTopk operation for beam search to choose compatible algorithm.
 *  @param[in]  softmax_mode
 *    Input. Softmax mode of FcTopk operation for beam search to choose compatible algorithm.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    The value of one or more parameters are invalid.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetTransformerBeamSearchDescriptorV2(cnnlTransformerBeamSearchDescriptor_t desc,
                                         int k,
                                         float alpha,
                                         int eos_index,
                                         int vocab_length,
                                         cnnlTransformerFcTopkMode_t fctopk_mode,
                                         cnnlTransformerSoftmaxMode_t softmax_mode);

// Group:Transformer Beam Search
/*!
 *  @brief Performs beam search logic based on greedy algorithm.
 *
 *  @param[in]  handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           operation.
 *  @param[in]  desc
 *    Input. Description of TransformerBeamSearch operation.
 *  @param[in]  topk_indices_desc
 *    Input. Descriptor of \b topk_indices_seq. Shape must be [batch, k * beam] or [batch, beam, k].
 *           Data type must be float.
 *  @param[in]  topk_indices_seq
 *    Input. Device pointer points to topk_indices_seq tensor space, holding indices of the
 *           top-(k*beam) possible tokens.
 *  @param[in]  topk_log_probs_desc
 *    Input. Descriptor of \b topk_log_probs_seq. Shape must be [batch, k * beam] or
 *           [batch, beam, k]. Data type must be float.
 *  @param[in]  topk_log_probs_seq
 *    Input. Device pointer points to topk_log_probs_seq tensor space, holding probabilities of the
 *           top-(k*beam) possible tokens.
 *  @param[in]  nframe_desc
 *    Input. Descriptor of \b nframe. Shape must be [1]. Data type must be int32.
 *  @param[in,out]  nframe
 *    Input and Output. Device pointer points to nframe tensor space, holding index of current frame.
 *           Its value will be incremented by 1 during beam search.
 *  @param[in]  state_alive_seq_desc
 *    Input. Descriptor of \b state_alive_seq. Shape must be [batch, beam, max_decode_len + 1].
 *           Data type must be int32.
 *  @param[in,out]  state_alive_seq
 *    Input and Output. Device pointer points to state_alive_seq tensor space,
 *           holding possible token sequences.
 *  @param[in]  state_alive_log_probs_desc
 *    Input. Descriptor of \b state_alive_log_probs. Shape must be [batch, beam].
 *           Data type must be float.
 *  @param[in,out]  state_alive_log_probs
 *    Input and Output. Device pointer points to state_alive_log_probs tensor space,
 *           holding probabilities of corresponding sequences of \b state_alive_seq.
 *  @param[in]  state_finished_seq_desc
 *    Input. Descriptor of \b state_finished_seq. Shape must be [batch, beam, max_decode_len + 1].
 *           Data type must be int32.
 *  @param[in,out]  state_finished_seq
 *    Input and Output. Device pointer points to state_finished_seq tensor space,
 *           holding possible token sequences.
 *  @param[in]  state_finished_scores_desc
 *    Input. Descriptor of \b state_finished_scores. Shape must be [batch, beam].
 *           Data type must be float.
 *  @param[in,out]  state_finished_scores
 *    Input and Output. Device pointer points to state_finished_scores tensor space,
 *           holding probabilities of corresponding sequences of \b state_finished_seq.
 *  @param[in]  state_finished_flags_desc
 *    Input. Descriptor of \b state_finished_flags. Shape must be [batch, beam].
 *           Data type must be bool.
 *  @param[in,out]  state_finished_flags
 *    Input and Output. Device pointer points to state_finished_flags tensor space.
 *           Each element determines whether corresponding sequence of \b state_finished_seq has
 *           finished or not.
 *  @param[in]  output_topk_indicies_alive_desc
 *    Input. Descriptor of \b state_finished_flags. Shape must be [batch, beam].
 *           Data type must be int8.
 *  @param[out]  output_topk_indicies_alive
 *    Output. Device pointer points to state_finished_flags tensor space.
 *           Each element determines which beam is the corresponding sequence of
 *           \b state_finished_seq forked from. It will be used in beam rearrange operation.
 *  @param[in]  latest_token_alive_desc
 *    Input. Descriptor of \b latest_token_alive. Shape must be [batch, beam].
 *           Data type must be int32. This parameter is optional.
 *  @param[out]  latest_token_alive
 *    Output. Device pointer points to latest_token_alive tensor space.
 *           These tokens will be embedded in the next decoding frame. This parameter is optional.
 *  @param[in]  continue_search_desc
 *    Input. Descriptor of \b continue_search. Shape must be [batch].
 *           Data type must be bool. This parameter is optional.
 *  @param[out]  continue_search
 *    Output. Device pointer points to continue_search tensor space.
 *           Each element determines whether this batch should continue decoding or not.
 *           This parameter is optional.
 *  @par Return
 *  - CNNL_STATUS_SUCCESS, CNNL_STATUS_BAD_PARAM
 *
 *  @par Reference
 *  - https://github.com/tensorflow/models/blob/r1.13.0/official/transformer/model/beam_search.py
 *
 *  @par Note
 *  - This operation supports batch-topk mode and beam-topk mode.
 *    If \b op_desc is set by cnnlSetTransformerBeamSearchDescriptorV2 function, the topk mode is
 *    determined by the \b fctopk_mode parameter. Otherwise, it is determined by the dimensions of
 *    \b topk_indices_seq and \b topk_log_probs_seq.
 *    - If the dimension of \b topk_indices_seq and \b topk_log_probs_seq is 2, the batch-topk mode is used.
 *    - If the dimension of \b topk_indices_seq and \b topk_log_probs_seq is 3, the beam-topk mode is used.
 *  - Batch-topk mode or beam-topk mode must be consistent with topk mode of the FcTopk operation.
 *
 *  @par Data Type
 *  - \b state_alive_seq, \b state_finished_seq, \b nframe, \b latest_token_alive: INT32.
 *  - \b topk_indices_seq, \b topk_log_probs_seq: FLOAT.
 *  - \b state_alive_log_probs, \b state_finished_scores: FLOAT or HALF.
 *  - \b state_finished_flags, \b continue_search: BOOL.
 *  - \b output_topk_indicies_alive: INT8.
 *
 *  @par Scale Limitation
 *  - The dimensions of tensors must meet following requirements:
 *    - 1 <= batch_size.
 *    - 1 <= beam_size <= 16.
 *    - 1 <= max_decode_len <= 1024.
 *    - k == 2
 *    - Shapes of \b topk_indices_seq and \b topk_log_probs_seq must be the same.
 *    - In batch-topk mode, values of \b topk_indices_seq must be in [0, beam_size * vocab_length).
 *    - In beam-topk mode, values of \b topk_indices_seq must be in [0, vocab_length).
 *
 *  @par Requirements
 *  - None.
 *
 *  @par Example
 *  - None.
 */
cnnlStatus_t CNNL_WIN_API
cnnlTransformerBeamSearch(cnnlHandle_t handle,
                          cnnlTransformerBeamSearchDescriptor_t op_desc,
                          cnnlTensorDescriptor_t topk_indices_desc,
                          const void *topk_indices_seq,
                          cnnlTensorDescriptor_t topk_log_probs_desc,
                          const void *topk_log_probs_seq,
                          cnnlTensorDescriptor_t nframe_desc,
                          void *nframe,
                          cnnlTensorDescriptor_t state_alive_seq_desc,
                          void *state_alive_seq,
                          cnnlTensorDescriptor_t state_alive_log_probs_desc,
                          void *state_alive_log_probs,
                          cnnlTensorDescriptor_t state_finished_seq_desc,
                          void *state_finished_seq,
                          cnnlTensorDescriptor_t state_finished_scores_desc,
                          void *state_finished_scores,
                          cnnlTensorDescriptor_t state_finished_flags_desc,
                          void *state_finished_flags,
                          cnnlTensorDescriptor_t output_topk_indicies_alive_desc,
                          void *output_topk_indicies_alive,
                          cnnlTensorDescriptor_t latest_token_alive_desc,
                          void *latest_token_alive,
                          cnnlTensorDescriptor_t continue_search_desc,
                          void *continue_search);

/******************************************************************************
 * Cambricon CNNL OP: Transformer Embedding
 ******************************************************************************/
/*!
 * @brief An enum.
 *
 * Enumeration variables describing whether to add embedding for token_ids.
 *
 */
typedef enum {
    CNNL_EMBEDDING_TOKEN_UNUSED = 0,   /*!<The embedding for token_ids is not added.*/
    CNNL_EMBEDDING_TOKEN_USED = 1,     /*!<The embedding for token_ids is added.*/
} cnnlTransformerEmbeddingTokenMode_t;

/*!
 * @brief An enum.
 *
 * Enumeration variables describing whether to add the information of position dictionary to
 * the output after embedding operation. And enumeration variables describing the modes that
 * are used in the implementation of the position embedding operation.
 *
 */
typedef enum {
    CNNL_EMBEDDING_ENCODING_UNUSED = 0,  /*!<The position encoding dictionary is not used.*/
    CNNL_EMBEDDING_POSITION_CACHED = 1,      /*!<Decoder cache mode, get current token encoding.*/
    CNNL_EMBEDDING_POSITION_UNCACHED = 2,    /*!<Encoder or decoder uncached mode.*/
} cnnlTransformerEmbeddingEncodingMode_t;

// Group:Transformer Embedding
/*!
 * @brief Adds the result of embedding and position encoding to \b output.
 *
 * **Formula**
 *
 * This operation do following steps:
 *
 * mask = indices != 0
 *
 * output = filter[indices, :]
 *
 * If CNNL_EMBEDDING_ENCODING_UNUSED is set : output *= mask
 *
 * output *= alpha
 *
 * if CNNL_EMBEDDING_POSITION_UNCACHED is set: output += position
 *
 * else : output = output;
 *
 * @param[in] handle
 *   Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *   position embedding operation.
 * @param[in] filter_desc
 *   Input. The descriptor of the filter tensor to store the information of vocab dictionary.
 * @param[in] filter
 *   Input. A Pointer to the MLU memory that stores the filter tensor. Shape should be
 *   [vocab_size, embedding_size].
 * @param[in] indices_desc
 *   Input. The descriptor of the index tensor used to store the index of \b convolution \b filter which
 *   corresponds to each row of \b output. The number of indices dimensions should be 2.
 *   The most common shape is [batch_size, seq_len].
 * @param[in] indices
 *   Input. A pointer to the MLU memory that stores the index of \b convolution \b filter.
 * @param[in] position_desc
 *   Input. The descriptor of the position encoding tensor.
 * @param[in] position
 *   Input. A Pointer to the MLU memory that stores the information of position encoding.
 *   Shape should be [position_size, embedding_size].
 * @param[in] length_desc
 *   Input. The descriptor of the seq_len to express offset and acquire the information of
 *   position encoding in cached mode.
 * @param[in] length
 *   Input. A Pointer to the MLU memory that stores the offset. Shape should be 1.
 * @param[in] token_dic_desc
 *   Input. The descriptor of the token_dic tensor to store the information of token dictionary.
 * @param[in] token_dic
 *   Input. A Pointer to the MLU memory that stores the token tensor. Shape should be
 *   [token_dic_size, embedding_size].
 * @param[in] token_ids_desc
 *   Input. The descriptor of the index tensor used to store the index of \b token_dic. The number
 *   of indices dimensions should be 2. The most common shape is [batch_size, seq_len].
 * @param[in] token_ids
 *   Input. A pointer to the MLU memory that stores the index of \b token_dic. Must be
 *   specified if  \p use_token_type is set to 1.
 * @param[in] alpha
 *   Input. A const float scalar used in embedding, usually set to the sqrt of embedding_size.
 * @param[in] use_token_type
 *   Input. A const enum type. Indicates whether to use token embedding. Set to 0 in order
 *   to reserve the interface.
 * @param[in] use_position_encoding
 *   Input. A const enum type. Indicates whether to use position encoding after embedding.
 * @param[in] output_desc
 *   Input. The descriptor of the output tensor to achieve embedding and position encoding.
 *   The number of output dimensions should be 3. The most common shape is
 *   [batch_size, seq_len, embedding_size]. In the CNNL_EMBEDDING_POSITION_CACHED mode
 *   the seq_len must be equal to 1.
 * @param[out] output
 *   Output. A pointer to the MLU memory that stores the output tensor.
 * @retval CNNL_STATUS_SUCCESS
 *   The function ends normally.
 * @retval CNNL_STATUS_ARCH_MISMATCH
 *   One or more of the following conditions are encountered:
 *   - This function is run on the hardware platform that is not supported.
 * @retval CNNL_STATUS_BAD_PARAM
 *   The value of one or more parameters are invalid.
 *
 * @par Data Type
 * - This function supports any combinations of the following data types for index tensor
 *   \b indices, filter tensor \b filter, position tensor \b position, length tensor \b length,
 *   token_dic tensor \b token_dic, token_ids tensor \b token_ids, output tensor \b output
 *   and \b alpha.
 *   <b>Note that the data type of filter tensor, position tensor, token_dic tensor and output
 *   tensor must be the same.</b>
 *   - filter tensor: half, float.
 *   - index tensor: int32.
 *   - position tensor: half, float.
 *   - token_dic tensor: half float.
 *   - token_ids tensor: int32.
 *   - alpha: float.
 *   - output tensor: half, float.
 *
 * @par Data Layout
 * - The supported data layout of the filter tensor, index tensor, position tensor,
 *   token_dic tensor, token_ids and output tensor are as follows:
 *   <b>Note that the data layout of filter tensor, index tensor, position tensor
 *   token_dic tensor, token_ids and output tensor must be same.</b>
 *   - filter tensor: \p CNNL_LAYOUT_ARRAY.
 *   - index tensor: \p CNNL_LAYOUT_ARRAY.
 *   - position tensor: \p CNNL_LAYOUT_ARRAY.
 *   - token_dic tensor: \p CNNL_LAYOUT_ARRAY.
 *   - token_ids tensor: \p CNNL_LAYOUT_ARRAY.
 *   - output tensor: \p CNNL_LAYOUT_ARRAY.
 *
 * @par Scale Limitation
 * - The filter tensor, index tensor, position tensor, length tensor and output tensor must meet
 *   the following requirements:
 *   - filter tensor: the number of filter dimensions must be 2.
 *     The shape of filter tensor is [vocab_size, embedding_size].
 *     When use_position_encoding is not CNNL_EMBEDDING_ENCODING_UNUSED:
 *     If the data type of filter tensor is float, the embedding_size is a multiple of 32.
 *     If the data type of filter tensor is half, the embedding_size is a multiple of 64.
 *   - indices tensor: the number of indices dimensions must be 2.
 *     The shape of indices tensor is [batch_size, seq_len].
 *   - 1 <= batch_size <= 4096.
 *   - 1 <= seq_len <= 4096.
 *   - position tensor: it can be set to a nullptr if use_position_encoding is
 *     CNNL_EMBEDDING_ENCODING_UNUSED. The number of position dimensions must be 2 if
 *     use_position_encoding is CNNL_EMBEDDING_ENCODING_USED and the total element
 *     numbers of position tensor must be less than 8,388,608.
 *   - token_dic tensor: it can be set to a nullptr if use_token_type is
 *     CNNL_EMBEDDING_TOKEN_UNUSED. The number of token_dic dimensions must be 2 if
 *     use_token_type is CNNL_EMBEDDING_TOKEN_USED.
 *   - token_ids tensor: it can be set to a nullptr if use_token_type is
 *     CNNL_EMBEDDING_TOKEN_UNUSED. The number of token_ids dimensions must be 2 if
 *     use_token_type is CNNL_EMBEDDING_TOKEN_USED.
 *   - length tensor: it can be set to a nullptr if use_position_encoding is not
 *     CNNL_EMBEDDING_POSITION_CACHED.
 *   - embedding_size: if use_position_encoding is CNNL_EMBEDDING_ENCODING_UNUSED,
 *     embedding_size <= 2048.
 *   - output tensor: The dimension must be indices dimension plus 1.
 *     The total element numbers of output tensor must be less than (2^31 -1),
 *     that is,
 *   - 1 <= batch_size * seq_len * embedding_size * sizeof(data type) <= (2^31 -1).
 *
 * @note
 * - None.
 *
 * @par Requirements
 * - None.
 *
 * @par Reference
 * - papers.nips.cc/paper/7181-attention-is-all-you-need.pdf
 *
 * @par Example
 * - The example of the embedding operation is as follows:
     @verbatim
     input five arrays by 3 * 3, 2 * 2, 2 * 3, 3 * 3 and 2 * 2, alpha equals to 1.0,
     use_token_type equals to CNNL_EMBEDDING_TOKEN_UNUSED, use_position_encoding equals to
     CNNL_EMBEDDING_POSITION_UNCACHED.

     --> filter: [[0.3472, -0.1983, 0.8744], [0.5356, 1.5739, -0.4864], [-0.6622, -0.4790, 0.8539]]

     --> indices: [[1, 2], [2, 1]]

     --> position: [[0.5578, 0.3548, 0.2574], [0.2546, 0.4695, 0.5784]]

    --> token_dic: [[0.3543, 0.2587, -0.1245], [0.4569, 1.2596, 0.2589], [-0.2333, -0.5467, 0.2356]]

     --> token_ids: [[1, 3], [2, 3]]

     output array by 2 * 2 * 3

     --> output: [[[1.0934,  1.9287, -0.2290], [-0.4076, -0.0095,  1.4323]],
                  [[-0.1044, -0.1242,  1.1113], [0.7902,  2.0434,  0.0920]]]
     @endverbatim
 */
cnnlStatus_t CNNL_WIN_API cnnlTransformerEmbedding(cnnlHandle_t handle,
                                const cnnlTensorDescriptor_t filter_desc,
                                const void *filter,
                                const cnnlTensorDescriptor_t indices_desc,
                                const int *indices,
                                const cnnlTensorDescriptor_t position_desc,
                                const void *position,
                                const cnnlTensorDescriptor_t length_desc,
                                const int *length,
                                const cnnlTensorDescriptor_t token_dic_desc,
                                const void *token_dic,
                                const cnnlTensorDescriptor_t token_ids_desc,
                                const int* token_ids,
                                float alpha,
                                cnnlTransformerEmbeddingTokenMode_t use_token_type,
                                cnnlTransformerEmbeddingEncodingMode_t use_position_encoding,
                                const cnnlTensorDescriptor_t output_desc,
                                void *output);

/******************************************************************************
 * Cambricon CNNL OP: Transformer Position Encoding
 ******************************************************************************/
/*!
 * @brief An enum.
 *
 * Enumeration variables describe the modes that are used in the
 * implementation of the position encoding op.
 *
 */
typedef enum {
    CNNL_POSITION_ENCODING_CACHED,   /*!<Decoder cache mode, get current token encoding.*/
    CNNL_POSITION_ENCODING_UNCACHED, /*!<Encoder or decoder uncached mode,*/
                                     /*!<get all tokens encoding.*/
} cnnlTransformerPositionEncodingMode_t;

/*!
 * @brief An enum.
 *
 * Enumeration variables describe the modes that how to concate
 * two tensors in the position encoding op.
 *
 */
typedef enum {
    CNNL_POSITION_ENCODING_CONTINUOUS, /*!<Concate sin and cos along the last dim.*/
    CNNL_POSITION_ENCODING_DISCRETED,  /*!<Odd in sin and even in cos.*/
} cnnlTransformerPositionEncodingConcateMode_t;

// Group:Transformer Position Encoding
/*!
 * @brief Gets position encoding of transformer and stores into tensor \p output
 * according to input \p length and \p embedding_size.
 *
 * **Formula**
 *
 * This operation do following steps:
 *
 * num_time_scale = embedding_size / 2
 *
 * log_time_scale = -log(max_time_scale / min_time_scale / (num_time_scale - 1))
 *
 * inv_time_scale = min_time_scale * exp(range(num_time_scale) * log_time_scale)
 *
 * scaled_time = matmul(position, inv_time_scale)
 *
 * output = concate([sin(scaled_time), cos(scaled_time)], axis = 1)
 *
 * @param[in] handle
 *   Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the position
 *   encoding operation.
 * @param[in] length
 *   Input. A const int scalar. Indicates the first dim of output.
 * @param[in] embedding_size
 *   Input. A const int scalar. Indicates the second dim of output.
 * @param[in] min_time_scale
 *   Input. A const float scalar. Minimum scale that will be applied at each position. Default as 1.0.
 * @param[in] max_time_scale
 *   Input. A const float scalar. Maximum scale that will be applied at each position. Default as 10000.0.
 * @param[in] position_encoding_mode
 *   Input. A const enum type. Indicates cache or uncached mode.
 * @param[in] concate_mode
 *   Input. A const enum type. Indicates concate mode.
 * @param[in] output_desc
 *   Input. The descriptor of the output tensor. Shape should be [length, embedding_size].
 *   If position_encoding_mode is CNNL_POSITION_ENCODING_CACHED. Shape could be [1, embedding_size]
 *   and only the first row is computed.
 * @param[out] output
 *   Output. A pointer to the MLU memory that stores the output tensor.
 * @retval CNNL_STATUS_SUCCESS
 *   The function ends normally.
 * @retval CNNL_STATUS_ARCH_MISMATCH
 *   One or more of the following conditions are encountered:
 *   - This function is run on the hardware platform that is not supported.
 *
 * @par Data Type
 * - This function supports the following data types for output tensor \b output.
 *   - output tensor: half, float.
 *
 * @par Data Layout
 * - The supported data layout of the output tensor are as follows:
 *   - output tensor: \p CNNL_LAYOUT_NHWC and \p CNNL_LAYOUT_NCHW.
 *
 * @par Scale Limitation
 * - The output tensor must meet the following requirements:
 *   - output tensor: The dimension must be 2. The element number of all dimensions
 *     must be less than \p 1024.
 *   - min_time_scale: The value of min_time_scale must be larger than 0 and no larger than 2.0
 *
 * @note
 * - None.
 *
 * @par Requirements
 * - None.
 *
 * @par Reference
 * - papers.nips.cc/paper/7181-attention-is-all-you-need.pdf
 *
 * @par Example
 * - The example of the position encoding operation is as follows:
     @verbatim
     length equals to 128 and embedding_size equals to 512, position_encoding_mode equals to
     CNNL_POSITION_ENCODING_UNCACHED

     output array by 128 * 512
     @endverbatim
 */
cnnlStatus_t CNNL_WIN_API cnnlTransformerPositionEncoding(
                              cnnlHandle_t handle,
                              int length,
                              int embedding_size,
                              float min_time_scale,
                              float max_time_scale,
                              cnnlTransformerPositionEncodingMode_t position_encoding_mode,
                              cnnlTransformerPositionEncodingConcateMode_t concate_mode,
                              const cnnlTensorDescriptor_t output_desc,
                              void *output);

/******************************************************************************
 * Cambricon CNNL OP: ContinuationIndicator.
 ******************************************************************************/
// Group:Continuation Indicator
/*!
 *  @brief A function.
 *
 *  This function is used to generate continuous 0 and 1. The first batch data is 0,
 *  the rest batch data is 1.
 *
 *  **Reference:**
 *
 *    This implementation is based on the project on https://github/xmfbit/warpctc-caffe.
 *
 *  **Formula:**
    @verbatim
    This op contains one step:

    Set the value of the output:

    for (int t = 0; t < time_step; t++) {

      for (int b = 0; b < batch_size; b++) {

        output[t * batch_size + b] = t == 0 ? 0 : 1;

      }

    }
	@endverbatim
 *
 *  **DataType:**
 *
 *    Supports half(float16) and float32.
 *
 *  **Supports MLU220, MLU270, MLU290, MLU370, MLU365, CE3226.**
 *
 *  **Scale Limitation**
 *
 *   According to continuation_indicator operation, the parameters must be satisfied to the
 *   following conditions:
 *
 *   - time_step(output_data_desc->dims[0]) >= 0.
 *
 *   - 0 <= batch_size(output_data_desc->dims[1]).
 *
 *   - time_step(output_data_desc->dims[0]) * batch_size(output_data_desc->dims[1]) <= INT32_MAX.
 *
 *  @param[in] handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and
 *           queues in the continuation_indicator operation.
 *  @param[in] output_data_desc
 *    Input. Descriptor of output tensor, containing dimension of [time_step, batch_size].
 *  @param[out] output_data
 *    Output. A pointer to device output data.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions is met:
 *    - The handle is NULL.
 *    - The output_data_desc is NULL.
 *    - The output_data_desc->dim != 2.
 *    - The output_data is NULL.
 *    - The time_step(output_data_desc->dims[0]) is smaller than 0.
 *    - The batch_size(output_data_desc->dims[1]) < 0.
 *    - The output data type is not equal than CNNL_DTYPE_HALF and CNNL_DTYPE_FLOAT.
 *    - The time_step(output_data_desc->dims[0]) * batch_size(output_data_desc->dims[1]) > INT32_MAX.
 */
cnnlStatus_t CNNL_WIN_API cnnlContinuationIndicator(
    cnnlHandle_t handle,
    const cnnlTensorDescriptor_t output_data_desc,
    void *output_data);

/******************************************************************************
 * Cambricon CNNL OP: Tacotron2Decoder
 ******************************************************************************/
/*! The descriptor of the tacotron2 decoder operation that holds information
 *  including prenet dropout rate and auto stop flag.
 *
 *  You need to call the ::cnnlCreateTacotron2DecoderDescriptor function
 *  to create a descriptor, and call the ::cnnlSetTacotron2DecoderDescriptor
 *  function to set the information of the decoder operation to the descriptor.
 *  Also, you need to destroy the Cambricon CNNL context at the end with the
 *  ::cnnlDestroyTacotron2DecoderDescriptor function.
 */
typedef struct cnnlTacotron2DecoderStruct *cnnlTacotron2DecoderDescriptor_t;

// Group:Tacotron2
/*!
 *  @brief A function.
 *
 *  This function is used to create a descriptor of tacotron2 decoder and malloc
 *  memory for it.
 *
 *  @param[in]  desc
 *    Input. Descritpor of tacotron2 decoder operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_ALLOC_FAILED
 *    The function failed to malloc memory space.
 */
cnnlStatus_t CNNL_WIN_API
cnnlCreateTacotron2DecoderDescriptor(cnnlTacotron2DecoderDescriptor_t *desc);

// Group:Tacotron2
/*!
 *  @brief A function.
 *
 *  This function is used to destroy a descriptor of tacotron2 decoder and free
 * memory for it.
 *
 *  @param[in]  desc
 *    Input. Descritpor of tacotron2 decoder operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlDestroyTacotron2DecoderDescriptor(cnnlTacotron2DecoderDescriptor_t desc);

// Group:Tacotron2
/*!
 *  @brief A function.
 *
 *  This function is used to assign tacotron2 decoder descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *     Before using this API, users need to call ::cnnlCreateTacotron2DecoderDescriptor() to create the descriptor.
 *
 *  @param[in]  desc
 *    Input. Descritpor of tacotron2 decoder operation.
 *  @param[in]  prenet_dropout_rate
 *    Input. dropout rate of prenet.
 *  @param[in]  auto_stop
 *    Input. An integer describes whether to enable auto-stop decoding. 1 means enabling auto-stop decoding, while 0 means disabling auto-stop decoding.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetTacotron2DecoderDescriptor(cnnlTacotron2DecoderDescriptor_t desc,
                                  float prenet_dropout_rate,
                                  int auto_stop);

// Group:Tacotron2
/*!
 *  @brief A function.
 *
 *  This function retrieves extra space size required in tacotron2 decoder operation.
 *
 *  @param[in]  handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           tacotron2 decoder operation.
 *  @param[out]  size
 *    Output. Extra space size needed in tacotron2 decoder operation.
 *  @retval CNNL_STATUS_SUCCESS = 0
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM = 3
 *    One or more of the following conditions are met:
 *    - The value of handle is NULL.
 *    - The value of size is NULL.
 */
cnnlStatus_t CNNL_WIN_API cnnlGetTacotron2DecoderWorkspaceSize(cnnlHandle_t handle,
                                                               size_t *size);

// Group:Tacotron2
/*!
 *  @brief A function
 *
 *  This function is used to build the tacotron2 decoder network, which is a decoder
 *  used in speech synthesis to significantly improve the efficiency and quality on speech synthesis.
 *
 *  **DataType**
 *    - input: float, half.
 *    - filter: half.
 *    - bias: float, half.
 *
 * **Scale Limitation**
 *   - The value of batch must be greater than 0.
 *   - The value of sequence_length must be greater than 0.
 *   - The value of max_frame_length must be greater than 0.
 *   - The shape of decoder_input must be [batch, 80].
 *   - The shape of lstm1_hidden must be [batch, 1024].
 *   - The shape of lstm1_cell must be [batch, 1024].
 *   - The shape of lstm2_hidden must be [batch, 1024].
 *   - The shape of lstm2_cell must be [batch, 1024].
 *   - The shape of attention must be [batche, sequence_length].
 *   - The shape of attention_cum must be [batch, sequence_length].
 *   - The shape of attention_context must be [batch, 512].
 *   - The shape of memory must be [batch, sequence_length, 512].
 *   - The shape of processed_memory must be [batch, sequence_length, 128].
 *   - The shape of mask must be [batch, sequence_length].
 *   - The shape of prenet1_filter must be [Co, Ci], where Co = 256 and Ci = 80.
 *   - The shape of prenet1_filter must be [Co, Ci], where Co = 256 and Ci = 256.
 *   - The shape of lstm1_input_filters must be [Co, Ci], where Co = 4096 and Ci = 768.
 *   - The shape of lstm1_hidden_filters must be [Co, Ci], where Co = 4096 and Ci = 1024.
 *   - The shape of lstm1_bias must be [8192].
 *   - The shape of lstm2_input_filters must be [Co, Ci], where Co = 4096 and Ci = 1536.
 *   - The shape of lstm2_hidden_filters must be [Co, Ci], where Co = 4096 and Ci = 1024.
 *   - The shape of lstm2_bias must be [8192].
 *   - The shape of attention_query_filter must be [Co, Ci], where Co = 128 and Ci = 1024.
 *   - The shape of attention_conv_filter must be [Co, T, Ci], where Co = 32, T = 31 and Ci = 2.
 *   - The shape of attention_full_filter must be [Co, Ci], where Co = 128 and Ci = 32.
 *   - The shape of attention_out_filter must be [Co, Ci], where Co = 1 and Ci = 128.
 *   - The shape of prj_mel_filter must be [Co, Ci], where Co = 80 and Ci = 1536.
 *   - The shape of prj_mel_bias must be [80].
 *   - The shape of prj_gate_filter must be [Co, Ci], where Co = 1 and Ci = 1536.
 *   - The shape of prj_gate_bias must be [1].
 *   - The shape of output_mel must be [max_frame_length, batch, 80].
 *   - The shape of output_lengths must be [batch, 1].
 *
 *  @param[in] handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the tacotron2
 *           decoder operations.
 *  @param[in] desc
 *    Input. The Descritpor of tacotron2 decoder operation.
 *  @param[in] decoder_input_desc
 *    Input.  Descriptor of the decoder input tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [batch, 80], and data type must be float or half.
 *  @param[in] decoder_input
 *    Input. Pointer to the MLU memory that stores the decoder input tensor.
 *  @param[in] lstm1_hidden_desc
 *    Input.  Descriptor of the lstm1 hidden tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [batch, 1024], and data type must be float or half.
 *  @param[in] lstm1_hidden
 *    Input. Pointer to the MLU memory that stores the lstm1 hidden tensor.
 *  @param[in] lstm1_cell_desc
 *    Input.  Descriptor of the lstm1 cell tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [batch, 1024], and data type must be float or half.
 *  @param[in] lstm1_cell
 *    Input. Pointer to the MLU memory that stores the lstm1 cell tensor.
 *  @param[in] lstm2_hidden_desc
 *    Input.  Descriptor of the lstm2 hidden tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [batch, 1024], and data type must be float or half.
 *  @param[in] lstm2_hidden
 *    Input. Pointer to the MLU memory that stores the lstm2 hidden tensor.
 *  @param[in] lstm2_cell_desc
 *    Input.  Descriptor of the lstm2 cell tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [batch, 1024], and data type must be float or half.
 *  @param[in] lstm2_cell
 *    Input. Pointer to the MLU memory that stores the lstm2 cell tensor.
 *  @param[in] attention_desc
 *    Input.  Descriptor of the attention tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [batch, sequence_length], and data type must be float or half.
 *  @param[in] attention
 *    Input. Pointer to the MLU memory that stores the attention tensor.
 *  @param[in] attention_cum_desc
 *    Input.  Descriptor of the attention accumulation tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [batch, sequence_length], and data type must be float or half.
 *  @param[in] attention_cum
 *    Input. Pointer to the MLU memory that stores the attention accumulation tensor.
 *  @param[in] attention_context_desc
 *    Input.  Descriptor of the attention context tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [batch, 512], and data type must be float or half.
 *  @param[in] attention_context
 *    Input. Pointer to the MLU memory that stores the attention context tensor.
 *  @param[in] memory_desc
 *    Input.  Descriptor of the memory tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [batch, sequence_length, 512], and data type must be float or half.
 *  @param[in] memory
 *    Input. Pointer to the MLU memory that stores the memory tensor.
 *  @param[in] processed_memory_desc
 *    Input.  Descriptor of the processed memory tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [batch, sequence_length, 128], and data type must be float or half.
 *  @param[in] processed_memory
 *    Input. Pointer to the MLU memory that stores the processed memory tensor.
 *  @param[in] mask_desc
 *    Input.  Descriptor of the mask tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [batch, sequence_length], and data type must be int8.
 *  @param[in] mask
 *    Input. Pointer to the MLU memory that stores the mask tensor.
 *  @param[in] prenet0_filter_desc
 *    Input.  Descriptor of the prenet0 filter tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [Co, Ci], where Co = 256 and Ci = 80, and data type must be half.
 *  @param[in] prenet0_filter
 *    Input. Pointer to the MLU memory that stores the prenet0 filter tensor.
 *  @param[in] prenet1_filter_desc
 *    Input.  Descriptor of the prenet1 filter tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [Co, Ci], where Co = 256 and Ci = 256, and data type must be half.
 *  @param[in] prenet1_filter
 *    Input. Pointer to the MLU memory that stores the prenet1 filter tensor.
 *  @param[in] lstm1_input_filters_desc
 *    Input.  Descriptor of the lstm1 input filters tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [Co, Ci], where Co = 4096 and Ci = 768, and data type must be half.
 *  @param[in] lstm1_input_filters
 *    Input. Pointer to the MLU memory that stores the lstm1 input filters tensor.
 *  @param[in] lstm1_hidden_filters_desc
 *    Input.  Descriptor of the lstm1 hidden filters tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [Co, Ci], where Co = 4096 and Ci = 1024, and data type must be half.
 *  @param[in] lstm1_hidden_filters
 *    Input. Pointer to the MLU memory that stores the lstm1 hidden filters tensor.
 *  @param[in] lstm1_bias_desc
 *    Input.  Descriptor of the lstm1 bias tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [8192], and data type must be float or half.
 *  @param[in] lstm1_bias
 *    Input. Pointer to the MLU memory that stores the lstm1 bias tensor.
 *  @param[in] lstm2_input_filters_desc
 *    Input.  Descriptor of the lstm2 input filters tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [Co, Ci], where Co = 4096 and Ci = 1536, and data type must be half.
 *  @param[in] lstm2_input_filters
 *    Input. Pointer to the MLU memory that stores the lstm2 input filters tensor.
 *  @param[in] lstm2_hidden_filters_desc
 *    Input.  Descriptor of the lstm2 hidden filters tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [Co, Ci], where Co = 4096 and Ci = 1024, and data type must be half.
 *  @param[in] lstm2_hidden_filters
 *    Input. Pointer to the MLU memory that stores the lstm2 hidden filters tensor.
 *  @param[in] lstm2_bias_desc
 *    Input.  Descriptor of the lstm2 bias tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [8192], and data type must be float or half.
 *  @param[in] lstm2_bias
 *    Input. Pointer to the MLU memory that stores the lstm2 bias tensor.
 *  @param[in] attention_query_filter_desc
 *    Input.  Descriptor of the attention query filter tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [Co, Ci], where Co = 128 and Ci = 1024, and data type must be half.
 *  @param[in] attention_query_filter
 *    Input. Pointer to the MLU memory that stores the attention query filter tensor.
 *  @param[in] attention_conv_filter_desc
 *    Input.  Descriptor of the attention conv filter tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [Co, T, Ci], where Co = 32, T = 31 and Ci = 2, and data type must be half.
 *  @param[in] attention_conv_filter
 *    Input. Pointer to the MLU memory that stores the attention conv filter tensor.
 *  @param[in] attention_full_filter_desc
 *    Input.  Descriptor of the attention full filter tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [Co, Ci], where Co = 128 and Ci = 32, and data type must be half.
 *  @param[in] attention_full_filter
 *    Input. Pointer to the MLU memory that stores the attention full filter tensor.
 *  @param[in] attention_out_filter_desc
 *    Input.  Descriptor of the attention output filter tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [Co, Ci], where Co = 1 and Ci = 128, and data type must be half.
 *  @param[in] attention_out_filter
 *    Input. Pointer to the MLU memory that stores the attention output filter tensor.
 *  @param[in] prj_mel_filter_desc
 *    Input.  Descriptor of the filter tensor for the mel output of the projection layer, which holds dimension, data type and layout.
 *            The shape of tensor must be [Co, Ci], where Co = 80 and Ci = 1536, and data type must be half.
 *  @param[in] prj_mel_filter
 *    Input. Pointer to the MLU memory that stores the filter tensor for the mel output of the projection layer.
 *  @param[in] prj_mel_bias_desc
 *    Input.  Descriptor of the bias tensor for the mel output of the projection layer, which holds dimension, data type and layout.
 *            The shape of tensor must be [80], and data type must be float or half.
 *  @param[in] prj_mel_bias
 *    Input. Pointer to the MLU memory that stores the bias tensor for the mel output of the projection layer.
 *  @param[in] prj_gate_filter_desc
 *    Input.  Descriptor of the filter tensor for the gate of the projection layer, which holds dimension, data type and layout.
 *            The shape of tensor must be [Co, Ci], where Co = 1 and Ci = 1536, and data type must be half.
 *  @param[in] prj_gate_filter
 *    Input. Pointer to the MLU memory that stores the filter tensor for the gate of the projection layer.
 *  @param[in] prj_gate_bias_desc
 *    Input.  Descriptor of the bias tensor for the gate of the projection layer, which holds dimension, data type and layout.
 *            The shape of tensor must be [1], and data type must be float or half.
 *  @param[in] prj_gate_bias
 *    Input. Pointer to the MLU memory that stores the bias tensor for the gate of the projection layer.
 *  @param[in] workspace
 *    Input.  Pointer to the MLU memory that is used as an extra workspace.
 *  @param[in] workspace_size
 *    Input.  The size of extra workspace.
 *  @param[in] output_mel_desc
 *    Input.  Descriptor of output mel tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [max_frame_length, batch, 80], and data type must be float or half.
 *  @param[out] output_mel
 *    Output. Pointer to the MLU memory that stores the output mel data.
 *  @param[in] output_lengths_desc
 *    Input.  Descriptor of output lengths tensor, which holds dimension, data type and layout.
 *            The shape of tensor must be [batch, 1], and data type must be int32.
 *  @param[out] output_lengths
 *    Output. Pointer to the MLU memory that stores the output lengths data.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions are encountered:
 *    - handle is NULL.
 *    - pointer is NULL.
 *    - parameters do not meet scale limitation.
 *  @retval CNNL_STATUS_ARCH_MISMATCH
 *    One or more of the following conditions are encountered:
 *    - This function is run on the hardware platform that is not supported.
 */
cnnlStatus_t CNNL_WIN_API
cnnlTacotron2Decoder(cnnlHandle_t handle,
                     const cnnlTacotron2DecoderDescriptor_t desc,
                     const cnnlTensorDescriptor_t decoder_input_desc,
                     void *decoder_input,
                     const cnnlTensorDescriptor_t lstm1_hidden_desc,
                     void *lstm1_hidden,
                     const cnnlTensorDescriptor_t lstm1_cell_desc,
                     void *lstm1_cell,
                     const cnnlTensorDescriptor_t lstm2_hidden_desc,
                     void *lstm2_hidden,
                     const cnnlTensorDescriptor_t lstm2_cell_desc,
                     void *lstm2_cell,
                     const cnnlTensorDescriptor_t attention_desc,
                     void *attention,
                     const cnnlTensorDescriptor_t attention_cum_desc,
                     void *attention_cum,
                     const cnnlTensorDescriptor_t attention_context_desc,
                     void *atttention_context,
                     const cnnlTensorDescriptor_t memory_desc,
                     void *memory,
                     const cnnlTensorDescriptor_t processed_memory_desc,
                     void *processed_memory,
                     const cnnlTensorDescriptor_t mask_desc,
                     void *mask,
                     const cnnlTensorDescriptor_t prenet0_filter_desc,
                     void *prenet0_filter,
                     const cnnlTensorDescriptor_t prenet1_filter_desc,
                     void *prenet1_filter,
                     const cnnlTensorDescriptor_t lstm1_input_filters_desc,
                     void *lstm1_input_filters,
                     const cnnlTensorDescriptor_t lstm1_hidden_filters_desc,
                     void *lstm1_hidden_filters,
                     const cnnlTensorDescriptor_t lstm1_bias_desc,
                     void *lstm1_bias,
                     const cnnlTensorDescriptor_t lstm2_input_filters_desc,
                     void *lstm2_input_filters,
                     const cnnlTensorDescriptor_t lstm2_hidden_filters_desc,
                     void *lstm2_hidden_filters,
                     const cnnlTensorDescriptor_t lstm2_bias_desc,
                     void *lstm2_bias,
                     const cnnlTensorDescriptor_t attention_query_filter_desc,
                     void *attention_query_filter,
                     const cnnlTensorDescriptor_t attention_conv_filter_desc,
                     void *attention_conv_filter,
                     const cnnlTensorDescriptor_t attention_full_filter_desc,
                     void *attention_full_filter,
                     const cnnlTensorDescriptor_t attention_out_filter_desc,
                     void *attention_out_filter,
                     const cnnlTensorDescriptor_t prj_mel_filter_desc,
                     void *prj_mel_filter,
                     const cnnlTensorDescriptor_t prj_mel_bias_desc,
                     void *prj_mel_bias,
                     const cnnlTensorDescriptor_t prj_gate_filter_desc,
                     void *prj_gate_filter,
                     const cnnlTensorDescriptor_t prj_gate_bias_desc,
                     void *prj_gate_bias,
                     void *workspace,
                     size_t workspace_size,
                     const cnnlTensorDescriptor_t output_mel_desc,
                     void *output_mel,
                     const cnnlTensorDescriptor_t output_lengths_desc,
                     void *output_lengths);

/******************************************************************************
 * Cambricon CNNL OP: FlatSearch
 ******************************************************************************/
// Group:Flat Search
/*!
 * @brief A function
 * This function retrieves extra space size needed in FlatSearch operation.
 *
 * @param[in] handle
 *   Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and
 *          queues in the FlatSearch operation.
 * @param[in] lib_desc
 *   Input. Descriptor of the lib tensor.
 * @param[in] topk_distance_desc
 *   Input. Descriptor of the topk_distance tensor.
 * @param[in] topk_index_desc
 *   Input. Descriptor of the topk_index_tensor.
 * @param[out] workspace_size
 *   Output. Pointer to the MLU memory that stores the extra space size (Bytes)
 *   needed in FlatSearch operation.
 * @retval CNNL_STATUS_SUCCESS
 *   The function ended normally.
 * @retval CNNL_STATUS_BAD_PARAM
 *   One or more of the following conditions must be met:
 *   - handle is NULL.
 *   - lib_desc is NULL.
 *   - topk_distance_desc is NULL.
 *   - topk_index_desc is NULL.
 *   - workspace_size is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlGetFlatSearchWorkspaceSize(cnnlHandle_t handle,
                               const cnnlTensorDescriptor_t lib_desc,
                               const cnnlTensorDescriptor_t topk_distance_desc,
                               const cnnlTensorDescriptor_t topk_index_desc,
                               size_t *workspace_size);

// Group:Flat Search
/*!
 * @brief A function
 * This function retrieves extra space size needed in FlatSearch operation.
 *
 * This function computes the topk-min distance and corresponding index between
 * query vector and lib vector.
 *
 * **Formula**
 *
 * This operation contains the following steps:
 *
 * 1. Compute distance.
 *
 *    Compute L2-distance between query vector and lib vector.
 *
 * 2. Compute topk.
 *
 *    Selects the most relevant [nk] ones from the [nlib] lib according to the
 *    distance. nk represents the number of probed lib. nlib represents the
 *    number of all lib vector.
 *
 * **DataType**
 *
 *   - input: float(lib), float(query).
 *   - output: float(topk_distance), int32(topk_index).
 *
 * **Only supports MLU370**
 *
 * **Scale Limitation**
 *
 *   - nk cannot be greater than 1200.
 *   - d(lib_desc->dim[1]) represents the dimensions of feature vector and
 *     cannot be greater than 30000.
 *
 * **Reference**
 *
 *   http://github.com/facebookresearch/faiss
 *
 * @param[in] handle
 *   Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and
 *          queues in the FlatSearch operation.
 * @param[in] lib_desc
 *   Input. Descriptor of the lib tensor, which contains the dimension, data
 *   type and layout of the tensor. The dimension is [nlib, d].
 * @param[in] lib
 *   Input. Pointer to the MLU memory that stores the lib tensor. lib stores all
 *   the lib vector.
 * @param[in] query_desc
 *   Input. Descriptor of the query tensor, which contains the dimension, data
 *   type and layout of the tensor. The dimension is [nq, d]. nq represents the
 *   number of all the query vector.
 * @param[in] query
 *   Input. Pointer to the MLU memory that stores the query tensor. query stores
 *   all the query vector.
 * @param[in] workspace
 *   Input. Pointer to the MLU memory that stores some temporary result.
 *  @param[in] workspace_size
 *    Input. The value of workspace_size.
 * @param[out] topk_distance_desc
 *   Output. Descriptor of the topk_distance tensor, which contains the
 *   dimension, data type and layout of the tensor. The dimension is [nq, nk].
 * @param[out] topk_distance
 *   Output. Pointer to the MLU memory that stores the topk_distance tensor.
 *   topk_distance stores the topk-distance between query vector and lib vector.
 * @param[out] topk_index_desc
 *   Output. Descriptor of the topk_index tensor, which contains the dimension,
 *   data type and layout of the tensor. The dimension is [nq, nk].
 * @param[out] topk_index
 *   Output. Pointer to the MLU memory that stores the topk_index tensor.
 *   topk_index stores the topk-index with respect to query.
 * @retval CNNL_STATUS_SUCCESS
 *   The function ended normally.
 * @retval CNNL_STATUS_BAD_PARAM
 *   One or more of the following conditions must be met:
 *   - handle is NULL.
 *   - lib_desc is NULL.
 *   - lib is NULL.
 *   - query_desc is NULL.
 *   - query is NULL.
 *   - workspace is NULL.
 *   - workspace_size is too small.
 *   - topk_distance_desc is NULL.
 *   - topk_distance is NULL.
 *   - topk_index_desc is NULL.
 *   - topk_index is NULL.
 *   - tensor dim or datatype does not match.
 *  @retval CNNL_STATUS_ARCH_MISMATCH
 *    One or more of the following conditions are encountered:
 *    - This function is run on the hardware platform that is not supported.
 */
cnnlStatus_t CNNL_WIN_API
cnnlFlatSearch(cnnlHandle_t handle,
               const cnnlTensorDescriptor_t lib_desc,
               const void *lib,
               const cnnlTensorDescriptor_t query_desc,
               const void *query,
               void *workspace,
               size_t workspace_size,
               const cnnlTensorDescriptor_t topk_distance_desc,
               void *topk_distance,
               const cnnlTensorDescriptor_t topk_index_desc,
               void *topk_index);

/******************************************************************************
 * Cambricon CNNL OP: FSMN
 ******************************************************************************/
/*! The descriptor of the feedforward sequential memory convolution input network, including
 *  the number of loop_back_step and loop_ahead_step.
 *
 *  You need to call the ::cnnlCreateFSMNDescriptor function to create a descriptor,
 *  and call the ::cnnlSetFSMNDescriptor function to set the information of the fsmn
 *  operation to the descriptor. Also, you need to destroy the Cambricon CNNL context at the
 *  end with the ::cnnlDestroyFSMNDescriptor function.
 */
typedef struct cnnlFSMNStruct *cnnlFSMNDescriptor_t;

// Group:FSMN
/*!
 *  @brief A function.
 *
 *  This function is used to create a descriptor of fsmn and malloc memory for it.
 *
 *  @param[in]  desc
 *    Input. Pointer to the MLU memory that stores the descriptor of fsmn.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_ALLOC_FAILED
 *    The function malloc memory space failed.
 */
cnnlStatus_t CNNL_WIN_API
cnnlCreateFSMNDescriptor(cnnlFSMNDescriptor_t *desc);

// Group:FSMN
/*!
 *  @brief A function.
 *
 *  This function is used to destroy a descriptor of fsmn and free memory for it.
 *
 *  @param[in]  desc
 *    Input. The descriptor of fsmn operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlDestroyFSMNDescriptor(cnnlFSMNDescriptor_t desc);

// Group:FSMN
/*!
 *  @brief A function.
 *
 *  This function is used to assign fsmn descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *     Users need to handle fsmn descriptor, use
 *     cnnlCreateFSMNDescriptor() to create descriptor and use
 *     cnnlSetFSMNDescriptor() to set its parameters.
 *
 *  @param[in]  look_back_step
 *    Input. Number of look back step of the current token.
 *  @param[in]  look_ahead_step
 *    Input. Number of look ahead step of the current token.
 *  @param[in]  use_residual
 *    Input. Whether to use residual when computing output.
 *  @param[in]  use_mask
 *    Input. Whether to use mask.
 *  @param[in]  mask
 *    Input. Device pointer that points to mask space.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetFSMNDescriptor(cnnlFSMNDescriptor_t desc,
                      const int look_back_step,
                      const int look_ahead_step,
                      const bool use_residual,
                      const bool use_mask,
                      const void *mask);

// Group:FSMN
/*!
 *  @brief A function.
 *
 *  This function is used to do the fsmn operation used in SCAMA network.
 *
 *  **Formula**
 *
 *  This operation contains following steps:
 *
 *  1. depthwise conv
 *
 *    intermediate = depthwise(input, filter)
 *
 *  2. add residual
 *
 *    output = add(intermediate, residual)
 *
 *  **Data Type**
 *
 *  - input: float, half.
 *
 *  - filter: float, half.
 *
 *  - residual: float, half.
 *
 *  - output: float, half.
 *
 *  **Attention: **
 *
 *    - The data type of input, filter, residual, output must be the same.
 *
 *  **Scale Limitation**
 *
 *    - The number of dimensions of input, residual and output tensors must match.
 *
 *    - The fsmn descriptor parameter should meet:
 *        0 <= look_back_step <= filter_size
 *        0 <= look_ahead_step <= filter_size
 *
 *    - batch_size and seq_len must not be greater than the max value of int32.
 *
 *    - seq_len must not be greater than 512.
 *
 *    - filter_size must not be greater than 32.
 *
 *    - hidden_size must be dividable by 64 and not be greater than 512.
 *
 *  **Example**
 *
 *    Dimension of input: [batch_size, seq_len, hidden_size]
 *
 *    Dimension of filter: [filter_size, hidden_size]
 *
 *    Dimension of mask: [batch_size, seq_len]
 *
 *    Dimension of residual: [batch_size, seq_len, hidden_size]
 *
 *    Dimension of output: [batch_size, seq_len, hidden_size]
 *
 *  **API Dependency**
 *
 *   You need to call the cnnlCreateFSMNDescriptor() before calling this function.
 *
 *   You need to call the cnnlDestroyFSMNDescriptor() function after
 *   calling this function.
 *
 *  @param[in]  handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           fsmn operation.
 *  @param[in] desc
 *    Input. A struct with parameters of FSMN, containing loop_back_step, loop_back_step
 *           and use_residual.
 *  @param[in]  input_desc
 *    Input. Descriptor of input, containing dimension and the layout of input.
 *  @param[in]  input
 *    Input. Device pointer points to input space.
 *  @param[in]  filter_desc
 *    Input. Descriptor of filter, containing dimension and the layout of filter.
 *  @param[in]  filter
 *    Input. Device pointer points to filter space.
 *  @param[in]  residual_desc
 *    Input. Descriptor of residual, containing dimension and the layout of residual.
 *  @param[in]  residual
 *    Input. Device pointer points to residual space.
 *  @param[out]  output_desc
 *    Input. Descriptor of output, containing dimension and the layout of output.
 *  @param[out]  output
 *    Input. Device pointer points to output space.
 *  @retval CNNL_STATUS_SUCCESS = 0
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM = 3
 *    One or more of the following conditions are encountered:
 *    - handle is NULL.
 *    - pointer is NULL.
 *    - parameters do not meet scale limitation.
 *  @retval CNNL_STATUS_ARCH_MISMATCH
 *    One or more of the following conditions are encountered:
 *    - This function is run on the hardware platform that is not supported.
 */
cnnlStatus_t cnnlFSMN(
    cnnlHandle_t handle,
    const cnnlFSMNDescriptor_t desc,
    const cnnlTensorDescriptor_t input_desc,
    const void *input,
    const cnnlTensorDescriptor_t filter_desc,
    const void *filter,
    const cnnlTensorDescriptor_t residual_desc,
    const void *residual,
    cnnlTensorDescriptor_t output_desc,
    void *output);

/******************************************************************************
 * Cambricon CNNL OP: SiamRPNPost
 ******************************************************************************/
/*! The descriptor of SiamRPNPost operator that holds the information including
 *  batch, num_anchor, height, width, stride, penality_k, window_influence and
 *  lr_attr.
 *
 *  You need to call the ::cnnlCreateSiamRPNPostDescriptor() function
 *  to create a descriptor, and call the ::cnnlSetSiamRPNPostDescriptor()
 *  function to set the tensor information to the descriptor.
 *  Also, you need to destroy the SiamRPNPost descriptor at the end with the
 *  ::cnnlDestroySiamRPNPostDescriptor() function.
 */
typedef struct cnnlSiamRPNPostStruct *cnnlSiamRPNPostDescriptor_t;

// Group:SiamRPNPost
/*!
 *  @brief A function.
 *
 *  The one-shot detection and proposal selection process in
 *  Siamese Region Proposal Network. It is used to get the bbox in object
 *  tracking.
 *
 *  **Formula**
 *
 *  This operation contains three steps:
 *
 *  1. Update anchors
 *
 *    delta = (dx, dy, dw, dh)
 *
 *    anchor = (x, y, w, h)
 *
 *    tmp_x = ori_w + w_const * stride + dx * w
 *
 *    tmp_y = ori_h + h_const * stride + dy * h
 *
 *    tmp_w = w * exp(dw)
 *
 *    tmp_h = h * exp(dh)
 *
 *    where ori_w = -(width / 2) * stride, ori_h = -(height / 2) * stride.
 *
 *  2. Compute penalty
 *
 *    penalty = exp(penalty_k * max(r / r', r' / r) * max(s / s', s' / s))
 *
 *    r = tmp_w / tmp_h, r' = ratio
 *
 *    (tmp_w + p) * (tmp_h + p) = s^2
 *
 *    p = (tmp_w + tmp_h) / 2
 *
 *    s' = scale
 *
 *    where ratio and scale are saved in target_scale_ratio.
 *
 *  3. Compute score
 *
 *    score_neg = score[:, 0:num_anchor]
 *
 *    score_pos = scores[:, num_anchor:]
 *
 *    scores = sigmoid(score_pos - score_neg)
 *
 *    scores1 = scores * penalty
 *
 *    scores2 = scores1 * (1.0 - window_influence) + cos_window * window_influence
 *
 *    offset = argmax(scores2)
 *
 *    output = (tmp_x[offset], tmp_y[offset], tmp_w[offset], tmp_h[offset],
 *              scores[offset], scores1[offset] * lr_attr)
 *
 *  **DataType**
 *
 *    MLU270 & MLU370:
 *
 *    - scores: float, half.
 *
 *    - delta: float, half.
 *
 *    - target_scale_ratio: float, half.
 *
 *    - anchor: float, half.
 *
 *    - h_const: float, half.
 *
 *    - w_const: float, half.
 *
 *    - cos_window: float, half.
 *
 *    - output: float, half.
 *
 *  **Data Layout**
 *
 *    - scores: CNNL_LAYOUT_NCHW
 *
 *    - delta: CNNL_LAYOUT_NCHW
 *
 *  **Attention: **
 *
 *    - The data type of inputs and outputs must be same.
 *
 *  **Scale Limitation**
 *
 *    hw_align = PAD_UP(height * width, 64)
 *
 *    ahw_align = hw_align * num_anchor
 *
 *    num_anchor_align = PAD_UP(num_anchor, 64)
 *
 *    (3 * hw_align + 15 * ahw_align + 4 * num_anchor_align + PAD_UP(2 * batch_size, 64) + 64) * sizeof(dtype) < 384KB
 *
 *  **Example**
 *
 *    scores : a tensor of [batch_size, 2 * num_anchor, height, width]
 *
 *    delta : a tensor of [batch_size, 4 * num_anchor, height, width]
 *
 *    target_scale_ratio : a tensor of [batch_size, 2]
 *
 *    anchor : a tensor of [4, num_anchor], anchor's layout is (x, y, w, h)
 *
 *    h_const : a tensor of [height, width]
 *
 *    w_const : a tensor of [height, width]
 *
 *    cos_window : a tensor of [height, width]
 *
 *    Then we will get the output:
 *
 *    output : a tensor of [batch_size, 6]
 *
 *  **Reference**
 *
 *    openaccess.thecvf.com/content_cvpr_2018/papers/Li_High_Performance_Visual_CVPR_2018_paper.pdf
 *
 *  **API Dependency**
 *
 *    You need to call the ::cnnlCreateSiamRPNPostDescriptor() to
 *    create descriptor and use ::cnnlSetSiamRPNPostDescriptor()
 *    to set its parameters before calling this function.
 *
 *    You need to call the ::cnnlDestroySiamRPNPostDescriptor()
 *    function after calling this function.
 *
 *  @param[in]  handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           SiamRPNPost operation.
 *  @param[in] siam_rpn_post_desc
 *    Input. A struct with parameters of SiamRPNPost operation.
 *  @param[in]  desc_scores
 *    Input. Descriptor of scores, containing dimensions of [batch_size, 2 * num_anchor, height, width].
 *  @param[in]  scores
 *    Input. Pointer to the device memory that stores the scores space.
 *  @param[in]  desc_delta
 *    Input. Descriptor of delta, containing dimensions of [batch_size, 4 * num_anchor, height, width].
 *  @param[in]  delta
 *    Input. Pointer to the device memory that stores the delta space.
 *  @param[in]  desc_target_scale_ratio
 *    Input. Descriptor of target_scale_ratio, containing dimensions of [batch_size, 2].
 *  @param[in]  target_scale_ratio
 *    Input. Pointer to the device memory that stores the target_scale_ratio space.
 *  @param[in]  desc_anchor
 *    Input. Descriptor of anchor, containing dimensions of [4, num_anchor], where anchor is described by (x, y, w, h).
 *  @param[in]  anchor
 *    Input. Pointer to the device memory that stores the anchor space.
 *  @param[in]  desc_h_const
 *    Input. Descriptor of h_const, containing dimensions of [height, width].
 *  @param[in]  h_const
 *    Input. Pointer to the device memory that stores the h_const space.
 *    It is the ordinate used to generate the grid.
 *  @param[in]  desc_w_const
 *    Input. Descriptor of w_const, containing dimensions of [height, width].
 *  @param[in]  w_const
 *    Input. Pointer to the device memory that stores the w_const space.
 *    It is the abscissa used to generate the grid.
 *  @param[in]  desc_cos_window
 *    Input. Descriptor of cos_window, containing dimensions of [height, width].
 *  @param[in]  cos_window
 *    Input. Pointer to the device memory that stores the cos_window space.
 *    cos_window is a cosine window used for filtering in spatial positions.
 *  @param[in]  workspace
 *    Input. The pointer to data address of workspace.
 *  @param[in]  workspace_size
 *    Input. The value of workspace_size.
 *  @param[out]  desc_output
 *    Output. Descriptor of output, containing data type, dimensions and layout.
 *    Shape must be [batch_size, 6].
 *  @param[out]  output
 *    Output. Pointer to the device memory that stores the output space.
 *
 *  @retval CNNL_STATUS_SUCCESS = 0
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM = 3
 *    One or more of the following conditions are encountered:
 *    - handle is NULL.
 *    - pointer is NULL.
 *    - parameters is invalid.
 *  @retval CNNL_STATUS_ARCH_MISMATCH
 *    One or more of the following conditions are encountered:
 *    - This function is run on the hardware platform that is not supported.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSiamRPNPost(cnnlHandle_t handle,
                const cnnlSiamRPNPostDescriptor_t siam_rpn_post_desc,
                const cnnlTensorDescriptor_t desc_scores,
                const void *scores,
                const cnnlTensorDescriptor_t desc_delta,
                const void *delta,
                const cnnlTensorDescriptor_t desc_target_scale_ratio,
                const void *target_scale_ratio,
                const cnnlTensorDescriptor_t desc_anchor,
                const void *anchor,
                const cnnlTensorDescriptor_t desc_h_const,
                const void *h_const,
                const cnnlTensorDescriptor_t desc_w_const,
                const void *w_const,
                const cnnlTensorDescriptor_t desc_cos_window,
                const void *cos_window,
                void *workspace,
                size_t workspace_size,
                const cnnlTensorDescriptor_t desc_output,
                const void *output);

// Group:SiamRPNPost
/*!
 *  @brief A function.
 *
 *  This function is used to create a descriptor of SiamRPNPost
 *  and allocate memory for it.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *  After calling this function, you can call the ::cnnlSetSiamRPNPostDescriptor()
 *  function to initialize and set the information to the SiamRPNPost descriptor.
 *  You need to call the ::cnnlDestroySiamRPNPostDescriptor() function
 *  to destroy the descriptor.
 *
 *  @param[in]  desc
 *    Input. Descriptor of SiamRPNPost operation. The information of the operation
 *    is defined by ::cnnlSiamRPNPostDescriptor_t.
 *
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_ALLOC_FAILED
 *    The function failed to allocate memory space.
 */
cnnlStatus_t CNNL_WIN_API
cnnlCreateSiamRPNPostDescriptor(cnnlSiamRPNPostDescriptor_t *desc);

// Group:SiamRPNPost
/*!
 *  @brief A function.
 *
 *  This function is used to destroy a descriptor of SiamRPNPost
 *  and free memory for it.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *  You need to call this function after calling the
 *  ::cnnlCreateSiamRPNPostDescriptor() function.
 *
 *  @param[in]  desc
 *    Input. Descriptor of SiamRPNPost operation.
 *
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlDestroySiamRPNPostDescriptor(cnnlSiamRPNPostDescriptor_t desc);

// Group:SiamRPNPost
/*!
 *  @brief A function.
 *
 *  This function is used to assign SiamRPNPost descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *  In terms of SiamRPNPost descriptor, use
 *  ::cnnlCreateSiamRPNPostDescriptor() to create descriptor
 *  and use ::cnnlSetSiamRPNPostDescriptor() to set its parameters.
 *
 *  @param[out] siam_rpn_post_desc
 *    Output. Descriptor of SiamRPNPost operation.
 *  @param[in]  stride
 *    Input. The size of stride in SiamRPNPost, used to generate anchors.
 *  @param[in]  penalty_k
 *    Input. The penalty coefficient in SiamRPNPost, it is a hyper-parameter.
 *  @param[in]  window_influence
 *    Input. It is used for filtering in spatial positions with cos_window. The formula is
 *    scores2 = scores1 * (1.0 - window_influence) + cos_window * window_influence.
 *  @param[in]  lr_attr
 *    Input. A parameter for linear interpolation. After the final bounding box
 *    is selected, target size is updated by linear interpolation to keep the shape
 *    changing smoothly.
 *
 *  @retval CNNL_STATUS_SUCCESS
 *    The object was set successfully.
 *  @retval CNNL_STATUS_INVALIDPARAM
 *    One of the following conditions is met: PARAM_CHECK failed.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetSiamRPNPostDescriptor(
    cnnlSiamRPNPostDescriptor_t siam_rpn_post_desc,
    const int stride,
    const float penalty_k,
    const float window_influence,
    const float lr_attr);

// Group:SiamRPNPost
/*!
 *  @brief A function.
 *  This function is used to get extra space size needed in SiamRPNPos
 *  operation.
 *
 *  **API Dependency**
 *
 *  Some functions need to be called before this function. The dependence is as
 *  follow:
 *
 *  In terms of SiamRPNPost descriptor, use
 *  ::cnnlCreateSiamRPNPostDescriptor() to create descriptor
 *  and use ::cnnlSetSiamRPNPostDescriptor() to set its parameters.
 *
 *  @param[in]  handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           SiamRPNPost operation.
 *  @param[in]  siam_rpn_post_desc
 *    Input. Descriptor of SiamRPNPost operation.
 *  @param[in]  desc_scores
 *    Input. Descriptor of scores, containing dimensions and the layout of scores.
 *  @param[in]  desc_delta
 *    Input. Descriptor of delta, containing dimensions and the layout of delta.
 *  @param[in]  desc_target_scale_ratio
 *    Input. Descriptor of target_scale_ratio, containing dimensions and the layout of target_scale_ratio.
 *  @param[in]  desc_anchor
 *    Input. Descriptor of anchor, containing dimensions and the layout of anchor.
 *  @param[in]  desc_h_const
 *    Input. Descriptor of h_const, containing dimensions and the layout of h_const.
 *  @param[in]  desc_w_const
 *    Input. Descriptor of w_const, containing dimensions and the layout of w_const.
 *  @param[in]  desc_cos_window
 *    Input. Descriptor of cos_window, containing dimensions and the layout of cos_window.
 *  @param[out] size
 *    Output. Pointer to the host memory that stores the workspace size.
 *
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of descs or size is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlGetSiamRPNPostWorkspaceSize(cnnlHandle_t handle,
                                const cnnlSiamRPNPostDescriptor_t siam_rpn_post_desc,
                                const cnnlTensorDescriptor_t desc_scores,
                                const cnnlTensorDescriptor_t desc_delta,
                                const cnnlTensorDescriptor_t desc_target_scale_ratio,
                                const cnnlTensorDescriptor_t desc_anchor,
                                const cnnlTensorDescriptor_t desc_h_const,
                                const cnnlTensorDescriptor_t desc_w_const,
                                const cnnlTensorDescriptor_t desc_cos_window,
                                size_t *size);

/******************************************************************************
 * Cambricon CNNL OP: ctc greedy decoder
 ******************************************************************************/
/*! The descriptor of ctc greedy decoder function that holds the information including
 *  num_batch, num_classes, seq_len and merge_repeated.
 *
 *  You need to call the ::cnnlCreateCtcGreedyDecoderDescriptor() function
 *  to create a descriptor, and call the ::cnnlSetCtcGreedyDecoderDescriptor()
 *  function to set the input information to the descriptor.
 *  Also, you need to destroy the CtcGreedyDecoder descriptor at the end with the
 *  ::cnnlDestroyCtcGreedyDocoderDescriptor() function.
 */
typedef struct cnnlCtcGreedyDecoderStruct *cnnlCtcGreedyDecoderDescriptor_t;

// Group:Ctc Greedy Decoder
/*!
 *  @brief A function.
 *  This function is used to create a ctc greedy decoder descriptor.
 *
 *  @param[in] ctc_greedy_decoder_desc
 *    Input.  A pointer to the struct of ctc greedy decoder descriptor.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *      - ctc_greedy_decoder_desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlCreateCtcGreedyDecoderDescriptor(cnnlCtcGreedyDecoderDescriptor_t *ctc_greedy_decoder_desc);

// Group:Ctc Greedy Decoder
/*!
 *  @brief A function.
 *  This function is used to assign ctc greedy decode descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  The dependence is as follow:
 *
 *    - Before calling this function, you need to call ::cnnlCreateCtcGreedyDecoderDescriptor to
 *      create a descriptor and use ::cnnlSetCtcGreedyDecoderDescriptor() to set its parameters.
 *
 *    - After calling this function, you need to call ::cnnlDestroyCtcGreedyDecoderDescriptor to
 *      destory the decritptor.
 *
 *  @param[in]  ctc_greedy_decoder_desc
 *     Input. Descriptor of ctc greedy decode operation.
 *  @param[in]  merge_repeated
 *     Input. Bool type value indicating whether to remove the flag of duplicate label. Only support
 *            merge_repeated is true.
 *  @retval CNNL_STATUS_SUCCESS
 *     The function ended normally.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetCtcGreedyDecoderDescriptor(cnnlCtcGreedyDecoderDescriptor_t ctc_greedy_decoder_desc,
                                  bool merge_repeated);

// Group:Ctc Greedy Decoder
/*!
 *  @brief A function.
 *
 *  This function is used to destroy ctc greedy decode descriptor.
 *
 *  @param[in] ctc_greedy_decoder_desc
 *    Input.  A pointer to the struct of ctc greedy decode descriptor.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_EXECUTION_FAILED
 *    One of the following conditions are met:
 *      - ctc_greedy_decoder_desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlDestroyCtcGreedyDecoderDescriptor(cnnlCtcGreedyDecoderDescriptor_t ctc_greedy_decoder_desc);

// Group:Ctc Greedy Decoder
/*!
 * @brief A function
 *
 * This function handles the Connnectionist Temporal Classification (CTC) algorithm.
 *
 * **Formula**
 *
 * This operation contains the following steps:
 *
 * 1. Compute index of max value.
 *
 *    The length of input sequence is seq_len * num_classes and calculate the index of
 *    maximum value for each num_clasess data.
 *
 * 2. Remap the maximum index of seq_len.
 *
 *    Each element is compared with its previous one. If the result is same, the
 *    element will be removed. Otherwise, it will be retained.
 *
 * 3. Remove delimiters from reserved elements.
 *
 * 4. Connect the remaining elements of each sequence in step 3 as output.
 *
 * **Data Type**
 *
 *   - input: float.
 *   - output: float.
 *
 * **Scale Limitation**
 *
 *   - Element number of input tensor cannot exceed INT32_MAX, i.e., 2147483647.
 *
 * **Reference**
 *
 *   - http://distill.pub/2017/ctc/
 *   - http://gist.github.com/awni.56369a90d03953e370f3964c826ed4b0
 *
 * @param[in] handle
 *   Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and
 *          queues in the ctc greedy decoder operation.
 * @param[in] ctc_greedy_decoder_desc
 *   Input. Descriptor of ctc greedy decoder, which includes parameters of num_batch,
 *          num_classes, seq_len and merge_repeated.
 * @param[in] input_desc
 *   Input. Descriptor of input sequence, the dimension is [num_batch, seq_len,
 *          num_classes].
 * @param[in] input
 *   Input. Pointer to the MLU memory that stores the input data.
 * @param[out] output_desc
 *   Output. Descriptor of output, the dimension is [num_batch, seq_len].
 * @param[out] output
 *   Output. Pointer to the MLU memory that stores the output data.
 * @retval CNNL_STATUS_BAD_PARAM
 *   One or more of the following conditions must be met:
 *   - handle is NULL.
 *   - ctc_greedy_decoder_desc is NULL.
 *   - lib is NULL.
 *   - input_desc is NULL.
 *   - input is NULL.
 *   - output_desc is NULL.
 *   - distance is NULL.
 *   - output is NULL.
 *   - tensor dimension or data type does not match.
 * @retval CNNL_STATUS_SUCCESS
 *   The function ended normally.
 */
cnnlStatus_t CNNL_WIN_API
cnnlCtcGreedyDecoder(cnnlHandle_t handle,
                     const cnnlCtcGreedyDecoderDescriptor_t ctc_greedy_decoder_desc,
                     const cnnlTensorDescriptor_t input_desc,
                     const void *input,
                     const cnnlTensorDescriptor_t output_desc,
                     void *output);

/******************************************************************************
 * Cambricon CNNL OP: Relative position multi-head attention.
 ******************************************************************************/
/*!
 * @brief An enum.
 * Enumeration variables describe the shape of mask tensor of multi-head attention.
 */
typedef enum {
  CNNL_ATTN_MASK_NONE = 0,
  /*!< Performs attention without softmax masking.*/

  CNNL_ATTN_MASK_NT = 1,
  /*!< The mask tensor has shape [batch, seq_len]. */

  CNNL_ATTN_MASK_TT = 2,
  /*!< The mask tensor has shape [seq_len, seq_len]. */

  CNNL_ATTN_MASK_NTT = 3,
  /*!< The mask tensor has shape [batch, seq_len, seq_len]. */

  CNNL_ATTN_MASK_N = 4,
  /*!< The mask tensor has shape [batch], where each value denotes length of valid sequence. */

  CNNL_ATTN_MASK_NHTT = 5,
} cnnlAttentionMaskMode_t;

/*!
 * @brief An enum.
 * Enumeration variables describe the impelment of mask operation of relative position multi-head attention.
 */
typedef enum {
  CNNL_REL_POS_ATTN_MASK_SOFTMAX_FILLZERO = 0,
  /*!< Mask tensor contains only 0 or -1, and mask operation is performed as:
       scores = scores + mask * maskfill_value
       scores = softmax(scores)
       scores = scores * (mask + 1) */

  CNNL_REL_POS_ATTN_MASK_SOFTMAX = 1,
  /*!< Mask operation is performed as:
       scores = scores + mask * maskfill_value
       scores = softmax(scores) */
} cnnlRelPosAttnMaskImplType_t;

/*! The descriptor of Relative position multi-head attention operation that holds the information
 *  including maskfill_value.
 *
 *  You need to call the ::cnnlCreateRelPositionMultiHeadAttentionDescriptor() function
 *  to create a descriptor, and call the ::cnnlSetRelPositionMultiHeadAttentionDescriptor()
 *  function to set the input information to the descriptor.
 *  Also, you need to destroy the descriptor at the end with the
 *  ::cnnlDestroyRelPositionMultiHeadAttentionDescriptor() function.
 */
typedef struct cnnlRelPositionMultiHeadAttentionStruct
    *cnnlRelPositionMultiHeadAttentionDescriptor_t;

// Group:Relative Position Multi-head Attention
/*!
 *  @brief A function.
 *  This function is used to create a relative position multi-head attention descriptor.
 *
 *  @param[out] desc
 *    Output. A pointer to the host memory that stores the relative position multi-head attention
 *            descriptor.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *      - desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlCreateRelPositionMultiHeadAttentionDescriptor(
    cnnlRelPositionMultiHeadAttentionDescriptor_t *desc);

// Group:Relative Position Multi-head Attention
/*!
 *  @brief A function.
 *  This function is used to assign a relative position multi-head attention descriptor with
 *  parameters.
 *
 *  @param[in] desc
 *    Input. The relative position multi-head attention descriptor to be set.
 *  @param[in] maskfill_value
 *    Input. The scalar value that will be multiplied with mask tensor, before softmax operation.
 *           If \b mask_mode is CNNL_REL_POS_ATTN_MASK_SOFTMAX_FILLZERO,
 *           it should be a large positive value so that maskfill_value * mask is small
 *           enough to ensure that masked parts are zero after softmax operation.
 *  @param[in] mask_mode
 *    Input. Mask mode of relative position multi-head attention. Currently only CNNL_ATTN_MASK_NTT
 *           is supported.
 *  @param[in] mask_impl
 *    Input. Implement of mask operation of relative position multi-head attention. If \b mask_impl
 *           is set to CNNL_REL_POS_ATTN_MASK_SOFTMAX, we recommend to set \b maskfill_value to 1
 *           and pre-process mask tensor for better performance.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *      - desc is NULL.
 *      - one or more parameters are unsupported.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetRelPositionMultiHeadAttentionDescriptor(
    cnnlRelPositionMultiHeadAttentionDescriptor_t desc,
    float maskfill_value,
    cnnlAttentionMaskMode_t mask_mode,
    cnnlRelPosAttnMaskImplType_t mask_impl);

// Group:Relative Position Multi-head Attention
/*!
 *  @brief A function.
 *
 *  This function is used to destroy relative position multi-head attention descriptor.
 *
 *  @param[in] desc
 *    Input.  The relative position multi-head attention descriptor to be destroyed.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *      - desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlDestroyRelPositionMultiHeadAttentionDescriptor(
    cnnlRelPositionMultiHeadAttentionDescriptor_t desc);

// Group:Relative Position Multi-head Attention
/*!
 * @brief A function
 *
 * This function handles the multi-head attention with relative position algorithm.
 *
 * **Formula**
 *
 * This operation contains the following steps:
 *
 * 1. Generate score
 *
 * q_with_bias_u = (query + pos_bias_u)
 *
 * q_with_bias_v = (query + pos_bias_v)
 *
 * matrix_ac = batchdot(q_with_bias_u, key)
 *
 * matrix_bd = batchdot(q_with_bias_v, key_relative_position)
 *
 * scores = softmax((matrix_ac + matrix_bd) / sqrt(head_size) + mask * op_desc->maskfill_value)
 *
 * if (op_desc->mask_impl == CNNL_REL_POS_ATTN_MASK_SOFTMAX_FILLZERO) {
 *   scores = scores * (mask + 1)
 * }
 *
 * 2. Compute attention
 *
 * qkv = batchdot(scores, value)
 *
 * 3. Compute linear layer
 *
 * output = matmul(qkv, out_filter) + out_bias
 *
 * **Data Type**
 *
 *   - All inputs, filter, and outputs must have the same data type, either half or float.
 *
 * **Scale Limitation**
 *
 *   - 0 < batch
 *   - 0 < seq_len_q <= 512
 *   - 0 < seq_len_kv <= 512
 *   - head_num = 4 or 8 or 12 or 16
 *   - 0 < head_size <= 64
 *
 * **Reference**
 *
 *   - https://github.com/wenet-e2e/wenet/blob/main/wenet/transformer/attention.py
 *
 * @param[in] handle
 *   Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and
 *          queues in the operation.
 * @param[in] op_desc
 *   Input. Descriptor of relative position multi-head attention operation.
 * @param[in] workspace
 *   Input. A pointer to the MLU memory that is used as an extra workspace. Reserved for future
 *          use.
 * @param[in] workspace_size
 *   Input. The size of extra space. Reserved for future use.
 * @param[in] query_desc
 *   Input. Descriptor of \b query tensor. Shape must be [batch, seq_len_q, head_num, head_size].
 * @param[in] query
 *   Input. A pointer to the MLU memory that stores the query data.
 * @param[in] key_desc
 *   Input. Descriptor of \b key tensor. Shape must be [batch, seq_len_kv, head_num, head_size].
 * @param[in] key
 *   Input. A pointer to the MLU memory that stores the key data.
 * @param[in] value_desc
 *   Input. Descriptor of \b value tensor. Shape must be [batch, seq_len_kv, head_num, head_size].
 * @param[in] value
 *   Input. A pointer to the MLU memory that stores the value data.
 * @param[in] key_relative_position_desc
 *   Input. Descriptor of \b key_relative_position tensor. Shape must be
 *          [seq_len_kv, head_num, head_size].
 * @param[in] key_relative_position
 *   Input. A pointer to the MLU memory that stores the key_relative_position data.
 * @param[in] value_relative_position_desc
 *   Input. Descriptor of \b value_relative_position tensor. Reserved for future use.
 * @param[in] value_relative_position
 *   Input. Reserved for future use.
 * @param[in] mask_desc
 *   Input. Descriptor of \b mask tensor. Shape must be [batch, seq_len_q, seq_len_kv].
 * @param[in] mask
 *   Input. A pointer to the MLU memory that stores the mask data. It must only contain 0 and -1,
 *          where 0 means corresponding token is valid, -1 means corresponding token is meaningless
 *          padded token.
 * @param[in] position_bias_u_desc
 *   Input. Descriptor of \b position_bias_u tensor. Shape must be [head_num * head_size].
 * @param[in] position_bias_u
 *   Input. A pointer to the MLU memory that stores the position_bias_u data.
 * @param[in] position_bias_v_desc
 *   Input. Descriptor of \b position_bias_v tensor. Shape must be [head_num * head_size].
 * @param[in] position_bias_v
 *   Input. A pointer to the MLU memory that stores the position_bias_v data.
 * @param[in] out_filter_desc
 *   Input. Descriptor of \b out_filter tensor. Shape must be
 *          [head_num * head_size, head_num * head_size].
 * @param[in] out_filter
 *   Input. A pointer to the MLU memory that stores the filter data of linear layer.
 * @param[in] out_bias_desc
 *   Input. Descriptor of \b out_bias tensor. Shape must be [head_num * head_size].
 * @param[in] out_bias
 *   Input. A pointer to the MLU memory that stores the bias data of linear layer.
 * @param[out] output_desc
 *   Input. Descriptor of \b output tensor. Shape must be [batch, seq_len_q, head_num, head_size].
 * @param[out] output
 *   Input. A pointer to the MLU memory that stores the output data.
 * @retval CNNL_STATUS_BAD_PARAM
 *   One or more of the following errors occurred:
 *     - One or more required argument is NULL.
 *     - Scale limitation is not satisfied.
 * @retval CNNL_STATUS_ARCH_MISMATCH
 *   One or more of the following errors occurred:
 *     - Device type is not MLU370.
 *     - Device has less than 4 visible clusters.
 *     - Device has less or more than 4 cores per cluster.
 *     - Device does not support Union4 task.
 * @retval CNNL_STATUS_SUCCESS
 *   The function ended normally.
 */
cnnlStatus_t CNNL_WIN_API
cnnlRelPositionMultiHeadAttention(
    const cnnlHandle_t handle,
    const cnnlRelPositionMultiHeadAttentionDescriptor_t op_desc,
    void *workspace,
    size_t workspace_size,
    const cnnlTensorDescriptor_t query_desc,
    const void *query,
    const cnnlTensorDescriptor_t key_desc,
    const void *key,
    const cnnlTensorDescriptor_t value_desc,
    const void *value,
    const cnnlTensorDescriptor_t key_relative_position_desc,
    const void *key_relative_position,
    const cnnlTensorDescriptor_t value_relative_position_desc,
    const void *value_relative_position,
    const cnnlTensorDescriptor_t mask_desc,
    const void *mask,
    const cnnlTensorDescriptor_t position_bias_u_desc,
    const void *position_bias_u,
    const cnnlTensorDescriptor_t position_bias_v_desc,
    const void *position_bias_v,
    const cnnlTensorDescriptor_t out_filter_desc,
    const void *out_filter,
    const cnnlTensorDescriptor_t out_bias_desc,
    const void *out_bias,
    const cnnlTensorDescriptor_t output_desc,
    void *output);

/******************************************************************************
 * Cambricon CNNL OP: Pack2PAD
 ******************************************************************************/
/*! The descriptor of Pack2Pad.
 * You can use cnnlCreatePadPackedSequenceDescriptor() and
 * cnnlDestroyPadPackedSequenceDescriptor() to create and destroy the descriptor
 * respectively.
 */
typedef struct cnnlPadPackedSequenceStruct *cnnlPadPackedSequenceDescriptor_t;

// Group:Pack2Pad
/*!
 *  @brief A function.
 *
 *  This function is used to create a descriptor of pack2pad,
 *  which contains enforce_sorted.
 *
 *  @param[in]  desc
 *    Input. Descriptor of pack2pad operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_ALLOC_FAILED
 *    The function fails to allocate memory for the pack2pad descriptor.
 */
cnnlStatus_t CNNL_WIN_API
cnnlCreatePadPackedSequenceDescriptor(cnnlPadPackedSequenceDescriptor_t *desc);

// Group:Pack2Pad
/*!
 *  @brief A function.
 *
 *  This function is used to destroy a descriptor of pack2pad.
 *
 *  @param[in]  desc
 *    Input. Descriptor of pack2pad operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */

cnnlStatus_t CNNL_WIN_API
cnnlDestroyPadPackedSequenceDescriptor(cnnlPadPackedSequenceDescriptor_t desc);

// Group:Pack2Pad
/*!
 *  @brief A function.
 *
 *  The pack2pad function pads sequence length to max_seq_len with pad
 *  value which can be set.
 *
 *  **Formula**
 *
 *  This operation contains the following steps:
 *
 *  1. Pad seq_len to max_seq_len with pad value if max_seq_len is not less than seq_len.
 *
 *  2. Output max_seq_len if max_seq_len is less than seq_len.
 *
 *  **Example**
 *
 *  @verbatim
 *   Dimension of packed_tensor: [1, valid_word_num, hidden_size].
 *
 *   Dimension of pad_value: [1].
 *
 *   Dimension of seq_lengths: [batch_num].
 *
 *   Dimension of batch_sizes: [max_seq_len].
 *
 *   Dimension of unsorted_indices: [batch_num].
 *
 *   Dimension of output: [batch_num, max_seq_len, hidden_size].
 *  @endverbatim
 *
 *  **DataType**
 *
 *  - packed_tensor: float, half, int16, int8.
 *  - pad_value: float, half, int16, int8.
 *  - seq_lengths: int32.
 *  - batch_sizes: int32.
 *  - unsorted_indices: int32.
 *  - output: float, half, int16, int8.
 *
 *  **Scale Limitation**
 *
 *  1. hidden_size supports [1, 1024].
 *
 *  2. max_seq_len is not less than seq_length in any batch.
 *
 *  @param[in]  handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           pack2pad operation.
 *  @param[in]  desc
 *    Input. A descriptor of pack2pad.
 *  @param[in]  packed_tensor_desc
 *    Input. A descriptor of packed_tensor.
 *  @param[in]  packed_tensor
 *    Input. Device pointer points to the packed data.
 *  @param[in]  pad_value_desc
 *    Input. A descriptor of pad_value tensor.
 *  @param[in]  pad_value
 *    Input. Device pointer points to the pad_value.
 *  @param[in]  seq_lengths_desc
 *    Input. A descriptor of seq_lengths tensor.
 *  @param[in]  seq_lengths
 *    Input. Device pointer points to the seq_lengths.
 *  @param[in]  batch_sizes_desc
 *    Input. A descriptor of batch_sizes tensor.
 *  @param[in]  batch_sizes
 *    Input. Device pointer points to the batch_sizes.
 *  @param[in]  unsorted_indices_desc
 *    Input. A descriptor of unsorted_indices tensor.
 *  @param[in]  unsorted_indices
 *    Input. Device pointer points to the unsorted_indices.
 *  @param[in]  workspace
 *    Input. The pointer to data address of workspace.
 *  @param[in]  workspace_size
 *    Input. The value of workspace_size.
 *  @param[out]  padded_tensor_desc
 *    Output. An array of cnnlTensorDescriptors which holds dimension, data type, and layout of
 *    padded_tensor. The shape of padded_tensor is [batch, max_seq_len, hidden_size].
 *  @param[out]  padded_tensor
 *    Output. Device pointer points to output space.
 *  @retval CNNL_STATUS_SUCCESS = 0
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM = 3
 *    One or more of the following conditions are encountered:
 *    - handle is NULL.
 *    - packed_tensor is NULL.
 *    - pad_value is NULL.
 *    - padded_tensor is NULL.
 *    - Dims are invalid.
 */
cnnlStatus_t CNNL_WIN_API
cnnlPadPackedSequence(
    cnnlHandle_t handle,
    const cnnlPadPackedSequenceDescriptor_t desc,
    const cnnlTensorDescriptor_t packed_tensor_desc,
    const void *packed_tensor,
    const cnnlTensorDescriptor_t pad_value_desc,
    const void *pad_value,
    const cnnlTensorDescriptor_t seq_lengths_desc,
    const void *seq_lengths,
    const cnnlTensorDescriptor_t batch_sizes_desc,
    const void *batch_sizes,
    const cnnlTensorDescriptor_t unsorted_indices_desc,
    const void *unsorted_indices,
    const cnnlTensorDescriptor_t padded_tensor_desc,
    void *padded_tensor,
    void *workspace,
    size_t workspace_size);

// Group:Pack2Pad
/*!
 *  @brief A function.
 *  This function retrieves extra space size needed in Pack2pad operation.
 *
 *  Some functions need to be called before this function. The dependence is as follow:
 *
 *  1.cnnlCreatePadPackedSequenceDescriptor().
 *
 *  @param[in] handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           Pack2pad operations.
 *  @param[in] desc
 *    Input. The descriptor of pack2pad.
 *  @param[out] size
 *    Output. Extra space size needed in Pack2pad operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions are met:
 *    - The handle is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlGetPadPackedSequenceWorkspaceSize(cnnlHandle_t handle,
                                      const cnnlPadPackedSequenceDescriptor_t desc,
                                      size_t *size);
/******************************************************************************
 * Cambricon CNNL OP: Pq Search
 ******************************************************************************/
// Group:Ivfpq
/*!
 *  @brief A function
 *
 *  This function is one part of the IVFPQ (Invert File System Product Quantization) algorithm.
 *  IVFPQ is used to search and select the nearest feature vectors from the database based on query
 *  vectors. It contains three sub-operators: flat search, residual-computing and pq search.
 *  This function implements the pq search with residual-computing and the pq search without
 *  residual-computing algorithm on MLU.
 *
 *  **Formula**
 *
 *  1. Reorder(optional)
 *
 *    Arrange nprobe buckets in descending order according to the number of vectors in each bucket.
 *
 *  2. Compute residual(optional)
 *
 *    Subtract coarse centers from the query vector to obtain the corresponding
 *    residual vectors.
 *
 *  3. Generate look-up table.
 *
 *    Compute L2-distance between input query(or residual query) and input code_book,
 *    then store the distance as the look-up table:
 *
 *      look_up_table = computeL2Distance(query, code_book).
 *
 *  4. Search and find nearest k-features from lib.
 *
 *    In previous step of IVFPQ training, original database is quantified into [lib] based on
 *    [code_book]. [lib] consists of [nlist] coarse centers. Flat search selects
 *    the most relevant [nprobe] centers from the [lib], using the input [query].
 *    This operation computes the distance between [residual_query] and features related to those selected
 *    centers, and output the indices and distances of the nearest k-features from [ntotal] features.
 *
 *      topk_output = searchAndTopk(look_up_table, lib)
 *
 *  **DataType**
 *
 *    - Input: float(query), float(residual_query), float(coarse_center), float(code_book).
 *    - Input: int32(lib_index_size) int32(lib), int32(lib_index).
 *    - Input: int32(probe_index), int32(search_mode).
 *    - Output: float(topk_output_value), int32(topk_output_index).
 *
 *  **Scale Limitation**
 *
 *    - ntotal represents the number of features in lib, must be no larger than
 *      (pow(2,30) - 1) / 32.
 *    - nlist represents the number of segments that lib is divided into during training, must be
 *      no larger than [ntotal].
 *    - code_book_desc->dims[0] represents the number of cluster centers(ksub), must be 256.
 *    - query_desc->dims[1] represents the length of query and code_book vector(D),
 *      can be 256, 512, 768, 1024.
 *    - code_book_desc->dims[1] represents the number of segments of code_book vector(m),
 *      can be 32 and 64.
 *    - code_book_desc->dims[2] represents the sub segment length of code_book(dsub).
 *      The product of m and dsub must be equal to D.
 *    - Users must cnrtMalloc np * D * sizeof(float) memory in device for residual_query at least,
 *      which means np must be the maximum of nprobe and the number of valid cores of
 *      the current board.
 *    - When search_mode is 0 or 1, nlist and nprobe must be 1.
 *    - When search_mode is 2, both nlist and nprobe must be greater than 1,
 *      and nlist must be greater than nprobe.
 *
 *  **Reference**
 *
 *    - http://github.com/facebookresearch/faiss
 *
 *  @param[in] handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           IVFPQ operation.
 *  @param[in] query_desc
 *    Input. Descriptor of query, the dimension is [batch, D].
 *  @param[in] query
 *    Input. An MLU tensor, a pointer to device query data.
 *  @param[in] residual_query_desc
 *    Input. Descriptor of residual query, the dimension is [nprobe, D].
 *  @param[in] residual_query
 *    Input. An MLU tensor, a pointer to device residual query data.
 *  @param[in] coarse_center_desc
 *    Input. Descriptor of coarse center, the dimension is [nlist, D].
 *  @param[in] coarse_center
 *    Input. An MLU tensor, a pointer to device coarse center data.
 *  @param[in] code_book_desc
 *    Input. Descriptor of codebook, the dimension is [ksub, m, dsub].
 *  @param[in] code_book
 *    Input. An MLU tensor, a pointer to device code_book data.
 *  @param[in] lib_index_size_desc
 *    Input. Descriptor of the size of nlist buckets, the dimension is [nlist].
 *  @param[in] lib_index_size
 *    Input. An MLU tensor, a pointer to device nlist bucket size data.
 *  @param[in] lib_desc
 *    Input. Descriptor of the lib data of nlist bucket, the dimension is [nlist].
 *  @param[in] lib
 *    Input. An MLU tensor, a pointer to device lib data. lib is the database which contains all
 *           feature vectors to search. lib is divided into [nlist] segments with different sizes
 *           during training. The size of every lib segments must be equal to the product of
 *           m and the size of corresponding segment of lib_index_size.
 *  @param[in] lib_index_desc
 *    Input. Descriptor of lib index, the dimension is [nlist].
 *  @param[in] lib_index
 *    Input. An MLU tensor, a pointer to device lib index data. lib_index stores the index of
 *           every lib feature in the original database. Each feature has a unique index.
 *           lib_index is also divided into [nlist] segments according to the partition of lib.
 *           lib_index_size is defined to store the size of every lib_index segments.
 *  @param[in] probe_index_desc
 *    Input. Descriptor of probe index, the dimension is [batch, nprobe].
 *  @param[in] probe_index
 *    Input. An MLU tensor, a pointer to device probe index data. probe_index stores the indices of
 *           selected segments from coarse center.
 *  @param[out] topk_output_value_desc
 *    Output. Descriptor of topk output value, the dimension is [batch, topk_k].
 *  @param[out] topk_output_value
 *    Output. An MLU tensor, a pointer to device topk output value data. topk_output_value stores
 *            the nearest topk_k distances with respect to query.
 *  @param[out] topk_output_index_desc
 *    Output. Descriptor of topk output index, the dimension is [batch, topk_k].
 *  @param[out] topk_output_index
 *    Output. An MLU tensor, a pointer to device topk output index data. topk_output_index stores
 *            the indexes of topk_k nearest features from lib_index.
 *  @param[in] search_mode
 *    Input. Descriptor of search mode. search_mode can be 0(pq_search_with_residual),
 *           1(pq_search_without_residual), 2(ivfpq_search_with_residual).
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_ARCH_MISMATCH
 *    - MLU task type is not supported (currently only union1/2/4/8 task is supported).
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions must be met:
 *    - handle is NULL.
 *    - query_desc is NULL.
 *    - query is NULL.
 *    - residual_query_desc is NULL.
 *    - residual_query is NULL.
 *    - coarse_center_desc is NULL.
 *    - coarse_center is NULL.
 *    - code_book_desc is NULL.
 *    - code_book is NULL.
 *    - lib_index_size_desc is NULL.
 *    - lib_index_size is NULL.
 *    - lib_desc is NULL.
 *    - lib is NULL.
 *    - lib_index_desc is NULL.
 *    - lib_index is NULL.
 *    - nprobe_index_desc is NULL.
 *    - nprobe_index is NULL.
 *    - topk_output_value_desc is NULL.
 *    - topk_output_value is NULL.
 *    - topk_output_index_desc is NULL.
 *    - topk_output_index is NULL.
 *    - search_mode is not equal to 0/1/2.
 *    - tensor dim does not match.
 */
cnnlStatus_t CNNL_WIN_API
cnnlPqSearch(cnnlHandle_t handle,
             const cnnlTensorDescriptor_t query_desc,
             const void *query,
             const cnnlTensorDescriptor_t residual_query_desc,
             void *residual_query,
             const cnnlTensorDescriptor_t coarse_center_desc,
             const void *coarse_center,
             const cnnlTensorDescriptor_t code_book_desc,
             const void *code_book,
             const cnnlTensorDescriptor_t lib_index_size_desc,
             const void *lib_index_size,
             const cnnlTensorDescriptor_t lib_desc,
             const void **lib,
             const cnnlTensorDescriptor_t lib_index_desc,
             const void **lib_index,
             const cnnlTensorDescriptor_t probe_index_desc,
             void *probe_index,
             const cnnlTensorDescriptor_t topk_output_value_desc,
             void *topk_output_value,
             const cnnlTensorDescriptor_t topk_output_index_desc,
             void *topk_output_index,
             int search_mode);

/******************************************************************************
 * Cambricon CNNL OP: Pad2Pack
 ******************************************************************************/
/*! The descriptor of Pad2Pack.
 * You can use cnnlCreatePackPaddedSequenceDescriptor() and
 * cnnlDestroyPackPaddedSequenceDescriptor() to create and destroy the descriptor
 * respectively.
 */
typedef struct cnnlPackPaddedSequenceStruct *cnnlPackPaddedSequenceDescriptor_t;

// Group:Pad2Pack
/*!
 *  @brief A function.
 *
 *  This function is used to create a descriptor of pad2pack,
 *  which contains enforce_sorted.
 *
 *  @param[in]  desc
 *    Input. Descriptor of pad2pack operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_ALLOC_FAILED
 *    The function fails to allocate memory for the pad2pack descriptor.
 */
cnnlStatus_t CNNL_WIN_API
cnnlCreatePackPaddedSequenceDescriptor(cnnlPackPaddedSequenceDescriptor_t *desc);

// Group:Pad2Pack
/*!
 *  @brief A function.
 *
 *  This function is used to destroy a descriptor of pad2pack.
 *
 *  @param[in]  desc
 *    Input. Descriptor of pad2pack operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */

cnnlStatus_t CNNL_WIN_API
cnnlDestroyPackPaddedSequenceDescriptor(cnnlPackPaddedSequenceDescriptor_t desc);

// Group:Pad2Pack
/*!
 *  @brief A function.
 *
 *  The pad2pack function gets valid tokens of a padded tensor and rearranges to a packed tensor.
 *
 *  Pack seq_lengths to seq_len if seq_lengths is not more than seq_len.
 *
 *  **Example**
 *
 *  @verbatim
 *   Dimension of padded_tensor: [batch_num, seq_len, hidden_size].
 *
 *   Dimension of seq_lengths: [batch_num].
 *
 *   Dimension of batch_sizes: [seq_len].
 *
 *   Dimension of sorted_indices: [batch_num].
 *
 *   Dimension of unsorted_indices: [batch_num].
 *
 *   Dimension of packed_tensor: [1, valid_word_num, hidden_size].
 *  @endverbatim
 *
 *  **DataType**
 *
 *  - padded_tensor: float, half, int16, int8.
 *  - seq_lengths: int32.
 *  - batch_sizes: int32.
 *  - sorted_indices: int32.
 *  - unsorted_indices: int32.
 *  - packed_tensor: float, half, int16, int8.
 *
 *  **Attention: **
 *
 *  - The data types of padded_tensor and packed_tensor must be the same.
 *
 *  - The dimensions of padded_tensor and pakced_tensor must be the same, which is three-dimensional.
 *
 *  - The layouts of padded_tensor and packed_tensor must be same, which is NTC layout.
 *
 *  **Scale Limitation**
 *
 *  1. hidden_size supports [1, 1024].
 *
 *  2. seq_len is not less than seq_lengths in any batch.
 *
 *  @param[in]  handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           pad2pack operation.
 *  @param[in]  desc
 *    Input. A descriptor of pad2pack.
 *  @param[in]  padded_tensor_desc
 *    Input. A descriptor of padded_tensor.
 *  @param[in]  padded_tensor
 *    Input. Device pointer points to the padded data.
 *  @param[in]  seq_lengths_desc
 *    Input. A descriptor of seq_lengths tensor.
 *  @param[in]  seq_lengths
 *    Input. Device pointer points to the seq_lengths.
 *  @param[in]  batch_sizes_desc (not used now)
 *    Input. A descriptor of batch_sizes tensor.
 *  @param[out]  batch_sizes (not used now)
 *    Output. Device pointer points to the batch_sizes.
 *  @param[in]  sorted_indices_desc (not used now)
 *    Input. A descriptor of sorted_indices tensor.
 *  @param[out]  sorted_indices (not used now)
 *    Output. Device pointer points to the sorted_indices.
 *  @param[in]  unsorted_indices_desc (not used now)
 *    Input. A descriptor of unsorted_indices tensor.
 *  @param[out]  unsorted_indices (not used now)
 *    Output. Device pointer points to the unsorted_indices.
 *  @param[in]  workspace
 *    Input. The pointer to data address of workspace.
 *  @param[in]  workspace_size
 *    Input. The value of workspace_size.
 *  @param[in]  packed_tensor_desc
 *    Input. An array of cnnlTensorDescriptors which holds dimension, data type, and layout of
 *    packed_tensor. The shape of packed_tensor is [1, valid_word_num, hidden_size].
 *  @param[out]  packed_tensor
 *    Output. Device pointer points to the packed_tensor.
 *  @retval CNNL_STATUS_SUCCESS = 0
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM = 3
 *    One or more of the following conditions are encountered:
 *    - handle is NULL.
 *    - packed_tensor is NULL.
 *    - padded_tensor is NULL.
 *    - Dims are invalid.
 */
cnnlStatus_t CNNL_WIN_API
cnnlPackPaddedSequence(
    cnnlHandle_t handle,
    const cnnlPackPaddedSequenceDescriptor_t desc,
    const cnnlTensorDescriptor_t padded_tensor_desc,
    const void *padded_tensor,
    const cnnlTensorDescriptor_t seq_lengths_desc,
    const void *seq_lengths,
    const cnnlTensorDescriptor_t packed_tensor_desc,
    void *packed_tensor,
    const cnnlTensorDescriptor_t batch_sizes_desc,
    const void *batch_sizes,
    const cnnlTensorDescriptor_t sorted_indices_desc,
    const void *sorted_indices,
    const cnnlTensorDescriptor_t unsorted_indices_desc,
    const void *unsorted_indices,
    void *workspace,
    size_t workspace_size);

// Group:Pad2Pack
/*!
 *  @brief A function.
 *  This function retrieves extra space size  needed in Pad2pack operation.
 *
 *  Some functions need to be called before this function. The dependence is as follow:
 *
 *  1.cnnlCreatePackPaddedSequenceDescriptor().
 *
 *  @param[in] handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           Pad2pack operations.
 *  @param[in] desc
 *    Input. A descriptor of pad2pack.
 *  @param[out] size
 *    Output. Extra space size needed in Pad2pack operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions are met:
 *    - The handle is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlGetPackPaddedSequenceWorkspaceSize(cnnlHandle_t handle,
                                       const cnnlPackPaddedSequenceDescriptor_t desc,
                                       size_t *size);

/******************************************************************************
 * Cambricon CNNL OP: PqAdd
 ******************************************************************************/
// Group:Ivfpq
/*!
 *  @brief A function
 *
 *  This function is one part of the IVFPQ-ADD (Invert File System Product Quantization) algorithm.
 *  IVFPQ-ADD is used to add features to the library.
 *
 *  **Formula**
 *
 *  This operation contains the following steps:
 *
 *  1. Get residual vector.
 *
       @verbatim
        for batch_idx in range(len(add)):
            get corresponding sub code index as nlist_idx
            residual_add[batch_idx] = add[batch_idx] - coarse_center[nlist_idx]
       @endverbatim
 *
 *  2. Encode the residual vector.
 *
 *    Compute L2-distance between input queries and input codebook, then select minimum value's index
 *    as code:
 *
      @verbatim
       distances = computeL2Distance(insert_vec, codebook).
       code = argmin(distances).
      @endverbatim
 *
 *  3. Add codes to library.
 *
 *    [src_lib] consists of [nlist] Level 1 cluster centroids. codes will be added to corresponding
 *    sub library:
 *
 *      src_lib[nlist_index].push_back(codes).
 *
 *  **Only supports MLU370**
 *
 *  **DataType**
 *
 *    - input: float(add), float(residual_add), int32(add_ids), float(coarse_center), float(codebook).
 *    - input: uint8(src_lib), int32(src_lib_ids), int32(every_list_size).
 *    - input: int32(list_ids_for_add), int32(insert_num_per_list).
 *    - output: int32(every_list_size),uint8(dst_lib),int32(dst_lib_ids).
 *
 *  **Scale Limitation**
 *
 *    - [ntotal] represents the number of features in codes, must be no larger than
 *      (pow(2,30) - 1) / 32.
 *    - [nlist] represents the number of segments that codes is divided into during training,
 *      must be no larger than [ntotal].
 *    - \p code_book_desc->dims[0] represents the number of cluster centroids, must be 256.
 *    - \p code_book_desc->dims[1] represents the number of segments of code_book vector(m),
 *      can be 32 and 64.
 *    - \p code_book_desc->dims[2] represents the sub segment length of code_book(dsub).
 *      The product of m and dsub must be equal to D.
 *    - \p add_desc->dims[0] represents the number of data to be inserted, must be
 *      no more than 57360.
 *    - \p add_desc->dims[1] represents the length of data to be inserted, must be one of [256, 512, 768, 1024].
 *    - ntotal = sum(every_list_size[i]), 0 <= i <= nlist - 1.
 *    - add_desc->dims[0] = add_ids_desc->dims[0].
 *    - residual_add_desc and resisual_add not be NULL if mode == 1
 *
 *  @note
 *  - None.
 *
 *  @par Requirements
 *  - None.
 *
 *  **Reference**
 *
 *  http://github.com/facebookresearch/faiss
 *
 *  @param[in] handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           PqAdd operation.
 *  @param[in] add_desc
 *    Input. The descriptor of add tensor, the dimension is [batch, d].
 *  @param[in] add
 *    Input. Pointer to the MLU memory that stores the input data to be inserted.
 *  @param[in] residual_add_desc
 *    Input. The descriptor of residual_add tensor, The dimension is same with add tensor.
 *  @param[in] residual_add
 *    Input. Pointer to the MLU memory that stores the residual input data.
 *  @param[in] add_ids_desc
 *    Input. The descriptor of add_ids tensor, the dimension is [batch].
 *  @param[in] add_ids
 *    Input. An MLU tensor, a pointer to ID of input data on device.
 *    Insert_vec_ids is the id of each feature to be inserted, each feature has a unique ID.
 *  @param[in] coarse_center_desc
 *    Input. The descriptor of coarse_center, the dimension is [nlist, d].
 *  @param[in] coarse_center
 *    Input. Pointer to the MLU memory that stores the level-1 cluster centroids
 *  @param[in] code_book_desc
 *    Input. The descriptor of code_book tensor, the dimension is [ksub, m, dsub].
 *  @param[in] code_book
 *    Input. Pointer to the MLU memory that stores the level-2 cluster centroids
 *  @param[in] src_lib_desc
 *    Input. The descriptor of src_lib tensor, the dimension is [nlist].
 *  @param[in] src_lib
 *    Input. Pointer to the MLU memory that stores an array of pointers to the device memory of sub src code lib tensor.
 *           Src code lib is the database which contains all feature vectors. Src code is divided into [nlist] segments
 *           with different sizes. Each segment should has shape as [m,align(n)] and align value depends on user.
 *  @param[in] src_lib_ids_desc
 *    Input. The descriptor of src_lib_ids tensor, the dimension is [nlist].
 *  @param[in] src_lib_ids
 *    Input. Pointer to the MLU memory that stores an array of pointers to the device memory of sub src code ids tensor.
 *           Src code ids stores the ID of every feature vector in the src code lib, and each feature has a unique id.
 *           Code ids is also divided into [nlist] segments according to the partition of code lib and nlist_id_size is
 *           defined to store the size of every code ids segments. Each segment should has shape as [align(n)], align
 *           value should be same as sub code lib.
 *  @param[in] dst_lib_desc
 *    Input. The descriptor of dst_lib tensor, the dimension is same with src_lib_desc.
 *  @param[out] dst_lib
 *    Output. Pointer to the MLU memory that stores an array of pointers to the device memory of sub dst code lib tensor.
 *           Dst code lib'shape is same with src lib, but sub code lib's device pointer may differ from src code lib. dst
 *           code is divided into [nlist] segments same as src code, and each segment'size depends on src sub code size
 *           and inserted data size.
 *  @param[in] dst_lib_ids_desc
 *    Input. The descriptor of dst_lib_ids tensor, the dimension is same with src_lib_ids_desc.
 *  @param[out] dst_lib_ids
 *    Output. Pointer to the MLU memory that stores an array of pointers to the device memory of sub dst code ids tensor.
 *           Dst code ids'shape is same with src code ids, but sub code ids's device pointer may differ from src code ids.
 *           Dst code ids is divided into [nlist] segments same as src code ids, and each segment' size depends on src sub ids
 *           size and inserted data size.
 *  @param[in] list_ids_for_add_desc
 *    Input. The descriptor of list_ids_for_add tensor. The dimension is [list_num_for_add], and list_num_for_add is the number of the
 *           buckets to be insertd into feature data.
 *  @param[in] list_ids_for_add
 *    Input. Pointer to the MLU memory that contains sub code lib index to insert, which should be sorted from smallest to biggest.
 *  @param[in] insert_num_per_list_desc
 *    Input. The descriptor  of insert_num_per_list tensor, the dimension is [list_num_for_add].
 *  @param[in] insert_num_per_list
 *    Input. Pointer to the MLU memory that contains num for insert vector for each sub code lib whose order should be consistent with
 *           list_ids_for_add.
 *  @param[in] every_list_size_desc
 *    Input. The descriptor of every_list_size tensor, the dimension is [nlist].
 *  @param[in,out] every_list_size
 *    Input/output. Pointer to the MLU memory that contains each sub code lib's size.
 *  @param[in] mode
 *    Input. mode should be one of [0, 1, 2].
 *           mode 0 means pq algorithm with residual input calculated inside.
 *           mode 1 means pq algorithm with residual input not calculated inside.
 *           mode 2 means ivfpq algorithm with residual input calculated inside.
 *           If mode equals 0 or 1, nlist shoule equals 1.
 *  @par Return
 *  - ::CNNL_STATUS_SUCCESS, ::CNNL_STATUS_BAD_PARAM
 */

cnnlStatus_t CNNL_WIN_API
cnnlPqAdd(cnnlHandle_t handle,
             const cnnlTensorDescriptor_t add_desc,
             const void *add,
             const cnnlTensorDescriptor_t residual_add_desc,
             const void *residual_add,
             const cnnlTensorDescriptor_t add_ids_desc,
             const void *add_ids,
             const cnnlTensorDescriptor_t coarse_center_desc,
             const void *coarse_center,
             const cnnlTensorDescriptor_t code_book_desc,
             const void *code_book,
             const cnnlTensorDescriptor_t src_lib_desc,
             void **src_lib,
             const cnnlTensorDescriptor_t src_lib_ids_desc,
             void **src_lib_ids,
             const cnnlTensorDescriptor_t dst_lib_desc,
             void **dst_lib,
             const cnnlTensorDescriptor_t dst_lib_ids_desc,
             void **dst_lib_ids,
             const cnnlTensorDescriptor_t list_ids_for_add_desc,
             const void *list_ids_for_add,
             const cnnlTensorDescriptor_t insert_num_per_list_desc,
             const void *insert_num_per_list,
             const cnnlTensorDescriptor_t every_list_size_desc,
             void *every_list_size,
             int mode);

/******************************************************************************
 * Cambricon CNNL OP: PqRemove
 ******************************************************************************/
// Group:Ivfpq
/*!
 *  @brief A function
 *
 *  This function is one part of the IVFPQ-REMOVE (Invert File System Product Quantization) algorithm.
 *  IVFPQ-REMOVE is used to delete features from the library. It contains two sub-operators: finding
 *  the id of the bucket where the data to be deleted is located and the index of the data to be
 *  deleted in the bucket, and updating library based on id and index found.
 *  This function implements updating library by replacing the code and id to be removed with last
 *  code & id in the lib and erasing the original last code and id.
 *
 *  **Formula**
 *
 * 1. Replace the code & id to be removed with last code & id in the lib.
 *
      @verbatim
       codes[nlist_idx][idx] = code[nlist_idx][-1]
       code_ids[nlist_idx][idx] = code_ids[nlist_idx][-1]
      @endverbatim
 *
 * 2. Erase the original last code & id.
 *
      @verbatim
       codes = codes[:-1]
       code_ids = code_ids[:-1]
      @endverbatim
 *
 *  **Only supports MLU370**
 *
 *  **DataType**
 *
 *    - input: uint8(codes), int32(code_ids), int32(every_list_size).
 *    - input: int32(nlist_idx), int32(offset).
 *    - output: int32(every_list_size).
 *
 *  **Scale Limitation**
 *
 *    - codes_desc->dims[0] represents the number of segment of one feature vector, must be 32 or 64.
 *
 *  **Reference**
 *
 *  http://github.com/facebookresearch/faiss
 *
 *  @param[in] handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           PqRemove operation.
 *  @param[in] codes_desc
 *    Input. The descriptor of codes tensor, the dimension is [m, n].
 *  @param[in,out] codes
 *    Input. Pointer to the MLU memory that stores target bucket codes data on device.
 *  @param[in] code_ids_desc
 *    Input. The descriptor of ids tensor, the dimension is [n].
 *  @param[in,out] code_ids
 *    Input. An MLU tensor, a pointer to ID of target bucket codes data on device.
 *  @param[in] every_list_size_desc
 *    Input. The descriptor of every_list_size tensor, the dimension is [nlist].
 *  @param[in,out] every_list_size
 *    Input/output. Pointer to the MLU memory that contains each bucket codes's size.
 *  @param[in]  nlist_idx
 *    Input. Index of target bucket codes whose feature will be removed. The Index should be in [0, nlist).
 *  @param[in]  offset
 *    Input. Feature offset in target bucket. The offset should be in [0, n).
 *  @par Return
 *  - ::CNNL_STATUS_SUCCESS, ::CNNL_STATUS_BAD_PARAM
 */

cnnlStatus_t CNNL_WIN_API
cnnlPqRemove(cnnlHandle_t handle,
                const cnnlTensorDescriptor_t codes_desc,
                uint8_t *codes,
                const cnnlTensorDescriptor_t code_ids_desc,
                int *code_ids,
                const cnnlTensorDescriptor_t every_list_size_desc,
                int *every_list_size,
                int nlist_idx,
                int offset);

/******************************************************************************
 * Cambricon CNNL OP: dlrm interact
 ******************************************************************************/
/*! The descriptor of the dlrm interact operation that holds interact attributes
 *  including the interact_mode and enable_self_interact.
 *
 *  You need to call the ::cnnlCreateDlrmInteractDescriptor function
 *  to create a descriptor, and call the ::cnnlSetDlrmInteractDescriptor function
 *  to set the attributes. Also, you need to destroy the descriptor at the end
 *  with the ::cnnlDestroyDlrmInteractDescriptor function.
 */
typedef struct cnnlDlrmInteractStruct *cnnlDlrmInteractDescriptor_t;

//! @brief An enum.
/*! Enumeration variables describe the interact modes.*/
typedef enum {
  CNNL_DLRM_INTERACT_DOT = 0,
  /*!< Performs batched matmul and triled select operations after concatenating x and ly.*/
  CNNL_DLRM_INTERACT_CAT = 1,
  /*!< Only concatenates x and ly.*/
} cnnlDlrmInteractMode_t;

// Group:dlrm interact
/*!
 *  @brief A function.
 *
 *  This function is used to create a dlrm interact descriptor.
 *
 *  @param[in] dlrm_interact_desc
 *    Input.  A pointer to the dlrm_interact descriptor.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *      - dlrm_interact_desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlCreateDlrmInteractDescriptor(cnnlDlrmInteractDescriptor_t *dlrm_interact_desc);

// Group:dlrm interact
/*!
 *  @brief A function.
 *
 *  This function is used to destroy a dlrm interact descriptor.
 *
 *  **API Dependency**
 *
 *  This function must be used if you call the ::cnnlCreateDlrmInteractDescriptor function.
 *
 *  @param[in] dlrm_interact_desc
 *    Input.  A dlrm interact descriptor.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_EXECUTION_FAILED
 *    One of the following conditions are met:
 *      - dlrm_interact_desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlDestroyDlrmInteractDescriptor(cnnlDlrmInteractDescriptor_t dlrm_interact_desc);

// Group:dlrm interact
/*!
 *  @brief A function.
 *
 *  This function is used to set the dlrm interact descriptor with parameters.
 *
 *  **API Dependency**
 *
 *  1. Call ::cnnlCreateDlrmInteractDescriptor before using this function.
 *
 *  2. Call ::cnnlDestroyDlrmInteractDescriptor when the dlrm_interact_desc is no longer needed.
 *
 *  @param[in] dlrm_interact_desc
 *    Input.  A dlrm interact descriptor.
 *  @param[in] interact_mode
 *    Input.  Controls the operations to be applied. See ::cnnlDlrmInteractMode_t.
 *  @param[in] enable_self_interact
 *    Input.  The flag of whether to include principal diagonal in the triled select operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions are met:
 *    - dlrm_interact_desc is NULL.
 *    - parameters do not meet requirements.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetDlrmInteractDescriptor(cnnlDlrmInteractDescriptor_t dlrm_interact_desc,
                              const cnnlDlrmInteractMode_t interact_mode,
                              const bool enable_self_interact);

// Group:dlrm interact
/*!
 *  @brief A function.
 *  This function is used to get extra space size that needed in dlrm interact operation.
 *
 *  @param[in] dlrm_interact_desc
 *    Input.  The dlrm interact descriptor.
 *  @param[in] x_desc
 *    Input.  Tensor descriptor of input x.
 *  @param[in] ly_num
 *    Input.  The number of sparse features.
 *  @param[out] size
 *    Output. Pointer to the size of workspace.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions are met:
 *    - dlrm_interact_desc is NULL.
 *    - x_desc is NULL.
 *    - ly_desc is NULL.
 *    - size is NULL.
 *    - ly_num is invalid.
 */
cnnlStatus_t CNNL_WIN_API
cnnlGetDlrmInteractWorkspaceSize(const cnnlDlrmInteractDescriptor_t dlrm_interact_desc,
                                 const cnnlTensorDescriptor_t x_desc,
                                 const cnnlTensorDescriptor_t ly_desc,
                                 const int ly_num,
                                 size_t *size);

// Group:dlrm interact
/*!
 * @brief A function. This function performs interactions between the dense feature and sparse features
 *  from Deep Learning Recommendation Model.
 *
 * **Formula**
 *
 *  This function contains two types of operations:
 *
 *  - If interact_mode = CNNL_DLRM_INTERACT_DOT
 *
      @verbatim
       output = concat([x] + lys, axis=1)
      @endverbatim
 *
 *  - If interact_mode = CNNL_DLRM_INTERACT_CAT
 *
      @verbatim
       C = concat([x] + lys, axis=1)
       R = reshape(C, (batch_size, ly_num + 1, embedding_size))
       D = bmm(r, transpose(R, (0, 2, 1))
       S = bts(D)
       output = concat([x, S], axis=1)
       - bmm: Batched Matmul.
       - bts: Batched Triled Select. Selects the tril of each matrix contained in a 3-D tensor.
       The attribute enable_self_interact controls if include the principal diagonal.
      @endverbatim
 *
 *  **Example**
 *
 *  @verbatim
     Dimension of x: [batch_size, embedding_size].

     Dimension of each ly: [batch_size, embedding_size].

     Dimension of C: [batch_size, (ly_num + 1) * embedding_size].

     Dimension of R: [batch_size, ly_num + 1, embedding_size].

     Dimension of D: [batch_size, ly_num + 1, ly_num + 1].

     Dimension of S: [batch_size, cs].
       cs = (ly_num + 1) * (ly_num + 2) / 2, if enable_self_interact = true;
       cs = ly_num * (ly_num + 1) / 2, if enable_self_interact = false.

     Dimension of output: [batch_size, embedding_size + cs].
 *  @endverbatim
 *
 * **Datatype**
 *
 *  - input: float, half.
 *
 *  - output: float, half.
 *
 * **Attention:**
 *
 *  - Datatype of input and output must be the same.
 *
 *  - Only supports MLU370.
 *
 * **Scale Limitation**
 *
 *  According to dlrm_interact op, the parameters must satisfy following conditions:
 *
 *  batch > 0.
 *
 *  0 < ly_num <= 128.
 *
 *  0 < embedding_size <= 512.
 *
 *  @param[in] handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           dlrm_interact operation.
 *  @param[in] x_desc
 *    Input. A descriptor of dense feature tensor x, contains dimension of [batch_size, embedding_size].
 *  @param[in] x
 *    Input. Pointer to the MLU memory that stores the x tensor.
 *  @param[in] ly_desc
 *    Input. A descriptor of each sparse feature tensor ly, contains dimension of [batch_size, embedding_size].
 *  @param[in] lys
 *    Input. A host array contains pointers to MLU memory that store the ly tensors.
 *  @param[in] ly_num
 *    Input. The number of sparse features.
 *  @param[in] workspace
 *    Input.  A pointer to the MLU memory that is used as an extra workspace.
 *  @param[in] workspace_size
 *    Input. The size of extra space.
 *  @param[out] output_desc
 *    Output. A descriptor of output tensor.
 *  @param[out] output
 *    Output.  A pointer to the MLU memory that stores the output tensor.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions must be met:
 *    - handle is NULL.
 *    - interact_desc is NULL.
 *    - x_desc is NULL.
 *    - x is NULL.
 *    - ly_desc is NULL.
 *    - lys is NULL.
 *    - lys[i] is NULL, where i is in the range of [0, ly_num-1].
 *    - workspace is invalid.
 *    - output_desc is NULL.
 *    - output is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlDlrmInteract(cnnlHandle_t handle,
                 const cnnlDlrmInteractDescriptor_t interact_desc,
                 const cnnlTensorDescriptor_t x_desc,
                 const void *x,
                 const cnnlTensorDescriptor_t ly_desc,
                 const void *const lys[],
                 const int ly_num,
                 void *workspace,
                 size_t workspace_size,
                 const cnnlTensorDescriptor_t output_desc,
                 void *output);


/******************************************************************************
 * Cambricon CNNL OP: TransformerFeedForward
 ******************************************************************************/
/*! The descriptor of the transformer_feed_forward operation that holds feed_forward information
 *  including \b post_scale, \b layernorm_eps, \b compute_dtype, and \b layernorm_structure
 *
 *  You need to call the ::cnnlCreateTransformerFeedForwardDescriptor function
 *  to create a descriptor, and call the ::cnnlSetTransformerFeedForwardDescriptor
 *  to set the information of the feed_forward operation to the descriptor.
 *  Also, you need to destroy the Cambricon CNNL context at the end with the
 *  ::cnnlDestroyTransformerFeedForwardDescriptor function.
 */
typedef struct cnnlTransformerFeedForwardStruct *cnnlTransformerFeedForwardDescriptor_t;

/*! The descriptor of the quantization funciton of transformer_feed_forward operation.
    Not implemented yet.
 */
typedef struct cnnlTransformerFeedForwardQuantizeStruct
                *cnnlTransformerFeedForwardQuantizeDescriptor_t;

// Group:TransformerFeedForward
/*!
 *  @brief A function.
 *
 *  The FeedForwardNetwork layer in Transformer network and its derivative network.
 *
 *  **Formula**
 *
 *  This operation contains the following steps:
 *
 *    1. Pre_layernorm (optional)
 *
 *        input = layernorm(input, layernorm_scale, layernorm_bias)
 *
 *    2. Fc1
 *
 *        input = fc(input, fc1_filters)
 *
 *    3. Add bias
 *
 *        input = add(input, fc1_bias)
 *
 *    4. Avtivation
 *
 *        input = active(input)
 *
 *    5. Fc2
 *
 *        input = fc(input, fc2_filters)
 *
 *    6. Add bias
 *
 *        input = add(input, fc2_bias)
 *
 *    7. Post_scale (optional)
 *
 *        input = mul(input, post_scale)
 *
 *    8. Residual add (optional)
 *
 *        input = add(input, residual_input). When the feed_forward structure is
 *        PRE_LAYERNORM_OUTSIDE_RESIDUAL, the residual_input is the result of pre_layernorm,
 *        otherwise is the original input.
 *
 *    9. Post layernorm (optional)
 *
 *        output = layernorm(input, layernorm_scale, layernorm_bias)
 *
 *  **Data Type**
 *
 *     - input: float, half.
 *
 *     - fc1 filters: float, half.
 *
 *     - fc1 bias: float, half.
 *
 *     - fc2 filters: float, half.
 *
 *     - fc2 bias: float, half.
 *
 *     - layernorm scale: float, half.
 *
 *     - layernorm bias: float, half.
 *
 *     - output: float, half.
 *
 *  **Supports MLU300 series.**
 *
 *  **Attention: **
 *
 *    - When \b desc and \b activation_desc is necessary, use ::cnnlCreateTransformerFeedForwardDescriptor and
 *      ::cnnlCreateActivationDescriptor to create the descriptor, use ::cnnlSetTransformerFeedForwardDescriptor and
 *      ::cnnlSetActivationDescriptor_v5 to set the descriptor, use ::cnnlDestroyTransformerFeedForwardDescriptor and
 *      ::cnnlDestroyActivationDescriptor to free the descriptor.
 *    - \b quantize_desc is not implemented yet, set it to NULL.
 *    - When \b workspace is necessary to complete the function, use ::cnnlGetTransformerFeedForwardWorkspaceSize
 *      to get the \b workspace_size .
 *    - The data type of all tensors must be same with each other.
 *    - The dimensions of all tensors must meet the following conditions:
 *        - The dimensions of \b input and \b output must be the same.
 *        - The dimensions of \b input can only be 2 or 3.
 *        - The dimensions of \b fc1_filters and \b fc2_filters must be 2.
 *        - The dimensions of \b fc1_bias, \b fc2_bias, \b layernorm_scale and \b layernorm_bias
 *          must be 1.
 *    - The dimension size of \b input and \b output along the same dimension must be the same.
 *    - The last dimension of \b input must be same as the following dimensions of tensors:
 *        - The second dimension of \b fc1_filters .
 *        - The first dimension of \b fc2_filters .
 *        - The first dimension of \b fc2_bias .
 *        - The first dimension of \b layernorm_scale .
 *        - The first dimension of \b layernorm_bias .
 *     - The first dimension of \b fc1_filters must be same as the following dimensions of tensors:
 *        - The second dimension of \b fc2_filters .
 *        - The first dimension of \b fc1_bias .
 *
 *  **Scale Limitation**
 *
 *    - The range of the last dimension of \b input : [16, 2048]
 *    - The range of the first dimension of \b fc1_filters : [16, 8192]
 *
 *  **Performance Optimization**
 *
 *    - When the last dimension of \b input can be divisible by 64, meanwhile the first dimension of \b fc1_filters is 4
 *      times of the last dimension of \b input, feed_forward function performs best.
 *
 *  **Example**
 *
 *    Dimension of \b input: [batch_num, seq_len, hidden_size]
 *    Dimension of \b fc1_filters: [filter_size, hidden_size]
 *    Dimension of \b fc1_bias: [filter_size]
 *    Dimension of \b fc2_filters: [hidden_size, filter_size]
 *    Dimension of \b fc2_bias: [hidden_size]
 *    Dimension of \b layernorm_scale: [hidden_size]
 *    Dimension of \b layernorm_bias: [hidden_size]
 *
 *    Then we will get the output:
 *
 *    Dimension of \b output: [batch_num, seq_len, hidden_size]
 *
 *  **API Dependency**
 *
 *      - You need to call the ::cnnlCreateTransformerFeedForwardDescriptor, ::cnnlGetTransformerFeedForwardWorkspaceSize
 *        and ::cnnlCreateActivationDescriptor functions before calling this function.
 *
 *      - You need to call the ::cnnlDestroyTransformerFeedForwardDescriptor and ::cnnlCreateActivationDescriptor
 *        function after calling this function.
 *
 *  @param[in] handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices
 *    and queues in the transformer_feed_forward operation. For detailed information, see ::cnnlHandle_t.
 *  @param[in] desc
 *    Input. The descriptor of the transformer_feed_forward operation. For detailed information, see ::cnnlTransformerFeedForwardDescriptor_t
 *  @param[in] activation_desc
 *    Input. The descriptor of the activation in transformer_feed_forward operation.
 *    For detailed information, see ::cnnlActivationDescriptor_t
 *  @param[in] quantize_desc
 *    Input. The descriptor of the quantization mode in transformer_feed_forward operation.
 *    For detailed information, see ::cnnlTransformerFeedForwardQuantizeDescriptor_t
 *  @param[in] input_desc
 *    Input. The descriptor of the input tensor.
 *    For detailed information, see ::cnnlTensorDescriptor_t.
 *  @param[in] input
 *    Input. Pointer to the MLU memory that stores the input tensor.
 *  @param[in] fc1_filters_desc
 *    Input. The descriptor of the fc1_filters tensor used as filters in the transformer_feed_forward operation.
 *    For detailed information, see ::cnnlTensorDescriptor_t.
 *  @param[in] fc1_filters
 *    Input. Pointer to the MLU memory that stores the fc1_filters tensor.
 *  @param[in] fc1_bias_desc
 *    Input. The descriptor of the fc1_bias tensor used as bias in the transformer_feed_forward operation.
 *    For detailed information, see ::cnnlTensorDescriptor_t.
 *  @param[in] fc1_bias
 *    Input. Pointer to the MLU memory that stores the fc1_bias tensor.
 *  @param[in] fc2_filters_desc
 *    Input. The descriptor of the fc2_filters tensor used as filters in the transformer_feed_forward operation.
 *    For detailed information, see ::cnnlTensorDescriptor_t.
 *  @param[in] fc2_filters
 *    Input. Pointer to the MLU memory that stores the fc2_filters tensor.
 *  @param[in] fc2_bias_desc
 *    Input. The descriptor of the fc2_bias tensor used as bias in the transformer_feed_forward operation.
 *    For detailed information, see ::cnnlTensorDescriptor_t.
 *  @param[in] fc2_bias
 *    Input. Pointer to the MLU memory that stores the fc2_bias tensor.
 *  @param[in] layernorm_scale_desc
 *    Input. The descriptor of the layernorm_scale tensor used as the scale of layernorm module
 *    in the transformer_feed_forward operation. For detailed information, see ::cnnlTensorDescriptor_t.
 *  @param[in] layernorm_scale
 *    Input. Pointer to the MLU memory that stores the layernorm_scale tensor.
 *  @param[in] layernorm_bias_desc
 *    Input. The descriptor of the layernorm_bias tensor used as the bias of layernorm module
 *    in the transformer_feed_forward operation. For detailed information, see ::cnnlTensorDescriptor_t.
 *  @param[in] layernorm_bias
 *    Input. Pointer to the MLU memory that stores the layernorm_bias tensor.
 *  @param[in] workspace
 *    Input. Pointer to the MLU memory that is used as an extra workspace for the
 *    transformer_feed_forward operation.
 *  @param[in] workspace_size
 *    Input. The size of the extra workspace in bytes that needs to be used in
 *    the transformer_feed_forward operation. You can get the size of the workspace with
 *    the ::cnnlGetTransformerFeedForwardWorkspaceSize function.
 *  @param[in] output_desc
 *    Output. The descriptor of the output tensor.
 *    For detailed information, see ::cnnlTensorDescriptor_t.
 *  @param[out] output
 *    Output. Pointer to the MLU memory that stores the output tensor.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more of the following conditions are encountered:
 *    - handle is NULL.
 *    - pointer is NULL.
 *    - parameters do not meet scale limitation.
 *  @retval CNNL_STATUS_ARCH_MISMATCH
 *    One or more of the following conditions are encountered:
 *    - This function is run on the hardware platform that is not supported.
 */
cnnlStatus_t CNNL_WIN_API
cnnlTransformerFeedForward(cnnlHandle_t handle,
                           const cnnlTransformerFeedForwardDescriptor_t desc,
                           const cnnlActivationDescriptor_t activation_desc,
                           const cnnlTransformerFeedForwardQuantizeDescriptor_t quantize_desc,
                           const cnnlTensorDescriptor_t input_desc,
                           const void *input,
                           const cnnlTensorDescriptor_t fc1_filters_desc,
                           const void *fc1_filters,
                           const cnnlTensorDescriptor_t fc1_bias_desc,
                           const void *fc1_bias,
                           const cnnlTensorDescriptor_t fc2_filters_desc,
                           const void *fc2_filters,
                           const cnnlTensorDescriptor_t fc2_bias_desc,
                           const void *fc2_bias,
                           const cnnlTensorDescriptor_t layernorm_scale_desc,
                           const void *layernorm_scale,
                           const cnnlTensorDescriptor_t layernorm_bias_desc,
                           const void *layernorm_bias,
                           void *workspace,
                           size_t workspace_size,
                           cnnlTensorDescriptor_t output_desc,
                           void *output);

// Group:Transformer FeedForward
/*!
 *  @brief Initializes the transformer_feed_forward descriptor \b desc that is previously created
 *  with the ::cnnlCreateTransformerFeedForwardDescriptor function, and sets the information
 *  about the feed-forware-network operation to the transformer_feed_forward descriptor
 *  \b desc. The information includes the value of the layernorm epsilon \b layernorm_eps,
 *  the value of the scale at the end of fc2 \b post_scale, the data type of the computation in
 *  transformer_feed_forward \b compute_dtype and the layernorm and residual structure of transformer_feed_forward
 *  \b layernorm_structure.
 *
 *  @param[in] desc
 *    Input. The descriptor of the transformer_feed_forward operation. For detailed information,
 *    see ::cnnlTransformerFeedForwardDescriptor_t
 *  @param[in] layernorm_eps
 *    Input. The value of epsilon in the layernorm module of the transformer_feed_forward operation.
 *    In layernorm module, the divisor is the variance of input which could be zero or very close to zero.
 *    \b layernorm_eps is added to the divisor to prevent divisor from being zero.
 *    \b layernorm_eps is usually set to 1e-7 .
 *  @param[in] post_scale
 *    Input. The value of scale factor after fc2 and before residual and post layernorm module. Set
 *    \b post_scale to 1.0 when it is not needed.
 *  @param[in] compute_dtype
 *    Input. The data type of computation in transformer_feed_forward operator. It controls the
 *    data type used in all the computation module except fc module whose data type is controlled
 *    by the data type of input. For detailed information, see ::cnnlDataType_t.
 *  @param[in] layernorm_structure
 *    Input. The structure of transformer_feed_forward operation, see ::cnnlTransformerLayernormResidualStructure_t
 *    for details.
 *
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    \b desc is NULL.
 *
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetTransformerFeedForwardDescriptor(cnnlTransformerFeedForwardDescriptor_t desc,
                                        const float layernorm_eps,
                                        const float post_scale,
                                        const cnnlDataType_t compute_dtype,
                                        const cnnlTransformerLayernormResidualStructure_t
                                                             layernorm_structure);


// Group:Transformer FeedForward
/*!
 *  @brief A function.
 *
 *  This function is used to create a descriptor of transformerfeedforward and allocate
 *  memory for it.
 *
 *  @param[in]  desc
 *    Input. Description of transformerfeedforward operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_ALLOC_FAILED
 *    The function allocate memory space failed.
 */
cnnlStatus_t CNNL_WIN_API
cnnlCreateTransformerFeedForwardDescriptor(cnnlTransformerFeedForwardDescriptor_t *desc);


// Group:Transformer FeedForward
/*!
 *  @brief A function.
 *
 *  This function is used to destroy a descriptor of transformerfeedforward and free
 * memory for it.
 *
 *  @param[in]  desc
 *    Input. Description of transformerfeedforward operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlDestroyTransformerFeedForwardDescriptor(cnnlTransformerFeedForwardDescriptor_t desc);


// Group:Transformer FeedForward
/*!
 *  @brief A function.
 *
 *  This function is used to get extra space size needed in transformerfeedforward operation.
 *
 *  **API Dependency**
 *
 *  You need to call the ::cnnlCreateTransformerFeedForwardDescriptor(), and
 *  ::cnnlSetTransformerFeedForwardDescriptor() functions before calling this function.
 *
 *  You need to call the ::cnnlDestroyTransformerFeedForwardDescriptor() function after
 *  calling this function.
 *
 *  @param[in]  handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues in the
 *           transformer_feed_forward operation.
 *  @param[in]  desc
 *    Input. Description of transformer_feed_forward.
 *  @param[in]  input_desc
 *    Input. Descriptor of input, containing dimension and the layout of input.
 *  @param[in]  fc1_filters_desc
 *    Input. Descriptor of fc1_filters, containing dimension and the layout of fc1_filters.
 *  @param[out] size
 *    Output. Size of workspace.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ended normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One of the following conditions are met:
 *    - The value of desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlGetTransformerFeedForwardWorkspaceSize(cnnlHandle_t handle,
                                           const cnnlTransformerFeedForwardDescriptor_t desc,
                                           const cnnlTensorDescriptor_t input_desc,
                                           const cnnlTensorDescriptor_t fc1_filters_desc,
                                           size_t *size);

/******************************************************************************
 * CNNLEXTRA OP Information
 ******************************************************************************/

/*!
 * @brief An enum.
 * Enumeration variables describing the supported operation names.
 */
typedef enum {
  TRANSFORMER_SELF_ATTN = 0,  /*!< The operation transformer_self_attn.*/
  PYTORCH_SELFATTN,  /*!< The operation pytorch_selfattn.*/
  TRANSFORMER_FFN,  /*!< The operation transformer_ffn.*/
  PYTORCH_FFN,  /*!< The operation pytorch_ffn.*/
  BERT_POST,  /*!< The operation bertpost.*/
  BERT_PRE,  /*!< The operation bertpre.*/
  TRANSFORMER_BEAMSEARCH,  /*!< The operation transformer_beamsearch.*/
  TRANSFORMER_BEAMREARRANGE,  /*!< The operation transformer_beamrearrange.*/
  TRANSFORMER_EMBEDDING,  /*!< The operation transformer_embedding.*/
  TRANSFORMER_ENCODER_OUTPUT,  /*!< The operation transformer_encoder_output.*/
  TRANSFORMER_POSITION_ENCODING,  /*!< The operation transformer_position_encoding.*/
  TRANSFORMER_ENCDECATTN,  /*!< The operation transformer_encdecattn.*/
  TRANSFORMER_FCTOPK,  /*!< The operation transformer_fctopk.*/
  PACK2PAD,  /*!< The operation pack2pad.*/
  PAD2PACK,  /*!< The operation pad2pack.*/
  TACOTRON2_DECODER,  /*!< The operation tacotron2_decoder.*/
  CNNLEXTRA_OP_COUNT,  /*!< The total count of operations.*/
} cnnlextraSupportOps_t;

/*!
 * @brief An enum.
 * Enumeration variables describing the supported devices.
 */
typedef enum {
  MTP_220_1_CLUSTER = 0,  /*!< The device mtp220 with 1 cluster.*/
  MTP_270_4_CLUSTER,  /*!< The device mtp270 with 4 cluster.*/
  MTP_290_8_CLUSTER,  /*!< The device mtp290 with 8 cluster.*/
  MTP_322_2_CLUSTER,  /*!< The device mtp322 with 2 cluster.*/
  MTP_372_2_CLUSTER,  /*!< The device mtp372 with 2 cluster.*/
  MTP_372_4_CLUSTER,  /*!< The device mtp372 with 4 cluster.*/
  MTP_372_6_CLUSTER,  /*!< The device mtp372 with 6 cluster.*/
  MTP_372_8_CLUSTER,  /*!< The device mtp372 with 8 cluster.*/
  CNNLEXTRA_DEVICE_COUNT,  /*!< The total count of devices.*/
} cnnlextraSupportDevices_t;

/*!
 * @brief An enum.
 * Enumeration variables describing the supported data types.
 */
typedef enum {
  DEVICE_SPPT_NON = 0,
  /*!< The operator supports no device.*/
  DEVICE_SPPT_FP16_FP32 = 3,
  /*!< The operator supports fp16/fp32.*/
  DEVICE_SPPT_FP16_FP32_INT8 = 7,
  /*!< The operator supports fp16/fp32/int8.*/
  DEVICE_SPPT_FP16_FP32_INT16 = 11,
  /*!< The operator supports fp16/fp32/int16.*/
  DEVICE_SPPT_FP16_FP32_INT8_INT16 = 15,
  /*!< The operator supports fp16/fp32/int8/int16.*/
  DEVICE_SPPT_FP16_FP32_INT32 = 19,
  /*!< The operator supports fp16/fp32/int32.*/
} cnnlextraSupportDeviceDataType_t;

// Group:GetSupportDevice
/*!
 *  @brief A function
 *
 *  This function receives a certain group of operation names and then gets the supported devices and data types.
 *
 *  @param[in] kernel_name
 *    Input. The name of the operation.
 *           See ::cnnlextraSupportOps_t to view the supported operations.
 *  @param[out] output
 *    Output. Pointer to the host memory that stores the final data.
 *  @param[out] output_size
 *    Output. The number of output elements. It should be not less than ::CNNLEXTRA_DEVICE_COUNT.
 *  @retval CNNL_STATUS_SUCCESS
      The function ended normally.
    @retval CNNL_STATUS_BAD_PARAM
      One of the following conditions are met:
      - The pointer of output is null.
 */
cnnlStatus_t CNNL_WIN_API
cnnlextraGetSupportDevice(cnnlextraSupportOps_t kernel_name,
                          cnnlextraSupportDeviceDataType_t  * output,
                          int output_size);

/******************************************************************************
 * Cambricon CNNL OP: TransformerAttnProj
 ******************************************************************************/
/*! The descriptor of TransformerAttnProj.
 * You can use cnnlCreateTransformerAttnProjDescriptor, cnnlSetTransformerAttnProjDescriptor,
 * cnnlGetTransformerAttnProjDescriptor, cnnlDestroyTransformerAttnProjDescriptor to create,
 * set, get and destroy the descriptor respectively.
 */
typedef struct cnnlTransformerAttnProjStruct *cnnlTransformerAttnProjDescriptor_t;

/*! The descriptor of TransformerAttnProj that holds quantization information.
 * Reserved for future use.
 */
typedef struct cnnlTransformerAttnProjQuantizeStruct *cnnlTransformerAttnProjQuantizeDescriptor_t;

// Group:TransformerAttnProj
/*!
 *  @brief A function.
 *
 *  This function is used to create a descriptor of TransformerAttnProj.
 *
 *  @param[out]  attn_proj_desc
 *    Output. Descriptor of TransformerAttnProj operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_ALLOC_FAILED
 *    The function fails to allocate memory for the TransformerAttnProj descriptor.
 */
cnnlStatus_t CNNL_WIN_API
cnnlCreateTransformerAttnProjDescriptor(cnnlTransformerAttnProjDescriptor_t *attn_proj_desc);

// Group:TransformerAttnProj
/*!
 *  @brief A function.
 *
 *  This function is used to destroy a descriptor of TransformerAttnProj.
 *
 *  @param[in]  attn_proj_desc
 *    Input. Descriptor of TransformerAttnProj operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    \b desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlDestroyTransformerAttnProjDescriptor(cnnlTransformerAttnProjDescriptor_t attn_proj_desc);

// Group:TransformerAttnProj
/*!
 *  @brief A function.
 *
 *  This function retrieves extra space size needed in TransformerAttnProj operation.
 *
 *  @param[in] handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues.
 *  @param[in] attn_proj_desc
 *    Input. Descriptor of TransformerAttnProj operation.
 *  @param[in] attn_proj_quan_desc
 *    Input. Descriptor of TransformerAttnProj operation including quantization related information.
 *    Reserverd for future use. Currently attn_proj_quan_desc must be NULL.
 *  @param[in] input_desc
 *    Input. Descriptor of input tensor. The shape is [batch, seq_len, input_size].
 *  @param[in] filter_desc
 *    Input. Descriptor of filter tensor. The shape is [hidden_size, input_size].
 *  @param[in] output_desc
 *    Input. Descriptor of output tensor. The shape is [batch, seq_len, hidden_size] or
 *    [batch, head_num, seq_len, head_size].
 *  @param[out] size
 *    Output. Size of needed workspace.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more required parameter is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlGetTransformerAttnProjWorkspaceSize(cnnlHandle_t handle,
    const cnnlTransformerAttnProjDescriptor_t attn_proj_desc,
    const cnnlTransformerAttnProjQuantizeDescriptor_t attn_proj_quan_desc,
    const cnnlTensorDescriptor_t input_desc,
    const cnnlTensorDescriptor_t filter_desc,
    const cnnlTensorDescriptor_t output_desc,
    size_t *size);

// Group:TransformerAttnProj
/*!
 *  @brief A function.
 *
 *  This function is used to set a descriptor of TransformerAttnProj with values.
 *
 *  @param[in] handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues.
 *  @param[in] attn_proj_desc
 *    Input. Descriptor of TransformerAttnProj operation.
 *  @param[in] layernorm_residual_mode
 *    Input. Position relations between matrix multiply, layernorm and residual.
 *    Accepted value is CNNL_TRANSFORMER_NO_LAYERNORM_NO_RESIDUAL,
 *    CNNL_TRANSFORMER_NO_LAYERNORM_WITH_RESIDUAL, CNNL_TRANSFORMER_PRE_LAYERNORM_NO_RESIDUAL,
 *    CNNL_TRANSFORMER_POST_LAYERNORM_NO_RESIDUAL, CNNL_TRANSFORMER_POST_LAYERNORM_INSIDE_RESIDUAL,
 *    CNNL_TRANSFORMER_POST_LAYERNORM_OUTSIDE_RESIDUAL.
 *  @param[in] activation_desc
 *    Input. Descriptor of activation. Reserved for future use. Currently must be NULL;
 *  @param[in] math_pre
 *    Input. Onchip computation data type of layernorm.
 *  @param[in] q_has_value
 *    Input. Indicates whether q(query) has been involved in computing.
 *  @param[in] k_has_value
 *    Input. Indicates whether k(key) has been involved in computing.
 *  @param[in] v_has_value
 *    Input. Indicates whether v(value) has been involved in computing.
 *  @param[in] has_bias
 *    Input. Indicates whether q(query)/k(key)/v(value) has bias.
 *  @param[in] is_pack_mode
 *    Input. Reserved for future use, currently must be false.
 *  @param[in] packed_max_seq_len
 *    Input. Reserved for future use.
 *  @param[in] trans_out
 *    Input. Indicates whether output should be transposed.
 *  @param[in] store_layernorm_result
 *    Input. Indicates whether to store layernorm output before doing matrix multiplication.
 *    When store_layernorm_result is true, layernorm_residual_mode should be
 *    CNNL_TRANSFORMER_PRE_LAYERNORM_NO_RESIDUAL.
 *  @param[in] alpha
 *    Input. Reserved for future use. Currently alpha must be 1.0.
 *  @param[in] beta
 *    Input. Reserved for future use. Currently beta must be 1.0.
 *  @param[in] layernorm_eps
 *    Input. A small value that adds to variance when doing layernorm. layernorm_eps must be
 *    equal to or greater than 0, and equal to or less than 1e-4.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    \b attn_proj_desc is NULL or one or more parameter is not supported.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetTransformerAttnProjDescriptor(
    cnnlTransformerAttnProjDescriptor_t attn_proj_desc,
    const cnnlTransformerLayernormResidualStructure_t layernorm_residual_mode,
    const cnnlActivationDescriptor_t activation_desc,
    const cnnlDataType_t math_pre,
    const bool q_has_value,
    const bool k_has_value,
    const bool v_has_value,
    const bool has_bias,
    const bool is_pack_mode,
    const int packed_max_seq_len,
    const bool trans_out,
    const bool store_layernorm_result,
    const float alpha,
    const float beta,
    const float layernorm_eps);

// Group:TransformerAttnProj
/*!
 *  @brief A function.
 *
 *  This function is used to get a descriptor of TransformerAttnProj with values.
 *
 *  @param[in] handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues.
 *  @param[in] attn_proj_desc
 *    Input. Descriptor of TransformerAttnProj operation.
 *  @param[out] layernorm_residual_mode
 *    Output. Position relations between matrix multiply, layernorm and residual.
 *  @param[out] activation_desc
 *    Output. Descriptor of activation. Reserved for future use.
 *  @param[out] math_pre
 *    Output. Onchip computation data type of layernorm.
 *  @param[out] q_has_value
 *    Output. Indicates whether q(query) has been involved in computing.
 *  @param[out] k_has_value
 *    Output. Indicates whether k(key) has been involved in computing.
 *  @param[out] v_has_value
 *    Output. Indicates whether v(value) has been involved in computing.
 *  @param[out] has_bias
 *    Output. Indicates whether q(query)/k(key)/v(value) has bias.
 *  @param[out] is_pack_mode
 *    Output. Reserved for future use.
 *  @param[out] packed_max_seq_len
 *    Output. Reserved for future use.
 *  @param[out] trans_out
 *    Output. Indicates whether output should be transposed.
 *  @param[out] store_layernorm_result
 *    Output. Indicates whether to store layernorm output before doing matrix multiplication.
 *  @param[out] alpha
 *    Output. Reserved for future use.
 *  @param[out] beta
 *    Output. Reserved for future use.
 *  @param[out] layernorm_eps
 *    Output. A small value that adds to variance when doing layernorm.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    \b attn_proj_desc is NULL or one or more parameter is not supported.
 */
cnnlStatus_t CNNL_WIN_API
cnnlGetTransformerAttnProjDescriptor(
    const cnnlTransformerAttnProjDescriptor_t attn_proj_desc,
    cnnlTransformerLayernormResidualStructure_t* layernorm_residual_mode,
    cnnlActivationDescriptor_t* activation_desc,
    cnnlDataType_t* math_pre,
    bool* q_has_value,
    bool* k_has_value,
    bool* v_has_value,
    bool* has_bias,
    bool* is_pack_mode,
    int* packed_max_seq_len,
    bool* trans_out,
    bool* store_layernorm_result,
    float* alpha,
    float* beta,
    float* layernorm_eps);

// Group:TransformerAttnProj
/*!
 *  @brief A function.
 *
 *  This function executes attention projection in Transformer encoder and decoder network.
 *
 *  **Formula**
 *
 *    if (pre_layernorm):
 *      x = layernorm(x)
 *
 *    if (q_has_value):
 *      q = x * q_filter + q_bias
 *
 *    if (k_has_value):
 *      k = x * k_filter + k_bias
 *
 *    if (v_has_value):
 *      v = x * v_filter + v_bias
 *
 *    if (residual):
 *      q += residual
 *
 *    if (post_layernorm):
 *      q = layernorm(q)
 *
 *  some opeations may not be done or may be done in differnet order according to attn_proj_desc.
 *
 *  **DataType**
 *
 *    - Data type of input must be float or half.
 *    - Data type of input, filter, bias, and output must be same.
 *    - When data type of input is float, math_pre must be float.
 *
 *  **Attention**
 *
 *    - Only MLU370 and MLU365-D2 are supported.
 *
 *    - Inputs and outputs cannot be homologous operand.
 *
 *    - The content of all input tensors are not modified.
 *
 *  **Scale Limitation**
 *
 *    - \b batch > 0
 *    - \b seq_len > 0
 *    - \b input_size >= 16
 *    - \b hidden_size >= 16
 *    - If \b layernorm_residual_mode is set with pre-layernormal, \b input_size should be equal to or less than 2048,
 *      otherwise input_size should be less than or equal to 8192.
 *    - If \b layernorm_residual_mode is set with  post_layernorm, \b hidden_size should be equal to or less than 2048,
 *      otherwise hidden_size should be less than or equal to 8192.
 *    - \b hidden_size = \b head_num * \b head_size.
 *    - When \b trans_out is true, \b head_num must be in the range [1, 128].
 *    - When \b trans_out is true, \b head_size must be in the range [16, 128].
 *    - \b layernorm_residual_mode must be:
 *      - CNNL_TRANSFORMER_NO_LAYERNORM_NO_RESIDUAL
 *      - CNNL_TRANSFORMER_NO_LAYERNORM_WITH_RESIDUAL
 *      - CNNL_TRANSFORMER_PRE_LAYERNORM_NO_RESIDUAL
 *      - CNNL_TRANSFORMER_POST_LAYERNORM_NO_RESIDUAL
 *      - CNNL_TRANSFORMER_POST_LAYERNORM_INSIDE_RESIDUAL
 *      - CNNL_TRANSFORMER_POST_LAYERNORM_OUTSIDE_RESIDUAL
 *    - When doing post layernorm or adding residual, only one filter is avaliable.
 *    - When \b trans_out is true, post layernorm or residual is forbidden.
 *    - When \b store_layernorm_result is true, \b layernorm_residual_mode must
 *      contain pre layernorm mode.
 *    - Total count of elements of each input, filter and output should be less than or
 *      or equal to INT32_MAX.
 *
 *  @param[in] handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues.
 *  @param[in] attn_proj_desc
 *    Input. Descriptor of TransformerAttnProj operation.
 *  @param[in] attn_proj_quan_desc
 *    Input. Descriptor of quantization information of TransformerAttnProj operation.
 *  @param[in] input_desc
 *    Input. Descriptor of input tensor. The shape is [batch, seq_len, input_size].
 *  @param[in] input
 *    Input. Device pointer points to input space.
 *  @param[in] residual_desc
 *    Input. Descriptor of residual tensor. The shape is [batch, seq_len, hidden_size].
 *  @param[in] residual
 *    Input. Device pointer points to residual space.
 *  @param[in] q_filter_desc
 *    Input. Descriptor of q_filter tensor. The shape is [hidden_size, input_size].
 *    When q_has_value is false, q_filter_desc must be NULL.
 *  @param[in] q_filter
 *    Input. Device pointer points to q_filter space.
 *    When q_has_value is false, q_filter must be NULL.
 *  @param[in] k_filter_desc
 *    Input. Descriptor of k_filter tensor. The shape is [hidden_size, input_size].
 *    When k_has_value is false, k_filter_desc must be NULL.
 *  @param[in] k_filter
 *    Input. Device pointer points to k_filter space.
 *    When k_has_value is false, k_filter must be NULL.
 *  @param[in] v_filter_desc
 *    Input. Descriptor of v_filter tensor. The shape is [hidden_size, input_size].
 *    When v_has_value is false, v_filter_desc must be NULL.
 *  @param[in] v_filter
 *    Input. Device pointer points to v_filter space.
 *    When v_has_value is false, v_filter must be NULL.
 *  @param[in] q_bias_desc
 *    Input. Descriptor of q_bias tensor. The shape is [hidden_size].
 *    When q_has_value is false or has_bias is false, q_bias_desc must be NULL.
 *  @param[in] q_bias
 *    Input. Device pointer points to q_bias space.
 *    When q_has_value is false, q_bias must be NULL.
 *  @param[in] k_bias_desc
 *    Input. Descriptor of k_bias tensor. The shape is [hidden_size].
 *    When k_has_value is false or has_bias is false, k_bias_desc must be NULL.
 *  @param[in] k_bias
 *    Input. Device pointer points to k_bias space.
 *    When k_has_value is false or has_bias is false, k_bias must be NULL.
 *  @param[in] v_bias_desc
 *    Input. Descriptor of v_bias tensor. The shape is [hidden_size].
 *    When v_has_value is false or has_bias is false, v_bias_desc must be NULL.
 *  @param[in] v_bias
 *    Input. Device pointer points to v_bias space.
 *    When v_has_value is false or has_bias is false, v_bias must be NULL.
 *  @param[in] valid_token_desc
 *    Input. Descriptor of valid_token tensor. The shape is [batch_size].
 *    Reserved for future use, currently must be NULL.
 *  @param[in] valid_token
 *    Input. Device pointer points to valid_token space.
 *    Reserved for future use, currently must be NULL.
 *  @param[in] layernorm_scale_desc
 *    Input. Descriptor of layernorm_scale tensor.
 *    When pre_layernorm is enabled, the shape is [input_size].
 *    When post_layernorm is enabled, the shape is [hidden_size].
 *    When no layernorm is enabled, layernorm_scale_desc must be NULL.
 *  @param[in] layernorm_scale
 *    Input. Device pointer points to layernorm_scale space.
 *    When no layernorm is enabled, layernorm_scale must be NULL.
 *  @param[in] layernorm_bias_desc
 *    Input. Descriptor of layernorm_bias tensor.
 *    When pre_layernorm is enabled, the shape is [input_size].
 *    When post_layernorm is enabled, the shape is [hidden_size].
 *    When no layernorm is enabled, layernorm_bias_desc must be NULL.
 *  @param[in] layernorm_bias
 *    Input. Device pointer points to layernorm_bias space.
 *    When no layernorm is enabled, layernorm_bias must be NULL.
 *  @param[in] workspace
 *    Input. Pointer to the MLU memory that is used as an extra workspace.
 *  @param[in] workspace_size
 *    Input. The size of workspace.
 *  @param[in] q_out_desc
 *    Input. Descriptor of q_out tensor. When trans_out is false, the shape is
 *    [batch, seq_len, hidden_size]. When trans_out is true, the shape is
 *    [batch, head_num, seq_len, head_size].
 *    When q_has_value is false, q_out_desc must be NULL.
 *  @param[out] q_out
 *    Output. Device pointer points to q_out space.
 *    When q_has_value is false, q_out must be NULL.
 *  @param[in] k_out_desc
 *    Input. Descriptor of k_out tensor. When trans_out is false, the shape is
 *    [batch, seq_len, hidden_size]. When trans_out is true, the shape is
 *    [batch, head_num, seq_len, head_size].
 *    When k_has_value is false, k_out_desc must be NULL.
 *  @param[out] k_out
 *    Output. Device pointer points to k_out space.
 *    When k_has_value is false, k_out must be NULL.
 *  @param[in] v_out_desc
 *    Input. Descriptor of v_out tensor. When trans_out is false, the shape is
 *    [batch, seq_len, hidden_size]. When trans_out is true, the shape is
 *    [batch, head_num, seq_len, head_size].
 *    When v_has_value is false, v_out_desc must be NULL.
 *  @param[out] v_out
 *    Output. Device pointer points to v_out space.
 *    When v_has_value is false, v_out must be NULL.
 *  @param[in] layernorm_out_desc
 *    Input. Descriptor of layernorm_out tensor. When store_layernorm_result is true, the shape is
 *    [batch, seq_len, input_size].
 *    When store_layernorm_result is false, layernorm_out_desc must be NULL.
 *  @param[out] layernorm_out
 *    Output. Device pointer points to layernorm_out space.
 *    When store_layernorm_result is false, layernorm_out must be NULL.
 *  @retval CNNL_STATUS_SUCCESS = 0
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM = 3
 *    One or more of the following conditions are encountered:
 *    - handle is NULL.
 *    - one or more required pointer is NULL.
 *    - scale or data type limitation is not satisfied.
 */
cnnlStatus_t CNNL_WIN_API
cnnlTransformerAttnProj(cnnlHandle_t handle,
                        const cnnlTransformerAttnProjDescriptor_t attn_proj_desc,
                        const cnnlTransformerAttnProjQuantizeDescriptor_t attn_proj_quan_desc,
                        const cnnlTensorDescriptor_t input_desc,
                        const void* input,
                        const cnnlTensorDescriptor_t residual_desc,
                        const void* residual,
                        const cnnlTensorDescriptor_t q_filter_desc,
                        const void* q_filter,
                        const cnnlTensorDescriptor_t k_filter_desc,
                        const void* k_filter,
                        const cnnlTensorDescriptor_t v_filter_desc,
                        const void* v_filter,
                        const cnnlTensorDescriptor_t q_bias_desc,
                        const void* q_bias,
                        const cnnlTensorDescriptor_t k_bias_desc,
                        const void* k_bias,
                        const cnnlTensorDescriptor_t v_bias_desc,
                        const void* v_bias,
                        const cnnlTensorDescriptor_t valid_token_desc,
                        const void* valid_token,
                        const cnnlTensorDescriptor_t layernorm_scale_desc,
                        const void* layernorm_scale,
                        const cnnlTensorDescriptor_t layernorm_bias_desc,
                        const void* layernorm_bias,
                        void* workspace,
                        size_t workspace_size,
                        const cnnlTensorDescriptor_t q_out_desc,
                        void* q_out,
                        const cnnlTensorDescriptor_t k_out_desc,
                        void* k_out,
                        const cnnlTensorDescriptor_t v_out_desc,
                        void* v_out,
                        const cnnlTensorDescriptor_t layernorm_out_desc,
                        void* layernorm_out);

/******************************************************************************
 * Cambricon CNNL OP: TransformerAttention
 ******************************************************************************/
/*! The descriptor of TransformerAttention.
 * You can use cnnlCreateTransformerAttentionDescriptor(), cnnlSetTransformerAttentionDescriptor()
 * and cnnlDestroyTransformerAttentionDescriptor() to create, set and destroy the descriptor
 * respectively.
 */
typedef struct cnnlTransformerAttentionStruct *cnnlTransformerAttentionDescriptor_t;

/*! The descriptor of TransformerAttention that holds quantization information.
 * Reserved for future use.
 */
typedef struct cnnlTransformerAttentionQuantizeStruct *cnnlTransformerAttentionQuantizeDescriptor_t;

// Group:TransformerAttention
/*!
 *  @brief A function.
 *
 *  This function is used to create a descriptor of TransformerAttention.
 *
 *  @param[out]  desc
 *    Output. Descriptor of TransformerAttention operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_ALLOC_FAILED
 *    The function fails to allocate memory for the TransformerAttention descriptor.
 */
cnnlStatus_t CNNL_WIN_API
cnnlCreateTransformerAttentionDescriptor(cnnlTransformerAttentionDescriptor_t *desc);

// Group:TransformerAttention
/*!
 *  @brief A function.
 *
 *  This function is used to destroy a descriptor of TransformerAttention.
 *
 *  @param[in]  desc
 *    Input. Descriptor of TransformerAttention operation.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    \b desc is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlDestroyTransformerAttentionDescriptor(cnnlTransformerAttentionDescriptor_t desc);

// Group:TransformerAttention
/*!
 *  @brief A function.
 *
 *  This function is used to set a descriptor of TransformerAttention with values.
 *
 *  @param[in]  desc
 *    Input. Descriptor of TransformerAttention operation.
 *  @param[in]  compute_dtype
 *    Input. Data type to be used during computation.
 *    If data type of inputs are half, \b compute_dtype can be half or float.
 *    If data type of inputs are float, \b compute_dtype must be float.
 *    If \b compute_dtype is set to CNNL_DTYPE_INVALID, it will be the same as data type of inputs.
 *  @param[in]  act_pref
 *    Input. The indicator of activation operation preference, including:
 *           - CNNL_ACTIVATION_FAST: use high-performace for activation operations.
 *           - CNNL_ACTIVATION_HIGH_PRECISION: use high-precision for activation operations.
 *  @param[in]  mask_mode
 *    Input. The indicator of mask adding mode, including:
 *           - CNNL_ATTN_MASK_NONE: no mask adding after QK matmul.
 *           - CNNL_ATTN_MASK_NT: add mask with shape [batch, seq_kv] after QK matmul.
 *           - CNNL_ATTN_MASK_TT: add mask with shape [seq_q, seq_kv] after QK matmul.
 *           - CNNL_ATTN_MASK_NTT: add mask with shape [batch, seq_q, seq_kv] after QK matmul.
 *           - CNNL_ATTN_MASK_N: the mask has shape [batch] and int32 data type, indicating length of each batch.
 *             The kernel generates mask value with shape [batch, seq_len] according to input mask.
 *           - CNNL_ATTN_MASK_NHTT: add mask with shape [batch, head_num, seq_q, seq_kv] after QK matmul.
 *    Currently only CNNL_ATTN_MASK_NONE, CNNL_ATTN_MASK_NT, CNNL_ATTN_MASK_NTT and CNNL_ATTN_MASK_N are supported.
 *  @param[in]  is_pack_mode
 *    Input. If true, inputs of multi-head attention are packed. If false, inputs are padded.
 *    Currently only false (pad mode) is supported.
 *  @param[in]  packed_max_seq_len
 *    Input. The indicator of maximum sequence length of pack mode.
 *           This parameter is only used when \b is_pack_mode is true.
 *           When \b is_pack_mode is false, this parameter is ignored.
 *  @param[in]  query_factor
 *    Input. The scale factor for scaled batchdot of q and k.
 *  @param[in]  is_mul_factor_after_qk
 *    Input. If true, \b query_factor is multiplied after calculating q dot k. If false,
 *           \b query_factor is multiplied on q, then perform q dot k.
 *  @param[in]  is_store_qk
 *    Input. Reserved for future use.
 *    Currently only false is supported.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    \b desc is NULL or one or more parameter is not supported.
 */
cnnlStatus_t CNNL_WIN_API
cnnlSetTransformerAttentionDescriptor(cnnlTransformerAttentionDescriptor_t desc,
                                      cnnlDataType_t compute_dtype,
                                      cnnlActivationPreference_t act_pref,
                                      cnnlAttentionMaskMode_t mask_mode,
                                      bool is_pack_mode,
                                      int packed_max_seq_len,
                                      float query_factor,
                                      bool is_mul_factor_after_qk,
                                      bool is_store_qk);

// Group:TransformerAttention
/*!
 *  @brief A function.
 *
 *  This function retrieves extra space size needed in attention operation.
 *
 *  @param[in] handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues.
 *  @param[in]  desc
 *    Input. Descriptor of TransformerAttention operation.
 *  @param[in]  quan_desc
 *    Input. Descriptor of TransformerAttention operation including quantization related information.
 *    Reserverd for future use.
 *  @param[in]  query_desc
 *    Input. Descriptor of query tensor. The shape is [batch, head_num, seq_q, head_size].
 *  @param[in]  key_desc
 *    Input. Descriptor of key tensor. The shape is [batch, head_num, seq_kv, head_size].
 *  @param[in]  value_desc
 *    Input. Descriptor of value tensor. The shape is [batch, head_num, seq_kv, head_size].
 *  @param[out] size
 *    Output. Size of needed workspace.
 *  @retval CNNL_STATUS_SUCCESS
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM
 *    One or more required parameter is NULL.
 */
cnnlStatus_t CNNL_WIN_API
cnnlGetTransformerAttentionWorkspaceSize(cnnlHandle_t handle,
                                         cnnlTransformerAttentionDescriptor_t desc,
                                         cnnlTransformerAttentionQuantizeDescriptor_t quan_desc,
                                         cnnlTensorDescriptor_t query_desc,
                                         cnnlTensorDescriptor_t key_desc,
                                         cnnlTensorDescriptor_t value_desc,
                                         size_t *size);

// Group:TransformerAttention
/*!
 *  @brief A function.
 *
 *  This function executes multi-head attention in Transformer encoder and decoder network.
 *
 *  **Formula**
 *
 *  In Transformer encoder:
 *
 *    if (is_mul_factor_after_qk == false) then
 *      query = query * query_factor
 *
 *    beta = batch_matmul(query, key)
 *
 *    beta = beta + mask
 *
 *    if (is_mul_factor_after_qk == true) then
 *      beta = beta * query_factor
 *
 *    alpha = softmax(beta)
 *
 *    output = batch_matmul(alpha, value)
 *
 *  In Transformer decoder:
 *
 *    f = curr_idx[0]
 *
 *    key = concat(key_cache[:,:,0:f], key)
 *
 *    value = concat(value_cache[:,:,0:f], value)
 *
 *    if (is_mul_factor_after_qk == false) then
 *      query = query * query_factor
 *
 *    beta = batch_matmul(query, key)
 *
 *    if (is_mul_factor_after_qk == true) then
 *      beta = beta * query_factor
 *
 *    alpha = softmax(beta)
 *
 *    output = batch_matmul(alpha, value)
 *
 *  **DataType**
 *
 *    - If mask_mode is CNNL_ATTN_MASK_N, then data type of \b mask must be int32. Otherwise,
 *      it must be same as data type of \b query.
 *
 *    - Data type of \b curr_idx must be int32.
 *
 *    - All other inputs and outputs must have the same data type, either float or half.
 *
 *  **Attention**
 *
 *    - Only MLU370 and MLU365-D2 are supported.
 *
 *    - If \b curr_idx is NULL, the operation computes encoder attention.
 *
 *    - if \b curr_idx is not NULL, the operation computes decoder attention.
 *
 *    - Inputs and outputs cannot be homologous operand.
 *
 *    - The content of all input tensors are not modified.
 *
 *  **Scale Limitation**
 *
 *    - \b batch > 0.
 *    - \b seq_q must be in the range [1, 1024].
 *    - \b seq_kv must be in the range [1, 1024].
 *    - \b head_num must be in the range [1, 128].
 *    - \b head_size must be in the range [16, 128].
 *    - \b compute_dtype must be half or float. If data type of input is float, \b compute_dtype must be float.
 *    - \b mask_mode must be:
 *      - CNNL_ATTN_MASK_NONE
 *      - CNNL_ATTN_MASK_NT
 *      - CNNL_ATTN_MASK_NTT
 *      - CNNL_ATTN_MASK_N
 *    - \b is_pack_mode must be false.
 *    - \b output_qk must be false.
 *    - \b max_decode_len must be in the range [1, 1024].
 *    - \b curr_idx must be in the range [0, max_decode_len).
 *    - \b beam must be in the range [1, 32].
 *    - \b batch % \b beam must be 0 in decoder attention.
 *    - \b ngroup must be 1.
 *
 *  @param[in] handle
 *    Input. Handle to a Cambricon CNNL context that is used to manage MLU devices and queues.
 *  @param[in]  desc
 *    Input. Descriptor of TransformerAttention operation.
 *  @param[in]  quan_desc
 *    Input. Descriptor of TransformerAttention operation including quantization related info.
 *    Reserverd for future use.
 *  @param[in]  query_desc
 *    Input. Descriptor of query tensor. The shape is [batch, head_num, seq_q, head_size].
 *  @param[in]  query
 *    Input. Device pointer points to query space.
 *  @param[in]  key_desc
 *    Input. Descriptor of key tensor. The shape is [batch, head_num, seq_kv, head_size].
 *  @param[in]  key
 *    Input. Device pointer points to query space.
 *  @param[in]  value_desc
 *    Input. Descriptor of value tensor. The shape is [batch, head_num, seq_kv, head_size].
 *  @param[in]  value
 *    Input. Device pointer points to query space.
 *  @param[in]  mask_desc
 *    Input. Descriptor of mask tensor. The shape and data type must be consistent with mask_mode.
 *  @param[in]  mask
 *    Input. Device pointer points to mask space.
 *  @param[in]  curr_idx_desc
 *    Input. Descriptor of curr_idx tensor. The shape is [1], and data type is int32.
 *           This parameter is only required in decoder mode.
 *  @param[in]  curr_idx
 *    Input. Device pointer points to curr_idx space.
 *           This parameter is only required in decoder mode.
 *  @param[in]  key_cache_desc
 *    Input. Descriptor of key_cache tensor. The shape is [batch, head_num, max_decode_len, head_size].
 *           This parameter is only required in decoder mode.
 *  @param[in]  key_cache
 *    Input. Device pointer points to key_cache space.
 *           This parameter is only required in decoder mode.
 *  @param[in]  value_cache_desc
 *    Input. Descriptor of value_cache tensor. The shape is [batch, head_num, max_decode_len, head_size].
 *           This parameter is only required in decoder mode.
 *  @param[in]  value_cache
 *    Input. Device pointer points to value_cache space.
 *           This parameter is only required in decoder mode.
 *  @param[in] best_beams_cache_desc
 *    Input. Descriptor of best_beams_cache tensor. The shape must be [(batch / beam), ngroup, beam].
 *           This parameter is optional, and is only used in decoder mode.
 *  @param[in] best_beams_cache
 *    Input. Device pointer points to best_beams_cache tensor space. It is a state
 *           inferred from beam search result, to restore historical K/V cache correctly.
 *           If this is the first frame of decoder, this cache must be initialized with zero
 *           before calling this operation.
 *           This parameter is optional, and is only used in decoder mode.
 *  @param[in]  workspace
 *    Input. Device pointer points to workspace space.
 *  @param[in]  workspace_size
 *    Input. Size of workspace.
 *  @param[in]  output_qk_desc
 *    Input. Descriptor of output_qk tensor. The shape is [batch, head_num, seq_q, seq_k].
 *           Reserverd for future use.
 *  @param[in]  output_qk
 *    Input. Device pointer points to output_qk space. Reserverd for future use.
 *  @param[in]  output_desc
 *    Input. Descriptor of output tensor. The shape is [batch, seq_q, head_num, head_size].
 *  @param[in]  output
 *    Input. Device pointer points to output space.
 *  @retval CNNL_STATUS_SUCCESS = 0
 *    The function ends normally.
 *  @retval CNNL_STATUS_BAD_PARAM = 3
 *    One or more of the following conditions are encountered:
 *    - handle is NULL.
 *    - one or more required pointer is NULL.
 *    - scale or data type limitation is not satisfied.
 */
cnnlStatus_t CNNL_WIN_API
cnnlTransformerAttention(cnnlHandle_t handle,
                         cnnlTransformerAttentionDescriptor_t desc,
                         cnnlTransformerAttentionQuantizeDescriptor_t quan_desc,
                         cnnlTensorDescriptor_t query_desc,
                         const void *query,
                         cnnlTensorDescriptor_t key_desc,
                         const void *key,
                         cnnlTensorDescriptor_t value_desc,
                         const void *value,
                         cnnlTensorDescriptor_t mask_desc,
                         const void *mask,
                         cnnlTensorDescriptor_t curr_idx_desc,
                         const void *curr_idx,
                         cnnlTensorDescriptor_t key_cache_desc,
                         const void *key_cache,
                         cnnlTensorDescriptor_t value_cache_desc,
                         const void *value_cache,
                         cnnlTensorDescriptor_t best_beams_cache_desc,
                         const void *best_beams_cache,
                         void *workspace,
                         const size_t workspace_size,
                         cnnlTensorDescriptor_t output_qk_desc,
                         void *output_qk,
                         cnnlTensorDescriptor_t output_desc,
                         void *output);
#if defined(__cplusplus)
}
#endif

#endif  // CNNL_EXTRA_H_
