/*
 * PI_Laengsregler.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "PI_Laengsregler".
 *
 * Model version              : 1.13
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Wed Jan 22 20:18:13 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
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
  SL_Bus_PI_Laengsregler_std_msgs_Float32 In1;/* '<S52>/In1' */
} B_EnabledSubsystem_PI_Laengsr_T;

/* Block signals (default storage) */
typedef struct {
  real_T Bu[2];                        /* '<S7>/Product' */
  real_T dx[2];                        /* '<S7>/Sum' */
  real_T Du;                           /* '<S7>/Product2' */
  real_T Sum1;                         /* '<S7>/Sum1' */
  real_T ProportionalGain;             /* '<S42>/Proportional Gain' */
  real_T DerivativeGain;               /* '<S31>/Derivative Gain' */
  real_T FilterCoefficient;            /* '<S40>/Filter Coefficient' */
  real_T Add1;                         /* '<S2>/Add1' */
  real_T IntegralGain;                 /* '<S34>/Integral Gain' */
  B_EnabledSubsystem_PI_Laengsr_T EnabledSubsystem_l;/* '<S5>/Enabled Subsystem' */
  B_EnabledSubsystem_PI_Laengsr_T EnabledSubsystem;/* '<S4>/Enabled Subsystem' */
} B_PI_Laengsregler_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  ros_slros_internal_block_Publ_T obj; /* '<S3>/SinkBlock' */
  ros_slros_internal_block_Subs_T obj_i;/* '<S5>/SourceBlock' */
  ros_slros_internal_block_Subs_T obj_iz;/* '<S4>/SourceBlock' */
  struct {
    void *LoggedData[2];
  } Scope2_PWORK;                      /* '<S2>/Scope2' */

  struct {
    void *LoggedData[2];
  } Scope_PWORK;                       /* '<S2>/Scope' */

  struct {
    void *LoggedData;
  } Scope1_PWORK;                      /* '<S2>/Scope1' */

  boolean_T objisempty;                /* '<S5>/SourceBlock' */
  boolean_T objisempty_c;              /* '<S4>/SourceBlock' */
  boolean_T objisempty_i;              /* '<S3>/SinkBlock' */
} DW_PI_Laengsregler_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE[2];         /* '<S7>/Integrator' */
  real_T Integrator_CSTATE_k;          /* '<S37>/Integrator' */
  real_T Filter_CSTATE;                /* '<S32>/Filter' */
} X_PI_Laengsregler_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE[2];         /* '<S7>/Integrator' */
  real_T Integrator_CSTATE_k;          /* '<S37>/Integrator' */
  real_T Filter_CSTATE;                /* '<S32>/Filter' */
} XDot_PI_Laengsregler_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE[2];      /* '<S7>/Integrator' */
  boolean_T Integrator_CSTATE_k;       /* '<S37>/Integrator' */
  boolean_T Filter_CSTATE;             /* '<S32>/Filter' */
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
                                                   * Referenced by: '<S52>/Out1'
                                                   */
};

/* Parameters (default storage) */
struct P_PI_Laengsregler_T_ {
  real_T A[4];                         /* Variable: A
                                        * Referenced by: '<S2>/Constant'
                                        */
  real_T b[2];                         /* Variable: b
                                        * Referenced by: '<S2>/Constant1'
                                        */
  real_T cT[2];                        /* Variable: cT
                                        * Referenced by: '<S2>/Constant2'
                                        */
  real_T ir;                           /* Variable: ir
                                        * Referenced by: '<S34>/Integral Gain'
                                        */
  real_T pr;                           /* Variable: pr
                                        * Referenced by: '<S42>/Proportional Gain'
                                        */
  real_T u;                            /* Variable: u
                                        * Referenced by: '<S2>/Multiply'
                                        */
  real_T PIDController1_D;             /* Mask Parameter: PIDController1_D
                                        * Referenced by: '<S31>/Derivative Gain'
                                        */
  real_T PIDController1_InitialCondition;
                              /* Mask Parameter: PIDController1_InitialCondition
                               * Referenced by: '<S32>/Filter'
                               */
  real_T PIDController1_InitialConditi_b;
                              /* Mask Parameter: PIDController1_InitialConditi_b
                               * Referenced by: '<S37>/Integrator'
                               */
  real_T PIDController1_N;             /* Mask Parameter: PIDController1_N
                                        * Referenced by: '<S40>/Filter Coefficient'
                                        */
  SL_Bus_PI_Laengsregler_std_msgs_Float32 Constant_Value;/* Computed Parameter: Constant_Value
                                                          * Referenced by: '<S4>/Constant'
                                                          */
  SL_Bus_PI_Laengsregler_std_msgs_Float32 Constant_Value_b;/* Computed Parameter: Constant_Value_b
                                                            * Referenced by: '<S5>/Constant'
                                                            */
  SL_Bus_PI_Laengsregler_std_msgs_Int32 Constant_Value_j;/* Computed Parameter: Constant_Value_j
                                                          * Referenced by: '<S1>/Constant'
                                                          */
  real_T Integrator_IC;                /* Expression: x0
                                        * Referenced by: '<S7>/Integrator'
                                        */
  real_T Constant3_Value;              /* Expression: 0
                                        * Referenced by: '<S2>/Constant3'
                                        */
  P_EnabledSubsystem_PI_Laengsr_T EnabledSubsystem_l;/* '<S5>/Enabled Subsystem' */
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
  real_T odeY[4];
  real_T odeF[3][4];
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
 * '<S2>'   : 'PI_Laengsregler/Geschwindigkeitsregler 1'
 * '<S3>'   : 'PI_Laengsregler/Publish'
 * '<S4>'   : 'PI_Laengsregler/Subscribe'
 * '<S5>'   : 'PI_Laengsregler/Subscribe1'
 * '<S6>'   : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1'
 * '<S7>'   : 'PI_Laengsregler/Geschwindigkeitsregler 1/Varying State Space'
 * '<S8>'   : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Anti-windup'
 * '<S9>'   : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/D Gain'
 * '<S10>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Filter'
 * '<S11>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Filter ICs'
 * '<S12>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/I Gain'
 * '<S13>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Ideal P Gain'
 * '<S14>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Ideal P Gain Fdbk'
 * '<S15>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Integrator'
 * '<S16>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Integrator ICs'
 * '<S17>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/N Copy'
 * '<S18>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/N Gain'
 * '<S19>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/P Copy'
 * '<S20>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Parallel P Gain'
 * '<S21>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Reset Signal'
 * '<S22>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Saturation'
 * '<S23>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Saturation Fdbk'
 * '<S24>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Sum'
 * '<S25>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Sum Fdbk'
 * '<S26>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Tracking Mode'
 * '<S27>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Tracking Mode Sum'
 * '<S28>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/postSat Signal'
 * '<S29>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/preSat Signal'
 * '<S30>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Anti-windup/Passthrough'
 * '<S31>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/D Gain/Internal Parameters'
 * '<S32>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Filter/Cont. Filter'
 * '<S33>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Filter ICs/Internal IC - Filter'
 * '<S34>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/I Gain/Internal Parameters'
 * '<S35>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Ideal P Gain/Passthrough'
 * '<S36>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S37>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Integrator/Continuous'
 * '<S38>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Integrator ICs/Internal IC'
 * '<S39>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/N Copy/Disabled'
 * '<S40>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/N Gain/Internal Parameters'
 * '<S41>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/P Copy/Disabled'
 * '<S42>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Parallel P Gain/Internal Parameters'
 * '<S43>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Reset Signal/Disabled'
 * '<S44>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Saturation/Passthrough'
 * '<S45>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Saturation Fdbk/Disabled'
 * '<S46>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Sum/Sum_PID'
 * '<S47>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Sum Fdbk/Disabled'
 * '<S48>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Tracking Mode/Disabled'
 * '<S49>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S50>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/postSat Signal/Forward_Path'
 * '<S51>'  : 'PI_Laengsregler/Geschwindigkeitsregler 1/PID Controller1/preSat Signal/Forward_Path'
 * '<S52>'  : 'PI_Laengsregler/Subscribe/Enabled Subsystem'
 * '<S53>'  : 'PI_Laengsregler/Subscribe1/Enabled Subsystem'
 */
#endif                                 /* RTW_HEADER_PI_Laengsregler_h_ */
