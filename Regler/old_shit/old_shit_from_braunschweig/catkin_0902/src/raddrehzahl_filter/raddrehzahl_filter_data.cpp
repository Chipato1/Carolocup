/*
 * raddrehzahl_filter_data.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "raddrehzahl_filter".
 *
 * Model version              : 1.16
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Sat Feb  8 16:55:50 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "raddrehzahl_filter.h"
#include "raddrehzahl_filter_private.h"

/* Block parameters (default storage) */
P_raddrehzahl_filter_T raddrehzahl_filter_P = {
  /* Variable: denom_drehzahl
   * Referenced by: '<Root>/Discrete Transfer Fcn'
   */
  { 1.0, -0.94280904158206336, 0.33333333333333337 },

  /* Variable: num_drehzahl
   * Referenced by: '<Root>/Discrete Transfer Fcn'
   */
  { 0.0976310729378175, 0.195262145875635, 0.0976310729378175 },

  /* Computed Parameter: Out1_Y0
   * Referenced by: '<S6>/Out1'
   */
  {
    0.0F                               /* Data */
  },

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S5>/Constant'
   */
  {
    0.0F                               /* Data */
  },

  /* Computed Parameter: Constant_Value_l
   * Referenced by: '<S1>/Constant'
   */
  {
    0.0F                               /* Data */
  },

  /* Computed Parameter: Constant_Value_n
   * Referenced by: '<S2>/Constant'
   */
  {
    0.0F                               /* Data */
  },

  /* Expression: 1/60
   * Referenced by: '<Root>/rpm to 1//s'
   */
  0.016666666666666666,

  /* Expression: 0
   * Referenced by: '<Root>/Discrete Transfer Fcn'
   */
  0.0,

  /* Expression: 0.175896
   * Referenced by: '<Root>/Multiply'
   */
  0.175896,

  /* Expression: 0
   * Referenced by: '<Root>/Integrator'
   */
  0.0,

  /* Computed Parameter: Gain_Gain
   * Referenced by: '<Root>/Gain'
   */
  1000.0F
};
