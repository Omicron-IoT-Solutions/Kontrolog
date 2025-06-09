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

//---------------------------------------------------------------------------------------------------------------------
// ---- START WiFi CONNECTION
// Function: 
// The configuration web page is launched
// Return res:
// 0: Network configured, but connection could not be established
// 1: Connected to preconfigured WiFi network
// 2: Network not configured, no connection established
//---------------------------------------------------------------------------------------------------------------------
#include "wifi_esp.h"

ubidots_class Ubi;

WebServer server_esp(80);       // Invoque Services for Autoconnect portal

uint8_t wifi_esp_class::Init_WiFi_Connection(void)
{ 
int counter;
    
    if (Ko.WIFI_MOD.on_off==1)
      {
      delay(1);
      return 1;
      }

    if (get_WiFi_configuration())                    // Get stored SSID and Password In EEPROM
        {


        counter=0;
        while ((wifiMulti1.run() != WL_CONNECTED)&&(counter <2))         // Wait for correct connection
                {
                delay (490);
                Ko.LED_RGB.G=1; 
                Di.Panel_Indicators();       
                delay(10);
                Ko.LED_RGB.G=0; 
                Di.Panel_Indicators();
                counter++; 
                }
                
        if (wifiMulti1.run()== WL_CONNECTED)                    
              {    
              Last_IP= WiFi.localIP().toString();       
              Ko.WIFI_MOD.on_off=1;                                     // This flag indicates WiFi is connected to the network
              if(activate_debug)
                Serial.printf(" connected to %s\r\n", WiFi.SSID().c_str());

              // Get MAC in HEX format
              byte mac[6];
              WiFi.macAddress(mac);
              Ko.WIFI_MOD.MAC = String(mac[0], HEX)+ String(mac[1], HEX)+ String(mac[2], HEX)+ String(mac[3], HEX)+ String(mac[4], HEX)+ String(mac[5], HEX);
              return 1;
              }
        else
            return 0;
        }

    else
         return -1;
}

int wifi_esp_class::get_WiFi_configuration(void)
{ 
        get_stored_network (dir_config1,add_ssid1,dir_pass1);
        get_stored_network (dir_config2,add_ssid2,dir_pass2);
        get_stored_network (dir_config3,add_ssid3,dir_pass3);
        return 1;
}

// get stored network data into EEPROM
uint8_t wifi_esp_class::get_stored_network (int conf_Address,  int net_address, int pas_address)
{
String ssid_read;
String pass_read;
int    ssid_size;
int    pass_size;
int    net=0;
  
        int config1= EEPROM_MEM.Read_1Byte_EEPROM (conf_Address);
        if (config1==1)
           {
              ssid_read=EEPROM_MEM.Read_String_EEPROM(net_address);                             //Read ssid and password
              if (ssid_read.equals(""))
                  EEPROM_MEM.Write_1Byte_EEPROM(conf_Address,0);
              else
                {
                pass_read=EEPROM_MEM.Read_String_EEPROM(pas_address);                         //read the password
                ssid_size=ssid_read.length()+1;
                ssid_read.toCharArray(ssid,ssid_size);        
                pass_size=pass_read.length()+1;
                pass_read.toCharArray(pass,pass_size);
                wifiMulti1.addAP(ssid,pass);
                net++;
                }
             }
      return net;
}



//---------------------------------------------------------------------------------------------------------------------
// ----DEVICE NETWORK CONFIGURATION ----

// Function: 
// Create an WiFi AP and Launch a Captive Portal to connect to ESP32 To be able to configure on the device: SSID, PASSWORD
// 

// Result: res;   
// 1: Correct: Parameters set and successful connection to the network
// 0: Not correct: It is not possible to connect to the  network

//---------------------------------------------------------------------------------------------------------------------
void wifi_esp_class::Launch_Config_Portal(void)
{
char ssid_portal_a[30];
String ssid_portal = "Kontrolog_";
String Password="OmicronIoT12345678";
char  Wait_Counter;
char  Result;
int Aux_Counter;
byte mac[6];
WiFi.macAddress(mac);

    ssid_portal = ssid_portal + String(mac[0], HEX)+ String(mac[1], HEX)+ String(mac[2], HEX)+ String(mac[3], HEX)+ String(mac[4], HEX)+ String(mac[5], HEX);
    ssid_portal.toCharArray(ssid_portal_a,30); 
    
    WiFi.mode (WIFI_OFF);               // Turn off preliminar connections
    delay (500);                        
    
    WiFi.mode (WIFI_AP_STA);            // Enable Wifi AP and Soft Mode
    delay (500); 
      
    WiFi.softAP(ssid_portal_a,Password);         // Launch the AP           
    delay (1000);


    server_esp.on("/", []() {server_esp.send(200, "text/html",HTTP_HEAD1+ppal+HTTP_END);}); 

    server_esp.on("/scan", std::bind(&wifi_esp_class::handle_wifi_config_scan,this));         // Calls the wifi_conf function if the Connect or Scan button is pressed
    server_esp.on("/wifisave", std::bind(&wifi_esp_class::wifi_conf1,this));                  // Save WiFi network configuration parameters
    server_esp.on("/test",std::bind(&wifi_esp_class:: Config_Response,this));                 // Response to the configuration test

    server_esp.on("/info",std::bind(&wifi_esp_class::send_info,this));                        //  More info page

    server_esp.on("/cloud",std::bind(&wifi_esp_class:: Launch_cloud_settings,this));          // Response to cloud Settings
    server_esp.on("/cloudsave",std::bind(&wifi_esp_class:: Get_cloud_settings,this));         // Get Claud Settings

    server_esp.on("/sel_inputs", std::bind(&wifi_esp_class::Select_Inputs, this));            // Handles input selection
    server_esp.on("/input1", std::bind(&wifi_esp_class::Set_Input1, this));                   // Sets input 1
    server_esp.on("/input2", std::bind(&wifi_esp_class::Set_Input2, this));                   // Sets input 2
    server_esp.on("/input3", std::bind(&wifi_esp_class::Set_Input3, this));                   // Sets input 3
    server_esp.on("/input4", std::bind(&wifi_esp_class::Set_Input4, this));                   // Sets input 4
    server_esp.on("/input5", std::bind(&wifi_esp_class::Set_Input5, this));                   // Sets input 5
    server_esp.on("/input6", std::bind(&wifi_esp_class::Set_Input6, this));                   // Sets input 6
    server_esp.on("/input7", std::bind(&wifi_esp_class::Set_Input7, this));                   // Sets input 7
    server_esp.on("/input8", std::bind(&wifi_esp_class::Set_Input8, this));                   // Sets input 8
    server_esp.on("/send_input_value", std::bind(&wifi_esp_class::Handle_input_value, this)); // Handles received input value
    server_esp.on("/inputs_settings", std::bind(&wifi_esp_class::Get_inputs_parameters, this)); // Gets input configuration parameters

    server_esp.on("/sel_outputs", std::bind(&wifi_esp_class::Select_Outputs, this));           // Handles output selection
    server_esp.on("/output1", std::bind(&wifi_esp_class::Set_Output1, this));                 // Sets output 1
    server_esp.on("/output2", std::bind(&wifi_esp_class::Set_Output2, this));                 // Sets output 2
    server_esp.on("/output3", std::bind(&wifi_esp_class::Set_Output3, this));                 // Sets output 3
    server_esp.on("/output4", std::bind(&wifi_esp_class::Set_Output4, this));                 // Sets output 4
    server_esp.on("/output5", std::bind(&wifi_esp_class::Set_Output5, this));                 // Sets output 5
    server_esp.on("/send_output_value", std::bind(&wifi_esp_class::Handle_output_value, this)); // Handles received output value
    server_esp.on("/outputs_settings", std::bind(&wifi_esp_class::Get_outputs_parameters, this)); // Gets output configuration parameters

    server_esp.begin();                                                                       // Start the server


}
// Web Portal root Manager
void wifi_esp_class:: Portal_Manager(void)
{
  server_esp.handleClient();
}

// Get the best stored position for Network into EEPROM.
uint8_t  wifi_esp_class::get_stored_position(void)
{
char res;

        int counter_config=EEPROM_MEM.Read_1Byte_EEPROM (add_count_config);               // Get the configuration counter
        if ((counter_config<1)|(counter_config>3))                                        // If it is not in a valid range, position 1 is assigned.                       
                  {counter_config=1; EEPROM_MEM.Write_1Byte_EEPROM(add_count_config,2);}
        
// First check that the network does not exist
           if (EEPROM_MEM.Read_String_EEPROM(add_ssid1).equals(ssid))
              {res = 1;}
           else if (EEPROM_MEM.Read_String_EEPROM(add_ssid2).equals(ssid))
              {res = 2;}
           else if  (EEPROM_MEM.Read_String_EEPROM(add_ssid3).equals(ssid))
              {res = 3;}
           else {
// Otherwise, the new configured networks are recorded in order
           int count2=counter_config+1;
           if (count2>3)
               count2=1;
  
            EEPROM_MEM.Write_1Byte_EEPROM(add_count_config,count2);
            res = counter_config;
            }           

 return res;
}


void wifi_esp_class:: config_portal_end(void)
{
  server_esp.close();
  WiFi.softAPdisconnect(true);             // End App SoftAP
  delay(100); 
  WiFi.mode(WIFI_STA);                     // Start WiFi in Station Mode
  delay(100);
}

// ----------------------------------------------------------------------------------------------------------------------------
// Runs network scan, and lists them on the WEB page so that the user can select one and register the network Password
void wifi_esp_class::handle_wifi_config_scan (void)
{
    int i;
    String web_page= HTTP_HEAD1;
    Ko.TIMERS.timer_wifi_AP=180;
    int n = WiFi.scanNetworks();
    
    if (n == 0) 
      {
      web_page += F("No networks found. Refresh to scan again.");
      } 
    else 
        {   
        int index[n];
        for (i = 0; i < n; i++) {
          index[i] = i;
            }
        // Organize according to power
        for (i = 0; i < n; i++) 
          {
          for (int j = i + 1; j < n; j++) 
              {
              if (WiFi.RSSI(index[j]) > WiFi.RSSI(index[i])) 
                {
                std::swap(index[i], index[j]);
                }
              }
          }

  // remove duplicates ( must be RSSI sorted )
        String cssid;
        for (int i = 0; i < n; i++) 
          {
          if (index[i] == -1) continue;
            cssid = WiFi.SSID(index[i]);
          for (int j = i + 1; j < n; j++) 
            {
            if (cssid == WiFi.SSID(index[j])) 
              {
              index[j] = -1; // set dup aps to index -1
              }
            }
          }
 
 //display networks in page   
        if (n>8)
            n=8; 
        
        for (int i=0; i<n ; i++)
          {
          if (index[i] == -1) continue; // skip dups
          int quality =getRSSIasQuality(WiFi.RSSI(index[i]));
          if (quality>=30) 
              {
              String item = HTTP_ITEM;
              String rssiQ;
              rssiQ += quality;
              item.replace("{v}", WiFi.SSID(index[i]));
              item.replace("{r}", rssiQ);
              if (WiFi.encryptionType(index[i]) != 0) {
                item.replace("{i}", "l");
              } 
              else 
              item.replace("{i}", "");
              
              web_page += item;
              delay(0);
              }
          else;
          }
        }
  web_page+=config_wifi_scan;
  web_page+=HTTP_END;
  

server_esp.send(200, "text/html", web_page); 
}

int wifi_esp_class::getRSSIasQuality(int RSSI) { 
  int quality = 0;

  if (RSSI <= -100) {
    quality = 0;
  } else if (RSSI >= -50) {
    quality = 100;
  } else {
    quality = 2 * (RSSI + 100);
  }
  return quality;
}

//---------------------------------------------------------------------------------------------------------------------
// --- Service launched when Device is Configured --- 
// 
// Function:
// Launched when pressing the "OK" button on the configuration page
// Result Variable Message:
// Not configured =0;
// Correct_Configuration = 1;
// Incorrect Password or SSID configuration = 2;
// Incorrect server or port configuration =3
//---------------------------------------------------------------------------------------------------------------------


void wifi_esp_class::wifi_conf1()                                     
{    
int ssid_size=0;
int pass_size=0;

int  counter;
WiFiMulti wifiMulti_test;

        String getssid = server_esp.arg("ssid");                  // Receive the values ​​sent by the portal
        String getpass = server_esp.arg("pass");
        
        getssid=Correct_Symbols(getssid);                         // replace the UTF8 symbols with the right symbol
        getpass=Correct_Symbols(getpass);
      
        ssid_size=getssid.length()+1;                             // size of ssid and password
        pass_size=getpass.length()+1;
        
        getssid.toCharArray(ssid,ssid_size);                      // String to char array
        getpass.toCharArray(pass,pass_size);


        if (ssid_size>1)
          {
          server_esp.send(200, "text/html",HTTP_HEAD1+wifi_save+Test_Config+HTTP_END);        
          
          WiFi.disconnect();
          delay(500);

          wifiMulti_test.addAP(ssid,pass);
          delay(10);        
              
          while ((wifiMulti_test.run() != WL_CONNECTED)&&(counter <5))         // Wait for connection
                {
                delay (500);
                Serial.print(".");
                counter++; 
                }
        
        if ((wifiMulti_test.run()== WL_CONNECTED))                             // Correct?
            {
            WiFi_Config_Response=1;
            int sotored_position = get_stored_position();
            if (activate_debug)
                {
                Serial.println("");
                Serial.printf("SSID %s saved in position: %d\r\n",getssid,sotored_position);
                Serial.println();
                }
           if (sotored_position==1)
                {
                EEPROM_MEM.Write_1Byte_EEPROM(dir_config1,1);                       // Record "configured" so that when the board boots, it knows that it has correct data, so it proceeds to try a connection.
                EEPROM_MEM.Write_String_EEPROM(add_ssid1,getssid);                  // Stored ssid 1
                EEPROM_MEM.Write_String_EEPROM(dir_pass1,getpass);                  // Stored Password 1
                }
           else if (sotored_position==2)
                { 
                EEPROM_MEM.Write_1Byte_EEPROM(dir_config2,1);                       
                EEPROM_MEM.Write_String_EEPROM(add_ssid2,getssid);               
                EEPROM_MEM.Write_String_EEPROM(dir_pass2,getpass);                
                }
              
           else
                {
                EEPROM_MEM.Write_1Byte_EEPROM(dir_config3,1);                      
                EEPROM_MEM.Write_String_EEPROM(add_ssid3,getssid);                
                EEPROM_MEM.Write_String_EEPROM(dir_pass3,getpass);                
                }               

            }
            else
               WiFi_Config_Response=3;
          }
        else
            server_esp.send(200, "text/html",HTTP_HEAD1+no_wifi_save+back_to_home+HTTP_END);

}


//---------------------------------------------------------------------------------------------
void wifi_esp_class::Config_Response (void)
{
    if (WiFi_Config_Response==1)
        server_esp.send(200, "text/html",HTTP_HEAD1+"<div style='text-align:center;'> <h3> !! CORRECT  !! <br>  Settings  Saved </h3></div><br/>"+back_to_home +HTTP_END);
    else if (WiFi_Config_Response==2)
        server_esp.send(200, "text/html",HTTP_HEAD1+"<div style='text-align:center;'> <h3> !! ERROR: Check Your Server Settings !! </h3></div><br/>"+ back_to_home + HTTP_END);
    else 
        server_esp.send(200, "text/html",HTTP_HEAD1+"<div style='text-align:center;'> <h3> !! ERROR: Check Your SSID And Password !! </h3></div><br/>"+back_to_home+HTTP_END);
}

//---------------------------------------------------------------------------------------------
void wifi_esp_class::Launch_cloud_settings (void)
 {
    String html_cloud=Cloud_settings; 
    Ko.TIMERS.timer_wifi_AP=180;
    html_cloud.replace("10",String(Ko.CONFIG.DT.TPU));
    String token=EEPROM_MEM.Read_String_EEPROM(dir_token);
    char modifyToken [50];
    token.toCharArray(modifyToken,50);
    for(int i=5; i<25;i++)
      modifyToken[i]='X';
   
    modifyToken[25]='-';
    
    token=String(modifyToken);
    html_cloud.replace("BBFF-",token);
    server_esp.send(200, "text/html",HTTP_HEAD1+html_cloud+back_to_home+HTTP_END);
  }

void wifi_esp_class::Get_cloud_settings(void)                                     
{    
        String getserver = server_esp.arg("server");                  // Receive the values ​​sent by the portal
        String gettoken = server_esp.arg("token");
        int TPU = server_esp.arg("tpu").toInt();
        if(TPU >=1 && TPU <= 1440)
            Ko.CONFIG.DT.TPU  = TPU;
        
        //getserver=Correct_Symbols(getserver);                         // replace the UTF8 symbols with the right symbol
        //gettoken=Correct_Symbols(gettoken);
       
        if(activate_debug)
          {
          Serial.printf("Servidor %s\r\n",getserver.c_str());
          Serial.printf("token %s\r\n",gettoken.c_str());
          Serial.printf("TPU %d\r\n",TPU);
          }

        EEPROM_MEM.Write_String_EEPROM(dir_url_server,getserver);
       
        if((gettoken!="")&&(gettoken.indexOf("XXXXXXXXX")==-1))
            {
              EEPROM_MEM.Write_String_EEPROM(dir_token,gettoken);
            }
        EEPROM_MEM.Write_Int_EEPROM(DIR_TPU,Ko.CONFIG.DT.TPU);
        
        //server_esp.send(302, "text/plain", "");
        server_esp.send(200, "text/html",HTTP_HEAD1+ppal+HTTP_END);
}

//---------------------------------------------------------------------------------------------
void wifi_esp_class::Select_Inputs (void)
{
    server_esp.send(200, "text/html",HTTP_HEAD1+inputs_selector+back_to_home+HTTP_END);
}

void wifi_esp_class::Set_Input1(void)
{
Capture_Inputs_Params(1);
}  
void wifi_esp_class::Set_Input2(void)
{
Capture_Inputs_Params(2);
}    

void wifi_esp_class::Set_Input3(void)
{
Capture_Inputs_Params(3);
}    

void wifi_esp_class::Set_Input4(void)
{
Capture_Inputs_Params(4);
}    

void wifi_esp_class::Set_Input5(void)
{
Capture_Inputs_Params(5);
}    

void wifi_esp_class::Set_Input6(void)
{
Capture_Inputs_Params(6);
}    

void wifi_esp_class::Set_Input7(void)
{
Capture_Inputs_Params(7);
}    

void wifi_esp_class::Set_Input8(void)
{
Capture_Inputs_Params(8);
}    


//-------------------------------------------
void wifi_esp_class::Capture_Inputs_Params(int input)                                     
{    
String Input_name;
String Label,offset,slope,alm_low,alm_high,alm_delay; 
int Input_Type, edge;
int Modbus_Slave_Addrress, Modbus_Start_Register, Modbus_qty_registers, Modbus_Format;
Ko.TIMERS.timer_wifi_AP=180;
 selected_input = input;

        String page = HTTP_HEAD1;
        if(selected_input==1)
          {
          Input_name = "Analog Input 1";
          Current_Value = String(Ko.IN1.value/pow10(Ko.IN1.resolution));
          Input_Type = Ko.IN1.type;
          Label   = Ko.IN1.Label;
          offset  = String((float)Ko.IN1.offset/10.0);
          slope   = String((float)Ko.IN1.slope/1000.0);
          alm_low = String((float)Ko.IN1.L_limit/10.0);
          alm_high= String((float)Ko.IN1.H_limit/10.0);
          alm_delay=String(Ko.IN1.alarm_delay);
          Modbus_Slave_Addrress=Ko.IN1.address;
          Modbus_Start_Register=Ko.IN1.modbus_start_register;
          Modbus_qty_registers=Ko.IN1.modbus_coils_qty;
          Modbus_Format=Ko.IN1.modbus_type;
          }
        else if(selected_input==2)
          {
          Input_name = "Analog Input 2";
          Current_Value = String(Ko.IN2.value/pow10(Ko.IN2.resolution));
          Input_Type = Ko.IN2.type;
          Label   = Ko.IN2.Label;
          offset  = String((float)Ko.IN2.offset/10.0);
          slope   = String((float)Ko.IN2.slope/1000.0);
          alm_low = String((float)Ko.IN2.L_limit/10.0);
          alm_high= String((float)Ko.IN2.H_limit/10.0);
          alm_delay=String(Ko.IN2.alarm_delay);
          Modbus_Slave_Addrress=Ko.IN2.address;
          Modbus_Start_Register=Ko.IN2.modbus_start_register;
          Modbus_qty_registers=Ko.IN2.modbus_coils_qty;
          Modbus_Format=Ko.IN2.modbus_type;
          }

        else if(selected_input==3)
          {
          Input_name = "Analog Input 3";
          Current_Value = String(Ko.IN3.value/pow10(Ko.IN3.resolution));
          Input_Type = Ko.IN3.type;
          Label   = Ko.IN3.Label;
          offset  = String((float)Ko.IN3.offset/10.0);
          slope   = String((float)Ko.IN3.slope/1000.0);
          alm_low = String((float)Ko.IN3.L_limit/10.0);
          alm_high= String((float)Ko.IN3.H_limit/10.0);
          alm_delay=String(Ko.IN3.alarm_delay);
          Modbus_Slave_Addrress=Ko.IN3.address;
          Modbus_Start_Register=Ko.IN3.modbus_start_register;
          Modbus_qty_registers=Ko.IN3.modbus_coils_qty;
          Modbus_Format=Ko.IN3.modbus_type;
          }

      else if(selected_input==4)
          {
          Input_name = "Analog Input 4";
          Current_Value = String(Ko.IN4.value/pow10(Ko.IN4.resolution));
          Input_Type = Ko.IN4.type;
          Label   = Ko.IN4.Label;
          offset  = String((float)Ko.IN4.offset/10.0);
          slope   = String((float)Ko.IN4.slope/1000.0);
          alm_low = String((float)Ko.IN4.L_limit/10.0);
          alm_high= String((float)Ko.IN4.H_limit/10.0);
          alm_delay=String(Ko.IN4.alarm_delay);
          Modbus_Slave_Addrress=Ko.IN4.address;
          Modbus_Start_Register=Ko.IN4.modbus_start_register;
          Modbus_qty_registers=Ko.IN4.modbus_coils_qty;
          Modbus_Format=Ko.IN4.modbus_type;
          }

      else if(selected_input==5)
          {
          Input_name = "Analog Input 5";
          Current_Value = String(Ko.IN5.value/pow10(Ko.IN5.resolution));
          Input_Type = Ko.IN5.type;
          Label   = Ko.IN5.Label;
          offset  = String((float)Ko.IN5.offset/10.0);
          slope   = String((float)Ko.IN5.slope/1000.0);
          alm_low = String((float)Ko.IN5.L_limit/10.0);
          alm_high= String((float)Ko.IN5.H_limit/10.0);
          alm_delay=String(Ko.IN5.alarm_delay);
          Modbus_Slave_Addrress=Ko.IN5.address;
          Modbus_Start_Register=Ko.IN5.modbus_start_register;
          Modbus_qty_registers=Ko.IN5.modbus_coils_qty;
          Modbus_Format=Ko.IN5.modbus_type;
          }

        else if(selected_input==6)
          {
          Input_name = "Digital Input 6";
          Current_Value = String(Ko.IN6.value);
          Input_Type = Ko.IN6.type;
          Label = Ko.IN6.Label;
          edge = Ko.IN6.Pulse_Edge;
          Modbus_Slave_Addrress=Ko.IN6.address;
          Modbus_Start_Register=Ko.IN6.modbus_start_register;
          Modbus_qty_registers=Ko.IN6.modbus_coils_qty;
          Modbus_Format=Ko.IN6.modbus_type;
          }
        
         else if(selected_input==7)
          {
          Input_name = "Digital Input 7";
          Current_Value = String(Ko.IN7.value);
          Input_Type = Ko.IN7.type;
          Label   = Ko.IN7.Label;
          edge = Ko.IN7.Pulse_Edge;
          Modbus_Slave_Addrress=Ko.IN7.address;
          Modbus_Start_Register=Ko.IN7.modbus_start_register;
          Modbus_qty_registers=Ko.IN7.modbus_coils_qty;
          Modbus_Format=Ko.IN7.modbus_type;
          }
        else
          {
          Input_name = "Digital Input 8";
          Current_Value = String(Ko.IN8.value);
          Input_Type = Ko.IN8.type;
          Label   = Ko.IN8.Label;
          edge = Ko.IN8.Pulse_Edge;
          Modbus_Slave_Addrress=Ko.IN8.address;
          Modbus_Start_Register=Ko.IN8.modbus_start_register;
          Modbus_qty_registers=Ko.IN8.modbus_coils_qty;
          Modbus_Format=Ko.IN8.modbus_type;
          }
      
      page += "<script>";
      page += "setInterval(function() { fetchTemperature(); }, 2000);";
      page += "function fetchTemperature() {";
      page += "fetch('/send_input_value').then(response => response.text()).then(data => {";
      page += "document.getElementById('value').innerHTML = data;";
      page += "});}";
      page += "</script>";
    
      page +="<form action='/inputs_settings' method='post'>";
      page += "<h2>"+ Input_name + "</h2><br>";
      page += "<h3>Current Value: <span id='value'>" + Current_Value + "</span> </h3><br>";
      page +="<h3>Input Label: </h3>";
      page += "<input id='p' name='label'  value='" + Label + "' length=7 type='text' placeholder='Label :'><br><br>";
      page += "<h3>Input Type: </h3>";
      page += "<select name='Type' id='Inputs_Selector'>";
       
      if((selected_input==6)||(selected_input==7)||(selected_input==8))
          {
          if(Input_Type==0)
            page+= "<option value='0' selected> Disable</option>";
          else
            page+= "<option value='0'> Disable</option>";
          
          if(Input_Type==1)
              page+= "<option value='1' selected> Digital Input (1/0)</option>";
          else  
              page+= "<option value='1'> Digital Input (1/0)</option>";
          
          if(Input_Type==7)
             page+= "<option value='7' selected> Counter (Cumulative)</option>";
          else
            page+= "<option value='7'> Counter (Cumulative)</option>";
     
          if(Input_Type==11)
            page+= "<option value='11' selected> Counter (Reset Every Interval)</option>";
          else
             page+= "<option value='11'> Counter (Reset Every Interval)</option>";
         
          if(Input_Type==10)
            page+= "<option value='10' selected> Frequency Hz</option>";
          else
            page+= "<option value='10'> Frequency Hz </option>";
          
          if(Input_Type==15)
            page+= "<option value='15' selected> Frequency RPM</option>";
          else
            page+= "<option value='15'> Frequency RPM </option>";
          
          if(Input_Type==12)
            page+= "<option value='12' selected> Runtime Minutes (Cumulative) </option>";
          else
            page+= "<option value='12'> Runtime Minutes (Cumulative) </option>";
          
          if(Input_Type==13)
             page+= "<option value='13' selected> Runtime Minutes (Reset Every Interval) </option>";
          else
            page+= "<option value='13'> Runtime Minutes (Reset Every Interval) </option>";
          
          page+="</select><br><br>";

          page +="<h3> Pulse Detection Edge: </h3>";
          page += "<select name='edge' id='Edge_Selector'>";
          if(edge==0)
            {
            page+= "<option value='0' selected> Falling Edge </option>";
            page+= "<option value='1'> Rising Edge </option>";
            }
          else
            {
            page+= "<option value='0'> Falling Edge </option>";
            page+= "<option value='1' selected> Rising Edge </option>";
            }
          page+="</select><br><br>";  
          }
      else
          {
          if(Input_Type==0)
            page+= "<option value='0' selected> Disable</option>";
          else
            page+= "<option value='0'> Disable</option>";

          if(Input_Type==1)
              page+= "<option value='1' selected> Digital Input (1/0)</option>";
          else  
              page+= "<option value='1'> Digital Input (1/0)</option>";

          if(Input_Type==2)
            page+= "<option value='2' selected> Current 4..20 mA</option>";
          else
            page+= "<option value='2'> Current 4..20 mA</option>";
          
          if(Input_Type==3)
            page+= "<option value='3' selected> Voltage 0..10 V</option>";
          else
             page+= "<option value='3'> Voltage 0..10 V</option>";
          if(Input_Type==4)
            page+= "<option value='4' selected> Temperature NTC 10K</option>";
          else
            page+= "<option value='4'> Temperature NTC 10K</option>";
          if(Input_Type==8)
            page+= "<option value='8' selected> Remote Input</option>";
          else
            page+= "<option value='8'> Remote Input</option>";
          
          page+="</select><br><br>";
          
          page +="<h3>Offset Value: </h3>";
          page += "<input id='q' name='offset'  value='" + offset + "' length=64 type='text' placeholder='offset :'><br><br>";
          page +="<h3>Slope: </h3>";
          page += "<input id='r' name='slope'  value='" + slope + "' length=64 type='text' placeholder='slope :'><br><br>";
          page +="<h3>Alarm Low Limit: </h3>";
          page += "<input id='s' name='alm_low'  value='" + alm_low + "' length=64 type='text' placeholder='alm_low :'><br><br>";
          page +="<h3>Alarm High Limit: </h3>";
          page += "<input id='t' name='alm_high'  value='" + alm_high + "' length=64 type='text' placeholder='alm_high :'><br><br>";
          page +="<h3>Alarm Delay (Seconds): </h3>";
          page += "<input id='u' name='alm_delay'  value='" + alm_delay + "' length=64 type='number' placeholder='alm_delay :'><br><br>";
          }
      

      page += "<br><button type='submit'>Save</button></form><br>";
      page += back_to_inputs;
      page += HTTP_END;
      server_esp.send(200, "text/html", page);
 
}

void wifi_esp_class:: Handle_input_value(void)
{
  String tempString;

        if(selected_input==1)
          {
           tempString = String(Ko.IN1.value/pow10(Ko.IN1.resolution));
          }
        else if(selected_input==2)
          {
            tempString = String(Ko.IN2.value/pow10(Ko.IN2.resolution));
          }
        else if(selected_input==3)
          {
            tempString = String(Ko.IN3.value);
          }
        else if(selected_input==4)
          {
            tempString = String(Ko.IN4.value);
          }
        else if(selected_input==5)
          {
            tempString = String(Ko.IN5.value);
          }
        else if(selected_input==6)
          {
            tempString = String(Ko.IN6.value);
          }
        else if(selected_input==7)
          {
            tempString = String(Ko.IN7.value);
          }
        else // if(selected_input==8)
          {
            tempString = String(Ko.IN8.value);
          }
      server_esp.send(200, "text/plain", tempString);
}
void  wifi_esp_class::Get_inputs_parameters(void)
{
  int input_change=0, old_input_type; 
  int type = server_esp.arg("Type").toInt();
  String Label= server_esp.arg("label").substring(0,7);
  float offset=round(server_esp.arg("offset").toFloat()*10.0);
  float slope=round(server_esp.arg("slope").toFloat()*1000.0);
  float alm_high=round(server_esp.arg("alm_high").toFloat()*10.0);
  float alm_low=round(server_esp.arg("alm_low").toFloat()*10.0);
  int alm_delay=server_esp.arg("alm_delay").toInt();
  int edge=server_esp.arg("edge").toInt();
  
  if(selected_input==1)
    {
    if(Ko.IN1.type!=type)
      {
      Ko.IN1.type=type;
      if(type==0)
        Ko.IN1.enable=0;
      else
        {
        Ko.IN1.enable=1;
        if(type==1)
          Ko.IN1.resolution=0;
        else if(type==4)
          Ko.IN1.resolution=1;
        else if((type==2)||(type==3))
          Ko.IN1.resolution=2;
        else 
          Ko.IN1.resolution=1;
        }
      EEPROM_MEM.Write_Int_EEPROM(IN1_EEPROM+2,Ko.IN1.type);
      EEPROM_MEM.Write_Int_EEPROM(IN1_EEPROM+3,Ko.IN1.resolution);
      EEPROM_MEM.Write_Int_EEPROM(IN1_EEPROM+4,Ko.IN1.enable);
      }
    if( Ko.IN1.offset!= (int)offset)
      {
      Ko.IN1.offset=offset;
      EEPROM_MEM.Write_Int_EEPROM(IN1_EEPROM+5,Ko.IN1.offset);
      }
    if(Ko.IN1.slope!= (int)slope)
        {
        Ko.IN1.slope=slope;
        EEPROM_MEM.Write_Int_EEPROM(IN1_EEPROM+12,Ko.IN1.slope);
        }
    if(Ko.IN1.L_limit!=(int)alm_low)
      {
      Ko.IN1.L_limit=alm_low;
      EEPROM_MEM.Write_Int_EEPROM(IN1_EEPROM+6,Ko.IN1.L_limit);
      }
    if(Ko.IN1.H_limit!=(int)alm_high)
      {
      Ko.IN1.H_limit=alm_high;
      EEPROM_MEM.Write_Int_EEPROM(IN1_EEPROM+7,Ko.IN1.H_limit);
      }
    if(Ko.IN1.alarm_delay!=alm_delay)
        {
        Ko.IN1.alarm_delay=alm_delay;
        EEPROM_MEM.Write_Int_EEPROM(IN1_EEPROM+8,Ko.IN1.alarm_delay);
        }
    if(Ko.IN1.Label!=Label)
      {
      Ko.IN1.Label=Label;
      EEPROM_MEM.Write_String_EEPROM(dir_label_input1,Label);
      }
    }
  
  else if(selected_input==2)
    {
    if(Ko.IN2.type!=type)
      {
      Ko.IN2.type=type;
      if(type==0)
        Ko.IN2.enable=0;
      else
        {
        Ko.IN2.enable=1;
        if(type==1)
          Ko.IN2.resolution=0;
        else if(type==4)
          Ko.IN2.resolution=1;
        else if((type==2)||(type==3))
          Ko.IN2.resolution=2;
        else 
          Ko.IN2.resolution=1;
        }
      EEPROM_MEM.Write_Int_EEPROM(IN2_EEPROM+2,Ko.IN2.type);
      EEPROM_MEM.Write_Int_EEPROM(IN2_EEPROM+3,Ko.IN2.resolution);
      EEPROM_MEM.Write_Int_EEPROM(IN2_EEPROM+4,Ko.IN2.enable);
      }
    if( Ko.IN2.offset!= (int)offset)
      {
      Ko.IN2.offset=offset;
      EEPROM_MEM.Write_Int_EEPROM(IN2_EEPROM+5,Ko.IN2.offset);
      }
    if(Ko.IN2.slope!= (int)slope)
        {
        Ko.IN2.slope=slope;
        EEPROM_MEM.Write_Int_EEPROM(IN2_EEPROM+12,Ko.IN2.slope);
        }
    if(Ko.IN2.L_limit!=(int)alm_low)
      {
      Ko.IN2.L_limit=alm_low;
      EEPROM_MEM.Write_Int_EEPROM(IN2_EEPROM+6,Ko.IN2.L_limit);
      }
    if(Ko.IN2.H_limit!=(int)alm_high)
      {
      Ko.IN2.H_limit=alm_high;
      EEPROM_MEM.Write_Int_EEPROM(IN2_EEPROM+7,Ko.IN2.H_limit);
      }
    if(Ko.IN2.alarm_delay!=alm_delay)
        {
        Ko.IN2.alarm_delay=alm_delay;
        EEPROM_MEM.Write_Int_EEPROM(IN2_EEPROM+8,Ko.IN2.alarm_delay);
        }
    if(Ko.IN2.Label!=Label)
      {
      Ko.IN2.Label=Label;
      EEPROM_MEM.Write_String_EEPROM(dir_label_input2,Label);
      }
    }
  
  else if(selected_input==3)
    {
    if(Ko.IN3.type!=type)
      {
      Ko.IN3.type=type;
      if(type==0)
        Ko.IN3.enable=0;
      else
        {
        Ko.IN3.enable=1;
        if(type==1)
          Ko.IN3.resolution=0;
        else if(type==4)
          Ko.IN3.resolution=1;
        else if((type==2)||(type==3))
          Ko.IN3.resolution=2;
        else 
          Ko.IN3.resolution=1;
        }
      EEPROM_MEM.Write_Int_EEPROM(IN3_EEPROM+2,Ko.IN3.type);
      EEPROM_MEM.Write_Int_EEPROM(IN3_EEPROM+3,Ko.IN3.resolution);
      EEPROM_MEM.Write_Int_EEPROM(IN3_EEPROM+4,Ko.IN3.enable);
      }
    if( Ko.IN3.offset!= (int)offset)
      {
      Ko.IN3.offset=offset;
      EEPROM_MEM.Write_Int_EEPROM(IN3_EEPROM+5,Ko.IN3.offset);
      }
    if(Ko.IN3.slope!= (int)slope)
        {
        Ko.IN3.slope=slope;
        EEPROM_MEM.Write_Int_EEPROM(IN3_EEPROM+12,Ko.IN3.slope);
        }
    if(Ko.IN3.L_limit!=(int)alm_low)
      {
      Ko.IN3.L_limit=alm_low;
      EEPROM_MEM.Write_Int_EEPROM(IN3_EEPROM+6,Ko.IN3.L_limit);
      }
    if(Ko.IN3.H_limit!=(int)alm_high)
      {
      Ko.IN3.H_limit=alm_high;
      EEPROM_MEM.Write_Int_EEPROM(IN3_EEPROM+7,Ko.IN3.H_limit);
      }
    if(Ko.IN3.alarm_delay!=alm_delay)
        {
        Ko.IN3.alarm_delay=alm_delay;
        EEPROM_MEM.Write_Int_EEPROM(IN3_EEPROM+8,Ko.IN3.alarm_delay);
        }
    if(Ko.IN3.Label!=Label)
      {
      Ko.IN3.Label=Label;
      EEPROM_MEM.Write_String_EEPROM(dir_label_input3,Label);
      }
    }
  
  else if(selected_input==4)
    {
    if(Ko.IN4.type!=type)
      {
      Ko.IN4.type=type;
      if(type==0)
        Ko.IN4.enable=0;
      else
        {
        Ko.IN4.enable=1;
        if(type==1)
          Ko.IN4.resolution=0;
        else if(type==4)
          Ko.IN4.resolution=1;
        else if((type==2)||(type==3))
          Ko.IN4.resolution=2;
        else 
          Ko.IN4.resolution=1;
        }
      EEPROM_MEM.Write_Int_EEPROM(IN4_EEPROM+2,Ko.IN4.type);
      EEPROM_MEM.Write_Int_EEPROM(IN4_EEPROM+3,Ko.IN4.resolution);
      EEPROM_MEM.Write_Int_EEPROM(IN4_EEPROM+4,Ko.IN4.enable);
      }
    if( Ko.IN4.offset!= (int)offset)
      {
      Ko.IN4.offset=offset;
      EEPROM_MEM.Write_Int_EEPROM(IN4_EEPROM+5,Ko.IN4.offset);
      }
    if(Ko.IN4.slope!= (int)slope)
        {
        Ko.IN4.slope=slope;
        EEPROM_MEM.Write_Int_EEPROM(IN4_EEPROM+12,Ko.IN4.slope);
        }
    if(Ko.IN4.L_limit!=(int)alm_low)
      {
      Ko.IN4.L_limit=alm_low;
      EEPROM_MEM.Write_Int_EEPROM(IN4_EEPROM+6,Ko.IN4.L_limit);
      }
    if(Ko.IN4.H_limit!=(int)alm_high)
      {
      Ko.IN4.H_limit=alm_high;
      EEPROM_MEM.Write_Int_EEPROM(IN4_EEPROM+7,Ko.IN4.H_limit);
      }
    if(Ko.IN4.alarm_delay!=alm_delay)
        {
        Ko.IN4.alarm_delay=alm_delay;
        EEPROM_MEM.Write_Int_EEPROM(IN4_EEPROM+8,Ko.IN4.alarm_delay);
        }
    if(Ko.IN4.Label!=Label)
      {
      Ko.IN4.Label=Label;
      EEPROM_MEM.Write_String_EEPROM(dir_label_input4,Label);
      }
    }

  else if(selected_input==5)
    {
    if(Ko.IN5.type!=type)
      {
      Ko.IN5.type=type;
      if(type==0)
        Ko.IN5.enable=0;
      else
        {
        Ko.IN5.enable=1;
        if(type==1)
          Ko.IN5.resolution=0;
        else if(type==4)
          Ko.IN5.resolution=1;
        else if((type==2)||(type==3))
          Ko.IN5.resolution=2;
        else 
          Ko.IN5.resolution=1;
        }
      EEPROM_MEM.Write_Int_EEPROM(IN5_EEPROM+2,Ko.IN5.type);
      EEPROM_MEM.Write_Int_EEPROM(IN5_EEPROM+3,Ko.IN5.resolution);
      EEPROM_MEM.Write_Int_EEPROM(IN5_EEPROM+4,Ko.IN5.enable);
      }
    if( Ko.IN5.offset!= (int)offset)
      {
      Ko.IN5.offset=offset;
      EEPROM_MEM.Write_Int_EEPROM(IN5_EEPROM+5,Ko.IN5.offset);
      }
    if(Ko.IN5.slope!= (int)slope)
        {
        Ko.IN5.slope=slope;
        EEPROM_MEM.Write_Int_EEPROM(IN5_EEPROM+12,Ko.IN5.slope);
        }
    if(Ko.IN5.L_limit!=(int)alm_low)
      {
      Ko.IN5.L_limit=alm_low;
      EEPROM_MEM.Write_Int_EEPROM(IN5_EEPROM+6,Ko.IN5.L_limit);
      }
    if(Ko.IN5.H_limit!=(int)alm_high)
      {
      Ko.IN5.H_limit=alm_high;
      EEPROM_MEM.Write_Int_EEPROM(IN5_EEPROM+7,Ko.IN5.H_limit);
      }
    if(Ko.IN5.alarm_delay!=alm_delay)
        {
        Ko.IN5.alarm_delay=alm_delay;
        EEPROM_MEM.Write_Int_EEPROM(IN5_EEPROM+8,Ko.IN5.alarm_delay);
        }
    if(Ko.IN5.Label!=Label)
      {
      Ko.IN5.Label=Label;
      EEPROM_MEM.Write_String_EEPROM(dir_label_input5,Label);
      }
    }
  
  else if(selected_input==6)
    {
    if(Ko.IN6.type!=type)
      {
      old_input_type=Ko.IN6.type;
      input_change++;
      Ko.IN6.type=type;
      if(type==0)
        Ko.IN6.enable=0;
      else
        Ko.IN6.enable=1;
      Ko.IN6.resolution=0;
      EEPROM_MEM.Write_Int_EEPROM(IN6_EEPROM+2,Ko.IN6.type);
      EEPROM_MEM.Write_Int_EEPROM(IN6_EEPROM+3,Ko.IN6.resolution);
      EEPROM_MEM.Write_Int_EEPROM(IN6_EEPROM+4,Ko.IN6.enable);
      }
    if(Ko.IN6.Pulse_Edge!=edge)
      {
      input_change++;
      Ko.IN6.Pulse_Edge=edge;
      EEPROM_MEM.Write_Int_EEPROM(IN6_EEPROM+14,Ko.IN6.Pulse_Edge);
      }
    if(input_change>0)
      In.INIT_DIGITAL_INPUTS(digital_input6,old_input_type);       // Init Input 6
    
    if(Ko.IN6.Label!=Label)
      {
      Ko.IN6.Label=Label;
      EEPROM_MEM.Write_String_EEPROM(dir_label_input6,Label);
      }
    }
  
  else if(selected_input==7)
    {
    if(Ko.IN7.type!=type)
      {
      input_change++;
      old_input_type=Ko.IN7.type;
      Ko.IN7.type=type;
      if(type==0)
        Ko.IN7.enable=0;
      else
        Ko.IN7.enable=1;
      Ko.IN7.resolution=0;
      Ko.IN7.Pulse_Edge=edge;
      EEPROM_MEM.Write_Int_EEPROM(IN7_EEPROM+2,Ko.IN7.type);
      EEPROM_MEM.Write_Int_EEPROM(IN7_EEPROM+3,Ko.IN7.resolution);
      EEPROM_MEM.Write_Int_EEPROM(IN7_EEPROM+4,Ko.IN7.enable);
      }
    
    if(Ko.IN7.Pulse_Edge!=edge)
      {
      input_change++;
      Ko.IN7.Pulse_Edge=edge;
      EEPROM_MEM.Write_Int_EEPROM(IN7_EEPROM+14,Ko.IN7.Pulse_Edge);
      }
    if(input_change>0)
      In.INIT_DIGITAL_INPUTS(digital_input7,old_input_type);       // Init Input 7
    
    if(Ko.IN7.Label!=Label)
      {
      Ko.IN7.Label=Label;
      EEPROM_MEM.Write_String_EEPROM(dir_label_input7,Label);
      }
    }

  else
    {
    if(Ko.IN8.type!=type)
      {
      input_change++;
      old_input_type=Ko.IN8.type;
      Ko.IN8.type=type;
      if(type==0)
        Ko.IN8.enable=0;
      else
        Ko.IN8.enable=1;
      Ko.IN8.resolution=0;
      Ko.IN8.Pulse_Edge=edge;
      EEPROM_MEM.Write_Int_EEPROM(IN8_EEPROM+2,Ko.IN8.type);
      EEPROM_MEM.Write_Int_EEPROM(IN8_EEPROM+3,Ko.IN8.resolution);
      EEPROM_MEM.Write_Int_EEPROM(IN8_EEPROM+4,Ko.IN8.enable);
      }

    if(Ko.IN8.Pulse_Edge!=edge)
      {
      input_change++;
      Ko.IN8.Pulse_Edge=edge;
      EEPROM_MEM.Write_Int_EEPROM(IN8_EEPROM+14,Ko.IN8.Pulse_Edge);
      }
    if(input_change>0)
      In.INIT_DIGITAL_INPUTS(digital_input8,old_input_type);       // Init Input 8
    
    if(Ko.IN8.Label!=Label)
      {
      Ko.IN8.Label=Label;
      EEPROM_MEM.Write_String_EEPROM(dir_label_input8,Label);
      }
  }
  Select_Inputs();
}
//--------------------------------------------------------------------------------------------
// OUTPUTS CONFIGURATOR

//---------------------------------------------------------------------------------------------
void wifi_esp_class::Select_Outputs (void)
{
    server_esp.send(200, "text/html",HTTP_HEAD1+outputs_selector+back_to_home+HTTP_END);
}

void wifi_esp_class::Set_Output1(void)
{
Capture_Outputs_Params(1);
}  
void wifi_esp_class::Set_Output2(void)
{
Capture_Outputs_Params(2);
}    

void wifi_esp_class::Set_Output3(void)
{
Capture_Outputs_Params(3);
} 

void wifi_esp_class::Set_Output4(void)
{
Capture_Outputs_Params(4);
} 

void wifi_esp_class::Set_Output5(void)
{
Capture_Outputs_Params(5);
} 

//-------------------------------------------
/*
   OUTPUTS Parameters
        int16_t  address;						// Addres of the output (Output 1 and 2)
        int16_t  value;							// Current value of the output [0 or 1]
        int16_t  control_funtion;			    // Designated control function:  Controll On/Off,  PID, Timer
        int16_t  control_signal;				// Control singal (input 1, 2 ; or 0: none).
        int16_t  set_point;						// Set Point
        int16_t  hysteresis;					// Hysteresis in On/Off control mode				
        int16_t  control_type;				    // Control Type (normal or inverted output)
        uint16_t set_time_ON;                   // Cycle time ON for timer / Cycle Time for PID
        uint16_t set_time_OFF;                  // Cycle time OFF for timer / Time to make Control Calculations for PID
        int16_t  Kp;                     		// Proportional Action for PID
        int16_t  Int;                    		// Integral Action for PID
        int16_t  Der;                    		// Derivative Action for PID
        int16_t  Pmax;   
*/
void wifi_esp_class::Capture_Outputs_Params(int output)                                     
{    
String Output_name,Label;
String set_point,hysteresis,control_type,timer_on, timer_off, pid_kp, pid_der, pid_int, pid_pow; 
int control_function,control_signal;
Ko.TIMERS.timer_wifi_AP=180;
selected_output=output;

        String page = HTTP_HEAD1;
        if(output==1)
          {
          Label = Ko.OUT1.Label;
          Output_name = "Relay Output 1";
          Current_Value = String(Ko.OUT1.value);
          control_function  = Ko.OUT1.control_function;
          control_signal   =  Ko.OUT1.control_signal;
          set_point = String((float) Ko.OUT1.set_point/10.0);
          hysteresis= String((float)Ko.OUT1.hysteresis/10.0);
          control_type=String(Ko.OUT1.control_type);
          timer_on=String(Ko.OUT1.set_time_ON);
          timer_off=String(Ko.OUT1.set_time_OFF);
          pid_kp=String(Ko.OUT1.Kp);
          pid_der=String(Ko.OUT1.Der);
          pid_int=String(Ko.OUT1.Int);
          pid_pow=String(Ko.OUT1.Pmax);
          }
        else if(output==2)
          {
          Label = Ko.OUT2.Label;
          Output_name = "Relay Output 2";
          Current_Value = String(Ko.OUT2.value);
          control_function  = Ko.OUT2.control_function;
          control_signal   =  Ko.OUT2.control_signal;
          set_point = String((float) Ko.OUT2.set_point/10.0);
          hysteresis= String((float)Ko.OUT2.hysteresis/10.0);
          control_type=String(Ko.OUT2.control_type);
          timer_on=String(Ko.OUT2.set_time_ON);
          timer_off=String(Ko.OUT2.set_time_OFF);
          pid_kp=String(Ko.OUT2.Kp);
          pid_der=String(Ko.OUT2.Der);
          pid_int=String(Ko.OUT2.Int);
          pid_pow=String(Ko.OUT2.Pmax);
          }        
      else if(output==3)
          {
          Label = Ko.OUT3.Label;
          Output_name = "Relay Output 3";
          Current_Value = String(Ko.OUT3.value);
          control_function  = Ko.OUT3.control_function;
          control_signal   =  Ko.OUT3.control_signal;
          set_point = String((float) Ko.OUT3.set_point/10.0);
          hysteresis= String((float)Ko.OUT3.hysteresis/10.0);
          control_type=String(Ko.OUT3.control_type);
          timer_on=String(Ko.OUT3.set_time_ON);
          timer_off=String(Ko.OUT3.set_time_OFF);
          pid_kp=String(Ko.OUT3.Kp);
          pid_der=String(Ko.OUT3.Der);
          pid_int=String(Ko.OUT3.Int);
          pid_pow=String(Ko.OUT3.Pmax);
          }    

      else if(output==4)
          {
          Label = Ko.OUT4.Label;
          Output_name = "Relay Output 4";
          Current_Value = String(Ko.OUT4.value);
          control_function  = Ko.OUT4.control_function;
          control_signal   =  Ko.OUT4.control_signal;
          set_point = String((float) Ko.OUT4.set_point/10.0);
          hysteresis= String((float)Ko.OUT4.hysteresis/10.0);
          control_type=String(Ko.OUT4.control_type);
          timer_on=String(Ko.OUT4.set_time_ON);
          timer_off=String(Ko.OUT4.set_time_OFF);
          pid_kp=String(Ko.OUT4.Kp);
          pid_der=String(Ko.OUT4.Der);
          pid_int=String(Ko.OUT4.Int);
          pid_pow=String(Ko.OUT4.Pmax);
          }    

      else        //if(output==5)
          {
          Label = Ko.OUT5.Label;
          Output_name = "Relay Output 5";
          Current_Value = String(Ko.OUT5.value);
          control_function  = Ko.OUT5.control_function;
          control_signal   =  Ko.OUT5.control_signal;
          set_point = String((float) Ko.OUT5.set_point/10.0);
          hysteresis= String((float)Ko.OUT5.hysteresis/10.0);
          control_type=String(Ko.OUT5.control_type);
          timer_on=String(Ko.OUT5.set_time_ON);
          timer_off=String(Ko.OUT5.set_time_OFF);
          pid_kp=String(Ko.OUT5.Kp);
          pid_der=String(Ko.OUT5.Der);
          pid_int=String(Ko.OUT5.Int);
          pid_pow=String(Ko.OUT5.Pmax);
          }    


      page += "<script>";
      page += "setInterval(function() { fetchOutput(); }, 2000);";
      page += "function fetchOutput() {";
      page += "fetch('/send_output_value').then(response => response.text()).then(data => {";
      page += "document.getElementById('value').innerHTML = data;";
      page += "});}";
      page += "</script>";
    
      page +="<form action='/outputs_settings' method='post'>";
      page += "<h2>"+ Output_name + "</h2><br>";
      page += "<h3>Current Value: <span id='value'>" + Current_Value + "</span> </h3><br>";
      page +="<h3>Output Label: </h3>";
      page += "<input id='p' name='label'  value='" + Label + "' length=7 type='text' placeholder='Label :'><br><br>";
      page += "<h3>Control Function: </h3>";
      page += "<select name='function' id='Outputs_Selector'>";
          
      if(control_function==outoff)
        page+= "<option value='0' selected> Disable</option>";
      else
        page+= "<option value='0'> Disable</option>";
      
      if(control_function==remote_commands)
          page+= "<option value='1' selected> Remotely Commanded</option>";
      else  
          page+= "<option value='1'>Remotely Commanded</option>";
      
      if(control_function==input_follower)
          page+= "<option value='2' selected> Input Follower</option>";
      else
        page+= "<option value='2'> Input Follower</option>";
  
      if(control_function==on_off)
        page+= "<option value='11' selected> On/Off Controller</option>";
      else
          page+= "<option value='3'> On/Off Controller</option>";
      
      if(control_function==timer)
        page+= "<option value='4' selected> Timer Output </option>";
      else
        page+= "<option value='4'> Timer Output </option>";
      
      if(control_function==remote_alarm)
        page+= "<option value='5' selected> External Alarm </option>";
      else
        page+= "<option value='5'> External Alarm </option>";
      
      if(control_function==event_counter)
          page+= "<option value='6' selected> Event Counter </option>";
      else
        page+= "<option value='6'>Event Counter </option>";
      
      if(control_function==PID)
          page+= "<option value='7' selected> PID Controller </option>";
      else
        page+= "<option value='7'>PID Controller </option>";
      
      page+="</select><br><br>";

      page +="<h3>Process Value Assigned: </h3>";
      page += "<select name='signal' id='Control_Signal'>";

      if(control_signal==1)         
        page+= "<option value='0' selected> No Signal Assigned </option>";
      else
        page+= "<option value='0'> No Signal Assigned </option>";
      if(control_signal==1)         
        page+= "<option value='1' selected> Analog Input 1 </option>";
      else
      page+= "<option value='1'> Analog Input 1 </option>";
      
      if(control_signal==2) 
          page+= "<option value='2' selected> Analog Input 2 </option>";
      else
        page+= "<option value='2'> Analog Input 2 </option>";
      
      if(control_signal==3) 
        page+= "<option value='3' selected> Analog Input 3 </option>";
      else
        page+= "<option value='3'> Analog Input 3 </option>";
      
      if(control_signal==4) 
        page+= "<option value='4' selected> Analog Input 4 </option>";
      else  
        page+= "<option value='4'> Analog Input 4 </option>";
        
      if(control_signal==5) 
        page+= "<option value='5' selected> Analog Input 5 </option>";
      else
        page+= "<option value='5'> Analog Input 5 </option>";

      if(control_signal==6) 
        page+= "<option value='6' selected> Digital Input 6 </option>";
      else
        page+= "<option value='6'> Digital Input 6 </option>";

      if(control_signal==7) 
        page+= "<option value='7' selected> Digital Input 7 </option>";
      else
        page+= "<option value='7'> Digital Input 7 </option>";

      if(control_signal==8) 
        page+= "<option value='8' selected> Digital Input 8 </option>";
      else
        page+= "<option value='8'> Digital Input 8 </option>";
      
      page+="</select><br><br>";  


      page += "<h3>Control Function Type: </h3>";
      page += "<select name='control_type' id='Control_Type'>";
      if(control_type==0)
        {
        page+= "<option value='0' selected> Cooling </option>";
        page+= "<option value='1'> Heating</option>";
        }
      else
        {
        page+= "<option value='0'> Cooling </option>";
        page+= "<option value='1' selected> Heating</option>";
        }
      page+="</select><br><br>";  

      page +="<h3>Set-Point Value: </h3>";
      page += "<input id='q' name='setpoint'  value='" + set_point + "' length=8 type='text'><br><br>";
      page +="<h3>Hysteresis: </h3>";
      page += "<input id='r' name='hysteresis'  value='" + hysteresis + "' length=8 type='text' ><br><br>";
      page +="<h3>Timer On / PID Cycling Time (Sec): </h3>";
      page += "<input id='s' name='timer_on'  value='" + timer_on + "' length=8 type='number' min='1' max='32767'><br><br>";
      page +="<h3>Timer Off / PID Action Time (Sec): </h3>";
      page += "<input id='t' name='timer_off'  value='" + timer_off + "' length=8 type='number'  min='0' max='32767' ><br><br>";
      page +="<h3>PID Proportional Action (%): </h3>";
      page += "<input id='u' name='pid_kp'  value='" + pid_kp + "' length=8 type='number' min='1' max='50' ><br><br>";
      page +="<h3>PID Integral Action: </h3>";
      page += "<input id='v' name='pid_int'  value='" + pid_int + "' length=8 type='number' min='1' max='50' ><br><br>";
      page +="<h3>PID Derivative Action: </h3>";
      page += "<input id='w' name='pid_der'  value='" + pid_der + "' length=8 type='number' min='1' max='50' ><br><br>";
      page +="<h3>PID Maximal Power (%): </h3>";
      page += "<input id='x' name='pid_pow'  value='" + pid_pow + "' length=8 type='number' min='10' max='100' ><br><br>";

      page += "<br><button type='submit'>Save</button></form><br>";
      page += back_to_outputs;
      page += HTTP_END;
      server_esp.send(200, "text/html", page);
}

void wifi_esp_class::Handle_output_value(void)
{
  String tempString;

        if(selected_output==1)
          {
           tempString = String(Ko.OUT1.value);
          }
        else if(selected_output==2)
          {
          tempString = String(Ko.OUT2.value);
          }
        else if(selected_output==3)
          {
            tempString = String(Ko.OUT3.value);
          }
        
        else if(selected_output==4)
          {
            tempString = String(Ko.OUT4.value);
          }
        
        else //if(selected_output==5)
          {
            tempString = String(Ko.OUT5.value);
          }
      server_esp.send(200, "text/plain", tempString);
}

void  wifi_esp_class::Get_outputs_parameters(void)
{
  int output_changed=0;
  String Label= server_esp.arg("label").substring(0,7);
  int control_function = server_esp.arg("function").toInt();
  float set_point=round(server_esp.arg("setpoint").toFloat()*10.0);
  float hysteresis=round(server_esp.arg("hysteresis").toFloat()*10.0);
  int control_signal = server_esp.arg("signal").toInt();
  int control_type=server_esp.arg("control_type").toInt();
  int timer_on=server_esp.arg("timer_on").toInt();
  int timer_off=server_esp.arg("timer_off").toInt();
  int pid_kp=server_esp.arg("pid_kp").toInt();
  int pid_int=server_esp.arg("pid_int").toInt();
  int pid_der=server_esp.arg("pid_der").toInt();
  int pid_pow=server_esp.arg("pid_pow").toInt();

  if(selected_output==1)
    {
    output_changed=0;
    if(Ko.OUT1.control_function!=control_function)
      {
      output_changed++;
      Ko.OUT1.control_function=control_function;
      EEPROM_MEM.Write_Int_EEPROM(OUT1_DIR+2,control_function);
      }
  
    if(Ko.OUT1.control_signal!=control_signal)
      {
      output_changed++;
      Ko.OUT1.control_signal=control_signal;
      EEPROM_MEM.Write_Int_EEPROM(OUT1_DIR+3,control_signal);
      }
    
    if(Ko.OUT1.set_point!=(int)set_point)
      {
      output_changed++;
      Ko.OUT1.set_point=set_point;
      EEPROM_MEM.Write_Int_EEPROM(OUT1_DIR+4,set_point);
      }
    
    if(Ko.OUT1.hysteresis!=(int)hysteresis)
      {
      output_changed++;
      Ko.OUT1.hysteresis=hysteresis;
      EEPROM_MEM.Write_Int_EEPROM(OUT1_DIR+5,hysteresis);
      }
    
    if(Ko.OUT1.control_type!=control_type)
      {
      output_changed++;
      Ko.OUT1.control_type=control_type;
      EEPROM_MEM.Write_Int_EEPROM(OUT1_DIR+6,control_type);
      }
    
    if(Ko.OUT1.set_time_ON!=timer_on)
      {
      output_changed++;
      Ko.OUT1.set_time_ON=timer_on;
      EEPROM_MEM.Write_Int_EEPROM(OUT1_DIR+7,timer_on);
      }

    if(Ko.OUT1.set_time_OFF!=timer_off)
      {
      output_changed++;
      Ko.OUT1.set_time_OFF=timer_off;
      EEPROM_MEM.Write_Int_EEPROM(OUT1_DIR+8,timer_off);
      }

   if(Ko.OUT1.Kp!=pid_kp)
      {
      output_changed++;
      Ko.OUT1.Kp=pid_kp;
      EEPROM_MEM.Write_Int_EEPROM(OUT1_DIR+9,pid_kp);
      }

   if(Ko.OUT1.Int!=pid_int)
      {
      output_changed++;
      Ko.OUT1.Int=pid_int;
      EEPROM_MEM.Write_Int_EEPROM(OUT1_DIR+10,pid_int);
      }  
    
    if(Ko.OUT1.Der!=pid_der)
      {
      output_changed++;
      Ko.OUT1.Der=pid_der;
      EEPROM_MEM.Write_Int_EEPROM(OUT1_DIR+11,pid_der);
      }
    
    if(Ko.OUT1.Pmax!=pid_pow)
      {
      output_changed++;
      Ko.OUT1.Pmax=pid_pow;
      EEPROM_MEM.Write_Int_EEPROM(OUT1_DIR+12,pid_pow);
      }
    
    if(Ko.OUT1.Label!=Label)
      {
      Ko.OUT1.Label=Label;
      EEPROM_MEM.Write_String_EEPROM(dir_label_output1,Label);
      }
    
    if (output_changed>0)
      { 
      Ko.OUT1.timer = 0;
      Ko.OUT1.phase = 0;
      Ko.OUT1.start_delay = 10;
      }
    }
  
  else if(selected_output==2)
    {
    output_changed=0;
    if(Ko.OUT2.control_function!=control_function)
      {
      output_changed++;
      Ko.OUT2.control_function=control_function;
      EEPROM_MEM.Write_Int_EEPROM(OUT2_DIR+2,control_function);
      }
  
    if(Ko.OUT2.control_signal!=control_signal)
      {
      output_changed++;
      Ko.OUT2.control_signal=control_signal;
      EEPROM_MEM.Write_Int_EEPROM(OUT2_DIR+3,control_signal);
      }
    
    if(Ko.OUT2.set_point!=(int)set_point)
      {
      output_changed++;
      Ko.OUT2.set_point=set_point;
      EEPROM_MEM.Write_Int_EEPROM(OUT2_DIR+4,set_point);
      }
    
    if(Ko.OUT2.hysteresis!=(int)hysteresis)
      {
      output_changed++;
      Ko.OUT2.hysteresis=hysteresis;
      EEPROM_MEM.Write_Int_EEPROM(OUT2_DIR+5,hysteresis);
      }
    
    if(Ko.OUT2.control_type!=control_type)
      {
      output_changed++;
      Ko.OUT2.control_type=control_type;
      EEPROM_MEM.Write_Int_EEPROM(OUT2_DIR+6,control_type);
      }
    
    if(Ko.OUT2.set_time_ON!=timer_on)
      {
      output_changed++;
      Ko.OUT2.set_time_ON=timer_on;
      EEPROM_MEM.Write_Int_EEPROM(OUT2_DIR+7,timer_on);
      }

    if(Ko.OUT2.set_time_OFF!=timer_off)
      {
      output_changed++;
      Ko.OUT2.set_time_OFF=timer_off;
      EEPROM_MEM.Write_Int_EEPROM(OUT2_DIR+8,timer_off);
      }

   if(Ko.OUT2.Kp!=pid_kp)
      {
      output_changed++;
      Ko.OUT2.Kp=pid_kp;
      EEPROM_MEM.Write_Int_EEPROM(OUT2_DIR+9,pid_kp);
      }

   if(Ko.OUT2.Int!=pid_int)
      {
      output_changed++;
      Ko.OUT2.Int=pid_int;
      EEPROM_MEM.Write_Int_EEPROM(OUT2_DIR+10,pid_int);
      }  
    
    if(Ko.OUT2.Der!=pid_der)
      {
      output_changed++;
      Ko.OUT2.Der=pid_der;
      EEPROM_MEM.Write_Int_EEPROM(OUT2_DIR+11,pid_der);
      }
    
    if(Ko.OUT2.Pmax!=pid_pow)
      {
      output_changed++;
      Ko.OUT2.Pmax=pid_pow;
      EEPROM_MEM.Write_Int_EEPROM(OUT2_DIR+12,pid_pow);
      }
    
    if(Ko.OUT2.Label!=Label)
      {
      Ko.OUT2.Label=Label;
      EEPROM_MEM.Write_String_EEPROM(dir_label_output2,Label);
      } 
   
   
    if (output_changed>0)
      { 
      Ko.OUT2.timer = 0;
      Ko.OUT2.phase = 0;
      Ko.OUT2.start_delay = 10;
      }
    }

else if(selected_output==3)
    {
    output_changed=0;
    if(Ko.OUT3.control_function!=control_function)
      {
      output_changed++;
      Ko.OUT3.control_function=control_function;
      EEPROM_MEM.Write_Int_EEPROM(OUT3_DIR+2,control_function);
      }
  
    if(Ko.OUT3.control_signal!=control_signal)
      {
      output_changed++;
      Ko.OUT3.control_signal=control_signal;
      EEPROM_MEM.Write_Int_EEPROM(OUT3_DIR+3,control_signal);
      }
    
    if(Ko.OUT3.set_point!=(int)set_point)
      {
      output_changed++;
      Ko.OUT3.set_point=set_point;
      EEPROM_MEM.Write_Int_EEPROM(OUT3_DIR+4,set_point);
      }
    
    if(Ko.OUT3.hysteresis!=(int)hysteresis)
      {
      output_changed++;
      Ko.OUT3.hysteresis=hysteresis;
      EEPROM_MEM.Write_Int_EEPROM(OUT3_DIR+5,hysteresis);
      }
    
    if(Ko.OUT3.control_type!=control_type)
      {
      output_changed++;
      Ko.OUT3.control_type=control_type;
      EEPROM_MEM.Write_Int_EEPROM(OUT3_DIR+6,control_type);
      }
    
    if(Ko.OUT3.set_time_ON!=timer_on)
      {
      output_changed++;
      Ko.OUT3.set_time_ON=timer_on;
      EEPROM_MEM.Write_Int_EEPROM(OUT3_DIR+7,timer_on);
      }

    if(Ko.OUT3.set_time_OFF!=timer_off)
      {
      output_changed++;
      Ko.OUT3.set_time_OFF=timer_off;
      EEPROM_MEM.Write_Int_EEPROM(OUT3_DIR+8,timer_off);
      }

   if(Ko.OUT3.Kp!=pid_kp)
      {
      output_changed++;
      Ko.OUT3.Kp=pid_kp;
      EEPROM_MEM.Write_Int_EEPROM(OUT3_DIR+9,pid_kp);
      }

   if(Ko.OUT3.Int!=pid_int)
      {
      output_changed++;
      Ko.OUT3.Int=pid_int;
      EEPROM_MEM.Write_Int_EEPROM(OUT3_DIR+10,pid_int);
      }  
    
    if(Ko.OUT3.Der!=pid_der)
      {
      output_changed++;
      Ko.OUT3.Der=pid_der;
      EEPROM_MEM.Write_Int_EEPROM(OUT3_DIR+11,pid_der);
      }
    
    if(Ko.OUT3.Pmax!=pid_pow)
      {
      output_changed++;
      Ko.OUT3.Pmax=pid_pow;
      EEPROM_MEM.Write_Int_EEPROM(OUT3_DIR+12,pid_pow);
      }
    
    if(Ko.OUT3.Label!=Label)
      {
      Ko.OUT3.Label=Label;
      EEPROM_MEM.Write_String_EEPROM(dir_label_output3,Label);
      } 
    
    if (output_changed>0)
      { 
      Ko.OUT3.timer = 0;
      Ko.OUT3.phase = 0;
      Ko.OUT3.start_delay = 10;
      }
    }

  else if(selected_output==4)
    {
    output_changed=0;
    if(Ko.OUT4.control_function!=control_function)
      {
      output_changed++;
      Ko.OUT4.control_function=control_function;
      EEPROM_MEM.Write_Int_EEPROM(OUT4_DIR+2,control_function);
      }
  
    if(Ko.OUT4.control_signal!=control_signal)
      {
      output_changed++;
      Ko.OUT4.control_signal=control_signal;
      EEPROM_MEM.Write_Int_EEPROM(OUT4_DIR+3,control_signal);
      }
    
    if(Ko.OUT4.set_point!=(int)set_point)
      {
      output_changed++;
      Ko.OUT4.set_point=set_point;
      EEPROM_MEM.Write_Int_EEPROM(OUT4_DIR+4,set_point);
      }
    
    if(Ko.OUT4.hysteresis!=(int)hysteresis)
      {
      output_changed++;
      Ko.OUT4.hysteresis=hysteresis;
      EEPROM_MEM.Write_Int_EEPROM(OUT4_DIR+5,hysteresis);
      }
    
    if(Ko.OUT4.control_type!=control_type)
      {
      output_changed++;
      Ko.OUT4.control_type=control_type;
      EEPROM_MEM.Write_Int_EEPROM(OUT4_DIR+6,control_type);
      }
    
    if(Ko.OUT4.set_time_ON!=timer_on)
      {
      output_changed++;
      Ko.OUT4.set_time_ON=timer_on;
      EEPROM_MEM.Write_Int_EEPROM(OUT4_DIR+7,timer_on);
      }

    if(Ko.OUT4.set_time_OFF!=timer_off)
      {
      output_changed++;
      Ko.OUT4.set_time_OFF=timer_off;
      EEPROM_MEM.Write_Int_EEPROM(OUT4_DIR+8,timer_off);
      }

    if(Ko.OUT4.Kp!=pid_kp)
      {
      output_changed++;
      Ko.OUT4.Kp=pid_kp;
      EEPROM_MEM.Write_Int_EEPROM(OUT4_DIR+9,pid_kp);
      }

    if(Ko.OUT4.Int!=pid_int)
      {
      output_changed++;
      Ko.OUT4.Int=pid_int;
      EEPROM_MEM.Write_Int_EEPROM(OUT4_DIR+10,pid_int);
      }  
    
    if(Ko.OUT4.Der!=pid_der)
      {
      output_changed++;
      Ko.OUT4.Der=pid_der;
      EEPROM_MEM.Write_Int_EEPROM(OUT4_DIR+11,pid_der);
      }
    
    if(Ko.OUT4.Pmax!=pid_pow)
      {
      output_changed++;
      Ko.OUT4.Pmax=pid_pow;
      EEPROM_MEM.Write_Int_EEPROM(OUT4_DIR+12,pid_pow);
      }
    
    if(Ko.OUT4.Label!=Label)
      {
      Ko.OUT4.Label=Label;
      EEPROM_MEM.Write_String_EEPROM(dir_label_output4,Label);
      } 
    
    if (output_changed>0)
      { 
      Ko.OUT4.timer = 0;
      Ko.OUT4.phase = 0;
      Ko.OUT4.start_delay = 10;
      }
    }

    else //if(selected_output==5)
    {
    output_changed=0;
    if(Ko.OUT5.control_function!=control_function)
      {
      output_changed++;
      Ko.OUT5.control_function=control_function;
      EEPROM_MEM.Write_Int_EEPROM(OUT5_DIR+2,control_function);
      }
  
    if(Ko.OUT5.control_signal!=control_signal)
      {
      output_changed++;
      Ko.OUT5.control_signal=control_signal;
      EEPROM_MEM.Write_Int_EEPROM(OUT5_DIR+3,control_signal);
      }
    
    if(Ko.OUT5.set_point!=(int)set_point)
      {
      output_changed++;
      Ko.OUT5.set_point=set_point;
      EEPROM_MEM.Write_Int_EEPROM(OUT5_DIR+4,set_point);
      }
    
    if(Ko.OUT5.hysteresis!=(int)hysteresis)
      {
      output_changed++;
      Ko.OUT5.hysteresis=hysteresis;
      EEPROM_MEM.Write_Int_EEPROM(OUT5_DIR+5,hysteresis);
      }
    
    if(Ko.OUT5.control_type!=control_type)
      {
      output_changed++;
      Ko.OUT5.control_type=control_type;
      EEPROM_MEM.Write_Int_EEPROM(OUT5_DIR+6,control_type);
      }
    
    if(Ko.OUT5.set_time_ON!=timer_on)
      {
      output_changed++;
      Ko.OUT5.set_time_ON=timer_on;
      EEPROM_MEM.Write_Int_EEPROM(OUT5_DIR+7,timer_on);
      }

    if(Ko.OUT5.set_time_OFF!=timer_off)
      {
      output_changed++;
      Ko.OUT5.set_time_OFF=timer_off;
      EEPROM_MEM.Write_Int_EEPROM(OUT5_DIR+8,timer_off);
      }

    if(Ko.OUT5.Kp!=pid_kp)
      {
      output_changed++;
      Ko.OUT5.Kp=pid_kp;
      EEPROM_MEM.Write_Int_EEPROM(OUT5_DIR+9,pid_kp);
      }

    if(Ko.OUT5.Int!=pid_int)
      {
      output_changed++;
      Ko.OUT5.Int=pid_int;
      EEPROM_MEM.Write_Int_EEPROM(OUT5_DIR+10,pid_int);
      }  
    
    if(Ko.OUT5.Der!=pid_der)
      {
      output_changed++;
      Ko.OUT5.Der=pid_der;
      EEPROM_MEM.Write_Int_EEPROM(OUT5_DIR+11,pid_der);
      }
    
    if(Ko.OUT5.Pmax!=pid_pow)
      {
      output_changed++;
      Ko.OUT5.Pmax=pid_pow;
      EEPROM_MEM.Write_Int_EEPROM(OUT5_DIR+12,pid_pow);
      }
    
    if(Ko.OUT5.Label!=Label)
      {
      Ko.OUT5.Label=Label;
      EEPROM_MEM.Write_String_EEPROM(dir_label_output5,Label);
      } 
    
    if (output_changed>0)
      { 
      Ko.OUT5.timer = 0;
      Ko.OUT5.phase = 0;
      Ko.OUT5.start_delay = 10;
      }
    }


    Select_Outputs();
}


//---------------------------------------------------------------------------------------------
void wifi_esp_class::send_info (void)
{
  String page = HTTP_HEAD1;

  page += "<h3>Station MAC: ";
  page += WiFi.macAddress();
  page += "</h3><br>";
  page += "<h3>Software Version 2.0";
  page += "</h3><br>";
  page += back_to_home;
  page += HTTP_END;
  server_esp.send(200, "text/html", page);
}

//---------------------------------------------------------------------------------------------------------------------
//When the form data is passed through GET mode, the special characters are replaced by UTF-8 code, this function replaces all UTF codes of special characters 
//by the corresponding special character, that is, for explample if it finds a %23 in the string it will replace it with a #.
String wifi_esp_class::Correct_Symbols(String a){ 
     a.replace("%C3%A1","á");
     a.replace("%C3%A9","é");
     a.replace("%C3%A","í");
     a.replace("%C3%B3","ó");
     a.replace("%C3%BA","ú");
     a.replace("%21","!");
     a.replace("%23","#");
     a.replace("%24","$");
     a.replace("%25","%");
     a.replace("%26","&");
     a.replace("%2F","/");
     a.replace("%28","(");
     a.replace("%29",")");
     a.replace("%3D","=");
     a.replace("%3F","?");
     a.replace("%27","'");
     a.replace("%40","@");
     a.replace("%C2%BF","¿");
     a.replace("%C2%A1","¡");
     a.replace("%C3%B1","ñ");
     a.replace("%C3%91","Ñ");
     a.replace("+"," ");
     a.replace("%2B","+");
     a.replace("%22","\"");
     return a;
 }

//---------------------------------------------------------------------------------------------------------------------
// Turn Off Wifi Module
void wifi_esp_class::Deep_Sleep_Wifi(void)
{
      
      WiFi.softAPdisconnect(true);                // Turn off Wifi Soft Mode
      delay(100); 
      WiFi.disconnect();                          // Disconnect from network                 
         
      WiFi.mode(WIFI_OFF);                        // Turn Off Wifi Module in ESP32
      delay (100);                                
      Ko.WIFI_MOD.on_off=0;                       // Flag indicates not Wifi Connection
}

//---------------------------------------------------------------------------------------------------------------------
uint8_t wifi_esp_class::SendPayloadWiFi(unsigned char *outData, const unsigned char len, unsigned char downlink)
{
    uint8_t result=0;
	  char hex_str[70];
    if(Init_WiFi_Connection())
      {
	    
      Comms.ASCII2Hex(outData, len, hex_str);
      Ubi.send_data_to_server(hex_str);

      if(downlink){ 
        RTC.GET_TIME_FROM_SERVER();               // Get Epoch from Ubiserver
        Rx_Data=Ubi.get_downlink_data();          // Get Downlink Data from Ubidots
        }
      result=1;
      }
  return result;
}


uint8_t wifi_esp_class::wait_rx_wifi(void)
{
  Ubi.Procces_Rx_Data(Rx_Data);                 // User can handle the downlink data frorm server

return 1;
}

/*
*Enter WiFi to AP mode

*/
uint8_t wifi_esp_class::enter_to_AP_Mode(void)
{
  Launch_Config_Portal();
  return 1;
}


/*
End to Wifi Ap Mode
*/
int wifi_esp_class::end_AP_Mode(void)
{
  Deep_Sleep_Wifi(); 
  return 1;
}


