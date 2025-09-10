![266786784-1d867a2d-2f0b-40eb-bbb9-566f306320ba](https://github.com/user-attachments/assets/2ed5f521-2b13-472a-b7aa-a4604cd8a80a)

# Kontrolog Mini + OpenPLC

<img width="931" height="673" alt="Imagen2(1)" src="https://github.com/user-attachments/assets/71126117-d31a-4220-b51f-7f0f662a0b81" />

📄 **Available in other languages**: [Versión en Español](./README.es.md).

---

## 📘 Overview

In this guide, you will learn how to integrate your **Kontrolog Mini** with **OpenPLC**, with clear instructions on the required configurations, the files you need to modify, and practical examples to validate its operation.

> ✅ **Ideal if you are a student, professional, technician, or integrator and want to make the most of the Kontrolog Mini within the OpenPLC ecosystem.**

---

## 🛠️ Prerequisites

* [Download OpenPLC Editor](https://www.openplcproject.com/).

Once you install these programs, you will need to add configuration files to the OpenPLC environment.

---

## 📂 Files to add

Place the following files in the path:

```
C:\<Users\Personal>\OpenPLC_Editor\editor\arduino\src
```

* [config.h](https://github.com/Omicron-IoT-Solutions/Kontrolog/blob/OpenPLC/Kontrolog%20Mini/Files%20%28Archivos%29/config.h)
* [TLA2528.cpp](https://github.com/Omicron-IoT-Solutions/Kontrolog/blob/OpenPLC/Kontrolog%20Mini/Files%20%28Archivos%29/TLA2528.cpp)
* [tla2528.h](https://github.com/Omicron-IoT-Solutions/Kontrolog/blob/OpenPLC/Kontrolog%20Mini/Files%20%28Archivos%29/tla2528.h)
* [TLA2528\_C.h](https://github.com/Omicron-IoT-Solutions/Kontrolog/blob/OpenPLC/Kontrolog%20Mini/Files%20%28Archivos%29/TLA2528_C.h)

And replace the following file in the path:

```
C:\<Users\Personal>\OpenPLC_Editor\editor\arduino\src\hal
```

* [esp32.cpp](https://github.com/Omicron-IoT-Solutions/Kontrolog/blob/OpenPLC/Kontrolog%20Mini/Files%20%28Archivos%29/esp32.cpp)

These files are already included in this repository, so you only need to copy them into the specified folders.

---

## 🗂️ Pin mapping

Below is the pin assignment of the Kontrolog Mini within OpenPLC:

| Port | Type | Signal | Label  | Mapping                   |
| ---- | ---- | ------ | ------ | ------------------------- |
| 33   | I/O  | A/D    | GPIO33 | QX0.5 / QW0 / IX0.0 / IW0 |
| 25   | I/O  | A/D    | GPIO25 | QX0.6 / QW1 / IX0.1 / IW1 |
| 16   | I/O  | A/D    | GPIO16 | QX0.7 / QW2 / IX0.2 / IW2 |
| 04   | I/O  | A/D    | GPIO04 | QX1.0 / QW3 / IX0.3 / IW3 |
| 32   | O    | D      | LED\_R | QX0.0                     |
| 17   | O    | D      | BUZZER | QX0.4                     |
| 15   | O    | D      | LED\_G | QX0.1                     |
| 13   | O    | D      | LED\_B | QX0.2                     |
| 02   | O    | D      | LED2   | QX0.3                     |
| IN1  | I    | A/D    | IN1    | IX0.4 / IW4               |
| IN2  | I    | A/D    | IN2    | IX0.5 / IW5               |
| REL1 | O    | D      | REL1   | QX1.1                     |
| REL2 | O    | D      | REL2   | QX1.2                     |

> ⚠️ It is recommended that you respect this mapping in OpenPLC Editor to ensure stable operation and proper integration of OpenPLC with your Kontrolog Mini.

---

## 📥 Learning resources

* 📖 Official documentation: [OpenPLC Guide](https://autonomylogic.com/docs/openplc-overview/).
* 🎥 YouTube channel with OpenPLC tutorials: [OpenPLC Videos](https://www.youtube.com/@openplc/videos).

---

## ⚙️ Configuration in OpenPLC Editor

To make your Kontrolog Mini work correctly, you must perform configurations directly in **OpenPLC Editor**.

Open OpenPLC Editor and create a new project inside an empty folder. Keep in mind that each project in OpenPLC Editor is saved as a folder with all the necessary files, so you cannot use a folder that already has content.

When you define the path of your project, an initial settings window will appear. There you must assign the name of the POU (Program Organization Unit), keep the POU type as `program`, and choose the `LD` (Ladder) language.

A good starting point is to initialize the outputs in the OFF state, to avoid LEDs turning on unexpectedly at startup.

Once you have your program, you can simulate it and transfer it to the Kontrolog Mini using the editor options.

In the **I/O Config** section of OpenPLC Editor:

* Select **Board Type** as `ESP32 WROOM [3.3.0]`.
* Define the serial communication port you are using to connect your Kontrolog Mini to the computer.
* Enter as **Digital Outputs** the pins in this order: `32, 15, 13, 02`.
* Leave the fields for **Digital Inputs**, **Analog Inputs**, and **Analog Outputs** empty unless you are going to use them.

In the **Transfer** section, select the option `Transfer to PLC` and the program will be installed on your Kontrolog Mini.

> ⚠️ This configuration is essential to ensure that the integration of OpenPLC with your Kontrolog Mini works correctly and reliably from the beginning.

---

## 🎬 Included examples

In this repository, you will find practical examples that will serve as the first validation of the integration:

* ✅ **RGB LED blink**, where you will confirm that the pin mappings are working correctly.
* ✅ **Reading the analog input IN1**, ideal for verifying that the input signals are recognized without errors.

These examples are the simplest and most reliable way to confirm that your OpenPLC environment and the Kontrolog Mini are working together properly.

---

## 📞 Need help?

* 📧 Email: [solutions@omicroniot.com](mailto:solutions@omicroniot.com).
* 📱 WhatsApp / Phone: [+57 317 4365062](https://api.whatsapp.com/send?phone=573176478281).

---

**Omicron IoT Solutions**
