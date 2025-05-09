![Logo-Omicron-Vector](https://github.com/Omicron-IoT-Solutions/Kontrolog/assets/141452095/1d867a2d-2f0b-40eb-bbb9-566f306320ba)
# Kontrolog Max
## General
This repository contains instructions, manuals, schematics, packages, and examples to program your Kontrolog Max device for the different functions that best suit your application.

## Description
![DSC_0153](https://github.com/Omicron-IoT-Solutions/Kontrolog/assets/141452095/87452571-8b00-4312-8a06-4ba1d7e01cff)
The Kontrolog Max device is a programmable controller for IoT (Internet of Things) that incorporates the powerful ESP32 processing technology, designed for remote and real-time, control and monitoring of different processes with high security and precision requirements. Adapted to your application, the device can be easily used after installation. It houses electronic components such as a microcontroller (CPU) and the memory, and other hardware elements such as: voltage sources, power outputs, and the ports needed to host the sensors and the IoT communication module. The microcontroller contains the embedded software, which performs the tasks of: reading the sensors connected to its ports, obtaining their information, creating the monitoring packets or frames, configuring and activating the communication module, and sending the data at intervals that can be variable depending on the programmed publication times, generating alerts, and performing control tasks. In addition, the software is available in open source C++ language, which allows you to have two programming modes, which we present in two branches: 

- [No-Code (Corregir enlace)](https://github.com/Omicron-IoT-Solutions/Kontrolog-Mini/tree/No-Code)

- [Full-Code (Corregir enlace)](https://github.com/Omicron-IoT-Solutions/Kontrolog-Mini/tree/Full-Code)

## Features
The main technical features of this model of the Kontrolog Max device are listed below.

- Five (5) inputs for sensors which can be configured as:
  - Analog input 4-20mA.
  - Analog input 0-10V.
  - Analog temperature input for the NTC 10K – 3950 thermistor.
  - Digital input 1/0.
  - Input for analog ambient temperature and humidity sensors.
  - Digital pulse counter.
  - Frequency meter (Input 5 only, up to 20kHz).

- Four (4) GPIO ports that the user has the freedom to program as inputs or outputs, or use them to read other sensors or with communication protocols such as I2C, SPI, UART, among others.

- 1 input for battery 6-12VDC, also DC supply voltage is measured.

- Power supply 110-220VAC input, also AC supply voltage is measured.

- One (1) input for the current transformer to measure AC current in the following ranges:
  - 0-30A.
  - 0-50A.
  - 0-100A.

- One Modbus RTU (RS-485) input port operating as a master on the network.

- Alarms:
  - Built-in visual and audible alarms, as well as remotely visible alarms on the mobile or WEB application.
  - Integration to the platform for external alarms by SMS, voice message, email, and Telegram messaging service, etc.

- Five (5) control outputs: (queda pendiente por definir.) 
  - For the Kontrolog 9.2: Up to 5 output relays, of which two can handle up to 12A@120VAC and three up to 3A@120VAC
  - For the Kontrolog 9.3: Up to 4 output relays, of which two can handle up to 12A@120VAC and two up to 3A@120VAC; and a fifth 4-20 mA analog output.

  - One (1) USB type C port that allows communication with the programming and simulation environment, and also serves as a 5V power supply for the Kontrolog Max.
    
- To perform control tasks, such as:
  - Control by remote commands sent from the platform. 
  - ON/OFF control with hysteresis for cooling or heating. 
  - Timer.
  - Output follows associated input sensor.
  - Remote alarm.
  - Event counter.
  - PID control. 

- HMI screen: (Human Machine Interface); 4.3" full-color LCD touch screen for programming and data visualization.

- Communication port, where a dual communication module with protocols for LoRaWAN™/Sigfox for the USA/EU/Latam/Australia zones or a WiFi communication module can be installed.
  
The Kontrolog Max is powered by a two-wire power cable, connecting its AC1 and AC2 inputs to the 110-220VAC, 50-60Hz lines. It can also be powered by a 6 or 12V battery. The system is delivered with the wireless communication modules ordered. According to the product philosophy, all the above-mentioned add-ons can be prescribed, and remote data transmission can be done by different popular wireless technologies. Customers are also offered memberships for the use of a platform for remote monitoring and configuration, supported by the manufacturer.