/*
 * Zustandsregler_types.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Zustandsregler".
 *
 * Model version              : 1.33
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Mon Jan 20 02:09:21 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Zustandsregler_types_h_
#define RTW_HEADER_Zustandsregler_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_Zustandsregler_std_msgs_Float32_
#define DEFINED_TYPEDEF_FOR_SL_Bus_Zustandsregler_std_msgs_Float32_

typedef struct {
  real32_T Data;
} SL_Bus_Zustandsregler_std_msgs_Float32;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_Zustandsregler_std_msgs_Float64_
#define DEFINED_TYPEDEF_FOR_SL_Bus_Zustandsregler_std_msgs_Float64_

typedef struct {
  real_T Data;
} SL_Bus_Zustandsregler_std_msgs_Float64;

#endif

#ifndef typedef_ros_slros_internal_block_Publ_T
#define typedef_ros_slros_internal_block_Publ_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
} ros_slros_internal_block_Publ_T;

#endif                               /*typedef_ros_slros_internal_block_Publ_T*/

#ifndef typedef_ros_slros_internal_block_Subs_T
#define typedef_ros_slros_internal_block_Subs_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
} ros_slros_internal_block_Subs_T;

#endif                               /*typedef_ros_slros_internal_block_Subs_T*/

/* Parameters for system: '<S3>/Enabled Subsystem' */
typedef struct P_EnabledSubsystem_Zustandsre_T_ P_EnabledSubsystem_Zustandsre_T;

/* Parameters (default storage) */
typedef struct P_Zustandsregler_T_ P_Zustandsregler_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_Zustandsregler_T RT_MODEL_Zustandsregler_T;

#endif                                 /* RTW_HEADER_Zustandsregler_types_h_ */
