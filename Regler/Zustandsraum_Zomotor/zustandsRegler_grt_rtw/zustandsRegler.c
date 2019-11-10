/*
 * zustandsRegler.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "zustandsRegler".
 *
 * Model version              : 1.15
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C source code generated on : Sun Nov 10 15:13:12 2019
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "zustandsRegler.h"
#include "zustandsRegler_private.h"

/* Block signals (default storage) */
B_zustandsRegler_T zustandsRegler_B;

/* Continuous states */
X_zustandsRegler_T zustandsRegler_X;

/* Block states (default storage) */
DW_zustandsRegler_T zustandsRegler_DW;

/* Real-time model */
RT_MODEL_zustandsRegler_T zustandsRegler_M_;
RT_MODEL_zustandsRegler_T *const zustandsRegler_M = &zustandsRegler_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 3;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  zustandsRegler_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  zustandsRegler_step();
  zustandsRegler_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  zustandsRegler_step();
  zustandsRegler_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void zustandsRegler_step(void)
{
  real_T rtb_Add1;
  real_T rtb_TransferFcn;
  if (rtmIsMajorTimeStep(zustandsRegler_M)) {
    /* set solver stop time */
    if (!(zustandsRegler_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&zustandsRegler_M->solverInfo,
                            ((zustandsRegler_M->Timing.clockTickH0 + 1) *
        zustandsRegler_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&zustandsRegler_M->solverInfo,
                            ((zustandsRegler_M->Timing.clockTick0 + 1) *
        zustandsRegler_M->Timing.stepSize0 +
        zustandsRegler_M->Timing.clockTickH0 *
        zustandsRegler_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(zustandsRegler_M)) {
    zustandsRegler_M->Timing.t[0] = rtsiGetT(&zustandsRegler_M->solverInfo);
  }

  /* Step: '<Root>/Step' incorporates:
   *  Step: '<Root>/Step1'
   */
  rtb_Add1 = zustandsRegler_M->Timing.t[0];
  if (rtb_Add1 < zustandsRegler_P.Step_Time) {
    rtb_TransferFcn = zustandsRegler_P.Step_Y0;
  } else {
    rtb_TransferFcn = zustandsRegler_P.Step_YFinal;
  }

  /* End of Step: '<Root>/Step' */

  /* Step: '<Root>/Step1' */
  if (rtb_Add1 < zustandsRegler_P.Step1_Time) {
    rtb_Add1 = zustandsRegler_P.Step1_Y0;
  } else {
    rtb_Add1 = zustandsRegler_P.Step1_YFinal;
  }

  /* Sum: '<Root>/Add1' */
  rtb_Add1 += rtb_TransferFcn;

  /* Gain: '<Root>/Gain1' */
  zustandsRegler_B.c0 = zustandsRegler_P.Gain1_Gain * rtb_Add1;

  /* Integrator: '<Root>/Integrator' */
  zustandsRegler_B.x[0] = zustandsRegler_X.Integrator_CSTATE[0];
  zustandsRegler_B.x[1] = zustandsRegler_X.Integrator_CSTATE[1];

  /* Sum: '<Root>/Add2' incorporates:
   *  Constant: '<Root>/cT'
   *  Product: '<Root>/Product3'
   *  TransferFcn: '<Root>/Transfer Fcn'
   */
  zustandsRegler_B.psideltapsi = (zustandsRegler_P.ausgangsVektor_cT[0] *
    zustandsRegler_B.x[0] + zustandsRegler_P.ausgangsVektor_cT[1] *
    zustandsRegler_B.x[1]) + zustandsRegler_P.TransferFcn_C *
    zustandsRegler_X.TransferFcn_CSTATE;

  /* Sum: '<Root>/Subtract' incorporates:
   *  Constant: '<Root>/kT'
   *  Product: '<Root>/Product'
   */
  rtb_TransferFcn = zustandsRegler_B.c0 - (zustandsRegler_P.K[0] *
    zustandsRegler_B.x[0] + zustandsRegler_P.K[1] * zustandsRegler_B.x[1]);

  /* Sum: '<Root>/Add' incorporates:
   *  Constant: '<Root>/ '
   *  Constant: '<Root>/A'
   *  Constant: '<Root>/b'
   *  Product: '<Root>/Product1'
   *  Product: '<Root>/Product2'
   *  Product: '<Root>/Product4'
   */
  zustandsRegler_B.x_b[0] = ((zustandsRegler_P.systemMatrix_A[0] *
    zustandsRegler_B.x[0] + zustandsRegler_P.systemMatrix_A[2] *
    zustandsRegler_B.x[1]) + rtb_TransferFcn *
    zustandsRegler_P.eingangsVektor_b[0]) + rtb_Add1 * zustandsRegler_P._Value[0];
  zustandsRegler_B.x_b[1] = ((zustandsRegler_P.systemMatrix_A[1] *
    zustandsRegler_B.x[0] + zustandsRegler_P.systemMatrix_A[3] *
    zustandsRegler_B.x[1]) + rtb_TransferFcn *
    zustandsRegler_P.eingangsVektor_b[1]) + rtb_Add1 * zustandsRegler_P._Value[1];
  if (rtmIsMajorTimeStep(zustandsRegler_M)) {
  }

  /* Gain: '<Root>/Multiply' */
  zustandsRegler_B.psi = zustandsRegler_P.Multiply_Gain * zustandsRegler_B.c0;
  if (rtmIsMajorTimeStep(zustandsRegler_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(zustandsRegler_M->rtwLogInfo,
                        (zustandsRegler_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(zustandsRegler_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(zustandsRegler_M)!=-1) &&
          !((rtmGetTFinal(zustandsRegler_M)-
             (((zustandsRegler_M->Timing.clockTick1+
                zustandsRegler_M->Timing.clockTickH1* 4294967296.0)) * 0.001)) >
            (((zustandsRegler_M->Timing.clockTick1+
               zustandsRegler_M->Timing.clockTickH1* 4294967296.0)) * 0.001) *
            (DBL_EPSILON))) {
        rtmSetErrorStatus(zustandsRegler_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&zustandsRegler_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++zustandsRegler_M->Timing.clockTick0)) {
      ++zustandsRegler_M->Timing.clockTickH0;
    }

    zustandsRegler_M->Timing.t[0] = rtsiGetSolverStopTime
      (&zustandsRegler_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      zustandsRegler_M->Timing.clockTick1++;
      if (!zustandsRegler_M->Timing.clockTick1) {
        zustandsRegler_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void zustandsRegler_derivatives(void)
{
  XDot_zustandsRegler_T *_rtXdot;
  _rtXdot = ((XDot_zustandsRegler_T *) zustandsRegler_M->derivs);

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = 0.0;
  _rtXdot->TransferFcn_CSTATE += zustandsRegler_P.TransferFcn_A *
    zustandsRegler_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += zustandsRegler_B.psi;

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE[0] = zustandsRegler_B.x_b[0];
  _rtXdot->Integrator_CSTATE[1] = zustandsRegler_B.x_b[1];
}

/* Model initialize function */
void zustandsRegler_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)zustandsRegler_M, 0,
                sizeof(RT_MODEL_zustandsRegler_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&zustandsRegler_M->solverInfo,
                          &zustandsRegler_M->Timing.simTimeStep);
    rtsiSetTPtr(&zustandsRegler_M->solverInfo, &rtmGetTPtr(zustandsRegler_M));
    rtsiSetStepSizePtr(&zustandsRegler_M->solverInfo,
                       &zustandsRegler_M->Timing.stepSize0);
    rtsiSetdXPtr(&zustandsRegler_M->solverInfo, &zustandsRegler_M->derivs);
    rtsiSetContStatesPtr(&zustandsRegler_M->solverInfo, (real_T **)
                         &zustandsRegler_M->contStates);
    rtsiSetNumContStatesPtr(&zustandsRegler_M->solverInfo,
      &zustandsRegler_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&zustandsRegler_M->solverInfo,
      &zustandsRegler_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&zustandsRegler_M->solverInfo,
      &zustandsRegler_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&zustandsRegler_M->solverInfo,
      &zustandsRegler_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&zustandsRegler_M->solverInfo, (&rtmGetErrorStatus
      (zustandsRegler_M)));
    rtsiSetRTModelPtr(&zustandsRegler_M->solverInfo, zustandsRegler_M);
  }

  rtsiSetSimTimeStep(&zustandsRegler_M->solverInfo, MAJOR_TIME_STEP);
  zustandsRegler_M->intgData.y = zustandsRegler_M->odeY;
  zustandsRegler_M->intgData.f[0] = zustandsRegler_M->odeF[0];
  zustandsRegler_M->intgData.f[1] = zustandsRegler_M->odeF[1];
  zustandsRegler_M->intgData.f[2] = zustandsRegler_M->odeF[2];
  zustandsRegler_M->contStates = ((X_zustandsRegler_T *) &zustandsRegler_X);
  rtsiSetSolverData(&zustandsRegler_M->solverInfo, (void *)
                    &zustandsRegler_M->intgData);
  rtsiSetSolverName(&zustandsRegler_M->solverInfo,"ode3");
  rtmSetTPtr(zustandsRegler_M, &zustandsRegler_M->Timing.tArray[0]);
  rtmSetTFinal(zustandsRegler_M, 7.0);
  zustandsRegler_M->Timing.stepSize0 = 0.001;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    zustandsRegler_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(zustandsRegler_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(zustandsRegler_M->rtwLogInfo, (NULL));
    rtliSetLogT(zustandsRegler_M->rtwLogInfo, "tout");
    rtliSetLogX(zustandsRegler_M->rtwLogInfo, "");
    rtliSetLogXFinal(zustandsRegler_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(zustandsRegler_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(zustandsRegler_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(zustandsRegler_M->rtwLogInfo, 0);
    rtliSetLogDecimation(zustandsRegler_M->rtwLogInfo, 1);
    rtliSetLogY(zustandsRegler_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(zustandsRegler_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(zustandsRegler_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &zustandsRegler_B), 0,
                sizeof(B_zustandsRegler_T));

  /* states (continuous) */
  {
    (void) memset((void *)&zustandsRegler_X, 0,
                  sizeof(X_zustandsRegler_T));
  }

  /* states (dwork) */
  (void) memset((void *)&zustandsRegler_DW, 0,
                sizeof(DW_zustandsRegler_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(zustandsRegler_M->rtwLogInfo, 0.0,
    rtmGetTFinal(zustandsRegler_M), zustandsRegler_M->Timing.stepSize0,
    (&rtmGetErrorStatus(zustandsRegler_M)));

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn' */
  zustandsRegler_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  zustandsRegler_X.Integrator_CSTATE[0] = zustandsRegler_P.Integrator_IC;
  zustandsRegler_X.Integrator_CSTATE[1] = zustandsRegler_P.Integrator_IC;
}

/* Model terminate function */
void zustandsRegler_terminate(void)
{
  /* (no terminate code required) */
}
