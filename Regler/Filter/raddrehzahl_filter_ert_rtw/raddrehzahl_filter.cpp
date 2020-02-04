/*
 * raddrehzahl_filter.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "raddrehzahl_filter".
 *
 * Model version              : 1.9
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Tue Feb  4 19:28:58 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "raddrehzahl_filter.h"
#include "raddrehzahl_filter_private.h"

/* Block signals (default storage) */
B_raddrehzahl_filter_T raddrehzahl_filter_B;

/* Continuous states */
X_raddrehzahl_filter_T raddrehzahl_filter_X;

/* Block states (default storage) */
DW_raddrehzahl_filter_T raddrehzahl_filter_DW;

/* Real-time model */
RT_MODEL_raddrehzahl_filter_T raddrehzahl_filter_M_ =
  RT_MODEL_raddrehzahl_filter_T();
RT_MODEL_raddrehzahl_filter_T *const raddrehzahl_filter_M =
  &raddrehzahl_filter_M_;

/* Forward declaration for local functions */
static void matlabCodegenHandle_matlabCo_my(ros_slros_internal_block_Subs_T *obj);
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
  raddrehzahl_filter_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  raddrehzahl_filter_step();
  raddrehzahl_filter_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  raddrehzahl_filter_step();
  raddrehzahl_filter_derivatives();

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
 *    '<S6>/Enabled Subsystem'
 *    '<S7>/Enabled Subsystem'
 */
void raddrehza_EnabledSubsystem_Init(B_EnabledSubsystem_raddrehzah_T *localB,
  P_EnabledSubsystem_raddrehzah_T *localP)
{
  /* SystemInitialize for Outport: '<S9>/Out1' */
  localB->In1 = localP->Out1_Y0;
}

/*
 * Output and update for enable system:
 *    '<S6>/Enabled Subsystem'
 *    '<S7>/Enabled Subsystem'
 */
void raddrehzahl_fi_EnabledSubsystem(boolean_T rtu_Enable, const
  SL_Bus_raddrehzahl_filter_std_msgs_Float32 *rtu_In1,
  B_EnabledSubsystem_raddrehzah_T *localB)
{
  /* Outputs for Enabled SubSystem: '<S6>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S9>/Enable'
   */
  if (rtu_Enable) {
    /* Inport: '<S9>/In1' */
    localB->In1 = *rtu_In1;
  }

  /* End of Outputs for SubSystem: '<S6>/Enabled Subsystem' */
}

static void matlabCodegenHandle_matlabCo_my(ros_slros_internal_block_Subs_T *obj)
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
void raddrehzahl_filter_step(void)
{
  /* local block i/o variables */
  SL_Bus_raddrehzahl_filter_std_msgs_Float32 rtb_SourceBlock_o2;
  SL_Bus_raddrehzahl_filter_std_msgs_Float32 rtb_SourceBlock_o2_g;
  boolean_T rtb_SourceBlock_o1;
  boolean_T rtb_SourceBlock_o1_d;
  SL_Bus_raddrehzahl_filter_std_msgs_Bool b_varargout_2;
  boolean_T b_varargout_1;
  SL_Bus_raddrehzahl_filter_std_msgs_Float32 rtb_BusAssignment1;
  SL_Bus_raddrehzahl_filter_std_msgs_Float32 rtb_BusAssignment;
  if (rtmIsMajorTimeStep(raddrehzahl_filter_M)) {
    /* set solver stop time */
    if (!(raddrehzahl_filter_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&raddrehzahl_filter_M->solverInfo,
                            ((raddrehzahl_filter_M->Timing.clockTickH0 + 1) *
        raddrehzahl_filter_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&raddrehzahl_filter_M->solverInfo,
                            ((raddrehzahl_filter_M->Timing.clockTick0 + 1) *
        raddrehzahl_filter_M->Timing.stepSize0 +
        raddrehzahl_filter_M->Timing.clockTickH0 *
        raddrehzahl_filter_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(raddrehzahl_filter_M)) {
    raddrehzahl_filter_M->Timing.t[0] = rtsiGetT
      (&raddrehzahl_filter_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(raddrehzahl_filter_M)) {
    /* Outputs for Atomic SubSystem: '<Root>/Subscribe2' */
    /* MATLABSystem: '<S7>/SourceBlock' */
    rtb_SourceBlock_o1 = Sub_raddrehzahl_filter_22.getLatestMessage
      (&rtb_SourceBlock_o2);

    /* Outputs for Enabled SubSystem: '<S7>/Enabled Subsystem' */
    raddrehzahl_fi_EnabledSubsystem(rtb_SourceBlock_o1, &rtb_SourceBlock_o2,
      &raddrehzahl_filter_B.EnabledSubsystem_b);

    /* End of Outputs for SubSystem: '<S7>/Enabled Subsystem' */
    /* End of Outputs for SubSystem: '<Root>/Subscribe2' */

    /* Outputs for Atomic SubSystem: '<Root>/Subscribe' */
    /* MATLABSystem: '<S5>/SourceBlock' incorporates:
     *  Inport: '<S8>/In1'
     */
    b_varargout_1 = Sub_raddrehzahl_filter_19.getLatestMessage(&b_varargout_2);

    /* Outputs for Enabled SubSystem: '<S5>/Enabled Subsystem' incorporates:
     *  EnablePort: '<S8>/Enable'
     */
    if (b_varargout_1) {
      raddrehzahl_filter_B.In1 = b_varargout_2;
    }

    /* End of MATLABSystem: '<S5>/SourceBlock' */
    /* End of Outputs for SubSystem: '<S5>/Enabled Subsystem' */
    /* End of Outputs for SubSystem: '<Root>/Subscribe' */

    /* Outputs for Atomic SubSystem: '<Root>/Subscribe1' */
    /* MATLABSystem: '<S6>/SourceBlock' */
    rtb_SourceBlock_o1_d = Sub_raddrehzahl_filter_3.getLatestMessage
      (&rtb_SourceBlock_o2_g);

    /* Outputs for Enabled SubSystem: '<S6>/Enabled Subsystem' */
    raddrehzahl_fi_EnabledSubsystem(rtb_SourceBlock_o1_d, &rtb_SourceBlock_o2_g,
      &raddrehzahl_filter_B.EnabledSubsystem_a);

    /* End of Outputs for SubSystem: '<S6>/Enabled Subsystem' */
    /* End of Outputs for SubSystem: '<Root>/Subscribe1' */

    /* DiscreteTransferFcn: '<Root>/Discrete Transfer Fcn' incorporates:
     *  DataTypeConversion: '<Root>/Data Type Conversion'
     */
    raddrehzahl_filter_DW.DiscreteTransferFcn_tmp =
      ((raddrehzahl_filter_B.EnabledSubsystem_a.In1.Data -
        raddrehzahl_filter_P.denom_drehzahl[1] *
        raddrehzahl_filter_DW.DiscreteTransferFcn_states[0]) -
       raddrehzahl_filter_P.denom_drehzahl[2] *
       raddrehzahl_filter_DW.DiscreteTransferFcn_states[1]) /
      raddrehzahl_filter_P.denom_drehzahl[0];

    /* Switch: '<Root>/Switch' incorporates:
     *  DiscreteTransferFcn: '<Root>/Discrete Transfer Fcn'
     *  Gain: '<Root>/Multiply'
     */
    if (raddrehzahl_filter_B.In1.Data) {
      raddrehzahl_filter_B.Switch =
        raddrehzahl_filter_B.EnabledSubsystem_b.In1.Data;
    } else {
      raddrehzahl_filter_B.Switch = ((raddrehzahl_filter_P.num_drehzahl[0] *
        raddrehzahl_filter_DW.DiscreteTransferFcn_tmp +
        raddrehzahl_filter_P.num_drehzahl[1] *
        raddrehzahl_filter_DW.DiscreteTransferFcn_states[0]) +
        raddrehzahl_filter_P.num_drehzahl[2] *
        raddrehzahl_filter_DW.DiscreteTransferFcn_states[1]) *
        raddrehzahl_filter_P.Multiply_Gain;
    }

    /* End of Switch: '<Root>/Switch' */

    /* BusAssignment: '<Root>/Bus Assignment' incorporates:
     *  DataTypeConversion: '<Root>/Data Type Conversion1'
     */
    rtb_BusAssignment.Data = static_cast<real32_T>(raddrehzahl_filter_B.Switch);

    /* Outputs for Atomic SubSystem: '<Root>/Publish' */
    /* MATLABSystem: '<S3>/SinkBlock' */
    Pub_raddrehzahl_filter_7.publish(&rtb_BusAssignment);

    /* End of Outputs for SubSystem: '<Root>/Publish' */
  }

  /* BusAssignment: '<Root>/Bus Assignment1' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion2'
   *  Integrator: '<Root>/Integrator'
   */
  rtb_BusAssignment1.Data = static_cast<real32_T>
    (raddrehzahl_filter_X.Integrator_CSTATE);

  /* Outputs for Atomic SubSystem: '<Root>/Publish1' */
  /* MATLABSystem: '<S4>/SinkBlock' */
  Pub_raddrehzahl_filter_12.publish(&rtb_BusAssignment1);

  /* End of Outputs for SubSystem: '<Root>/Publish1' */
  if (rtmIsMajorTimeStep(raddrehzahl_filter_M)) {
    if (rtmIsMajorTimeStep(raddrehzahl_filter_M)) {
      /* Update for DiscreteTransferFcn: '<Root>/Discrete Transfer Fcn' */
      raddrehzahl_filter_DW.DiscreteTransferFcn_states[1] =
        raddrehzahl_filter_DW.DiscreteTransferFcn_states[0];
      raddrehzahl_filter_DW.DiscreteTransferFcn_states[0] =
        raddrehzahl_filter_DW.DiscreteTransferFcn_tmp;
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(raddrehzahl_filter_M)) {
    rt_ertODEUpdateContinuousStates(&raddrehzahl_filter_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++raddrehzahl_filter_M->Timing.clockTick0)) {
      ++raddrehzahl_filter_M->Timing.clockTickH0;
    }

    raddrehzahl_filter_M->Timing.t[0] = rtsiGetSolverStopTime
      (&raddrehzahl_filter_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.2s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.2, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      raddrehzahl_filter_M->Timing.clockTick1++;
      if (!raddrehzahl_filter_M->Timing.clockTick1) {
        raddrehzahl_filter_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void raddrehzahl_filter_derivatives(void)
{
  XDot_raddrehzahl_filter_T *_rtXdot;
  _rtXdot = ((XDot_raddrehzahl_filter_T *) raddrehzahl_filter_M->derivs);

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE = raddrehzahl_filter_B.Switch;
}

/* Model initialize function */
void raddrehzahl_filter_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&raddrehzahl_filter_M->solverInfo,
                          &raddrehzahl_filter_M->Timing.simTimeStep);
    rtsiSetTPtr(&raddrehzahl_filter_M->solverInfo, &rtmGetTPtr
                (raddrehzahl_filter_M));
    rtsiSetStepSizePtr(&raddrehzahl_filter_M->solverInfo,
                       &raddrehzahl_filter_M->Timing.stepSize0);
    rtsiSetdXPtr(&raddrehzahl_filter_M->solverInfo,
                 &raddrehzahl_filter_M->derivs);
    rtsiSetContStatesPtr(&raddrehzahl_filter_M->solverInfo, (real_T **)
                         &raddrehzahl_filter_M->contStates);
    rtsiSetNumContStatesPtr(&raddrehzahl_filter_M->solverInfo,
      &raddrehzahl_filter_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&raddrehzahl_filter_M->solverInfo,
      &raddrehzahl_filter_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&raddrehzahl_filter_M->solverInfo,
      &raddrehzahl_filter_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&raddrehzahl_filter_M->solverInfo,
      &raddrehzahl_filter_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&raddrehzahl_filter_M->solverInfo, (&rtmGetErrorStatus
      (raddrehzahl_filter_M)));
    rtsiSetRTModelPtr(&raddrehzahl_filter_M->solverInfo, raddrehzahl_filter_M);
  }

  rtsiSetSimTimeStep(&raddrehzahl_filter_M->solverInfo, MAJOR_TIME_STEP);
  raddrehzahl_filter_M->intgData.y = raddrehzahl_filter_M->odeY;
  raddrehzahl_filter_M->intgData.f[0] = raddrehzahl_filter_M->odeF[0];
  raddrehzahl_filter_M->intgData.f[1] = raddrehzahl_filter_M->odeF[1];
  raddrehzahl_filter_M->intgData.f[2] = raddrehzahl_filter_M->odeF[2];
  raddrehzahl_filter_M->contStates = ((X_raddrehzahl_filter_T *)
    &raddrehzahl_filter_X);
  rtsiSetSolverData(&raddrehzahl_filter_M->solverInfo, static_cast<void *>
                    (&raddrehzahl_filter_M->intgData));
  rtsiSetSolverName(&raddrehzahl_filter_M->solverInfo,"ode3");
  rtmSetTPtr(raddrehzahl_filter_M, &raddrehzahl_filter_M->Timing.tArray[0]);
  raddrehzahl_filter_M->Timing.stepSize0 = 0.2;

  /* block I/O */
  (void) memset((static_cast<void *>(&raddrehzahl_filter_B)), 0,
                sizeof(B_raddrehzahl_filter_T));

  /* states (continuous) */
  {
    (void) memset(static_cast<void *>(&raddrehzahl_filter_X), 0,
                  sizeof(X_raddrehzahl_filter_T));
  }

  /* states (dwork) */
  (void) memset(static_cast<void *>(&raddrehzahl_filter_DW), 0,
                sizeof(DW_raddrehzahl_filter_T));

  {
    char_T tmp[14];
    char_T tmp_0[25];
    char_T tmp_1[17];
    int32_T i;
    static const char_T tmp_2[16] = { '/', 't', 'r', 'j', '_', 't', 'a', 'r',
      'g', 'e', 't', 'S', 'p', 'e', 'e', 'd' };

    static const char_T tmp_3[24] = { '/', 'c', 't', 'l', '_', 'w', 'i', 't',
      'h', 'o', 'u', 't', 'S', 'e', 'n', 's', 'o', 'r', 'V', 'a', 'l', 'u', 'e',
      's' };

    static const char_T tmp_4[13] = { '/', 's', 'n', 's', '_', 'w', 'h', 'e',
      'e', 'l', 'R', 'p', 'm' };

    static const char_T tmp_5[13] = { '/', 'c', 't', 'l', '_', 'v', 'e', 'l',
      'o', 'c', 'i', 't', 'y' };

    static const char_T tmp_6[13] = { '/', 'c', 't', 'l', '_', 'd', 'i', 's',
      't', 'a', 'n', 'c', 'e' };

    /* Start for Atomic SubSystem: '<Root>/Subscribe2' */
    /* Start for MATLABSystem: '<S7>/SourceBlock' */
    raddrehzahl_filter_DW.obj_d.matlabCodegenIsDeleted = false;
    raddrehzahl_filter_DW.objisempty = true;
    raddrehzahl_filter_DW.obj_d.isInitialized = 1;
    for (i = 0; i < 16; i++) {
      tmp_1[i] = tmp_2[i];
    }

    tmp_1[16] = '\x00';
    Sub_raddrehzahl_filter_22.createSubscriber(tmp_1, 1);
    raddrehzahl_filter_DW.obj_d.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S7>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe2' */

    /* Start for Atomic SubSystem: '<Root>/Subscribe' */
    /* Start for MATLABSystem: '<S5>/SourceBlock' */
    raddrehzahl_filter_DW.obj_m.matlabCodegenIsDeleted = false;
    raddrehzahl_filter_DW.objisempty_g = true;
    raddrehzahl_filter_DW.obj_m.isInitialized = 1;
    for (i = 0; i < 24; i++) {
      tmp_0[i] = tmp_3[i];
    }

    tmp_0[24] = '\x00';
    Sub_raddrehzahl_filter_19.createSubscriber(tmp_0, 1);
    raddrehzahl_filter_DW.obj_m.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S5>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe' */

    /* Start for Atomic SubSystem: '<Root>/Subscribe1' */
    /* Start for MATLABSystem: '<S6>/SourceBlock' */
    raddrehzahl_filter_DW.obj_dl.matlabCodegenIsDeleted = false;
    raddrehzahl_filter_DW.objisempty_o = true;
    raddrehzahl_filter_DW.obj_dl.isInitialized = 1;
    for (i = 0; i < 13; i++) {
      tmp[i] = tmp_4[i];
    }

    tmp[13] = '\x00';
    Sub_raddrehzahl_filter_3.createSubscriber(tmp, 1);
    raddrehzahl_filter_DW.obj_dl.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S6>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe1' */

    /* Start for Atomic SubSystem: '<Root>/Publish' */
    /* Start for MATLABSystem: '<S3>/SinkBlock' */
    raddrehzahl_filter_DW.obj_i.matlabCodegenIsDeleted = false;
    raddrehzahl_filter_DW.objisempty_k = true;
    raddrehzahl_filter_DW.obj_i.isInitialized = 1;
    for (i = 0; i < 13; i++) {
      tmp[i] = tmp_5[i];
    }

    tmp[13] = '\x00';
    Pub_raddrehzahl_filter_7.createPublisher(tmp, 1);
    raddrehzahl_filter_DW.obj_i.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S3>/SinkBlock' */
    /* End of Start for SubSystem: '<Root>/Publish' */

    /* Start for Atomic SubSystem: '<Root>/Publish1' */
    /* Start for MATLABSystem: '<S4>/SinkBlock' */
    raddrehzahl_filter_DW.obj.matlabCodegenIsDeleted = false;
    raddrehzahl_filter_DW.objisempty_j = true;
    raddrehzahl_filter_DW.obj.isInitialized = 1;
    for (i = 0; i < 13; i++) {
      tmp[i] = tmp_6[i];
    }

    tmp[13] = '\x00';
    Pub_raddrehzahl_filter_12.createPublisher(tmp, 1);
    raddrehzahl_filter_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S4>/SinkBlock' */
    /* End of Start for SubSystem: '<Root>/Publish1' */
  }

  /* InitializeConditions for DiscreteTransferFcn: '<Root>/Discrete Transfer Fcn' */
  raddrehzahl_filter_DW.DiscreteTransferFcn_states[0] =
    raddrehzahl_filter_P.DiscreteTransferFcn_InitialStat;
  raddrehzahl_filter_DW.DiscreteTransferFcn_states[1] =
    raddrehzahl_filter_P.DiscreteTransferFcn_InitialStat;

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  raddrehzahl_filter_X.Integrator_CSTATE = raddrehzahl_filter_P.Integrator_IC;

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe2' */
  /* SystemInitialize for Enabled SubSystem: '<S7>/Enabled Subsystem' */
  raddrehza_EnabledSubsystem_Init(&raddrehzahl_filter_B.EnabledSubsystem_b,
    &raddrehzahl_filter_P.EnabledSubsystem_b);

  /* End of SystemInitialize for SubSystem: '<S7>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe2' */

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe' */
  /* SystemInitialize for Enabled SubSystem: '<S5>/Enabled Subsystem' */
  /* SystemInitialize for Outport: '<S8>/Out1' */
  raddrehzahl_filter_B.In1 = raddrehzahl_filter_P.Out1_Y0;

  /* End of SystemInitialize for SubSystem: '<S5>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe' */

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe1' */
  /* SystemInitialize for Enabled SubSystem: '<S6>/Enabled Subsystem' */
  raddrehza_EnabledSubsystem_Init(&raddrehzahl_filter_B.EnabledSubsystem_a,
    &raddrehzahl_filter_P.EnabledSubsystem_a);

  /* End of SystemInitialize for SubSystem: '<S6>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe1' */
}

/* Model terminate function */
void raddrehzahl_filter_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Subscribe2' */
  /* Terminate for MATLABSystem: '<S7>/SourceBlock' */
  matlabCodegenHandle_matlabCo_my(&raddrehzahl_filter_DW.obj_d);

  /* End of Terminate for SubSystem: '<Root>/Subscribe2' */

  /* Terminate for Atomic SubSystem: '<Root>/Subscribe' */
  /* Terminate for MATLABSystem: '<S5>/SourceBlock' */
  matlabCodegenHandle_matlabCo_my(&raddrehzahl_filter_DW.obj_m);

  /* End of Terminate for SubSystem: '<Root>/Subscribe' */

  /* Terminate for Atomic SubSystem: '<Root>/Subscribe1' */
  /* Terminate for MATLABSystem: '<S6>/SourceBlock' */
  matlabCodegenHandle_matlabCo_my(&raddrehzahl_filter_DW.obj_dl);

  /* End of Terminate for SubSystem: '<Root>/Subscribe1' */

  /* Terminate for Atomic SubSystem: '<Root>/Publish' */
  /* Terminate for MATLABSystem: '<S3>/SinkBlock' */
  matlabCodegenHandle_matlabCodeg(&raddrehzahl_filter_DW.obj_i);

  /* End of Terminate for SubSystem: '<Root>/Publish' */

  /* Terminate for Atomic SubSystem: '<Root>/Publish1' */
  /* Terminate for MATLABSystem: '<S4>/SinkBlock' */
  matlabCodegenHandle_matlabCodeg(&raddrehzahl_filter_DW.obj);

  /* End of Terminate for SubSystem: '<Root>/Publish1' */
}
