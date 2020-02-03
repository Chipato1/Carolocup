/*
 * PI_Laengsregler_private.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "PI_Laengsregler".
 *
 * Model version              : 1.27
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Mon Feb  3 23:45:19 2020
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

extern void PI_Laengs_EnabledSubsystem_Init(B_EnabledSubsystem_PI_Laengsr_T
  *localB, P_EnabledSubsystem_PI_Laengsr_T *localP);
extern void PI_Laengsregle_EnabledSubsystem(boolean_T rtu_Enable, const
  SL_Bus_PI_Laengsregler_std_msgs_Float32 *rtu_In1,
  B_EnabledSubsystem_PI_Laengsr_T *localB);

#endif                               /* RTW_HEADER_PI_Laengsregler_private_h_ */
