# Univ-LightControl

Is a system that controls the intensity of an LED on a MAX32 microcontroller board. It features two manual modes and two automatic modes (an ambient light is used to decide which action to take), as well as an emulator for testing purposes and a diagram schematic with instructions on how to build the system.

Instructions:

    All Modes:
    
        Insert a number.
            Terminal input: from '0' to '9' multiple times (numbers inputted from the left to the right) or 'c' to reset the number.

    Mode 1:
    	
        Set the led intensity to the max/min intensity allowed.
            Terminal input: 'o'
            Button press: on/off
    
        Change the current mode to the next mode.
            Terminal input: 'm'

    	Discard future buttons inputs.
            Terminal input: 'l'

    	Use future buttons inputs.
            Terminal input: 'u'

    	Set the maximum intensity to the last number inserted on the board if it is between the minimum intensity and 100.
            Terminal input: 'w'

    	Set the minimum intensity to the last number inserted on the board if it is between 0 and the maximum intensity.
            Terminal input: 's'

    Mode 2:
        
        In addition to the previous mode functionalities, it's also possible:
        
        Increase the led intensity
            Terminal input: '>'
            Button press: +

    	Decrease the led intensity
            Terminal input: '<'
            Button press: -

    Mode 3:

        Change the current mode to the next mode.
            Terminal input: 'm'

    	Set the LDR reference value to the last number inserted on the board (Turn the led to the maximum intensity allowed if the value is higher than the reference value or to the minimum intensity allowed if the value is lower than the reference value).
            Terminal input: 'g'

    Mode 4:
    
        Change the current mode to the first mode.
            Terminal input: 'm'
        
        Set the LDR reference value to the last number inserted on the board (Automatically adjust the led intensity to maintain a LDR value close to the reference LDR value).
            Terminal input: 'g'
