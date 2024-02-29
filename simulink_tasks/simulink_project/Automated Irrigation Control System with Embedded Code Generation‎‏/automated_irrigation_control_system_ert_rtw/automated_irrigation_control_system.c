/*
 * File: automated_irrigation_control_system.c
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

#include "automated_irrigation_control_system.h"

/* Block signals and states (default storage) */
DW rtDW;

/* Model step function */
void automated_irrigation_control_system_step(void)
{
  /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
  if (rtDW.clockTickCounter >= 1) {
    rtDW.clockTickCounter = 0;
  } else {
    rtDW.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<Root>/Pulse Generator' */
}

/* Model initialize function */
void automated_irrigation_control_system_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
