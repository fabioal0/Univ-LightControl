#include "lightControll.h"

/* System state variables */
buttons_status ButtonStatus;
terminal_status TerminalStatus;
ext_input_status ExtInputStatus;
uint32_t Intensity_Stored_Value;
uint32_t Intensity_Value;
uint32_t Min_Intensity;
uint32_t Max_Intensity;
uint32_t LDR_Led_On_Value;
uint32_t LDR_Value;

void set_intensity_stored_value(uint32_t number){
	Intensity_Stored_Value = number;
	return;
} 

void set_intensity_value(uint32_t number){
	Intensity_Value = number;
	return;
} 

void set_min_intensity(uint32_t number){
	Min_Intensity = number;
	return;
}

void set_max_intensity(uint32_t number){
	Max_Intensity = number;
	return;
}

void set_LDR_on_value(uint32_t number){
	LDR_Led_On_Value = number;
	return;
}

void set_ext_input_status(ext_input_status status)
{
	ExtInputStatus = status;
	return;
}

void set_button_wait_mode(char button)
{
	if( button == 'o') ButtonStatus.On_Off = b_Wait;
	else if( button == 'l') ButtonStatus.Less_intensity = b_Wait;
	else if( button == 'm') ButtonStatus.More_intensity = b_Wait;
}

void set_terminal_wait_mode(){
	TerminalStatus = t_Wait;
	return;
}

buttons_status get_button_status(void)
{
	return ButtonStatus;
}

ext_input_status get_ext_input_status(void)
{
	return ExtInputStatus;
}

terminal_status get_terminal_status(void)
{
	return TerminalStatus;
}

uint32_t get_intensity_stored_value(void)
{
	return Intensity_Stored_Value;
}

uint32_t get_intensity_value(void)
{
	return Intensity_Value;
}

uint32_t get_min_intensity_value(void)
{
	return Min_Intensity;
}

uint32_t get_max_intensity_value(void)
{
	return Max_Intensity;
}

uint32_t get_LDR_on_value(void)
{
	return LDR_Led_On_Value;
}

uint32_t get_LDR_value(void)
{
	return LDR_Value;
}