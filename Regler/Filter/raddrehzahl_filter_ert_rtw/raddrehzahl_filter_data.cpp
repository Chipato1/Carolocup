/*
 * raddrehzahl_filter_data.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "raddrehzahl_filter".
 *
 * Model version              : 1.9
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Tue Feb  4 19:28:58 2020
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
  { 1.0, -1.5610180758007179, 0.641351538057563 },

  /* Variable: num_drehzahl
   * Referenced by: '<Root>/Discrete Transfer Fcn'
   */
  { 0.020083365564211253, 0.040166731128422506, 0.020083365564211253 },

  /* Computed Parameter: Out1_Y0
   * Referenced by: '<S8>/Out1'
   */
  {
    false                              /* Data */
  },

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S5>/Constant'
   */
  {
    false                              /* Data */
  },

  /* Computed Parameter: Constant_Value_j
   * Referenced by: '<S6>/Constant'
   */
  {
    0.0F                               /* Data */
  },

  /* Computed Parameter: Constant_Value_m
   * Referenced by: '<S7>/Constant'
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

  /* Expression: 0.175896
   * Referenced by: '<Root>/Multiply'
   */
  0.175896,

  /* Expression: 0
   * Referenced by: '<Root>/Discrete Transfer Fcn'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Integrator'
   */
  0.0,

  /* Start of '<S7>/Enabled Subsystem' */
  {
    /* Computed Parameter: Out1_Y0
     * Referenced by: '<S10>/Out1'
     */
    {
      0.0F                             /* Data */
    }
  }
  ,

  /* End of '<S7>/Enabled Subsystem' */

  /* Start of '<S6>/Enabled Subsystem' */
  {
    /* Computed Parameter: Out1_Y0
     * Referenced by: '<S9>/Out1'
     */
    {
      0.0F                             /* Data */
    }
  }
  /* End of '<S6>/Enabled Subsystem' */
};
