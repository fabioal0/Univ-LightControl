#include "lightControllSM.h"
#include "lightControll.h"
#include <stdbool.h>
#include <stdio.h>

uint8_t letter = ' ';

void init(void){
    ButtonStatus.On_Off = b_Wait;
    ButtonStatus.Less_intensity = b_Wait;
    ButtonStatus.More_intensity = b_Wait;
    ExtInputStatus = Unlocked;
    TerminalStatus = t_Wait;
    Intensity_Value = 0;
    Min_Intensity = 0;
    Max_Intensity = 100;
    LDR_Led_On_Value = 15;
    LDR_Value = 0;
    stateMachine_init(&smLightControll);
}

int main(void){

    // Create Auxiliar Varibles
    uint32_t number = 0;
    uint32_t cnt = 0;
    uint8_t message[250];

    // Create Emulator Variables
    bool finish = false;

    // Initiate State Machine
    init();

    // Display UI Instructions
    sprintf(message,"Buttons:\tp (On/Off)\t\t+ (More Intensity)\t- (Less Intensity)\r\nTerminal:\to (On/Off)\t\t> (More Intensity)\t< (Less Intensity)\n\r\t\tl (lock)\t\tu (unlock)\t\tw (Set Max Intensity)\n\r\t\ts (Set Min Intensity)\tg (Set LDR On Value)\tm (Change Mode)\r\n\n");
        
    for(cnt=0;cnt<231;cnt++)
    {
        printf("%c", message[cnt]);
    }
    
    // Run
    while(!finish)
    {
        // Emulate LDR Value
        LDR_Value = 3300 - Intensity_Value*33;

        // Emulate UART Input
        letter = getchar();

        // Process Input
        if(letter != ' ')
        {
            // Register User Action
            switch (letter)
            {
                case 'p':
                    ButtonStatus.On_Off = b_Pressed;
                    break;
                case '+':
                    ButtonStatus.More_intensity = b_Pressed;
                    break;
                case '-':
                    ButtonStatus.Less_intensity = b_Pressed;
                    break;
                case 'o':
                    TerminalStatus = t_On_Off;
                    break;
                case 'l':
                    TerminalStatus = t_Lock;
                    break;
                case 'u':
                    TerminalStatus = t_Unlock;
                    break;
                case '>':
                    TerminalStatus = t_More_intensity;
                    break;
                case '<':
                    TerminalStatus = t_Less_intensity;
                    break;
                case 'm':
                    TerminalStatus = t_Mode;
                    break;
                case 'w':
                    if(number >= Min_Intensity && number <= 100)
                    {
                        Max_Intensity = number;
                    }
                    number = 0;
                    break;
                case 's':
                    if(number <= Max_Intensity && number >= 0)
                    {
                        Min_Intensity = number;
                    }
                    number = 0;
                    break;
                case 'g':
                    if(number >= 0)
                    {
                        LDR_Led_On_Value = number;
                    }
                    number = 0;
                    break;
                case 'c':   number = 0;             break;
                case '0':   number = number*10 + 0; break;
                case '1':   number = number*10 + 1; break;
                case '2':   number = number*10 + 2; break;
                case '3':   number = number*10 + 3; break;
                case '4':   number = number*10 + 4; break;
                case '5':   number = number*10 + 5; break;
                case '6':   number = number*10 + 6; break;
                case '7':   number = number*10 + 7; break;
                case '8':   number = number*10 + 8; break;
                case '9':   number = number*10 + 9; break;
            }
            
            // Display Current State Values
            sprintf(message,"\nLock: %1d\r\nNumber: %1d\r\nLDR: %4d\tOn: %4d\r\nIntensity: %3d\tMax: %3d\tMin: %3d\r\nMode: %1d\r\n\n", get_ext_input_status(), number, get_LDR_value(), get_LDR_on_value(), get_intensity_value(), get_max_intensity_value(), get_min_intensity_value(), get_current_state(&smLightControll));
                
            for(cnt=0;cnt<85;cnt++)
            {
                printf("%c", message[cnt]);
            }

            // Clear UART Input
            letter = ' ';
        }
        
        // Run State Machine
        stateMachine_execute(&smLightControll);
    }
    return 0;
}
