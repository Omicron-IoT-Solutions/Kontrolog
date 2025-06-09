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


#include "TLA2528.h"
#include "TLA2528_c.h"
#include <Wire.h>


int TLA2528Class::begin()
{
  // Start I2C communication

    MyI2C_1.begin(SDA1_PIN,SCL1_PIN,1000000); 
    Serial.println("INIT TLA228");
  
  // Set Analog and Digital Output Pins for  tla2528
    
    reset(tla2528_i2c_address_inputs);                    // Reset TLA228
    pinModeIO(tla2528_i2c_address_inputs,AN1,ANALOG);      
    pinModeIO(tla2528_i2c_address_inputs,AN2,ANALOG);
    pinModeIO(tla2528_i2c_address_inputs,AN3,ANALOG);
    pinModeIO(tla2528_i2c_address_inputs,AN4,ANALOG);
    pinModeIO(tla2528_i2c_address_inputs,AN5,ANALOG);
    pinModeIO(tla2528_i2c_address_inputs,ANVDC,ANALOG);
    pinModeIO(tla2528_i2c_address_inputs,DIVAC,INPUT);
    pinModeIO(tla2528_i2c_address_inputs,ANIAC,ANALOG);
    
    reset(tla2528_i2c_address_outputs); 
    pinModeIO(tla2528_i2c_address_outputs,REL1,OUTPUT);     
    pinModeIO(tla2528_i2c_address_outputs,REL2,OUTPUT);  
    pinModeIO(tla2528_i2c_address_outputs,REL3,OUTPUT);   
    pinModeIO(tla2528_i2c_address_outputs,REL4,OUTPUT);   
    pinModeIO(tla2528_i2c_address_outputs,REL5,OUTPUT);   

    return 1;
}

void TLA2528Class::end()
{
    MyI2C_1.end();
}

void TLA2528Class::Read_registers_Status(uint8_t i2caddress)
{
    Serial.println("-------- TLA2528 --------");
    Serial.println(readRegister(i2caddress,SYSTEM_STATUS_ADDRESS));
    Serial.println(readRegister(i2caddress,GENERAL_CFG_ADDRESS));
    Serial.println(readRegister(i2caddress,DATA_CFG_ADDRESS));
    Serial.println(readRegister(i2caddress,OSR_CFG_ADDRESS));
    Serial.println(readRegister(i2caddress,OPMODE_CFG_ADDRESS));
    Serial.println(readRegister(i2caddress,PIN_CFG_ADDRESS));
    Serial.println(readRegister(i2caddress,GPIO_CFG_ADDRESS));
    Serial.println(readRegister(i2caddress,GPO_DRIVE_CFG_ADDRESS));
    Serial.println(readRegister(i2caddress,GPO_VALUE_ADDRESS));
    Serial.println(readRegister(i2caddress,GPI_VALUE_ADDRESS));
    Serial.println(readRegister(i2caddress,SEQUENCE_CFG_ADDRESS));
    Serial.println(readRegister(i2caddress,MANUAL_CH_SEL_ADDRESS));
}

int TLA2528Class::readRegister(uint8_t i2caddress,uint8_t address)
{
    uint8_t value;

    if (readRegisters(i2caddress,address, &value, sizeof(value)) != 1) {
        return -1;
    }

    return value;
}

int TLA2528Class::readRegisters(uint8_t i2caddress,uint8_t address, uint8_t* data, size_t length)
{
    MyI2C_1.beginTransmission(i2caddress);  // Start transmission to device
    MyI2C_1.write(0b00010000);  // Read Register Command
    MyI2C_1.write(address);     // Register Address
    MyI2C_1.endTransmission();  // End transmission
    MyI2C_1.requestFrom(i2caddress,length);  // Request data from device
    if (MyI2C_1.available()) {
        *data=MyI2C_1.read();   // Read received data
        return 1;
    }
    
return 0;
}

int TLA2528Class::readAnalogInput(uint8_t i2caddress,uint8_t input, uint8_t* data)
{
    MyI2C_1.beginTransmission(i2caddress);    // Start transmission to device
    MyI2C_1.write(0b00001000);                  // Send Write Command
    MyI2C_1.write(MANUAL_CH_SEL_ADDRESS);       // Dir Sel channel
    MyI2C_1.write(input);                       // Set Channel        
    MyI2C_1.endTransmission();                  // End transmission

    uint8_t bytesReceived = MyI2C_1.requestFrom(i2caddress,sizeof(data));  // Request data from device
    if ((bool)bytesReceived)                    //If received more than zero bytes
      {  
      MyI2C_1.readBytes(data, bytesReceived);
      return 1;
      }
return 0;
}

void TLA2528Class::digitalWriteIO(uint8_t i2caddress,uint8_t pin, uint8_t val)
{
    if (pin >= 0 && pin <= 7)
    {
        if (pin == 0)
        {
            //Pin 0 is used for alarm and needs to be specialtreated. Inverted for correct behaviour
            if (val)
            {
                resetBit(i2caddress,ALERT_PIN_CFG, 1 << pin);
            }
            else
            {
                setBit(i2caddress,ALERT_PIN_CFG, 1 << pin);
            }

        }
        else
        {
            if (val)
            {
                setBit(i2caddress,GPO_VALUE_ADDRESS, 1 << pin);
            }
            else
            {
                resetBit(i2caddress,GPO_VALUE_ADDRESS, 1 << pin);
            }
        }
    }
}

uint8_t TLA2528Class::digitalReadIO(uint8_t i2caddress,uint8_t pin)
{
    if (pin >= 0 && pin < 8)
    {
        int result = readRegister(i2caddress,GPI_VALUE_ADDRESS);

        return (result >> pin) & 0x1;
    }
    return uint8_t();
}

int TLA2528Class::analogReadIO(uint8_t i2caddress,uint8_t pin)
{
    uint8_t value[3];
    readAnalogInput(i2caddress,pin, (uint8_t*)value);
    return (value[0] << 4) | (value[1] >> 4);
}

void TLA2528Class::reset(uint8_t i2caddress)
{
    setBit(i2caddress,GENERAL_CFG_ADDRESS,1 << RST_MASK);
}

void TLA2528Class::pinModeIO(uint8_t i2caddress,uint8_t pin, uint8_t mode)
{
    if (pin < 8)
    {
        switch (mode)
        {
        case INPUT:
            setBit(i2caddress,PIN_CFG_ADDRESS, 1 << pin);
            resetBit(i2caddress,GPIO_CFG_ADDRESS, 1 << pin);
            break;
        case OUTPUT:
            setBit(i2caddress,PIN_CFG_ADDRESS, 1 << pin);
            setBit(i2caddress,GPIO_CFG_ADDRESS, 1 << pin);
            setBit(i2caddress,GPO_DRIVE_CFG_ADDRESS, 1 << pin);
            break;
        case ANALOG:
            resetBit(i2caddress,PIN_CFG_ADDRESS, 1 << pin);
            resetBit(i2caddress,GPIO_CFG_ADDRESS, 1 << pin);
            break;
        }
    }
}

int TLA2528Class::writeRegister(uint8_t i2caddress,uint8_t address, uint8_t value)
{
    MyI2C_1.beginTransmission(i2caddress);
    MyI2C_1.write(0b00001000);  // Write Command
    MyI2C_1.write(address);     // Register Addres
    MyI2C_1.write(value);       // Set Value
    MyI2C_1.endTransmission();  // End transmission
    return 1;
}

int TLA2528Class::setBit(uint8_t i2caddress,uint8_t address, uint8_t value)
{
    MyI2C_1.beginTransmission(i2caddress);
    MyI2C_1.write(0b00011000);  // Set Bit Command
    MyI2C_1.write(address);     // Register Addres
    MyI2C_1.write(value);       // Set Value
    MyI2C_1.endTransmission();  // End transmission
    return 1;
}

int TLA2528Class::resetBit(uint8_t i2caddress,uint8_t address, uint8_t value)
{
    MyI2C_1.beginTransmission(i2caddress);
    MyI2C_1.write(0b00100000);  // Reset Bit Command
    MyI2C_1.write(address);     // Register Addres
    MyI2C_1.write(value);       // Set Value
    MyI2C_1.endTransmission();  // End transmission
    return 1;
}
