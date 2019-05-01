/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2019 Renesas Electronics Corporation. All rights reserved.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_ob1203.c
 * Version      : 1.0 <- Optional as long as history is shown below
 * Description  : This module solves all the world's problems
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 15.01.2007 1.00     First Release
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_ob1203.h"
/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
#define OB1203_MAX_FIFO_DEPTH_IN_BYTES      UINT8_C(96)
 
#define BIT_MASK_STATUS_0           (0x83)
#define BIT_MASK_STATUS_1           (0xF7)
#define BIT_MASK_PS_DATA_0          (0xFF)
#define BIT_MASK_PS_DATA_1          (0xFF)
#define BIT_MASK_LS_CLEAR_DATA_0    (0xFF)
#define BIT_MASK_LS_CLEAR_DATA_1    (0xFF)
#define BIT_MASK_LS_CLEAR_DATA_2    (0x0F)
#define BIT_MASK_LS_GREEN_DATA_0    (0xFF)
#define BIT_MASK_LS_GREEN_DATA_1    (0xFF)
#define BIT_MASK_LS_GREEN_DATA_2    (0x0F)
#define BIT_MASK_LS_BLUE_DATA_0     (0xFF)
#define BIT_MASK_LS_BLUE_DATA_1     (0xFF)
#define BIT_MASK_LS_BLUE_DATA_2     (0x0F)
#define BIT_MASK_LS_RED_DATA_0      (0xFF)
#define BIT_MASK_LS_RED_DATA_1      (0xFF)
#define BIT_MASK_LS_RED_DATA_2      (0x0F)
#define BIT_MASK_COMP_DATA_0        (0xFF)
#define BIT_MASK_COMP_DATA_1        (0xFF)
#define BIT_MASK_COMP_DATA_2        (0x0F)

#define BIT_MASK_MAIN_CTRL_0        (0x8B)
#define BIT_MASK_MAIN_CTRL_1        (0x0F)
#define BIT_MASK_PS_LED_CURR_0      (0xFF)
#define BIT_MASK_PS_LED_CURR_1      (0x03)
#define BIT_MASK_PS_CAN_PULSES      (0x78)
#define BIT_MASK_PS_PWIDTH_PERIOD   (0x37)
#define BIT_MASK_PS_CAN_DIG_0       (0xFF)
#define BIT_MASK_PS_CAN_DIG_1       (0xFF)
#define BIT_MASK_PS_MOV_AVG_HYS     (0xFF)
#define BIT_MASK_PS_THRES_UP_0      (0xFF)
#define BIT_MASK_PS_THRES_UP_1      (0xFF)
#define BIT_MASK_PS_THRES_LOW_0     (0xFF)
#define BIT_MASK_PS_THRES_LOW_1     (0xFF)
#define BIT_MASK_LS_RES_PERIOD      (0x77)
#define BIT_MASK_LS_GAIN            (0x03)
#define BIT_MASK_LS_THRES_UP_0      (0xFF)
#define BIT_MASK_LS_THRES_UP_1      (0xFF)
#define BIT_MASK_LS_THRES_UP_2      (0x0F)
#define BIT_MASK_LS_THRES_LOW_0     (0xFF)
#define BIT_MASK_LS_THRES_LOW_1     (0xFF)
#define BIT_MASK_LS_THRES_LOW_2     (0x0F)
#define BIT_MASK_LS_THRES_VAR       (0x07)
#define BIT_MASK_INT_CFG_0          (0x33)
#define BIT_MASK_INT_CFG_1          (0x33)
#define BIT_MASK_INT_PST            (0xFF)
#define BIT_MASK_PPG_PS_GAIN        (0x30)
#define BIT_MASK_PPG_PS_CFG         (0x48)
#define BIT_MASK_PPG_IRLED_CURR_0   (0xFF)
#define BIT_MASK_PPG_IRLED_CURR_1   (0x03)
#define BIT_MASK_PPG_RLED_CURR_0    (0xFF)
#define BIT_MASK_PPG_RLED_CURR_1    (0x01)
#define BIT_MASK_PPG_CAN_ANA        (0x05)
#define BIT_MASK_PPG_AVG            (0x7A)
#define BIT_MASK_PPG_PWIDTH_PERIOD  (0x77)
#define BIT_MASK_FIFO_CFG           (0x1F)
#define BIT_MASK_FIFO_WR_PTR        (0x1F)
#define BIT_MASK_FIFO_RD_PTR        (0x1F)
#define BIT_MASK_FIFO_OVF_CNT       (0x0F)


/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/

const uint8_t bit_mask[] =
{
  /* Read Only Registers */
  [ STATUS_0 ] = BIT_MASK_STATUS_0,
  [ STATUS_1 ] = BIT_MASK_STATUS_1,
  [ PS_DATA_0 ] = BIT_MASK_PS_DATA_0,
  [ PS_DATA_1 ] = BIT_MASK_PS_DATA_1,
  [ LS_CLEAR_DATA_0 ] = BIT_MASK_LS_CLEAR_DATA_0,
  [ LS_CLEAR_DATA_1 ] = BIT_MASK_LS_CLEAR_DATA_1,
  [ LS_CLEAR_DATA_2 ] = BIT_MASK_LS_CLEAR_DATA_2,
  [ LS_GREEN_DATA_0 ] = BIT_MASK_LS_GREEN_DATA_0,
  [ LS_GREEN_DATA_1 ] = BIT_MASK_LS_GREEN_DATA_1,
  [ LS_GREEN_DATA_2 ] = BIT_MASK_LS_GREEN_DATA_2,
  [ LS_BLUE_DATA_0 ] = BIT_MASK_LS_BLUE_DATA_0,
  [ LS_BLUE_DATA_1 ] = BIT_MASK_LS_BLUE_DATA_1,
  [ LS_BLUE_DATA_2 ] = BIT_MASK_LS_BLUE_DATA_2,
  [ LS_RED_DATA_0 ] = BIT_MASK_LS_RED_DATA_0,
  [ LS_RED_DATA_1 ] = BIT_MASK_LS_RED_DATA_1,
  [ LS_RED_DATA_2 ] = BIT_MASK_LS_RED_DATA_2,
  [ COMP_DATA_0 ] = BIT_MASK_COMP_DATA_0,
  [ COMP_DATA_1 ] = BIT_MASK_COMP_DATA_1,
  [ COMP_DATA_2 ] = BIT_MASK_COMP_DATA_2,

  /* Read write registers */
  [ MAIN_CTRL_0 ] = BIT_MASK_MAIN_CTRL_0,
  [ MAIN_CTRL_1 ] = BIT_MASK_MAIN_CTRL_1,
  [ PS_LED_CURR_0 ] = BIT_MASK_PS_LED_CURR_0,
  [ PS_LED_CURR_1 ] = BIT_MASK_PS_LED_CURR_1,
  [ PS_CAN_PULSES ] = BIT_MASK_PS_CAN_PULSES,
  [ PS_PWIDTH_PERIOD ] = BIT_MASK_PS_PWIDTH_PERIOD,
  [ PS_CAN_DIG_0 ] = BIT_MASK_PS_CAN_DIG_0,
  [ PS_CAN_DIG_1 ] = BIT_MASK_PS_CAN_DIG_1,
  [ PS_MOV_AVG_HYS ] = BIT_MASK_PS_MOV_AVG_HYS,
  [ PS_THRES_UP_0 ] = BIT_MASK_PS_THRES_UP_0,
  [ PS_THRES_UP_1 ] = BIT_MASK_PS_THRES_UP_1,
  [ PS_THRES_LOW_0 ] = BIT_MASK_PS_THRES_LOW_0,
  [ PS_THRES_LOW_1 ] = BIT_MASK_PS_THRES_LOW_1,
  [ LS_RES_PERIOD ] = BIT_MASK_LS_RES_PERIOD,
  [ LS_GAIN ] = BIT_MASK_LS_GAIN,
  [ LS_THRES_UP_0 ] = BIT_MASK_LS_THRES_UP_0,
  [ LS_THRES_UP_1 ] = BIT_MASK_LS_THRES_UP_1,
  [ LS_THRES_UP_2 ] = BIT_MASK_LS_THRES_UP_2,
  [ LS_THRES_LOW_0 ] = BIT_MASK_LS_THRES_LOW_0,
  [ LS_THRES_LOW_1 ] = BIT_MASK_LS_THRES_LOW_1,
  [ LS_THRES_LOW_2 ] = BIT_MASK_LS_THRES_LOW_2,
  [ LS_THRES_VAR ] = BIT_MASK_LS_THRES_VAR,
  [ INT_CFG_0 ] = BIT_MASK_INT_CFG_0,
  [ INT_CFG_1 ] = BIT_MASK_INT_CFG_1,
  [ INT_PST ] = BIT_MASK_INT_PST,
  [ PPG_PS_GAIN ] = BIT_MASK_PPG_PS_GAIN,
  [ PPG_PS_CFG ] = BIT_MASK_PPG_PS_CFG,
  [ PPG_IRLED_CURR_0 ] = BIT_MASK_PPG_IRLED_CURR_0,
  [ PPG_IRLED_CURR_1 ] = BIT_MASK_PPG_IRLED_CURR_1,
  [ PPG_RLED_CURR_0 ] = BIT_MASK_PPG_RLED_CURR_0,
  [ PPG_RLED_CURR_1 ] = BIT_MASK_PPG_RLED_CURR_1,
  [ PPG_CAN_ANA ] = BIT_MASK_PPG_CAN_ANA,
  [ PPG_AVG ] = BIT_MASK_PPG_AVG,
  [ PPG_PWIDTH_PERIOD ] = BIT_MASK_PPG_PWIDTH_PERIOD,
  [ FIFO_CFG ] = BIT_MASK_FIFO_CFG,
  [ FIFO_WR_PTR ] = BIT_MASK_FIFO_WR_PTR,
  [ FIFO_RD_PTR ] = BIT_MASK_FIFO_RD_PTR,
  [ FIFO_OVF_CNT ] = BIT_MASK_FIFO_OVF_CNT,

};

/***********************************************************************************************************************
 * Function Name: R_EXAMPLE_FooBar
 * Description  : Does an example task. Making this longer just to see how it wraps. Making this long just to see how it
 *                wraps.
 * Arguments    : index - 
 *                    Where to start looking
 *                p_output - 
 *                    Pointer of where to put the output data
 * Return Value : count - 
 *                    How many entries were found
 **********************************************************************************************************************/

/* End of function R_EXAMPLE_FooBar() */
