/*
 * raddrehzahl_filter.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "raddrehzahl_filter".
 *
 * Model version              : 1.9
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Tue Feb  4 19:28:58 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_raddrehzahl_filter_h_
#define RTW_HEADER_raddrehzahl_filter_h_
#include <string.h>
#include <stddef.h>
#ifndef raddrehzahl_filter_COMMON_INCLUDES_
# define raddrehzahl_filter_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "slros_initialize.h"
#endif                                 /* raddrehzahl_filter_COMMON_INCLUDES_ */

#include "raddrehzahl_filter_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
# define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
# define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
# define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
# define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
# define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
# define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

/* Block signals for system '<S6>/Enabled Subsystem' */
typedef struct {
  SL_Bus_raddrehzahl_filter_std_msgs_Float32 In1;/* '<S9>/In1' */
} B_EnabledSubsystem_raddrehzah_T;

/* Block signals (default storage) */
typedef struct {
  real_T Switch;                       /* '<Root>/Switch' */
  SL_Bus_raddrehzahl_filter_std_msgs_Bool In1;/* '<S8>/In1' */
  B_EnabledSubsystem_raddrehzah_T EnabledSubsystem_b;/* '<S7>/Enabled Subsystem' */
  B_EnabledSubsystem_raddrehzah_T EnabledSubsystem_a;/* '<S6>/Enabled Subsystem' */
} B_raddrehzahl_filter_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  ros_slros_internal_block_Publ_T obj; /* '<S4>/SinkBlock' */
  ros_slros_internal_block_Publ_T obj_i;/* '<S3>/SinkBlock' */
  ros_slros_internal_block_Subs_T obj_d;/* '<S7>/SourceBlock' */
  ros_slros_internal_block_Subs_T obj_dl;/* '<S6>/SourceBlock' */
  ros_slros_internal_block_Subs_T obj_m;/* '<S5>/SourceBlock' */
  real_T DiscreteTransferFcn_states[2];/* '<Root>/Discrete Transfer Fcn' */
  real_T DiscreteTransferFcn_tmp;      /* '<Root>/Discrete Transfer Fcn' */
  boolean_T objisempty;                /* '<S7>/SourceBlock' */
  boolean_T objisempty_o;              /* '<S6>/SourceBlock' */
  boolean_T objisempty_g;              /* '<S5>/SourceBlock' */
  boolean_T objisempty_j;              /* '<S4>/SinkBlock' */
  boolean_T objisempty_k;              /* '<S3>/SinkBlock' */
} DW_raddrehzahl_filter_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
} X_raddrehzahl_filter_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
} XDot_raddrehzahl_filter_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<Root>/Integrator' */
} XDis_raddrehzahl_filter_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Parameters for system: '<S6>/Enabled Subsystem' */
struct P_EnabledSubsystem_raddrehzah_T_ {
  SL_Bus_raddrehzahl_filter_std_msgs_Float32 Out1_Y0;/* Computed Parameter: Out1_Y0
                                                      * Referenced by: '<S9>/Out1'
                                                      */
};

/* Parameters (default storage) */
struct P_raddrehzahl_filter_T_ {
  real_T denom_drehzahl[3];            /* Variable: denom_drehzahl
                                        * Referenced by: '<Root>/Discrete Transfer Fcn'
                                        */
  real_T num_drehzahl[3];              /* Variable: num_drehzahl
                                        * Referenced by: '<Root>/Discrete Transfer Fcn'
                                        */
  SL_Bus_raddrehzahl_filter_std_msgs_Bool Out1_Y0;/* Computed Parameter: Out1_Y0
                                                   * Referenced by: '<S8>/Out1'
                                                   */
  SL_Bus_raddrehzahl_filter_std_msgs_Bool Constant_Value;/* Computed Parameter: Constant_Value
                                                          * Referenced by: '<S5>/Constant'
                                                          */
  SL_Bus_raddrehzahl_filter_std_msgs_Float32 Constant_Value_j;/* Computed Parameter: Constant_Value_j
                                                               * Referenced by: '<S6>/Constant'
                                                               */
  SL_Bus_raddrehzahl_filter_std_msgs_Float32 Constant_Value_m;/* Computed Parameter: Constant_Value_m
                                                               * Referenced by: '<S7>/Constant'
                                                               */
  SL_Bus_raddrehzahl_filter_std_msgs_Float32 Constant_Value_l;/* Computed Parameter: Constant_Value_l
                                                               * Referenced by: '<S1>/Constant'
                                                               */
  SL_Bus_raddrehzahl_filter_std_msgs_Float32 Constant_Value_n;/* Computed Parameter: Constant_Value_n
                                                               * Referenced by: '<S2>/Constant'
                                                               */
  real_T Multiply_Gain;                /* Expression: 0.175896
                                        * Referenced by: '<Root>/Multiply'
                                        */
  real_T DiscreteTransferFcn_InitialStat;/* Expression: 0
                                          * Referenced by: '<Root>/Discrete Transfer Fcn'
                                          */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<Root>/Integrator'
                                        */
  P_EnabledSubsystem_raddrehzah_T EnabledSubsystem_b;/* '<S7>/Enabled Subsystem' */
  P_EnabledSubsystem_raddrehzah_T EnabledSubsystem_a;/* '<S6>/Enabled Subsystem' */
};

/* Real-time Model Data Structure */
struct tag_RTM_raddrehzahl_filter_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_raddrehzahl_filter_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[1];
  real_T odeF[3][1];
  ODE3_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
#ifdef __cplusplus

extern "C" {

#endif

  extern P_raddrehzahl_filter_T raddrehzahl_filter_P;

#ifdef __cplusplus

}
#endif

/* Block signals (default storage) */
#ifdef __cplusplus

extern "C" {

#endif

  extern B_raddrehzahl_filter_T raddrehzahl_filter_B;

#ifdef __cplusplus

}
#endif

/* Continuous states (default storage) */
extern X_raddrehzahl_filter_T raddrehzahl_filter_X;

/* Block states (default storage) */
extern DW_raddrehzahl_filter_T raddrehzahl_filter_DW;

#ifdef __cplusplus

extern "C" {

#endif

  /* Model entry point functions */
  extern void raddrehzahl_filter_initialize(void);
  extern void raddrehzahl_filter_step(void);
  extern void raddrehzahl_filter_terminate(void);

#ifdef __cplusplus

}
#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_raddrehzahl_filter_T *const raddrehzahl_filter_M;

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
 * '<Root>' : 'raddrehzahl_filter'
 * '<S1>'   : 'raddrehzahl_filter/Blank Message'
 * '<S2>'   : 'raddrehzahl_filter/Blank Message1'
 * '<S3>'   : 'raddrehzahl_filter/Publish'
 * '<S4>'   : 'raddrehzahl_filter/Publish1'
 * '<S5>'   : 'raddrehzahl_filter/Subscribe'
 * '<S6>'   : 'raddrehzahl_filter/Subscribe1'
 * '<S7>'   : 'raddrehzahl_filter/Subscribe2'
 * '<S8>'   : 'raddrehzahl_filter/Subscribe/Enabled Subsystem'
 * '<S9>'   : 'raddrehzahl_filter/Subscribe1/Enabled Subsystem'
 * '<S10>'  : 'raddrehzahl_filter/Subscribe2/Enabled Subsystem'
 */
#endif                                 /* RTW_HEADER_raddrehzahl_filter_h_ */
