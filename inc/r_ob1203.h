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
 * File Name    : r_ob1203.h
 * Version      : 1.0
 * Description  : This module provides a connection interface to OB1203 chip over I2C.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 15.01.2007 1.00     First Release
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

#ifndef _R_OB1203_H_
#define _R_OB1203_H_

#include <stddef.h>
#include <stdint.h>

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
typedef enum
{
	OB1203_PROXIMITY_SENSOR,
	OB1203_LIGHT_SENSOR,
	OB1203_PPG_SENSOR_MODE0,
	OB1203_PPG_SENSOR_MODE1,
}e_ob1203_mode_t;

typedef e_ob1203_mode_t ob1203_mode_t;
 
typedef enum
{
	/** All OK */
	OB1203_OK,
	
	/** Insufficient memory buffer */
	OB1203_INSUFFICIENT_MEMORY,
	
	/** I2C Bus is busy */
	OB1203_I2C_BUSY,
	
	/** Invalid bit set */
	OB1203_INVALID_SETTING,
}e_ob1203_api_status_t;

typedef e_ob1203_api_status_t api_status_t;
 
 
typedef enum
{
    /**  Power-on status, LS interrupt and LS data status    */
    STATUS_0 = 0x00,

    /**  PPG/PS data status, PS/PPG interrupt status */
    STATUS_1 = 0x01,

    /**  PS measurement data, LSB    */
    PS_DATA_0 = 0x02,

    /**  PS measurement data, MSB    */
    PS_DATA_1 = 0x03,

    /**  LS Clear measurement data, LSB  */
    LS_CLEAR_DATA_0 = 0x04,

    /**  LS Clear measurement data intervening bits  */
    LS_CLEAR_DATA_1 = 0x05,

    /**  LS Clear measurement data, MSB  */
    LS_CLEAR_DATA_2 = 0x06,

    /**  LS Green/LS measurement data, LSB   */
    LS_GREEN_DATA_0 = 0x07,

    /**  LS Green/LS measurement data intervening bits   */
    LS_GREEN_DATA_1 = 0x08,

    /**  LS Green/LS measurement data, MSB   */
    LS_GREEN_DATA_2 = 0x09,

    /**  LS Blue measurement data, LSB   */
    LS_BLUE_DATA_0 = 0x0A,

    /**  LS Blue measurement data intervening bits   */
    LS_BLUE_DATA_1 = 0x0B,

    /**  LS Blue measurement data, MSB   */
    LS_BLUE_DATA_2 = 0x0C,

    /**  LS Red measurement data, LSB    */
    LS_RED_DATA_0 = 0x0D,

    /**  LS Red measurement data intervening bits    */
    LS_RED_DATA_1 = 0x0E,

    /**  LS Red measurement data, MSB    */
    LS_RED_DATA_2 = 0x0F,

    /**  LS Comp measurement data, LSB   */
    COMP_DATA_0 = 0x10,

    /**  LS Comp measurement data intervening bits   */
    COMP_DATA_1 = 0x11,

    /**  LS Comp measurement data, MSB   */
    COMP_DATA_2 = 0x12,

} e_ob1203_read_only_registers_t;

typedef enum
{

    /**  LS operation mode control, software (SW) reset  */
    MAIN_CTRL_0 = 0x15,

    /**  PPG/PS operation mode control   */
    MAIN_CTRL_1 = 0x16,

    /**  PS LED current, LSB */
    PS_LED_CURR_0 = 0x17,

    /**  PS LED current, MSB */
    PS_LED_CURR_1 = 0x18,

    /**  PS analog cancellation level and pulse setting  */
    PS_CAN_PULSES = 0x19,

    /**  PS pulse width and measurement period   */
    PS_PWIDTH_PERIOD = 0x1A,

    /**  PS digital cancellation level setting, LSB  */
    PS_CAN_DIG_0 = 0x1B,

    /**  PS digital cancellation level setting, MSB  */
    PS_CAN_DIG_1 = 0x1C,

    /**  PS moving average and hysteresis configuration  */
    PS_MOV_AVG_HYS = 0x1D,

    /**  PS interrupt upper threshold, LSB   */
    PS_THRES_UP_0 = 0x1E,

    /**  PS interrupt upper threshold, MSB   */
    PS_THRES_UP_1 = 0x1F,

    /**  PS interrupt lower threshold, LSB   */
    PS_THRES_LOW_0 = 0x20,

    /**  PS interrupt lower threshold, MSB   */
    PS_THRES_LOW_1 = 0x21,

    /**  LS resolution and measurement period setting    */
    LS_RES_PERIOD = 0x22,

    /**  LS analog gain range setting    */
    LS_GAIN = 0x23,

    /**  LS interrupt upper threshold, LSB   */
    LS_THRES_UP_0 = 0x24,

    /**  LS interrupt upper threshold, intervening bits  */
    LS_THRES_UP_1 = 0x25,

    /**  LS interrupt upper threshold, MSB   */
    LS_THRES_UP_2 = 0x26,

    /**  LS interrupt lower threshold, LSB   */
    LS_THRES_LOW_0 = 0x27,

    /**  LS interrupt lower threshold, intervening bits  */
    LS_THRES_LOW_1 = 0x28,

    /**  LS interrupt lower threshold, MSB   */
    LS_THRES_LOW_2 = 0x29,

    /**  LS interrupt variance threshold */
    LS_THRES_VAR = 0x2A,

    /**  LS interrupt configuration  */
    INT_CFG_0 = 0x2B,

    /**  PS/PPG interrupt configuration  */
    INT_CFG_1 = 0x2C,

    /**  LS/PS interrupt persist setting */
    INT_PST = 0x2D,

    /**  PPG/PS gain setting */
    PPG_PS_GAIN = 0x2E,

    /**  PPG power save and LED flip setting */
    PPG_PS_CFG = 0x2F,

    /**  PPG IR LED current, LSB */
    PPG_IRLED_CURR_0 = 0x30,

    /**  PPG IR LED current, MSB */
    PPG_IRLED_CURR_1 = 0x31,

    /**  PPG Red LED current, LSB    */
    PPG_RLED_CURR_0 = 0x32,

    /**  PPG Red LED current, MSB    */
    PPG_RLED_CURR_1 = 0x33,

    /**  PPG analog cancellation value   */
    PPG_CAN_ANA = 0x34,

    /**  Number of averaged PPG samples  */
    PPG_AVG = 0x35,

    /**  PPG pulse width and measurement period  */
    PPG_PWIDTH_PERIOD = 0x36,

    /**  FIFO roll over and almost full configuration */
    FIFO_CFG = 0x37,
	
    /**  FIFO write pointer  */
    FIFO_WR_PTR = 0x38,

    /**  FIFO read pointer   */
    FIFO_RD_PTR = 0x39,

    /**  FIFO overflow counter   */
    FIFO_OVF_CNT = 0x3A,

} e_ob1203_read_write_registers_t;



/***********************************************************************************************************************
 Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
api_status_t get_buffer_sizes	  (size_t const * p_read, size_t const * p_write);
api_status_t set_read_buffer      (uint8_t const * p_data, size_t buffer_size);
api_status_t set_write_buffer     (uint8_t const * p_data, size_t buffer_size);
api_status_t set_ob1203_address	  (uint8_t const addr);

/**
 * Core Get Functions
 */
 
api_status_t get_status           (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ps_data          (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ls_clear_data    (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ls_green_data    (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ls_blue_data     (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ls_red_data      (uint8_t const * p_data, size_t buffer_size);
api_status_t get_comp_data        (uint8_t const * p_data, size_t buffer_size);
api_status_t get_main_ctrl        (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ps_led_curr      (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ps_can_pulses    (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ps_pwidth_period (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ps_can_dig       (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ps_mov_avg_hys   (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ps_thres_up      (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ps_thres_low     (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ls_res_period    (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ls_gain          (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ls_thres_up      (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ls_thres_low     (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ls_thres_var     (uint8_t const * p_data, size_t buffer_size);
api_status_t get_int_cfg          (uint8_t const * p_data, size_t buffer_size);
api_status_t get_int_pst          (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ppg_ps_gain      (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ppg_ps_cfg       (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ppg_irled_curr   (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ppg_rled_curr    (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ppg_can_ana      (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ppg_avg          (uint8_t const * p_data, size_t buffer_size);
api_status_t get_ppg_pwidth_period(uint8_t const * p_data, size_t buffer_size);
api_status_t get_fifo_cfg         (uint8_t const * p_data, size_t buffer_size);
api_status_t get_fifo_wr_ptr      (uint8_t const * p_data, size_t buffer_size);
api_status_t get_fifo_rd_ptr      (uint8_t const * p_data, size_t buffer_size);
api_status_t get_fifo_ovf_cnt     (uint8_t const * p_data, size_t buffer_size);
api_status_t get_fifo_cfg		  (uint8_t const * p_data, size_t buffer_size);

/**
 * Core Set Functions
 */
 
api_status_t set_main_ctrl        (uint8_t const * p_data, size_t buffer_size);
api_status_t set_ps_led_curr      (uint8_t const * p_data, size_t buffer_size);
api_status_t set_ps_can_pulses    (uint8_t const * p_data, size_t buffer_size);
api_status_t set_ps_pwidth_period (uint8_t const * p_data, size_t buffer_size);
api_status_t set_ps_can_dig       (uint8_t const * p_data, size_t buffer_size);
api_status_t set_ps_mov_avg_hys   (uint8_t const * p_data, size_t buffer_size);
api_status_t set_ps_thres_up      (uint8_t const * p_data, size_t buffer_size);
api_status_t set_ps_thres_low     (uint8_t const * p_data, size_t buffer_size);
api_status_t set_ls_res_period    (uint8_t const * p_data, size_t buffer_size);
api_status_t set_ls_gain          (uint8_t const * p_data, size_t buffer_size);
api_status_t set_ls_thres_up      (uint8_t const * p_data, size_t buffer_size);
api_status_t set_ls_thres_low     (uint8_t const * p_data, size_t buffer_size);
api_status_t set_ls_thres_var     (uint8_t const * p_data, size_t buffer_size);
api_status_t set_int_cfg          (uint8_t const * p_data, size_t buffer_size);
api_status_t set_int_pst          (uint8_t const * p_data, size_t buffer_size);
api_status_t set_ppg_ps_gain      (uint8_t const * p_data, size_t buffer_size);
api_status_t set_ppg_ps_cfg       (uint8_t const * p_data, size_t buffer_size);
api_status_t set_ppg_irled_curr   (uint8_t const * p_data, size_t buffer_size);
api_status_t set_ppg_rled_curr    (uint8_t const * p_data, size_t buffer_size);
api_status_t set_ppg_can_ana      (uint8_t const * p_data, size_t buffer_size);
api_status_t set_ppg_avg          (uint8_t const * p_data, size_t buffer_size);
api_status_t set_ppg_pwidth_period(uint8_t const * p_data, size_t buffer_size);
api_status_t set_fifo_cfg         (uint8_t const * p_data, size_t buffer_size);
api_status_t set_fifo_wr_ptr      (uint8_t const * p_data, size_t buffer_size);
api_status_t set_fifo_rd_ptr      (uint8_t const * p_data, size_t buffer_size);
api_status_t set_fifo_ovf_cnt     (uint8_t const * p_data, size_t buffer_size);


#endif /* _R_OB1203_H_ */
