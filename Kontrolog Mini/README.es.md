![Logo-Omicron-Vector](https://github.com/Omicron-IoT-Solutions/Kontrolog/assets/141452095/1d867a2d-2f0b-40eb-bbb9-566f306320ba)

# 📆 Kontrolog Mini – Board Support Package (BSP)

![bitmap2](https://github.com/user-attachments/assets/ce062b7b-13b5-4596-9dc3-d58d14262f44)

📄 **Disponible también en inglés**: [English version](./docs/English/README.md)

---

## 📘 Descripción general

Esta rama contiene la documentación y los archivos básicos de encabezado e implementación que componen el **Board Support Package (BSP)** para el **Kontrolog Mini**, así como ejemplos y tutoriales guiados para que aprendas a programarlo en modo **Full-Code**.

---

## 📁 Estructura del BSP

[Kontrolog_Mini_BSP](https://github.com/Omicron-IoT-Solutions/Kontrolog/tree/Full-Code/Kontrolog%20Mini/Kontrolog_Mini_BSP)
```text
├── docs
│   ├── English
│   │   ├── Datasheets
│   │   ├── Manuals
│   │   └── Schematics
│   └── Español
│       ├── Esquemas
│       ├── Hojas de datos
│       └── Manuales
├── examples
│   ├── ReadModbus_SendLoRa.cpp
│   └── ReadNTC10k.cpp
├── include         ← Archivos cabecera (.h)
├── src             ← Archivos fuente (.cpp)
├── README.md
├── library.json
├── platformio.ini
└── wokwi.toml
```

---

## 🛠️ Guía de uso con PlatformIO

Para usar la biblioteca **Kontrolog Mini**, sigue estos pasos:

### 1. 📁 Crear un nuevo proyecto

Utiliza **PlatformIO** (preferiblemente desde Visual Studio Code) y selecciona la placa:

```
Espressif ESP32 Dev Module
```

> Framework por defecto: **Arduino**

![Captura de pantalla 2024-10-01 084556](https://github.com/user-attachments/assets/755282c3-2c37-470c-a1ab-5080e34b671c)

---

### 2. 📚 Buscar e instalar la biblioteca

En el registro de bibliotecas de PlatformIO, busca:

```
Kontrolog Mini
```

> Palabras clave útiles: `kontrolog`, `mini`, `iot`, `esp32`, `plc`

![Captura de pantalla 2024-10-01 090355](https://github.com/user-attachments/assets/f00a9eb2-4b1d-4f98-acf3-7baf086da0d0)

---

### 3. ➕ Vincular la biblioteca al proyecto

Una vez agregada, accede al archivo:

```text
Your project/.pio/libdeps/esp32dev/Kontrolog_Mini/README.md
```

Allí verás las bibliotecas necesarias para incluir en el archivo `platformio.ini` de tu proyecto.

---

### 4. ⚙️ Configurar `platformio.ini`

Agrega las siguientes bibliotecas al archivo `platformio.ini` de tu proyecto:

```text
EEPROM
ESP32Time
ArduinoJson
Wire
WiFi
WebServer
HTTPClient
WiFiClientSecure
FS
```

Guarda los cambios realizados. Esto permitirá una compilación exitosa y el correcto funcionamiento de tu código.

![Captura de pantalla 2024-10-01 091138](https://github.com/user-attachments/assets/954452e5-9bf8-4709-97aa-532de264bfa2)

---

## 💡 ¿Qué puedes hacer?

Este entorno te permite:

* Usar entradas y salidas del Kontrolog Mini.
* Leer sensores.
* Activar relés.
* Configurar comunicación (LoRa, WiFi, etc.).
* Controlar LEDs y buzzer.

Lo importante de esta herramienta es que puedes capturar todas tus ideas y todo lo que deseas ejecutar con tu Kontrolog Mini. Desde tu archivo de encabezado principal, puedes llamar a las entradas y salidas disponibles, indicar las funciones que deseas que realicen, como lecturas de sensores, activación de salidas de relé, definir los tipos de comunicación que deseas vincular y asignar funciones para los LEDs y el buzzer. Solo necesitas explorar cada uno de los archivos de encabezado y los códigos fuente para saber cómo llamar a las funciones respectivas y definir los estados deseados.

---

## 📞 ¿Necesitas ayuda?

* 📧 Correo electrónico: [solutions@omicroniot.com](mailto:solutions@omicroniot.com)
* 📞 WhatsApp / Teléfono: [+57 317 4365062](https://api.whatsapp.com/send?phone=573176478281)

---

**Omicron IoT Solutions** – Tecnología para desarrolladores que transforman industrias.
