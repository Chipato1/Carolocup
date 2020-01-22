/*
 * Zustandsregler_data.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Zustandsregler".
 *
 * Model version              : 1.35
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Wed Jan 22 23:34:49 2020
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
  /* Variable: K
   * Referenced by: '<S7>/kT'
   */
  { 4.0, -1.9999999999999984, 4.7328638264796936, -2.3664319132398455 },

  /* Variable: ausgangsVektor_cT
   * Referenced by: '<S7>/cT'
   */
  { 0.0, 1.0 },

  /* Variable: d
   * Referenced by: '<S7>/d'
   */
  { 0.25, -0.0625 },

  /* Variable: eingangsVektor_b
   * Referenced by: '<S7>/b'
   */
  { 0.0, 2.0, 0.0, -1.0 },

  /* Variable: systemMatrix_A
   * Referenced by: '<S7>/A'
   */
  { 0.0, 0.0, 2.0, 0.0 },

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S1>/Constant'
   */
  {
    0.0F                               /* Data */
  },

  /* Computed Parameter: Constant_Value_p
   * Referenced by: '<S3>/Constant'
   */
  {
    0.0                                /* Data */
  },

  /* Computed Parameter: Constant_Value_o
   * Referenced by: '<S4>/Constant'
   */
  {
    0.0                                /* Data */
  },

  /* Computed Parameter: Constant_Value_e
   * Referenced by: '<S5>/Constant'
   */
  {
    0.0                                /* Data */
  },

  /* Computed Parameter: Constant_Value_j
   * Referenced by: '<S6>/Constant'
   */
  {
    0.0                                /* Data */
  },

  /* Expression: [1;0]
   * Referenced by: '<S7>/Multiply2'
   */
  { 1.0, 0.0 },

  /* Expression: [0;1]
   * Referenced by: '<S7>/Multiply3'
   */
  { 0.0, 1.0 },

  /* Expression: [1;0]
   * Referenced by: '<S7>/Multiply'
   */
  { 1.0, 0.0 },

  /* Expression: [0;1]
   * Referenced by: '<S7>/Multiply1'
   */
  { 0.0, 1.0 },

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

  /* Start of '<S6>/Enabled Subsystem' */
  {
    /* Computed Parameter: Out1_Y0
     * Referenced by: '<S11>/Out1'
     */
    {
      0.0                              /* Data */
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
      0.0                              /* Data */
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
      0.0                              /* Data */
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
      0.0                              /* Data */
    }
  }
  /* End of '<S3>/Enabled Subsystem' */
};
