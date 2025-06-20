![Logo-Omicron-Vector](https://github.com/Omicron-IoT-Solutions/Kontrolog/assets/141452095/1d867a2d-2f0b-40eb-bbb9-566f306320ba)
# Kontrolog Max in No-Code mode
## General
This branch contains the Firmaware code (default programming of the device) for the Kontrolog Max to be programmed locally through the graphical HMI interface provided, the device's captive portal, or remotely through the IoT Web platform, as well as examples and guided tutorials for you to learn how to program in No-Code mode your Kontrolog Max.

## Flashing Firmware to the Kontrolog Max
![Imagen1](https://github.com/user-attachments/assets/37fd4bb7-4cba-4d6c-b353-0b62dececda8)
[The Kontrolog Max Firmware](https://github.com/Omicron-IoT-Solutions/Kontrolog/tree/No-Code/Kontrolog%20Max/Firmware) contains the factory default code, which is programmed into the Kontrolog Max from the moment you receive it for your purchase, where you only need to link it to the graphical HMI or IoT Web platform and you can start configuring alarms, inputs and outputs, and monitor the status of them.

To install the Firmware we provide you, you must install the “FLASH DOWNLOAD TOOL” program, which you can find at the following [link](https://www.espressif.com/en/support/download/other-tools)

![Imagen2](https://github.com/user-attachments/assets/fc215966-4041-422f-84bb-b3eeed420ba5)

Once installed, download the [Firmware binary file](https://github.com/Omicron-IoT-Solutions/Kontrolog/tree/No-Code/Kontrolog%20Max/Firmware) and connect your Kontrolog Max to your computer using the USB-C cable. Then, run the downloaded application and set, in the download tool mode, ESP32 as the chip type and the working mode as development. 

![Imagen3](https://github.com/user-attachments/assets/984e6492-870a-4387-b2a1-094750439a2d)

Now you must assign to the software the location where the downloaded firmware file is located and set the memory address to 0x10000. Make sure that the following parameters are assigned:
- SPI Speed in 40MHz.
- SPI mode in DIO.
- The “DoNotChgBin” option must be enabled.
  
Select the communication port your Kontrolog Max is connected to on your computer and set the baud rate to 460800 Baud. With this you can start downloading the Firmaware to your Kontrolog Max and it is ready to be configured. 

![Imagen4](https://github.com/user-attachments/assets/4aad81dd-59d8-40c9-bd78-ba3652b1fefd)

## Simulating our graphic HMI
For practical purposes, you will be able to verify this code by simulating it using the NEXTION software, which allows you to simulate and implement graphical HMI interfaces. You will need to download and install this software, which you will find at the following [link](https://nextion.tech/nextion-editor/)

![Imagen5](https://github.com/user-attachments/assets/294eecee-2c46-407a-bc09-050294e6581c)

Next, download the [.HMI file](https://github.com/Omicron-IoT-Solutions/Kontrolog/tree/No-Code/Kontrolog%20Max/Display), which is the code we provide so that you can simulate the HMI screen in NEXTION and which is also the code that is set in the HMI screens that allow you to program the Kontrolog Max locally in No-Code mode.

Run Nextion, connect your Kontrolog Max to your computer via USB-C cable, and select the option that allows you to open documents and indicate the .HMI file you have previously downloaded, and start the debug mode so you can simulate the HMI screen with which you can configure your Kontrolog Max.

![Imagen6](https://github.com/user-attachments/assets/83b7a714-c48e-43a1-9cf7-6307f888263b)

Once the debug interface is open, set the following configurations and... You can start your simulation!
- Set as “Current Simulator” in the “send command to:” option.
- Select the “User MCU input” option.
- Set the baud rate to 115200 Baud.
- Indicate the communication port on which you have connected your Kontrolog Max to your computer.

![Imagen7](https://github.com/user-attachments/assets/cb5291b9-c9d8-445f-ae72-a3d91c251c6b)

## Configuring the Kontrolog Max from the captive portal
When you turn on your Kontrolog Max, in its default configuration, it generates a temporary WiFi network for 2 minutes. This network is named "Kontrolog_xxxxxxxxxxx", followed by the device ID (for example, **"Kontrolog_bcddc212345"**). Connect to this network from any internet-capable device and enter the password **"OmicronIoT12345678"**. Now, open any web browser and enter the device's default IP address **192.168.4.1**. Upon accessing it, the captive portal's home screen for your Kontrolog Max should appear.

![Imagen8](https://github.com/user-attachments/assets/0da060f1-f171-41c8-a78d-dda696d925e2)

From the Kontrolog Max captive portal, you will be able to:
- Connect the Kontrolog Max to the Internet for wireless data transmission.
- Establish communication with your preferred Ubidots cloud server account.
- Monitor and configure the operation of the input pins (analog and digital) and output pins (relay and digital) of the Kontrolog Max.
- Check the MAC address and the installed version of your Kontrolog Max device.

The important thing about this tool is that your Kontrolog Max is already enabled so you can configure it through the HMI interface or through the IoT web platform. From the tool where you are programming the Kontrolog Max, you can configure the inputs and outputs, indicate the functions you want them to perform such as sensor readings, activation of relay outputs, define the types of communication you want to use and assign the functions for the LED and the buzzer. Just manipulate the control tools to know how to set the functions you want your Kontrolog Max to perform.
