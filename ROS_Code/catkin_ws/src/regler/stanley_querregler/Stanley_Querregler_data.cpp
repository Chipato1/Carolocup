/*
 * Stanley_Querregler_data.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Stanley_Querregler".
 *
 * Model version              : 1.11
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Wed Jan 22 14:25:49 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Stanley_Querregler.h"
#include "Stanley_Querregler_private.h"

/* Block parameters (default storage) */
P_Stanley_Querregler_T Stanley_Querregler_P = {
  /* Mask Parameter: LateralControllerStanley_Positi
   * Referenced by: '<S9>/Kinematic'
   */
  2.5,

  /* Mask Parameter: LateralControllerStanley_Posi_p
   * Referenced by: '<S9>/Kinematic'
   */
  2.5,

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S3>/Constant'
   */
  {
    0.0F                               /* Data */
  },

  /* Computed Parameter: Constant_Value_c
   * Referenced by: '<S4>/Constant'
   */
  {
    0.0F                               /* Data */
  },

  /* Computed Parameter: Constant_Value_g
   * Referenced by: '<S1>/Constant'
   */
  {
    0.0F                               /* Data */
  },

  /* Expression: -1
   * Referenced by: '<S5>/Gain'
   */
  -1.0,

  /* Expression: -1
   * Referenced by: '<S5>/Rückwärts'
   */
  -1.0,

  /* Expression: 1
   * Referenced by: '<S5>/Vorwärts'
   */
  1.0,

  /* Expression: MaxSteeringAngle
   * Referenced by: '<S9>/Kinematic'
   */
  20.0,

  /* Expression: Wheelbase
   * Referenced by: '<S9>/Kinematic'
   */
  2.8,

  /* Computed Parameter: Lenkwinkel_Y0
   * Referenced by: '<S5>/Lenkwinkel'
   */
  0.0,

  /* Expression: [0.4, 0, 0]
   * Referenced by: '<S5>/[x, y, theta]'
   */
  { 0.4, 0.0, 0.0 },

  /* Expression: [0 1 0]
   * Referenced by: '<S5>/Constant1'
   */
  { 0.0, 1.0, 0.0 },

  /* Expression: [0 0 0]
   * Referenced by: '<S5>/Constant'
   */
  { 0.0, 0.0, 0.0 },

  /* Expression: 2*pi
   * Referenced by: '<S8>/Constant'
   */
  6.2831853071795862,

  /* Expression: 5.6/2
   * Referenced by: '<S8>/Radius (cm)'
   */
  2.8,

  /* Expression: 0.01
   * Referenced by: '<S8>/cm in m'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<S5>/Switch1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S5>/Switch'
   */
  0.0,

  /* Start of '<S4>/Enabled Subsystem' */
  {
    /* Computed Parameter: Out1_Y0
     * Referenced by: '<S7>/Out1'
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
     * Referenced by: '<S6>/Out1'
     */
    {
      0.0F                             /* Data */
    }
  }
  /* End of '<S3>/Enabled Subsystem' */
};
