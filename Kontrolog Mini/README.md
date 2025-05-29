# **📆 Kontrolog Mini – Board Support Package (BSP)**

📄 **Also available in Spanish**: [Versión en Español](https://github.com/Omicron-IoT-Solutions/Kontrolog/blob/Full-Code/Kontrolog%20Mini/docs/Espa%C3%B1ol/README.md)

---

## **📘 Overview**

This branch contains the documentation and the basic header and source files that make up the **Board Support Package (BSP)** for the **Kontrolog Mini**, along with examples and guided tutorials to help you program it in **Full-Code** mode.

---

## **📁 BSP Structure**

[Kontrolog\_Mini\_BSP](https://github.com/Omicron-IoT-Solutions/Kontrolog/tree/Full-Code/Kontrolog%20Mini/Kontrolog_Mini_BSP)

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
├── include         ← Header files (.h)
├── src             ← Source files (.cpp)
├── README.md
├── library.json
├── platformio.ini
└── wokwi.toml
```

---

## **🛠️ How to Use with PlatformIO**

To use the **Kontrolog Mini** library, follow these steps:

### **1. 📁 Create a new project**

Use **PlatformIO** (preferably with Visual Studio Code) and select the board:

```text
Espressif ESP32 Dev Module
```

> Default framework: **Arduino**

![372495867-755282c3-2c37-470c-a1ab-5080e34b671c](https://github.com/user-attachments/assets/611ca6b2-87bf-48db-94ea-f8dcde6dee67)

---

### **2. 📚 Search and install the library**

In the PlatformIO library registry, search for:

```text
Kontrolog Mini
```

> Useful keywords: `kontrolog`, `mini`, `iot`, `esp32`, `plc`

![372500573-f00a9eb2-4b1d-4f98-acf3-7baf086da0d0](https://github.com/user-attachments/assets/d44f66de-ef81-4cf8-b797-296cbe1f9b61)

---

### **3. ➕ Link the library to your project**

Once added, go to the file:

```text
Your project/.pio/libdeps/esp32dev/Kontrolog_Mini/README.md
```

There you'll find the libraries needed to include in your project's `platformio.ini` file.

---

### **4. ⚙️ Configure `platformio.ini`**

Add the following libraries to your `platformio.ini` file:

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

Save the changes. This will ensure successful compilation and correct operation of your code.

![372506405-954452e5-9bf8-4709-97aa-532de264bfa2](https://github.com/user-attachments/assets/b3badfd3-ba55-4d4a-9653-6a666387187b)

---

## **💡 What can you do?**

This environment allows you to:

* Use the Kontrolog Mini's input and output pins.
* Read sensors.
* Activate relays.
* Configure communication (LoRa, WiFi, etc.).
* Control LEDs and the buzzer.

This tool is ideal for capturing all your ideas and implementing everything you want with your Kontrolog Mini. From your main header file, you can call the available inputs and outputs, specify their functions such as sensor readings, relay activation, configure the communication interfaces you want to use, and assign actions to the LEDs and buzzer. You only need to explore the provided header and source files to understand how to call each function and define the desired behavior.

---

## **📞 Need help?**

* 📧 Email: [solutions@omicroniot.com](mailto:solutions@omicroniot.com)
* 📞 WhatsApp / Phone: [+57 317 4365062](https://api.whatsapp.com/send?phone=573176478281)

---

**Omicron IoT Solutions** – Technology for developers transforming industries.
