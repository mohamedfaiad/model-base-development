/*
 * File: automated_irrigation_control_system.h
 *
 * Code generated for Simulink model 'automated_irrigation_control_system'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Thu Feb 29 19:45:25 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_automated_irrigation_control_system_h_
#define RTW_HEADER_automated_irrigation_control_system_h_
#ifndef automated_irrigation_control_system_COMMON_INCLUDES_
#define automated_irrigation_control_system_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                /* automated_irrigation_control_system_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  int32_T clockTickCounter;            /* '<Root>/Pulse Generator' */
} DW;

/* Block signals and states (default storage) */
extern DW rtDW;

/* Model entry point functions */
extern void automated_irrigation_control_system_initialize(void);
extern void automated_irrigation_control_system_step(void);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Display' : Unused code path elimination
 * Block '<Root>/Display1' : Unused code path elimination
 * Block '<Root>/Display3' : Unused code path elimination
 * Block '<S4>/Add' : Unused code path elimination
 * Block '<S4>/Unit Delay' : Unused code path elimination
 * Block '<Root>/Scope' : Unused code path elimination
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
 * '<Root>' : 'automated_irrigation_control_system'
 * '<S1>'   : 'automated_irrigation_control_system/If Action Subsystem'
 * '<S2>'   : 'automated_irrigation_control_system/If Action Subsystem1'
 * '<S3>'   : 'automated_irrigation_control_system/If Action Subsystem2'
 * '<S4>'   : 'automated_irrigation_control_system/If Action Subsystem3'
 * '<S5>'   : 'automated_irrigation_control_system/If Action Subsystem4'
 */
#endif                   /* RTW_HEADER_automated_irrigation_control_system_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
