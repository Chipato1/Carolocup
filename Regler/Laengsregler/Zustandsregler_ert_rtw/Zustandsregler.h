/*
 * Zustandsregler.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Zustandsregler".
 *
 * Model version              : 1.35
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Wed Jan 22 23:04:18 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Zustandsregler_h_
#define RTW_HEADER_Zustandsregler_h_
#include <string.h>
#include <stddef.h>
#ifndef Zustandsregler_COMMON_INCLUDES_
# define Zustandsregler_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "slros_initialize.h"
#endif                                 /* Zustandsregler_COMMON_INCLUDES_ */

#include "Zustandsregler_types.h"

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

/* Block signals for system '<S3>/Enabled Subsystem' */
typedef struct {
  SL_Bus_Zustandsregler_std_msgs_Float64 In1;/* '<S8>/In1' */
} B_EnabledSubsystem_Zustandsre_T;

/* Block signals (default storage) */
typedef struct {
  real_T x[2];                         /* '<S7>/Add' */
  real_T Product4;                     /* '<S7>/Product4' */
  real_T rtb_Add3_idx_0;
  real_T rtb_Add3_idx_1;
  real_T rtb_Add1_idx_0;
  B_EnabledSubsystem_Zustandsre_T EnabledSubsystem_a;/* '<S6>/Enabled Subsystem' */
  B_EnabledSubsystem_Zustandsre_T EnabledSubsystem_m;/* '<S5>/Enabled Subsystem' */
  B_EnabledSubsystem_Zustandsre_T EnabledSubsystem_p;/* '<S4>/Enabled Subsystem' */
  B_EnabledSubsystem_Zustandsre_T EnabledSubsystem;/* '<S3>/Enabled Subsystem' */
} B_Zustandsregler_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  ros_slros_internal_block_Publ_T obj; /* '<S2>/SinkBlock' */
  ros_slros_internal_block_Subs_T obj_a;/* '<S6>/SourceBlock' */
  ros_slros_internal_block_Subs_T obj_b;/* '<S5>/SourceBlock' */
  ros_slros_internal_block_Subs_T obj_k;/* '<S4>/SourceBlock' */
  ros_slros_internal_block_Subs_T obj_n;/* '<S3>/SourceBlock' */
  boolean_T objisempty;                /* '<S6>/SourceBlock' */
  boolean_T objisempty_k;              /* '<S5>/SourceBlock' */
  boolean_T objisempty_d;              /* '<S4>/SourceBlock' */
  boolean_T objisempty_j;              /* '<S3>/SourceBlock' */
  boolean_T objisempty_o;              /* '<S2>/SinkBlock' */
} DW_Zustandsregler_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE[2];         /* '<S7>/Integrator' */
} X_Zustandsregler_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE[2];         /* '<S7>/Integrator' */
} XDot_Zustandsregler_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE[2];      /* '<S7>/Integrator' */
} XDis_Zustandsregler_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Parameters for system: '<S3>/Enabled Subsystem' */
struct P_EnabledSubsystem_Zustandsre_T_ {
  SL_Bus_Zustandsregler_std_msgs_Float64 Out1_Y0;/* Computed Parameter: Out1_Y0
                                                  * Referenced by: '<S8>/Out1'
                                                  */
};

/* Parameters (default storage) */
struct P_Zustandsregler_T_ {
  real_T K[4];                         /* Variable: K
                                        * Referenced by: '<S7>/kT'
                                        */
  real_T ausgangsVektor_cT[2];         /* Variable: ausgangsVektor_cT
                                        * Referenced by: '<S7>/cT'
                                        */
  real_T d[2];                         /* Variable: d
                                        * Referenced by: '<S7>/d'
                                        */
  real_T eingangsVektor_b[4];          /* Variable: eingangsVektor_b
                                        * Referenced by: '<S7>/b'
                                        */
  real_T systemMatrix_A[4];            /* Variable: systemMatrix_A
                                        * Referenced by: '<S7>/A'
                                        */
  SL_Bus_Zustandsregler_std_msgs_Float32 Constant_Value;/* Computed Parameter: Constant_Value
                                                         * Referenced by: '<S1>/Constant'
                                                         */
  SL_Bus_Zustandsregler_std_msgs_Float64 Constant_Value_p;/* Computed Parameter: Constant_Value_p
                                                           * Referenced by: '<S3>/Constant'
                                                           */
  SL_Bus_Zustandsregler_std_msgs_Float64 Constant_Value_o;/* Computed Parameter: Constant_Value_o
                                                           * Referenced by: '<S4>/Constant'
                                                           */
  SL_Bus_Zustandsregler_std_msgs_Float64 Constant_Value_e;/* Computed Parameter: Constant_Value_e
                                                           * Referenced by: '<S5>/Constant'
                                                           */
  SL_Bus_Zustandsregler_std_msgs_Float64 Constant_Value_j;/* Computed Parameter: Constant_Value_j
                                                           * Referenced by: '<S6>/Constant'
                                                           */
  real_T Multiply2_Gain[2];            /* Expression: [1;0]
                                        * Referenced by: '<S7>/Multiply2'
                                        */
  real_T Multiply3_Gain[2];            /* Expression: [0;1]
                                        * Referenced by: '<S7>/Multiply3'
                                        */
  real_T Multiply_Gain[2];             /* Expression: [1;0]
                                        * Referenced by: '<S7>/Multiply'
                                        */
  real_T Multiply1_Gain[2];            /* Expression: [0;1]
                                        * Referenced by: '<S7>/Multiply1'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<S7>/Integrator'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 0.349
                                        * Referenced by: '<S7>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -0.349
                                        * Referenced by: '<S7>/Saturation'
                                        */
  P_EnabledSubsystem_Zustandsre_T EnabledSubsystem_a;/* '<S6>/Enabled Subsystem' */
  P_EnabledSubsystem_Zustandsre_T EnabledSubsystem_m;/* '<S5>/Enabled Subsystem' */
  P_EnabledSubsystem_Zustandsre_T EnabledSubsystem_p;/* '<S4>/Enabled Subsystem' */
  P_EnabledSubsystem_Zustandsre_T EnabledSubsystem;/* '<S3>/Enabled Subsystem' */
};

/* Real-time Model Data Structure */
struct tag_RTM_Zustandsregler_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_Zustandsregler_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[2];
  real_T odeF[3][2];
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

  extern P_Zustandsregler_T Zustandsregler_P;

#ifdef __cplusplus

}
#endif

/* Block signals (default storage) */
#ifdef __cplusplus

extern "C" {

#endif

  extern B_Zustandsregler_T Zustandsregler_B;

#ifdef __cplusplus

}
#endif

/* Continuous states (default storage) */
extern X_Zustandsregler_T Zustandsregler_X;

/* Block states (default storage) */
extern DW_Zustandsregler_T Zustandsregler_DW;

#ifdef __cplusplus

extern "C" {

#endif

  /* Model entry point functions */
  extern void Zustandsregler_initialize(void);
  extern void Zustandsregler_step(void);
  extern void Zustandsregler_terminate(void);

#ifdef __cplusplus

}
#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_Zustandsregler_T *const Zustandsregler_M;

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
 * '<Root>' : 'Zustandsregler'
 * '<S1>'   : 'Zustandsregler/Blank Message'
 * '<S2>'   : 'Zustandsregler/Publish'
 * '<S3>'   : 'Zustandsregler/Subscribe'
 * '<S4>'   : 'Zustandsregler/Subscribe1'
 * '<S5>'   : 'Zustandsregler/Subscribe2'
 * '<S6>'   : 'Zustandsregler/Subscribe3'
 * '<S7>'   : 'Zustandsregler/Zustandsregler 1'
 * '<S8>'   : 'Zustandsregler/Subscribe/Enabled Subsystem'
 * '<S9>'   : 'Zustandsregler/Subscribe1/Enabled Subsystem'
 * '<S10>'  : 'Zustandsregler/Subscribe2/Enabled Subsystem'
 * '<S11>'  : 'Zustandsregler/Subscribe3/Enabled Subsystem'
 */
#endif                                 /* RTW_HEADER_Zustandsregler_h_ */
