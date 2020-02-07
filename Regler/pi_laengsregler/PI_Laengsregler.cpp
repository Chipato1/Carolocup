/*
 * PI_Laengsregler.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "PI_Laengsregler".
 *
 * Model version              : 1.36
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Fri Feb  7 18:15:48 2020
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

/* Block states (default storage) */
DW_PI_Laengsregler_T PI_Laengsregler_DW;

/* Real-time model */
RT_MODEL_PI_Laengsregler_T PI_Laengsregler_M_ = RT_MODEL_PI_Laengsregler_T();
RT_MODEL_PI_Laengsregler_T *const PI_Laengsregler_M = &PI_Laengsregler_M_;

/* Forward declaration for local functions */
static void matlabCodegenHandle_matlabCod_l(ros_slros_internal_block_Subs_T *obj);
static void matlabCodegenHandle_matlabCodeg(ros_slros_internal_block_Publ_T *obj);
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
  SL_Bus_PI_Laengsregler_std_msgs_Float32 b_varargout_2;
  boolean_T b_varargout_1;
  SL_Bus_PI_Laengsregler_std_msgs_Int16 rtb_BusAssignment;
  real_T tmp;

  /* Outputs for Atomic SubSystem: '<Root>/Subscribe' */
  /* MATLABSystem: '<S3>/SourceBlock' incorporates:
   *  Inport: '<S4>/In1'
   */
  b_varargout_1 = Sub_PI_Laengsregler_80.getLatestMessage(&b_varargout_2);

  /* Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S4>/Enable'
   */
  if (b_varargout_1) {
    PI_Laengsregler_B.In1 = b_varargout_2;
  }

  /* End of MATLABSystem: '<S3>/SourceBlock' */
  /* End of Outputs for SubSystem: '<S3>/Enabled Subsystem' */
  /* End of Outputs for SubSystem: '<Root>/Subscribe' */

  /* Saturate: '<Root>/Saturation' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion1'
   */
  if (PI_Laengsregler_B.In1.Data > PI_Laengsregler_P.Saturation_UpperSat) {
    tmp = PI_Laengsregler_P.Saturation_UpperSat;
  } else if (PI_Laengsregler_B.In1.Data < PI_Laengsregler_P.Saturation_LowerSat)
  {
    tmp = PI_Laengsregler_P.Saturation_LowerSat;
  } else {
    tmp = PI_Laengsregler_B.In1.Data;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* DataTypeConversion: '<Root>/Data Type Conversion' incorporates:
   *  Gain: '<Root>/Getriebe'
   *  Gain: '<Root>/Radumfang'
   */
  tmp = floor(PI_Laengsregler_P.Radumfang_Gain * tmp *
              PI_Laengsregler_P.Getriebe_Gain);
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
  /* MATLABSystem: '<S2>/SinkBlock' */
  Pub_PI_Laengsregler_79.publish(&rtb_BusAssignment);

  /* End of Outputs for SubSystem: '<Root>/Publish' */
}

/* Model initialize function */
void PI_Laengsregler_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* block I/O */
  (void) memset((static_cast<void *>(&PI_Laengsregler_B)), 0,
                sizeof(B_PI_Laengsregler_T));

  /* states (dwork) */
  (void) memset(static_cast<void *>(&PI_Laengsregler_DW), 0,
                sizeof(DW_PI_Laengsregler_T));

  {
    char_T tmp[14];
    char_T tmp_0[17];
    int32_T i;
    static const char_T tmp_1[16] = { '/', 't', 'r', 'j', '_', 't', 'a', 'r',
      'g', 'e', 't', 'S', 'p', 'e', 'e', 'd' };

    static const char_T tmp_2[13] = { '/', 'c', 't', 'l', '_', 'm', 'o', 't',
      'o', 'r', 'R', 'p', 'm' };

    /* Start for Atomic SubSystem: '<Root>/Subscribe' */
    /* Start for MATLABSystem: '<S3>/SourceBlock' */
    PI_Laengsregler_DW.obj_j.matlabCodegenIsDeleted = false;
    PI_Laengsregler_DW.objisempty = true;
    PI_Laengsregler_DW.obj_j.isInitialized = 1;
    for (i = 0; i < 16; i++) {
      tmp_0[i] = tmp_1[i];
    }

    tmp_0[16] = '\x00';
    Sub_PI_Laengsregler_80.createSubscriber(tmp_0, 1);
    PI_Laengsregler_DW.obj_j.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S3>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe' */

    /* Start for Atomic SubSystem: '<Root>/Publish' */
    /* Start for MATLABSystem: '<S2>/SinkBlock' */
    PI_Laengsregler_DW.obj.matlabCodegenIsDeleted = false;
    PI_Laengsregler_DW.objisempty_f = true;
    PI_Laengsregler_DW.obj.isInitialized = 1;
    for (i = 0; i < 13; i++) {
      tmp[i] = tmp_2[i];
    }

    tmp[13] = '\x00';
    Pub_PI_Laengsregler_79.createPublisher(tmp, 1);
    PI_Laengsregler_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S2>/SinkBlock' */
    /* End of Start for SubSystem: '<Root>/Publish' */
  }

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe' */
  /* SystemInitialize for Enabled SubSystem: '<S3>/Enabled Subsystem' */
  /* SystemInitialize for Outport: '<S4>/Out1' */
  PI_Laengsregler_B.In1 = PI_Laengsregler_P.Out1_Y0;

  /* End of SystemInitialize for SubSystem: '<S3>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe' */
}

/* Model terminate function */
void PI_Laengsregler_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Subscribe' */
  /* Terminate for MATLABSystem: '<S3>/SourceBlock' */
  matlabCodegenHandle_matlabCod_l(&PI_Laengsregler_DW.obj_j);

  /* End of Terminate for SubSystem: '<Root>/Subscribe' */

  /* Terminate for Atomic SubSystem: '<Root>/Publish' */
  /* Terminate for MATLABSystem: '<S2>/SinkBlock' */
  matlabCodegenHandle_matlabCodeg(&PI_Laengsregler_DW.obj);

  /* End of Terminate for SubSystem: '<Root>/Publish' */
}
