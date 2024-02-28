/*
 * File: separetly_excited_DC_motor.c
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

#include "separetly_excited_DC_motor.h"
#include "separetly_excited_DC_motor_private.h"

/* Continuous states */
X rtX;

/* Block signals and states (default storage) */
DW rtDW;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

/* Forward declaration for local functions */
static real_T mod(real_T x);

/*
 * Time delay interpolation routine
 *
 * The linear interpolation is performed using the formula:
 *
 *          (t2 - tMinusDelay)         (tMinusDelay - t1)
 * u(t)  =  ----------------- * u1  +  ------------------- * u2
 *              (t2 - t1)                  (t2 - t1)
 */
real_T rt_TDelayInterpolate(
  real_T tMinusDelay,                 /* tMinusDelay = currentSimTime - delay */
  real_T tStart,
  real_T *uBuf,
  int_T bufSz,
  int_T *lastIdx,
  int_T oldestIdx,
  int_T newIdx,
  real_T initOutput,
  boolean_T discrete,
  boolean_T minorStepAndTAtLastMajorOutput)
{
  int_T i;
  real_T yout, t1, t2, u1, u2;
  real_T* tBuf = uBuf + bufSz;

  /*
   * If there is only one data point in the buffer, this data point must be
   * the t= 0 and tMinusDelay > t0, it ask for something unknown. The best
   * guess if initial output as well
   */
  if ((newIdx == 0) && (oldestIdx ==0 ) && (tMinusDelay > tStart))
    return initOutput;

  /*
   * If tMinusDelay is less than zero, should output initial value
   */
  if (tMinusDelay <= tStart)
    return initOutput;

  /* For fixed buffer extrapolation:
   * if tMinusDelay is small than the time at oldestIdx, if discrete, output
   * tailptr value,  else use tailptr and tailptr+1 value to extrapolate
   * It is also for fixed buffer. Note: The same condition can happen for transport delay block where
   * use tStart and and t[tail] other than using t[tail] and t[tail+1].
   * See below
   */
  if ((tMinusDelay <= tBuf[oldestIdx] ) ) {
    if (discrete) {
      return(uBuf[oldestIdx]);
    } else {
      int_T tempIdx= oldestIdx + 1;
      if (oldestIdx == bufSz-1)
        tempIdx = 0;
      t1= tBuf[oldestIdx];
      t2= tBuf[tempIdx];
      u1= uBuf[oldestIdx];
      u2= uBuf[tempIdx];
      if (t2 == t1) {
        if (tMinusDelay >= t2) {
          yout = u2;
        } else {
          yout = u1;
        }
      } else {
        real_T f1 = (t2-tMinusDelay) / (t2-t1);
        real_T f2 = 1.0 - f1;

        /*
         * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
         */
        yout = f1*u1 + f2*u2;
      }

      return yout;
    }
  }

  /*
   * When block does not have direct feedthrough, we use the table of
   * values to extrapolate off the end of the table for delays that are less
   * than 0 (less then step size).  This is not completely accurate.  The
   * chain of events is as follows for a given time t.  Major output - look
   * in table.  Update - add entry to table.  Now, if we call the output at
   * time t again, there is a new entry in the table. For very small delays,
   * this means that we will have a different answer from the previous call
   * to the output fcn at the same time t.  The following code prevents this
   * from happening.
   */
  if (minorStepAndTAtLastMajorOutput) {
    /* pretend that the new entry has not been added to table */
    if (newIdx != 0) {
      if (*lastIdx == newIdx) {
        (*lastIdx)--;
      }

      newIdx--;
    } else {
      if (*lastIdx == newIdx) {
        *lastIdx = bufSz-1;
      }

      newIdx = bufSz - 1;
    }
  }

  i = *lastIdx;
  if (tBuf[i] < tMinusDelay) {
    /* Look forward starting at last index */
    while (tBuf[i] < tMinusDelay) {
      /* May occur if the delay is less than step-size - extrapolate */
      if (i == newIdx)
        break;
      i = ( i < (bufSz-1) ) ? (i+1) : 0;/* move through buffer */
    }
  } else {
    /*
     * Look backwards starting at last index which can happen when the
     * delay time increases.
     */
    while (tBuf[i] >= tMinusDelay) {
      /*
       * Due to the entry condition at top of function, we
       * should never hit the end.
       */
      i = (i > 0) ? i-1 : (bufSz-1);   /* move through buffer */
    }

    i = ( i < (bufSz-1) ) ? (i+1) : 0;
  }

  *lastIdx = i;
  if (discrete) {
    /*
     * tempEps = 128 * eps;
     * localEps = max(tempEps, tempEps*fabs(tBuf[i]))/2;
     */
    double tempEps = (DBL_EPSILON) * 128.0;
    double localEps = tempEps * fabs(tBuf[i]);
    if (tempEps > localEps) {
      localEps = tempEps;
    }

    localEps = localEps / 2.0;
    if (tMinusDelay >= (tBuf[i] - localEps)) {
      yout = uBuf[i];
    } else {
      if (i == 0) {
        yout = uBuf[bufSz-1];
      } else {
        yout = uBuf[i-1];
      }
    }
  } else {
    if (i == 0) {
      t1 = tBuf[bufSz-1];
      u1 = uBuf[bufSz-1];
    } else {
      t1 = tBuf[i-1];
      u1 = uBuf[i-1];
    }

    t2 = tBuf[i];
    u2 = uBuf[i];
    if (t2 == t1) {
      if (tMinusDelay >= t2) {
        yout = u2;
      } else {
        yout = u1;
      }
    } else {
      real_T f1 = (t2-tMinusDelay) / (t2-t1);
      real_T f2 = 1.0 - f1;

      /*
       * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
       */
      yout = f1*u1 + f2*u2;
    }
  }

  return(yout);
}

/* Projection for root system: '<Root>' */
void separetly_excited_DC_motor_projection(void)
{
  /* Projection for S-Function (sfun_spid_contc): '<S10>/State-Space' incorporates:
   *  Constant: '<S21>/ddd'
   *  Constant: '<S23>/ddd'
   *  Constant: '<S25>/ddd'
   *  Constant: '<S27>/ddd'
   *  Constant: '<S32>/g'
   */
  /* Level2 S-Function Block: '<S10>/State-Space' (sfun_spid_contc) */
  {
    SimStruct *rts = rtM->childSfunctions[0];
    sfcnProjection(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }
}

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
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 7;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  separetly_excited_DC_motor_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  separetly_excited_DC_motor_step();
  separetly_excited_DC_motor_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  separetly_excited_DC_motor_step();
  separetly_excited_DC_motor_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  separetly_excited_DC_motor_step();
  separetly_excited_DC_motor_projection();
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

uint32_T MWDSP_EPH_R_B(boolean_T evt, uint32_T *sta)
{
  int32_T curState;
  int32_T lastzcevent;
  int32_T newState;
  int32_T newStateR;
  uint32_T previousState;
  uint32_T retVal;

  /* S-Function (sdspcount2): '<S19>/Counter' */
  /* Detect rising edge events */
  previousState = *sta;
  retVal = 0U;
  lastzcevent = 0;
  newState = 5;
  newStateR = 5;
  if (evt) {
    curState = 2;
  } else {
    curState = 1;
  }

  if (*sta == 5U) {
    newStateR = curState;
  } else if ((uint32_T)curState != *sta) {
    if (*sta == 3U) {
      if ((uint32_T)curState == 1U) {
        newStateR = 1;
      } else {
        lastzcevent = 2;
        previousState = 1U;
      }
    }

    if (previousState == 4U) {
      if ((uint32_T)curState == 1U) {
        newStateR = 1;
      } else {
        lastzcevent = 3;
        previousState = 1U;
      }
    }

    if ((previousState == 1U) && ((uint32_T)curState == 2U)) {
      retVal = 2U;
    }

    if (previousState == 0U) {
      retVal = 2U;
    }

    if (retVal == (uint32_T)lastzcevent) {
      retVal = 0U;
    }

    if (((uint32_T)curState == 1U) && (retVal == 2U)) {
      newState = 3;
    } else {
      newState = curState;
    }
  }

  if ((uint32_T)newStateR != 5U) {
    *sta = (uint32_T)newStateR;
    retVal = 0U;
  }

  if ((uint32_T)newState != 5U) {
    *sta = (uint32_T)newState;
  }

  /* End of S-Function (sdspcount2): '<S19>/Counter' */
  return retVal;
}

/* Function for MATLAB Function: '<S19>/MATLAB Function' */
static real_T mod(real_T x)
{
  real_T r;
  if (rtIsNaN(x)) {
    r = (rtNaN);
  } else if (rtIsInf(x)) {
    r = (rtNaN);
  } else if (x == 0.0) {
    r = 0.0;
  } else {
    r = fmod(x, 2.0);
    if (r == 0.0) {
      r = 0.0;
    } else if (x < 0.0) {
      r += 2.0;
    }
  }

  return r;
}

/* Model step function */
void separetly_excited_DC_motor_step(void)
{
  real_T AC_tmp;
  real_T rtb_Counter;
  int32_T En2;
  boolean_T zerocrosssignal;
  if (rtmIsMajorTimeStep(rtM)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&rtM->solverInfo,((rtM->Timing.clockTick0+1)*
      rtM->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(rtM)) {
    rtM->Timing.t[0] = rtsiGetT(&rtM->solverInfo);
  }

  /* Sin: '<S7>/AC' incorporates:
   *  Step: '<S2>/Tl'
   */
  AC_tmp = rtM->Timing.t[0];

  /* Sin: '<S7>/AC' */
  rtDW.AC = sin(314.15926535897933 * AC_tmp) * 311.12698372208092;

  /* S-Function (sfun_spid_contc): '<S10>/State-Space' incorporates:
   *  Constant: '<S21>/ddd'
   *  Constant: '<S23>/ddd'
   *  Constant: '<S25>/ddd'
   *  Constant: '<S27>/ddd'
   *  Constant: '<S32>/g'
   */

  /* Level2 S-Function Block: '<S10>/State-Space' (sfun_spid_contc) */
  {
    SimStruct *rts = rtM->childSfunctions[0];
    sfcnOutputs(rts,0);
  }

  /* Sum: '<S2>/Sum' incorporates:
   *  Gain: '<S2>/Gain1'
   *  TransferFcn: '<S2>/Transfer Fcn1'
   */
  rtDW.Sum = rtDW.StateSpace_o1[0] - 0.2 * rtX.TransferFcn1_CSTATE * 1.6;

  /* Logic: '<S20>/Logical Operator' incorporates:
   *  Constant: '<S20>/Constant'
   *  Constant: '<S20>/Constant1'
   *  RelationalOperator: '<S20>/Relational Operator'
   *  RelationalOperator: '<S20>/Relational Operator1'
   */
  zerocrosssignal = ((rtDW.StateSpace_o1[2] <= 0.0) && (rtDW.StateSpace_o1[2] <=
    10.0));
  if (rtmIsMajorTimeStep(rtM)) {
    /* S-Function (sdspcount2): '<S19>/Counter' */
    if (MWDSP_EPH_R_B(zerocrosssignal, &rtDW.Counter_ClkEphState) != 0U) {
      if (rtDW.Counter_Count < 255) {
        rtDW.Counter_Count++;
      } else {
        rtDW.Counter_Count = 0U;
      }
    }

    /* MATLAB Function: '<S19>/MATLAB Function' incorporates:
     *  S-Function (sdspcount2): '<S19>/Counter'
     */
    rtDW.En1 = 0.0;
    En2 = 0;
    rtb_Counter = mod((real_T)rtDW.Counter_Count);
    if (rtb_Counter == 0.0) {
      rtDW.En1 = 1.0;
    }

    if (rtb_Counter == 1.0) {
      rtDW.En1 = 0.0;
      En2 = 1;
    }

    /* End of MATLAB Function: '<S19>/MATLAB Function' */

    /* Outputs for Enabled SubSystem: '<S19>/Enabled Subsystem1' incorporates:
     *  EnablePort: '<S30>/Enable'
     */
    if (rtmIsMajorTimeStep(rtM)) {
      rtDW.EnabledSubsystem1_MODE = (En2 > 0);
    }

    /* End of Outputs for SubSystem: '<S19>/Enabled Subsystem1' */
  }

  /* Outputs for Enabled SubSystem: '<S19>/Enabled Subsystem1' incorporates:
   *  EnablePort: '<S30>/Enable'
   */
  if (rtDW.EnabledSubsystem1_MODE) {
    /* VariableTransportDelay: '<S30>/Variable Time Delay' */
    {
      real_T **uBuffer = (real_T**)&rtDW.VariableTimeDelay_PWORK.TUbufferPtrs[0];
      real_T simTime = rtM->Timing.t[0];
      real_T appliedDelay;
      appliedDelay = rtConstB.Gain;

      /* For variable time delay, output here */
      if (appliedDelay > 10.0) {
        appliedDelay = 10.0;
      }

      if (appliedDelay < 0.0) {
        /* negative delay is not supported
         *  set delay to 0
         */
        appliedDelay = 0.0;
      }

      rtDW.VariableTimeDelay = rt_TDelayInterpolate(
        simTime - appliedDelay,
        0.0,
        *uBuffer,
        rtDW.VariableTimeDelay_IWORK.CircularBufSize,
        &rtDW.VariableTimeDelay_IWORK.Last,
        rtDW.VariableTimeDelay_IWORK.Tail,
        rtDW.VariableTimeDelay_IWORK.Head,
        0.0,
        0,
        0);
    }

    /* DataTypeConversion: '<S30>/Data Type Conversion' */
    rtDW.DataTypeConversion = zerocrosssignal;
  }

  /* End of Outputs for SubSystem: '<S19>/Enabled Subsystem1' */

  /* Outputs for Enabled SubSystem: '<S19>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S29>/Enable'
   */
  if (rtmIsMajorTimeStep(rtM) && rtmIsMajorTimeStep(rtM)) {
    rtDW.EnabledSubsystem_MODE = (rtDW.En1 > 0.0);
  }

  if (rtDW.EnabledSubsystem_MODE) {
    /* Gain: '<S29>/Gain' incorporates:
     *  DataTypeConversion: '<S29>/Data Type Conversion1'
     */
    rtDW.Gain = 5.5555555555555558E-5 * (real_T)zerocrosssignal;

    /* VariableTransportDelay: '<S29>/Variable Time Delay' incorporates:
     *  Constant: '<S6>/firing angle'
     */
    {
      real_T **uBuffer = (real_T**)&rtDW.VariableTimeDelay_PWORK_o.TUbufferPtrs
        [0];
      real_T simTime = rtM->Timing.t[0];
      real_T appliedDelay;
      appliedDelay = rtDW.Gain;

      /* For variable time delay, output here */
      if (appliedDelay > 10.0) {
        appliedDelay = 10.0;
      }

      if (appliedDelay < 0.0) {
        /* negative delay is not supported
         *  set delay to 0
         */
        appliedDelay = 0.0;
      }

      if (appliedDelay == 0.0) {
        rtDW.VariableTimeDelay_c = 34.027571868896487;
      } else {
        rtDW.VariableTimeDelay_c = rt_TDelayInterpolate(
          simTime - appliedDelay,
          0.0,
          *uBuffer,
          rtDW.VariableTimeDelay_IWORK_m.CircularBufSize,
          &rtDW.VariableTimeDelay_IWORK_m.Last,
          rtDW.VariableTimeDelay_IWORK_m.Tail,
          rtDW.VariableTimeDelay_IWORK_m.Head,
          0.0,
          1,
          0);
      }
    }
  }

  /* End of Outputs for SubSystem: '<S19>/Enabled Subsystem' */

  /* Step: '<S2>/Tl' */
  if (AC_tmp < 6.0) {
    En2 = 25;
  } else {
    En2 = 75;
  }

  /* Sum: '<S2>/Sum1' incorporates:
   *  Gain: '<S2>/Gain'
   *  TransferFcn: '<S2>/Transfer Fcn'
   */
  rtDW.Sum1 = 10.0 * rtX.TransferFcn_CSTATE * 1.6 - (real_T)En2;
  if (rtmIsMajorTimeStep(rtM)) {
    /* Update for S-Function (sfun_spid_contc): '<S10>/State-Space' incorporates:
     *  Constant: '<S21>/ddd'
     *  Constant: '<S23>/ddd'
     *  Constant: '<S25>/ddd'
     *  Constant: '<S27>/ddd'
     *  Constant: '<S32>/g'
     */
    /* Level2 S-Function Block: '<S10>/State-Space' (sfun_spid_contc) */
    {
      SimStruct *rts = rtM->childSfunctions[0];
      sfcnUpdate(rts,0);
      if (ssGetErrorStatus(rts) != (NULL))
        return;
    }

    /* Update for Enabled SubSystem: '<S19>/Enabled Subsystem1' incorporates:
     *  EnablePort: '<S30>/Enable'
     */
    if (rtDW.EnabledSubsystem1_MODE) {
      /* Update for VariableTransportDelay: '<S30>/Variable Time Delay' */
      {
        real_T **uBuffer = (real_T**)&rtDW.VariableTimeDelay_PWORK.TUbufferPtrs
          [0];
        real_T simTime = rtM->Timing.t[0];
        rtDW.VariableTimeDelay_IWORK.Head = ((rtDW.VariableTimeDelay_IWORK.Head <
          (rtDW.VariableTimeDelay_IWORK.CircularBufSize-1)) ?
          (rtDW.VariableTimeDelay_IWORK.Head+1) : 0);
        if (rtDW.VariableTimeDelay_IWORK.Head ==
            rtDW.VariableTimeDelay_IWORK.Tail) {
          rtDW.VariableTimeDelay_IWORK.Tail =
            ((rtDW.VariableTimeDelay_IWORK.Tail <
              (rtDW.VariableTimeDelay_IWORK.CircularBufSize-1)) ?
             (rtDW.VariableTimeDelay_IWORK.Tail+1) : 0);
        }

        (*uBuffer + rtDW.VariableTimeDelay_IWORK.CircularBufSize)
          [rtDW.VariableTimeDelay_IWORK.Head] = simTime;
        (*uBuffer)[rtDW.VariableTimeDelay_IWORK.Head] = rtDW.DataTypeConversion;

        /* when use fixed buffer, reset solver at when buffer is updated
         * to avoid output consistency fail.
         */
      }
    }

    /* End of Update for SubSystem: '<S19>/Enabled Subsystem1' */

    /* Update for Enabled SubSystem: '<S19>/Enabled Subsystem' incorporates:
     *  EnablePort: '<S29>/Enable'
     */
    if (rtDW.EnabledSubsystem_MODE) {
      /* Update for VariableTransportDelay: '<S29>/Variable Time Delay' incorporates:
       *  Constant: '<S6>/firing angle'
       */
      {
        real_T **uBuffer = (real_T**)
          &rtDW.VariableTimeDelay_PWORK_o.TUbufferPtrs[0];
        real_T simTime = rtM->Timing.t[0];
        rtDW.VariableTimeDelay_IWORK_m.Head =
          ((rtDW.VariableTimeDelay_IWORK_m.Head <
            (rtDW.VariableTimeDelay_IWORK_m.CircularBufSize-1)) ?
           (rtDW.VariableTimeDelay_IWORK_m.Head+1) : 0);
        if (rtDW.VariableTimeDelay_IWORK_m.Head ==
            rtDW.VariableTimeDelay_IWORK_m.Tail) {
          rtDW.VariableTimeDelay_IWORK_m.Tail =
            ((rtDW.VariableTimeDelay_IWORK_m.Tail <
              (rtDW.VariableTimeDelay_IWORK_m.CircularBufSize-1)) ?
             (rtDW.VariableTimeDelay_IWORK_m.Tail+1) : 0);
        }

        (*uBuffer + rtDW.VariableTimeDelay_IWORK_m.CircularBufSize)
          [rtDW.VariableTimeDelay_IWORK_m.Head] = simTime;
        (*uBuffer)[rtDW.VariableTimeDelay_IWORK_m.Head] = 34.027571868896487;

        /* when use fixed buffer, reset solver at when buffer is updated
         * to avoid output consistency fail.
         */
      }
    }

    /* End of Update for SubSystem: '<S19>/Enabled Subsystem' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(rtM)) {
    rt_ertODEUpdateContinuousStates(&rtM->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++rtM->Timing.clockTick0;
    rtM->Timing.t[0] = rtsiGetSolverStopTime(&rtM->solverInfo);

    {
      /* Update absolute timer for sample time: [0.0066666666666666671s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.0066666666666666671, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      rtM->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void separetly_excited_DC_motor_derivatives(void)
{
  XDot *_rtXdot;
  _rtXdot = ((XDot *) rtM->derivs);

  /* Derivatives for S-Function (sfun_spid_contc): '<S10>/State-Space' incorporates:
   *  Constant: '<S21>/ddd'
   *  Constant: '<S23>/ddd'
   *  Constant: '<S25>/ddd'
   *  Constant: '<S27>/ddd'
   *  Constant: '<S32>/g'
   */
  /* Level2 S-Function Block: '<S10>/State-Space' (sfun_spid_contc) */
  {
    SimStruct *rts = rtM->childSfunctions[0];
    real_T *sfcndX_fx = (real_T *) &((XDot *) rtM->derivs)->StateSpace_CSTATE[0];
    ssSetdX(rts, sfcndX_fx);
    sfcnDerivatives(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Derivatives for TransferFcn: '<S2>/Transfer Fcn1' */
  _rtXdot->TransferFcn1_CSTATE = 0.0;
  _rtXdot->TransferFcn1_CSTATE += -0.002 * rtX.TransferFcn1_CSTATE;
  _rtXdot->TransferFcn1_CSTATE += rtDW.Sum1;

  /* Derivatives for TransferFcn: '<S2>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = 0.0;
  _rtXdot->TransferFcn_CSTATE += -5.0 * rtX.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += rtDW.Sum;
}

/* Model initialize function */
void separetly_excited_DC_motor_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&rtM->solverInfo, &rtM->Timing.simTimeStep);
    rtsiSetTPtr(&rtM->solverInfo, &rtmGetTPtr(rtM));
    rtsiSetStepSizePtr(&rtM->solverInfo, &rtM->Timing.stepSize0);
    rtsiSetdXPtr(&rtM->solverInfo, &rtM->derivs);
    rtsiSetContStatesPtr(&rtM->solverInfo, (real_T **) &rtM->contStates);
    rtsiSetNumContStatesPtr(&rtM->solverInfo, &rtM->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&rtM->solverInfo,
      &rtM->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&rtM->solverInfo,
      &rtM->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&rtM->solverInfo,
      &rtM->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&rtM->solverInfo, (&rtmGetErrorStatus(rtM)));
    rtsiSetRTModelPtr(&rtM->solverInfo, rtM);
  }

  rtsiSetSimTimeStep(&rtM->solverInfo, MAJOR_TIME_STEP);
  rtM->intgData.y = rtM->odeY;
  rtM->intgData.f[0] = rtM->odeF[0];
  rtM->intgData.f[1] = rtM->odeF[1];
  rtM->intgData.f[2] = rtM->odeF[2];
  rtM->contStates = ((X *) &rtX);
  rtsiSetSolverData(&rtM->solverInfo, (void *)&rtM->intgData);
  rtsiSetSolverName(&rtM->solverInfo,"ode3");
  rtM->solverInfoPtr = (&rtM->solverInfo);

  /* Initialize timing info */
  {
    int_T *mdlTsMap = rtM->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    rtM->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    rtM->Timing.sampleTimes = (&rtM->Timing.sampleTimesArray[0]);
    rtM->Timing.offsetTimes = (&rtM->Timing.offsetTimesArray[0]);

    /* task periods */
    rtM->Timing.sampleTimes[0] = (0.0);
    rtM->Timing.sampleTimes[1] = (0.0066666666666666671);

    /* task offsets */
    rtM->Timing.offsetTimes[0] = (0.0);
    rtM->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(rtM, &rtM->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = rtM->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    rtM->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(rtM, -1);
  rtM->Timing.stepSize0 = 0.0066666666666666671;
  rtM->solverInfoPtr = (&rtM->solverInfo);
  rtM->Timing.stepSize = (0.0066666666666666671);
  rtsiSetFixedStepSize(&rtM->solverInfo, 0.0066666666666666671);
  rtsiSetSolverMode(&rtM->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* child S-Function registration */
  {
    RTWSfcnInfo *sfcnInfo = &rtM->NonInlinedSFcns.sfcnInfo;
    rtM->sfcnInfo = (sfcnInfo);
    rtssSetErrorStatusPtr(sfcnInfo, (&rtmGetErrorStatus(rtM)));
    rtssSetNumRootSampTimesPtr(sfcnInfo, &rtM->Sizes.numSampTimes);
    rtM->NonInlinedSFcns.taskTimePtrs[0] = &(rtmGetTPtr(rtM)[0]);
    rtM->NonInlinedSFcns.taskTimePtrs[1] = &(rtmGetTPtr(rtM)[1]);
    rtssSetTPtrPtr(sfcnInfo,rtM->NonInlinedSFcns.taskTimePtrs);
    rtssSetTStartPtr(sfcnInfo, &rtmGetTStart(rtM));
    rtssSetTFinalPtr(sfcnInfo, &rtmGetTFinal(rtM));
    rtssSetTimeOfLastOutputPtr(sfcnInfo, &rtmGetTimeOfLastOutput(rtM));
    rtssSetStepSizePtr(sfcnInfo, &rtM->Timing.stepSize);
    rtssSetStopRequestedPtr(sfcnInfo, &rtmGetStopRequested(rtM));
    rtssSetDerivCacheNeedsResetPtr(sfcnInfo, &rtM->derivCacheNeedsReset);
    rtssSetZCCacheNeedsResetPtr(sfcnInfo, &rtM->zCCacheNeedsReset);
    rtssSetContTimeOutputInconsistentWithStateAtMajorStepPtr(sfcnInfo,
      &rtM->CTOutputIncnstWithState);
    rtssSetSampleHitsPtr(sfcnInfo, &rtM->Timing.sampleHits);
    rtssSetPerTaskSampleHitsPtr(sfcnInfo, &rtM->Timing.perTaskSampleHits);
    rtssSetSimModePtr(sfcnInfo, &rtM->simMode);
    rtssSetSolverInfoPtr(sfcnInfo, &rtM->solverInfoPtr);
  }

  rtM->Sizes.numSFcns = (1);

  /* register each child */
  {
    (void) memset((void *)&rtM->NonInlinedSFcns.childSFunctions[0], 0,
                  1*sizeof(SimStruct));
    rtM->childSfunctions = (&rtM->NonInlinedSFcns.childSFunctionPtrs[0]);
    rtM->childSfunctions[0] = (&rtM->NonInlinedSFcns.childSFunctions[0]);

    /* Level2 S-Function Block: separetly_excited_DC_motor/<S10>/State-Space (sfun_spid_contc) */
    {
      SimStruct *rts = rtM->childSfunctions[0];

      /* timing info */
      time_T *sfcnPeriod = rtM->NonInlinedSFcns.Sfcn0.sfcnPeriod;
      time_T *sfcnOffset = rtM->NonInlinedSFcns.Sfcn0.sfcnOffset;
      int_T *sfcnTsMap = rtM->NonInlinedSFcns.Sfcn0.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &rtM->NonInlinedSFcns.blkInfo2[0]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts, &rtM->
        NonInlinedSFcns.inputOutputPortInfo2[0]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, rtM->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &rtM->NonInlinedSFcns.methods2[0]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &rtM->NonInlinedSFcns.methods3[0]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &rtM->NonInlinedSFcns.methods4[0]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &rtM->NonInlinedSFcns.statesInfo2[0]);
        ssSetPeriodicStatesInfo(rts, &rtM->NonInlinedSFcns.periodicStatesInfo[0]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 2);
        ssSetPortInfoForInputs(rts, &rtM->NonInlinedSFcns.Sfcn0.inputPortInfo[0]);
        _ssSetPortInfo2ForInputUnits(rts,
          &rtM->NonInlinedSFcns.Sfcn0.inputPortUnits[0]);
        ssSetInputPortUnit(rts, 0, 0);
        ssSetInputPortUnit(rts, 1, 0);
        _ssSetPortInfo2ForInputCoSimAttribute(rts,
          &rtM->NonInlinedSFcns.Sfcn0.inputPortCoSimAttribute[0]);
        ssSetInputPortIsContinuousQuantity(rts, 0, 0);
        ssSetInputPortIsContinuousQuantity(rts, 1, 0);

        /* port 0 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &rtM->NonInlinedSFcns.Sfcn0.UPtrs0;
          sfcnUPtrs[0] = &rtDW.AC;
          sfcnUPtrs[1] = &rtConstP.pooled4;
          sfcnUPtrs[2] = &rtConstP.pooled4;
          sfcnUPtrs[3] = &rtConstP.pooled4;
          sfcnUPtrs[4] = &rtConstP.pooled4;
          ssSetInputPortSignalPtrs(rts, 0, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidth(rts, 0, 5);
        }

        /* port 1 */
        {
          real_T const **sfcnUPtrs = (real_T const **)
            &rtM->NonInlinedSFcns.Sfcn0.UPtrs1;
          sfcnUPtrs[0] = rtConstP.g_Value;
          sfcnUPtrs[1] = &rtConstP.g_Value[1];
          sfcnUPtrs[2] = &rtConstP.g_Value[2];
          sfcnUPtrs[3] = &rtConstP.g_Value[3];
          sfcnUPtrs[4] = &rtDW.VariableTimeDelay_c;
          sfcnUPtrs[5] = &rtDW.VariableTimeDelay;
          sfcnUPtrs[6] = &rtDW.VariableTimeDelay;
          sfcnUPtrs[7] = &rtDW.VariableTimeDelay_c;
          ssSetInputPortSignalPtrs(rts, 1, (InputPtrsType)&sfcnUPtrs[0]);
          _ssSetInputPortNumDimensions(rts, 1, 1);
          ssSetInputPortWidth(rts, 1, 8);
        }
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts, &rtM->NonInlinedSFcns.Sfcn0.outputPortInfo
          [0]);
        _ssSetNumOutputPorts(rts, 2);
        _ssSetPortInfo2ForOutputUnits(rts,
          &rtM->NonInlinedSFcns.Sfcn0.outputPortUnits[0]);
        ssSetOutputPortUnit(rts, 0, 0);
        ssSetOutputPortUnit(rts, 1, 0);
        _ssSetPortInfo2ForOutputCoSimAttribute(rts,
          &rtM->NonInlinedSFcns.Sfcn0.outputPortCoSimAttribute[0]);
        ssSetOutputPortIsContinuousQuantity(rts, 0, 0);
        ssSetOutputPortIsContinuousQuantity(rts, 1, 0);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidth(rts, 0, 3);
          ssSetOutputPortSignal(rts, 0, ((real_T *) rtDW.StateSpace_o1));
        }

        /* port 1 */
        {
          _ssSetOutputPortNumDimensions(rts, 1, 1);
          ssSetOutputPortWidth(rts, 1, 16);
          ssSetOutputPortSignal(rts, 1, ((real_T *) rtDW.StateSpace_o2));
        }
      }

      /* states */
      ssSetContStates(rts, &rtX.StateSpace_CSTATE[0]);

      /* path info */
      ssSetModelName(rts, "State-Space");
      ssSetPath(rts,
                "separetly_excited_DC_motor/powergui/EquivalentModel1/State-Space");
      ssSetRTModel(rts,rtM);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **) &rtM->NonInlinedSFcns.Sfcn0.params;
        ssSetSFcnParamsCount(rts, 10);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)rtConstP.StateSpace_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)rtConstP.StateSpace_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)rtConstP.StateSpace_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)rtConstP.StateSpace_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)rtConstP.StateSpace_P5_Size);
        ssSetSFcnParam(rts, 5, (mxArray*)rtConstP.StateSpace_P6_Size);
        ssSetSFcnParam(rts, 6, (mxArray*)rtConstP.StateSpace_P7_Size);
        ssSetSFcnParam(rts, 7, (mxArray*)rtConstP.StateSpace_P8_Size);
        ssSetSFcnParam(rts, 8, (mxArray*)rtConstP.StateSpace_P9_Size);
        ssSetSFcnParam(rts, 9, (mxArray*)rtConstP.StateSpace_P10_Size);
      }

      /* work vectors */
      ssSetRWork(rts, (real_T *) &rtDW.StateSpace_RWORK[0]);
      ssSetIWork(rts, (int_T *) &rtDW.StateSpace_IWORK[0]);
      ssSetPWork(rts, (void **) &rtDW.StateSpace_PWORK[0]);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &rtM->NonInlinedSFcns.Sfcn0.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &rtM->NonInlinedSFcns.Sfcn0.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 4);

        /* MODE */
        ssSetDWorkWidth(rts, 0, 9);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &rtDW.StateSpace_MODE[0]);

        /* RWORK */
        ssSetDWorkWidth(rts, 1, 2);
        ssSetDWorkDataType(rts, 1,SS_DOUBLE);
        ssSetDWorkComplexSignal(rts, 1, 0);
        ssSetDWork(rts, 1, &rtDW.StateSpace_RWORK[0]);

        /* IWORK */
        ssSetDWorkWidth(rts, 2, 23);
        ssSetDWorkDataType(rts, 2,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 2, 0);
        ssSetDWork(rts, 2, &rtDW.StateSpace_IWORK[0]);

        /* PWORK */
        ssSetDWorkWidth(rts, 3, 22);
        ssSetDWorkDataType(rts, 3,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 3, 0);
        ssSetDWork(rts, 3, &rtDW.StateSpace_PWORK[0]);
      }

      ssSetModeVector(rts, (int_T *) &rtDW.StateSpace_MODE[0]);

      /* registration */
      sfun_spid_contc(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.0);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 0;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCs(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetInputPortConnected(rts, 0, 1);
      _ssSetInputPortConnected(rts, 1, 1);
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortConnected(rts, 1, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);
      _ssSetOutputPortBeingMerged(rts, 1, 0);

      /* Update the BufferDstPort flags for each input port */
      ssSetInputPortBufferDstPort(rts, 0, -1);
      ssSetInputPortBufferDstPort(rts, 1, -1);
    }
  }

  /* Start for S-Function (sfun_spid_contc): '<S10>/State-Space' incorporates:
   *  Constant: '<S21>/ddd'
   *  Constant: '<S23>/ddd'
   *  Constant: '<S25>/ddd'
   *  Constant: '<S27>/ddd'
   *  Constant: '<S32>/g'
   */
  /* Level2 S-Function Block: '<S10>/State-Space' (sfun_spid_contc) */
  {
    SimStruct *rts = rtM->childSfunctions[0];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* InitializeConditions for S-Function (sfun_spid_contc): '<S10>/State-Space' incorporates:
   *  Constant: '<S21>/ddd'
   *  Constant: '<S23>/ddd'
   *  Constant: '<S25>/ddd'
   *  Constant: '<S27>/ddd'
   *  Constant: '<S32>/g'
   */
  /* Level2 S-Function Block: '<S10>/State-Space' (sfun_spid_contc) */
  {
    SimStruct *rts = rtM->childSfunctions[0];
    sfcnInitializeConditions(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* InitializeConditions for TransferFcn: '<S2>/Transfer Fcn1' */
  rtX.TransferFcn1_CSTATE = 0.0;

  /* InitializeConditions for S-Function (sdspcount2): '<S19>/Counter' */
  rtDW.Counter_ClkEphState = 5U;

  /* InitializeConditions for TransferFcn: '<S2>/Transfer Fcn' */
  rtX.TransferFcn_CSTATE = 0.0;

  /* SystemInitialize for Enabled SubSystem: '<S19>/Enabled Subsystem1' */

  /* Start for VariableTransportDelay: '<S30>/Variable Time Delay' */
  {
    real_T *pBuffer = &rtDW.VariableTimeDelay_RWORK.TUbufferArea[0];
    int_T j;
    rtDW.VariableTimeDelay_IWORK.Tail = 0;
    rtDW.VariableTimeDelay_IWORK.Head = 0;
    rtDW.VariableTimeDelay_IWORK.Last = 0;
    rtDW.VariableTimeDelay_IWORK.CircularBufSize = 1024;
    for (j=0; j < 1024; j++) {
      pBuffer[j] = 0.0;
      pBuffer[1024 + j] = rtM->Timing.t[0];
    }

    rtDW.VariableTimeDelay_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
  }

  /* End of SystemInitialize for SubSystem: '<S19>/Enabled Subsystem1' */

  /* SystemInitialize for Enabled SubSystem: '<S19>/Enabled Subsystem' */

  /* Start for VariableTransportDelay: '<S29>/Variable Time Delay' incorporates:
   *  Constant: '<S6>/firing angle'
   */
  {
    real_T *pBuffer = &rtDW.VariableTimeDelay_RWORK_o.TUbufferArea[0];
    int_T j;
    rtDW.VariableTimeDelay_IWORK_m.Tail = 0;
    rtDW.VariableTimeDelay_IWORK_m.Head = 0;
    rtDW.VariableTimeDelay_IWORK_m.Last = 0;
    rtDW.VariableTimeDelay_IWORK_m.CircularBufSize = 13312;
    for (j=0; j < 13312; j++) {
      pBuffer[j] = 0.0;
      pBuffer[13312 + j] = rtM->Timing.t[0];
    }

    rtDW.VariableTimeDelay_PWORK_o.TUbufferPtrs[0] = (void *) &pBuffer[0];
  }

  /* End of SystemInitialize for SubSystem: '<S19>/Enabled Subsystem' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
