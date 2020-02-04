/*
 * Stanley_Querregler_private.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Stanley_Querregler".
 *
 * Model version              : 1.19
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Tue Feb  4 19:48:55 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Stanley_Querregler_private_h_
#define RTW_HEADER_Stanley_Querregler_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "Stanley_Querregler.h"

extern void Stanley_Q_EnabledSubsystem_Init(B_EnabledSubsystem_Stanley_Qu_T
  *localB, P_EnabledSubsystem_Stanley_Qu_T *localP);
extern void Stanley_Querre_EnabledSubsystem(boolean_T rtu_Enable, const
  SL_Bus_Stanley_Querregler_std_msgs_Float32 *rtu_In1,
  B_EnabledSubsystem_Stanley_Qu_T *localB);

#endif                            /* RTW_HEADER_Stanley_Querregler_private_h_ */
