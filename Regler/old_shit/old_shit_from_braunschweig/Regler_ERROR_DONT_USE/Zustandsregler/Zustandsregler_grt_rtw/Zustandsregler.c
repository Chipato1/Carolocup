/*
 * Zustandsregler.c
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

/* Block signals (default storage) */
B_Zustandsregler_T Zustandsregler_B;

/* Continuous states */
X_Zustandsregler_T Zustandsregler_X;

/* Block states (default storage) */
DW_Zustandsregler_T Zustandsregler_DW;

/* Real-time model */
RT_MODEL_Zustandsregler_T Zustandsregler_M_;
RT_MODEL_Zustandsregler_T *const Zustandsregler_M = &Zustandsregler_M_;
static void rate_scheduler(void);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (Zustandsregler_M->Timing.TaskCounters.TID[2])++;
  if ((Zustandsregler_M->Timing.TaskCounters.TID[2]) > 99) {/* Sample time: [0.1s, 0.0s] */
    Zustandsregler_M->Timing.TaskCounters.TID[2] = 0;
  }
}

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
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Zustandsregler_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  Zustandsregler_step();
  Zustandsregler_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  Zustandsregler_step();
  Zustandsregler_derivatives();

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
void Zustandsregler_step(void)
{
  real_T rtb_Multiply_j;
  real_T rtb_Product2_0;
  real_T rtb_Product2_idx_0;
  real_T rtb_Product2_idx_1;
  if (rtmIsMajorTimeStep(Zustandsregler_M)) {
    /* set solver stop time */
    if (!(Zustandsregler_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&Zustandsregler_M->solverInfo,
                            ((Zustandsregler_M->Timing.clockTickH0 + 1) *
        Zustandsregler_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&Zustandsregler_M->solverInfo,
                            ((Zustandsregler_M->Timing.clockTick0 + 1) *
        Zustandsregler_M->Timing.stepSize0 +
        Zustandsregler_M->Timing.clockTickH0 *
        Zustandsregler_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Zustandsregler_M)) {
    Zustandsregler_M->Timing.t[0] = rtsiGetT(&Zustandsregler_M->solverInfo);
  }

  /* Step: '<Root>/Step' incorporates:
   *  Step: '<Root>/Step1'
   */
  rtb_Multiply_j = Zustandsregler_M->Timing.t[0];
  if (rtb_Multiply_j < Zustandsregler_P.Step_Time) {
    rtb_Product2_0 = Zustandsregler_P.Step_Y0;
  } else {
    rtb_Product2_0 = Zustandsregler_P.Step_YFinal;
  }

  /* End of Step: '<Root>/Step' */

  /* Step: '<Root>/Step1' */
  if (rtb_Multiply_j < Zustandsregler_P.Step1_Time) {
    rtb_Multiply_j = Zustandsregler_P.Step1_Y0;
  } else {
    rtb_Multiply_j = Zustandsregler_P.Step1_YFinal;
  }

  /* Sum: '<Root>/Add1' */
  Zustandsregler_B.Add1 = rtb_Product2_0 + rtb_Multiply_j;

  /* RateTransition: '<S1>/Rate Transition' incorporates:
   *  Sum: '<S3>/Add1'
   */
  if ((rtmIsMajorTimeStep(Zustandsregler_M) &&
       Zustandsregler_M->Timing.TaskCounters.TID[1] == 0) && (rtmIsMajorTimeStep
       (Zustandsregler_M) &&
       Zustandsregler_M->Timing.TaskCounters.TID[2] == 0)) {
    Zustandsregler_DW.RateTransition_Buffer = Zustandsregler_B.Add1;
  }

  if (rtmIsMajorTimeStep(Zustandsregler_M) &&
      Zustandsregler_M->Timing.TaskCounters.TID[2] == 0) {
    Zustandsregler_B.RateTransition = Zustandsregler_DW.RateTransition_Buffer;

    /* Gain: '<Root>/Multiply' */
    rtb_Multiply_j = Zustandsregler_P.Multiply_Gain_e *
      Zustandsregler_B.RateTransition;

    /* Sum: '<S3>/Add1' incorporates:
     *  Gain: '<S3>/Multiply'
     *  Gain: '<S3>/Multiply1'
     */
    rtb_Product2_idx_1 = Zustandsregler_P.Multiply_Gain[0] *
      Zustandsregler_B.RateTransition + Zustandsregler_P.Multiply1_Gain[0] *
      rtb_Multiply_j;

    /* Product: '<S3>/Product4' incorporates:
     *  Constant: '<S3>/d'
     */
    rtb_Product2_0 = rtb_Product2_idx_1 * Zustandsregler_P.d[0];
    rtb_Product2_idx_0 = rtb_Product2_idx_1;

    /* Sum: '<S3>/Add1' incorporates:
     *  Gain: '<S3>/Multiply'
     *  Gain: '<S3>/Multiply1'
     */
    rtb_Product2_idx_1 = Zustandsregler_P.Multiply_Gain[1] *
      Zustandsregler_B.RateTransition + Zustandsregler_P.Multiply1_Gain[1] *
      rtb_Multiply_j;

    /* Product: '<S3>/Product4' incorporates:
     *  Constant: '<S3>/d'
     */
    Zustandsregler_B.Product4 = rtb_Product2_idx_1 * Zustandsregler_P.d[1] +
      rtb_Product2_0;
  }

  /* End of RateTransition: '<S1>/Rate Transition' */

  /* Integrator: '<S3>/Integrator' */
  Zustandsregler_B.x[0] = Zustandsregler_X.Integrator_CSTATE[0];
  Zustandsregler_B.x[1] = Zustandsregler_X.Integrator_CSTATE[1];

  /* Sum: '<S3>/Add2' incorporates:
   *  Constant: '<S3>/cT'
   *  Product: '<S3>/Product3'
   */
  rtb_Multiply_j = (Zustandsregler_P.ausgangsVektor_cT[0] * Zustandsregler_B.x[0]
                    + Zustandsregler_P.ausgangsVektor_cT[1] *
                    Zustandsregler_B.x[1]) + Zustandsregler_B.Product4;

  /* Saturate: '<S3>/Saturation' */
  if (rtb_Multiply_j > Zustandsregler_P.Saturation_UpperSat) {
    Zustandsregler_B.Saturation = Zustandsregler_P.Saturation_UpperSat;
  } else if (rtb_Multiply_j < Zustandsregler_P.Saturation_LowerSat) {
    Zustandsregler_B.Saturation = Zustandsregler_P.Saturation_LowerSat;
  } else {
    Zustandsregler_B.Saturation = rtb_Multiply_j;
  }

  /* End of Saturate: '<S3>/Saturation' */

  /* RateTransition: '<S2>/Rate Transition' incorporates:
   *  Constant: '<S3>/kT'
   *  Product: '<S3>/Product'
   *  Sum: '<S3>/Subtract'
   */
  if ((rtmIsMajorTimeStep(Zustandsregler_M) &&
       Zustandsregler_M->Timing.TaskCounters.TID[1] == 0) && (rtmIsMajorTimeStep
       (Zustandsregler_M) &&
       Zustandsregler_M->Timing.TaskCounters.TID[2] == 0)) {
    Zustandsregler_DW.RateTransition_Buffer_j[0] = Zustandsregler_B.x[0];
    Zustandsregler_DW.RateTransition_Buffer_j[1] = Zustandsregler_B.x[1];
  }

  if (rtmIsMajorTimeStep(Zustandsregler_M) &&
      Zustandsregler_M->Timing.TaskCounters.TID[2] == 0) {
    rtb_Product2_idx_0 -= Zustandsregler_P.K[0] *
      Zustandsregler_DW.RateTransition_Buffer_j[0] + Zustandsregler_P.K[2] *
      Zustandsregler_DW.RateTransition_Buffer_j[1];

    /* Sum: '<S3>/Subtract' incorporates:
     *  Constant: '<S3>/kT'
     *  Product: '<S3>/Product'
     */
    rtb_Product2_0 = rtb_Product2_idx_1 - (Zustandsregler_P.K[1] *
      Zustandsregler_DW.RateTransition_Buffer_j[0] + Zustandsregler_P.K[3] *
      Zustandsregler_DW.RateTransition_Buffer_j[1]);

    /* Sum: '<S3>/Add' incorporates:
     *  Constant: '<S3>/A'
     *  Constant: '<S3>/b'
     *  Product: '<S3>/Product1'
     *  Product: '<S3>/Product2'
     */
    Zustandsregler_B.x_b[0] = (Zustandsregler_P.eingangsVektor_b[0] *
      rtb_Product2_idx_0 + Zustandsregler_P.eingangsVektor_b[2] * rtb_Product2_0)
      + (Zustandsregler_P.systemMatrix_A[0] *
         Zustandsregler_DW.RateTransition_Buffer_j[0] +
         Zustandsregler_P.systemMatrix_A[2] *
         Zustandsregler_DW.RateTransition_Buffer_j[1]);
    Zustandsregler_B.x_b[1] = (Zustandsregler_P.eingangsVektor_b[1] *
      rtb_Product2_idx_0 + Zustandsregler_P.eingangsVektor_b[3] * rtb_Product2_0)
      + (Zustandsregler_P.systemMatrix_A[1] *
         Zustandsregler_DW.RateTransition_Buffer_j[0] +
         Zustandsregler_P.systemMatrix_A[3] *
         Zustandsregler_DW.RateTransition_Buffer_j[1]);
  }

  /* End of RateTransition: '<S2>/Rate Transition' */
  if (rtmIsMajorTimeStep(Zustandsregler_M) &&
      Zustandsregler_M->Timing.TaskCounters.TID[1] == 0) {
  }

  if (rtmIsMajorTimeStep(Zustandsregler_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(Zustandsregler_M->rtwLogInfo,
                        (Zustandsregler_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(Zustandsregler_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(Zustandsregler_M)!=-1) &&
          !((rtmGetTFinal(Zustandsregler_M)-
             (((Zustandsregler_M->Timing.clockTick1+
                Zustandsregler_M->Timing.clockTickH1* 4294967296.0)) * 0.001)) >
            (((Zustandsregler_M->Timing.clockTick1+
               Zustandsregler_M->Timing.clockTickH1* 4294967296.0)) * 0.001) *
            (DBL_EPSILON))) {
        rtmSetErrorStatus(Zustandsregler_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&Zustandsregler_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++Zustandsregler_M->Timing.clockTick0)) {
      ++Zustandsregler_M->Timing.clockTickH0;
    }

    Zustandsregler_M->Timing.t[0] = rtsiGetSolverStopTime
      (&Zustandsregler_M->solverInfo);

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
      Zustandsregler_M->Timing.clockTick1++;
      if (!Zustandsregler_M->Timing.clockTick1) {
        Zustandsregler_M->Timing.clockTickH1++;
      }
    }

    rate_scheduler();
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Zustandsregler_derivatives(void)
{
  XDot_Zustandsregler_T *_rtXdot;
  _rtXdot = ((XDot_Zustandsregler_T *) Zustandsregler_M->derivs);

  /* Derivatives for Integrator: '<S3>/Integrator' */
  _rtXdot->Integrator_CSTATE[0] = Zustandsregler_B.x_b[0];
  _rtXdot->Integrator_CSTATE[1] = Zustandsregler_B.x_b[1];
}

/* Model initialize function */
void Zustandsregler_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Zustandsregler_M, 0,
                sizeof(RT_MODEL_Zustandsregler_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Zustandsregler_M->solverInfo,
                          &Zustandsregler_M->Timing.simTimeStep);
    rtsiSetTPtr(&Zustandsregler_M->solverInfo, &rtmGetTPtr(Zustandsregler_M));
    rtsiSetStepSizePtr(&Zustandsregler_M->solverInfo,
                       &Zustandsregler_M->Timing.stepSize0);
    rtsiSetdXPtr(&Zustandsregler_M->solverInfo, &Zustandsregler_M->derivs);
    rtsiSetContStatesPtr(&Zustandsregler_M->solverInfo, (real_T **)
                         &Zustandsregler_M->contStates);
    rtsiSetNumContStatesPtr(&Zustandsregler_M->solverInfo,
      &Zustandsregler_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&Zustandsregler_M->solverInfo,
      &Zustandsregler_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&Zustandsregler_M->solverInfo,
      &Zustandsregler_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&Zustandsregler_M->solverInfo,
      &Zustandsregler_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&Zustandsregler_M->solverInfo, (&rtmGetErrorStatus
      (Zustandsregler_M)));
    rtsiSetRTModelPtr(&Zustandsregler_M->solverInfo, Zustandsregler_M);
  }

  rtsiSetSimTimeStep(&Zustandsregler_M->solverInfo, MAJOR_TIME_STEP);
  Zustandsregler_M->intgData.y = Zustandsregler_M->odeY;
  Zustandsregler_M->intgData.f[0] = Zustandsregler_M->odeF[0];
  Zustandsregler_M->intgData.f[1] = Zustandsregler_M->odeF[1];
  Zustandsregler_M->intgData.f[2] = Zustandsregler_M->odeF[2];
  Zustandsregler_M->contStates = ((X_Zustandsregler_T *) &Zustandsregler_X);
  rtsiSetSolverData(&Zustandsregler_M->solverInfo, (void *)
                    &Zustandsregler_M->intgData);
  rtsiSetSolverName(&Zustandsregler_M->solverInfo,"ode3");
  rtmSetTPtr(Zustandsregler_M, &Zustandsregler_M->Timing.tArray[0]);
  rtmSetTFinal(Zustandsregler_M, 7.0);
  Zustandsregler_M->Timing.stepSize0 = 0.001;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    Zustandsregler_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(Zustandsregler_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(Zustandsregler_M->rtwLogInfo, (NULL));
    rtliSetLogT(Zustandsregler_M->rtwLogInfo, "tout");
    rtliSetLogX(Zustandsregler_M->rtwLogInfo, "");
    rtliSetLogXFinal(Zustandsregler_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(Zustandsregler_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(Zustandsregler_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(Zustandsregler_M->rtwLogInfo, 0);
    rtliSetLogDecimation(Zustandsregler_M->rtwLogInfo, 1);
    rtliSetLogY(Zustandsregler_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(Zustandsregler_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(Zustandsregler_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &Zustandsregler_B), 0,
                sizeof(B_Zustandsregler_T));

  /* states (continuous) */
  {
    (void) memset((void *)&Zustandsregler_X, 0,
                  sizeof(X_Zustandsregler_T));
  }

  /* states (dwork) */
  (void) memset((void *)&Zustandsregler_DW, 0,
                sizeof(DW_Zustandsregler_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(Zustandsregler_M->rtwLogInfo, 0.0,
    rtmGetTFinal(Zustandsregler_M), Zustandsregler_M->Timing.stepSize0,
    (&rtmGetErrorStatus(Zustandsregler_M)));

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  Zustandsregler_X.Integrator_CSTATE[0] = Zustandsregler_P.Integrator_IC;
  Zustandsregler_X.Integrator_CSTATE[1] = Zustandsregler_P.Integrator_IC;
}

/* Model terminate function */
void Zustandsregler_terminate(void)
{
  /* (no terminate code required) */
}
