#include "lightControllSM.h"
#include "lightControll.h"
#include <stdbool.h>

/* Create the machine state data */
stateMachine smLightControll;

/*
* State Machine execution
*/
void stateMachine_execute(stateMachine *stateMachine)
{
    switch (stateMachine->current_state) 
    {
        case ManualMode:
            if(get_terminal_status() == t_Mode) 
            {           
                stateMachine->current_state = Dimmer;
            }
            else if(get_terminal_status() == t_Lock)
            {       
                set_ext_input_status(Locked);
            }
            else if(get_terminal_status() == t_Unlock)
            {     
                set_ext_input_status(Unlocked);
            }
            else
            {
                if((get_terminal_status() == t_On_Off) || ((get_ext_input_status() == Unlocked) && (get_button_status().On_Off == b_Pressed)))
                {
                    if(get_intensity_value() > get_min_intensity_value())
                    {       
                        set_intensity_value(get_min_intensity_value());
                    }
                    else
                    {                                                        
                        set_intensity_value(get_max_intensity_value());
                    }
                }     
            }
            set_button_wait_mode('o');                                                        
            set_terminal_wait_mode();
            break;
        case Dimmer:

            if(get_intensity_value() < get_min_intensity_value())
            {
                set_intensity_value(get_min_intensity_value());
            }
            else if(get_intensity_value() > get_max_intensity_value())
            {
                set_intensity_value(get_max_intensity_value());
            }

            if(get_terminal_status() == t_Mode) 
            {           
                stateMachine->current_state = AutomaticSwitch;
            }
            else if(get_terminal_status() == t_Lock)
            {       
                set_ext_input_status(Locked);
            }
            else if(get_terminal_status() == t_Unlock)
            {     
                set_ext_input_status(Unlocked);
            }
            else
            {
                if((get_terminal_status() == t_On_Off) || ((get_ext_input_status() == Unlocked) && (get_button_status().On_Off == b_Pressed)))
                {
                    if(get_intensity_value() > get_min_intensity_value())
                    {
                        set_intensity_stored_value(get_intensity_value());
                        set_intensity_value(get_min_intensity_value());
                    }
                    else 
                    {
                        if(get_intensity_stored_value() < get_min_intensity_value())
                        {
                            set_intensity_value(get_min_intensity_value()); 
                        }
                        else if(get_intensity_stored_value() > get_max_intensity_value())
                        {
                            set_intensity_value(get_max_intensity_value()); 
                        }
                        else
                        {
                            set_intensity_value(get_intensity_stored_value()); 
                        }
                    }                                                      
                }                
                else 
                {
                    if((get_terminal_status() == t_More_intensity) || ((get_ext_input_status() == Unlocked) && (get_button_status().More_intensity == b_Pressed)))
                    {
                        if ((get_intensity_value() + 10) <= get_max_intensity_value())
                        {         
                            set_intensity_value(get_intensity_value()+10);
                            set_intensity_stored_value(get_intensity_value());
                        }
                        else if(get_intensity_value() > get_max_intensity_value())
                        {
                            set_intensity_value(get_max_intensity_value());
                            set_intensity_stored_value(get_intensity_value());
                        }

                    } 
                    if((get_terminal_status() == t_Less_intensity) || ((get_ext_input_status() == Unlocked) && (get_button_status().Less_intensity == b_Pressed)))
                    {
                        if ((int)(get_intensity_value() - 10) >= (int) get_min_intensity_value()) 
                        {           
                            set_intensity_value(get_intensity_value()-10);
                            set_intensity_stored_value(get_intensity_value());
                        }
                        else if(get_intensity_value() > get_min_intensity_value())
                        {
                            set_intensity_value(get_min_intensity_value());
                            set_intensity_stored_value(get_intensity_value());
                        }
                    }      
                }         
            }
            set_button_wait_mode('o');
            set_button_wait_mode('m');
            set_button_wait_mode('l');
            set_terminal_wait_mode();   
            break;
        case AutomaticSwitch:
            if(get_terminal_status() == t_Mode) 
            {           
                stateMachine->current_state = AutomaticAjust;
            }
            if(get_LDR_value() > get_LDR_on_value())
            {
                set_intensity_value(get_max_intensity_value());  
            }
            else
            {
                set_intensity_value(get_min_intensity_value());  
            }          
            set_terminal_wait_mode();   
            break;
        case AutomaticAjust:
            if(get_terminal_status() == t_Mode) 
            {           
                stateMachine->current_state = ManualMode;
            }
            if(get_LDR_value() > get_LDR_on_value()+100 && get_intensity_value() < get_max_intensity_value())
            {
                set_intensity_value(get_intensity_value()+1);  
            }
            else if(get_LDR_value() < get_LDR_on_value()-100 && get_intensity_value() > get_min_intensity_value())
            {
                set_intensity_value(get_intensity_value()-1);  
            }
            set_terminal_wait_mode();              
            break;
    }
}

/*
* Initiate the State Machine
*/
void stateMachine_init(stateMachine *stateMachine)
{
    stateMachine->initial_state = ManualMode;
    stateMachine->current_state = stateMachine->initial_state;
}

/*
* Return current state from the State Machine
*/
uint32_t get_current_state(stateMachine *stateMachine)
{
	return stateMachine->current_state;
}