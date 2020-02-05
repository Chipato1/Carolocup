/*
 * Zustandsregler_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Zustandsregler".
 *
 * Model version              : 1.28
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C source code generated on : Sat Jan 11 17:56:01 2020
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Zustandsregler.h"
#include "Zustandsregler_private.h"

/* Block parameters (default storage) */
P_Zustandsregler_T Zustandsregler_P = {
  /* Variable: K
   * Referenced by: '<S3>/kT'
   */
  { 0.89442719099991419, -0.44721359549995759, 1.4936811927583009,
    -0.74684059637915157 },

  /* Variable: ausgangsVektor_cT
   * Referenced by: '<S3>/cT'
   */
  { 0.0, 1.0 },

  /* Variable: d
   * Referenced by: '<S3>/d'
   */
  { 0.25, -0.0625 },

  /* Variable: eingangsVektor_b
   * Referenced by: '<S3>/b'
   */
  { 0.0, 2.0, 0.0, -1.0 },

  /* Variable: systemMatrix_A
   * Referenced by: '<S3>/A'
   */
  { 0.0, 0.0, 2.0, 0.0 },

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

  /* Expression: 0
   * Referenced by: '<S3>/Integrator'
   */
  0.0,

  /* Expression: [1;0]
   * Referenced by: '<S3>/Multiply'
   */
  { 1.0, 0.0 },

  /* Expression: 0.8
   * Referenced by: '<Root>/Multiply'
   */
  0.8,

  /* Expression: [0;1]
   * Referenced by: '<S3>/Multiply1'
   */
  { 0.0, 1.0 },

  /* Expression: 0.349
   * Referenced by: '<S3>/Saturation'
   */
  0.349,

  /* Expression: -0.349
   * Referenced by: '<S3>/Saturation'
   */
  -0.349
};
