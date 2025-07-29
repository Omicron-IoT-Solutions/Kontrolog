![Logo-Omicron-Vector](https://github.com/Omicron-IoT-Solutions/Kontrolog/assets/141452095/1d867a2d-2f0b-40eb-bbb9-566f306320ba)

# 📆 Kontrolog Mini – Board Support Package (BSP)

![458474100-dae119af-4867-4a18-a82f-a2c2725e21b4](https://github.com/user-attachments/assets/2f764f75-c2cd-471b-813f-434569d5f4f2)

📄 **Disponible en otros idiomas**: [English version](./README.md)

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
├── PartitionsFlashKontrolog16MB.csv
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

![448928778-611ca6b2-87bf-48db-94ea-f8dcde6dee67](https://github.com/user-attachments/assets/6605b321-1357-4c13-95b3-c17a8f21dabc)

---

### 2. 📚 Buscar e instalar la biblioteca

En el registro de bibliotecas de PlatformIO, busca:

```
Kontrolog Mini
```

> Palabras clave útiles: `kontrolog`, `mini`, `iot`, `esp32`, `plc`

![448928995-d44f66de-ef81-4cf8-b797-296cbe1f9b61](https://github.com/user-attachments/assets/fc72caca-0d82-477c-948b-3f9099c5a628)

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

![448929228-b3badfd3-ba55-4d4a-9653-6a666387187b](https://github.com/user-attachments/assets/ffa7b0bb-3171-4dd9-897c-e4578de0b312)

---

### **5. 🔁 Reemplazar el archivo esp32dev.json**

Para asegurar la correcta configuración de la placa, reemplaza el archivo `esp32dev.json` -que se encuentra en la ruta `C:\Users\<TU_USUARIO>\.platformio/platforms/espressif32/boards/`- de tu entorno por el archivo personalizado que se encuentra en la siguiente dirección:

👉 [esp32dev.json](https://github.com/Omicron-IoT-Solutions/Kontrolog/blob/Full-Code/Kontrolog%20Mini/esp32dev.json).

Este archivo contiene ajustes avanzados que permiten una compilación más optimizada y compatible con las funciones del Kontrolog Mini.

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
