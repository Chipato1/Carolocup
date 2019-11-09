/*
 * zustandsRegler_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "zustandsRegler".
 *
 * Model version              : 1.13
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C source code generated on : Fri Nov  8 21:05:15 2019
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "zustandsRegler.h"
#include "zustandsRegler_private.h"

/* Block parameters (default storage) */
P_zustandsRegler_T zustandsRegler_P = {
  /* Variable: K
   * Referenced by: '<Root>/kT'
   */
  { 9.99999999999999, 4.7958315233127191 },

  /* Variable: ausgangsVektor_cT
   * Referenced by: '<Root>/cT'
   */
  { 0.0, 2.0 },

  /* Variable: eingangsVektor_b
   * Referenced by: '<Root>/b'
   */
  { 0.0, 2.63 },

  /* Variable: systemMatrix_A
   * Referenced by: '<Root>/A'
   */
  { 0.0, 0.0, 2.63, 0.0 },

  /* Expression: 1
   * Referenced by: '<Root>/Step'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<Root>/Step'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<Root>/Step'
   */
  1.0,

  /* Expression: 5
   * Referenced by: '<Root>/Step1'
   */
  5.0,

  /* Expression: 0
   * Referenced by: '<Root>/Step1'
   */
  0.0,

  /* Expression: -1
   * Referenced by: '<Root>/Step1'
   */
  -1.0,

  /* Expression: 1
   * Referenced by: '<Root>/Gain1'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<Root>/Integrator1'
   */
  0.0,

  /* Expression: 180/pi
   * Referenced by: '<Root>/Gain'
   */
  57.295779513082323,

  /* Expression: 20
   * Referenced by: '<Root>/Saturation'
   */
  20.0,

  /* Expression: -20
   * Referenced by: '<Root>/Saturation'
   */
  -20.0,

  /* Expression: 0
   * Referenced by: '<Root>/Integrator'
   */
  0.0,

  /* Expression: [0;-2.63*0.9]
   * Referenced by: '<Root>/Giergeschwindigkeit '
   */
  { 0.0, -2.367 }
};
