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

#include "inputs.h"
#include "TLA2528_C.h"


TLA2528Class TLA2528;



// Setup a OneWire instance for temperature sensor DS18B20
OneWire oneWire1(IN6_PIN);
OneWire oneWire2(IN7_PIN);

// Pass our OneWire reference to DallasTemperature object
DallasTemperature sensor6_ds18b20(&oneWire1);
DallasTemperature sensor7_ds18b20(&oneWire2);


int Inputs::PREV_SENS[5] = {0, 0, 0, 0, 0};

//-----------------------------------------------------------------------------------------------
void Inputs::ANALOG_INPUTS_READER(char Nx) {          
    if (++Kv >= Nx)                                 // If sensor reading and monitoring are enabled
        {
        Kv=0;                                       // Controls the battery reading time
  
        READ_ANALOG_AND_STORING();                   // Reads and stores the analog channels of the inputs                 

        // Input 1
        if (Ko.IN1.enable==1)
            {
            if (Ko.IN1.type==digital_input)
                {Ko.IN1.value=READ_ANALOGS_AS_DIGITAL_INPUT(0);}
            else if (Ko.IN1.type==i4to20mA)
                {Ko.IN1.value=i4to20mA_INPUT_R(0);}    
            else if (Ko.IN1.type==v0to10V)
                {Ko.IN1.value=V0to10V_INPUT_R(0);}     
            else if (Ko.IN1.type==temp_ntc)             
                {Ko.IN1.value=NTC_TEMP_INPUT_R(0);}
            else if (Ko.IN1.type==temp_amb)             
                {Ko.IN1.value=AMB_TEMP_INPUT_R(0); Ko.IN1.resolution=1;}    
            else if (Ko.IN1.type==hum_amb)             
                {Ko.IN1.value=AMB_HUM_INPUT_R(0);  Ko.IN1.resolution=1;}             
            else if (Ko.IN1.type==in_remote)
                {Ko.IN1.resolution=1;}
            else if (Ko.IN1.type==in_modbus)
                {
                Ko.IN1.value=MODBUS_INPUT_R(Ko.IN1.address,Ko.IN1.modbus_start_register,Ko.IN1.modbus_coils_qty,Ko.IN1.modbus_type); 
                Ko.IN1.resolution=1;
                }
            else
                {Ko.IN1.value=0;}    
            
            Ko.IN1.value=INPUT_SCALING_ALGORITHM(Ko.IN1.Array);
            
            }
        else
            {Ko.IN1.value=0;}    

        // Input 2
        if (Ko.IN2.enable==1)
            {
            if (Ko.IN2.type==digital_input)
                {Ko.IN2.value=READ_ANALOGS_AS_DIGITAL_INPUT(1);}    
            else if (Ko.IN2.type==i4to20mA)
                {Ko.IN2.value=i4to20mA_INPUT_R(1);}    
            else if (Ko.IN2.type==v0to10V)
                {Ko.IN2.value=V0to10V_INPUT_R(1);}  
            else if (Ko.IN2.type==temp_ntc)             
                {Ko.IN2.value=NTC_TEMP_INPUT_R(1);}
            else if (Ko.IN2.type==temp_amb)             
                {Ko.IN2.value=AMB_TEMP_INPUT_R(1); Ko.IN2.resolution=1;}    
            else if (Ko.IN2.type==hum_amb)             
                {Ko.IN2.value=AMB_HUM_INPUT_R(1);  Ko.IN2.resolution=1;}     
            else if (Ko.IN2.type==in_remote)
                {Ko.IN2.resolution=1;}
            else if (Ko.IN2.type==in_modbus)
                {   
                Ko.IN2.value=MODBUS_INPUT_R(Ko.IN2.address,Ko.IN2.modbus_start_register,Ko.IN2.modbus_coils_qty,Ko.IN2.modbus_type);
                Ko.IN2.resolution=1;
                }
            else
                {Ko.IN2.value=0;}
            
            Ko.IN2.value=INPUT_SCALING_ALGORITHM(Ko.IN2.Array);
            }
        else
            {Ko.IN2.value=0;}


        // Input 3
        if (Ko.IN3.enable==1)
            {
            if (Ko.IN3.type==digital_input)
                {Ko.IN3.value=READ_ANALOGS_AS_DIGITAL_INPUT(2);}    
            else if (Ko.IN3.type==i4to20mA)
                {Ko.IN3.value=i4to20mA_INPUT_R(2);}    
            else if (Ko.IN3.type==v0to10V)
                {Ko.IN3.value=V0to10V_INPUT_R(2);}  
            else if (Ko.IN3.type==temp_ntc)             
                {Ko.IN3.value=NTC_TEMP_INPUT_R(2);}
            else if (Ko.IN3.type==temp_amb)             
                {Ko.IN3.value=AMB_TEMP_INPUT_R(2); Ko.IN3.resolution=1;}    
            else if (Ko.IN3.type==hum_amb)             
                {Ko.IN3.value=AMB_HUM_INPUT_R(2);  Ko.IN3.resolution=1;}     
            else if (Ko.IN3.type==in_remote)
                {Ko.IN3.resolution=1;}
            else if (Ko.IN3.type==in_modbus)
                {   
                Ko.IN3.value=MODBUS_INPUT_R(Ko.IN3.address,Ko.IN3.modbus_start_register,Ko.IN3.modbus_coils_qty,Ko.IN3.modbus_type);
                Ko.IN3.resolution=1;
                }
            else
                {Ko.IN3.value=0;}
            
            Ko.IN3.value=INPUT_SCALING_ALGORITHM(Ko.IN3.Array);
            }
        else
            {Ko.IN3.value=0;}
       
        // Input 4
            if (Ko.IN4.enable==1)
            {
            if (Ko.IN4.type==digital_input)
                {Ko.IN4.value=READ_ANALOGS_AS_DIGITAL_INPUT(3);}    
            else if (Ko.IN4.type==i4to20mA)
                {Ko.IN4.value=i4to20mA_INPUT_R(3);}    
            else if (Ko.IN4.type==v0to10V)
                {Ko.IN4.value=V0to10V_INPUT_R(3);}  
            else if (Ko.IN4.type==temp_ntc)             
                {Ko.IN4.value=NTC_TEMP_INPUT_R(3);}
            else if (Ko.IN4.type==temp_amb)             
                {Ko.IN4.value=AMB_TEMP_INPUT_R(3); Ko.IN4.resolution=1;}    
            else if (Ko.IN4.type==hum_amb)             
                {Ko.IN4.value=AMB_HUM_INPUT_R(3);  Ko.IN4.resolution=1;}     
            else if (Ko.IN4.type==in_remote)
                {Ko.IN4.resolution=1;}
            else if (Ko.IN4.type==in_modbus)
                {   
                Ko.IN4.value=MODBUS_INPUT_R(Ko.IN4.address,Ko.IN4.modbus_start_register,Ko.IN4.modbus_coils_qty,Ko.IN4.modbus_type);
                Ko.IN4.resolution=1;
                }
            else
                {Ko.IN4.value=0;}
            
            Ko.IN4.value=INPUT_SCALING_ALGORITHM(Ko.IN4.Array);
            }
        else
            {Ko.IN4.value=0;}

        // Input 5
            if (Ko.IN5.enable==1)
            {
            if (Ko.IN5.type==digital_input)
                {Ko.IN5.value=READ_ANALOGS_AS_DIGITAL_INPUT(4);}    
            else if (Ko.IN5.type==i4to20mA)
                {Ko.IN5.value=i4to20mA_INPUT_R(4);}    
            else if (Ko.IN5.type==v0to10V)
                {Ko.IN5.value=V0to10V_INPUT_R(4);}  
            else if (Ko.IN5.type==temp_ntc)             
                {Ko.IN5.value=NTC_TEMP_INPUT_R(4);}
            else if (Ko.IN5.type==temp_amb)             
                {Ko.IN5.value=AMB_TEMP_INPUT_R(4); Ko.IN5.resolution=1;}    
            else if (Ko.IN5.type==hum_amb)             
                {Ko.IN5.value=AMB_HUM_INPUT_R(4);  Ko.IN5.resolution=1;}     
            else if (Ko.IN5.type==in_remote)
                {Ko.IN5.resolution=1;}
            else if (Ko.IN5.type==in_modbus)
                {   
                Ko.IN5.value=MODBUS_INPUT_R(Ko.IN5.address,Ko.IN5.modbus_start_register,Ko.IN5.modbus_coils_qty,Ko.IN5.modbus_type);
                Ko.IN5.resolution=1;
                }
            else
                {Ko.IN5.value=0;}
            
            Ko.IN5.value=INPUT_SCALING_ALGORITHM(Ko.IN5.Array);
            }
        else
            {Ko.IN5.value=0;}

        // DC Power Supply 
        SUPPLY_VDC_READER(0);                             // Calculate Power Supply Voltage


    }
}

int Inputs::READ_ANALOGS_AS_DIGITAL_INPUT (unsigned char CHN) {        // Digital input: Dry contact.          
// In this type of input, a contactor is placed at the input, then, if the contactor is: opened=0 , closed=1.
        if (READ_A.TEN_READINGS_SUM[CHN]>20480)  
            return 0;                           // If the voltage is greater than the half of the scale (1.65V), it indicates that the contactor is open.
        else
            return 1;                           // In the contrary case, the contactor is closed.
}

short Inputs::i4to20mA_INPUT_R (unsigned char CHN) {     // Analog input read: 4-20 mA.
/* For calculating the 4..20mA current:
    1) The voltage read at the Input is calculated with the next formula:  Readinf of 10 samples of the A/D channel/10  * 3.3V /4096
    2) Because the sensor is pre-polarized (internally) with a 10K resistor, From this reading 0.0488V is subtracted, which is caused by the current flowing from VCC through the 10K 
       Pull-UP resistor and the 150 Ohms resistor.
    3) The value is divided by the 4-20mA conversion resistor (150 Ohms or divide 0.150 for mA).  
    4) The result is Multiplied by 100.0 (The result is scaled by 100)
*/
    float I_CAL;
    
    I_CAL= (float) READ_A.TEN_READINGS_SUM[CHN]/10.0;
    I_CAL= (I_CAL*3.3)/4096.0;                        
    I_CAL= 100.0*(I_CAL - 0.0488)/0.150;                
    
    if(I_CAL<0)
        I_CAL=0;
    
    return  round (I_CAL);  // 0.5 is added for rounding purposes
}

short Inputs::V0to10V_INPUT_R (unsigned char CHN) {      // Analog input read: 0-10 V.
/*
* Get DC voltage 0 to 10 VDC
 * Based on an external 2.2K pin-to-Ground voltage divider and a series resistor with the voltage of 10K
 * Because the sensor is pre-polarized (internally) with a 10K resistor, and having a 2.2K base resistance
 * The conversion formula = VB= 6.545 VN - 3.3
 * The result is Multiplied by 100.0 (the result is scaled by 100)
  */
    float V_CAL;
    
    V_CAL= (float) READ_A.TEN_READINGS_SUM[CHN]/10.0;
    V_CAL= (V_CAL*3.3)/4096.0;            // Calculate the reading voltage
    V_CAL= 6.545*V_CAL-3.3;
    if(V_CAL<0)
        V_CAL=0;
    return round (100.0*V_CAL);     // 0.5 is added for rounding purposes
}


short Inputs::NTC_TEMP_INPUT_R (unsigned char CHN)
{
// Get the temperature from  thermistor NTC  10K,   The NTC is polarized by Internal 10K resistor
// 1)  Find the interval between which the sum of the last 10 readings of the A/D converter is in the Thermistor 10K (NTC)  data table
// 2)  Each Interval in NTC table is of 5 °C
// 3)  The result is the linear regression of the data in this interval and It is Scaled by 10

unsigned short DELTAi;
long int T_CAL;
unsigned char Vi=0;
char s;

	if (READ_A.TEN_READINGS_SUM[CHN] >TEMP_TABLE[0])    // If the value is bigger than Table[0] (begin of table), Temperarature < 50°C
		{T_CAL=-501;}                                   // Return -50.1°C
	else if (READ_A.TEN_READINGS_SUM[CHN] <= TEMP_TABLE[34])   // If the value is Lower  than Table[34] (end of table), Temperarature > 120°C
		{T_CAL=1201;}                                   // Return 120.1°C
	
    else                                                // Now Find the interval of 10 radings of A/D Data converted in the table   
		{     
            if  (READ_A.TEN_READINGS_SUM[CHN]>=TEMP_TABLE[10])      
                if  (READ_A.TEN_READINGS_SUM[CHN]>=TEMP_TABLE[5])
                    Vi=0;                               // Pre-Interval 0
                else
                    Vi=5;                               
            else if  (READ_A.TEN_READINGS_SUM[CHN]>=TEMP_TABLE[20])
                if  (READ_A.TEN_READINGS_SUM[CHN]>=TEMP_TABLE[15])    
                    Vi=10;                             
                else
                    Vi=15;                             
            else if  (READ_A.TEN_READINGS_SUM[CHN]>=TEMP_TABLE[30])
                if  (READ_A.TEN_READINGS_SUM[CHN]>=TEMP_TABLE[25])    
                    Vi=20;  
                else
                    Vi=25;
            else
                Vi=30;
                

		while (READ_A.TEN_READINGS_SUM[CHN]<=TEMP_TABLE[Vi+1])          // Find the exactly interval
			Vi++;                                                  

		// Calculate the temperature by Linear Regression
        DELTAi = TEMP_TABLE[Vi]-TEMP_TABLE[Vi+1];                       // Deta of readings
		T_CAL=  (TEMP_TABLE[Vi]-READ_A.TEN_READINGS_SUM[CHN]);
        T_CAL*=50;                                                      // Escaled by 5 (interval of table)  and by 10 for 0.1°C of Resolution
        
		if ((T_CAL%DELTAi)>(DELTAi/2))                                  // Calculate if the reading Division Module is Bigger thant the half of Inteval for Better Aproximation
			s=1;                                                        // If yes sum 1
		else
			s=0;
		T_CAL=  T_CAL/(DELTAi)+s;                                       // Linear calculation into the interval

       
        T_CAL = T_CAL+50*(Vi-10);                                       // Sums the temperature base of the interval  (Multiplied by 50 = 5°C scaled by 10,  and Vi-10 is because the table Stars in -50°C)
        }
return T_CAL;
}

short Inputs::AMB_TEMP_INPUT_R(unsigned char CHN)
{
/*  We use the IC : SHT31-ARP-B2.5kS  ANALOG SENSOR FOR TEMPERATURE AND RH
    T(C) = -66.875+218.75*Vt/VDD;
 *  VDD = 3.3V;
 *  Vt=SUM_10LECT/40950*VDD
 *  temp=-66.875+218.75*SUM_10LECT/40950,
 */
    
    float temp;
    temp=(float) READ_A.TEN_READINGS_SUM[CHN];
    temp=temp/40950.0;               
    temp=-66.875+218.75*temp;          
    temp= round(10.0*temp);      // Scaled by 10
    return (short) temp;  
    
}

short Inputs::AMB_HUM_INPUT_R(unsigned char CHN)
{
/*  We use the IC : SHT31-ARP-B2.5kS  ANALOG SENSOR FOR TEMPERATURE AND RH
    HR(%) = -12.5+125*Vt/VDD;
    VDD = 3.3V;
 *  Vt=SUM_10LECT/40950*VDD;
 */
    
    float rel_hum;
    rel_hum=(float) READ_A.TEN_READINGS_SUM[CHN];
    rel_hum=rel_hum/40950.0;
    rel_hum=-12.5+125.0*rel_hum;  
    rel_hum=round(10.0*rel_hum);         // Scaled by 10
    if (rel_hum>1000.0)
        rel_hum=1000.0;
    else if (rel_hum<0.0)
        rel_hum=0.0;
    
    return (short) rel_hum; 
    
}

void Inputs::SUPPLY_VDC_READER(char ini) 
// The resistors used in the voltage divider to read the 12V-24V Supply Voltage are 10K and 1.5K
// The voltage read is calculated in  volts (Scaled by 10) as follows:
// CAL_V= SUM_10_READINGS /10 * (3.3/4096) * 11.5 /(1.5) + 1.4
// SUM_1_ READINGS is already is divided by 10
// 3.3/4096: ADC conversion factor to real voltage since external reference voltage is used 3.3 and the conversor is 12 bit 2^12=4096
// 11.5 and 1.5: Values ​​given by the voltage divider resistors.
// Add 1.4 Volts is the voltage drop across the diode bridge if the power is from an external 12V or 24V source
// If the Supply is internal (By USB Cable)  don´t rest the 1.4V
//--------------------------
{
float V_CAL;

if(Ko.VDC.enable==1)
    {
    V_CAL = (READ_A.TEN_READINGS_SUM[5])/10;                            // Divided by 10
    V_CAL=(V_CAL*11.5*3.3)/(1.5*4096.0);                                // Resistor divisor are:  10K and 1.5K = 11.5 /1.5
    V_CAL=V_CAL*10;                                                     // Scaled by 10 (0.1V of resolution)
    Ko.VDC.value = round (V_CAL);                                       // 0.5 is added for rounding purposes
    }
else
    Ko.VDC.value=0;
    
    Ko.VDC.resolution=1;

}

//----------------------------------------------------------
void Inputs::READ_VAC(void)
// The measured voltage is calculated by measuring the pulse width generated when the AC voltage exceeds the threshold of 55V AC
// The pulse width in high state is captured with Timer 3, which counts in a scale of 4 microseconds.
// The capture function delivers the TM3 values in the Time_Voltage[8] table

/* To calculate the voltage:
1) The 8 readings of the pulse in high state are averaged, but we are interested in the low state time.
2) The total pulse width in low state =  1/60 - pulse width in high state.
3) The following calculation formula is used, see http://www.radiolocman.com/shem/schematics.html?di=162524
 * VIN = VE / Cos(Pi*f*Ttotal),  This is the amplitude of the voltage in volts
 * VE = the threshold voltage at 55V
 * VAC = VIN/√2;  For RMS calculation.
 * 
 *    
*/  
//--------------------------
{
float CAL_V = 0;
unsigned char i;
unsigned int FRt = 0;
uint64_t time=0, time2=0;
const int max_timer = 3;
if (Ko.VAC.enable == 1)
    {
    Ko.TIMERS.maxtime_read_vac=0;
    while ((TLA2528.digitalReadIO(tla2528_i2c_address_inputs,DIVAC)==0) && (Ko.TIMERS.maxtime_read_vac<max_timer));
    if (Ko.TIMERS.maxtime_read_vac<max_timer)
        {
        Ko.TIMERS.maxtime_read_vac=0;
        while ((TLA2528.digitalReadIO(tla2528_i2c_address_inputs,DIVAC)==1)&&(Ko.TIMERS.maxtime_read_vac<max_timer));          // Wait Until The Value Is Zero
        if (Ko.TIMERS.maxtime_read_vac<max_timer)
            {  
            Ko.TIMERS.maxtime_read_vac=0;
            time=Ti.get_counter_value();
            while ((TLA2528.digitalReadIO(tla2528_i2c_address_inputs,DIVAC)==0)&&(Ko.TIMERS.maxtime_read_vac<max_timer));
            if (Ko.TIMERS.maxtime_read_vac<max_timer)
                {  
                time2=Ti.get_counter_value();
                if(time2>time)
                    time=time2-time;
                else
                    time=time2+(10000-time);
                }
            else
                time=0;
            }
        else
            time=0;
        }
    else
       time=0;
        
   ENG.DELTA_TIME=time-ENG.MEAN_TIME/10;              // We need to aply a filter of the reading time values
   
   if(ENG.DELTA_TIME>=150)
       {
       ENG.Prom_TIME[ENG.Vx]=time;
       }
   else if(ENG.DELTA_TIME>=10)
       {
       ENG.Prom_TIME[ENG.Vx]=ENG.MEAN_TIME/10+10;  
       }
   else if(ENG.DELTA_TIME<=-150)
       {
        ENG.Prom_TIME[ENG.Vx]=time; 
       }
   else if(ENG.DELTA_TIME<=-10)
       {
        ENG.Prom_TIME[ENG.Vx]=ENG.MEAN_TIME/10-10;  
       }
   else
        ENG.Prom_TIME[ENG.Vx]=time; 

    ENG.MEAN_TIME= 0;
    for(i=0;i<10;i++)
      {
        ENG.MEAN_TIME+=ENG.Prom_TIME[i]; 
      }
    
    
    if (++ENG.Vx >= 10)
       ENG.Vx=0;

    FR.Read_Frequency=60.0;
    CAL_V = (float) ENG.MEAN_TIME/10.0-25;                            //-25 TICS it´s for delay en read pulses                                 
    if (CAL_V>0)
        {
        CAL_V = (CAL_V*3.1416*FR.Read_Frequency)/1000000.0;           // The width of each pulse is 1us,  1/1us = 1,000,000
        CAL_V = 520.0 / (cos(CAL_V));                                         // Adjustment to compensate for heating and reading errors
                                                                              // 52.0 multiplied by 10 for one decimal resolution 
        Ko.VAC.value= round(CAL_V);
        if (Ko.VAC.value < 0)
        Ko.VAC.value = 0;                                                                   
        }
    else
        Ko.VAC.value=0;

    }
else 
    Ko.VAC.value=0;

    Ko.VAC.resolution = 1;

}

void Inputs::INIT_VAC(void)
{
    int i;
    
    for (i = 0; i < 10; i++)
        {
        READ_VAC();
        }
}

void Inputs::sortDescending(int *arr, int n) {
    float temp; int i,j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                // Swap if the current element is smaller than the next one
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

//----------------------------------------------------------        
void Inputs::READ_IAC(void)
{
// To read the current, the peak voltage of the signal is measured for 20 ms
// The peak-to-peak voltage is divided by 2 to obtain VP
// The peak voltage is converted to VRMS
// I = VRMS/RLOAD  * N_turns * 100
// Where RLOAD is the load resistance value for the current transformer
// N_turns is the transformer ratio
// 100 is the normalized value to scale the measurement
    
float CAL_I;
unsigned char i;

int MAX_PEAK = 0, MIN_PEAK = 4096, NEW_READ=0;   
    
    
    Ko.TIMERS.maxtime_read_iac=3;       // The variable is decremented every 10 ms in timer 0, ensuring sampling between 18 and 20 ms
    int samples = 0;
    while (Ko.TIMERS.maxtime_read_iac > 0)
        {
        NEW_READ=TLA2528.analogReadIO(tla2528_i2c_address_inputs,ANIAC);
        samples++;
        if (NEW_READ > MAX_PEAK)
            MAX_PEAK = NEW_READ;
        else if (NEW_READ < MIN_PEAK)
            MIN_PEAK = NEW_READ;
        else;
        }
    
    CAL_I = (MAX_PEAK - MIN_PEAK) / 2;   // Calculate the peak value
    CAL_I = CAL_I * 3.3 / 4096;          // Normalize to volts based on the converter ratio
    CAL_I = CAL_I / 1.414;               // Convert to RMS
    CAL_I = (10.0 * (float) Ko.IAC.Turns * CAL_I) / (float) Ko.IAC.Rload;  // Scale current value by 10 for two decimal precision
    
    if (ENG.Ix >= 4)
        ENG.Ix = 0;
    
    ENG.Prom_IAC[ENG.Ix++] = CAL_I;
    
    ENG.SUMA_IAC = 0;
    for (i = 0; i < 4; i++)
        {
        ENG.SUMA_IAC += ENG.Prom_IAC[i];
        }
    
    i = 0;
    if ((ENG.SUMA_IAC % 4) > 2)
        i = 1;
    Ko.IAC.value = ENG.SUMA_IAC / 4 + i;  // Calculate the average to one decimal place
    
    
}


void Inputs::INIT_IAC(void)
{
    int i;
    
    for (i = 0; i < 4; i++)
        {
        READ_IAC();
        }
}


//------------------------------------------------------------------------------
//  Init the A/D channels
//------------------------------------------------------------------------------

void Inputs::INIT_ANALOG_INPUTS(void)
{
    TLA2528.begin();
    uint8_t i;

        Jx1=0;                                              // Init stack index
        for (i = 0; i<10;i++)
            {
             READ_ANALOG_AND_STORING ();                    // Store the firt 10 readings of A/D conversor for each channel
            }
            
}


// Read A/D channels and stored them in the stack of each one
void Inputs::READ_ANALOG_AND_STORING(void)
{
    uint8_t j,k;
    uint16_t SUMMATORY;
    READ_A.CHN_DATA[0][Jx1]=TLA2528.analogReadIO(tla2528_i2c_address_inputs,AN1);
    READ_A.CHN_DATA[1][Jx1]=TLA2528.analogReadIO(tla2528_i2c_address_inputs,AN2);
    READ_A.CHN_DATA[2][Jx1]=TLA2528.analogReadIO(tla2528_i2c_address_inputs,AN3);
    READ_A.CHN_DATA[3][Jx1]=TLA2528.analogReadIO(tla2528_i2c_address_inputs,AN4);
    READ_A.CHN_DATA[4][Jx1]=TLA2528.analogReadIO(tla2528_i2c_address_inputs,AN5);
    READ_A.CHN_DATA[5][Jx1]=TLA2528.analogReadIO(tla2528_i2c_address_inputs,ANVDC);
       
    if (++Jx1>=10)                                                  // Increases the stack pointer
        Jx1=0;

    for (k=0;k<6;k++)                                               // Add the value of the last 10 readings for each A/D channel            
        {
        SUMMATORY=0;
        for (j=0;j<10;j++)
            SUMMATORY= SUMMATORY+READ_A.CHN_DATA[k][j];

        READ_A.TEN_READINGS_SUM[k]=SUMMATORY;                       //Store the result of the sum of the 10 A/D readings for each channel
        }
}



//------------------------------------------------------------------------------
int Inputs::MODBUS_INPUT_R(int8_t slave_address, int16_t Start_Address, int16_t Coils_No, int8_t sens_type)
{
    int Valor_L=-501;
    union{
        uint8_t datos[4];
        float  valor;
    }Valor_Float;
    
    Ko.MODBUS.slave_address= slave_address;                       // Modbus address (number between 1 and 247)
    Ko.MODBUS.funtion_code=3;                                     // Funtion Read Coils
    Ko.MODBUS.start_address=Start_Address;                        // Address of the register (to be read/written)
    Ko.MODBUS.coils_no=Coils_No; 

    Ko.MODBUS=Modbus.Modbus_Telegram(Ko.MODBUS);                             // Send Modbus Telegram to the sensor and wait for Answer
    
    if(sens_type==0)              // Integer ?
        {
        Valor_L=(Ko.MODBUS.registers[3]*256+Ko.MODBUS.registers[4])*10;
        }
     if(sens_type==1)             //Integer 1 digit ?
        {
        Valor_L=(Ko.MODBUS.registers[3]*256+Ko.MODBUS.registers[4]);
        }
     if(sens_type==2)            // Integer 2 digits ?
        {
        Valor_L=(Ko.MODBUS.registers[3]*256+Ko.MODBUS.registers[4])/10;
        }
     else if (sens_type==3)      // Little-Endiand
        {
        Valor_Float.datos[0]=Ko.MODBUS.registers[3];
        Valor_Float.datos[1]=Ko.MODBUS.registers[4];
        Valor_Float.datos[2]=Ko.MODBUS.registers[5];
        Valor_Float.datos[3]=Ko.MODBUS.registers[6];
        Valor_L=(int) (Valor_Float.valor*10.0);
        }
    
     else if (sens_type==4)      // Big-Endiand
        {
        Valor_Float.datos[0]=Ko.MODBUS.registers[6];
        Valor_Float.datos[1]=Ko.MODBUS.registers[5];
        Valor_Float.datos[2]=Ko.MODBUS.registers[4];
        Valor_Float.datos[3]=Ko.MODBUS.registers[3];
        Valor_Float.valor*=10.0;
        Valor_L= (int)(Valor_Float.valor);
        }
    else if (sens_type==5)      // Little-Endiand Byte Swap 
        {
        Valor_Float.datos[0]=Ko.MODBUS.registers[4];
        Valor_Float.datos[1]=Ko.MODBUS.registers[3];
        Valor_Float.datos[2]=Ko.MODBUS.registers[6];
        Valor_Float.datos[3]=Ko.MODBUS.registers[5];
        Valor_L=(int) (Valor_Float.valor*10.0);
        }
    
     else if (sens_type==4)       //Big-Endiand Byte swap
        {
        Valor_Float.datos[0]=Ko.MODBUS.registers[5];
        Valor_Float.datos[1]=Ko.MODBUS.registers[6];
        Valor_Float.datos[2]=Ko.MODBUS.registers[3];
        Valor_Float.datos[3]=Ko.MODBUS.registers[4];
        Valor_Float.valor*=10.0;
        Valor_L= (int)(Valor_Float.valor);
        }

    return Valor_L;
}

//  Funtion for Scaling the inputs 
//  Value = (Value - Offset)/Slope
//  The analog inputs are limited to 12 Bits in KONTROLOG MAX,  -2048 to 2047, 
int16_t Inputs::INPUT_SCALING_ALGORITHM(int16_t *input)
{
    IN_t IN_T;
    int i;
    for(i=0;i<16;i++)
        IN_T.Array[i]=input[i];

    float calc =(float)IN_T.value/pow10(IN_T.resolution);
    calc=calc+(float)IN_T.offset/10.0;
    calc=calc*(float)IN_T.slope/1000.0;
    IN_T.value=(int)(calc*pow10(IN_T.resolution));   

    if(IN_T.resolution>0)
        {
        if(IN_T.value>2047)
            IN_T.value=2047;
        else if(IN_T.value<-2048)
            IN_T.value=-2048;
        else;
        }
    else                        // Counters
        {
        if(IN_T.value>4095)
            IN_T.value=4095;
        }
    return IN_T.value;
}


/* --------------------------------------------------------------------------------
//  DIGITAL INPUTS CHANNELS 6 to 8  of Kontrolog MAX
// --------------------------------------------------------------------------------
Configuration Options
1) Digital Input
2) Counter Input
3) Frequency Input HZ
4) Frequency Input RPM
5) Digital Temperature Sensor DS18B20 (Only Inputs 3 and 4)

*/

// Digital Inputs

void Inputs::INIT_DIGITAL_INPUTS(uint8_t selected_input, uint8_t previos_type)
{
    int i=0;
    // IN PIN6
    switch(selected_input)
    {
    case 6:
        {
        if((previos_type==counter_cumulative)||(previos_type==counter_reset)||(previos_type==frequency_Hz)||(previos_type==frequency_rpm))
            destroyCounter(6);                      // If Pulse Counter was enabled,  Stop and free the resource.
        
        if(Ko.IN6.type==digital_input)
            {
            pinMode(IN6_PIN,INPUT_PULLDOWN);
            }
        else if((Ko.IN6.type==counter_cumulative)||(Ko.IN6.type==counter_reset)||(Ko.IN6.type==frequency_Hz)||(Ko.IN6.type==frequency_rpm))
            {
            Counter_Input_setup(6,Ko.IN6.Pulse_Edge);
            for(i=0;i<10;i++)
                RPM.IN6[i]=0;
            RPM.CounterI6=0;
            }
        else if((Ko.IN6.type==runtime)||(Ko.IN6.type==runtime_reset))
            {
            pinMode(IN6_PIN,INPUT_PULLDOWN);
            Ko.IN6.value=0;
            }
        
        else if (Ko.IN6.type==in_remote)
                {Ko.IN6.resolution=1;}
        
        else if(Ko.IN6.type==in_modbus)
            Ko.IN6.resolution=1;

        else if(Ko.IN6.type==temp_ds18b20)
            {
            pinMode(IN6_PIN,INPUT_PULLUP);
            sensor6_ds18b20.begin();                      // Inicia el sensor DS18B20
            }
        else;
        }
    break;
    // IN PIN7
    case 7:
        {
        if((previos_type==counter_cumulative)||(previos_type==counter_reset)||(previos_type==frequency_Hz)||(previos_type==frequency_rpm))
            destroyCounter(7);                      // If Pulse Counter was enabled,  Stop and free the resource.
        
        if(Ko.IN7.type==digital_input)
            {
            pinMode(IN7_PIN,INPUT_PULLDOWN);
            }
        else if((Ko.IN7.type==counter_cumulative)||(Ko.IN7.type==counter_reset)||(Ko.IN7.type==frequency_Hz)||(Ko.IN7.type==frequency_rpm))
            {
            Counter_Input_setup(7,Ko.IN7.Pulse_Edge);
            for(i=0;i<10;i++)
                RPM.IN7[i]=0;
            RPM.CounterI7=0;
            }
        else if((Ko.IN7.type==runtime)||(Ko.IN7.type==runtime_reset))
            {
            pinMode(IN7_PIN,INPUT_PULLDOWN);
            Ko.IN7.value=0;
            }
        else if (Ko.IN7.type==in_remote)
                {Ko.IN7.resolution=1;}
        
        else if(Ko.IN7.type==in_modbus)
            Ko.IN7.resolution=1;
        
        else if(Ko.IN7.type==temp_ds18b20)
            {
            pinMode(IN7_PIN,INPUT_PULLUP);
            sensor7_ds18b20.begin();   
            }
        }
    break;
    // IN PIN8
    case 8:
        {
        if((previos_type==counter_cumulative)||(previos_type==counter_reset)||(previos_type==frequency_Hz)||(previos_type==frequency_rpm))
            destroyCounter(8);                      // If Pulse Counter was enabled,  Stop and free the resource.
        
        if(Ko.IN8.type==digital_input)
            {
            pinMode(IN8_PIN,INPUT_PULLDOWN);
            }
        else if((Ko.IN8.type==counter_cumulative)||(Ko.IN8.type==counter_reset)||(Ko.IN8.type==frequency_Hz)||(Ko.IN8.type==frequency_rpm))
            {
            Counter_Input_setup(8,Ko.IN8.Pulse_Edge);
            for(i=0;i<10;i++)
                RPM.IN8[i]=0;
            RPM.CounterI8=0;
            }
        else if((Ko.IN8.type==runtime)||(Ko.IN8.type==runtime_reset))
            {
            pinMode(IN8_PIN,INPUT_PULLDOWN);
            Ko.IN8.value=0;
            }
        else if (Ko.IN8.type==in_remote)
                {Ko.IN8.resolution=1;}

        else if(Ko.IN8.type==in_modbus)
            Ko.IN8.resolution=1;
        }   
    break;
    }
}

void Inputs::DIGITAL_INPUTS_READER(void) {          

        // Input 6
        if (Ko.IN6.enable==1)
            {
            Ko.IN6.resolution=0;
            if (Ko.IN6.type==digital_input)
                {Ko.IN6.value=GET_DIGITAL_INPUT_STATUS(6);}
            else if ((Ko.IN6.type==counter_cumulative)||(Ko.IN6.type==counter_reset))
                {Ko.IN6.value=Counter_Reader(6);Ko.IN6.resolution=0;}    
            else if (Ko.IN6.type==frequency_Hz)              // Frequency is reading every second in Timer0_ISR: Timers.cpp
                {Ko.IN6.resolution=0;}
            else if(Ko.IN6.type==frequency_rpm)
                {Ko.IN6.value=CAL_DIGITAL_INPUT_RPM(6);Ko.IN6.resolution=0;}          
            else if ((Ko.IN6.type==runtime)||(Ko.IN6.type==runtime_reset))  // Runtime is reading every second in Timer0_ISR: Timers.cpp
                {Ko.IN6.resolution=0;}
            
            else if (Ko.IN6.type==in_remote)
                {Ko.IN6.resolution=1;}
            
            else if (Ko.IN6.type==in_modbus)
                {
                Ko.IN6.value=MODBUS_INPUT_R(Ko.IN6.address,Ko.IN6.modbus_start_register,Ko.IN6.modbus_coils_qty,Ko.IN6.modbus_type); 
                Ko.IN6.resolution=1;
                }

            else if(Ko.IN6.type==temp_ds18b20)
                {Ko.IN6.value=get_ds18b20_temp(6);Ko.IN6.resolution=1;}
            else
                {Ko.IN6.value=0;}    
            }
        else
            {Ko.IN6.value=0;}    

        // Input 7
        if (Ko.IN7.enable==1)
            {
            Ko.IN7.resolution=0;
            if (Ko.IN7.type==digital_input)
                {Ko.IN7.value=GET_DIGITAL_INPUT_STATUS(7);}
            else if ((Ko.IN7.type==counter_cumulative)||(Ko.IN7.type==counter_reset))
                {Ko.IN7.value=Counter_Reader(7);}
            else if (Ko.IN7.type==frequency_Hz)              // Frequency is reading every second in Timer0_ISR: Timers.cpp
                {Ko.IN7.resolution=0;} 
            else if(Ko.IN7.type==frequency_rpm)
                {Ko.IN7.value=CAL_DIGITAL_INPUT_RPM(7);Ko.IN8.resolution=0;}
            else if ((Ko.IN7.type==runtime)||(Ko.IN7.type==runtime_reset))  // Runtime is reading every second in Timer0_ISR: Timers.cpp
                {Ko.IN7.resolution=0;}
            
            else if (Ko.IN7.type==in_remote)
                {Ko.IN7.resolution=1;}
            
            else if (Ko.IN7.type==in_modbus)
                {
                Ko.IN7.value=MODBUS_INPUT_R(Ko.IN7.address,Ko.IN7.modbus_start_register,Ko.IN7.modbus_coils_qty,Ko.IN7.modbus_type); 
                Ko.IN7.resolution=1;
                }
            else if(Ko.IN7.type==temp_ds18b20)
                {Ko.IN7.value=get_ds18b20_temp(7);Ko.IN7.resolution=1;}
            else
                {Ko.IN7.value=0;}    
            }
        else
            {Ko.IN7.value=0;}   

        // Input 8
        if (Ko.IN8.enable==1)
            {
            Ko.IN8.resolution=0;
            if (Ko.IN8.type==digital_input)
                {Ko.IN8.value=GET_DIGITAL_INPUT_STATUS(8);}
            else if ((Ko.IN8.type==counter_cumulative)||(Ko.IN8.type==counter_reset))
                {Ko.IN8.value=Counter_Reader(8);}
            else if (Ko.IN8.type==frequency_Hz)              // Frequency is reading every second in Timer0_ISR: Timers.cpp
                {Ko.IN8.resolution=0;} 
            else if(Ko.IN8.type==frequency_rpm)
                {Ko.IN8.value=CAL_DIGITAL_INPUT_RPM(8);Ko.IN8.resolution=0;}
            else if ((Ko.IN8.type==runtime)||(Ko.IN8.type==runtime_reset)) // Runtime is reading every second in Timer0_ISR: Timers.cpp
                 {Ko.IN8.resolution=0;}
            else if (Ko.IN8.type==in_remote)
                {Ko.IN1.resolution=1;}
            else if (Ko.IN8.type==in_modbus)
                {
                Ko.IN8.value=MODBUS_INPUT_R(Ko.IN8.address,Ko.IN8.modbus_start_register,Ko.IN8.modbus_coils_qty,Ko.IN8.modbus_type); 
                Ko.IN8.resolution=1;
                }
            else
                {Ko.IN8.value=0;}    
            }
        else
            {Ko.IN8.value=0;}   
     
}


int Inputs::GET_DIGITAL_INPUT_STATUS(int8_t input_channel)
{
    if(input_channel==6)
        return digitalRead(IN6_PIN);
    else if (input_channel==7)
        return digitalRead(IN7_PIN);
    else if (input_channel==8)
        return digitalRead(IN8_PIN);
    else 
        return 0;
}

int16_t Inputs::CAL_DIGITAL_INPUT_RPM(int8_t input_channel)
{
    int32_t FRPM=0; int i;
    if(input_channel==6)
        {
           for(i=0;i<=In.RPM.CounterI6;i++) 
                FRPM+=In.RPM.IN6[i];
            
            FRPM= FRPM*60/(In.RPM.CounterI6+1);

            if(++In.RPM.CounterI6>=9)      // Clear the last sample
                {
                In.RPM.CounterI6=9;
                    for(i=0;i<9;i++)
                        {
                        In.RPM.IN6[i]=In.RPM.IN6[i+1];   
                        }
                }
        }

    else if(input_channel==7)
        {
           for(i=0;i<=In.RPM.CounterI7;i++) 
                FRPM+=In.RPM.IN7[i];
            
            FRPM= FRPM*60/(In.RPM.CounterI7+1);

            if(++In.RPM.CounterI7>=9)      // Clear the last sample
                {
                In.RPM.CounterI7=9;
                    for(i=0;i<9;i++)
                        {
                        In.RPM.IN7[i]=In.RPM.IN7[i+1];   
                        }
                }
        }

    else if(input_channel==8)
        {
           for(i=0;i<=In.RPM.CounterI8;i++) 
                FRPM+=In.RPM.IN8[i];
            
            FRPM= FRPM*60/(In.RPM.CounterI8+1);

            if(++In.RPM.CounterI8>=9)      // Clear the last sample
                {
                In.RPM.CounterI8=9;
                    for(i=0;i<9;i++)
                        {
                        In.RPM.IN8[i]=In.RPM.IN8[i+1];   
                        }
                }
        }
        if (FRPM>32767)
            return 32767;
        return FRPM;
}


void Inputs::Counter_Input_setup(uint8_t input_channel, bool edge_type) {

    get_counter_channel(input_channel);

  // Configure the pulse counter
    pcnt_config_t pcnt_config = {
        .pulse_gpio_num = GPIO_PIN_COUNTER,  // GPIO pin where the button is connected,  // GPIO pin for pulses
        .ctrl_gpio_num = PCNT_PIN_NOT_USED,  // Control pin (not used in this example)
        .lctrl_mode = PCNT_MODE_KEEP,        // Low control mode (keep the value)
        .hctrl_mode = PCNT_MODE_KEEP,       // High control mode (keep the value)
        .pos_mode = PCNT_COUNT_INC,         // Increment counter on rising edges
        .neg_mode = PCNT_COUNT_DIS,         // Do not counter ON falling edges
        .counter_h_lim = 32767,             // Upper limit of the counter
        .counter_l_lim = 0,                 // Lower limit of the counter
        .unit = PULSE_COUNT_UNIT,           // Counter unit
        .channel = PCNT_CHANNEL_0           // Counter channel
  };

    if (edge_type==0)                    // Change pulse detect mode, if counter mode==0 (Falling edge);
        {
        pcnt_config.pos_mode=PCNT_COUNT_DIS;
        pcnt_config.neg_mode=PCNT_COUNT_INC;
        }


  pcnt_unit_config(&pcnt_config);       // Configure the counter unit

    // Enable glitch filter if necessary
  pcnt_set_filter_value(PULSE_COUNT_UNIT, 1023);   // Pulses filter  ex: 4000/80Mhz = 50uS minimal pulse duration  (Increase if need better filter)
  pcnt_filter_enable(PULSE_COUNT_UNIT);
  
  // Initialize the counter to zero
  pcnt_counter_pause(PULSE_COUNT_UNIT);     // Pause the counter
  Counter_clear(input_channel,1);             // Clear the counter
  pcnt_counter_resume(PULSE_COUNT_UNIT);    // Resume the counter

}

int16_t Inputs::Counter_Reader(uint8_t input_channel) {
  
  int16_t counter_value = 0;
  esp_err_t error_flag;
  get_counter_channel(input_channel);
  error_flag=pcnt_get_counter_value(PULSE_COUNT_UNIT, &counter_value);  // Get the current counter value
  if(error_flag!=ESP_OK)
    {
    Serial.println("Error de contador");
    pcnt_counter_pause(PULSE_COUNT_UNIT); 
    INIT_DIGITAL_INPUTS(input_channel,counter_cumulative);             // Detiene el contador y lo reinicia.
    }
  return counter_value;
}

void Inputs::Counter_clear(uint8_t input_channel, bool clear_input) {
  get_counter_channel(input_channel);

  pcnt_counter_clear(PULSE_COUNT_UNIT);  // Clear the counter
  if(clear_input==1)
    {
        if(input_channel==6)
            Ko.IN6.value=0;
        else if(input_channel==7)
            Ko.IN7.value=0;
        else if(input_channel==8)
            Ko.IN8.value=0;
        else;
    }
}


void Inputs::destroyCounter(uint8_t input_channel) {
  get_counter_channel(input_channel);
  pcnt_counter_pause(PULSE_COUNT_UNIT);  // Pause the counter
  pcnt_counter_clear(PULSE_COUNT_UNIT);  // Clear the counter
  pcnt_set_pin(PULSE_COUNT_UNIT, PCNT_CHANNEL_0, PCNT_PIN_NOT_USED, PCNT_PIN_NOT_USED);
}

void Inputs::get_counter_channel(uint8_t input_channel)
{
   
    if (input_channel==6)             // Configure Input 6 of Kontrolog MAX as PCNT Counter
        {
        PULSE_COUNT_UNIT = PCNT_UNIT_0;
        GPIO_PIN_COUNTER = IN6_PIN;
        }
    else if(input_channel==7)        // Configure Input 6 of Kontrolog MAX as PCNT Counter
        {
        PULSE_COUNT_UNIT = PCNT_UNIT_1;
        GPIO_PIN_COUNTER = IN7_PIN;
        }

    else                    // Configure Input 8 of Kontrolog MAX as PCNT Counter
       {
        PULSE_COUNT_UNIT = PCNT_UNIT_2;
        GPIO_PIN_COUNTER = IN8_PIN;
        }

}


int16_t Inputs::get_ds18b20_temp(uint8_t input_channel) 
{
  
    if(input_channel==6)
        {
        sensor6_ds18b20.requestTemperatures();
        float temperatureC = sensor6_ds18b20.getTempCByIndex(0);
        return (int16_t)(temperatureC*10.0);
        }

    if(input_channel==7)
        {
        sensor7_ds18b20.requestTemperatures();
        float temperatureC = sensor7_ds18b20.getTempCByIndex(0);
        return (int16_t)(temperatureC*10.0);
        }
    
    else 
        return 0;

}
