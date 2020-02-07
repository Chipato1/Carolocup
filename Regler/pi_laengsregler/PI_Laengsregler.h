/*
 * PI_Laengsregler.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "PI_Laengsregler".
 *
 * Model version              : 1.36
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Fri Feb  7 18:15:48 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_PI_Laengsregler_h_
#define RTW_HEADER_PI_Laengsregler_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef PI_Laengsregler_COMMON_INCLUDES_
# define PI_Laengsregler_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "slros_initialize.h"
#endif                                 /* PI_Laengsregler_COMMON_INCLUDES_ */

#include "PI_Laengsregler_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  SL_Bus_PI_Laengsregler_std_msgs_Float32 In1;/* '<S4>/In1' */
} B_PI_Laengsregler_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  ros_slros_internal_block_Publ_T obj; /* '<S2>/SinkBlock' */
  ros_slros_internal_block_Subs_T obj_j;/* '<S3>/SourceBlock' */
  boolean_T objisempty;                /* '<S3>/SourceBlock' */
  boolean_T objisempty_f;              /* '<S2>/SinkBlock' */
} DW_PI_Laengsregler_T;

/* Parameters (default storage) */
struct P_PI_Laengsregler_T_ {
  SL_Bus_PI_Laengsregler_std_msgs_Float32 Out1_Y0;/* Computed Parameter: Out1_Y0
                                                   * Referenced by: '<S4>/Out1'
                                                   */
  SL_Bus_PI_Laengsregler_std_msgs_Float32 Constant_Value;/* Computed Parameter: Constant_Value
                                                          * Referenced by: '<S3>/Constant'
                                                          */
  SL_Bus_PI_Laengsregler_std_msgs_Int16 Constant_Value_j;/* Computed Parameter: Constant_Value_j
                                                          * Referenced by: '<S1>/Constant'
                                                          */
  real_T Saturation_UpperSat;          /* Expression: 2.63
                                        * Referenced by: '<Root>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -2.63
                                        * Referenced by: '<Root>/Saturation'
                                        */
  real_T Radumfang_Gain;               /* Expression: 1/0.175896
                                        * Referenced by: '<Root>/Radumfang'
                                        */
  real_T Getriebe_Gain;                /* Expression: 7
                                        * Referenced by: '<Root>/Getriebe'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_PI_Laengsregler_T {
  const char_T *errorStatus;
};

/* Block parameters (default storage) */
#ifdef __cplusplus

extern "C" {

#endif

  extern P_PI_Laengsregler_T PI_Laengsregler_P;

#ifdef __cplusplus

}
#endif

/* Block signals (default storage) */
#ifdef __cplusplus

extern "C" {

#endif

  extern B_PI_Laengsregler_T PI_Laengsregler_B;

#ifdef __cplusplus

}
#endif

/* Block states (default storage) */
extern DW_PI_Laengsregler_T PI_Laengsregler_DW;

#ifdef __cplusplus

extern "C" {

#endif

  /* Model entry point functions */
  extern void PI_Laengsregler_initialize(void);
  extern void PI_Laengsregler_step(void);
  extern void PI_Laengsregler_terminate(void);

#ifdef __cplusplus

}
#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_PI_Laengsregler_T *const PI_Laengsregler_M;

#ifdef __cplusplus

}
#endif

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'PI_Laengsregler'
 * '<S1>'   : 'PI_Laengsregler/Blank Message'
 * '<S2>'   : 'PI_Laengsregler/Publish'
 * '<S3>'   : 'PI_Laengsregler/Subscribe'
 * '<S4>'   : 'PI_Laengsregler/Subscribe/Enabled Subsystem'
 */
#endif                                 /* RTW_HEADER_PI_Laengsregler_h_ */
