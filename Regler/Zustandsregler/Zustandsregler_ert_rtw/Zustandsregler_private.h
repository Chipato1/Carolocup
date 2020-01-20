/*
 * Zustandsregler_private.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Zustandsregler".
 *
 * Model version              : 1.33
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Mon Jan 20 02:09:21 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Zustandsregler_private_h_
#define RTW_HEADER_Zustandsregler_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "Zustandsregler.h"

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

extern void Zustandsr_EnabledSubsystem_Init(B_EnabledSubsystem_Zustandsre_T
  *localB, P_EnabledSubsystem_Zustandsre_T *localP);
extern void Zustandsregler_EnabledSubsystem(boolean_T rtu_Enable, const
  SL_Bus_Zustandsregler_std_msgs_Float64 *rtu_In1,
  B_EnabledSubsystem_Zustandsre_T *localB);

/* private model entry point functions */
extern void Zustandsregler_derivatives(void);

#endif                                /* RTW_HEADER_Zustandsregler_private_h_ */
