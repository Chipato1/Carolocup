/*
 * PI_Laengsregler_types.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "PI_Laengsregler".
 *
 * Model version              : 1.34
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Thu Feb  6 20:42:28 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_PI_Laengsregler_types_h_
#define RTW_HEADER_PI_Laengsregler_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_PI_Laengsregler_std_msgs_Int16_
#define DEFINED_TYPEDEF_FOR_SL_Bus_PI_Laengsregler_std_msgs_Int16_

typedef struct {
  int16_T Data;
} SL_Bus_PI_Laengsregler_std_msgs_Int16;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_PI_Laengsregler_std_msgs_Float32_
#define DEFINED_TYPEDEF_FOR_SL_Bus_PI_Laengsregler_std_msgs_Float32_

typedef struct {
  real32_T Data;
} SL_Bus_PI_Laengsregler_std_msgs_Float32;

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

/* Parameters for system: '<S4>/Enabled Subsystem' */
typedef struct P_EnabledSubsystem_PI_Laengsr_T_ P_EnabledSubsystem_PI_Laengsr_T;

/* Parameters (default storage) */
typedef struct P_PI_Laengsregler_T_ P_PI_Laengsregler_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_PI_Laengsregler_T RT_MODEL_PI_Laengsregler_T;

#endif                                 /* RTW_HEADER_PI_Laengsregler_types_h_ */
