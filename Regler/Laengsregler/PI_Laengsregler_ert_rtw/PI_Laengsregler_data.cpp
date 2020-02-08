/*
 * PI_Laengsregler_data.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "PI_Laengsregler".
 *
 * Model version              : 1.37
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Sat Feb  8 16:46:29 2020
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
   * Referenced by: '<S9>/Out1'
   */
  {
    false                              /* Data */
  },

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S6>/Constant'
   */
  {
    false                              /* Data */
  },

  /* Computed Parameter: Constant_Value_h
   * Referenced by: '<S4>/Constant'
   */
  {
    0.0F                               /* Data */
  },

  /* Computed Parameter: Constant_Value_l
   * Referenced by: '<S5>/Constant'
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

  /* Expression: 1/0.175896
   * Referenced by: '<S2>/Radumfang'
   */
  5.6851776049483789,

  /* Expression: 7
   * Referenced by: '<S2>/Getriebe'
   */
  7.0,

  /* Expression: inf
   * Referenced by: '<S2>/Saturation1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S2>/Saturation1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S2>/Switch1'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S2>/Gain'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S2>/Integrator'
   */
  0.0,

  /* Expression: 4
   * Referenced by: '<S2>/Gain1'
   */
  4.0,

  /* Expression: 2.3
   * Referenced by: '<S2>/Saturation'
   */
  2.3,

  /* Expression: 0
   * Referenced by: '<S2>/Saturation'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S2>/Begrenzung auf maximale Geschwindigkeit '
   */
  0.0,

  /* Expression: -2.3
   * Referenced by: '<S2>/Begrenzung auf maximale Geschwindigkeit '
   */
  -2.3,

  /* Expression: 1/0.175896
   * Referenced by: '<S2>/Radumfang1'
   */
  5.6851776049483789,

  /* Expression: 7
   * Referenced by: '<S2>/Getriebe1'
   */
  7.0,

  /* Expression: 0
   * Referenced by: '<S2>/Saturation2'
   */
  0.0,

  /* Expression: -inf
   * Referenced by: '<S2>/Saturation2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S2>/Switch3'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S2>/Constant1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S2>/Constant'
   */
  0.0,

  /* Expression: 2.25
   * Referenced by: '<S2>/Switch'
   */
  2.25,

  /* Start of '<S5>/Enabled Subsystem' */
  {
    /* Computed Parameter: Out1_Y0
     * Referenced by: '<S8>/Out1'
     */
    {
      0.0F                             /* Data */
    }
  }
  ,

  /* End of '<S5>/Enabled Subsystem' */

  /* Start of '<S4>/Enabled Subsystem' */
  {
    /* Computed Parameter: Out1_Y0
     * Referenced by: '<S7>/Out1'
     */
    {
      0.0F                             /* Data */
    }
  }
  /* End of '<S4>/Enabled Subsystem' */
};
