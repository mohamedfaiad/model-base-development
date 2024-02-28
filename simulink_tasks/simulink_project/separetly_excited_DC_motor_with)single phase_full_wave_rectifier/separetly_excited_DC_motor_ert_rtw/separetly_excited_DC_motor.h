/*
 * File: separetly_excited_DC_motor.h
 *
 * Code generated for Simulink model 'separetly_excited_DC_motor'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Wed Feb 28 21:11:19 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_separetly_excited_DC_motor_h_
#define RTW_HEADER_separetly_excited_DC_motor_h_
#include <stddef.h>
#include <float.h>
#include <math.h>
#include <string.h>
#ifndef separetly_excited_DC_motor_COMMON_INCLUDES_
#define separetly_excited_DC_motor_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif                         /* separetly_excited_DC_motor_COMMON_INCLUDES_ */

#include "separetly_excited_DC_motor_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetSampleHitArray
#define rtmGetSampleHitArray(rtm)      ((rtm)->Timing.sampleHitArray)
#endif

#ifndef rtmGetStepSize
#define rtmGetStepSize(rtm)            ((rtm)->Timing.stepSize)
#endif

#ifndef rtmGet_TimeOfLastOutput
#define rtmGet_TimeOfLastOutput(rtm)   ((rtm)->Timing.timeOfLastOutput)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

#ifndef rtmGetTimeOfLastOutput
#define rtmGetTimeOfLastOutput(rtm)    ((rtm)->Timing.timeOfLastOutput)
#endif

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T StateSpace_o1[3];             /* '<S10>/State-Space' */
  real_T StateSpace_o2[16];            /* '<S10>/State-Space' */
  real_T StateSpace_RWORK[2];          /* '<S10>/State-Space' */
  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } VariableTimeDelay_RWORK;           /* '<S30>/Variable Time Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[26624];
  } VariableTimeDelay_RWORK_o;         /* '<S29>/Variable Time Delay' */

  real_T AC;                           /* '<S7>/AC' */
  real_T Sum;                          /* '<S2>/Sum' */
  real_T Sum1;                         /* '<S2>/Sum1' */
  real_T En1;                          /* '<S19>/MATLAB Function' */
  real_T VariableTimeDelay;            /* '<S30>/Variable Time Delay' */
  real_T DataTypeConversion;           /* '<S30>/Data Type Conversion' */
  real_T Gain;                         /* '<S29>/Gain' */
  real_T VariableTimeDelay_c;          /* '<S29>/Variable Time Delay' */
  void *StateSpace_PWORK[22];          /* '<S10>/State-Space' */
  struct {
    void *TUbufferPtrs[2];
  } VariableTimeDelay_PWORK;           /* '<S30>/Variable Time Delay' */

  struct {
    void *TUbufferPtrs[2];
  } VariableTimeDelay_PWORK_o;         /* '<S29>/Variable Time Delay' */

  int_T StateSpace_IWORK[23];          /* '<S10>/State-Space' */
  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } VariableTimeDelay_IWORK;           /* '<S30>/Variable Time Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } VariableTimeDelay_IWORK_m;         /* '<S29>/Variable Time Delay' */

  int_T StateSpace_MODE[9];            /* '<S10>/State-Space' */
  uint32_T Counter_ClkEphState;        /* '<S19>/Counter' */
  uint8_T Counter_Count;               /* '<S19>/Counter' */
  boolean_T EnabledSubsystem1_MODE;    /* '<S19>/Enabled Subsystem1' */
  boolean_T EnabledSubsystem_MODE;     /* '<S19>/Enabled Subsystem' */
} DW;

/* Continuous states (default storage) */
typedef struct {
  real_T StateSpace_CSTATE[5];         /* '<S10>/State-Space' */
  real_T TransferFcn1_CSTATE;          /* '<S2>/Transfer Fcn1' */
  real_T TransferFcn_CSTATE;           /* '<S2>/Transfer Fcn' */
} X;

/* State derivatives (default storage) */
typedef struct {
  real_T StateSpace_CSTATE[5];         /* '<S10>/State-Space' */
  real_T TransferFcn1_CSTATE;          /* '<S2>/Transfer Fcn1' */
  real_T TransferFcn_CSTATE;           /* '<S2>/Transfer Fcn' */
} XDot;

/* State disabled  */
typedef struct {
  boolean_T StateSpace_CSTATE[5];      /* '<S10>/State-Space' */
  boolean_T TransferFcn1_CSTATE;       /* '<S2>/Transfer Fcn1' */
  boolean_T TransferFcn_CSTATE;        /* '<S2>/Transfer Fcn' */
} XDis;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T Gain;                   /* '<S30>/Gain' */
} ConstB;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: Vf)
   * Referenced by:
   *   '<S21>/ddd'
   *   '<S23>/ddd'
   *   '<S25>/ddd'
   *   '<S27>/ddd'
   */
  real_T pooled4;

  /* Expression: zeros(1,4)
   * Referenced by: '<S32>/g'
   */
  real_T g_Value[4];

  /* Computed Parameter: StateSpace_P1_Size
   * Referenced by: '<S10>/State-Space'
   */
  real_T StateSpace_P1_Size[2];

  /* Expression: S.Mg
   * Referenced by: '<S10>/State-Space'
   */
  real_T StateSpace_P1[624];

  /* Computed Parameter: StateSpace_P2_Size
   * Referenced by: '<S10>/State-Space'
   */
  real_T StateSpace_P2_Size[2];

  /* Expression: [S.nb.x S.nb.u S.nb.y S.nb.s]
   * Referenced by: '<S10>/State-Space'
   */
  real_T StateSpace_P2[4];

  /* Computed Parameter: StateSpace_P3_Size
   * Referenced by: '<S10>/State-Space'
   */
  real_T StateSpace_P3_Size[2];

  /* Expression: S.x0
   * Referenced by: '<S10>/State-Space'
   */
  real_T StateSpace_P3[5];

  /* Computed Parameter: StateSpace_P4_Size
   * Referenced by: '<S10>/State-Space'
   */
  real_T StateSpace_P4_Size[2];

  /* Computed Parameter: StateSpace_P4
   * Referenced by: '<S10>/State-Space'
   */
  real_T StateSpace_P4[4563];

  /* Computed Parameter: StateSpace_P5_Size
   * Referenced by: '<S10>/State-Space'
   */
  real_T StateSpace_P5_Size[2];

  /* Expression: S.SwitchVf
   * Referenced by: '<S10>/State-Space'
   */
  real_T StateSpace_P5[16];

  /* Computed Parameter: StateSpace_P6_Size
   * Referenced by: '<S10>/State-Space'
   */
  real_T StateSpace_P6_Size[2];

  /* Expression: S.SwitchType
   * Referenced by: '<S10>/State-Space'
   */
  real_T StateSpace_P6[8];

  /* Computed Parameter: StateSpace_P7_Size
   * Referenced by: '<S10>/State-Space'
   */
  real_T StateSpace_P7_Size[2];

  /* Expression: S.SwitchGateInitialValue
   * Referenced by: '<S10>/State-Space'
   */
  real_T StateSpace_P7[8];

  /* Computed Parameter: StateSpace_P8_Size
   * Referenced by: '<S10>/State-Space'
   */
  real_T StateSpace_P8_Size[2];

  /* Expression: S.SwitchTolerance
   * Referenced by: '<S10>/State-Space'
   */
  real_T StateSpace_P8[8];

  /* Computed Parameter: StateSpace_P9_Size
   * Referenced by: '<S10>/State-Space'
   */
  real_T StateSpace_P9_Size[2];

  /* Expression: S.SaveMatrices
   * Referenced by: '<S10>/State-Space'
   */
  real_T StateSpace_P9;

  /* Computed Parameter: StateSpace_P10_Size
   * Referenced by: '<S10>/State-Space'
   */
  real_T StateSpace_P10_Size[2];

  /* Expression: S.BufferSize
   * Referenced by: '<S10>/State-Space'
   */
  real_T StateSpace_P10;
} ConstP;

/* Real-time Model Data Structure */
struct tag_RTM {
  struct SimStruct_tag * *childSfunctions;
  const char_T *errorStatus;
  SS_SimMode simMode;
  RTWSolverInfo solverInfo;
  RTWSolverInfo *solverInfoPtr;
  void *sfcnInfo;

  /*
   * NonInlinedSFcns:
   * The following substructure contains information regarding
   * non-inlined s-functions used in the model.
   */
  struct {
    RTWSfcnInfo sfcnInfo;
    time_T *taskTimePtrs[2];
    SimStruct childSFunctions[1];
    SimStruct *childSFunctionPtrs[1];
    struct _ssBlkInfo2 blkInfo2[1];
    struct _ssSFcnModelMethods2 methods2[1];
    struct _ssSFcnModelMethods3 methods3[1];
    struct _ssSFcnModelMethods4 methods4[1];
    struct _ssStatesInfo2 statesInfo2[1];
    ssPeriodicStatesInfo periodicStatesInfo[1];
    struct _ssPortInfo2 inputOutputPortInfo2[1];
    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[2];
      struct _ssInPortUnit inputPortUnits[2];
      struct _ssInPortCoSimAttribute inputPortCoSimAttribute[2];
      real_T const *UPtrs0[5];
      real_T const *UPtrs1[8];
      struct _ssPortOutputs outputPortInfo[2];
      struct _ssOutPortUnit outputPortUnits[2];
      struct _ssOutPortCoSimAttribute outputPortCoSimAttribute[2];
      uint_T attribs[10];
      mxArray *params[10];
      struct _ssDWorkRecord dWork[4];
      struct _ssDWorkAuxRecord dWorkAux[4];
    } Sfcn0;
  } NonInlinedSFcns;

  X *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[7];
  real_T odeF[3][7];
  ODE3_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T options;
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numU;
    int_T numY;
    int_T numSampTimes;
    int_T numBlocks;
    int_T numBlockIO;
    int_T numBlockPrms;
    int_T numDwork;
    int_T numSFcnPrms;
    int_T numSFcns;
    int_T numIports;
    int_T numOports;
    int_T numNonSampZCs;
    int_T sysDirFeedThru;
    int_T rtwGenSfcn;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T stepSize;
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    time_T tStart;
    time_T tFinal;
    time_T timeOfLastOutput;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *sampleTimes;
    time_T *offsetTimes;
    int_T *sampleTimeTaskIDPtr;
    int_T *sampleHits;
    int_T *perTaskSampleHits;
    time_T *t;
    time_T sampleTimesArray[2];
    time_T offsetTimesArray[2];
    int_T sampleTimeTaskIDArray[2];
    int_T sampleHitArray[2];
    int_T perTaskSampleHitsArray[4];
    time_T tArray[2];
  } Timing;
};

/* Continuous states (default storage) */
extern X rtX;

/* Block signals and states (default storage) */
extern DW rtDW;
extern const ConstB rtConstB;          /* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void separetly_excited_DC_motor_initialize(void);
extern void separetly_excited_DC_motor_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Gain2' : Unused code path elimination
 * Block '<Root>/Scope' : Unused code path elimination
 * Block '<Root>/Scope1' : Unused code path elimination
 * Block '<Root>/Scope2' : Unused code path elimination
 * Block '<S4>/do not delete this gain' : Unused code path elimination
 * Block '<S21>/Ron' : Unused code path elimination
 * Block '<S21>/Sum' : Unused code path elimination
 * Block '<S23>/Ron' : Unused code path elimination
 * Block '<S23>/Sum' : Unused code path elimination
 * Block '<S25>/Ron' : Unused code path elimination
 * Block '<S25>/Sum' : Unused code path elimination
 * Block '<S27>/Ron' : Unused code path elimination
 * Block '<S27>/Sum' : Unused code path elimination
 * Block '<S34>/Constant' : Unused code path elimination
 * Block '<S3>/do not delete this gain' : Eliminated nontunable gain of 1
 * Block '<S21>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S23>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S25>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S27>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S29>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S34>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S33>/do not delete this gain' : Eliminated nontunable gain of 1
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'separetly_excited_DC_motor'
 * '<S1>'   : 'separetly_excited_DC_motor/AC Voltage Source'
 * '<S2>'   : 'separetly_excited_DC_motor/DC motor'
 * '<S3>'   : 'separetly_excited_DC_motor/Voltage Measurement'
 * '<S4>'   : 'separetly_excited_DC_motor/Voltage Measurement1'
 * '<S5>'   : 'separetly_excited_DC_motor/powergui'
 * '<S6>'   : 'separetly_excited_DC_motor/single phase full wave rectifier with Determination zero crossing '
 * '<S7>'   : 'separetly_excited_DC_motor/AC Voltage Source/Model'
 * '<S8>'   : 'separetly_excited_DC_motor/Voltage Measurement/Model'
 * '<S9>'   : 'separetly_excited_DC_motor/Voltage Measurement1/Model'
 * '<S10>'  : 'separetly_excited_DC_motor/powergui/EquivalentModel1'
 * '<S11>'  : 'separetly_excited_DC_motor/powergui/EquivalentModel1/Gates'
 * '<S12>'  : 'separetly_excited_DC_motor/powergui/EquivalentModel1/Sources'
 * '<S13>'  : 'separetly_excited_DC_motor/powergui/EquivalentModel1/Status'
 * '<S14>'  : 'separetly_excited_DC_motor/powergui/EquivalentModel1/Yout'
 * '<S15>'  : 'separetly_excited_DC_motor/single phase full wave rectifier with Determination zero crossing /Thyristor'
 * '<S16>'  : 'separetly_excited_DC_motor/single phase full wave rectifier with Determination zero crossing /Thyristor1'
 * '<S17>'  : 'separetly_excited_DC_motor/single phase full wave rectifier with Determination zero crossing /Thyristor2'
 * '<S18>'  : 'separetly_excited_DC_motor/single phase full wave rectifier with Determination zero crossing /Thyristor3'
 * '<S19>'  : 'separetly_excited_DC_motor/single phase full wave rectifier with Determination zero crossing /firing logic'
 * '<S20>'  : 'separetly_excited_DC_motor/single phase full wave rectifier with Determination zero crossing /zero cross subsyystem'
 * '<S21>'  : 'separetly_excited_DC_motor/single phase full wave rectifier with Determination zero crossing /Thyristor/Model'
 * '<S22>'  : 'separetly_excited_DC_motor/single phase full wave rectifier with Determination zero crossing /Thyristor/Model/Measurement list'
 * '<S23>'  : 'separetly_excited_DC_motor/single phase full wave rectifier with Determination zero crossing /Thyristor1/Model'
 * '<S24>'  : 'separetly_excited_DC_motor/single phase full wave rectifier with Determination zero crossing /Thyristor1/Model/Measurement list'
 * '<S25>'  : 'separetly_excited_DC_motor/single phase full wave rectifier with Determination zero crossing /Thyristor2/Model'
 * '<S26>'  : 'separetly_excited_DC_motor/single phase full wave rectifier with Determination zero crossing /Thyristor2/Model/Measurement list'
 * '<S27>'  : 'separetly_excited_DC_motor/single phase full wave rectifier with Determination zero crossing /Thyristor3/Model'
 * '<S28>'  : 'separetly_excited_DC_motor/single phase full wave rectifier with Determination zero crossing /Thyristor3/Model/Measurement list'
 * '<S29>'  : 'separetly_excited_DC_motor/single phase full wave rectifier with Determination zero crossing /firing logic/Enabled Subsystem'
 * '<S30>'  : 'separetly_excited_DC_motor/single phase full wave rectifier with Determination zero crossing /firing logic/Enabled Subsystem1'
 * '<S31>'  : 'separetly_excited_DC_motor/single phase full wave rectifier with Determination zero crossing /firing logic/MATLAB Function'
 * '<S32>'  : 'separetly_excited_DC_motor/single phase full wave rectifier with Determination zero crossing /zero cross subsyystem/Universal Bridge'
 * '<S33>'  : 'separetly_excited_DC_motor/single phase full wave rectifier with Determination zero crossing /zero cross subsyystem/Voltage Measurement'
 * '<S34>'  : 'separetly_excited_DC_motor/single phase full wave rectifier with Determination zero crossing /zero cross subsyystem/Universal Bridge/Model'
 * '<S35>'  : 'separetly_excited_DC_motor/single phase full wave rectifier with Determination zero crossing /zero cross subsyystem/Voltage Measurement/Model'
 */
#endif                            /* RTW_HEADER_separetly_excited_DC_motor_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
