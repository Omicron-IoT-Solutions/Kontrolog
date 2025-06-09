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

version 1.0 September 2024
*/
#ifndef eeprom_esp_h
#define	eeprom_esp_h

#include <Arduino.h>
#include <EEPROM.h>
#include "Config.h"
#include "RTC_CLOCK.h"


// Data Version in EEPROM
const int EEPROM_VERSION = 0x0005;              // Change this number each time that you want to modify factory setting parameters.

// Reserved addresses in the EEPROM for stored parameters for inputs, outputs and general parameters
const unsigned int
// Inputs
IN1_EEPROM = 0,
IN2_EEPROM = 0x10,
IN3_EEPROM = 0X20,
IN4_EEPROM = 0X30,
IN5_EEPROM = 0X40,
IN6_EEPROM = 0X50,
IN7_EEPROM = 0X60,
IN8_EEPROM = 0X70,
VDC_EEPROM  =0x80,
VAC_EEPROM = 0x90,
IAC_EEPROM = 0xA0,

// Outputs
OUT1_DIR = 0xB0,
OUT2_DIR = 0xC0,
OUT3_DIR = 0xD0,
OUT4_DIR = 0xE0,
OUT5_DIR = 0xF0,

// RTC       
RTC_DIR  = 0x100,
// General configuration Parameters
EEPROM_CONFIG_INI=0x110,    
EEPROM_ID      = 0x110,
DIR_TPU        = 0x112,      // TPU
DIR_BOOT       = 0x113,      // Boot Loader
EEPROM_EEINI   = 0x115,      // Programación inicial de parámetros de fábrica.
DIR_COM_MODULE = 0x116,      // Dirección módulo de comunicación
DIR_DOWNLINK   = 0x118,      // Dirección de Downlink
DIR_RF_ZONE    = 0x119,      // Dirección de zona RF para Sigfox y LoRa
DIR_STATUS     = 0X11A;      // Operational Status Address  0:off, 1: On



// Sensor Factory settings
 
/* Estructura de Datos
        0:  address;						// UID of the sensor
        1:  value;							// Current reading value
        2:  type;							// Type of the sensor, temperature,  humidity,  diferent from sensor
        3:  resolution;	            		// Resolution, 0, 1, 2 or 3 digits					
        4:  enable;							// Enable/Disable the sensor
        5:  offset;							// Offset to correct the reading value
        6:  L_limit;				    	// Lower alarm limit
        7:  H_limit;						// Higher alarm limit
        8:  alarm_delay;					// delay for triggering the alarm [in seconds]
        9:  modbus_address_register;        // Modbus Start Adrress Register
        10: modbus_coils;                   // Modbus number of reading registers
        11: modbus_type;                    // Modbus type of data
        12: slope;                          // Slope Scaled for 1000
        13: Pulse_edge

 */

/* Types of sensors
    inputoff=0,
    digital_input,
    i4to20mA,
    v0to10V,
    temp_ntc,
    temp_amb,
    hum_amb,
    counter_input, 
    in_remote,
    in_modbus,
    temp_ds18b20,
    frequency_input,
    digital_output,
    */

const int Sens_Ini1[16]={1,0,4,1,1,0,150,300,300,1,1,1,1000,1};          // Sensor S1 
const int Sens_Ini2[16]={2,0,4,1,1,0,150,300,300,1,1,1,1000,1};          // Sensor S2 
const int Sens_Ini3[16]={3,0,4,1,1,0,150,300,300,1,1,1,1000,1};          // Sensor S3
const int Sens_Ini4[16]={4,0,4,1,1,0,150,300,300,1,1,1,1000,1};          // Sensor S4 
const int Sens_Ini5[16]={5,0,4,1,1,0,150,300,300,1,1,1,1000,1};          // Sensor S5 
const int Sens_Ini6[16]={6,0,7,0,1,0,150,300,300,1,1,1,1000,1};          // Sensor S6
const int Sens_Ini7[16]={7,0,7,0,1,0,150,300,300,1,1,1,1000,1};          // Sensor S7 
const int Sens_Ini8[16]={8,0,7,0,1,0,150,300,300,1,1,1,1000,1};          // Sensor S8 

const int Sens_Ini_Vdc[16]={9 ,0,3,1,1,0,0,240,600,1,1,1,1000,0};         // DC Voltage
const int Sens_Ini_Vac[16]={10,0,3,1,1,0,900,1500,600,1,1,1,1000,0};         // AC Voltage
const int Sens_Ini_Iac[16]={11,0,3,1,1,0,0,100,600,2000,60,1,1000,0};     // AC Current

/*  Outputs factory settings
    0: Output Address 1 or 2
    1: value;
    2: Control Funtion;
    3: Control Singal;
    4: Set_point;
    5: Hysteresis
    6: Control Type
    7: Set_Time_ON;
    8: Set_Time_OFF;
    9:  Kp;                     		// Proportional Action for PID
    10: Int;                    		// Integral Action for PID
    11: Der;                    		// Derivative Action for PID
    12: Pmax;                   		// Maximum Power to apply at the Output in PID Control

    */
/* Outputs Types
    0: Output Off,
    1: Remote Commands
    2: Input follower
    3: Control ON/ OFF  Heating and Cooling
    4: Timer
    5: External Alarm
 */
const int Out1_Init[16]={1,0,3,1,300,10,0,60,60,10,5,3,100,0};          // Output1
const int Out2_Init[16]={2,0,4,2,300,20,0,60,60,10,5,3,100,0};          // Output2
const int Out3_Init[16]={3,0,4,2,300,20,0,60,60,10,5,3,100,0};          // Output3
const int Out4_Init[16]={3,0,4,2,300,20,0,60,60,10,5,3,100,0};          // Output4
const int Out5_Init[16]={3,0,4,2,300,20,0,60,60,10,5,3,100,0};          // Output5


const int Initial_Params [16] = {                                 // General Configurations
0,221,                 // initial ID
1,                     // TPU: Publication Time
1,                     // Enter to Service Mode
0,                     // Not used,  Reserved
1,                     // Version of factory parameters (Reset to factory settings Stored in EEPROM)
3,                     // Type of communication module programmed (0: none, 1: Sigfox, 2: WiFi, 3: Lora)
0,                     // Not Used, Reserved
3,                     // Number of messages for downlink
2,                     // RF zone  (2: USA-US915, 4: Latam-Australia-AU915 / 1: EU-EU868)
1,                     // Current status of the device (off, on, test mode)
0,                     // Password for configuration
0,                     // Sub task mode 
0,                     // Real communication module detected (0: none, 1: Sigfox, 2: WiFi, 3: Lora)
0,                     // Not Used, Reserved
0,                     // Not Used, Reserved
};                     


class ee_prom_class {

public:
    void Setup_EEPROM();                            // Begin EEPROM
    void Extract_Data_EEPROM(void);                 // Extract all parameter for sensor, outpus and general configuration stored into EEPROM 
    uint8_t Read_1Byte_EEPROM(unsigned int);        // Read one Byte Stored into EEPROM
    void Write_1Byte_EEPROM(int, unsigned char);    // Write one Byte into EEPROM
    int16_t Read_Int_EEPROM(unsigned int);          // Read one Integer (2bytes) stored into EEPROM
    void Write_Int_EEPROM(unsigned int, int16_t);   // Write one Integer (2bytes) into EEPROM
    String Read_String_EEPROM (unsigned int);       // Read one String Stored into EEPROM
    void Write_String_EEPROM (unsigned int, String);// Write one String into EEPROM


private:
    void Init_Sensor_Data (int,const int *, int16_t *,char);
    void Read_Sensor_Data (int, int16_t *, char);

};

extern ee_prom_class EEPROM_MEM;
#endif
