/*
 * Stanley_Querregler.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Stanley_Querregler".
 *
 * Model version              : 1.22
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Fri Feb  7 23:34:38 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Stanley_Querregler.h"
#include "Stanley_Querregler_private.h"

/* Block signals (default storage) */
B_Stanley_Querregler_T Stanley_Querregler_B;

/* Block states (default storage) */
DW_Stanley_Querregler_T Stanley_Querregler_DW;

/* Real-time model */
RT_MODEL_Stanley_Querregler_T Stanley_Querregler_M_ =
  RT_MODEL_Stanley_Querregler_T();
RT_MODEL_Stanley_Querregler_T *const Stanley_Querregler_M =
  &Stanley_Querregler_M_;

/* Forward declaration for local functions */
static void Stanle_angleUtilities_wrapTo2Pi(real_T *theta);
static void matlabCodegenHandle_matlabCod_a(ros_slros_internal_block_Subs_T *obj);
static void matlabCodegenHandle_matlabCodeg(ros_slros_internal_block_Publ_T *obj);

/*
 * System initialize for enable system:
 *    '<S4>/Enabled Subsystem'
 *    '<S5>/Enabled Subsystem'
 *    '<S6>/Enabled Subsystem'
 */
void Stanley_Q_EnabledSubsystem_Init(B_EnabledSubsystem_Stanley_Qu_T *localB,
  P_EnabledSubsystem_Stanley_Qu_T *localP)
{
  /* SystemInitialize for Outport: '<S9>/Out1' */
  localB->In1 = localP->Out1_Y0;
}

/*
 * Output and update for enable system:
 *    '<S4>/Enabled Subsystem'
 *    '<S5>/Enabled Subsystem'
 *    '<S6>/Enabled Subsystem'
 */
void Stanley_Querre_EnabledSubsystem(boolean_T rtu_Enable, const
  SL_Bus_Stanley_Querregler_std_msgs_Float32 *rtu_In1,
  B_EnabledSubsystem_Stanley_Qu_T *localB)
{
  /* Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S9>/Enable'
   */
  if (rtu_Enable) {
    /* Inport: '<S9>/In1' */
    localB->In1 = *rtu_In1;
  }

  /* End of Outputs for SubSystem: '<S4>/Enabled Subsystem' */
}

/* Function for MATLAB Function: '<S12>/Kinematic' */
static void Stanle_angleUtilities_wrapTo2Pi(real_T *theta)
{
  boolean_T positiveInput;
  real_T x;
  boolean_T rEQ0;
  real_T q;
  positiveInput = (*theta > 0.0);
  x = *theta;
  if (rtIsNaN(*theta) || rtIsInf(*theta)) {
    *theta = (rtNaN);
  } else if (*theta == 0.0) {
    *theta = 0.0;
  } else {
    *theta = fmod(*theta, 6.2831853071795862);
    rEQ0 = (*theta == 0.0);
    if (!rEQ0) {
      q = fabs(x / 6.2831853071795862);
      rEQ0 = (fabs(q - floor(q + 0.5)) <= 2.2204460492503131E-16 * q);
    }

    if (rEQ0) {
      *theta = 0.0;
    } else {
      if (x < 0.0) {
        *theta += 6.2831853071795862;
      }
    }
  }

  positiveInput = ((*theta == 0.0) && positiveInput);
  *theta += 6.2831853071795862 * static_cast<real_T>(positiveInput);
}

static void matlabCodegenHandle_matlabCod_a(ros_slros_internal_block_Subs_T *obj)
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
void Stanley_Querregler_step(void)
{
  SL_Bus_Stanley_Querregler_std_msgs_Bool b_varargout_2;
  boolean_T b_varargout_1;
  SL_Bus_Stanley_Querregler_std_msgs_Float32 b_varargout_2_0;
  SL_Bus_Stanley_Querregler_std_msgs_Float32 rtb_BusAssignment;
  real_T rtb_ms;
  real32_T rtb_Switch;
  real_T d_idx_0;
  real_T d_idx_1;
  real32_T u0;

  /* Outputs for Atomic SubSystem: '<Root>/Subscribe1' */
  /* MATLABSystem: '<S3>/SourceBlock' incorporates:
   *  Inport: '<S8>/In1'
   */
  b_varargout_1 = Sub_Stanley_Querregler_75.getLatestMessage(&b_varargout_2);

  /* Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S8>/Enable'
   */
  if (b_varargout_1) {
    Stanley_Querregler_B.In1 = b_varargout_2;
  }

  /* End of MATLABSystem: '<S3>/SourceBlock' */
  /* End of Outputs for SubSystem: '<S3>/Enabled Subsystem' */
  /* End of Outputs for SubSystem: '<Root>/Subscribe1' */

  /* Outputs for Atomic SubSystem: '<Root>/Subscribe3' */
  /* MATLABSystem: '<S5>/SourceBlock' */
  b_varargout_1 = Sub_Stanley_Querregler_66.getLatestMessage(&b_varargout_2_0);

  /* Outputs for Enabled SubSystem: '<S5>/Enabled Subsystem' */
  Stanley_Querre_EnabledSubsystem(b_varargout_1, &b_varargout_2_0,
    &Stanley_Querregler_B.EnabledSubsystem_p);

  /* End of Outputs for SubSystem: '<S5>/Enabled Subsystem' */
  /* End of Outputs for SubSystem: '<Root>/Subscribe3' */

  /* Outputs for Atomic SubSystem: '<Root>/Subscribe2' */
  /* MATLABSystem: '<S4>/SourceBlock' */
  b_varargout_1 = Sub_Stanley_Querregler_65.getLatestMessage(&b_varargout_2_0);

  /* Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' */
  Stanley_Querre_EnabledSubsystem(b_varargout_1, &b_varargout_2_0,
    &Stanley_Querregler_B.EnabledSubsystem_g);

  /* End of Outputs for SubSystem: '<S4>/Enabled Subsystem' */
  /* End of Outputs for SubSystem: '<Root>/Subscribe2' */

  /* Outputs for Enabled SubSystem: '<Root>/Subsystem' incorporates:
   *  EnablePort: '<S7>/Enable'
   */
  if (Stanley_Querregler_B.In1.Data) {
    /* Gain: '<S7>/Gain1' */
    rtb_Switch = Stanley_Querregler_P.Gain1_Gain *
      Stanley_Querregler_B.EnabledSubsystem_g.In1.Data;

    /* Switch: '<S7>/Switch' incorporates:
     *  Constant: '<S7>/Rückwärts'
     *  Constant: '<S7>/Vorwärts'
     */
    if (Stanley_Querregler_B.EnabledSubsystem_p.In1.Data >=
        Stanley_Querregler_P.Switch_Threshold) {
      rtb_ms = Stanley_Querregler_P.Vorwrts_Value;
    } else {
      rtb_ms = Stanley_Querregler_P.Rckwrts_Value;
    }

    /* End of Switch: '<S7>/Switch' */

    /* MATLAB Function: '<S12>/Kinematic' incorporates:
     *  Constant: '<S7>/ '
     *  Constant: '<S7>/  '
     *  Constant: '<S7>/[x, y, theta]'
     *  Product: '<S7>/Matrix Multiply'
     *  Sum: '<S7>/Add'
     */
    Stanley_Querregler_B.refPose[0] = Stanley_Querregler_P._Value_m[0] *
      rtb_Switch + Stanley_Querregler_P._Value[0];
    Stanley_Querregler_B.currPose[0] = Stanley_Querregler_P.xytheta_Value[0];
    Stanley_Querregler_B.refPose[1] = Stanley_Querregler_P._Value_m[1] *
      rtb_Switch + Stanley_Querregler_P._Value[1];
    Stanley_Querregler_B.currPose[1] = Stanley_Querregler_P.xytheta_Value[1];
    Stanley_Querregler_B.refPose[2] = (Stanley_Querregler_P._Value_m[2] *
      rtb_Switch + Stanley_Querregler_P._Value[2]) * 0.017453292519943295;
    Stanle_angleUtilities_wrapTo2Pi(&Stanley_Querregler_B.refPose[2]);
    Stanley_Querregler_B.currPose[2] = 0.017453292519943295 *
      Stanley_Querregler_P.xytheta_Value[2];
    Stanle_angleUtilities_wrapTo2Pi(&Stanley_Querregler_B.currPose[2]);
    if (rtb_ms == 1.0) {
      d_idx_0 = (Stanley_Querregler_P.Kinematic_Wheelbase * cos
                 (Stanley_Querregler_B.currPose[2]) +
                 Stanley_Querregler_P.xytheta_Value[0]) -
        Stanley_Querregler_B.refPose[0];
      d_idx_1 = (Stanley_Querregler_P.Kinematic_Wheelbase * sin
                 (Stanley_Querregler_B.currPose[2]) +
                 Stanley_Querregler_P.xytheta_Value[1]) -
        Stanley_Querregler_B.refPose[1];
    } else {
      d_idx_0 = Stanley_Querregler_B.currPose[0] - Stanley_Querregler_B.refPose
        [0];
      d_idx_1 = Stanley_Querregler_B.currPose[1] - Stanley_Querregler_B.refPose
        [1];
    }

    Stanley_Querregler_B.b = (Stanley_Querregler_B.currPose[2] -
      Stanley_Querregler_B.refPose[2]) + 3.1415926535897931;
    Stanle_angleUtilities_wrapTo2Pi(&Stanley_Querregler_B.b);
    if (rtb_ms == 1.0) {
      /* Switch: '<S7>/Switch1' incorporates:
       *  Gain: '<S7>/Gain'
       */
      if (Stanley_Querregler_B.EnabledSubsystem_p.In1.Data >
          Stanley_Querregler_P.Switch1_Threshold) {
        rtb_Switch = Stanley_Querregler_B.EnabledSubsystem_p.In1.Data;
      } else {
        rtb_Switch = Stanley_Querregler_P.Gain_Gain *
          Stanley_Querregler_B.EnabledSubsystem_p.In1.Data;
      }

      rtb_Switch = -(static_cast<real32_T>(atan(static_cast<real_T>((
        static_cast<real32_T>((-(d_idx_0 * sin(Stanley_Querregler_B.refPose[2])
        - d_idx_1 * cos(Stanley_Querregler_B.refPose[2])) *
        Stanley_Querregler_P.LateralControllerStanley_Positi)) / (rtb_Switch +
        1.0F))))) + static_cast<real32_T>((Stanley_Querregler_B.b -
        3.1415926535897931)));
    } else {
      if (rtb_ms == 1.0) {
        rtb_ms = Stanley_Querregler_P.LateralControllerStanley_Positi;
      } else {
        rtb_ms = Stanley_Querregler_P.LateralControllerStanley_Posi_p;
      }

      /* Switch: '<S7>/Switch1' incorporates:
       *  Gain: '<S7>/Gain'
       */
      if (Stanley_Querregler_B.EnabledSubsystem_p.In1.Data >
          Stanley_Querregler_P.Switch1_Threshold) {
        rtb_Switch = Stanley_Querregler_B.EnabledSubsystem_p.In1.Data;
      } else {
        rtb_Switch = Stanley_Querregler_P.Gain_Gain *
          Stanley_Querregler_B.EnabledSubsystem_p.In1.Data;
      }

      rtb_Switch = static_cast<real32_T>(atan(static_cast<real_T>
        ((static_cast<real32_T>((-(d_idx_0 * sin(Stanley_Querregler_B.refPose[2])
        - d_idx_1 * cos(Stanley_Querregler_B.refPose[2])) * rtb_ms)) /
          (rtb_Switch + -1.0F))))) + static_cast<real32_T>
        ((Stanley_Querregler_B.b - 3.1415926535897931));
    }

    rtb_Switch *= 57.2957802F;
    u0 = static_cast<real32_T>(fabs(static_cast<real_T>(rtb_Switch)));
    if (rtb_Switch < 0.0F) {
      rtb_Switch = -1.0F;
    } else if (rtb_Switch > 0.0F) {
      rtb_Switch = 1.0F;
    } else if (rtb_Switch == 0.0F) {
      rtb_Switch = 0.0F;
    } else {
      rtb_Switch = (rtNaNF);
    }

    if ((!(u0 < static_cast<real32_T>
           (Stanley_Querregler_P.Kinematic_MaxSteeringAngle))) && (!rtIsNaNF(
          static_cast<real32_T>(Stanley_Querregler_P.Kinematic_MaxSteeringAngle))))
    {
      u0 = static_cast<real32_T>(Stanley_Querregler_P.Kinematic_MaxSteeringAngle);
    }

    rtb_Switch *= u0;

    /* End of MATLAB Function: '<S12>/Kinematic' */

    /* Saturate: '<S7>/Sättigung' */
    if (rtb_Switch > Stanley_Querregler_P.Sttigung_UpperSat) {
      rtb_Switch = Stanley_Querregler_P.Sttigung_UpperSat;
    } else {
      if (rtb_Switch < Stanley_Querregler_P.Sttigung_LowerSat) {
        rtb_Switch = Stanley_Querregler_P.Sttigung_LowerSat;
      }
    }

    /* End of Saturate: '<S7>/Sättigung' */

    /* Gain: '<S7>/Bogenmaß' */
    Stanley_Querregler_B.Bogenma = Stanley_Querregler_P.Bogenma_Gain *
      rtb_Switch;
  }

  /* End of Outputs for SubSystem: '<Root>/Subsystem' */

  /* Outputs for Atomic SubSystem: '<Root>/Subscribe4' */
  /* MATLABSystem: '<S6>/SourceBlock' */
  b_varargout_1 = Sub_Stanley_Querregler_78.getLatestMessage(&b_varargout_2_0);

  /* Outputs for Enabled SubSystem: '<S6>/Enabled Subsystem' */
  Stanley_Querre_EnabledSubsystem(b_varargout_1, &b_varargout_2_0,
    &Stanley_Querregler_B.EnabledSubsystem_i);

  /* End of Outputs for SubSystem: '<S6>/Enabled Subsystem' */
  /* End of Outputs for SubSystem: '<Root>/Subscribe4' */

  /* Switch: '<Root>/Switch' */
  if (Stanley_Querregler_B.In1.Data) {
    /* BusAssignment: '<Root>/Bus Assignment' */
    rtb_BusAssignment.Data = Stanley_Querregler_B.Bogenma;
  } else {
    /* BusAssignment: '<Root>/Bus Assignment' */
    rtb_BusAssignment.Data = Stanley_Querregler_B.EnabledSubsystem_i.In1.Data;
  }

  /* End of Switch: '<Root>/Switch' */

  /* Outputs for Atomic SubSystem: '<Root>/Publish1' */
  /* MATLABSystem: '<S2>/SinkBlock' */
  Pub_Stanley_Querregler_72.publish(&rtb_BusAssignment);

  /* End of Outputs for SubSystem: '<Root>/Publish1' */
}

/* Model initialize function */
void Stanley_Querregler_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* block I/O */
  (void) memset((static_cast<void *>(&Stanley_Querregler_B)), 0,
                sizeof(B_Stanley_Querregler_T));

  /* states (dwork) */
  (void) memset(static_cast<void *>(&Stanley_Querregler_DW), 0,
                sizeof(DW_Stanley_Querregler_T));

  {
    char_T tmp[16];
    char_T tmp_0[12];
    char_T tmp_1[14];
    int32_T i;
    static const char_T tmp_2[25] = { '/', 't', 'r', 'j', '_', 'e', 'n', 'a',
      'b', 'l', 'e', 'L', 'a', 't', 'e', 'r', 'a', 'l', 'C', 'o', 'n', 't', 'r',
      'o', 'l' };

    static const char_T tmp_3[13] = { '/', 'c', 't', 'l', '_', 'v', 'e', 'l',
      'o', 'c', 'i', 't', 'y' };

    static const char_T tmp_4[11] = { '/', 't', 'r', 'j', '_', 'd', 'e', 'l',
      't', 'a', 'Y' };

    static const char_T tmp_5[18] = { '/', 't', 'r', 'j', '_', 's', 't', 'e',
      'e', 'r', 'i', 'n', 'g', 'A', 'n', 'g', 'l', 'e' };

    static const char_T tmp_6[15] = { '/', 'c', 't', 'l', '_', 's', 'e', 'r',
      'v', 'o', 'A', 'n', 'g', 'l', 'e' };

    /* Start for Atomic SubSystem: '<Root>/Subscribe1' */
    /* Start for MATLABSystem: '<S3>/SourceBlock' */
    Stanley_Querregler_DW.obj_l.matlabCodegenIsDeleted = false;
    Stanley_Querregler_DW.objisempty_n = true;
    Stanley_Querregler_DW.obj_l.isInitialized = 1;
    for (i = 0; i < 25; i++) {
      Stanley_Querregler_B.cv[i] = tmp_2[i];
    }

    Stanley_Querregler_B.cv[25] = '\x00';
    Sub_Stanley_Querregler_75.createSubscriber(Stanley_Querregler_B.cv, 1);
    Stanley_Querregler_DW.obj_l.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S3>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe1' */

    /* Start for Atomic SubSystem: '<Root>/Subscribe3' */
    /* Start for MATLABSystem: '<S5>/SourceBlock' */
    Stanley_Querregler_DW.obj_o.matlabCodegenIsDeleted = false;
    Stanley_Querregler_DW.objisempty_h = true;
    Stanley_Querregler_DW.obj_o.isInitialized = 1;
    for (i = 0; i < 13; i++) {
      tmp_1[i] = tmp_3[i];
    }

    tmp_1[13] = '\x00';
    Sub_Stanley_Querregler_66.createSubscriber(tmp_1, 1);
    Stanley_Querregler_DW.obj_o.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S5>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe3' */

    /* Start for Atomic SubSystem: '<Root>/Subscribe2' */
    /* Start for MATLABSystem: '<S4>/SourceBlock' */
    Stanley_Querregler_DW.obj_e.matlabCodegenIsDeleted = false;
    Stanley_Querregler_DW.objisempty_d = true;
    Stanley_Querregler_DW.obj_e.isInitialized = 1;
    for (i = 0; i < 11; i++) {
      tmp_0[i] = tmp_4[i];
    }

    tmp_0[11] = '\x00';
    Sub_Stanley_Querregler_65.createSubscriber(tmp_0, 1);
    Stanley_Querregler_DW.obj_e.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S4>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe2' */

    /* Start for Atomic SubSystem: '<Root>/Subscribe4' */
    /* Start for MATLABSystem: '<S6>/SourceBlock' */
    Stanley_Querregler_DW.obj_c.matlabCodegenIsDeleted = false;
    Stanley_Querregler_DW.objisempty = true;
    Stanley_Querregler_DW.obj_c.isInitialized = 1;
    for (i = 0; i < 18; i++) {
      Stanley_Querregler_B.cv1[i] = tmp_5[i];
    }

    Stanley_Querregler_B.cv1[18] = '\x00';
    Sub_Stanley_Querregler_78.createSubscriber(Stanley_Querregler_B.cv1, 1);
    Stanley_Querregler_DW.obj_c.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S6>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe4' */

    /* Start for Atomic SubSystem: '<Root>/Publish1' */
    /* Start for MATLABSystem: '<S2>/SinkBlock' */
    Stanley_Querregler_DW.obj.matlabCodegenIsDeleted = false;
    Stanley_Querregler_DW.objisempty_p = true;
    Stanley_Querregler_DW.obj.isInitialized = 1;
    for (i = 0; i < 15; i++) {
      tmp[i] = tmp_6[i];
    }

    tmp[15] = '\x00';
    Pub_Stanley_Querregler_72.createPublisher(tmp, 1);
    Stanley_Querregler_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S2>/SinkBlock' */
    /* End of Start for SubSystem: '<Root>/Publish1' */
  }

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe1' */
  /* SystemInitialize for Enabled SubSystem: '<S3>/Enabled Subsystem' */
  /* SystemInitialize for Outport: '<S8>/Out1' */
  Stanley_Querregler_B.In1 = Stanley_Querregler_P.Out1_Y0;

  /* End of SystemInitialize for SubSystem: '<S3>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe1' */

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe3' */
  /* SystemInitialize for Enabled SubSystem: '<S5>/Enabled Subsystem' */
  Stanley_Q_EnabledSubsystem_Init(&Stanley_Querregler_B.EnabledSubsystem_p,
    &Stanley_Querregler_P.EnabledSubsystem_p);

  /* End of SystemInitialize for SubSystem: '<S5>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe3' */

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe2' */
  /* SystemInitialize for Enabled SubSystem: '<S4>/Enabled Subsystem' */
  Stanley_Q_EnabledSubsystem_Init(&Stanley_Querregler_B.EnabledSubsystem_g,
    &Stanley_Querregler_P.EnabledSubsystem_g);

  /* End of SystemInitialize for SubSystem: '<S4>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe2' */

  /* SystemInitialize for Enabled SubSystem: '<Root>/Subsystem' */
  /* SystemInitialize for Outport: '<S7>/Lenkwinkel' */
  Stanley_Querregler_B.Bogenma = Stanley_Querregler_P.Lenkwinkel_Y0;

  /* End of SystemInitialize for SubSystem: '<Root>/Subsystem' */

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe4' */
  /* SystemInitialize for Enabled SubSystem: '<S6>/Enabled Subsystem' */
  Stanley_Q_EnabledSubsystem_Init(&Stanley_Querregler_B.EnabledSubsystem_i,
    &Stanley_Querregler_P.EnabledSubsystem_i);

  /* End of SystemInitialize for SubSystem: '<S6>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe4' */
}

/* Model terminate function */
void Stanley_Querregler_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Subscribe1' */
  /* Terminate for MATLABSystem: '<S3>/SourceBlock' */
  matlabCodegenHandle_matlabCod_a(&Stanley_Querregler_DW.obj_l);

  /* End of Terminate for SubSystem: '<Root>/Subscribe1' */

  /* Terminate for Atomic SubSystem: '<Root>/Subscribe3' */
  /* Terminate for MATLABSystem: '<S5>/SourceBlock' */
  matlabCodegenHandle_matlabCod_a(&Stanley_Querregler_DW.obj_o);

  /* End of Terminate for SubSystem: '<Root>/Subscribe3' */

  /* Terminate for Atomic SubSystem: '<Root>/Subscribe2' */
  /* Terminate for MATLABSystem: '<S4>/SourceBlock' */
  matlabCodegenHandle_matlabCod_a(&Stanley_Querregler_DW.obj_e);

  /* End of Terminate for SubSystem: '<Root>/Subscribe2' */

  /* Terminate for Atomic SubSystem: '<Root>/Subscribe4' */
  /* Terminate for MATLABSystem: '<S6>/SourceBlock' */
  matlabCodegenHandle_matlabCod_a(&Stanley_Querregler_DW.obj_c);

  /* End of Terminate for SubSystem: '<Root>/Subscribe4' */

  /* Terminate for Atomic SubSystem: '<Root>/Publish1' */
  /* Terminate for MATLABSystem: '<S2>/SinkBlock' */
  matlabCodegenHandle_matlabCodeg(&Stanley_Querregler_DW.obj);

  /* End of Terminate for SubSystem: '<Root>/Publish1' */
}
