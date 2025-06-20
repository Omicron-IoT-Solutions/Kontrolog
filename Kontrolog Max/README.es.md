![Logo-Omicron-Vector](https://github.com/Omicron-IoT-Solutions/Kontrolog/assets/141452095/1d867a2d-2f0b-40eb-bbb9-566f306320ba)
# Kontrolog Max en modo No-Code
## General
Esta rama contiene el código del Firmware (programación predeterminada del dispositivo) para el Kontrolog Max, permitiendo su programación local a través de la interfaz gráfica HMI proporcionada, el portal cautivo del dispositivo o de forma remota mediante la plataforma web IoT. También incluye ejemplos y tutoriales guiados para que aprendas a programar tu Kontrolog Max en modo No-Code.

## Grabando el Firmware a el Kontrolog Max
![Imagen1](https://github.com/user-attachments/assets/fbf9d6a2-eeb3-418f-a79d-9f943d3a5ea5)
[El Firmware del Kontrolog Max](https://github.com/Omicron-IoT-Solutions/Kontrolog/tree/No-Code/Kontrolog%20Max/Firmware) contiene el código de fábrica predeterminado, que viene programado en el Kontrolog Max desde el momento en que lo recibes tras tu compra. Solo necesitas vincularlo a la interfaz gráfica HMI o a la plataforma web IoT para comenzar a configurar alarmas, entradas y salidas, y monitorear su estado.

Para instalar el Firmware que te proporcionamos, debes instalar el programa "FLASH DOWNLOAD TOOL", el cual puedes encontrar en el siguiente [enlace](https://www.espressif.com/en/support/download/other-tools)

![Imagen2](https://github.com/user-attachments/assets/caf67ec2-89f7-4994-ae45-d49b2b44ff7a)

Una vez instalado, descarga el [archivo binario del Firmware](https://github.com/Omicron-IoT-Solutions/Kontrolog/tree/No-Code/Kontrolog%20Max/Firmware) y conecta tu Kontrolog Max a tu computadora usando el cable USB-C. Luego, ejecuta la aplicación descargada y configura, en el modo de la herramienta de descarga, ESP32 como el tipo de chip y el modo de trabajo como desarrollo. 

![Imagen3](https://github.com/user-attachments/assets/83327661-6feb-41ee-af04-5c0a71357d86)

Ahora debes asignar en el software la ubicación donde se encuentra el archivo de firmware descargado y establecer la dirección de memoria en 0x10000. Asegúrate de configurar los siguientes parámetros:
- SPI Speed en 40MHz.
- SPI Mode en DIO.
- La opción “DoNotChgBin” debe estar habilitada.

Selecciona el puerto de comunicación al que está conectado tu Kontrolog Max en tu computadora y establece la tasa de baudios en 460800 Baud.

Con esto, puedes iniciar la descarga del Firmware en tu Kontrolog Max, y estará listo para ser configurado.

![Imagen4](https://github.com/user-attachments/assets/96bd23b2-2f7a-4f38-bbd1-caf6cbca2cce)

## Simulando nuestra HMI gráfica
Para fines prácticos, podrás verificar este código simulándolo mediante el software NEXTION, que permite simular e implementar interfaces gráficas HMI. Debes descargar e instalar este software, el cual puedes encontrar en el si [enlace](https://nextion.tech/nextion-editor/)

![Imagen5](https://github.com/user-attachments/assets/398834d9-ea50-4df7-9848-b467aec50017)

A continuación, descarga el  [archivo .HMI ](https://github.com/Omicron-IoT-Solutions/Kontrolog/tree/No-Code/Kontrolog%20Max/Display), el cual contiene el código que te proporcionamos para simular la pantalla HMI en NEXTION. Este mismo código está preconfigurado en las pantallas HMI que permiten programar el Kontrolog Max localmente en modo No-Code.

Ejecuta Nextion, conecta tu Kontrolog Max a tu computadora mediante el cable USB-C, y selecciona la opción para abrir documentos. Luego, indica el archivo .HMI que descargaste previamente y activa el modo de depuración para simular la pantalla HMI con la que podrás configurar tu Kontrolog Max.

![Imagen6](https://github.com/user-attachments/assets/0e52eb0d-38e8-477c-b083-8d3984bbb8ac)

Una vez que la interfaz de depuración esté abierta, configura los siguientes parámetros y… ¡puedes comenzar tu simulación!
- Establece "Current Simulator" en la opción “send command to:”.
- Selecciona la opción “User MCU input”.
- Configura la tasa de baudios en 115200 Baud.
- Indica el puerto de comunicación en el que has conectado tu Kontrolog Max a tu computadora.

![Imagen7](https://github.com/user-attachments/assets/fcbfef68-324c-4960-b7fb-15dd5e9dac0e)

## Configuración del Kontrolog Max desde el portal cautivo
Cuando enciendes tu Kontrolog Max, en su configuración por defecto, este genera una red WiFi temporal durante 2 minutos. Esta red se nombra "Kontrolog_xxxxxxxxxxx", seguido del ID del dispositivo (por ejemplo, **"Kontrolog_bcddc212345"**). Conéctate a esta red desde un dispositivo con acceso a Internet e ingresa la contraseña **"OmicronIoT12345678"**. Abre cualquier navegador web e ingresa la dirección IP **192.168.4.1**. Una vez dentro, se mostrará la pantalla de inicio del portal cautivo de tu Kontrolog Max.

![Imagen8](https://github.com/user-attachments/assets/7987efe7-a73c-4dc1-a390-77a2f19e8f43)

Desde el portal cautivo, podrás:
- Conectar tu Kontrolog Max a Internet para la transmisión inalámbrica de datos.
- Establecer comunicación con tu cuenta en la nube de Ubidots.
- Monitorear y configurar el funcionamiento de los pines de entrada (análogos y digitales) y salida (relé y digitales) del dispositivo.
- Consultar la dirección MAC y la versión instalada de tu Kontrolog Max.

Lo importante de esta herramienta es que tu Kontrolog Max ya estará habilitado para configurarse tanto a través de la interfaz HMI como de la plataforma web IoT. Desde la herramienta donde programes el Kontrolog Max, podrás configurar entradas y salidas, asignar funciones como lecturas de sensores y activación de salidas de relé, definir los tipos de comunicación a utilizar, asignar funciones para el LED y el buzzer. Simplemente ajusta las herramientas de control para definir las funciones que deseas que ejecute tu Kontrolog Max.
