/*
 * PI_Laengsregler_data.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "PI_Laengsregler".
 *
 * Model version              : 1.13
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Wed Jan 22 20:18:13 2020
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
  { 39.478417604357432, 0.0 },

  /* Variable: ir
   * Referenced by: '<S34>/Integral Gain'
   */
  1.7,

  /* Variable: pr
   * Referenced by: '<S42>/Proportional Gain'
   */
  1.3,

  /* Variable: u
   * Referenced by: '<S2>/Multiply'
   */
  7.0,

  /* Mask Parameter: PIDController1_D
   * Referenced by: '<S31>/Derivative Gain'
   */
  0.0,

  /* Mask Parameter: PIDController1_InitialCondition
   * Referenced by: '<S32>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController1_InitialConditi_b
   * Referenced by: '<S37>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController1_N
   * Referenced by: '<S40>/Filter Coefficient'
   */
  100.0,

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S4>/Constant'
   */
  {
    0.0F                               /* Data */
  },

  /* Computed Parameter: Constant_Value_b
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

  /* Expression: x0
   * Referenced by: '<S7>/Integrator'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S2>/Constant3'
   */
  0.0,

  /* Start of '<S5>/Enabled Subsystem' */
  {
    /* Computed Parameter: Out1_Y0
     * Referenced by: '<S53>/Out1'
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
     * Referenced by: '<S52>/Out1'
     */
    {
      0.0F                             /* Data */
    }
  }
  /* End of '<S4>/Enabled Subsystem' */
};
