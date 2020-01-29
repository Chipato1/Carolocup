/*
 * Zustandsregler_data.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Zustandsregler".
 *
 * Model version              : 1.39
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Wed Jan 29 19:01:07 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Zustandsregler.h"
#include "Zustandsregler_private.h"

/* Block parameters (default storage) */
P_Zustandsregler_T Zustandsregler_P = {
  /* Variable: ausgangsVektor_cT
   * Referenced by: '<S7>/cT'
   */
  { 0.0, 1.0 },

  /* Variable: durchgriffsVektor_d
   * Referenced by: '<S7>/d'
   */
  { 0.25, -0.0625 },

  /* Variable: eingangsMatrix_B
   * Referenced by: '<S7>/b'
   */
  { 0.0, 2.0, 0.0, -1.0 },

  /* Variable: regelMatrix_K
   * Referenced by: '<S7>/kT'
   */
  { 50.0, 50.0, 20.0, 20.0 },

  /* Variable: systemMatrix_A
   * Referenced by: '<S7>/A'
   */
  { 0.0, 0.0, 2.0, 0.0 },

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S3>/Constant'
   */
  {
    0.0F                               /* Data */
  },

  /* Computed Parameter: Constant_Value_o
   * Referenced by: '<S4>/Constant'
   */
  {
    0.0F                               /* Data */
  },

  /* Computed Parameter: Constant_Value_e
   * Referenced by: '<S5>/Constant'
   */
  {
    0.0F                               /* Data */
  },

  /* Computed Parameter: Constant_Value_j
   * Referenced by: '<S6>/Constant'
   */
  {
    0.0F                               /* Data */
  },

  /* Computed Parameter: Constant_Value_f
   * Referenced by: '<S1>/Constant'
   */
  {
    0.0F                               /* Data */
  },

  /* Expression: 0
   * Referenced by: '<S7>/Integrator'
   */
  0.0,

  /* Expression: 0.349
   * Referenced by: '<S7>/Saturation'
   */
  0.349,

  /* Expression: -0.349
   * Referenced by: '<S7>/Saturation'
   */
  -0.349,

  /* Computed Parameter: Multiply2_Gain
   * Referenced by: '<S7>/Multiply2'
   */
  { 1.0F, 0.0F },

  /* Computed Parameter: Multiply3_Gain
   * Referenced by: '<S7>/Multiply3'
   */
  { 0.0F, 1.0F },

  /* Computed Parameter: Multiply_Gain
   * Referenced by: '<S7>/Multiply'
   */
  { 1.0F, 0.0F },

  /* Computed Parameter: Multiply1_Gain
   * Referenced by: '<S7>/Multiply1'
   */
  { 0.0F, 1.0F },

  /* Start of '<S6>/Enabled Subsystem' */
  {
    /* Computed Parameter: Out1_Y0
     * Referenced by: '<S11>/Out1'
     */
    {
      0.0F                             /* Data */
    }
  }
  ,

  /* End of '<S6>/Enabled Subsystem' */

  /* Start of '<S5>/Enabled Subsystem' */
  {
    /* Computed Parameter: Out1_Y0
     * Referenced by: '<S10>/Out1'
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
     * Referenced by: '<S9>/Out1'
     */
    {
      0.0F                             /* Data */
    }
  }
  ,

  /* End of '<S4>/Enabled Subsystem' */

  /* Start of '<S3>/Enabled Subsystem' */
  {
    /* Computed Parameter: Out1_Y0
     * Referenced by: '<S8>/Out1'
     */
    {
      0.0F                             /* Data */
    }
  }
  /* End of '<S3>/Enabled Subsystem' */
};
