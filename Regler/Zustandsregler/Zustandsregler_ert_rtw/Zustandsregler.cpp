/*
 * Zustandsregler.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Zustandsregler".
 *
 * Model version              : 1.33
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Mon Jan 20 02:09:21 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
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
RT_MODEL_Zustandsregler_T Zustandsregler_M_ = RT_MODEL_Zustandsregler_T();
RT_MODEL_Zustandsregler_T *const Zustandsregler_M = &Zustandsregler_M_;

/* Forward declaration for local functions */
static void matlabCodegenHandle_matlabCod_i(ros_slros_internal_block_Subs_T *obj);
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
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                static_cast<uint_T>(nXc)*sizeof(real_T));

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

/*
 * System initialize for enable system:
 *    '<S3>/Enabled Subsystem'
 *    '<S4>/Enabled Subsystem'
 *    '<S5>/Enabled Subsystem'
 *    '<S6>/Enabled Subsystem'
 */
void Zustandsr_EnabledSubsystem_Init(B_EnabledSubsystem_Zustandsre_T *localB,
  P_EnabledSubsystem_Zustandsre_T *localP)
{
  /* SystemInitialize for Outport: '<S8>/Out1' */
  localB->In1 = localP->Out1_Y0;
}

/*
 * Output and update for enable system:
 *    '<S3>/Enabled Subsystem'
 *    '<S4>/Enabled Subsystem'
 *    '<S5>/Enabled Subsystem'
 *    '<S6>/Enabled Subsystem'
 */
void Zustandsregler_EnabledSubsystem(boolean_T rtu_Enable, const
  SL_Bus_Zustandsregler_std_msgs_Float64 *rtu_In1,
  B_EnabledSubsystem_Zustandsre_T *localB)
{
  /* Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S8>/Enable'
   */
  if (rtu_Enable) {
    /* Inport: '<S8>/In1' */
    localB->In1 = *rtu_In1;
  }

  /* End of Outputs for SubSystem: '<S3>/Enabled Subsystem' */
}

static void matlabCodegenHandle_matlabCod_i(ros_slros_internal_block_Subs_T *obj)
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
void Zustandsregler_step(void)
{
  /* local block i/o variables */
  SL_Bus_Zustandsregler_std_msgs_Float64 rtb_SourceBlock_o2;
  SL_Bus_Zustandsregler_std_msgs_Float64 rtb_SourceBlock_o2_e;
  SL_Bus_Zustandsregler_std_msgs_Float64 rtb_SourceBlock_o2_e5;
  SL_Bus_Zustandsregler_std_msgs_Float64 rtb_SourceBlock_o2_f;
  boolean_T rtb_SourceBlock_o1;
  boolean_T rtb_SourceBlock_o1_i;
  boolean_T rtb_SourceBlock_o1_m;
  boolean_T rtb_SourceBlock_o1_o;
  SL_Bus_Zustandsregler_std_msgs_Float32 rtb_BusAssignment;
  real_T rtb_Add1_idx_1;
  real_T rtb_Add1_idx_0;
  real_T rtb_Add1_idx_1_0;
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

  if (rtmIsMajorTimeStep(Zustandsregler_M)) {
    /* Outputs for Atomic SubSystem: '<Root>/Subscribe2' */
    /* MATLABSystem: '<S5>/SourceBlock' */
    rtb_SourceBlock_o1_i = Sub_Zustandsregler_172.getLatestMessage
      (&rtb_SourceBlock_o2_e);

    /* Outputs for Enabled SubSystem: '<S5>/Enabled Subsystem' */
    Zustandsregler_EnabledSubsystem(rtb_SourceBlock_o1_i, &rtb_SourceBlock_o2_e,
      &Zustandsregler_B.EnabledSubsystem_m);

    /* End of Outputs for SubSystem: '<S5>/Enabled Subsystem' */
    /* End of Outputs for SubSystem: '<Root>/Subscribe2' */

    /* Outputs for Atomic SubSystem: '<Root>/Subscribe3' */
    /* MATLABSystem: '<S6>/SourceBlock' */
    rtb_SourceBlock_o1 = Sub_Zustandsregler_174.getLatestMessage
      (&rtb_SourceBlock_o2);

    /* Outputs for Enabled SubSystem: '<S6>/Enabled Subsystem' */
    Zustandsregler_EnabledSubsystem(rtb_SourceBlock_o1, &rtb_SourceBlock_o2,
      &Zustandsregler_B.EnabledSubsystem_a);

    /* End of Outputs for SubSystem: '<S6>/Enabled Subsystem' */
    /* End of Outputs for SubSystem: '<Root>/Subscribe3' */

    /* Sum: '<S7>/Add3' incorporates:
     *  Gain: '<S7>/Multiply2'
     *  Gain: '<S7>/Multiply3'
     */
    Zustandsregler_B.rtb_Add3_idx_0 = Zustandsregler_P.Multiply2_Gain[0] *
      Zustandsregler_B.EnabledSubsystem_m.In1.Data +
      Zustandsregler_P.Multiply3_Gain[0] *
      Zustandsregler_B.EnabledSubsystem_a.In1.Data;
    Zustandsregler_B.rtb_Add3_idx_1 = Zustandsregler_P.Multiply2_Gain[1] *
      Zustandsregler_B.EnabledSubsystem_m.In1.Data +
      Zustandsregler_P.Multiply3_Gain[1] *
      Zustandsregler_B.EnabledSubsystem_a.In1.Data;

    /* Outputs for Atomic SubSystem: '<Root>/Subscribe' */
    /* MATLABSystem: '<S3>/SourceBlock' */
    rtb_SourceBlock_o1_o = Sub_Zustandsregler_126.getLatestMessage
      (&rtb_SourceBlock_o2_f);

    /* Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' */
    Zustandsregler_EnabledSubsystem(rtb_SourceBlock_o1_o, &rtb_SourceBlock_o2_f,
      &Zustandsregler_B.EnabledSubsystem);

    /* End of Outputs for SubSystem: '<S3>/Enabled Subsystem' */
    /* End of Outputs for SubSystem: '<Root>/Subscribe' */

    /* Outputs for Atomic SubSystem: '<Root>/Subscribe1' */
    /* MATLABSystem: '<S4>/SourceBlock' */
    rtb_SourceBlock_o1_m = Sub_Zustandsregler_170.getLatestMessage
      (&rtb_SourceBlock_o2_e5);

    /* Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' */
    Zustandsregler_EnabledSubsystem(rtb_SourceBlock_o1_m, &rtb_SourceBlock_o2_e5,
      &Zustandsregler_B.EnabledSubsystem_p);

    /* End of Outputs for SubSystem: '<S4>/Enabled Subsystem' */
    /* End of Outputs for SubSystem: '<Root>/Subscribe1' */

    /* Sum: '<S7>/Add1' incorporates:
     *  Gain: '<S7>/Multiply'
     *  Gain: '<S7>/Multiply1'
     */
    Zustandsregler_B.rtb_Add1_idx_0 = Zustandsregler_P.Multiply_Gain[0] *
      Zustandsregler_B.EnabledSubsystem.In1.Data +
      Zustandsregler_P.Multiply1_Gain[0] *
      Zustandsregler_B.EnabledSubsystem_p.In1.Data;
    rtb_Add1_idx_1 = Zustandsregler_P.Multiply_Gain[1] *
      Zustandsregler_B.EnabledSubsystem.In1.Data +
      Zustandsregler_P.Multiply1_Gain[1] *
      Zustandsregler_B.EnabledSubsystem_p.In1.Data;

    /* Sum: '<S7>/Subtract' incorporates:
     *  Constant: '<S7>/kT'
     *  Product: '<S7>/Product'
     */
    rtb_Add1_idx_0 = Zustandsregler_B.rtb_Add1_idx_0 - (Zustandsregler_P.K[0] *
      Zustandsregler_B.rtb_Add3_idx_0 + Zustandsregler_P.K[2] *
      Zustandsregler_B.rtb_Add3_idx_1);
    rtb_Add1_idx_1_0 = rtb_Add1_idx_1 - (Zustandsregler_P.K[1] *
      Zustandsregler_B.rtb_Add3_idx_0 + Zustandsregler_P.K[3] *
      Zustandsregler_B.rtb_Add3_idx_1);

    /* Sum: '<S7>/Add' incorporates:
     *  Constant: '<S7>/A'
     *  Constant: '<S7>/b'
     *  Product: '<S7>/Product1'
     *  Product: '<S7>/Product2'
     */
    Zustandsregler_B.x[0] = (Zustandsregler_P.eingangsVektor_b[0] *
      rtb_Add1_idx_0 + Zustandsregler_P.eingangsVektor_b[2] * rtb_Add1_idx_1_0)
      + (Zustandsregler_P.systemMatrix_A[0] * Zustandsregler_B.rtb_Add3_idx_0 +
         Zustandsregler_P.systemMatrix_A[2] * Zustandsregler_B.rtb_Add3_idx_1);
    Zustandsregler_B.x[1] = (Zustandsregler_P.eingangsVektor_b[1] *
      rtb_Add1_idx_0 + Zustandsregler_P.eingangsVektor_b[3] * rtb_Add1_idx_1_0)
      + (Zustandsregler_P.systemMatrix_A[1] * Zustandsregler_B.rtb_Add3_idx_0 +
         Zustandsregler_P.systemMatrix_A[3] * Zustandsregler_B.rtb_Add3_idx_1);

    /* Product: '<S7>/Product4' incorporates:
     *  Constant: '<S7>/d'
     */
    Zustandsregler_B.Product4 = Zustandsregler_P.d[0] *
      Zustandsregler_B.rtb_Add1_idx_0 + Zustandsregler_P.d[1] * rtb_Add1_idx_1;
  }

  /* Sum: '<S7>/Add2' incorporates:
   *  Constant: '<S7>/cT'
   *  Integrator: '<S7>/Integrator'
   *  Product: '<S7>/Product3'
   */
  Zustandsregler_B.rtb_Add3_idx_0 = (Zustandsregler_P.ausgangsVektor_cT[0] *
    Zustandsregler_X.Integrator_CSTATE[0] + Zustandsregler_P.ausgangsVektor_cT[1]
    * Zustandsregler_X.Integrator_CSTATE[1]) + Zustandsregler_B.Product4;

  /* Saturate: '<S7>/Saturation' */
  if (Zustandsregler_B.rtb_Add3_idx_0 > Zustandsregler_P.Saturation_UpperSat) {
    /* BusAssignment: '<Root>/Bus Assignment' incorporates:
     *  DataTypeConversion: '<Root>/Data Type Conversion'
     */
    rtb_BusAssignment.Data = static_cast<real32_T>
      (Zustandsregler_P.Saturation_UpperSat);
  } else if (Zustandsregler_B.rtb_Add3_idx_0 <
             Zustandsregler_P.Saturation_LowerSat) {
    /* BusAssignment: '<Root>/Bus Assignment' incorporates:
     *  DataTypeConversion: '<Root>/Data Type Conversion'
     */
    rtb_BusAssignment.Data = static_cast<real32_T>
      (Zustandsregler_P.Saturation_LowerSat);
  } else {
    /* BusAssignment: '<Root>/Bus Assignment' incorporates:
     *  DataTypeConversion: '<Root>/Data Type Conversion'
     */
    rtb_BusAssignment.Data = static_cast<real32_T>
      (Zustandsregler_B.rtb_Add3_idx_0);
  }

  /* End of Saturate: '<S7>/Saturation' */

  /* Outputs for Atomic SubSystem: '<Root>/Publish' */
  /* MATLABSystem: '<S2>/SinkBlock' */
  Pub_Zustandsregler_158.publish(&rtb_BusAssignment);

  /* End of Outputs for SubSystem: '<Root>/Publish' */
  if (rtmIsMajorTimeStep(Zustandsregler_M)) {
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
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Zustandsregler_derivatives(void)
{
  XDot_Zustandsregler_T *_rtXdot;
  _rtXdot = ((XDot_Zustandsregler_T *) Zustandsregler_M->derivs);

  /* Derivatives for Integrator: '<S7>/Integrator' */
  _rtXdot->Integrator_CSTATE[0] = Zustandsregler_B.x[0];
  _rtXdot->Integrator_CSTATE[1] = Zustandsregler_B.x[1];
}

/* Model initialize function */
void Zustandsregler_initialize(void)
{
  /* Registration code */
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
  rtsiSetSolverData(&Zustandsregler_M->solverInfo, static_cast<void *>
                    (&Zustandsregler_M->intgData));
  rtsiSetSolverName(&Zustandsregler_M->solverInfo,"ode3");
  rtmSetTPtr(Zustandsregler_M, &Zustandsregler_M->Timing.tArray[0]);
  Zustandsregler_M->Timing.stepSize0 = 0.001;

  /* block I/O */
  (void) memset((static_cast<void *>(&Zustandsregler_B)), 0,
                sizeof(B_Zustandsregler_T));

  /* states (continuous) */
  {
    (void) memset(static_cast<void *>(&Zustandsregler_X), 0,
                  sizeof(X_Zustandsregler_T));
  }

  /* states (dwork) */
  (void) memset(static_cast<void *>(&Zustandsregler_DW), 0,
                sizeof(DW_Zustandsregler_T));

  {
    char_T tmp[12];
    char_T tmp_0[21];
    char_T tmp_1[8];
    char_T tmp_2[9];
    int32_T i;
    static const char_T tmp_3[8] = { '/', 'A', 'b', 's', 't', 'a', 'n', 'd' };

    static const char_T tmp_4[7] = { '/', 'W', 'i', 'n', 'k', 'e', 'l' };

    static const char_T tmp_5[7] = { '/', 'K', 'a', 'm', 'e', 'r', 'a' };

    static const char_T tmp_6[20] = { '/', 'G', 'i', 'e', 'r', 'g', 'e', 's',
      'c', 'h', 'w', 'i', 'n', 'd', 'i', 'g', 'k', 'e', 'i', 't' };

    static const char_T tmp_7[11] = { '/', 'L', 'e', 'n', 'k', 'w', 'i', 'n',
      'k', 'e', 'l' };

    /* Start for Atomic SubSystem: '<Root>/Subscribe2' */
    /* Start for MATLABSystem: '<S5>/SourceBlock' */
    Zustandsregler_DW.obj_b.matlabCodegenIsDeleted = false;
    Zustandsregler_DW.objisempty_k = true;
    Zustandsregler_DW.obj_b.isInitialized = 1;
    for (i = 0; i < 8; i++) {
      tmp_2[i] = tmp_3[i];
    }

    tmp_2[8] = '\x00';
    Sub_Zustandsregler_172.createSubscriber(tmp_2, 1);
    Zustandsregler_DW.obj_b.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S5>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe2' */

    /* Start for Atomic SubSystem: '<Root>/Subscribe3' */
    /* Start for MATLABSystem: '<S6>/SourceBlock' */
    Zustandsregler_DW.obj_a.matlabCodegenIsDeleted = false;
    Zustandsregler_DW.objisempty = true;
    Zustandsregler_DW.obj_a.isInitialized = 1;
    for (i = 0; i < 7; i++) {
      tmp_1[i] = tmp_4[i];
    }

    tmp_1[7] = '\x00';
    Sub_Zustandsregler_174.createSubscriber(tmp_1, 1);
    Zustandsregler_DW.obj_a.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S6>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe3' */

    /* Start for Atomic SubSystem: '<Root>/Subscribe' */
    /* Start for MATLABSystem: '<S3>/SourceBlock' */
    Zustandsregler_DW.obj_n.matlabCodegenIsDeleted = false;
    Zustandsregler_DW.objisempty_j = true;
    Zustandsregler_DW.obj_n.isInitialized = 1;
    for (i = 0; i < 7; i++) {
      tmp_1[i] = tmp_5[i];
    }

    tmp_1[7] = '\x00';
    Sub_Zustandsregler_126.createSubscriber(tmp_1, 1);
    Zustandsregler_DW.obj_n.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S3>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe' */

    /* Start for Atomic SubSystem: '<Root>/Subscribe1' */
    /* Start for MATLABSystem: '<S4>/SourceBlock' */
    Zustandsregler_DW.obj_k.matlabCodegenIsDeleted = false;
    Zustandsregler_DW.objisempty_d = true;
    Zustandsregler_DW.obj_k.isInitialized = 1;
    for (i = 0; i < 20; i++) {
      tmp_0[i] = tmp_6[i];
    }

    tmp_0[20] = '\x00';
    Sub_Zustandsregler_170.createSubscriber(tmp_0, 1);
    Zustandsregler_DW.obj_k.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S4>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe1' */

    /* Start for Atomic SubSystem: '<Root>/Publish' */
    /* Start for MATLABSystem: '<S2>/SinkBlock' */
    Zustandsregler_DW.obj.matlabCodegenIsDeleted = false;
    Zustandsregler_DW.objisempty_o = true;
    Zustandsregler_DW.obj.isInitialized = 1;
    for (i = 0; i < 11; i++) {
      tmp[i] = tmp_7[i];
    }

    tmp[11] = '\x00';
    Pub_Zustandsregler_158.createPublisher(tmp, 1);
    Zustandsregler_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S2>/SinkBlock' */
    /* End of Start for SubSystem: '<Root>/Publish' */
  }

  /* InitializeConditions for Integrator: '<S7>/Integrator' */
  Zustandsregler_X.Integrator_CSTATE[0] = Zustandsregler_P.Integrator_IC;
  Zustandsregler_X.Integrator_CSTATE[1] = Zustandsregler_P.Integrator_IC;

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe2' */
  /* SystemInitialize for Enabled SubSystem: '<S5>/Enabled Subsystem' */
  Zustandsr_EnabledSubsystem_Init(&Zustandsregler_B.EnabledSubsystem_m,
    &Zustandsregler_P.EnabledSubsystem_m);

  /* End of SystemInitialize for SubSystem: '<S5>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe2' */

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe3' */
  /* SystemInitialize for Enabled SubSystem: '<S6>/Enabled Subsystem' */
  Zustandsr_EnabledSubsystem_Init(&Zustandsregler_B.EnabledSubsystem_a,
    &Zustandsregler_P.EnabledSubsystem_a);

  /* End of SystemInitialize for SubSystem: '<S6>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe3' */

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe' */
  /* SystemInitialize for Enabled SubSystem: '<S3>/Enabled Subsystem' */
  Zustandsr_EnabledSubsystem_Init(&Zustandsregler_B.EnabledSubsystem,
    &Zustandsregler_P.EnabledSubsystem);

  /* End of SystemInitialize for SubSystem: '<S3>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe' */

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe1' */
  /* SystemInitialize for Enabled SubSystem: '<S4>/Enabled Subsystem' */
  Zustandsr_EnabledSubsystem_Init(&Zustandsregler_B.EnabledSubsystem_p,
    &Zustandsregler_P.EnabledSubsystem_p);

  /* End of SystemInitialize for SubSystem: '<S4>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe1' */
}

/* Model terminate function */
void Zustandsregler_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Subscribe2' */
  /* Terminate for MATLABSystem: '<S5>/SourceBlock' */
  matlabCodegenHandle_matlabCod_i(&Zustandsregler_DW.obj_b);

  /* End of Terminate for SubSystem: '<Root>/Subscribe2' */

  /* Terminate for Atomic SubSystem: '<Root>/Subscribe3' */
  /* Terminate for MATLABSystem: '<S6>/SourceBlock' */
  matlabCodegenHandle_matlabCod_i(&Zustandsregler_DW.obj_a);

  /* End of Terminate for SubSystem: '<Root>/Subscribe3' */

  /* Terminate for Atomic SubSystem: '<Root>/Subscribe' */
  /* Terminate for MATLABSystem: '<S3>/SourceBlock' */
  matlabCodegenHandle_matlabCod_i(&Zustandsregler_DW.obj_n);

  /* End of Terminate for SubSystem: '<Root>/Subscribe' */

  /* Terminate for Atomic SubSystem: '<Root>/Subscribe1' */
  /* Terminate for MATLABSystem: '<S4>/SourceBlock' */
  matlabCodegenHandle_matlabCod_i(&Zustandsregler_DW.obj_k);

  /* End of Terminate for SubSystem: '<Root>/Subscribe1' */

  /* Terminate for Atomic SubSystem: '<Root>/Publish' */
  /* Terminate for MATLABSystem: '<S2>/SinkBlock' */
  matlabCodegenHandle_matlabCodeg(&Zustandsregler_DW.obj);

  /* End of Terminate for SubSystem: '<Root>/Publish' */
}
