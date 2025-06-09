/*
KONTROLOG-MAX LIBRARIES FOR ARDUINO

Copyright (c) 2025 Omicron IoT Solutions

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

version 1.0 May 2025
*/

#include "display.h"

extern comms Comms;

/*/ This Funtion set the activation of RGB and Panel Indicator LEDs
// KONTROLOG MAX Uses  Shift Register IC74595
// The rutins commanda the signals 
OE_LED : Chip ENABLE
CLK_LED: Clock for Shift register
DATA_LED: Data for Shift register
*/
void Display::Panel_Indicators (void)       // Refresh every 200mS
{
    unsigned char i;
    unsigned char  Panel_Ind=0;
    
    
        if (Ko.LED_RGB.R)  
            Panel_Ind|=LED_RED;

        if (Ko.LED_RGB.G)  
            Panel_Ind|=LED_GREEN;
        
        if (Ko.LED_RGB.B)  
            Panel_Ind|=LED_BLUE;    
        
        if (Ko.OUT1.value)
            Panel_Ind|=LED_REL1;
    
        if (Ko.OUT2.value)
            Panel_Ind|=LED_REL2;

        if (Ko.OUT3.value)
            Panel_Ind|=LED_REL3;

            if (Ko.OUT4.value)
            Panel_Ind|=LED_REL4;
    
        if (Ko.OUT5.value)
            Panel_Ind|=LED_REL5;


// Put the LED indicatos in the shift register   IC     
        
        digitalWrite(OE_LED,1);                 // Disable the shift register output Signal        
        digitalWrite(CLK_LED,0);                // Set Clock Signal to low

        for(i=0;i<9;i++)                        // Rotate the bit 9 times, The Shift rotates 9 positions
            {
            if (Panel_Ind&0x80)                 // Set Bit N
                {
                digitalWrite(DAT_LED,0);
                }
            else
                digitalWrite(DAT_LED,1);
            
            Panel_Ind=Panel_Ind*=2;              // Rotate register for the next data
            
            digitalWrite(CLK_LED,1);;            // Generate rising edge on the clock to set the data
            delayMicroseconds(4);
            digitalWrite(CLK_LED,0);;            // Generate falling edge on the clock to set the data
            }

            digitalWrite(OE_LED,0);              // Disable the shift register output
}