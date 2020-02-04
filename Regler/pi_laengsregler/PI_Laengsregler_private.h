/*
 * PI_Laengsregler_private.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "PI_Laengsregler".
 *
 * Model version              : 1.28
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Tue Feb  4 19:48:04 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_PI_Laengsregler_private_h_
#define RTW_HEADER_PI_Laengsregler_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "PI_Laengsregler.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

extern void PI_Laengs_EnabledSubsystem_Init(B_EnabledSubsystem_PI_Laengsr_T
  *localB, P_EnabledSubsystem_PI_Laengsr_T *localP);
extern void PI_Laengsregle_EnabledSubsystem(boolean_T rtu_Enable, const
  SL_Bus_PI_Laengsregler_std_msgs_Float32 *rtu_In1,
  B_EnabledSubsystem_PI_Laengsr_T *localB);

/* private model entry point functions */
extern void PI_Laengsregler_derivatives(void);

#endif                               /* RTW_HEADER_PI_Laengsregler_private_h_ */
