![Logo-Omicron-Vector](https://github.com/Omicron-IoT-Solutions/Kontrolog/assets/141452095/1d867a2d-2f0b-40eb-bbb9-566f306320ba)

# Kontrolog Mini + OpenPLC

<img width="931" height="673" alt="Imagen2(1)" src="https://github.com/user-attachments/assets/a99b089b-df82-4ea8-a3bd-a83dacc7c3c9" />

📄 **Disponible en otros idiomas**: [English version](./README.md).

---

## 📘 Descripción general

En esta guía aprenderás a integrar tu **Kontrolog Mini** con **OpenPLC**, con instrucciones claras sobre las configuraciones necesarias, los archivos que debes modificar y ejemplos prácticos que te ayudarán a validar su funcionamiento.

> ✅ **Ideal si eres estudiante, profesional, técnico o integrador y quieres aprovechar el Kontrolog Mini dentro del ecosistema OpenPLC.**

---

## 🛠️ Requisitos previos

* [Descargar OpenPLC Editor](https://autonomylogic.com/download).
* [Descargar Visual Studio Code](https://code.visualstudio.com/Download).

Una vez instales estos programas, deberás añadir archivos de configuración al entorno de OpenPLC.

---

## 📂 Archivos a agregar

Coloca los siguientes archivos en la ruta:

```
C:\...\OpenPLC_Editor\editor\arduino\src
```

* **[config.h](https://github.com/Omicron-IoT-Solutions/Kontrolog/blob/OpenPLC/Kontrolog%20Mini/config.h)**
* **[TLA2528.cpp](https://github.com/Omicron-IoT-Solutions/Kontrolog/blob/OpenPLC/Kontrolog%20Mini/TLA2528.cpp)**
* **[tla2528.h](https://github.com/Omicron-IoT-Solutions/Kontrolog/blob/OpenPLC/Kontrolog%20Mini/tla2528.h)**
* **[TLA2528\_C.h](https://github.com/Omicron-IoT-Solutions/Kontrolog/blob/OpenPLC/Kontrolog%20Mini/TLA2528_C.h)**

Y reemplaza el siguiente archivo en la ruta:

```
C:\...\OpenPLC_Editor\editor\arduino\src\hal
```

* **[esp32.cpp](https://github.com/Omicron-IoT-Solutions/Kontrolog/blob/OpenPLC/Kontrolog%20Mini/esp32.cpp)**

Estos archivos ya están incluidos en este repositorio, por lo que solo tendrás que copiarlos en las carpetas indicadas.

---

## 🗂️ Distribución de pines

A continuación tienes la asignación de pines del Kontrolog Mini dentro de OpenPLC:

| Puerto | Tipo | Señal | Etiqueta | Asignación                |
| ------ | ---- | ----- | -------- | ------------------------- |
| 33     | I/O  | A/D   | GPIO33   | QX0.5 / QW0 / IX0.0 / IW0 |
| 25     | I/O  | A/D   | GPIO25   | QX0.6 / QW1 / IX0.1 / IW1 |
| 16     | I/O  | A/D   | GPIO16   | QX0.7 / QW2 / IX0.2 / IW2 |
| 04     | I/O  | A/D   | GPIO04   | QX1.0 / QW3 / IX0.3 / IW3 |
| 32     | O    | D     | LED\_R   | QX0.0                     |
| 17     | O    | D     | BUZZER   | QX0.4                     |
| 15     | O    | D     | LED\_G   | QX0.1                     |
| 13     | O    | D     | LED\_B   | QX0.2                     |
| 02     | O    | D     | LED2     | QX0.3                     |
| IN1    | I    | A/D   | IN1      | IX0.4 / IW4               |
| IN2    | I    | A/D   | IN2      | IX0.5 / IW5               |
| REL1   | O    | D     | REL1     | QX1.1                     |
| REL2   | O    | D     | REL2     | QX1.2                     |

> ⚠️ Es recomendable que respetes este mapeo en OpenPLC Editor para garantizar un funcionamiento estable y una correcta integración de OpenPLC con tu Kontrolog Mini.

---

## 📥 Recursos de aprendizaje

* 📖 Documentación oficial: [Guía de OpenPLC](https://autonomylogic.com/docs/openplc-overview/).
* 🎥 Canal de YouTube con guías de uso de OpenPLC: [OpenPLC Videos](https://www.youtube.com/@openplc/videos).

---

## ⚙️ Configuración en OpenPLC Editor

Para que tu Kontrolog Mini funcione de manera adecuada, necesitas realizar configuraciones directamente en **OpenPLC Editor**.

Un buen punto de partida es inicializar las salidas en estado apagado, usando un programa en lenguaje Ladder. Así, evitarás que los LEDs se enciendan de manera inesperada al iniciar.

<img width="809" height="399" alt="05c6c738-2a89-4a98-b904-273bf0f5cc68" src="https://github.com/user-attachments/assets/bc6cc2f1-2166-4689-bc23-f97d0ca83bc5" />

En la sección **I/O Config** del OpenPLC Editor:

* Selecciona como Board Type la opción `ESP32 WROOM [3.3.0]`.
* Ingresa como **Digital Outputs** los pines en este orden: `32, 15, 13, 02`.
* Deja en blanco los campos de **Digital Inputs**, **Analog Inputs** y **Analog Outputs**, a menos que vayas a usarlos.

<img width="985" height="623" alt="61e3027c-b4ed-4c4b-974c-a6949b437e4e" src="https://github.com/user-attachments/assets/f0951973-eee9-489e-aed9-008c91c6c0cc" />

> ⚠️ Esta configuración es clave para asegurar que la integración de OpenPLC con tu Kontrolog Mini funcione de manera correcta y estable desde el inicio.

---

## 🎬 Ejemplos incluidos

Dentro de este repositorio encontrarás ejemplos prácticos que te servirán como primera validación de la integración:

* ✅ **Parpadeo del LED RGB**, donde comprobarás que los mapeos de pines funcionan correctamente.
* ✅ **Lectura de la entrada analógica IN1**, ideal para verificar que las señales de entrada se reconocen sin errores.

Estos ejemplos son la forma más sencilla y confiable de confirmar que tu entorno OpenPLC y el Kontrolog Mini están trabajando en conjunto de manera adecuada.

---

## 📞 ¿Necesitas ayuda?

* 📧 Correo electrónico: [solutions@omicroniot.com](mailto:solutions@omicroniot.com).
* 📱 WhatsApp / Teléfono: [+57 317 4365062](https://api.whatsapp.com/send?phone=573176478281).

---

**Omicron IoT Solutions**
