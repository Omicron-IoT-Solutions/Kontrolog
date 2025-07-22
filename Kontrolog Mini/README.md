![LogoOmicron](https://github.com/user-attachments/assets/d9f83630-a11e-481d-b205-3f96a689434e)

# 🧩 Kontrolog Mini in No-Code mode.

<img width="1054" height="673" alt="Imagen16" src="https://github.com/user-attachments/assets/79a27ced-9293-4473-a6a7-ce618b998fb5" />

📄 **Also available in Spanish**: [Versión en Español](./README.es.md).

---

## 📘 Overview:

This branch contains the default firmware for the **Kontrolog Mini**, allowing it to be configured without writing any code, through three main methods:

* Local HMI graphical interface.
* Captive portal via WiFi.
* IoT web platform (if enabled).

It also includes examples and tutorials to guide you step by step through installation and use in No-Code mode.

> ✅ **Ideal for technicians, professionals, students, and integrators.**

---

## ⚙️ How to upload the firmware to Kontrolog Mini?:

The [Kontrolog Mini firmware](https://github.com/Omicron-IoT-Solutions/Kontrolog/tree/No-Code/Kontrolog%20Mini/Firmware) is the default factory software that comes pre-installed on your device. However, you can reinstall or update it manually if needed.

### Steps:

1. Download and install the **[Flash Download Tool](https://www.espressif.com/en/support/download/other-tools)**.

![Imagen2](https://github.com/user-attachments/assets/d830d2c1-2b5f-41d7-9aa4-316e00b37646)

2. Download the `.bin` firmware file from the repository.
3. Connect your Kontrolog Mini to your PC via USB-C cable.
4. Open Flash Download Tool and select:

   * **Chip**: ESP32.
   * **Mode**: Development.

![Imagen3](https://github.com/user-attachments/assets/dc8715cd-fe37-4aad-93b5-ffe1435367ec)

5. Load the `.bin` file and configure:

   * Memory address: `0x10000`.
   * SPI Speed: `40MHz`.
   * SPI Mode: `DIO`.
   * Enable “DoNotChgBin”.
6. Select the correct COM port and baud rate: `460800 Baud`.
7. Click Start to flash the firmware onto your device.

![Imagen4](https://github.com/user-attachments/assets/0a965cd7-595f-4141-aa59-d5a2ba10c06d)

---

## 🖥️ Simulating the HMI screen:

You can simulate the touch interface of the Kontrolog Mini using the **[Nextion Editor](https://nextion.tech/nextion-editor/)** software.

### Steps:

1. Download and install Nextion Editor.

![Imagen5](https://github.com/user-attachments/assets/45701c91-f855-4795-b4de-9208c3d0a62a)

2. Download the [.HMI file](https://github.com/Omicron-IoT-Solutions/Kontrolog/tree/No-Code/Kontrolog%20Mini/Display).
3. Open it in Nextion Editor.
4. Launch debug mode.

![Imagen6](https://github.com/user-attachments/assets/a924e41f-6013-4a0a-b0d7-275547a75170)

5. Configure:

   * **Send command to**: “Current Simulator”.
   * **User MCU input**: enabled.
   * **Baudrate**: `115200`.
   * **Port**: same COM port connected to your Kontrolog Mini.

![Imagen7](https://github.com/user-attachments/assets/aebb5222-47fa-454e-8ee6-0c7e21311bef)

This allows you to simulate the real HMI screen experience and configure basic parameters.

---

## 🌐 Configuration via captive portal:

By default, when powered on, the Kontrolog Mini creates a temporary WiFi network:

```
Kontrolog_xxxxxxxxxxx
```

(Example: `Kontrolog_bcddc212345`).

### Steps:

1. Connect to this WiFi network from your PC or mobile (password: `OmicronIoT12345678`).
2. Open a browser and go to: `192.168.4.1`.

From the captive portal you can:

* Connect the device to the internet.
* Link your account to the cloud (Ubidots).
* Monitor and configure inputs and outputs.
* View the MAC address and firmware version.

![Imagen8](https://github.com/user-attachments/assets/666492e7-84ff-4054-98aa-303487e7e8d6)

This allows you to configure the Kontrolog Mini without coding, using a visual and user-friendly interface.

---

## 📞 Contact:

Do you have questions or need support?

* 📧 Email: [solutions@omicroniot.com](mailto:solutions@omicroniot.com).
* 📱 WhatsApp / Phone: [+57 317 4365062](https://api.whatsapp.com/send?phone=573176478281).

---

**Omicron IoT Solutions**
