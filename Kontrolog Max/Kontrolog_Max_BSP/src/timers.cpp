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

#include "timers.h"
#include "inputs.h"

hw_timer_t *timer0 = NULL;

 
// ----------------------------------------------------------------------------------------------------
void Timer0_ISR(void)                                       // Timer 0 Interrup, every 10mS
// ----------------------------------------------------------------------------------------------------
{
                
        Ko.TIMERS.maxtime_read_vac++;    // Max time for read VAC       
        
        if (Ko.TIMERS.maxtime_read_iac>0)
            Ko.TIMERS.maxtime_read_iac--;

        if (Ko.TIMERS.T_TASK>0)
            Ko.TIMERS.T_TASK--;

        if(Ko.TIMERS.delay>0)                                // Auxiliar for generate Timer Delays in 10mS Intervals
            Ko.TIMERS.delay--;

// --------------------------------------                
// Timers every 100m Seconds
// ------------ -------------------------- 
        if(++Ko.TIMERS.timer_100ms==10)
            {
            Ko.TIMERS.timer_100ms=0;
            OUTPUTS.PID_ACTIVATION_TIMER();             // Calls funtion to activate Outpus In PID Control Mode Every 100mS
            }
// --------------------------------------                
// Timers of 1 Second
// -------------------------------------- 

            if (++Ko.TIMERS.timer_s==100)                 //  Counter in Seconds
                {
                Ko.TIMERS.timer_s=0;
// Publication Timer            
            if (Ko.TIMERS.timer_publication > 0)
                Ko.TIMERS.timer_publication--;


//  Timer for clear the Password
                if (Ko.TIMERS.timer_password>0)
                    if(--Ko.TIMERS.timer_password==0)
                        Ko.CONFIG.DT.password=0;


// Timers for frequency Input in Hz for Inputs 6 to 8
    if(Ko.IN6.type==frequency_Hz)                         //Every Second read de counter 
        {
        Ko.IN6.value=In.Counter_Reader(6);                // The frequency value is the value reached by the counter every second.
        In.Counter_clear(6,0);                            // Clear the counter after each read
        }

    if(Ko.IN7.type==frequency_Hz)
        {
        Ko.IN7.value=In.Counter_Reader(7);                // The frequency value is the value reached by the counter every second.
        In.Counter_clear(7,0);                            // Clear the counter after each read
        }
    
    if(Ko.IN8.type==frequency_Hz)
        {
        Ko.IN8.value=In.Counter_Reader(8);                // The frequency value is the value reached by the counter every second.
        In.Counter_clear(8,0);                            // Clear the counter after each read
        }

// Timers for frequency Input in RPM for Inputs 6 to 8
    if(Ko.IN6.type==frequency_rpm)                        // Every Second read de counter 
        {
        In.RPM.IN6[In.RPM.CounterI6]=In.Counter_Reader(6);                      // The frequency value is the value reached by the counter every second.
        In.Counter_clear(6,0);                                // Clear the counter after each read
        }

    if(Ko.IN7.type==frequency_rpm)                        // Every Second read de counter 
        {
        In.RPM.IN7[In.RPM.CounterI7]=In.Counter_Reader(7);                      // The frequency value is the value reached by the counter every second.
        In.Counter_clear(7,0);                                // Clear the counter after each read
        }
    if(Ko.IN8.type==frequency_rpm)                        // Every Second read de counter 
        {
        In.RPM.IN8[In.RPM.CounterI8]=In.Counter_Reader(8);                      // The frequency value is the value reached by the counter every second.
        In.Counter_clear(8,0);                                // Clear the counter after each read
        }



// Timers for run time Mode
       if ((Ko.IN6.type==runtime)||(Ko.IN6.type==runtime_reset))
            {
            if(In.GET_DIGITAL_INPUT_STATUS(6)==1)
                if(++Ko.IN6.Seconds_Counter>=60)            // Counter in Minuts
                    {
                    Ko.IN6.value++;
                    Ko.IN6.Seconds_Counter=0;
                    }
            }
        
        if ((Ko.IN7.type==runtime)||(Ko.IN7.type==runtime_reset))
            {
            if(In.GET_DIGITAL_INPUT_STATUS(7)==1)
                if(++Ko.IN7.Seconds_Counter>=60)
                    {
                    Ko.IN7.value++;
                    Ko.IN7.Seconds_Counter=0;
                    }
            }
        
        if ((Ko.IN8.type==runtime)||(Ko.IN8.type==runtime_reset))
            {
            if(In.GET_DIGITAL_INPUT_STATUS(8)==1)
                if(++Ko.IN8.Seconds_Counter>=60)
                    {
                    Ko.IN8.value++;
                    Ko.IN8.Seconds_Counter=0;
                    }
            }

//  Timer Delay for activation of the Outpus 1 and Output 2
                if (Ko.OUT1. start_delay>0)
                    Ko.OUT1. start_delay--;
                if (Ko.OUT2. start_delay>0)
                    Ko.OUT2. start_delay--;
                if (Ko.OUT3. start_delay>0)
                    Ko.OUT3. start_delay--;
                if (Ko.OUT4. start_delay>0)
                    Ko.OUT4. start_delay--;
                if (Ko.OUT5. start_delay>0)
                    Ko.OUT5. start_delay--;

//  Auxiliar Timers for Outputs
                if(Ko.OUT1.timer>0)
                    Ko.OUT1.timer--;
                if(Ko.OUT2.timer>0)
                    Ko.OUT2.timer--;      
                if(Ko.OUT3.timer>0)
                    Ko.OUT3.timer--;     
                if(Ko.OUT4.timer>0)
                    Ko.OUT4.timer--;  
                if(Ko.OUT5.timer>0)
                    Ko.OUT5.timer--;          
                  

                
// -------------------------------------- 
// Timers of Minuts
// --------------------------------------            
               if (++Ko.TIMERS.seconds==60)     
                    {
                    Ko.TIMERS.seconds=0;
                    if(Ko.TIMERS.timer_end_test>0)
                        Ko.TIMERS.timer_end_test--;
                    
// -------------------------------------- 
// Timersof hours
// -------------------------------------- 
                    
                    if (++Ko.TIMERS.minutes==60)                   
                        {
                        Ko.TIMERS.timer_reset_com_module++;         // This timer allows the KONTROLOG to restart if there are communication failures.
                        Ko.TIMERS.minutes=0;
                        }
                    }

                }
  
}
// ----------------------------------------------------------------------------------------------------

void Timers::INIT_TIMER(void)                           // Activate ESP32 Timer 0 Every 10mS
{
    timer0 = timerBegin(0, 80, true); // Timer 0, clock divisor 80
    timerAttachInterrupt(timer0, &Timer0_ISR, true); // Attach the interrupt handling function
    timerAlarmWrite(timer0, 10000, true); // Interrupt every 10 mili seconds
    timerAlarmEnable(timer0); // Enable the alarm
}

// Create a Delay timer in mS
void Timers::DELAY_TMR (int delay_ms) {
    Ko.TIMERS.delay=delay_ms/10;
    while(Ko.TIMERS.delay>0)            // Wait for the end of the time
        {
        delayMicroseconds(100);    
        }

}


// User can use the method to put ESP32 in Sleep Mode
void Timers::SLEEP(int Sleep_Time_ms){
    esp_sleep_enable_timer_wakeup(Sleep_Time_ms*1000);
}

uint64_t Timers::get_counter_value(void)
    {
    uint64_t count=timerRead(timer0);
    return count;
}