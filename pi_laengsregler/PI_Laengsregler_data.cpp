/*
 * PI_Laengsregler_data.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "PI_Laengsregler".
 *
 * Model version              : 1.36
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Fri Feb  7 18:15:48 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "PI_Laengsregler.h"
#include "PI_Laengsregler_private.h"

/* Block parameters (default storage) */
P_PI_Laengsregler_T PI_Laengsregler_P = {
  /* Computed Parameter: Out1_Y0
   * Referenced by: '<S4>/Out1'
   */
  {
    0.0F                               /* Data */
  },

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S3>/Constant'
   */
  {
    0.0F                               /* Data */
  },

  /* Computed Parameter: Constant_Value_j
   * Referenced by: '<S1>/Constant'
   */
  {
    0                                  /* Data */
  },

  /* Expression: 2.63
   * Referenced by: '<Root>/Saturation'
   */
  2.63,

  /* Expression: -2.63
   * Referenced by: '<Root>/Saturation'
   */
  -2.63,

  /* Expression: 1/0.175896
   * Referenced by: '<Root>/Radumfang'
   */
  5.6851776049483789,

  /* Expression: 7
   * Referenced by: '<Root>/Getriebe'
   */
  7.0
};
