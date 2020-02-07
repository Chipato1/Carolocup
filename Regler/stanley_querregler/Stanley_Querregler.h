/*
 * Stanley_Querregler.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Stanley_Querregler".
 *
 * Model version              : 1.22
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Fri Feb  7 18:21:47 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Stanley_Querregler_h_
#define RTW_HEADER_Stanley_Querregler_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef Stanley_Querregler_COMMON_INCLUDES_
# define Stanley_Querregler_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "slros_initialize.h"
#endif                                 /* Stanley_Querregler_COMMON_INCLUDES_ */

#include "Stanley_Querregler_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals for system '<S4>/Enabled Subsystem' */
typedef struct {
  SL_Bus_Stanley_Querregler_std_msgs_Float32 In1;/* '<S9>/In1' */
} B_EnabledSubsystem_Stanley_Qu_T;

/* Block signals (default storage) */
typedef struct {
  char_T cv[26];
  real_T refPose[3];
  real_T currPose[3];
  char_T cv1[19];
  real_T Bogenma;                      /* '<S7>/Bogenmaß' */
  real_T b;
  SL_Bus_Stanley_Querregler_std_msgs_Bool In1;/* '<S8>/In1' */
  B_EnabledSubsystem_Stanley_Qu_T EnabledSubsystem_i;/* '<S6>/Enabled Subsystem' */
  B_EnabledSubsystem_Stanley_Qu_T EnabledSubsystem_p;/* '<S5>/Enabled Subsystem' */
  B_EnabledSubsystem_Stanley_Qu_T EnabledSubsystem_g;/* '<S4>/Enabled Subsystem' */
} B_Stanley_Querregler_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  ros_slros_internal_block_Publ_T obj; /* '<S2>/SinkBlock' */
  ros_slros_internal_block_Subs_T obj_c;/* '<S6>/SourceBlock' */
  ros_slros_internal_block_Subs_T obj_o;/* '<S5>/SourceBlock' */
  ros_slros_internal_block_Subs_T obj_e;/* '<S4>/SourceBlock' */
  ros_slros_internal_block_Subs_T obj_l;/* '<S3>/SourceBlock' */
  boolean_T objisempty;                /* '<S6>/SourceBlock' */
  boolean_T objisempty_h;              /* '<S5>/SourceBlock' */
  boolean_T objisempty_d;              /* '<S4>/SourceBlock' */
  boolean_T objisempty_n;              /* '<S3>/SourceBlock' */
  boolean_T objisempty_p;              /* '<S2>/SinkBlock' */
} DW_Stanley_Querregler_T;

/* Parameters for system: '<S4>/Enabled Subsystem' */
struct P_EnabledSubsystem_Stanley_Qu_T_ {
  SL_Bus_Stanley_Querregler_std_msgs_Float32 Out1_Y0;/* Computed Parameter: Out1_Y0
                                                      * Referenced by: '<S9>/Out1'
                                                      */
};

/* Parameters (default storage) */
struct P_Stanley_Querregler_T_ {
  real_T LateralControllerStanley_Positi;
                              /* Mask Parameter: LateralControllerStanley_Positi
                               * Referenced by: '<S12>/Kinematic'
                               */
  real_T LateralControllerStanley_Posi_p;
                              /* Mask Parameter: LateralControllerStanley_Posi_p
                               * Referenced by: '<S12>/Kinematic'
                               */
  SL_Bus_Stanley_Querregler_std_msgs_Bool Out1_Y0;/* Computed Parameter: Out1_Y0
                                                   * Referenced by: '<S8>/Out1'
                                                   */
  SL_Bus_Stanley_Querregler_std_msgs_Bool Constant_Value;/* Computed Parameter: Constant_Value
                                                          * Referenced by: '<S3>/Constant'
                                                          */
  SL_Bus_Stanley_Querregler_std_msgs_Float32 Constant_Value_d;/* Computed Parameter: Constant_Value_d
                                                               * Referenced by: '<S4>/Constant'
                                                               */
  SL_Bus_Stanley_Querregler_std_msgs_Float32 Constant_Value_c;/* Computed Parameter: Constant_Value_c
                                                               * Referenced by: '<S5>/Constant'
                                                               */
  SL_Bus_Stanley_Querregler_std_msgs_Float32 Constant_Value_i;/* Computed Parameter: Constant_Value_i
                                                               * Referenced by: '<S6>/Constant'
                                                               */
  SL_Bus_Stanley_Querregler_std_msgs_Float32 Constant_Value_k;/* Computed Parameter: Constant_Value_k
                                                               * Referenced by: '<S1>/Constant'
                                                               */
  real_T Gain_Gain;                    /* Expression: -1
                                        * Referenced by: '<S7>/Gain'
                                        */
  real_T Rckwrts_Value;                /* Expression: -1
                                        * Referenced by: '<S7>/Rückwärts'
                                        */
  real_T Vorwrts_Value;                /* Expression: 1
                                        * Referenced by: '<S7>/Vorwärts'
                                        */
  real_T Kinematic_MaxSteeringAngle;   /* Expression: MaxSteeringAngle
                                        * Referenced by: '<S12>/Kinematic'
                                        */
  real_T Kinematic_Wheelbase;          /* Expression: Wheelbase
                                        * Referenced by: '<S12>/Kinematic'
                                        */
  real_T Lenkwinkel_Y0;                /* Computed Parameter: Lenkwinkel_Y0
                                        * Referenced by: '<S7>/Lenkwinkel'
                                        */
  real_T _Value[3];                    /* Expression: [0.4, 0, 0]
                                        * Referenced by: '<S7>/ '
                                        */
  real_T _Value_m[3];                  /* Expression: [0 1 00000]
                                        * Referenced by: '<S7>/  '
                                        */
  real_T xytheta_Value[3];             /* Expression: [0 0 0000000]
                                        * Referenced by: '<S7>/[x, y, theta]'
                                        */
  real_T Switch1_Threshold;            /* Expression: 0
                                        * Referenced by: '<S7>/Switch1'
                                        */
  real_T Switch_Threshold;             /* Expression: 0
                                        * Referenced by: '<S7>/Switch'
                                        */
  real_T Sttigung_UpperSat;            /* Expression: 20
                                        * Referenced by: '<S7>/Sättigung'
                                        */
  real_T Sttigung_LowerSat;            /* Expression: -20
                                        * Referenced by: '<S7>/Sättigung'
                                        */
  real_T Bogenma_Gain;                 /* Expression: pi/180
                                        * Referenced by: '<S7>/Bogenmaß'
                                        */
  real32_T Gain1_Gain;                 /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<S7>/Gain1'
                                        */
  P_EnabledSubsystem_Stanley_Qu_T EnabledSubsystem_i;/* '<S6>/Enabled Subsystem' */
  P_EnabledSubsystem_Stanley_Qu_T EnabledSubsystem_p;/* '<S5>/Enabled Subsystem' */
  P_EnabledSubsystem_Stanley_Qu_T EnabledSubsystem_g;/* '<S4>/Enabled Subsystem' */
};

/* Real-time Model Data Structure */
struct tag_RTM_Stanley_Querregler_T {
  const char_T *errorStatus;
};

/* Block parameters (default storage) */
#ifdef __cplusplus

extern "C" {

#endif

  extern P_Stanley_Querregler_T Stanley_Querregler_P;

#ifdef __cplusplus

}
#endif

/* Block signals (default storage) */
#ifdef __cplusplus

extern "C" {

#endif

  extern B_Stanley_Querregler_T Stanley_Querregler_B;

#ifdef __cplusplus

}
#endif

/* Block states (default storage) */
extern DW_Stanley_Querregler_T Stanley_Querregler_DW;

#ifdef __cplusplus

extern "C" {

#endif

  /* Model entry point functions */
  extern void Stanley_Querregler_initialize(void);
  extern void Stanley_Querregler_step(void);
  extern void Stanley_Querregler_terminate(void);

#ifdef __cplusplus

}
#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_Stanley_Querregler_T *const Stanley_Querregler_M;

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
 * '<Root>' : 'Stanley_Querregler'
 * '<S1>'   : 'Stanley_Querregler/Blank Message'
 * '<S2>'   : 'Stanley_Querregler/Publish1'
 * '<S3>'   : 'Stanley_Querregler/Subscribe1'
 * '<S4>'   : 'Stanley_Querregler/Subscribe2'
 * '<S5>'   : 'Stanley_Querregler/Subscribe3'
 * '<S6>'   : 'Stanley_Querregler/Subscribe4'
 * '<S7>'   : 'Stanley_Querregler/Subsystem'
 * '<S8>'   : 'Stanley_Querregler/Subscribe1/Enabled Subsystem'
 * '<S9>'   : 'Stanley_Querregler/Subscribe2/Enabled Subsystem'
 * '<S10>'  : 'Stanley_Querregler/Subscribe3/Enabled Subsystem'
 * '<S11>'  : 'Stanley_Querregler/Subscribe4/Enabled Subsystem'
 * '<S12>'  : 'Stanley_Querregler/Subsystem/Lateral Controller Stanley'
 * '<S13>'  : 'Stanley_Querregler/Subsystem/Lateral Controller Stanley/Dynamic'
 * '<S14>'  : 'Stanley_Querregler/Subsystem/Lateral Controller Stanley/Kinematic'
 * '<S15>'  : 'Stanley_Querregler/Subsystem/Lateral Controller Stanley/Dynamic/Dynamic Disabled'
 */
#endif                                 /* RTW_HEADER_Stanley_Querregler_h_ */
