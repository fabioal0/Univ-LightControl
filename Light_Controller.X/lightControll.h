/**
 * \file: lightControll.h
 *
 * \brief Simulation of the light controll system.
 *
 *
 */
#pragma once

#include <stdint.h>

/******************************************************************
*
* Data types definitions
*
******************************************************************/

/**
* External inputs status (locked/unlocked)
*
*/
typedef enum{
    Unlocked,           /**< External inputs change the system */
    Locked              /**< External inputs dont change the system */
} ext_input_status;

/**
* Button status (wait/pressed)
*
*/
typedef enum{
    b_Wait,             /**< Waiting for push button interrupt */
    b_Pressed           /**< Button pushed */
} button_status;

/**
* Buttons status
*
*/
typedef struct ButtonStatus
{
	button_status On_Off;           /**< On/off button status */
	button_status Less_intensity;   /**< Less intensity button status */
	button_status More_intensity;   /**< More intensity button status */

} buttons_status;

/**
* Terminal events
*
*/
typedef enum{
    t_Wait,                 /**< Waiting for terminal input interrupt */
    t_Lock,                 /**< Lock external inputs */
    t_Unlock,               /**< Unock external inputs */
    t_On_Off,               /**< Turn on/off the led */
    t_More_intensity,       /**< Increase led intensity */
    t_Less_intensity,       /**< Decrease led intensity */
    t_Min_Intensity,        /**< Set min led intensity */
    t_Max_Intensity,        /**< Set max led intensity */
    t_LDR_Led_On_Value,     /**< Set on value or value to mantain */
    t_Mode                  /**< Change to next working mode */
} terminal_status;

/**********************************************************************
*
* Functions to interact with the physical system.
*
**********************************************************************/

/**
* \brief Save the intensity value to be used to turn on the led with the last intensity.
*
* \param number Intensity value.
*
*/
void set_intensity_stored_value(uint32_t number);

/**
* \brief Change the intensity value that the led shows.
*
* \param number Intensity value.
*
*/
void set_intensity_value(uint32_t number);

/**
* \brief Set the minimum led intensity that can be displayed.
*
* \param number Minimum led intensity.
*
*/
void set_min_intensity(uint32_t number);

/**
* \brief Set the maximum led intensity that can be displayed.
*
* \param number Maximum led intensity.
*
*/
void set_max_intensity(uint32_t number);

/**
* \brief Set the LDR value that turn on the led in the 3 mode or LDR value to mantain in the 4 mode.
*
* \param number LDR value.
*
*/
void set_LDR_on_value(uint32_t number);

/**
* \brief Set the external inputs status. If locked external inputs are ignored.
*
* \param ext_input_status External inputs status.
*
*/
void set_ext_input_status(ext_input_status status);

/**
* \brief Put the button selected in wait state. 
*
* \param button Select the button.
*
*/
void set_button_wait_mode(char button);

/**
* \brief Put terminal events in wait state.
*
*/
void set_terminal_wait_mode();

/**
* \brief Get button status.
*/
buttons_status get_button_status(void);

/**
* \brief Get external input status.
*/
ext_input_status get_ext_input_status(void);

/**
* \brief Get terminal status.
*/
terminal_status get_terminal_status(void);

/**
* \brief Get intensity stored value.
*/
uint32_t get_intensity_stored_value(void);

/**
* \brief Get intensity value.
*/
uint32_t get_intensity_value(void);

/**
* \brief Get min intensity value.
*/
uint32_t get_min_intensity_value(void);

/**
* \brief Get max intensity value.
*/
uint32_t get_max_intensity_value(void);

/**
* \brief Get LDR on value.
*/
uint32_t get_LDR_on_value(void);

/**
* \brief Get LDR value.
*/
uint32_t get_LDR_value(void);

/* System state variables */
extern buttons_status ButtonStatus;
extern terminal_status TerminalStatus;
extern ext_input_status ExtInputStatus;
extern uint32_t Intensity_Stored_Value;
extern uint32_t Intensity_Value;
extern uint32_t Min_Intensity;
extern uint32_t Max_Intensity;
extern uint32_t LDR_Led_On_Value;
extern uint32_t LDR_Value;