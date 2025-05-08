![Logo-Omicron-Vector](https://github.com/Omicron-IoT-Solutions/Kontrolog/assets/141452095/1d867a2d-2f0b-40eb-bbb9-566f306320ba)
# Kontrolog Mini in No-Code mode
## General
This branch contains the Firmaware code (default programming of the device) for the Kontrolog Mini to be programmed locally through the graphical HMI interface provided, the device's captive portal, or remotely through the IoT Web platform, as well as examples and guided tutorials for you to learn how to program in No-Code mode your Kontrolog Mini.

## Flashing Firmware to the Kontrolog Mini
![bitmap3](https://github.com/user-attachments/assets/53b01053-544c-4baa-89e1-4f7cb251cfb4)
[The Kontrolog Mini Firmware (verificar y corregir link)](https://github.com/Omicron-IoT-Solutions/Kontrolog-Mini/tree/No-Code/Firmware) contains the factory default code, which is programmed into the Kontrolog Mini from the moment you receive it for your purchase, where you only need to link it to the graphical HMI or IoT Web platform and you can start configuring alarms, inputs and outputs, and monitor the status of them.

To install the Firmware we provide you, you must install the “FLASH DOWNLOAD TOOL” program, which you can find at the following [link](https://www.espressif.com/en/support/download/other-tools)

![bitmap4](https://github.com/user-attachments/assets/b6a006e4-c233-4be9-896f-3023961ebbd6)

Once installed, download the Firmware binary file and connect your Kontrolog Mini to your computer using the USB-C cable. Then, run the downloaded application and set, in the download tool mode, ESP32 as the chip type and the working mode as development. 

![Captura de pantalla 2024-09-26 093040](https://github.com/user-attachments/assets/5428a370-f87d-42e4-8ab8-179a462d1211)

Now you must assign to the software the location where the downloaded firmware file is located and set the memory address to 0x10000. Make sure that the following parameters are assigned:
- SPI Speed in 40MHz.
- SPI mode in DIO.
- The “DoNotChgBin” option must be enabled.
  
Select the communication port your Kontrolog Mini is connected to on your computer and set the baud rate to 460800 Baud. With this you can start downloading the Firmaware to your Kontrolog Mini and it is ready to be configured. 

![Captura de pantalla 2024-09-26 093125](https://github.com/user-attachments/assets/965401de-3623-4b86-984d-8fd21320c8ce)

## Simulating our graphic HMI
For practical purposes, you will be able to verify this code by simulating it using the NEXTION software, which allows you to simulate and implement graphical HMI interfaces. You will need to download and install this software, which you will find at the following [link](https://nextion.tech/nextion-editor/)

![bitmap5](https://github.com/user-attachments/assets/474b78f5-1276-4cc6-bcec-e282d71e6dc2)

Next, download the [.HMI file (verificar y corregir link)](https://github.com/Omicron-IoT-Solutions/Kontrolog-Mini/tree/No-Code/Display), which is the code we provide so that you can simulate the HMI screen in NEXTION and which is also the code that is set in the HMI screens that allow you to program the Kontrolog Mini locally in No-Code mode.

Run Nextion, connect your Kontrolog Mini to your computer via USB-C cable, and select the option that allows you to open documents and indicate the .HMI file you have previously downloaded, and start the debug mode so you can simulate the HMI screen with which you can configure your Kontrolog Mini.

![bitmap6](https://github.com/user-attachments/assets/fedb8984-fed5-4dcf-bad6-4c01200c403d)

Once the debug interface is open, set the following configurations and... You can start your simulation!
- Set as “Current Simulator” in the “send command to:” option.
- Select the “User MCU input” option.
- Set the baud rate to 115200 Baud.
- Indicate the communication port on which you have connected your Kontrolog Mini to your computer.

![bitmap7](https://github.com/user-attachments/assets/2e8c4f9a-6de7-4317-ac4f-9b77bf4a5ec1)

## Configuring the Kontrolog Mini from the captive portal
When you turn on your Kontrolog Mini, in its default configuration, it generates a temporary WiFi network for 2 minutes. This network is named "Kontrolog_xxxxxxxxxxx", followed by the device ID (for example, **"Kontrolog_bcddc212345"**). Connect to this network from any internet-capable device and enter the password **"OmicronIoT12345678"**. Now, open any web browser and enter the device's default IP address **192.168.4.1**. Upon accessing it, the captive portal's home screen for your Kontrolog Mini should appear.

![bitmap8](https://github.com/user-attachments/assets/acdd8f3c-3f33-42a3-9b11-e15163b64d0d)

From the Kontrolog Mini captive portal, you will be able to:
- Connect the Kontrolog Mini to the Internet for wireless data transmission.
- Establish communication with your preferred Ubidots cloud server account.
- Monitor and configure the operation of the input pins (analog and digital) and output pins (relay and digital) of the Kontrolog Mini.
- Check the MAC address and the installed version of your Kontrolog Mini device.

The important thing about this tool is that your Kontrolog Mini is already enabled so you can configure it through the HMI interface or through the IoT web platform. From the tool where you are programming the Kontrolog Mini, you can configure the inputs and outputs, indicate the functions you want them to perform such as sensor readings, activation of relay outputs, define the types of communication you want to use and assign the functions for the LED and the buzzer. Just manipulate the control tools to know how to set the functions you want your Kontrolog Mini to perform.
