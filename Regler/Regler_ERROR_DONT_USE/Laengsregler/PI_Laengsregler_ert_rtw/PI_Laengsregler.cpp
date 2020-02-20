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
 * C++ source code generated on : Wed Feb  5 15:07:18 2020
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
  SL_Bus_PI_Laengsregler_std_msgs_Int16 rtb_BusAssignment2;
  real32_T tmp;

  /* Outputs for Atomic SubSystem: '<Root>/Subscribe4' */
  /* MATLABSystem: '<S3>/SourceBlock' incorporates:
   *  Inport: '<S5>/In1'
   */
  b_varargout_1 = Sub_PI_Laengsregler_305.getLatestMessage(&b_varargout_2);

  /* Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S5>/Enable'
   */
  if (b_varargout_1) {
    PI_Laengsregler_B.In1 = b_varargout_2;
  }

  /* End of MATLABSystem: '<S3>/SourceBlock' */
  /* End of Outputs for SubSystem: '<S3>/Enabled Subsystem' */
  /* End of Outputs for SubSystem: '<Root>/Subscribe4' */

  /* DataTypeConversion: '<Root>/Data Type Conversion4' incorporates:
   *  Gain: '<S4>/Getriebe'
   *  Gain: '<S4>/Radumfang'
   */
  tmp = static_cast<real32_T>(floor(static_cast<real_T>
    ((PI_Laengsregler_P.Radumfang_Gain * PI_Laengsregler_B.In1.Data *
      PI_Laengsregler_P.Getriebe_Gain))));
  if (rtIsNaNF(tmp) || rtIsInfF(tmp)) {
    tmp = 0.0F;
  } else {
    tmp = static_cast<real32_T>(fmod(static_cast<real_T>(tmp), 65536.0));
  }

  /* BusAssignment: '<Root>/Bus Assignment2' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion4'
   */
  rtb_BusAssignment2.Data = static_cast<int16_T>((tmp < 0.0F ?
    static_cast<int32_T>(static_cast<int16_T>(-static_cast<int16_T>
    (static_cast<uint16_T>(-tmp)))) : static_cast<int32_T>(static_cast<int16_T>(
    static_cast<uint16_T>(tmp)))));

  /* Outputs for Atomic SubSystem: '<Root>/Publish2' */
  /* MATLABSystem: '<S2>/SinkBlock' */
  Pub_PI_Laengsregler_304.publish(&rtb_BusAssignment2);

  /* End of Outputs for SubSystem: '<Root>/Publish2' */
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

    /* Start for Atomic SubSystem: '<Root>/Subscribe4' */
    /* Start for MATLABSystem: '<S3>/SourceBlock' */
    PI_Laengsregler_DW.obj_k.matlabCodegenIsDeleted = false;
    PI_Laengsregler_DW.objisempty = true;
    PI_Laengsregler_DW.obj_k.isInitialized = 1;
    for (i = 0; i < 16; i++) {
      tmp_0[i] = tmp_1[i];
    }

    tmp_0[16] = '\x00';
    Sub_PI_Laengsregler_305.createSubscriber(tmp_0, 1);
    PI_Laengsregler_DW.obj_k.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S3>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe4' */

    /* Start for Atomic SubSystem: '<Root>/Publish2' */
    /* Start for MATLABSystem: '<S2>/SinkBlock' */
    PI_Laengsregler_DW.obj.matlabCodegenIsDeleted = false;
    PI_Laengsregler_DW.objisempty_m = true;
    PI_Laengsregler_DW.obj.isInitialized = 1;
    for (i = 0; i < 13; i++) {
      tmp[i] = tmp_2[i];
    }

    tmp[13] = '\x00';
    Pub_PI_Laengsregler_304.createPublisher(tmp, 1);
    PI_Laengsregler_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S2>/SinkBlock' */
    /* End of Start for SubSystem: '<Root>/Publish2' */
  }

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe4' */
  /* SystemInitialize for Enabled SubSystem: '<S3>/Enabled Subsystem' */
  /* SystemInitialize for Outport: '<S5>/Out1' */
  PI_Laengsregler_B.In1 = PI_Laengsregler_P.Out1_Y0;

  /* End of SystemInitialize for SubSystem: '<S3>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe4' */
}

/* Model terminate function */
void PI_Laengsregler_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Subscribe4' */
  /* Terminate for MATLABSystem: '<S3>/SourceBlock' */
  matlabCodegenHandle_matlabCod_l(&PI_Laengsregler_DW.obj_k);

  /* End of Terminate for SubSystem: '<Root>/Subscribe4' */

  /* Terminate for Atomic SubSystem: '<Root>/Publish2' */
  /* Terminate for MATLABSystem: '<S2>/SinkBlock' */
  matlabCodegenHandle_matlabCodeg(&PI_Laengsregler_DW.obj);

  /* End of Terminate for SubSystem: '<Root>/Publish2' */
}
