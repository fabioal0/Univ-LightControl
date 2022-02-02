#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "main.h"
#include <sys/attribs.h>

#include "config_bits.h"
#include "uart.h"

#include "lightControllSM.h"
#include "lightControll.h"
#include <stdbool.h>

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
    LDR_Led_On_Value = 2500;
    LDR_Value = 0;
    stateMachine_init(&smLightControll);
}

int main(int argc, char** argv) 
{    
    // Create Auxiliar Varibles
    uint32_t number = 0;
    uint32_t cnt = 0;
    uint8_t message[250];

    // Make Configurations
    ConfigIOpins();
    ConfigTimer();    
    ConfigOC2();
    ConfigUart();
    InitInterruptController();
    ConfigADC();

    // Initiate State Machine
    init();
         
    // Display UI Instructions
    sprintf(message,"Buttons:\tp (On/Off)\t\t+ (More Intensity)\t- (Less Intensity)\r\nTerminal:\to (On/Off)\t\t> (More Intensity)\t< (Less Intensity)\n\r\t\tl (lock)\t\tu (unlock)\t\tw (Set Max Intensity)\n\r\t\ts (Set Min Intensity)\tg (Set LDR On Value)\tm (Change Mode)\r\n\n");
        
    for(cnt=0;cnt<231;cnt++)
    {
        PutChar(message[cnt]);
    }
    
    // Run
    while (1) {

        // Process  Input
        if(letter != ' ')
        {
            // Register User Action
            switch (letter)
            {
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
            sprintf(message,"Lock: %d\r\nNumber: %d\r\nLDR: %d\ton: %d\r\nIntensity: %d\tMax: %d\tMin: %d\r\nMode: %d\r\n\0", get_ext_input_status(), number, get_LDR_value(), get_LDR_on_value(), get_intensity_value(), get_max_intensity_value(), get_min_intensity_value(), get_current_state());
            
            for(cnt=0;cnt<85;cnt++)
            {
                PutChar(message[cnt]);
            }
            
            // Clear UART Input
            letter = ' ';
        }

        // Run State Machine
        stateMachine_execute(&smLightControll);

        // Update Output
        OC2RS = get_intensity_value()*10;
    }
    return (EXIT_SUCCESS);
}

void __ISR(_TIMER_3_VECTOR, IPL6AUTO) T3_IntHandler (void)
{
    AD1CON1bits.ASAM=1;
    IFS0bits.T3IF = 0;
}

void __ISR(_UART_1_VECTOR, IPL5AUTO) uart_isr (void)
{
    GetChar(&letter);
    IFS0bits.U1RXIF = 0;        
}

void __ISR(_ADC_VECTOR,IPL5AUTO) adc_isr(void)
{
    LDR_Value = (ADC1BUF0*3300)/ 1023;
    IFS1bits.AD1IF = 0;
}

void __ISR(_EXTERNAL_0_VECTOR,IPL4AUTO) button_on_off_isr(void)
{
    ButtonStatus.On_Off = b_Pressed;
    IFS0bits.INT0IF = 0;
}

void __ISR(_EXTERNAL_1_VECTOR,IPL3AUTO) button_plus_isr(void)
{
    ButtonStatus.More_intensity = b_Pressed;
    IFS0bits.INT1IF = 0;
}

void __ISR(_EXTERNAL_2_VECTOR,IPL3AUTO) button_less_isr(void)
{
    ButtonStatus.Less_intensity = b_Pressed;
    IFS0bits.INT2IF = 0;
}

void ConfigIOpins(void)
{
    TRISE = BUTTON_RE8_MASK | BUTTON_RE9_MASK;
    TRISD = BUTTON_RD0_MASK;
    TRISB = LDR_RB0_MASK;    
 
    LED_CLR();
}

void ConfigOC2(void)
{
    OC2CONbits.ON = 0;                    
    OC2CONbits.OCM = 6;                   
    OC2CONbits.OCTSEL = 0;
    OC2RS = 0;
    OC2CONbits.ON = 1;
}

void ConfigTimer(void)
{
    T3CONbits.ON = 0;   
    T3CONbits.TCS = 0;
    T3CONbits.TCKPS = 7;
    PR3 = PS_ADC_VALUE;      
    TMR3 = 0;
    T3CONbits.ON = 1;
}

void ConfigUart(void)
{
    UartInit(PBCLOCK, 115200);

    PutChar(0x1b);
    PutChar('[');
    PutChar('2');
    PutChar('J');

    PutChar(0x1b);
    PutChar('[');
    PutChar('H');
}

void ConfigADC(void)
{
    AD1PCFGbits.PCFG0 = 0;   
    AD1CHSbits.CH0SA = 0;    
    AD1CON1bits.FORM = 0;    
    AD1CON1bits.SSRC = 7;    
    AD1CON2bits.VCFG = 0;     
    AD1CON2bits.SMPI = 0;     
    AD1CON2bits.BUFM = 0;     
    AD1CON3bits.ADRC = 1;     
    AD1CON3bits.SAMC = 16;   
    AD1CON1bits.CLRASAM = 1; 
    AD1CON1bits.ON = 1;     
}

void InitInterruptController(void)
{
    __builtin_enable_interrupts();

    // On/Off Button  
    IEC0bits.INT0IE=0;
    IPC0bits.INT0IP=4;
    INTCONbits.INT0EP = 0;
    IFS0bits.INT0IF=0;
    IEC0bits.INT0IE=1;
        
    // + Button  
    IEC0bits.INT1IE=0;
    IPC1bits.INT1IP=3;
    INTCONbits.INT1EP = 0;
    IFS0bits.INT1IF=0;
    IEC0bits.INT1IE=1;

    // - Button  
    IEC0bits.INT2IE=0;
    IPC2bits.INT2IP=3;
    INTCONbits.INT2EP = 0;
    IFS0bits.INT2IF=0;
    IEC0bits.INT2IE=1;            
    
    // Timer 3
    IEC0bits.T3IE = 0;  
    IPC3bits.T3IP = 6;                 
    IFS0bits.T3IF = 0;                 
    IEC0bits.T3IE = 1;   
    
    // ADC
    IEC1bits.AD1IE = 0;
    IPC6bits.AD1IP = 5;
    IFS1bits.AD1IF = 0;
    IEC1bits.AD1IE = 1;

    // UART
    IEC0bits.U1RXIE = 0;
    IPC6bits.U1IP = 5;
    IFS0bits.U1RXIF = 0;        
    IEC0bits.U1RXIE = 1;

    INTCONSET=_INTCON_MVEC_MASK;
    
    __builtin_enable_interrupts();
}