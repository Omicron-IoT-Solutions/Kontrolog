/*
KONTROLOG-MINI LIBRARIES FOR ARDUINO
By Omicron IoT Solutions
	

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

#ifndef wifi_esp_h
#define	wifi_esp_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiMulti.h> 
#include <WebServer.h>
#include <HTTPClient.h>
#include "Config.h"
#include "RTC_clock.h"
#include "eeprom_esp.h"
#include "communications.h"

#define activate_debug   0          // Clear this bit if you dont want to see debug messages

//------------------------------------------------------------------------------------------------------------------------------------------------------
// HTML CODE FOR LAUNCH INTERNAL WEB PORTAL
//------------------------------------------------------------------------------------------------------------------------------------------------------
const String HTTP_HEAD1 =  "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/><title>KONTROLOG WEB PORTAL </title>"
"<style>.c{text-align: center;} div,option{padding:5px;font-size:1em;} input{padding:5px;font-size:1em;} h1{margin:0;font-size:1.2rem;text-transform:uppercase;font-weight:700} h2{margin:0;font-size:1.0rem;font-weight:700;}"
"select { background-color:rgb(255, 255, 255); color: black; border: 1px solid #333; border-radius: 1px; padding: 8px; cursor: pointer; font-size:1.0 rem;font-weight:700;width:100%}"
"h3{margin:0;font-size:0.7 rem;font-weight:400} input{width:95%;} body{text-align: center;font-family:verdana;} button{border:0;border-radius:0.3rem;background-color:#1fa3ec;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;}" 
".button_grey{border:0;border-radius:0.3rem;background-color:#2f4f4f;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;}" 
".q{float: right;width: 64px;text-align: right;} </style>"
"<script>function c(l){document.getElementById('s').value=l.innerText||l.textContent;document.getElementById('p').focus();}</script>"
"</head> <body><header><div class='col'><h1>KONTROLOG CONFIG. </h1><br/></div></header>"
"<div style='text-align:left;display:inline-block;min-width:260px;'>";

const String ppal= "<form action='scan' method='post'><button>Configure WiFi</button></form><br/>"
 "<form action='cloud' method='post'><button>Cloud Settings</button></form><br/>"
"<form action='sel_inputs' method='post'><button> Inputs Settings </button></form><br/>"
"<form action='sel_outputs' method='post'><button>Outputs Settings </button></form><br/>"
"<form action='info' method='post'><button>More Info </button></form><br/>";

const String HTTP_ITEM= "<div><a href='#p' onclick='c(this)'>{v}</a>&nbsp;<span class='q {i}'>{r}%</span></div>";

const String config_wifi_scan = "<form method='post' action='wifisave'><br>"
"<input id='s' name='ssid' length=32 placeholder='SSID'><br>"
"<input id='p' name='pass' length=64 type='text' placeholder='password'><br>"
"<br><button type='submit'>Save</button></form>"
"<div class=\"c\"><a href=\'scan'>Scan</a><br>";

const String Cloud_settings = "<form method='post' action='cloudsave'><br>"
"<h3> Server URL: </h3>"
"<input id='s' name='server' value='industrial.api.ubidots.com' length=64 placeholder='Server URL:'><br><br>"
"<h3> Token:</h3>"
"<input id='p' name='token' length=64 value='BBFF-' type='text' placeholder='Token:'><br><br>"
"<h3> Publication Interval (minutes): </h3>"
"<input id='q' name='tpu' value='10' length=64 type='number' placeholder='Interval(minutes):'><br><br>"
"<br><button type='submit'>Save</button></form><br>";

const String inputs_selector = 
"<h2> Select an option</h2><br>"
"<form action='input1' method='post'><button>Analog Input 1</button></form><br/>"
"<form action='input2' method='post'><button>Analog Input 2 </button></form><br/>"
"<form action='input3' method='post'><button>Analog Input 3</button></form><br/>"
"<form action='input4' method='post'><button>Analog Input 4 </button></form><br/>"
"<form action='input5' method='post'><button>Analog Input 5 </button></form><br/>"
"<form action='input6' method='post'><button>Digital Input 6 </button></form><br/>"
"<form action='input7' method='post'><button>Digital Input 7 </button></form><br/>"
"<form action='input8' method='post'><button>Digital Input 8 </button></form><br/>";

const String outputs_selector = 
"<h2> Select an option</h2><br>"
"<form action='output1' method='post'><button>Relay Output 1</button></form><br/>"
"<form action='output2' method='post'><button>Relay Output 2 </button></form><br/>"
"<form action='output3' method='post'><button>Relay Output 3</button></form><br/>"
"<form action='output4' method='post'><button>Relay Output 4</button></form><br/>"
"<form action='output5' method='post'><button>Relay Output 5</button></form><br/>";

const String no_wifi_save = "<div><h3>Credentials NOT Saved <br/> Invalid SSID</h3><br/>";
const String wifi_save = "<div><h3>Trying to connect your Device to network...<br> Wait for 30 seconds and press to view if <br> WiFi connection was correct</h3><br/>";
const String back_to_home = "<form action='/' method='post'><button class='button_grey'> Back to Home </button></form>";    //ppal
const String Test_Config = "<form action='test' method='post'><button> WiFi Results </button></form>";
const String back_to_inputs = "<form action='/sel_inputs' method='post'><button class='button_grey'> Back to Inputs </button></form>";    //ppal
const String back_to_outputs = "<form action='/sel_outputs' method='post'><button class='button_grey'> Back to Outputs </button></form>";    //ppal


const String HTTP_END =  "<div style='text-align:center;'><h2>Omicron IoT Solutions</h2><br/></div> </div></body></html>";



//------------------------------------------------------------------------------------------------------------------------------------------------------
const char cert_Sectigo_ECC_Domain_Validation_Secure_Server_CA [] PROGMEM = R"CERT(
-----BEGIN CERTIFICATE-----
MIIDqDCCAy6gAwIBAgIRAPNkTmtuAFAjfglGvXvh9R0wCgYIKoZIzj0EAwMwgYgx
CzAJBgNVBAYTAlVTMRMwEQYDVQQIEwpOZXcgSmVyc2V5MRQwEgYDVQQHEwtKZXJz
ZXkgQ2l0eTEeMBwGA1UEChMVVGhlIFVTRVJUUlVTVCBOZXR3b3JrMS4wLAYDVQQD
EyVVU0VSVHJ1c3QgRUNDIENlcnRpZmljYXRpb24gQXV0aG9yaXR5MB4XDTE4MTEw
MjAwMDAwMFoXDTMwMTIzMTIzNTk1OVowgY8xCzAJBgNVBAYTAkdCMRswGQYDVQQI
ExJHcmVhdGVyIE1hbmNoZXN0ZXIxEDAOBgNVBAcTB1NhbGZvcmQxGDAWBgNVBAoT
D1NlY3RpZ28gTGltaXRlZDE3MDUGA1UEAxMuU2VjdGlnbyBFQ0MgRG9tYWluIFZh
bGlkYXRpb24gU2VjdXJlIFNlcnZlciBDQTBZMBMGByqGSM49AgEGCCqGSM49AwEH
A0IABHkYk8qfbZ5sVwAjBTcLXw9YWsTef1Wj6R7W2SUKiKAgSh16TwUwimNJE4xk
IQeV/To14UrOkPAY9z2vaKb71EijggFuMIIBajAfBgNVHSMEGDAWgBQ64QmG1M8Z
wpZ2dEl23OA1xmNjmjAdBgNVHQ4EFgQU9oUKOxGG4QR9DqoLLNLuzGR7e64wDgYD
VR0PAQH/BAQDAgGGMBIGA1UdEwEB/wQIMAYBAf8CAQAwHQYDVR0lBBYwFAYIKwYB
BQUHAwEGCCsGAQUFBwMCMBsGA1UdIAQUMBIwBgYEVR0gADAIBgZngQwBAgEwUAYD
VR0fBEkwRzBFoEOgQYY/aHR0cDovL2NybC51c2VydHJ1c3QuY29tL1VTRVJUcnVz
dEVDQ0NlcnRpZmljYXRpb25BdXRob3JpdHkuY3JsMHYGCCsGAQUFBwEBBGowaDA/
BggrBgEFBQcwAoYzaHR0cDovL2NydC51c2VydHJ1c3QuY29tL1VTRVJUcnVzdEVD
Q0FkZFRydXN0Q0EuY3J0MCUGCCsGAQUFBzABhhlodHRwOi8vb2NzcC51c2VydHJ1
c3QuY29tMAoGCCqGSM49BAMDA2gAMGUCMEvnx3FcsVwJbZpCYF9z6fDWJtS1UVRs
cS0chWBNKPFNpvDKdrdKRe+oAkr2jU+ubgIxAODheSr2XhcA7oz9HmedGdMhlrd9
4ToKFbZl+/OnFFzqnvOhcjHvClECEQcKmc8fmA==
-----END CERTIFICATE-----
)CERT";
//------------------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------------------------------
// Data Stored for Wifi Configuration in EEPROM

const unsigned int
dir_base= 0x1000,                   // Base address for stored wifi configurations into EEPROM
dir_label_input1=dir_base+0,        // Inputs Labels
dir_label_input2=dir_base+8,        // 
dir_label_input3=dir_base+16,
dir_label_input4=dir_base+24,
dir_label_input5=dir_base+32,
dir_label_input6=dir_base+40,
dir_label_input7=dir_base+48,
dir_label_input8=dir_base+56,

dir_label_output1=dir_base+64,        // Outputs Labels
dir_label_output2=dir_base+72,        // 
dir_label_output3=dir_base+80,
dir_label_output4=dir_base+88,
dir_label_output5=dir_base+96,


add_count_config=dir_base+108,       // Stored wifi configuration counter
dir_config1=dir_base+110,            // Is ssid 1 configured?
add_ssid1=dir_base+112,              // ssid 1
dir_pass1=dir_base+144,              // pass 1

dir_config2=dir_base+180,           // Is ssid 2 configured?
add_ssid2=dir_base+182,             // ssid 2
dir_pass2=dir_base+214,             // pass 2

dir_config3=dir_base+250,           // Is ssid 2 configured?
add_ssid3=dir_base+252,             // ssid 3
dir_pass3=dir_base+284,             // pass 3


dir_url_server=dir_base+320,         // URL Server
dir_token=dir_base+360;              // Ubi Token 

class wifi_esp_class {

public:
    // Network Parameters
    char  ssid [32];                     // Network SSID 
    char  pass[32];                      // your network password (use for WPA, or use as key for WEP)
  
    uint8_t Init_WiFi_Connection(void);
    void Launch_Config_Portal(void);
    void Deep_Sleep_Wifi(void);
    void Portal_Manager(void);
    void config_portal_end(void);
    uint8_t SendPayloadWiFi(unsigned char *outData, const unsigned char len, unsigned char downlink);
    uint8_t enter_to_AP_Mode(void);
    int end_AP_Mode(void);
    uint8_t wait_rx_wifi(void);

private:

    WiFiMulti wifiMulti1;
    WiFiClient WiFi_client;
    String Current_Value;

    char  server_default[80]= "parse.ubidots.com";       // Ubidots server
    int   Port_default = 80;                             // Default port
    char  ssid_default [30] =  "YOUR_SSID";              // Replace with your Default SSID
    char  pass_default [30] =  "YOUR_DEFAULT_PASSWORD";  // Replace with your default Password
    int8_t selected_input=3;
    int8_t selected_output=1;
    

// Variables
   
    int  WiFi_Config_Response=0;
    String Last_IP = "0.0.0.0";
    String Rx_Data;

    int  get_WiFi_configuration(void);
    uint8_t get_stored_network (int,  int, int);
    uint8_t get_stored_position(void);
    String Correct_Symbols(String);
    void send_info (void);
    void Config_Response (void);
    void Launch_cloud_settings (void);
    void Get_cloud_settings(void);
    
    void Select_Inputs (void);
    void Capture_Inputs_Params(int);
    void Set_Input1(void);  
    void Set_Input2(void);  
    void Set_Input3(void);  
    void Set_Input4(void);
    void Set_Input5(void);
    void Set_Input6(void);  
    void Set_Input7(void);  
    void Set_Input8(void);    
    void Handle_input_value(void);
    void Get_inputs_parameters(void); 

    void Select_Outputs (void);
    void Capture_Outputs_Params(int);
    void Set_Output1(void);  
    void Set_Output2(void);  
    void Set_Output3(void);  
    void Set_Output4(void);  
    void Set_Output5(void);  
    void Handle_output_value(void);
    void Get_outputs_parameters(void); 


    void wifi_conf1();
    int getRSSIasQuality(int);
    void handle_wifi_config_scan (void);
};

class ubidots_class {

public:
int8_t send_data_to_server(String);
String get_downlink_data(void);
char Procces_Rx_Data (String);
float parsetofloat(String,int, unsigned int);
uint32_t get_utc();


private:
unsigned int hexToDec(String);
uint8_t hexAsciiToDec(char);
int send_data_to_ubidots(JsonDocument);
int send_data_to_NodeRed(JsonDocument, uint32_t);


};

extern wifi_esp_class Wi;
extern ubidots_class Ubi;
#endif