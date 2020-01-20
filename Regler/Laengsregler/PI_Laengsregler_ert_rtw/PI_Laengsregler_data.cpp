/*
 * PI_Laengsregler_data.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "PI_Laengsregler".
 *
 * Model version              : 1.11
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Fri Jan 17 18:21:14 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "PI_Laengsregler.h"
#include "PI_Laengsregler_private.h"

/* Block parameters (default storage) */
P_PI_Laengsregler_T PI_Laengsregler_P = {
  /* Variable: A
   * Referenced by: '<S2>/Constant'
   */
  { 0.0, -39.478417604357432, 1.0, -8.8857658763167322 },

  /* Variable: b
   * Referenced by: '<S2>/Constant1'
   */
  { 0.0, 1.0 },

  /* Variable: cT
   * Referenced by: '<S2>/Constant2'
   */
  { 0.0, 39.478417604357432 },

  /* Variable: ir
   * Referenced by: '<S2>/Gain1'
   */
  1.7,

  /* Variable: pr
   * Referenced by: '<S2>/Gain'
   */
  1.3,

  /* Variable: u
   * Referenced by: '<S2>/Multiply'
   */
  7.0,

  /* Computed Parameter: Out1_Y0
   * Referenced by: '<S7>/Out1'
   */
  {
    0.0F                               /* Data */
  },

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S4>/Constant'
   */
  {
    0.0F                               /* Data */
  },

  /* Computed Parameter: Out1_Y0_m
   * Referenced by: '<S8>/Out1'
   */
  {
    0                                  /* Data */
  },

  /* Computed Parameter: Constant_Value_l
   * Referenced by: '<S5>/Constant'
   */
  {
    0                                  /* Data */
  },

  /* Computed Parameter: Constant_Value_j
   * Referenced by: '<S1>/Constant'
   */
  {
    0                                  /* Data */
  },

  /* Expression: x0
   * Referenced by: '<S6>/Integrator'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S2>/Constant3'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S2>/Integrator'
   */
  0.0
};
