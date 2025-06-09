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


#include "config.h"
#include "inputs.h"
#include "eeprom_esp.h"
#include "wifi_esp.h"
#include "sigfox.h"
#include "time.h"
#include "display.h"
#include "outputs_control.h"



Board Ko;                       // Create all Data Struct  (from config.h)
Inputs In;                      // Create Analog and digital INPUTS Class.
ee_prom_class EEPROM_MEM;       // Create EEPROM Class 
Sigfox_class Si;                // Create Sigfox Class
wifi_esp_class Wi;              // Create Wifi Class
LoRa Lo;                        // Create Lora Class
Timers Ti;                      // Create Timer Class                   
comms Comms;                    // Create Communication task mannager Class           
ModbusClass Modbus;             // Create Modbus Class
RTC_clock_class RTC;            // Create RTC Class
Outputs_class OUTPUTS;          // Create Outputs Class
Display Di;                     // Create Display Class     

  int task=0;                   // Task Manager


void setup() {
  
  
  Serial.begin(115200);                                     // Serial 0, for Debug
  
  pinMode(OE_LED, OUTPUT);                                  // Configure IO Pins for RGB and other LEDs
  pinMode(CLK_LED, OUTPUT);
  pinMode(DAT_LED, OUTPUT);
  pinMode(Buzzer,OUTPUT);

  // Turn On Incation 
  Serial.println();
  Serial.println("WELCOME TO KONTROLOG MAX PROJECT");
  Ko.ALARM.bits.BUZZER=1;                                   // Turn ON Buzzer
  digitalWrite(Buzzer,HIGH);
  Comms.SET_LED_RGB(led_white);                             // Turn RGB LED: White
  Di.Panel_Indicators();                                    // Set the LEDs Output
  delay(1000);
  Ko.ALARM.bits.BUZZER=0;
  digitalWrite(Buzzer,LOW);
  Comms.SET_LED_RGB(led_off);
  Di.Panel_Indicators();
  
  
  Serial1.begin(9600,SERIAL_8N1,RX_COM,TX_COM);             // Serial 1, for Communication Module Sigfox / LoRa
  pinMode(EN_COM_MOD,OUTPUT);                               // Pin for Enable/Disable COM Module
  
  Serial2.begin(9600, SERIAL_8N1, RX_RS485, TX_RS485);      //Serial 2,  for RS-485 Communication   
  pinMode(EN_RS485,OUTPUT);                                 // Rx / Tx Pin for RS485
  digitalWrite(EN_RS485,LOW);                               // Set Rx RS-485


  EEPROM_MEM.Extract_Data_EEPROM();                        // Read Configuration Parameters Stored in EEPROM
 
  Ti.INIT_TIMER();                                         // Timer 0 initialization  (See timers.h)

  
  // Init Inputs and Outputs states
  In.INIT_ANALOG_INPUTS();
  In.INIT_VAC();
  In.INIT_IAC();
  In.INIT_DIGITAL_INPUTS(6,0);                            // Init all digital inputs
  In.INIT_DIGITAL_INPUTS(7,0);                            // User can reprogramte these digital I/O ports
  In.INIT_DIGITAL_INPUTS(8,0);
  Ko.OUT1.value=Ko.OUT2.value=Ko.OUT3.value=Ko.OUT4.value=Ko.OUT5.value=0;
  OUTPUTS.Set_Ouputs();                                 // Init Relay Outputs

  Ko.TIMERS.T_TASK=20;                                    // Start timer task interval, this timer is decreased every 10 mS in TIMER 0 ISR
  Ko.PUB.com_task=module_init;                            // Init Com Module Status


}

// Main Loop
void loop() {
    
    while(Ko.TIMERS.T_TASK>0)                           // Wait for next ciclying
      {
      delay(1);
      };
      Ko.TIMERS.T_TASK=20;                               // Set timer task interval to 200mS Timer T_TASK is drecrease every 10 mili-seconds in TIMER 0 ISR 
      
      switch(task)
        {
    
          case 0:         // Read Inputs
            In.ANALOG_INPUTS_READER(1);  
            In.DIGITAL_INPUTS_READER();
            Serial.printf("IN1 Value: %.1f\r\n", (float) Ko.IN1.value/pow10(Ko.IN1.resolution));    // Print some values of variables
            Serial.printf("IN2 Value: %.1f\r\n", (float) Ko.IN2.value/pow10(Ko.IN2.resolution));    

            task++;
          break;
          
          case 1:             // Read VAC
            In.READ_VAC();
            Serial.printf("VAC: %.1f\r\n", (float) Ko.VAC.value/10);
            task++;
          break;

          case 2:             // Read IAC
            In.READ_IAC();
            Serial.printf("IAC: %.1f\r\n", (float) Ko.IAC.value/10);
            task++;
          break;

          case 3:             // Otputs Control
            OUTPUTS.OUTPUTS_CONTROL_MANAGER();
            OUTPUTS.Set_Ouputs();                               // Set the realay outpus in Hardware.
            task++;
          break;

          case 4:
            Comms.Communication_Task();                         // Perform communications Tasks,  Note: Seting the right module and publication time in eeprom.h
            task=0;
          break;

      }
      

    Di.Panel_Indicators();                                      // Set RGB and LEDs Status
  
}