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


#include "wifi_esp.h"

// Variables 

WiFiClient WiFi_client;         // Constructor for Wifi Client Services
HTTPClient http2;
extern wifi_esp_class Wi;
 

// Ubidots Parser for Uplink and Downlink
String Ubiserver;              // Free Ubidots Server
String Ubi_token;              // Your Ubitoken
String NodeRedServer = "http://165.232.144.120:1880/Kontrolog";       // Omicron

/*---------------------------------------------------------------------------------------------------------------------
//  ---- Send Data to Ubidots Server

// This method makes a HTTP connection to Ubidots server:
// Create and Send .json Object with the data of the INPUTS and OUPUTS from Communications Class (Prepare_Data_To_Send) 

// Inputs  String with  .HEX  Data to send
// Result:

// Result:
  String with rx data

//---------------------------------------------------------------------------------------------------------------------
*/
int8_t ubidots_class::send_data_to_server(String Data_to_Send) 
{
    int8_t result=0;
    JsonDocument  Data_json;

// Get RSSI
    int rssi = WiFi.RSSI();
    Data_json["rssi"]["value"]=rssi;
    Ko.WIFI_MOD.rssi=rssi;
  
    //Get Server URL & Token
    Ubiserver=EEPROM_MEM.Read_String_EEPROM(dir_url_server);
    if(Ubiserver=="")
      return 0;

    Ubiserver= "http://" + Ubiserver + "/api/v1.6/devices/kontrolog-";
    Ubi_token=EEPROM_MEM.Read_String_EEPROM(dir_token);


    /*Serial.printf("Servidor: %s\r\n",Ubiserver.c_str());
    Serial.printf("Token: %s\r\n",Ubi_token.c_str());*/


// Get timeStamp from the Data String   
    String Data_time =  Data_to_Send.substring(24,32);
    int32_t timeStamp =hexToDec(Data_time);

    
    const char* Label1=Ko.IN1.Label.c_str();
    const char* Label2=Ko.IN2.Label.c_str();
    const char* Label3=Ko.IN3.Label.c_str();
    const char* Label4=Ko.IN4.Label.c_str();
    const char* Label5=Ko.IN5.Label.c_str();
    const char* Label6=Ko.IN6.Label.c_str();
    const char* Label7=Ko.IN7.Label.c_str();
    const char* Label8=Ko.IN8.Label.c_str();
    

//  Create .js on Object
    Data_json[Label1]["value"]= parsetofloat(Data_to_Send.substring(1,4),Ko.IN1.resolution,2048);
    Data_json[Label2]["value"]= parsetofloat(Data_to_Send.substring(4,7),Ko.IN2.resolution,2048);
    Data_json[Label3]["value"]= parsetofloat(Data_to_Send.substring(7,10),Ko.IN3.resolution,2048);
    Data_json[Label4]["value"]= parsetofloat(Data_to_Send.substring(10,13),Ko.IN4.resolution,2048);
    Data_json[Label5]["value"]= parsetofloat(Data_to_Send.substring(13,16),Ko.IN5.resolution,2048);
    Data_json["VDC"]["value"] = parsetofloat(Data_to_Send.substring(16,18),Ko.VDC.resolution,2048);
    Data_json[Label6]["value"]= parsetofloat(Data_to_Send.substring(36,40),Ko.IN6.resolution,32768);
    Data_json[Label7]["value"]= parsetofloat(Data_to_Send.substring(40,44),Ko.IN7.resolution,32768);
    Data_json[Label8]["value"]= parsetofloat(Data_to_Send.substring(44,48),Ko.IN8.resolution,32768);
    Data_json["VAC"]["value"] = parsetofloat(Data_to_Send.substring(18,20),0,2048);
    int current=hexToDec(Data_to_Send.substring(20,23))&0xFFC/40;
    // The bits that do not correspond to the variable are eliminated with &0ffc, and it must be divided by 4 for the shifting and 10 for the scaling.
    Data_json["IAC"]["value"] = current;
     
    int io = hexToDec(Data_to_Send.substring(22,24));
    
    int R1 = (io&0x02)/2;     //Output 1
    Data_json["OUT1"]["value"] = R1;
    
    int R2 = (io&0x04)/4;     //Output 2
    Data_json["OUT2"]["value"] = R2;
    
    int R3 = (io&0x08)/8;     //Output 3
    Data_json["OUT3"]["value"] = R3;

    int R4 = (io&0x10)/0x10;     //Output 4
    Data_json["OUT4"]["value"] = R4;

    int R5 = (io&0x20)/0x20;     //Output 5
    Data_json["OUT5"]["value"] = R5;
    
    io = hexToDec(Data_to_Send.substring(0,1));
    Data_json["Alarm_Type"]["value"] = io&0x0F;

    if (timeStamp>1704067200)     // Is Timestamp Correct?    (Compare with Jan 1, 2024 00:00)
      {
      uint64_t time64=timeStamp;
      time64*=1000;
      Data_json[Label1]["timestamp"]=time64;
      Data_json[Label2]["timestamp"]=time64;
      Data_json[Label3]["timestamp"]=time64;
      Data_json[Label4]["timestamp"]=time64;
      Data_json[Label5]["timestamp"]=time64;
      Data_json[Label6]["timestamp"]=time64;
      Data_json[Label7]["timestamp"]=time64;
      Data_json[Label8]["timestamp"]=time64;
      Data_json["VDC"]["timestamp"]=time64;
      Data_json["Alarm_Type"]["timestamp"]=time64;
      Data_json["OUT1"]["timestamp"]=time64;
      Data_json["OUT2"]["timestamp"]=time64;
      Data_json["OUT3"]["timestamp"]=time64;
      Data_json["OUT4"]["timestamp"]=time64;
      Data_json["OUT5"]["timestamp"]=time64;
      Data_json["VAC"]["timestamp"]=time64;
      Data_json["IAC"]["timestamp"]=time64;
      }

    
     //result=send_data_to_NodeRed(Data_json, timeStamp);
     result=send_data_to_ubidots(Data_json);
     
     return result;
}

int ubidots_class::send_data_to_ubidots(JsonDocument  Data_json)  
{
  int result=0;
  String serverPath = Ubiserver + Ko.WIFI_MOD.MAC;
  if(http2.begin(WiFi_client, serverPath))
    {
    http2.addHeader("Content-Type", "application/json");
    http2.addHeader("X-Auth-Token", Ubi_token);

    String Json="";
    serializeJson(Data_json, Json);
    int httpCode=http2.POST(Json);
    Serial.printf("http code: %d\r\n",httpCode);
    if (httpCode == HTTP_CODE_OK)
      {
       String payload = http2.getString();
       result= httpCode;
      }
    else 
      result= httpCode;
    }
  else
    {
    result = -1;
    }
  http2.end();
  return result;
}

int ubidots_class::send_data_to_NodeRed(JsonDocument  Data_json, uint32_t epoch)  
{
  int result=0;
  Data_json["TimeStamp"]=epoch;
  Data_json["ID"]=Ko.WIFI_MOD.MAC;
  if(http2.begin(WiFi_client, NodeRedServer))
    {
    http2.addHeader("Content-Type", "application/json");
    //http2.setAuthorization("omicron", "Mariana#081012");
    String Json="";
    serializeJson(Data_json, Json);
    int httpCode=http2.POST(Json);
    Serial.printf("http code: %d\r\n",httpCode);
    if (httpCode == HTTP_CODE_OK)
      {
       String payload = http2.getString();
       result= httpCode;
      }
    else 
      result= httpCode;
    }
  else
    {
    result = -1;
    }
  http2.end();
  return result;
}

  /* ------------------------------
//  ---- Receive data from  Ubidots Server 

// This method makes a HTTP connection to Ubidots server:

// Inputs :
   Read the last values of variable "downlink" From Ubidots Server
   Use the Time Epoch from the last send data

// Result:
  String with rx data
  // ------------------------------
  */
String ubidots_class::get_downlink_data(void)
{
    String URL_Downlink;
    String rx_line="";

    URL_Downlink = Ubiserver + Ko.WIFI_MOD.MAC + "/downlink/values/?start="+String(Ko.RTC.time_stamp-Ko.RTC.time_zone*3600-Ko.CONFIG.DT.TPU*60)+"000";
    if(http2.begin(WiFi_client,URL_Downlink))
      {
      http2.addHeader("X-Auth-Token", Ubi_token);
      int httpCode = http2.GET();
      if (httpCode > 0) 
          {
          if (httpCode == HTTP_CODE_OK) 
              {
              rx_line = http2.getString();
              if(activate_debug)
                Serial.println(rx_line);  
              }
          }
      }
    http2.end();
    return rx_line;
  }

//---------------------------------------------------------------------------------------------------------------------
// Function: 
// User manage the Ubidots server response
//---------------------------------------------------------------------------------------------------------------------

char ubidots_class::Procces_Rx_Data(String Data)
{

return 1;
}



// Converting String Hex to Decimal:

// NOTE: This function can handle a positive hex value from 0 - 65,535 (a four digit hex string).
// For larger/longer values, change "unsigned int" to "long" in both places.


unsigned int ubidots_class::hexToDec(String hexString) {
  
  unsigned int decimalValue = 0;
  for (int i = 0; i < hexString.length(); i++) {
      char digit = hexString[i];
      int value;
      
      if (digit >= '0' && digit <= '9') {
          value = digit - '0';
      } else if (digit >= 'A' && digit <= 'F') {
          value = digit - 'A' + 10;
      } else if (digit >= 'a' && digit <= 'f') {
          value = digit - 'a' + 10;
      } else {
          continue; // No valid character
      }

      decimalValue = (decimalValue * 16) + value;
  }
  return decimalValue;

}

// Converting  Ascii Hex Char to Decimal (0 to 15):
uint8_t ubidots_class::hexAsciiToDec(char Data) {

uint8_t decValue = 0;
    if (Data >= 48 && Data <= 57) Data = map(Data, 48, 57, 0, 9);
    else if (Data >= 65 && Data <= 70) Data = map(Data, 65, 70, 10, 15);
    else if (Data >= 97 && Data <= 102) Data = map(Data, 97, 102, 10, 15);
    else
    Data = 15;
    
    Data = constrain(Data, 0, 15);
    
    return Data;
    
    }

float ubidots_class::parsetofloat(String hexString, int pow, unsigned int limit)
{   
     float input = hexToDec(hexString);           // The variables in KONTROLOG are stored in 16 Bits
     if(limit==32768)                            
      {
        if(input>=32768)                          // if the value is grater than 32768 indicate that It is negative                    
        input-=65536;                             // if it´s negative,  rest from 65536 = 2^16
      }
    else                                           // Analogs Inputs Are Limit to 12 bits in KONTROLOG´s communication protocol
      {
      if(input>=2048)                             // if the Input is limited to 2047 and the value is grater than 2048 indicate that It is negative                    
      input-=4096;                                // if it´s negative,  rest from 4096 = 2^12
      }
     if(pow==1)
        return input/10.0;
     else if(pow==2)
        return input/100.0;
    else
      return input;
}

// GET UTC Epoch from Ubidots Server
uint32_t ubidots_class::get_utc() {

   uint32_t New_epoch=0;
   String  url = "http://industrial.api.ubidots.com/api/v1.6/utils/utcnow/";
   http2.begin(WiFi_client, url);
   int httpCode = http2.GET();
   if (httpCode > 0) 
          {
          if (httpCode == HTTP_CODE_OK) 
              {
              String rx_line = http2.getString();
              char epocharray[12];
              rx_line.toCharArray(epocharray,11);
              New_epoch=atol(epocharray);
              }
          }
    http2.end();
    return New_epoch;
}