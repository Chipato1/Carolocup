/*
 * Stanley_Querregler.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Stanley_Querregler".
 *
 * Model version              : 1.11
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Wed Jan 29 19:20:14 2020
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

/* Block signals for system '<S3>/Enabled Subsystem' */
typedef struct {
  SL_Bus_Stanley_Querregler_std_msgs_Float32 In1;/* '<S6>/In1' */
} B_EnabledSubsystem_Stanley_Qu_T;

/* Block signals (default storage) */
typedef struct {
  real_T refPose[3];
  real_T currPose[3];
  real_T b;
  B_EnabledSubsystem_Stanley_Qu_T EnabledSubsystem_e;/* '<S4>/Enabled Subsystem' */
  B_EnabledSubsystem_Stanley_Qu_T EnabledSubsystem;/* '<S3>/Enabled Subsystem' */
} B_Stanley_Querregler_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  ros_slros_internal_block_Publ_T obj; /* '<S2>/SinkBlock' */
  ros_slros_internal_block_Subs_T obj_p;/* '<S4>/SourceBlock' */
  ros_slros_internal_block_Subs_T obj_o;/* '<S3>/SourceBlock' */
  boolean_T objisempty;                /* '<S4>/SourceBlock' */
  boolean_T objisempty_h;              /* '<S3>/SourceBlock' */
  boolean_T objisempty_d;              /* '<S2>/SinkBlock' */
} DW_Stanley_Querregler_T;

/* Parameters for system: '<S3>/Enabled Subsystem' */
struct P_EnabledSubsystem_Stanley_Qu_T_ {
  SL_Bus_Stanley_Querregler_std_msgs_Float32 Out1_Y0;/* Computed Parameter: Out1_Y0
                                                      * Referenced by: '<S6>/Out1'
                                                      */
};

/* Parameters (default storage) */
struct P_Stanley_Querregler_T_ {
  real_T LateralControllerStanley_Positi;
                              /* Mask Parameter: LateralControllerStanley_Positi
                               * Referenced by: '<S9>/Kinematic'
                               */
  real_T LateralControllerStanley_Posi_o;
                              /* Mask Parameter: LateralControllerStanley_Posi_o
                               * Referenced by: '<S9>/Kinematic'
                               */
  SL_Bus_Stanley_Querregler_std_msgs_Float32 Constant_Value;/* Computed Parameter: Constant_Value
                                                             * Referenced by: '<S3>/Constant'
                                                             */
  SL_Bus_Stanley_Querregler_std_msgs_Float32 Constant_Value_f;/* Computed Parameter: Constant_Value_f
                                                               * Referenced by: '<S4>/Constant'
                                                               */
  SL_Bus_Stanley_Querregler_std_msgs_Float32 Constant_Value_m;/* Computed Parameter: Constant_Value_m
                                                               * Referenced by: '<S1>/Constant'
                                                               */
  real_T Gain_Gain;                    /* Expression: -1
                                        * Referenced by: '<S5>/Gain'
                                        */
  real_T Rckwrts_Value;                /* Expression: -1
                                        * Referenced by: '<S5>/Rückwärts'
                                        */
  real_T Vorwrts_Value;                /* Expression: 1
                                        * Referenced by: '<S5>/Vorwärts'
                                        */
  real_T Kinematic_MaxSteeringAngle;   /* Expression: MaxSteeringAngle
                                        * Referenced by: '<S9>/Kinematic'
                                        */
  real_T Kinematic_Wheelbase;          /* Expression: Wheelbase
                                        * Referenced by: '<S9>/Kinematic'
                                        */
  real_T xytheta_Value[3];             /* Expression: [0.4, 0, 0]
                                        * Referenced by: '<S5>/[x, y, theta]'
                                        */
  real_T Constant1_Value[3];           /* Expression: [0 1 0]
                                        * Referenced by: '<S5>/Constant1'
                                        */
  real_T Constant_Value_h[3];          /* Expression: [0 0 0]
                                        * Referenced by: '<S5>/Constant'
                                        */
  real_T Constant_Value_mh;            /* Expression: 2*pi
                                        * Referenced by: '<S8>/Constant'
                                        */
  real_T Radiuscm_Value;               /* Expression: 5.6/2
                                        * Referenced by: '<S8>/Radius (cm)'
                                        */
  real_T cminm_Gain;                   /* Expression: 0.01
                                        * Referenced by: '<S8>/cm in m'
                                        */
  real_T Switch1_Threshold;            /* Expression: 0
                                        * Referenced by: '<S5>/Switch1'
                                        */
  real_T Switch_Threshold;             /* Expression: 0
                                        * Referenced by: '<S5>/Switch'
                                        */
  P_EnabledSubsystem_Stanley_Qu_T EnabledSubsystem_e;/* '<S4>/Enabled Subsystem' */
  P_EnabledSubsystem_Stanley_Qu_T EnabledSubsystem;/* '<S3>/Enabled Subsystem' */
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
 * '<S3>'   : 'Stanley_Querregler/Subscribe2'
 * '<S4>'   : 'Stanley_Querregler/Subscribe3'
 * '<S5>'   : 'Stanley_Querregler/Subsystem1'
 * '<S6>'   : 'Stanley_Querregler/Subscribe2/Enabled Subsystem'
 * '<S7>'   : 'Stanley_Querregler/Subscribe3/Enabled Subsystem'
 * '<S8>'   : 'Stanley_Querregler/Subsystem1/Drehzahl in Geschwindigkeit  umrechnen'
 * '<S9>'   : 'Stanley_Querregler/Subsystem1/Lateral Controller Stanley'
 * '<S10>'  : 'Stanley_Querregler/Subsystem1/Lateral Controller Stanley/Dynamic'
 * '<S11>'  : 'Stanley_Querregler/Subsystem1/Lateral Controller Stanley/Kinematic'
 * '<S12>'  : 'Stanley_Querregler/Subsystem1/Lateral Controller Stanley/Dynamic/Dynamic Disabled'
 */
#endif                                 /* RTW_HEADER_Stanley_Querregler_h_ */
