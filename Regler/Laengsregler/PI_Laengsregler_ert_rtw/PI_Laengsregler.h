/*
 * PI_Laengsregler.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "PI_Laengsregler".
 *
 * Model version              : 1.25
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Sun Feb  2 23:15:39 2020
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

/* Block signals for system '<S4>/Enabled Subsystem' */
typedef struct {
  SL_Bus_PI_Laengsregler_std_msgs_Float32 In1;/* '<S51>/In1' */
} B_EnabledSubsystem_PI_Laengsr_T;

/* Block signals (default storage) */
typedef struct {
  real_T ProportionalGain;             /* '<S41>/Proportional Gain' */
  real_T IntegralGain;                 /* '<S33>/Integral Gain' */
  B_EnabledSubsystem_PI_Laengsr_T EnabledSubsystem_n;/* '<S5>/Enabled Subsystem' */
  B_EnabledSubsystem_PI_Laengsr_T EnabledSubsystem;/* '<S4>/Enabled Subsystem' */
} B_PI_Laengsregler_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  ros_slros_internal_block_Publ_T obj; /* '<S3>/SinkBlock' */
  ros_slros_internal_block_Subs_T obj_o;/* '<S5>/SourceBlock' */
  ros_slros_internal_block_Subs_T obj_j;/* '<S4>/SourceBlock' */
  boolean_T objisempty;                /* '<S5>/SourceBlock' */
  boolean_T objisempty_c;              /* '<S4>/SourceBlock' */
  boolean_T objisempty_f;              /* '<S3>/SinkBlock' */
} DW_PI_Laengsregler_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S36>/Integrator' */
} X_PI_Laengsregler_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S36>/Integrator' */
} XDot_PI_Laengsregler_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<S36>/Integrator' */
} XDis_PI_Laengsregler_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Parameters for system: '<S4>/Enabled Subsystem' */
struct P_EnabledSubsystem_PI_Laengsr_T_ {
  SL_Bus_PI_Laengsregler_std_msgs_Float32 Out1_Y0;/* Computed Parameter: Out1_Y0
                                                   * Referenced by: '<S51>/Out1'
                                                   */
};

/* Parameters (default storage) */
struct P_PI_Laengsregler_T_ {
  real_T ir;                           /* Variable: ir
                                        * Referenced by: '<S33>/Integral Gain'
                                        */
  real_T pr;                           /* Variable: pr
                                        * Referenced by: '<S41>/Proportional Gain'
                                        */
  real_T PIDController_InitialConditionF;
                              /* Mask Parameter: PIDController_InitialConditionF
                               * Referenced by: '<S36>/Integrator'
                               */
  SL_Bus_PI_Laengsregler_std_msgs_Float32 Constant_Value;/* Computed Parameter: Constant_Value
                                                          * Referenced by: '<S4>/Constant'
                                                          */
  SL_Bus_PI_Laengsregler_std_msgs_Float32 Constant_Value_l;/* Computed Parameter: Constant_Value_l
                                                            * Referenced by: '<S5>/Constant'
                                                            */
  SL_Bus_PI_Laengsregler_std_msgs_Int16 Constant_Value_j;/* Computed Parameter: Constant_Value_j
                                                          * Referenced by: '<S1>/Constant'
                                                          */
  real_T Gain_Gain;                    /* Expression: 1/0.175896
                                        * Referenced by: '<S2>/Gain'
                                        */
  P_EnabledSubsystem_PI_Laengsr_T EnabledSubsystem_n;/* '<S5>/Enabled Subsystem' */
  P_EnabledSubsystem_PI_Laengsr_T EnabledSubsystem;/* '<S4>/Enabled Subsystem' */
};

/* Real-time Model Data Structure */
struct tag_RTM_PI_Laengsregler_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_PI_Laengsregler_T *contStates;
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

/* Continuous states (default storage) */
extern X_PI_Laengsregler_T PI_Laengsregler_X;

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
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Data Type Conversion2' : Eliminate redundant data type conversion
 */

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
 * '<S2>'   : 'PI_Laengsregler/Geschwindigkeitsregler'
 * '<S3>'   : 'PI_Laengsregler/Publish'
 * '<S4>'   : 'PI_Laengsregler/Subscribe'
 * '<S5>'   : 'PI_Laengsregler/Subscribe1'
 * '<S6>'   : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller'
 * '<S7>'   : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Anti-windup'
 * '<S8>'   : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/D Gain'
 * '<S9>'   : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Filter'
 * '<S10>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Filter ICs'
 * '<S11>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/I Gain'
 * '<S12>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Ideal P Gain'
 * '<S13>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Ideal P Gain Fdbk'
 * '<S14>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Integrator'
 * '<S15>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Integrator ICs'
 * '<S16>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/N Copy'
 * '<S17>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/N Gain'
 * '<S18>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/P Copy'
 * '<S19>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Parallel P Gain'
 * '<S20>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Reset Signal'
 * '<S21>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Saturation'
 * '<S22>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Saturation Fdbk'
 * '<S23>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Sum'
 * '<S24>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Sum Fdbk'
 * '<S25>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Tracking Mode'
 * '<S26>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Tracking Mode Sum'
 * '<S27>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/postSat Signal'
 * '<S28>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/preSat Signal'
 * '<S29>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Anti-windup/Passthrough'
 * '<S30>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/D Gain/Disabled'
 * '<S31>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Filter/Disabled'
 * '<S32>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Filter ICs/Disabled'
 * '<S33>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/I Gain/Internal Parameters'
 * '<S34>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Ideal P Gain/Passthrough'
 * '<S35>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S36>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Integrator/Continuous'
 * '<S37>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Integrator ICs/Internal IC'
 * '<S38>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S39>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/N Gain/Disabled'
 * '<S40>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/P Copy/Disabled'
 * '<S41>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S42>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Reset Signal/Disabled'
 * '<S43>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Saturation/Passthrough'
 * '<S44>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Saturation Fdbk/Disabled'
 * '<S45>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Sum/Sum_PI'
 * '<S46>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Sum Fdbk/Disabled'
 * '<S47>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Tracking Mode/Disabled'
 * '<S48>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S49>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/postSat Signal/Forward_Path'
 * '<S50>'  : 'PI_Laengsregler/Geschwindigkeitsregler/PID Controller/preSat Signal/Forward_Path'
 * '<S51>'  : 'PI_Laengsregler/Subscribe/Enabled Subsystem'
 * '<S52>'  : 'PI_Laengsregler/Subscribe1/Enabled Subsystem'
 */
#endif                                 /* RTW_HEADER_PI_Laengsregler_h_ */
