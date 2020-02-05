/*
 * Stanley_Querregler_data.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Stanley_Querregler".
 *
 * Model version              : 1.19
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Wed Feb  5 16:58:17 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Stanley_Querregler.h"
#include "Stanley_Querregler_private.h"

/* Block parameters (default storage) */
P_Stanley_Querregler_T Stanley_Querregler_P = {
  /* Mask Parameter: LateralControllerStanley_Positi
   * Referenced by: '<S12>/Kinematic'
   */
  2.5,

  /* Mask Parameter: LateralControllerStanley_Posi_p
   * Referenced by: '<S12>/Kinematic'
   */
  2.5,

  /* Computed Parameter: Out1_Y0
   * Referenced by: '<S8>/Out1'
   */
  {
    false                              /* Data */
  },

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S3>/Constant'
   */
  {
    false                              /* Data */
  },

  /* Computed Parameter: Constant_Value_d
   * Referenced by: '<S4>/Constant'
   */
  {
    0.0F                               /* Data */
  },

  /* Computed Parameter: Constant_Value_c
   * Referenced by: '<S5>/Constant'
   */
  {
    0.0F                               /* Data */
  },

  /* Computed Parameter: Constant_Value_i
   * Referenced by: '<S6>/Constant'
   */
  {
    0.0F                               /* Data */
  },

  /* Computed Parameter: Constant_Value_k
   * Referenced by: '<S1>/Constant'
   */
  {
    0.0F                               /* Data */
  },

  /* Expression: -1
   * Referenced by: '<S7>/Rückwärts'
   */
  -1.0,

  /* Expression: 1
   * Referenced by: '<S7>/Vorwärts'
   */
  1.0,

  /* Expression: MaxSteeringAngle
   * Referenced by: '<S12>/Kinematic'
   */
  20.0,

  /* Expression: Wheelbase
   * Referenced by: '<S12>/Kinematic'
   */
  0.25,

  /* Expression: [0.4, 0, 0]
   * Referenced by: '<S7>/ '
   */
  { 0.4, 0.0, 0.0 },

  /* Expression: [0 1 00000]
   * Referenced by: '<S7>/  '
   */
  { 0.0, 1.0, 0.0 },

  /* Expression: [0 0 0000000]
   * Referenced by: '<S7>/[x, y, theta]'
   */
  { 0.0, 0.0, 0.0 },

  /* Computed Parameter: Gain_Gain
   * Referenced by: '<S7>/Gain'
   */
  -1.0F,

  /* Computed Parameter: Lenkwinkel_Y0
   * Referenced by: '<S7>/Lenkwinkel'
   */
  0.0F,

  /* Computed Parameter: Switch1_Threshold
   * Referenced by: '<S7>/Switch1'
   */
  0.0F,

  /* Computed Parameter: Switch_Threshold
   * Referenced by: '<S7>/Switch'
   */
  0.0F,

  /* Computed Parameter: Sttigung_UpperSat
   * Referenced by: '<S7>/Sättigung'
   */
  20.0F,

  /* Computed Parameter: Sttigung_LowerSat
   * Referenced by: '<S7>/Sättigung'
   */
  -20.0F,

  /* Computed Parameter: Bogenma_Gain
   * Referenced by: '<S7>/Bogenmaß'
   */
  0.0174532924F,

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
  /* End of '<S4>/Enabled Subsystem' */
};
