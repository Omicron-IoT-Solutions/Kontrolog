![Logo-Omicron-Vector](https://github.com/Omicron-IoT-Solutions/Kontrolog/assets/141452095/1d867a2d-2f0b-40eb-bbb9-566f306320ba)
# Kontrolog Max en modo No-Code
## General
Esta rama contiene el código del Firmware (programación predeterminada del dispositivo) para el Kontrolog Max, permitiendo su programación local a través de la interfaz gráfica HMI proporcionada, el portal cautivo del dispositivo o de forma remota mediante la plataforma web IoT. También incluye ejemplos y tutoriales guiados para que aprendas a programar tu Kontrolog Max en modo No-Code.

## Grabando el Firmware a el Kontrolog Max
![bitmap3](https://github.com/user-attachments/assets/53b01053-544c-4baa-89e1-4f7cb251cfb4)
[El Firmware del Kontrolog Max](https://github.com/Omicron-IoT-Solutions/Kontrolog/tree/No-Code/Kontrolog%20Max/Firmware) contiene el código de fábrica predeterminado, que viene programado en el Kontrolog Max desde el momento en que lo recibes tras tu compra. Solo necesitas vincularlo a la interfaz gráfica HMI o a la plataforma web IoT para comenzar a configurar alarmas, entradas y salidas, y monitorear su estado.

Para instalar el Firmware que te proporcionamos, debes instalar el programa "FLASH DOWNLOAD TOOL", el cual puedes encontrar en el siguiente [enlace](https://www.espressif.com/en/support/download/other-tools)

![bitmap4](https://github.com/user-attachments/assets/b6a006e4-c233-4be9-896f-3023961ebbd6)

Una vez instalado, descarga el archivo binario del Firmware y conecta tu Kontrolog Max a tu computadora usando el cable USB-C. Luego, ejecuta la aplicación descargada y configura, en el modo de la herramienta de descarga, ESP32 como el tipo de chip y el modo de trabajo como desarrollo. 

![Captura de pantalla 2024-09-26 093040](https://github.com/user-attachments/assets/5428a370-f87d-42e4-8ab8-179a462d1211)

Ahora debes asignar en el software la ubicación donde se encuentra el archivo de firmware descargado y establecer la dirección de memoria en 0x10000. Asegúrate de configurar los siguientes parámetros:
- SPI Speed en 40MHz.
- SPI Mode en DIO.
- La opción “DoNotChgBin” debe estar habilitada.

Selecciona el puerto de comunicación al que está conectado tu Kontrolog Max en tu computadora y establece la tasa de baudios en 460800 Baud.

Con esto, puedes iniciar la descarga del Firmware en tu Kontrolog Max, y estará listo para ser configurado.

![Captura de pantalla 2024-09-26 093125](https://github.com/user-attachments/assets/965401de-3623-4b86-984d-8fd21320c8ce)

## Simulando nuestra HMI gráfica
Para fines prácticos, podrás verificar este código simulándolo mediante el software NEXTION, que permite simular e implementar interfaces gráficas HMI. Debes descargar e instalar este software, el cual puedes encontrar en el si [enlace](https://nextion.tech/nextion-editor/)

![bitmap5](https://github.com/user-attachments/assets/474b78f5-1276-4cc6-bcec-e282d71e6dc2)

A continuación, descarga el  [archivo .HMI ](https://github.com/Omicron-IoT-Solutions/Kontrolog/tree/No-Code/Kontrolog%20Max/Display), el cual contiene el código que te proporcionamos para simular la pantalla HMI en NEXTION. Este mismo código está preconfigurado en las pantallas HMI que permiten programar el Kontrolog Max localmente en modo No-Code.

Ejecuta Nextion, conecta tu Kontrolog Max a tu computadora mediante el cable USB-C, y selecciona la opción para abrir documentos. Luego, indica el archivo .HMI que descargaste previamente y activa el modo de depuración para simular la pantalla HMI con la que podrás configurar tu Kontrolog Max.

![bitmap6](https://github.com/user-attachments/assets/fedb8984-fed5-4dcf-bad6-4c01200c403d)

Una vez que la interfaz de depuración esté abierta, configura los siguientes parámetros y… ¡puedes comenzar tu simulación!
- Establece "Current Simulator" en la opción “send command to:”.
- Selecciona la opción “User MCU input”.
- Configura la tasa de baudios en 115200 Baud.
- Indica el puerto de comunicación en el que has conectado tu Kontrolog Max a tu computadora.

![bitmap7](https://github.com/user-attachments/assets/2e8c4f9a-6de7-4317-ac4f-9b77bf4a5ec1)

## Configuración del Kontrolog Max desde el portal cautivo
Cuando enciendes tu Kontrolog Max, en su configuración por defecto, este genera una red WiFi temporal durante 2 minutos. Esta red se nombra "Kontrolog_xxxxxxxxxxx", seguido del ID del dispositivo (por ejemplo, **"Kontrolog_bcddc212345"**). Conéctate a esta red desde un dispositivo con acceso a Internet e ingresa la contraseña **"OmicronIoT12345678"**. Abre cualquier navegador web e ingresa la dirección IP **192.168.4.1**. Una vez dentro, se mostrará la pantalla de inicio del portal cautivo de tu Kontrolog Max.

![bitmap8](https://github.com/user-attachments/assets/14ef4256-675e-4f91-afd3-5d90d7457164)

Desde el portal cautivo, podrás:
- Conectar tu Kontrolog Max a Internet para la transmisión inalámbrica de datos.
- Establecer comunicación con tu cuenta en la nube de Ubidots.
- Monitorear y configurar el funcionamiento de los pines de entrada (análogos y digitales) y salida (relé y digitales) del dispositivo.
- Consultar la dirección MAC y la versión instalada de tu Kontrolog Max.

Lo importante de esta herramienta es que tu Kontrolog Max ya estará habilitado para configurarse tanto a través de la interfaz HMI como de la plataforma web IoT. Desde la herramienta donde programes el Kontrolog Max, podrás configurar entradas y salidas, asignar funciones como lecturas de sensores y activación de salidas de relé, definir los tipos de comunicación a utilizar, asignar funciones para el LED y el buzzer. Simplemente ajusta las herramientas de control para definir las funciones que deseas que ejecute tu Kontrolog Max.
