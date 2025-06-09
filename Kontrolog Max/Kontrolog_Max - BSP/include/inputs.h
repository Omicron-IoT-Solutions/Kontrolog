/*
KONTROLOG-MINI LIBRARIES FOR ARDUINO

Copyright (c) 2024 Omicron IoT Solutions

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

version 1.0 June 2024
*/

/* 
 * File:   CAL_T.h
 * Author: Harold Toro
 *
 * Created on 27 de septiembre de 2014, 11:13 AM
 */

#ifndef inputs_h
#define	inputs_h

#include <Arduino.h>
#include <cmath>
#include "config.h"
#include "modbus.h"
#include "timers.h"
#include "driver/pcnt.h"
#include <OneWire.h>
#include <DallasTemperature.h>


class Inputs {

public:
    void INIT_ANALOG_INPUTS (void);                  // Function for initializing inputs 
    void INIT_DIGITAL_INPUTS(uint8_t,uint8_t);
    int  GET_DIGITAL_INPUT_STATUS(int8_t);

    // Inputs functions
    void  ANALOG_INPUTS_READER(char);
    void  SUPPLY_VDC_READER (char);
    void  DIGITAL_INPUTS_READER(void);
    void  READ_VAC(void);
    void  INIT_VAC(void);
    void  READ_IAC(void);
    void  INIT_IAC(void);

    // Counters and frequency Inputs
    int16_t CAL_DIGITAL_INPUT_RPM(int8_t);
    void  Counter_Input_setup(uint8_t, bool);
    int16_t  Counter_Reader(uint8_t);
    void Counter_clear(uint8_t, bool);

// Digital Temperature from ds18b20
    int16_t get_ds18b20_temp(uint8_t);

    struct {
        int16_t IN6[10],IN7[10],IN8[10];
        int16_t CounterI6, CounterI7, CounterI8;
    }RPM;
 
    
private:
    // Functions for input reading according to sensor type
    int   READ_ANALOGS_AS_DIGITAL_INPUT (unsigned char CHN);
    short i4to20mA_INPUT_R (unsigned char CHN);
    short V0to10V_INPUT_R (unsigned char CHN);
    short NTC_TEMP_INPUT_R (unsigned char);
    short AMB_TEMP_INPUT_R (unsigned char);
    short AMB_HUM_INPUT_R (unsigned char);
    int   MODBUS_INPUT_R (int8_t, int16_t, int16_t, int8_t);
    void  sortDescending(int *arr, int n);


    void destroyCounter(uint8_t); 
    void get_counter_channel(uint8_t);
   
    // Funtion for the scaling algorithm for inputs
    int16_t INPUT_SCALING_ALGORITHM (int16_t *input);

    // Functions for storing input reading values
    void READ_ANALOG_AND_STORING(void);


    // Struct for channel readings
    struct {
        unsigned short CHN_DATA[8][10];        // Stores 10 readings per channel IN1, IN2, VDC
        unsigned short TEN_READINGS_SUM[8];    // Sums 10 readings to average channel reading
    } READ_A;

    struct{
        int Prom_TIME[25];
        int Prom_IAC[4];
        unsigned char Ix,Vx;
        int32_t MEAN_TIME;
        int16_t DELTA_TIME;
        int SUMA_IAC;
        }ENG;

    struct{
        float Read_Frequency;
        char Set_Frequency;
        }FR;
    

    // Counter
    static int PREV_SENS[5];
    pcnt_unit_t PULSE_COUNT_UNIT;  // Pulse counter unit
    int GPIO_PIN_COUNTER;  // GPIO pin where the button is connected

    // NTC temperature calculation table
    const unsigned short TEMP_TABLE[35] =     // Table of values to calculate the temperature of Thermistor NTC 10K. Step of 5 degree Celsius, range [-50 to 120 degree Celsius].
    {40358,40110,39778,39339,38769,38043,37135,36023,34690,33132,
    31356,29387,27261,25030,22750,20480,18276,16182,14234,12452,
    10847,9426,8166,7064,6109,5284,4571,3959,3435,2985,2598,2266,
    1981,1736,1525};

    // Auxiliary variables
    int Jx1=0,Kv=0;
    int Mx1=0;
};
    extern Inputs In;
#endif