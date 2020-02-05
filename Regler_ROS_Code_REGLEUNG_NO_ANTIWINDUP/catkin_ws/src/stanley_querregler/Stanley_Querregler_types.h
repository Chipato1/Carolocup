/*
 * Stanley_Querregler_types.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Stanley_Querregler".
 *
 * Model version              : 1.19
 * Simulink Coder version : 9.2 (R2019b) 18-Jul-2019
 * C++ source code generated on : Wed Feb  5 16:58:17 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Stanley_Querregler_types_h_
#define RTW_HEADER_Stanley_Querregler_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_Stanley_Querregler_std_msgs_Float32_
#define DEFINED_TYPEDEF_FOR_SL_Bus_Stanley_Querregler_std_msgs_Float32_

typedef struct {
  real32_T Data;
} SL_Bus_Stanley_Querregler_std_msgs_Float32;

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_Stanley_Querregler_std_msgs_Bool_
#define DEFINED_TYPEDEF_FOR_SL_Bus_Stanley_Querregler_std_msgs_Bool_

typedef struct {
  boolean_T Data;
} SL_Bus_Stanley_Querregler_std_msgs_Bool;

#endif

#ifndef typedef_ros_slros_internal_block_Publ_T
#define typedef_ros_slros_internal_block_Publ_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
} ros_slros_internal_block_Publ_T;

#endif                               /*typedef_ros_slros_internal_block_Publ_T*/

#ifndef typedef_ros_slros_internal_block_Subs_T
#define typedef_ros_slros_internal_block_Subs_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
} ros_slros_internal_block_Subs_T;

#endif                               /*typedef_ros_slros_internal_block_Subs_T*/

/* Custom Type definition for MATLAB Function: '<S12>/Kinematic' */
#ifndef struct_tag_sOUC5r4zsFawyqfEUBdluaD
#define struct_tag_sOUC5r4zsFawyqfEUBdluaD

struct tag_sOUC5r4zsFawyqfEUBdluaD
{
  real_T Direction;
  real_T PositionGain;
  real_T Wheelbase;
  real_T MaxSteeringAngle;
};

#endif                                 /*struct_tag_sOUC5r4zsFawyqfEUBdluaD*/

#ifndef typedef_sOUC5r4zsFawyqfEUBdluaD_Stanl_T
#define typedef_sOUC5r4zsFawyqfEUBdluaD_Stanl_T

typedef struct tag_sOUC5r4zsFawyqfEUBdluaD sOUC5r4zsFawyqfEUBdluaD_Stanl_T;

#endif                               /*typedef_sOUC5r4zsFawyqfEUBdluaD_Stanl_T*/

#ifndef struct_tag_sYnsNufJk5tTQplyRdCvlwG
#define struct_tag_sYnsNufJk5tTQplyRdCvlwG

struct tag_sYnsNufJk5tTQplyRdCvlwG
{
  uint32_T Direction;
  uint32_T PositionGain;
  uint32_T Wheelbase;
  uint32_T MaxSteeringAngle;
};

#endif                                 /*struct_tag_sYnsNufJk5tTQplyRdCvlwG*/

#ifndef typedef_sYnsNufJk5tTQplyRdCvlwG_Stanl_T
#define typedef_sYnsNufJk5tTQplyRdCvlwG_Stanl_T

typedef struct tag_sYnsNufJk5tTQplyRdCvlwG sYnsNufJk5tTQplyRdCvlwG_Stanl_T;

#endif                               /*typedef_sYnsNufJk5tTQplyRdCvlwG_Stanl_T*/

#ifndef struct_tag_s9s8BC13iTohZXRbLMSIDHE
#define struct_tag_s9s8BC13iTohZXRbLMSIDHE

struct tag_s9s8BC13iTohZXRbLMSIDHE
{
  boolean_T CaseSensitivity;
  boolean_T StructExpand;
  boolean_T PartialMatching;
};

#endif                                 /*struct_tag_s9s8BC13iTohZXRbLMSIDHE*/

#ifndef typedef_s9s8BC13iTohZXRbLMSIDHE_Stanl_T
#define typedef_s9s8BC13iTohZXRbLMSIDHE_Stanl_T

typedef struct tag_s9s8BC13iTohZXRbLMSIDHE s9s8BC13iTohZXRbLMSIDHE_Stanl_T;

#endif                               /*typedef_s9s8BC13iTohZXRbLMSIDHE_Stanl_T*/

/* Parameters for system: '<S4>/Enabled Subsystem' */
typedef struct P_EnabledSubsystem_Stanley_Qu_T_ P_EnabledSubsystem_Stanley_Qu_T;

/* Parameters (default storage) */
typedef struct P_Stanley_Querregler_T_ P_Stanley_Querregler_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_Stanley_Querregler_T RT_MODEL_Stanley_Querregler_T;

#endif                              /* RTW_HEADER_Stanley_Querregler_types_h_ */
