/*
 * raddrehzahl_filter_private.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "raddrehzahl_filter".
 *
 * Model version              : 1.10
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Tue Feb  4 19:46:14 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_raddrehzahl_filter_private_h_
#define RTW_HEADER_raddrehzahl_filter_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "raddrehzahl_filter.h"

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

extern void raddrehza_EnabledSubsystem_Init(B_EnabledSubsystem_raddrehzah_T
  *localB, P_EnabledSubsystem_raddrehzah_T *localP);
extern void raddrehzahl_fi_EnabledSubsystem(boolean_T rtu_Enable, const
  SL_Bus_raddrehzahl_filter_std_msgs_Float32 *rtu_In1,
  B_EnabledSubsystem_raddrehzah_T *localB);

/* private model entry point functions */
extern void raddrehzahl_filter_derivatives(void);

#endif                            /* RTW_HEADER_raddrehzahl_filter_private_h_ */
