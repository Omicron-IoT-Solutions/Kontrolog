![Logo-Omicron-Vector](https://github.com/Omicron-IoT-Solutions/Kontrolog/assets/141452095/1d867a2d-2f0b-40eb-bbb9-566f306320ba)
# Kontrolog Mini Board Support Package (BSP)
## General
![bitmap2](https://github.com/user-attachments/assets/ce062b7b-13b5-4596-9dc3-d58d14262f44)

Esta rama contiene la documentación y los archivos básicos de encabezado e implementación que componen el Board Support Package (BSP) para el Kontrolog Mini, así como ejemplos y tutoriales guiados para que aprendas a programar tu Kontrolog Mini en modo Full-Code.

## Estructura del BSP
- [Kontrolog_Mini_BSP](https://github.com/Omicron-IoT-Solutions/Kontrolog-Mini/tree/Full-Code/Kontrolog_Mini_BSP)
  - docs
    - English
      - Datasheets
      - Manuals
      - Schematics
    - Español
      - Esquemas
      - Hojas de datos
      - Manuales
  - examples
    - ReadModbus_SendLoRa.cpp
    - ReadNTC10k.cpp
  - include
    - (Archivos cabecera .h)
  - scr
    - (Archivos fuente .cpp)
  - README.md
  - library.json
  - platformio.ini
  - wokwi.toml

## Guía de uso
Para utilizar la biblioteca Kontrolog Mini, que se encuentra en el registro de bibliotecas de PlatformIO, primero debes crear un proyecto en PlatformIO utilizando el Arduino Framework (opción predeterminada) y asignar la placa “Espressif ESP32 Dev Module”.

![Captura de pantalla 2024-10-01 084556](https://github.com/user-attachments/assets/755282c3-2c37-470c-a1ab-5080e34b671c)

Una vez que tu proyecto esté creado, ve al registro de bibliotecas de PlatformIO y busca nuestra biblioteca como “Kontrolog Mini” (palabras clave: “kontrolog”, “mini”, “iot”, “esp32”, “plc”). Allí encontrarás información básica sobre la biblioteca proporcionada por la propia plataforma. Luego, procede a agregar esta biblioteca a tu proyecto.

![Captura de pantalla 2024-10-01 090355](https://github.com/user-attachments/assets/f00a9eb2-4b1d-4f98-acf3-7baf086da0d0)

Una vez que hayas vinculado la biblioteca Kontrolog Mini a tu proyecto, ve al archivo README.md de nuestra biblioteca (“Your project”/.pio/libdepsp32dev/Kontrolog_Mini/README.md) e incluye las bibliotecas que se muestran allí en el archivo de inicialización de PlatformIO (platformio.ini) de tu proyecto. Luego, guarda las modificaciones realizadas.

![Captura de pantalla 2024-10-01 091138](https://github.com/user-attachments/assets/954452e5-9bf8-4709-97aa-532de264bfa2)

Lo importante de esta herramienta es que puedes capturar todas tus ideas y todo lo que deseas ejecutar con tu Kontrolog Mini. Desde tu archivo de encabezado principal, puedes llamar a las entradas y salidas disponibles, indicar las funciones que deseas que realicen, como lecturas de sensores, activación de salidas de relé, definir los tipos de comunicación que deseas vincular y asignar funciones para los LEDs y el buzzer. Solo necesitas explorar cada uno de los archivos de encabezado y los códigos fuente para saber cómo llamar a las funciones respectivas y definir los estados deseados.
