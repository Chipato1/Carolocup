/*
 * multiword_types.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "raddrehzahl_filter".
 *
 * Model version              : 1.16
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Fri Feb  7 18:13:59 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef MULTIWORD_TYPES_H
#define MULTIWORD_TYPES_H
#include "rtwtypes.h"

/*
 * MultiWord supporting definitions
 */
typedef long int long_T;

/*
 * MultiWord types
 */
typedef struct {
  uint64_T chunks[2];
} int128m_T;

typedef struct {
  int128m_T re;
  int128m_T im;
} cint128m_T;

typedef struct {
  uint64_T chunks[2];
} uint128m_T;

typedef struct {
  uint128m_T re;
  uint128m_T im;
} cuint128m_T;

typedef struct {
  uint64_T chunks[3];
} int192m_T;

typedef struct {
  int192m_T re;
  int192m_T im;
} cint192m_T;

typedef struct {
  uint64_T chunks[3];
} uint192m_T;

typedef struct {
  uint192m_T re;
  uint192m_T im;
} cuint192m_T;

typedef struct {
  uint64_T chunks[4];
} int256m_T;

typedef struct {
  int256m_T re;
  int256m_T im;
} cint256m_T;

typedef struct {
  uint64_T chunks[4];
} uint256m_T;

typedef struct {
  uint256m_T re;
  uint256m_T im;
} cuint256m_T;

#endif                                 /* MULTIWORD_TYPES_H */
