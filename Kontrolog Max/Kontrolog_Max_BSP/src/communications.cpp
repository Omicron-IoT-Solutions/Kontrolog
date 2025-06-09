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

#include "communications.h"


void comms::Detect_Comm_Module(void)                      // This funtion Detects if the comm. module programated is present or not
    {

    if (Ko.CONFIG.DT.com_module_prog == mod_lora)       // If LoRa Module is Programmed
        {
         
        if (Lo.Active_LoRaMod()) {                      // Found Module LoRa
            Ko.CONFIG.DT.com_module_det = mod_lora;
            Lo.Set_LoRaMod_OTAA();
            Lo.GetLoRaDeviceID();
        } else {
            Ko.CONFIG.DT.com_module_det = mod_none;
        }
        Lo.Set_Sleep_LoRaMod();
        } 
    else if (Ko.CONFIG.DT.com_module_prog == mod_sigfox)  // If Sigfox Module is Programmed
        {
        if (Si.Active_Modulo_Sigfox()) {
            Ko.CONFIG.DT.com_module_det = mod_sigfox;
            Si.initSigfox();
            Si.GetDeviceID();
        } else {
            Ko.CONFIG.DT.com_module_det = mod_none;
        }
        Si.Deep_Sleep_Sigfox();
        } 
    else if (Ko.CONFIG.DT.com_module_prog == mod_wifi)    // If WiFi Module is programmed
        {
            Ko.CONFIG.DT.com_module_det = mod_wifi;

         } 
    else                 
        {
        Ko.CONFIG.DT.com_module_det = mod_none;
        }
    
    if (Ko.CONFIG.DT.com_module_det == mod_none)
        {
           Serial.println("communication module is not detected");
        }
        
}

// Turn off the comunication Module
void comms::Turn_Off_Com_Module(void)
{
    if(Ko.CONFIG.DT.com_module_det==mod_lora)
        Lo.Set_Sleep_LoRaMod();
    else if(Ko.CONFIG.DT.com_module_det==mod_sigfox)
        Si.Deep_Sleep_Sigfox(); 
    else if(Ko.CONFIG.DT.com_module_det==mod_wifi)
        {
        delay(1);
        //Wi.Deep_Sleep_Wifi();           // Uncomment if you want to close WiFi connection
        }

    else
        {
        Si.Deep_Sleep_Sigfox(); 
        Lo.Set_Sleep_LoRaMod();
        Wi.Deep_Sleep_Wifi();
        }
}

// Activation of communication module
char comms::Activate_Com_Module() {
    // Check if no module is programmed
    if (Ko.CONFIG.DT.com_module_prog == mod_none) {
        Detect_Comm_Module(); // Try to detect the current communication module
    }

    // Check which module is selected and activate it
    if (Ko.CONFIG.DT.com_module_det == mod_lora) {
        return Lo.Active_LoRaMod();
    }
    else if (Ko.CONFIG.DT.com_module_det == mod_sigfox) {
        return Si.Active_Modulo_Sigfox();
    } 
    else if (Ko.CONFIG.DT.com_module_det == mod_wifi) {
        return Wi.Init_WiFi_Connection();
    }
    else {
        return 0;
    }
}

// Trasmit data according to selected comm. module
void comms::Transmit_Data(unsigned char *buffer_datos, char ack) {
    
    if (Ko.CONFIG.DT.com_module_det == mod_lora) {          // LoRa Module?
        Lo.sendCMSGHEX(buffer_datos, 24, ack);
    }
    else if (Ko.CONFIG.DT.com_module_det == mod_sigfox) {   // Sigfox Module?
        Si.sendPayload(buffer_datos, 12, ack);

    } 
    else if (Ko.CONFIG.DT.com_module_det == mod_wifi) {      // WiFi Module?
        Wi.SendPayloadWiFi(buffer_datos, 24, ack);           // Keep consistent with LoRa
    } 

}

//-------------------------------------------------------------------------------------------------------
// Handle all communication tasks
//-------------------------------------------------------------------------------------------------------
void comms::Communication_Task(void)
{
    if (Ko.TIMERS.timer_reset_com_module >= 720) { // Device hasn't received any Downlink in more than 12 hours?
        esp_restart();                             // Reset device
    }

    if ((Ko.PUB.com_task == standby)&&(Ko.TIMERS.timer_wifi_AP==0)) {
        Ko.LED_RGB.G=0;
    } else {
        if (Ko.TIMERS.seconds & 0x01) {
            Ko.LED_RGB.G=1;
        } else {
            Ko.LED_RGB.G=0;
        }
    }
      
    
    Comms.Serial_Rx();                                 // Every Second Check if the Are there Any Data from communication module (Serial Port1)

    if(Ko.TIMERS.timer_wifi_AP>0)
        {
        Wi.Portal_Manager();
        if(--Ko.TIMERS.timer_wifi_AP==0) 
          {
          Wi.end_AP_Mode();
          }  
        }
    
     switch (Ko.PUB.com_task) {
            
            case module_init:                                        // Init Comm Module Task
                {
                Serial.println("Initializing communication module");
                Detect_Comm_Module();                                  // Detect the Communication Module Programmed
                Ko.PUB.counter_for_downlink=Ko.CONFIG.DT.downlink_msg-1;
               
                if (Ko.CONFIG.DT.com_module_det==mod_wifi)            // If the programme module is WiFi
                    {
                    Serial.println("Wifi Enter in AP Mode for 180 Seconds");
                    Wi.enter_to_AP_Mode();                            // Enter into AP Mode 
                    Ko.TIMERS.timer_wifi_AP=180;                      // Init Timer en AP Mode in 180 Seconds : User can modify this time
                    Ko.PUB.com_task=standby;                          // Go to WiFi AP mode Task
                    Ko.TIMERS.timer_publication=60;
                    }
                else
                    {

                    Turn_Off_Com_Module();
                    Ko.PUB.com_task=standby;
                    Ko.TIMERS.timer_publication=60;
                    }
                }
            break;
            
            case standby: {                                     // Module waiting until TPU is fulfilled
                // Time control to report parameters
                if ((Ko.TIMERS.timer_publication == 0) || (Ko.PUB.send_data == 1)) {
                    Ko.PUB.send_data = 0;
                    Ko.PUB.com_task = storing;
                    Ko.TIMERS.timer_publication = Ko.CONFIG.DT.TPU;
                    Ko.TIMERS.timer_publication *= 60;
                } else {
                    if (Ko.PUB.data_ACK_Rx) {               // Received some data out of time, this is asynchronous
                        if (Ko.CONFIG.DT.com_module_det == mod_lora)
                            Lo.Read_Rx_data_LoRa();
                        else if (Ko.CONFIG.DT.com_module_det == mod_sigfox)
                            Process_Rx_Data(BufferRx);
                        else if (Ko.CONFIG.DT.com_module_det == mod_wifi)
                            Process_Rx_Data(BufferRx);
                        Ko.PUB.data_ACK_Rx = 0;
                    }
                }
            }
            break;
            
            case storing:                             // Prepare data to send
                {
                Serial.println("Prepare data to send");
                Prepare_Data_To_Send();               // Prepare Uplink Message
                if(Ko.RTC.RTC_is_synchronized)        // If the RTC is synchronized?
                    { 
                buf_str[12] = (Ko.RTC.time_stamp >> 24) & 0xFF;     // Save the time Stamp
                buf_str[13] = (Ko.RTC.time_stamp >> 16) & 0xFF;
                buf_str[14] = (Ko.RTC.time_stamp >> 8) & 0xFF;
                buf_str[15] = Ko.RTC.time_stamp & 0xFF;
                }   
                else 
                    {
                    Ko.BACKUP_SENT.index=0;                // Se borran datos anteriores, no tiene sentido usarlos sin Estampa de tiempo
                    buf_str[12]=0;
                    buf_str[13]=0;
                    buf_str[14]=0;
                    buf_str[15]=0;
                    }

                buf_str[17]=Ko.BACKUP_SENT.index;
                Ko.PUB.wait_for_downlink=0;
                if(++Ko.PUB.counter_for_downlink >=Ko.CONFIG.DT.downlink_msg)
                    {
                    Ko.PUB.counter_for_downlink=0;
                    Ko.PUB.wait_for_downlink=1;
                    }
                buf_str[16]=Ko.PUB.wait_for_downlink;                   
                
                Store_data(buf_str);
                Ko.PUB.counter_of_attempts_to_send=0;                   // Clear counter max attempts to send
                Ko.PUB.com_task=joining;
                }
            break;
            
            case joining:                                               // Joining to the network task
                { 
                Ko.PUB.counter_of_attempts_to_send=0;
                if (Ko.CONFIG.DT.com_module_det==mod_none)              // If the module in not found
                    {
                    Ko.PUB.com_task=module_init;                        // Go to init task
                    }
                
                else if (Ko.CONFIG.DT.com_module_det==mod_wifi)         // Wifi Module
                    {
                    Ko.PUB.com_task=sending;
                    }
                
                else if (Ko.CONFIG.DT.com_module_det==mod_lora)         // Lora Module
                    {
                    if(Lo.Active_LoRaMod()==1)
                        {
                        Serial.println("Star joinig to LoRaWAN Network");
                        if(Ko.LORA_MOD.join_status==1)
                            Ko.PUB.com_task=sending;
                        else
                            {
                            Lo.joinNetwork(1);                          // Send the first join command
                            Ko.LORA_MOD.tries2join=0;                   // Init the Join counters
                            Ko.PUB.join_max_timer=0;                        // Init max time to join          
                            Ko.PUB.com_task=waiting_to_join;            // Go to waiting for join task
                            }
                        }    
                    else
                        {
                        Lo.Set_Sleep_LoRaMod();
                        Ko.PUB.com_task=standby;
                        }
                    }

                else if (Ko.CONFIG.DT.com_module_det==mod_sigfox)       // Sigfox Module
                    {
                    if(Si.Active_Modulo_Sigfox()==1)             
                        Ko.PUB.com_task=sending;
                    else
                        {
                        Si.Deep_Sleep_Sigfox();
                        Ko.PUB.com_task=standby;
                        }
                    }
                }
            break;
            
            case waiting_to_join:                           // Wainting for Join if LoRaWAN module is selected
                {
                
                int res=Lo.wait_for_join();                 // Check if Joined
                
                if (res==1)                                 //Join  correct?
                    {
                    Ko.LORA_MOD.join_status=1; 
                    Ko.PUB.com_task=sending;               // Go to Sending
                    }
                else if (res==-1)                           // Join Fail?
                    {
                    if(++Ko.LORA_MOD.tries2join<=10)      // tries 10 times to join the network
                        {
                        Lo.joinNetwork(1);
                        Ko.PUB.join_max_timer=0;
                        }
                    else
                        {
                        Lo.Set_LoRaMod_OTAA();             // if fails reset LoRa Module
                        Ko.PUB.com_task=standby;
                        }
                    }
                
                else                                     // Wait for answer
                    {
                    if(++Ko.PUB.join_max_timer==30)          // if not recieve answer of the join result in 30 seconds
                        {
                        Lo.Set_Sleep_LoRaMod();          // Abort to send the message
                        Ko.PUB.com_task=standby;
                        }
                    }
                }
            break;
                        
            case sending:                                 // Sending data task
                {
                Serial.println("Sending Data to the Selected Network");    
                if(Ko.BACKUP_SENT.index>0)
                    Ko.BACKUP_SENT.index--;
                
                Transmit_Data(Ko.BACKUP_SENT.data[Ko.BACKUP_SENT.index],Ko.PUB.wait_for_downlink);
                if(Ko.CONFIG.DT.com_module_det==mod_lora)
                    Ko.PUB.Rx_max_timer=30;
                else
                    Ko.PUB.Rx_max_timer=60;
                
                Ko.PUB.data_ACK_Rx=0;                   // Clear ACK Rx Flag
                Ko.PUB.counter_of_attempts_to_send=0;   // Init max attempts to send counter
                Ko.PUB.com_task=receiving;              // Go to Recieving task
                }
            break;
                
            case receiving:                             // Receiving task 
                {
                if (Ko.CONFIG.DT.com_module_det==mod_lora)
                    {
                    int res=Lo.wait_Rx_LoRa();
                    
                    if (res==1)                                                     // Correct Send
                        {
                        Ko.PUB.counter_of_attempts_to_send=0;                       // Reset counter max attempts to send
                        Ko.PUB.Rx_max_timer=0;
                        if(Ko.PUB.wait_for_downlink)
                            {
                            RTC.READ_TIME();                                        // Save the current Time_Stamp to get the correct time on next reception
                            Ko.RTC.previous_time_stamp=Ko.RTC.time_stamp;                              
                            }
                        }
                    else if(res==2)                                                 // Correct send and received downlink message.
                        {
                        Ko.PUB.counter_of_attempts_to_send=0;                       // Reset counter max attempts to send
                        Ko.PUB.Rx_max_timer=0;
                        Lo.Read_Rx_data_LoRa();                                     // Read the downlik data
                        if(Ko.PUB.wait_for_downlink)
                            {
                            RTC.READ_TIME();                                        // Save the current Time_Stamp to get the correct time on next reception
                            Ko.RTC.previous_time_stamp=Ko.RTC.time_stamp;        
                            }
                        }
                    else if(res==-1)                                                // if the module answer: Not Joined 
                        {
                        Ko.LORA_MOD.join_status=0;                                  // Abort transmission
                        Ko.PUB.com_task=standby;
                        }
                    else if(res==-2)                                                // AT_ERROR,  or other ==> Try againt to send the same data
                        {
                        Ko.PUB.Rx_max_timer=0; 
                        Ko.BACKUP_SENT.index++;
                        }

                    }
                
                else if (Ko.CONFIG.DT.com_module_det==mod_wifi)
                    {
                    if(Ko.PUB.wait_for_downlink)                   // Waiting for Downlink?
                        {
                        int res=Wi.wait_rx_wifi();                  

                        if(res==1)
                            {
							Ko.PUB.counter_of_attempts_to_send=0;                       // Reset counter max attempts to send
                            Ko.PUB.Rx_max_timer=0;
                            Process_Rx_Data(BufferRx);            // User can Procces Rx Data 
                            }
                        else if (res==-1)                         // Communication Error
                            { 
                            Ko.PUB.Rx_max_timer=0; 
                            Ko.BACKUP_SENT.index++;
                            }
                        }
                    else{
                        Ko.PUB.Rx_max_timer=0;                                // End of Rx
                        }
                    }                
                else if(Ko.CONFIG.DT.com_module_det==mod_sigfox)        
                    {
                    if(Ko.PUB.wait_for_downlink)                            // Wait for Downlink
                        {
                         if (Ko.PUB.data_ACK_Rx)
                            {
                            Si.rx_data_Sigfox();                            // rx downlink data
                            Ko.PUB.Rx_max_timer=0;               
                            }
                        }
                    else{
                        Ko.PUB.Rx_max_timer=0;                              // End of Rx
                        }
                    }
                
                if(--Ko.PUB.Rx_max_timer<=0)                                 // Wait until the end of rx max timer
                    {
                     if(Ko.BACKUP_SENT.index>0)                             // Is There any data pending to be send?
                        {
                        if(++Ko.PUB.counter_of_attempts_to_send<=5)         // If there is error, try to send 5 times
                            {
                            Ko.PUB.counter_for_delay=10;
                            Ko.PUB.com_task=waiting_for_next_sending;
                            }
                        else 
                            {
                            Turn_Off_Com_Module();
                            Ko.PUB.com_task=standby;
                            if(Ko.CONFIG.DT.com_module_det==mod_lora)
                                    Lo.Set_LoRaMod_OTAA();
                            if(Ko.RTC.RTC_is_synchronized==0)         // Clear all data pending to send if RTC is not Syncronized
                                Ko.BACKUP_SENT.index=0;
                            }
                        }
                    else
                        {
                        Turn_Off_Com_Module();
                        Ko.PUB.com_task=standby;
                        }
                    }
                }           
            break;
            
            case rx_lora:
            { 
                Lo.Read_Rx_data_LoRa();
                Ko.PUB.com_task=standby;
            }
            break;
            
            case waiting_for_next_sending:
            {
                if(--Ko.PUB.counter_for_delay==0)
                {
                   Ko.PUB.com_task=sending;
                }            
            }
            break;
            
           }
}


//-------------------------------------------------------------------------------------------------------
void comms::Prepare_Data_To_Send(void)
/*
 Struct of Uplink Message for KONTROLOG-MAX 1.0 
   
          yte 0      |  byte 1 | byte 2  | byte 3 | byte 4 | byte 5 |byte 6 | byte 7 | byte 8  | byte 9 | byte 10 |             byte 11           | byte 12 | byte 13 | byte 14 | byte 15 | byte 16  | byte 17    | byte 18 | Byte 19 | byte 20 |Byte 21 | Byte 22 | Byte 23 |
       ALM | IN1 MSB | IN1 LSB |      IN2    IN 3          |      IN4      IN5       |  VDC    |  VAC    | IAC MSB| IAC LSB O5 O4 O5 O2 O1 O1 BUZ |        Epoch Time                     | ACK Lora | Msg Counter|     IN6           |        IN7       |       IN 8
*/
{
    unsigned int data;
   

        // Alarms Status 4 Bits
        buf_str[0]|=Ko.PUB.alarm_type<<4;
        Ko.PUB.alarm_type=0;
    
        // Sensor 1 : 12 bits
        data= Ko.IN1.value&0x0FFF;
        buf_str[0] = buf_str[0]|(data>>8);
        buf_str[1] =(data&0x00FF);

        // Sensor 2 : 12 bits
        data = Ko.IN2.value&0x0FFF;
        buf_str[2] = (data>>4)&0x00FF;
        buf_str[3] = (data&0x000F)<<4;

        // Sensor 3 : 12 bits
        data = Ko.IN3.value&0x0FFF;;
        buf_str[3] = (buf_str[3])|(data>>8);
        buf_str[4] = (data&0x00FF);

        // Sensor 4 : 12 bits
        data = Ko.IN4.value&0x0FFF;;
        buf_str[5] = (data>>4)&0x00FF;
        buf_str[6] = (data&0x000F)<<4;
        
        // Sensor 5 : 12 bits
        data = Ko.IN5.value&0x0FFF;;
        buf_str[6] = (buf_str[6])|(data>>8);
        buf_str[7] = (data&0x00FF);
        
        // DC Voltage : 8 bits
        buf_str[8] = (unsigned char) Ko.VDC.value;

        // VAC : 8 bits
        data = Ko.VAC.value;
        buf_str[9] =  (uint8_t) (Ko.VAC.value/10);

        // IAC :  10 bits
        data =  Ko.IAC.value & 0x03FF;                       // 10 bits  0 a 102.3 Ampers
        buf_str[10]=  (data>>2)&0x00FF;;                                    
        buf_str[11]=  (data&0x0003)<<6;
   

        //Outputs
        uint8_t BITS=0;
        BITS|=(Ko.OUT4.value<<5);       // Bit 5  OUT4
        BITS|=(Ko.OUT4.value<<4);       // Bit 4  OUT4
        BITS|=(Ko.OUT3.value<<3);       // Bit 3  OUT3
        BITS|=(Ko.OUT2.value<<2);       // Bit 2  OUT2
        BITS|=(Ko.OUT1.value<<1);       // Bit 1  OUT1
        buf_str[11]|=BITS;
        
        // Sensor 6
        data = Ko.IN6.value;
        buf_str[18] = (data>>8)&0x00FF;
        buf_str[19] = (data&0x00FF);
        if(Ko.IN6.type==counter_reset)
            In.Counter_clear(6,1);
        else if(Ko.IN6.type==runtime_reset)
            Ko.IN6.value=0;

        // Sensor 7
        data = Ko.IN7.value;
        buf_str[20] = (data>>8)&0x00FF;
        buf_str[21] = (data&0x00FF);
        if(Ko.IN7.type==counter_reset)
            In.Counter_clear(7,1);
        else if  (Ko.IN7.type==runtime_reset)
            Ko.IN7.value=0;
        
        // Sensor 8
        data = Ko.IN8.value&0xFFFE;         // Clear the last bit
        buf_str[22] = (data>>8)&0x00FF;
        buf_str[23] = (data&0x00FF);
        if(Ko.IN8.type==counter_reset)
            In.Counter_clear(8,1);
        else if(Ko.IN8.type==runtime_reset)
            Ko.IN8.value=0;


}


void comms::Store_data(unsigned char * data)
{
  int i,j,k;
    if(Ko.BACKUP_SENT.index>=N_Backup_Data)
        k=N_Backup_Data-1;
    else
        k=Ko.BACKUP_SENT.index;
    
    for(i=k;i>0;i--)                    // Moves N-1 Data to a next position by deleting the last data.
        {
        for(j=0;j<24;j++)
            {
            Ko.BACKUP_SENT.data[i][j]= Ko.BACKUP_SENT.data[i-1][j];
            }
        }
    
    for(i=0;i<24;i++)
        {
        Ko.BACKUP_SENT.data[0][i]= data[i];         // Stores the new data in position 0
        }
    
    if(Ko.BACKUP_SENT.index<N_Backup_Data)
        Ko.BACKUP_SENT.index++;
}

//-------------------------------------------------------------------------------------------------------
int comms::Process_Rx_Data(char *Buffer_Datos_Rx)
/* Struct of Downlink Data for KONTROLOG 10.0 and KONTROLOG-MINI 1.0
 // Bytes in 00,  are reserve for KONTROLOG 10.0 (This device has moore inputs and outputs)
   
    byte 0  |  byte 1 | byte 2   |  byte 3 | byte 4 | byte 5 | byte 6 | byte 7 
     Group  | Subgrup | Parameter|  Data 3 | Data 2 | Data 1 | Data 0 | New_Data

where:
    Byte 0: Group of Parameters,  example  Group 1 : Parameters for sensor 1
    Byte 1: SubGroup of Parameters,  User can use for different task
    Byte 2: Parameter,  example  Group = 1 (Sensor 1),  Parameter = 5 (offset) ==> Message for modify the Offset of the sensor 1
    Bytes 3-6: New Data or Value for the parameter to modify (User can use Float or Integer data)
    Byte 7: New Data:  The Platform indicates to KONTROLOG that has other parameter for downlink,  so the device has to prepare the next reception

Example of DownliNk Messages
    RX=01 00 05 0000000A 00     ==>  Command for modify the offset value of sensor 1, en 10
*/

{
int i=0,j=0;
char Aux[20]={0};
char Aux2[10]={0};
unsigned char new_ack=0, mod=0;
unsigned char Buff[12] = {0};
char *pos_rx;
                
    Ko.PUB.data_ACK_Rx=0;                       // Clear ACK Rx Flag bit
    
    pos_rx=strstr(Buffer_Datos_Rx, "RX=");     // The command has to start by RX= command

    if (pos_rx!=0)
        {
        pos_rx+=3;
        while (*(pos_rx + i) != '\r' && j < 16)
            {
            
            if (*(pos_rx+i)!=0x20)
                Aux[j++]=*(pos_rx+i);
            i++;
            }
        Aux[j]=0;
    
        // Extracting and converting received data fields
        Aux2[0]=Aux[0];
        Aux2[1]=Aux[1];
        Aux2[2]=0;
        Ko.GET_DATA.group=strtol(Aux2,0,16);            // Group 
        
        Aux2[0]=Aux[2];
        Aux2[1]=Aux[3];
        Aux2[2]=0;
        Ko.GET_DATA.subgroup=strtol(Aux2,0,16);         // Subgroup
        
        Aux2[0]=Aux[4];
        Aux2[1]=Aux[5];
        Aux2[2]=0;
        Ko.GET_DATA.parameter=strtol(Aux2,0,16);       // Parameter
        
        Aux2[0]=Aux[6];
        Aux2[1]=Aux[7];
        Aux2[2]=Aux[8];
        Aux2[3]=Aux[9];
        Aux2[4]=Aux[10];
        Aux2[5]=Aux[11];
        Aux2[6]=Aux[12];
        Aux2[7]=Aux[13];
        Aux2[8]=0;
        Ko.GET_DATA.value_long=strtoul(Aux2,0,16);      // Get the value in long 
        Ko.GET_DATA.value_float=(float) Ko.GET_DATA.value_long;  // Also store in float
        
        Aux2[0]=Aux[14];                    // New Downlink Data in the next command?
        Aux2[1]=Aux[15];
        Aux2[2]=0;
        new_ack=strtol(Aux2,0,16);
        if (new_ack>1)
            new_ack=0;
        
        
        mod=User_downlink_data();           // Procces the Downlink data
        
        if (mod>0)
            {
            if(mod==1)
                {
                // Prepare the answer command
                Buff[0]= 0xF0;
                Buff[1]= Ko.GET_DATA.group;
                Buff[2]= Ko.GET_DATA.subgroup;
                Buff[3]= Ko.GET_DATA.parameter;
                Buff[4]= (Ko.GET_DATA.value_long>>24);
                Buff[5]= (Ko.GET_DATA.value_long>>16);
                Buff[6]= (Ko.GET_DATA.value_long>>8);
                Buff[7]= (Ko.GET_DATA.value_long);    
                }
            else
                {
                Buff[0]= 0xFE;              // Error in data received
                }
            
            if (new_ack)
                {
                Ko.PUB.Rx_max_timer=0;
                Ko.TIMERS.wait_for_sigfox_downlink=60;          // Wait for a new downlink
                }
            
            if (Ko.CONFIG.DT.com_module_prog == mod_wifi)          // Send the confirmation of received data
                Wi.SendPayloadWiFi(Buff,8,new_ack);
            else if(Ko.CONFIG.DT.com_module_prog == mod_sigfox)
                Si.sendPayload(Buff,8,new_ack);
            else if(Ko.CONFIG.DT.com_module_prog == mod_lora)
                Lo.sendCMSGHEX(Buff,8,new_ack);

            }
        }
        
    if (new_ack==1)
        return 1;
    else
        return 0;
                    
}

uint8_t comms::User_downlink_data(void)        
{ 
    uint8_t mod = 0, res = 0;
    uint8_t Old_sensor_type;

    switch (Ko.GET_DATA.group)
        {
        case 1: // Sensor 1 parameters
            {

            }
        break;
        
        case 2: // Sensor 2 parameters
            {

            }
        break;

        case 3: // Sensor 3 parameters
            {

            }
        break;

        case 4: // Sensor 4 parameters
            {

            }
        break;

        case 5: // Sensor 4 parameters
            {

            }
        break;

        case 60: // Digital Sensor 6
            {

            }
        break;

        case 70: // Digital Sensor 7
            {

            }
        break;

        case 80: // Digital Sensor 8
                {

                }
        break;
        
        
        case 6: // Battery Voltage
        {

        }
        break;

        case 7: // AC Voltage
        {

        }
        break;

        case 8: // AC Current
        {

        }
        break;

        case 11: // Output 1
        {

        }
        break;

        case 12: // Output 2
        {

        }
        break;
        
        case 13: // Relay Output 3
            {

            }
        break;
        
        case 14: // Relay  Output 4
            {

            }
        break;

        case 15: // Relay  Output 5
            {

            }
        break;


        case 20: // General Parameters
        {
            if ((Ko.GET_DATA.parameter == 1) && ((Ko.GET_DATA.value_long >= 1) || (Ko.GET_DATA.value_long <= 1440))) { // Publication Time
                Ko.CONFIG.DT.TPU = Ko.GET_DATA.value_long;
                EEPROM_MEM.Write_Int_EEPROM(DIR_TPU, Ko.GET_DATA.value_long);
                Ko.TIMERS.timer_publication = 60;
                mod = 1;
            }

            else if ((Ko.GET_DATA.parameter == 4) && (Ko.GET_DATA.value_long == 1)) { // Reset
                esp_restart();
            }

            else if ((Ko.GET_DATA.parameter == 5) && (Ko.GET_DATA.value_long == 1)) { // Factory Reset
                EEPROM_MEM.Write_Int_EEPROM(EEPROM_EEINI, 0);
                esp_restart();
            }


            else if ((Ko.GET_DATA.parameter == 8) && (Ko.GET_DATA.value_long >= 1) && (Ko.GET_DATA.value_long <= 140)) { //Number of Mesages betewen Downlink Messages
                Ko.CONFIG.DT.downlink_msg = Ko.GET_DATA.value_long;
                Ko.PUB.counter_for_downlink = Ko.CONFIG.DT.downlink_msg - 1;
                EEPROM_MEM.Write_Int_EEPROM(DIR_DOWNLINK, Ko.GET_DATA.value_long);
                mod = 1;
            }

            else if ((Ko.GET_DATA.parameter == 9) && ((Ko.GET_DATA.value_long == 1) || (Ko.GET_DATA.value_long == 2) || (Ko.GET_DATA.value_long == 4))) { // RF Zone
                Ko.CONFIG.DT.RF_zone = Ko.GET_DATA.value_long;
                EEPROM_MEM.Write_Int_EEPROM(DIR_RF_ZONE, Ko.GET_DATA.value_long);
                Ko.PUB.com_task = module_init;
                mod = 1;
            }

            else if (Ko.GET_DATA.parameter == 11) { // Password
                Ko.CONFIG.DT.password = Ko.GET_DATA.value_long;
                Ko.TIMERS.timer_password = 600;
            }

            else {
                mod = 0;
            }
        }
        break;
            

        case 22: // RTC
        {
            if (Ko.GET_DATA.parameter == 1) {               // Get the new epoch time
                if (Ko.CONFIG.DT.com_module_det == mod_lora) { 
                    RTC.READ_TIME(); // Read Actual Time Stamp
                    unsigned long time_adj = Ko.RTC.time_stamp - Ko.RTC.previous_time_stamp;
                    unsigned int tpu = Ko.CONFIG.DT.TPU * 60;
                    if ((time_adj >= 0) && (time_adj <= tpu + 40))
                        RTC.SET_TIME(Ko.GET_DATA.value_long + time_adj);
                } else if (Ko.CONFIG.DT.com_module_det == mod_sigfox) {
                    RTC.READ_TIME();
                    unsigned long time_adj = Ko.RTC.time_stamp - Ko.RTC.previous_time_stamp;
                    RTC.SET_TIME(Ko.GET_DATA.value_long + time_adj);
                } else {
                    RTC.SET_TIME(Ko.GET_DATA.value_long);
                }
                mod = 0;
                RTC.READ_TIME();
            }

            else if (Ko.GET_DATA.parameter == 2) { // Time Zone
                mod = 0;
                if ((Ko.GET_DATA.value_long >= -14) && (Ko.GET_DATA.value_long <= 14)) {
                    EEPROM_MEM.Write_Int_EEPROM(RTC_DIR + 2, Ko.GET_DATA.value_long);
                    RTC.READ_TIME();
                    Ko.RTC.time_zone = Ko.GET_DATA.value_long;
                    mod = 1;
                    RTC.SET_TIME(Ko.RTC.time_stamp);
                    RTC.READ_TIME();
                }
            }

            else {
                if (Ko.GET_DATA.parameter == 3) { // Year
                    if (Ko.GET_DATA.value_float > 2000) {
                        Ko.GET_DATA.value_long -= 2000;
                        Ko.GET_DATA.value_float -= 2000;
                    }
                }

                Ko.RTC.Array[Ko.GET_DATA.parameter] = Ko.GET_DATA.value_long;
            }
        }
        break;

            

    }
        
        return mod;
}


//*******************************************************************************************************************************
// Rx and Tx Funtions
//*******************************************************************************************************************************

/*-------------------------------------------------------------------------
	sendMessage
	- Input: outData is a pointer to the sending message.
	         len is the length of the sending message.
	- Output: recvMsg is received message
-------------------------------------------------------------------------*/
int comms::sendMessage(char *outData)
{
    int receivedResult;
	if (outData == NULL){      
		return -1;
	}
    // send message
    Prepare_Command_to_Send(outData);           //Prepare and send data
    // read ack or return payload
	receivedResult = get_answer_Msg(); 
	return receivedResult;
}

/*
recvMsg getRecvMsg()
	- Output: return receive message from LSM110A
*/
int comms::get_answer_Msg(void)
{
	int receivedResult;
    int wait_for_rx=20;
    Count_Rx=0;
    while (wait_for_rx-->0)
        {
        delay(10);
        Serial_Rx();
        }
    
    if ((strstr(BufferRx, "OK")!=0))
            {
			return 1;
            }		
        else 
            {
			return 0;
            }

}

void comms::Prepare_Command_to_Send(char *comando) {
    BufferRx_Init();  // Initialize the receive buffer and flags

    char BufferTx[200];  // Buffer for transmitting command
    unsigned char i = 0;

    // Copy the command string into the transmission buffer
    while (*(comando + i) != 0) {
        BufferTx[i] = *(comando + i);
        i++;
    }

    // Append '\r' and '\n' to the command
    BufferTx[i++] = '\r';
    BufferTx[i++] = '\n';
    BufferTx[i] = 0;  // Null-terminate the string (optional)

    // Transmit the constructed command
    Serial_Tx(BufferTx);  // This presumably starts the transmission process
}

void comms::BufferRx_Init(void)
{
    int i;

    // Initialize the receive buffer with zeros
    for (i = 0; i < sizeof(BufferRx); i++) {
        BufferRx[i] = 0;
    }
    
    Count_Rx = 0;    // Reset receive buffer index
    Dato_RxFlag=0;  // Reset Rx Flag
}

// Change .DEC data .HEX to prepare the data to send  by Sigfox or LoRaWAN in HEX 
#define TO_HEX(i) (i <= 9 ? '0' + i : 'A' - 10 + i)
void comms::ASCII2Hex(unsigned char* input, int length, char* buf_str)
{
    int i,j=0;

    for (i=0;i<length;i++)
    {
        *(buf_str+j++) = TO_HEX(((*(input+i) & 0xF0) >> 4));
        *(buf_str+j++) = TO_HEX((*(input+i) & 0x0F));  
    }
    *(buf_str+j)=0;
}


// Transmit TX Buffer

void comms::Serial_Tx (char *buffer)                
{

    Cont_Tx=0;                      // Init the counter
    while (*(buffer+Cont_Tx)!=0) 
        { 
        Serial1.write(*(buffer+Cont_Tx));
        Serial1.flush();
        Cont_Tx++;
        }
    Ti.DELAY_TMR(20);              // Wait 20 ms for wait module confirmation
}

//----------------------------------------------------------------------------
//	SERIAL RX FROM COMM. MODULE
//----------------------------------------------------------------------------

void comms::Serial_Rx() 
{
    while (Serial1.available() > 0) 
        {
        DataRx = Serial1.read();            // Read the incoming byte
        BufferRx[Count_Rx] = DataRx;         // Store in the receive buffer
        Count_Rx++;
        //Serial.print(DATORx);             // Uncomment if you want to Debug
        if (Count_Rx >= sizeof(BufferRx)){
            Count_Rx = 0;                    // Reset index if buffer overflow
            }
        
        if(Serial1.available()==0)
            {
            Dato_RxFlag=1;
            if(Ko.CONFIG.DT.com_module_det==mod_sigfox)     // Check if there is a Sigfox Rx Data
                {
                if (strstr(BufferRx, "RX=")!=0)             // Answer of LSM110A
                    {
                    Ko.PUB.data_ACK_Rx=1;
                    Ko.TIMERS.timer_reset_com_module=0;
                    }
                else;
                }
            else if(Ko.CONFIG.DT.com_module_det==mod_lora)      // Check if there is a LoRa Rx Data
                {
                if (strstr(BufferRx, "EVT:RECV_UNCONFIRMED")!=0)        // Answer of LM110A            
                    {
                    Ko.PUB.data_ACK_Rx=1;
                    Ko.TIMERS.timer_reset_com_module=0;
                    }
                else;
                }
            }
        }
}

//-----------------------------------------------------------------------------------
// LED RGB  OPERATION
//-----------------------------------------------------------------------------------

void comms::SET_LED_RGB(char color)
{
    switch (color)
    {
        case led_off:                           // Off
            Ko.LED_RGB.R=0;
            Ko.LED_RGB.G=0;
            Ko.LED_RGB.B=0;
        break;

        case led_white:                         // White       
            Ko.LED_RGB.R=1;
            Ko.LED_RGB.G=1;
            Ko.LED_RGB.B=1;
        break;
        
        case led_red:                          // Red 
            Ko.LED_RGB.R=1;
            Ko.LED_RGB.G=0;
            Ko.LED_RGB.B=0;
        break;
        
        case led_green:                        // Green    
            Ko.LED_RGB.R=0;
            Ko.LED_RGB.G=1;
            Ko.LED_RGB.B=0;
        break;
        
        case led_blue:                          // Blue
            Ko.LED_RGB.R=0;
            Ko.LED_RGB.G=0;
            Ko.LED_RGB.B=1;
        break;
        
        case led_violet:                         // Violet
            Ko.LED_RGB.R=1;
            Ko.LED_RGB.G=0;
            Ko.LED_RGB.B=1;
        break;
        
        case led_yellow:                         // Yellow
            Ko.LED_RGB.R=1;
            Ko.LED_RGB.G=1;
            Ko.LED_RGB.B=0;
        break;
        
        case led_navy_blue:                     // Navy Blue
            Ko.LED_RGB.R=0;
            Ko.LED_RGB.G=1;
            Ko.LED_RGB.B=1;
        break;


        default:
        break;
  
    }

}

void comms::LED_SEND_MSG(void)
{
    uint8_t i, rep;
    SET_LED_RGB(led_off);
    Ti.DELAY_TMR(100);
    
    if(Ko.CONFIG.DT.com_module_det==mod_sigfox)
        {
        if(Ko.SIGFOX_MOD.zone==1)
            rep=3;
        else
            rep=Ko.SIGFOX_MOD.zone;
        }
    else if(Ko.CONFIG.DT.com_module_det==mod_lora)
        {
        if(Ko.LORA_MOD.band==AU915)
            rep=4;
        else if(Ko.LORA_MOD.band==US915)
            rep=2;
        else
            rep=3;
        }
    else
        rep=3;        
        
    
    for (i=0;i<rep;i++)
        {
        if(Ko.CONFIG.DT.com_module_det==mod_sigfox)
            SET_LED_RGB(led_yellow);
        else
            SET_LED_RGB(led_green);
        Ti.DELAY_TMR(300);
        SET_LED_RGB(led_off);                       
        Ti.DELAY_TMR(300);
        }
}

void comms::LED_ERR_MSG(void)
{
    uint8_t i;
    Ti.DELAY_TMR(100);
    for (i=0;i<3;i++)
        {
        SET_LED_RGB(led_red);
        Ti.DELAY_TMR(300);
        SET_LED_RGB(led_off);                      
        Ti.DELAY_TMR(300);
        }
}