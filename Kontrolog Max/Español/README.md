![Logo-Omicron-Vector](https://github.com/Omicron-IoT-Solutions/Kontrolog/assets/141452095/1d867a2d-2f0b-40eb-bbb9-566f306320ba)
# Kontrolog Max
## General
Este repositorio contiene instrucciones, manuales, esquemas, paquetes y ejemplos para programar tu dispositivo Kontrolog Max según las distintas funciones que mejor se adapten a tu aplicación.

## Description
![DSC_0153](https://github.com/Omicron-IoT-Solutions/Kontrolog/assets/141452095/87452571-8b00-4312-8a06-4ba1d7e01cff)
El dispositivo Kontrolog Max es un controlador programable para IoT (Internet de las Cosas) que incorpora la potente tecnología de procesamiento ESP32, diseñado para el control y monitoreo remoto y en tiempo real de diferentes procesos con altos requerimientos de seguridad y precisión. Adaptado a tu aplicación, el dispositivo puede utilizarse fácilmente después de su instalación. Contiene componentes electrónicos como un microcontrolador (CPU), memoria, y otros elementos de hardware como: fuentes de voltaje, salidas de potencia y los puertos necesarios para alojar sensores y el módulo de comunicación IoT. El microcontrolador contiene el software embebido, que realiza tareas como: leer los sensores conectados a sus puertos, obtener su información, crear los paquetes o tramas de monitoreo, configurar y activar el módulo de comunicación, y enviar los datos en intervalos que pueden ser variables según los tiempos de publicación programados, generar alertas y ejecutar tareas de control. Además, el software está disponible en lenguaje C++ de código abierto, lo cual permite dos modos de programación, que se presentan en dos ramas:

- [No-Code (Corregir enlace)](https://github.com/Omicron-IoT-Solutions/Kontrolog-Mini/tree/No-Code)

- [Full-Code (Corregir enlace)](https://github.com/Omicron-IoT-Solutions/Kontrolog-Mini/tree/Full-Code)

## Características
Las principales características técnicas de este modelo del dispositivo Kontrolog Max se listan a continuación:

- Cinco (5) entradas para sensores que pueden configurarse como:
  - Entrada analógica 4-20mA.
  - Entrada analógica 0-10V.
  - Entrada analógica de temperatura para termistor NTC 10K – 3950.
  - Entrada digital 1/0.
  - Entrada para sensores analógicos de temperatura y humedad ambiental.
  - Contador de pulsos digital.
  - Medidor de frecuencia (solo en la entrada 5, hasta 20kHz).

- Cuatro (4) puertos GPIO que el usuario puede programar libremente como entradas o salidas, o utilizarlos para leer otros sensores o con protocolos de comunicación como I2C, SPI, UART, entre otros.

- Una (1) entrada para batería de 6-12VDC, además se mide el voltaje de alimentación en DC.

- Fuente de alimentación de entrada 110-220VAC, además se mide el voltaje de alimentación en AC.

- Una (1) entrada para transformador de corriente para medir corriente AC en los siguientes rangos:
  - 0-30A.
  - 0-50A.
  - 0-100A.

- Un puerto de entrada Modbus RTU (RS-485) operando como maestro en la red.

- AlarmAs:
  - Alarmas visuales y audibles integradas, así como alarmas visibles remotamente desde la aplicación móvil o WEB.
  - Integración con la plataforma para alarmas externas vía SMS, mensaje de voz, correo electrónico y servicio de mensajería Telegram, entre otros.

- Cinco (5) salidas de control: (queda pendiente por definir.)
  - Para el Kontrolog 9.2: Hasta 5 relés de salida, de los cuales dos pueden manejar hasta 12A@120VAC y tres hasta 3A@120VAC.
  - Para el Kontrolog 9.3: Hasta 4 relés de salida, de los cuales dos pueden manejar hasta 12A@120VAC y dos hasta 3A@120VAC; y una quinta salida analógica de 4-20 mA.

- Un (1) puerto USB tipo C que permite la comunicación con el entorno de programación y simulación, y también sirve como fuente de alimentación de 5V para el Kontrolog Max.

- Para realizar tareas de control, como:
  - Control mediante comandos remotos enviados desde la plataforma.
  - Control ON/OFF con histéresis para enfriamiento o calefacción.
  - Temporizador.
  - Salida que sigue al sensor de entrada asociado.
  - Alarma remota.
  - Contador de eventos.
  - Control PID.

- Pantalla HMI (Interfaz Hombre-Máquina); pantalla táctil LCD a color de 4.3" para programación y visualización de datos.

- Puerto de comunicación, donde puede instalarse un módulo de comunicación dual con protocolos para LoRaWAN™/Sigfox para las zonas USA/EU/Latam/Australia o un módulo de comunicación WiFi.
  
El Kontrolog Max se alimenta mediante un cable de poder de dos hilos, conectando sus entradas AC1 y AC2 a las líneas de 110-220VAC, 50-60Hz. También puede ser alimentado por una batería de 6-12V. El sistema se entrega con los módulos de comunicación inalámbrica solicitados. De acuerdo con la filosofía del producto, todos los complementos antes mencionados pueden prescribirse, y la transmisión de datos remota puede realizarse mediante diferentes tecnologías inalámbricas populares. También se ofrecen membresías para el uso de una plataforma de monitoreo y configuración remota, respaldada por el fabricante.