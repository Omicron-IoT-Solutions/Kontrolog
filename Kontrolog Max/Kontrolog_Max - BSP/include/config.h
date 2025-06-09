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

#ifndef config_h
#define config_h

#include <Arduino.h>


//-----------------------------------------------------------------------------------------------
// FUNCTIONS
//-----------------------------------------------------------------------------------------------

//int main(int argc, char** argv);

//-----------------------------------------------------------------------------------------------
// KONTROLOG MINI PIN DEFINITION
//-----------------------------------------------------------------------------------------------


#define LED_RED    0b00000001           // LED RGB RED 
#define LED_BLUE   0b00000010           // LED RGB BLUE
#define LED_GREEN  0b00000100           // LED RGB GREEN
#define LED_REL1   0b00001000           // LED 1  -->  Relay 1 Status
#define LED_REL2   0b00010000
#define LED_REL3   0b00100000
#define LED_REL4   0b01000000
#define LED_REL5   0b10000000

#define DAT_LED    15
#define CLK_LED    25
#define OE_LED     33

#define Buzzer 4		        // Alarm Buzzer GPIO4
#define EN_COM_MOD	27          // Enable Communication Module  GPIO26
#define RX_COM 35               // Rx pin for Com Module
#define TX_COM 26               // Tx pin for Com Module

//Digital IO Pins
#define IN6_PIN 14				 // Input 6 in GPIO14
#define IN7_PIN 13				 // Input 7 in GPIO13
#define IN8_PIN 16 			     // Input 8 in GPIO16

#define EN_RS485 32             // Read/Write RS-485 GPIO18
#define TX_RS485 12             // Tx pin for RS485
#define RX_RS485 34             // Rx pin for RS485

#define N_Backup_Data 144       // Number of messages stored as backup in case of connection lost
#define N_Historical_Data  96   // Number of sensor data stored in eeprom for graphics 
#define SDA1_PIN  18            // SDA Pin for ADC TLA2528
#define SCL1_PIN  19            // SCL Pin for ADC TLA2528

#define DISPLAY_RX_PIN 13       // External I/O pins for Display IN7
#define DISPLAY_TX_PIN 16       // IN8

//-----------------------------------------------------------------------------------------------
// WORKING ENUMERATORS
//-----------------------------------------------------------------------------------------------

enum com_module_type {            // Supported communication modules.
    mod_none = 0,
    mod_sigfox,
    mod_wifi,
    mod_lora,
    mod_ble
};

enum com_module_status {         // Communication module tasks	
    standby,
    storing,
    joining,
    waiting_to_join,
    sending,
    receiving,
    waiting_for_next_sending,
    rx_lora,
    module_init,
    wifi_AP_mode,
};

enum Lora_zones {                 // LoRaWAN band zones.
    AS923,
    AU915,
    CN470,
    CN779,
    EU433,
    EU868,
    KR920,
    IN865,
    US915,
    RU864,
    /*  <band>: [0: AS923, 1: AU915, 2: CN470, 3: CN779,
    4: EU433, 5: EU868, 6: KR920, 7: IN865, 8: US915, 9:
    RU864]  */
};

enum Lora_Modes {                 // LoRa modes.
    OTAA,
    ABP,
    none,
};

enum led_color {                   // RGB LED colors
    led_off,
    led_white,
    led_red,
    led_blue, 
    led_green,
    led_violet,
    led_yellow,
    led_navy_blue
};

enum control_functions {			// Types of output control functions.
    outoff,
    remote_commands,
    input_follower,
    on_off,
    timer,
    remote_alarm,
    event_counter,
    PID,
};

enum sensor_types {				    // Types of iput sensors.
    inputoff=0,
    digital_input=1,
    i4to20mA=2,
    v0to10V=3,
    temp_ntc=4,
    temp_amb=5,
    hum_amb=6,
    counter_cumulative=7, 
    in_remote=8,
    in_modbus=9,
    frequency_Hz=10,
    counter_reset=11,
    runtime=12,
    runtime_reset=13,
    temp_ds18b20=14,
    frequency_rpm=15,
    vac=16,
    iac=17

};

enum Ad_Channels                    // analog inputs channels
{
    analog_input1=0,
    analog_input2=1,
    analog_input3=2,
    analog_input4=3,
    analog_inpit5=4,
    analog_vdc=5,
    analog_vac=6,
    analog_iac=7,
};

enum  Di_Channels
{
    digital_input6=0b00100000,
    digital_input7=0b01000000,
    digital_input8=0b10000000,
};

//-----------------------------------------------------------------------------------------------
// STRUCTS
//-----------------------------------------------------------------------------------------------

typedef struct{ 
    union {                         	    // Inputs descriptor : each data is saved as an integer (2 bytes)
    int16_t Array [16];
    struct {
        int16_t address;						// Addres of the input (Input 1 and 2), or modbus slave address(1..247).
        int16_t value;							// Current reading value
        int16_t type;							// Type of the sensor, temperature,  4..20mA, 0..10V,  humidity,  diferent from sensor
        int16_t resolution;	            		// Resolution, 0, 1, 2 or 3 digits					
        int16_t enable;							// Enable/Disable the sensor
        int16_t offset;							// Offset to correct the reading value
        int16_t L_limit;				    	// Lower alarm limit
        int16_t H_limit;						// Higher alarm limit
        int16_t alarm_delay;					// delay for triggering the alarm [in seconds]
        int16_t modbus_start_register;           // Modbus: Start Reading Register
        int16_t modbus_coils_qty;               // Modbus: Number of registers for reading
        int16_t modbus_type;                    // Modbus: data format. 0: Integer / 1: Integer multiplied by 10 / 2: Integer multiplied by 100 / 3: Float IEEE 754-2008 / 4: Inverse Float  IEEE 754-2008				    			
        int16_t slope;                          // Slope to scale the reading value	
        int16_t Pulse_Edge;                     // Pulse counter detect on falling or rising edge 
        int16_t Seconds_Counter;                // Seconds Counter for Runtime Operation           
        };
    };
    String Label;
}IN_t;



typedef struct{ 
    union {                         	    // Inputs descriptor : each data is saved as an integer (2 bytes)
    int16_t Array [16];
    struct {
        int16_t address;						// Addres of the input (Input 1 and 2), or modbus slave address(1..247).
        int16_t value;							// Current reading value
        int16_t type;							// Type of the sensor, temperature,  4..20mA, 0..10V,  humidity,  diferent from sensor
        int16_t resolution;	            		// Resolution, 0, 1, 2 or 3 digits					
        int16_t enable;							// Enable/Disable the sensor
        int16_t offset;							// Offset to correct the reading value
        int16_t L_limit;				    	// Lower alarm limit
        int16_t H_limit;						// Higher alarm limit
        int16_t alarm_delay;					// delay for triggering the alarm [in seconds]
        int16_t Turns;                          // Turns for CT 
        int16_t Rload;                          // R Load for CT
        int16_t reserve;                        // Reserve
        int16_t slope;                          // Slope to scale the reading value	
        };
    };
    String Label;
}IAC_t;

typedef struct { 
    union {								    // Outputs descriptor : each data is saved as an integer (2 bytes)
    int16_t Array [35];
    struct {
        int16_t  address;						// Addres of the output (Output 1 and 2)
        int16_t  value;							// Current value of the output [0 or 1]
        int16_t  control_function;			    // Designated control function:  Controll On/Off,  PID, Timer
        int16_t  control_signal;				// Control singal (input 1, 2 ; or 0: none).
        int16_t  set_point;						// Set Point
        int16_t  hysteresis;					// Hysteresis in On/Off control mode				
        int16_t  control_type;				    // Control Type (normal or inverted output)
        uint16_t set_time_ON;                   // Cycle time ON for timer / Cycle Time for PID
        uint16_t set_time_OFF;                  // Cycle time OFF for timer / Time to make Control Calculations for PID
        int16_t  Kp;                     		// Proportional Action for PID
        int16_t  Int;                    		// Integral Action for PID
        int16_t  Der;                    		// Derivative Action for PID
        int16_t  Pmax;                   		// Maximum Power to apply at the Output for PID

        // Working Variables
        uint16_t timer;         		        // Timer Counter
        int16_t phase;							// Phase in PID control
        int16_t start_delay;					// Delay to start the control at the output
        int16_t prev_value;                   	// Previus value of the control signal
        int16_t error;                  		// Error =  SetPoint - CurrentValue in PID
        int16_t PB;                     		// Calculated Propotional Band PID
        int16_t TD[4];                  		// Delta of temperatures over time PID
        int16_t power;               			// Calculated Power PID
        float error_sum, max_int;    		    // Sum of integral error PID
        int16_t timer_PID;              		// Cycle timer PID
        int16_t reserved;              			// Reserved
        int16_t power_calc;              		// For calculations of the power delivered in PID
        int16_t aux_timer_calc;         		// Auxiliary timer
        };
    };
    String Label;
}OUT_t;

typedef union {								    // General Parameters descriptor : each data is saved as an integer (2 Bytes)
    int16_t Array [16];
    struct{
        int32_t ID;                        	    // Device ID (4 Bytes)
        int16_t TPU;                        	// Publication Time
        int16_t service;                    	// Enter to Service Mode
        int16_t Display_Port;           		// Define the display Port
        int16_t eeprom_vers;                	// Version of factory parameters (Reset to factory settings Stored in EEPROM)
        int16_t com_module_prog;            	// Type of communication module programmed (0: none, 1: Sigfox, 2: WiFi, 3: Lora)
        int16_t reserve2;                		// Not Used, Reserved
        int16_t downlink_msg;           	    // Number of messages for downlink
        int16_t RF_zone;                    	// RF zone  (2: USA-US915, 4: Latam-Australia-AU915 / 1: EU-EU868)
        int16_t status;                     	// Current status of the device (off, on, test mode)
        int16_t password;                   	// Password for configuration
        int16_t task;							// Sub task mode 
        int16_t com_module_det;   				// Real communication module detected (0: none, 1: Sigfox, 2: WiFi, 3: Lora)
		
    }DT;
}CONFIG_t;

typedef union {                             // Alarms descriptor : each data is saved as an unsigned short data.
    int32_t data;
    struct {												
            unsigned IN1_H:1;               // Alarm for input 1 exceeding higher limit
            unsigned IN1_L:1;               // Alarm for input 1 exceeding lower limit
            unsigned IN2_H:1;               // Alarm for input 2 exceeding higher limit
            unsigned IN2_L:1;               // Alarm for input 2 exceeding lower limit
            unsigned IN3_H:1;               // Alarm for input 3 exceeding higher limit
            unsigned IN3_L:1;               // Alarm for input 3 exceeding lower limit
            unsigned IN4_H:1;               // Alarm for input 4 exceeding higher limit
            unsigned IN4_L:1;               // Alarm for input 4 exceeding lower limit
            unsigned IN5_H:1;               // Alarm for input 5 exceeding higher limit
            unsigned IN5_L:1;               // Alarm for input 5 exceeding lower limit
            unsigned IN6_H:1;               // Alarm for input 6 exceeding higher limit
            unsigned IN6_L:1;               // Alarm for input 6 exceeding lower limit
            unsigned IN7_H:1;               // Alarm for input 7 exceeding higher limit
            unsigned IN7_L:1;               // Alarm for input 7 exceeding lower limit
            unsigned IN8_H:1;               // Alarm for input 8 exceeding higher limit
            unsigned IN8_L:1;               // Alarm for input 8 exceeding lower limit
            unsigned V_DC:1;                // Alarm for DC power supply voltage
            unsigned V_AC:1;                // Alarm for VAC power supply voltage
            unsigned I_AC:1;                // Alarm for IAC CT Current Sensor
            unsigned BUZZER:1;              // Audible alarm
        }bits;
}ALARM_t;

typedef union {                             // Alarms descriptor : each data is saved as an unsigned short data.
    int16_t data;
    struct {												
            unsigned R:1;               // Alarm for input 1 exceeding higher limit
            unsigned G:1;               // Alarm for input 1 exceeding lower limit
            unsigned B:1;               // Alarm for input 2 exceeding higher limit
        };
}RGBLED_t;

typedef union {                             // RTC descriptor : each data is saved as an integer of 15 bits..
    int16_t Array[50];
    struct{
        uint32_t time_stamp;                    // Unix Epoch        
        int16_t time_zone;                      // Time zone
        tm timeinfo;                            // Time Struct  from time.h (Arduino)
        uint16_t RTC_is_synchronized;           // Flag indicate if RTC is Configured
        uint32_t previous_time_stamp;           // Auxiliar for Stored Previus Unix Epoch
    };
}RTC_t;

typedef struct {                                // Sigfox communications module descriptor.
    char ID[9];                                 // Sigfox ID unique identifier
    int zone;								    // 1: EU, 2: USA, 4: AU/LATAM
}SIGFOX_MODULE_t;

typedef struct {                                // LoRa communications module descriptor.
    int  band;          					    // 1: AU915, 5: EU868, 8: US915 
    int  tries2join;                          // Auxiliar for counter the number of tries to join to the network
    bool join_status;                           // Flag indicate if the Networt is Joined    
    char OTAA_DEV_EUI[17];                      // Device EUI
}LORA_MODULE_t;

typedef struct{                                 // Wifi module descriptor
    bool on_off;                                // flag indicates if Wifi is Connected to network
    String MAC;                                 // Stored MAC address
    int16_t rssi;                               // Stored rssi level
}WIFI_MODULE_t;

typedef struct {							    // Downlink Messages descriptor: parameters modification commands.
    int16_t group;                              // Group of parameters that can be configured
    int16_t subgroup;                           // Subgroup of parameters that can be configured
    int16_t parameter;                          // Parameter to be configured 
    float value_float;                      // Value assigned to the parameter in float
    int32_t  value_long;                     // Value assigned to the parameter in long                
}GET_DATA_t; 

typedef struct {                                // Auxilar Timers descriptor.
    uint16_t timer_1ms,timer_100ms, timer_s, seconds, minutes;
    uint16_t T_TASK;                                        // Timer for main task manager     
    uint16_t delay;                                         // Timer used for timer delays
    uint16_t maxtime_read_vac;                              // Timer used for calculate VAC
    uint16_t maxtime_read_iac;                             // Timer used for calculate IAC
    uint32_t timer_publication;                             // Timer for Publication time in seconds
    uint16_t wait_for_sigfox_downlink;                      // Timer for wait Sigfox Downlink
    uint16_t timer_wifi_AP;                                 // Timer to exit WiFi AP Mode
    uint16_t timer_reset_com_module;                        // Timer to reset the device upon communication error
    uint16_t timer_password;                                // Timer for reset password
    uint16_t timer_alarm;                                   // Timer for activate the sound alarm
    uint16_t timer_end_test;                                // Timer for end Test modes
}TIMERS_t;

typedef struct {                                            // Publications descriptor.
    int16_t send_data, data_ACK_Rx;          			    // Flags and counters for communication tasks
    int16_t wait_for_downlink;                              // Wait for downlink data                       
    int16_t alarm_type;                                   // Publication message Type:  User Alarms
    int16_t com_task;                                       // Task of Comm module
    int16_t Rx_max_timer;                                     // Auxiliar counter wait Response from Comm Module                      
    int16_t join_max_timer;					  			    // Counter for attepts to join in Lora Mode
    int16_t counter_for_downlink;		                    // Counter for wait downlink data			
    int16_t counter_of_attempts_to_send;                    // Counter for attempts to send data
    int16_t counter_for_delay;
}PUB_t;

typedef struct {                                        // Backup of data sent descriptor.
    uint8_t   data [N_Backup_Data][25];
    uint16_t  index;
}BACKUP_DATA_SENT_t;

typedef struct {                                            // Modbus descriptor.
    uint8_t  slave_address;                                 // Modbus address (number between 1 and 247)
    uint8_t  funtion_code;                                  // Modbus function code
    uint16_t start_address;                                 // Address of the register (to be read/written)
    uint16_t coils_no;                                      // Number of registers (to be read/written)
    uint8_t  registers[80];                                 // Buffer for stored Modbus RTU data
}MODBUS_t;


class Board {
  
public:
    IN_t IN1,IN2,IN3,IN4,IN5,IN6,IN7,IN8;                   // Input 1 to 8
    IN_t VDC,VAC;                                           // VDC Input, VAC Input
    IAC_t IAC;                                              // IAC
    OUT_t OUT1,OUT2,OUT3,OUT4,OUT5;                         // OUT1..OUT5
    TIMERS_t TIMERS;                                        // Auxiliar timers
    CONFIG_t CONFIG;                                        // General configurations
    GET_DATA_t GET_DATA;                                    // Auxiliar for downlink data
    PUB_t PUB;                                              // Auxiliar for Communication tasks
    RTC_t RTC;                                              // Auxiliar for RTC
    LORA_MODULE_t LORA_MOD;                                 // Lora Module 
    SIGFOX_MODULE_t SIGFOX_MOD;                             // Sigfox Module
    WIFI_MODULE_t WIFI_MOD;                                 // Wifi Module
    MODBUS_t MODBUS;                                        // Modbus Variables
    ALARM_t ALARM;
    BACKUP_DATA_SENT_t BACKUP_SENT;
    RGBLED_t LED_RGB;
};

extern Board Ko;                                       // Set Public all Data Structs

#endif