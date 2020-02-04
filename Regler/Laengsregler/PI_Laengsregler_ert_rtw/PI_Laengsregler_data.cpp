/*
 * PI_Laengsregler_data.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "PI_Laengsregler".
 *
 * Model version              : 1.28
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Tue Feb  4 19:20:11 2020
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
  /* Variable: ir
   * Referenced by: '<S33>/Integral Gain'
   */
  1.7,

  /* Variable: pr
   * Referenced by: '<S41>/Proportional Gain'
   */
  1.3,

  /* Mask Parameter: PIDController_InitialConditionF
   * Referenced by: '<S36>/Integrator'
   */
  0.0,

  /* Computed Parameter: Constant_Value
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

  /* Start of '<S5>/Enabled Subsystem' */
  {
    /* Computed Parameter: Out1_Y0
     * Referenced by: '<S52>/Out1'
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
     * Referenced by: '<S51>/Out1'
     */
    {
      0.0F                             /* Data */
    }
  }
  /* End of '<S4>/Enabled Subsystem' */
};
