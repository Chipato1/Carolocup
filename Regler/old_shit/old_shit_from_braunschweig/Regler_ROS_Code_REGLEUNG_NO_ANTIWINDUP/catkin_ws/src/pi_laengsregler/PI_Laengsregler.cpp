/*
 * PI_Laengsregler.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "PI_Laengsregler".
 *
 * Model version              : 1.29
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Wed Feb  5 17:00:02 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "PI_Laengsregler.h"
#include "PI_Laengsregler_private.h"

/* Block signals (default storage) */
B_PI_Laengsregler_T PI_Laengsregler_B;

/* Continuous states */
X_PI_Laengsregler_T PI_Laengsregler_X;

/* Block states (default storage) */
DW_PI_Laengsregler_T PI_Laengsregler_DW;

/* Real-time model */
RT_MODEL_PI_Laengsregler_T PI_Laengsregler_M_ = RT_MODEL_PI_Laengsregler_T();
RT_MODEL_PI_Laengsregler_T *const PI_Laengsregler_M = &PI_Laengsregler_M_;

/* Forward declaration for local functions */
static void matlabCodegenHandle_matlabCod_l(ros_slros_internal_block_Subs_T *obj);
static void matlabCodegenHandle_matlabCodeg(ros_slros_internal_block_Publ_T *obj);

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
  ODE3_IntgData *id = static_cast<ODE3_IntgData *>(rtsiGetSolverData(si));
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 1;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                static_cast<uint_T>(nXc)*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  PI_Laengsregler_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  PI_Laengsregler_step();
  PI_Laengsregler_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  PI_Laengsregler_step();
  PI_Laengsregler_derivatives();

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

/*
 * System initialize for enable system:
 *    '<S4>/Enabled Subsystem'
 *    '<S5>/Enabled Subsystem'
 */
void PI_Laengs_EnabledSubsystem_Init(B_EnabledSubsystem_PI_Laengsr_T *localB,
  P_EnabledSubsystem_PI_Laengsr_T *localP)
{
  /* SystemInitialize for Outport: '<S51>/Out1' */
  localB->In1 = localP->Out1_Y0;
}

/*
 * Output and update for enable system:
 *    '<S4>/Enabled Subsystem'
 *    '<S5>/Enabled Subsystem'
 */
void PI_Laengsregle_EnabledSubsystem(boolean_T rtu_Enable, const
  SL_Bus_PI_Laengsregler_std_msgs_Float32 *rtu_In1,
  B_EnabledSubsystem_PI_Laengsr_T *localB)
{
  /* Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S51>/Enable'
   */
  if (rtu_Enable) {
    /* Inport: '<S51>/In1' */
    localB->In1 = *rtu_In1;
  }

  /* End of Outputs for SubSystem: '<S4>/Enabled Subsystem' */
}

static void matlabCodegenHandle_matlabCod_l(ros_slros_internal_block_Subs_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
  }
}

static void matlabCodegenHandle_matlabCodeg(ros_slros_internal_block_Publ_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
  }
}

/* Model step function */
void PI_Laengsregler_step(void)
{
  /* local block i/o variables */
  SL_Bus_PI_Laengsregler_std_msgs_Float32 rtb_SourceBlock_o2;
  SL_Bus_PI_Laengsregler_std_msgs_Float32 rtb_SourceBlock_o2_c;
  boolean_T rtb_SourceBlock_o1;
  boolean_T rtb_SourceBlock_o1_k;
  SL_Bus_PI_Laengsregler_std_msgs_Int16 rtb_BusAssignment;
  real_T rtb_Add;
  real_T tmp;
  if (rtmIsMajorTimeStep(PI_Laengsregler_M)) {
    /* set solver stop time */
    if (!(PI_Laengsregler_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&PI_Laengsregler_M->solverInfo,
                            ((PI_Laengsregler_M->Timing.clockTickH0 + 1) *
        PI_Laengsregler_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&PI_Laengsregler_M->solverInfo,
                            ((PI_Laengsregler_M->Timing.clockTick0 + 1) *
        PI_Laengsregler_M->Timing.stepSize0 +
        PI_Laengsregler_M->Timing.clockTickH0 *
        PI_Laengsregler_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(PI_Laengsregler_M)) {
    PI_Laengsregler_M->Timing.t[0] = rtsiGetT(&PI_Laengsregler_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(PI_Laengsregler_M)) {
    /* Outputs for Atomic SubSystem: '<Root>/Subscribe' */
    /* MATLABSystem: '<S4>/SourceBlock' */
    rtb_SourceBlock_o1_k = Sub_PI_Laengsregler_80.getLatestMessage
      (&rtb_SourceBlock_o2_c);

    /* Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' */
    PI_Laengsregle_EnabledSubsystem(rtb_SourceBlock_o1_k, &rtb_SourceBlock_o2_c,
      &PI_Laengsregler_B.EnabledSubsystem);

    /* End of Outputs for SubSystem: '<S4>/Enabled Subsystem' */
    /* End of Outputs for SubSystem: '<Root>/Subscribe' */

    /* Outputs for Atomic SubSystem: '<Root>/Subscribe1' */
    /* MATLABSystem: '<S5>/SourceBlock' */
    rtb_SourceBlock_o1 = Sub_PI_Laengsregler_128.getLatestMessage
      (&rtb_SourceBlock_o2);

    /* Outputs for Enabled SubSystem: '<S5>/Enabled Subsystem' */
    PI_Laengsregle_EnabledSubsystem(rtb_SourceBlock_o1, &rtb_SourceBlock_o2,
      &PI_Laengsregler_B.EnabledSubsystem_n);

    /* End of Outputs for SubSystem: '<S5>/Enabled Subsystem' */
    /* End of Outputs for SubSystem: '<Root>/Subscribe1' */

    /* Sum: '<S2>/Add' incorporates:
     *  DataTypeConversion: '<S2>/Data Type Conversion'
     *  DataTypeConversion: '<S2>/Data Type Conversion1'
     */
    rtb_Add = static_cast<real_T>(PI_Laengsregler_B.EnabledSubsystem.In1.Data) -
      PI_Laengsregler_B.EnabledSubsystem_n.In1.Data;

    /* Gain: '<S41>/Proportional Gain' */
    PI_Laengsregler_B.ProportionalGain = PI_Laengsregler_P.pr * rtb_Add;
  }

  /* DataTypeConversion: '<Root>/Data Type Conversion' incorporates:
   *  Gain: '<S2>/Getriebe'
   *  Gain: '<S2>/Radumfang'
   *  Integrator: '<S36>/Integrator'
   *  Sum: '<S45>/Sum'
   */
  tmp = floor((PI_Laengsregler_B.ProportionalGain +
               PI_Laengsregler_X.Integrator_CSTATE) *
              PI_Laengsregler_P.Radumfang_Gain * PI_Laengsregler_P.Getriebe_Gain);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 65536.0);
  }

  /* BusAssignment: '<Root>/Bus Assignment' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion'
   */
  rtb_BusAssignment.Data = static_cast<int16_T>((tmp < 0.0 ? static_cast<int32_T>
    (static_cast<int16_T>(-static_cast<int16_T>(static_cast<uint16_T>(-tmp)))) :
    static_cast<int32_T>(static_cast<int16_T>(static_cast<uint16_T>(tmp)))));

  /* Outputs for Atomic SubSystem: '<Root>/Publish' */
  /* MATLABSystem: '<S3>/SinkBlock' */
  Pub_PI_Laengsregler_79.publish(&rtb_BusAssignment);

  /* End of Outputs for SubSystem: '<Root>/Publish' */
  if (rtmIsMajorTimeStep(PI_Laengsregler_M)) {
    /* Gain: '<S33>/Integral Gain' */
    PI_Laengsregler_B.IntegralGain = PI_Laengsregler_P.ir * rtb_Add;
  }

  if (rtmIsMajorTimeStep(PI_Laengsregler_M)) {
    rt_ertODEUpdateContinuousStates(&PI_Laengsregler_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++PI_Laengsregler_M->Timing.clockTick0)) {
      ++PI_Laengsregler_M->Timing.clockTickH0;
    }

    PI_Laengsregler_M->Timing.t[0] = rtsiGetSolverStopTime
      (&PI_Laengsregler_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      PI_Laengsregler_M->Timing.clockTick1++;
      if (!PI_Laengsregler_M->Timing.clockTick1) {
        PI_Laengsregler_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void PI_Laengsregler_derivatives(void)
{
  XDot_PI_Laengsregler_T *_rtXdot;
  _rtXdot = ((XDot_PI_Laengsregler_T *) PI_Laengsregler_M->derivs);

  /* Derivatives for Integrator: '<S36>/Integrator' */
  _rtXdot->Integrator_CSTATE = PI_Laengsregler_B.IntegralGain;
}

/* Model initialize function */
void PI_Laengsregler_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&PI_Laengsregler_M->solverInfo,
                          &PI_Laengsregler_M->Timing.simTimeStep);
    rtsiSetTPtr(&PI_Laengsregler_M->solverInfo, &rtmGetTPtr(PI_Laengsregler_M));
    rtsiSetStepSizePtr(&PI_Laengsregler_M->solverInfo,
                       &PI_Laengsregler_M->Timing.stepSize0);
    rtsiSetdXPtr(&PI_Laengsregler_M->solverInfo, &PI_Laengsregler_M->derivs);
    rtsiSetContStatesPtr(&PI_Laengsregler_M->solverInfo, (real_T **)
                         &PI_Laengsregler_M->contStates);
    rtsiSetNumContStatesPtr(&PI_Laengsregler_M->solverInfo,
      &PI_Laengsregler_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&PI_Laengsregler_M->solverInfo,
      &PI_Laengsregler_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&PI_Laengsregler_M->solverInfo,
      &PI_Laengsregler_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&PI_Laengsregler_M->solverInfo,
      &PI_Laengsregler_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&PI_Laengsregler_M->solverInfo, (&rtmGetErrorStatus
      (PI_Laengsregler_M)));
    rtsiSetRTModelPtr(&PI_Laengsregler_M->solverInfo, PI_Laengsregler_M);
  }

  rtsiSetSimTimeStep(&PI_Laengsregler_M->solverInfo, MAJOR_TIME_STEP);
  PI_Laengsregler_M->intgData.y = PI_Laengsregler_M->odeY;
  PI_Laengsregler_M->intgData.f[0] = PI_Laengsregler_M->odeF[0];
  PI_Laengsregler_M->intgData.f[1] = PI_Laengsregler_M->odeF[1];
  PI_Laengsregler_M->intgData.f[2] = PI_Laengsregler_M->odeF[2];
  PI_Laengsregler_M->contStates = ((X_PI_Laengsregler_T *) &PI_Laengsregler_X);
  rtsiSetSolverData(&PI_Laengsregler_M->solverInfo, static_cast<void *>
                    (&PI_Laengsregler_M->intgData));
  rtsiSetSolverName(&PI_Laengsregler_M->solverInfo,"ode3");
  rtmSetTPtr(PI_Laengsregler_M, &PI_Laengsregler_M->Timing.tArray[0]);
  PI_Laengsregler_M->Timing.stepSize0 = 0.01;

  /* block I/O */
  (void) memset((static_cast<void *>(&PI_Laengsregler_B)), 0,
                sizeof(B_PI_Laengsregler_T));

  /* states (continuous) */
  {
    (void) memset(static_cast<void *>(&PI_Laengsregler_X), 0,
                  sizeof(X_PI_Laengsregler_T));
  }

  /* states (dwork) */
  (void) memset(static_cast<void *>(&PI_Laengsregler_DW), 0,
                sizeof(DW_PI_Laengsregler_T));

  {
    char_T tmp[14];
    char_T tmp_0[17];
    int32_T i;
    static const char_T tmp_1[16] = { '/', 't', 'r', 'j', '_', 't', 'a', 'r',
      'g', 'e', 't', 'S', 'p', 'e', 'e', 'd' };

    static const char_T tmp_2[13] = { '/', 'c', 't', 'l', '_', 'v', 'e', 'l',
      'o', 'c', 'i', 't', 'y' };

    static const char_T tmp_3[13] = { '/', 'c', 't', 'l', '_', 'm', 'o', 't',
      'o', 'r', 'R', 'p', 'm' };

    /* Start for Atomic SubSystem: '<Root>/Subscribe' */
    /* Start for MATLABSystem: '<S4>/SourceBlock' */
    PI_Laengsregler_DW.obj_j.matlabCodegenIsDeleted = false;
    PI_Laengsregler_DW.objisempty_c = true;
    PI_Laengsregler_DW.obj_j.isInitialized = 1;
    for (i = 0; i < 16; i++) {
      tmp_0[i] = tmp_1[i];
    }

    tmp_0[16] = '\x00';
    Sub_PI_Laengsregler_80.createSubscriber(tmp_0, 1);
    PI_Laengsregler_DW.obj_j.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S4>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe' */

    /* Start for Atomic SubSystem: '<Root>/Subscribe1' */
    /* Start for MATLABSystem: '<S5>/SourceBlock' */
    PI_Laengsregler_DW.obj_o.matlabCodegenIsDeleted = false;
    PI_Laengsregler_DW.objisempty = true;
    PI_Laengsregler_DW.obj_o.isInitialized = 1;
    for (i = 0; i < 13; i++) {
      tmp[i] = tmp_2[i];
    }

    tmp[13] = '\x00';
    Sub_PI_Laengsregler_128.createSubscriber(tmp, 1);
    PI_Laengsregler_DW.obj_o.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S5>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe1' */

    /* Start for Atomic SubSystem: '<Root>/Publish' */
    /* Start for MATLABSystem: '<S3>/SinkBlock' */
    PI_Laengsregler_DW.obj.matlabCodegenIsDeleted = false;
    PI_Laengsregler_DW.objisempty_f = true;
    PI_Laengsregler_DW.obj.isInitialized = 1;
    for (i = 0; i < 13; i++) {
      tmp[i] = tmp_3[i];
    }

    tmp[13] = '\x00';
    Pub_PI_Laengsregler_79.createPublisher(tmp, 1);
    PI_Laengsregler_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S3>/SinkBlock' */
    /* End of Start for SubSystem: '<Root>/Publish' */
  }

  /* InitializeConditions for Integrator: '<S36>/Integrator' */
  PI_Laengsregler_X.Integrator_CSTATE =
    PI_Laengsregler_P.PIDController_InitialConditionF;

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe' */
  /* SystemInitialize for Enabled SubSystem: '<S4>/Enabled Subsystem' */
  PI_Laengs_EnabledSubsystem_Init(&PI_Laengsregler_B.EnabledSubsystem,
    &PI_Laengsregler_P.EnabledSubsystem);

  /* End of SystemInitialize for SubSystem: '<S4>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe' */

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe1' */
  /* SystemInitialize for Enabled SubSystem: '<S5>/Enabled Subsystem' */
  PI_Laengs_EnabledSubsystem_Init(&PI_Laengsregler_B.EnabledSubsystem_n,
    &PI_Laengsregler_P.EnabledSubsystem_n);

  /* End of SystemInitialize for SubSystem: '<S5>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe1' */
}

/* Model terminate function */
void PI_Laengsregler_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Subscribe' */
  /* Terminate for MATLABSystem: '<S4>/SourceBlock' */
  matlabCodegenHandle_matlabCod_l(&PI_Laengsregler_DW.obj_j);

  /* End of Terminate for SubSystem: '<Root>/Subscribe' */

  /* Terminate for Atomic SubSystem: '<Root>/Subscribe1' */
  /* Terminate for MATLABSystem: '<S5>/SourceBlock' */
  matlabCodegenHandle_matlabCod_l(&PI_Laengsregler_DW.obj_o);

  /* End of Terminate for SubSystem: '<Root>/Subscribe1' */

  /* Terminate for Atomic SubSystem: '<Root>/Publish' */
  /* Terminate for MATLABSystem: '<S3>/SinkBlock' */
  matlabCodegenHandle_matlabCodeg(&PI_Laengsregler_DW.obj);

  /* End of Terminate for SubSystem: '<Root>/Publish' */
}
