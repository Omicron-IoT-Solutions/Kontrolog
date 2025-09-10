![Logo-Omicron-Vector](https://github.com/Omicron-IoT-Solutions/Kontrolog/assets/141452095/1d867a2d-2f0b-40eb-bbb9-566f306320ba)

# Kontrolog Mini + OpenPLC

<img width="939" height="673" alt="Imagen2(1)" src="https://github.com/user-attachments/assets/fa4ba6db-df3b-42ee-aba6-5f110a682ae6" />

📄 **Disponible en otros idiomas**: [English version](./README.md).

---

## 📘 Descripción general

En esta guía aprenderás a integrar tu **Kontrolog Mini** con **OpenPLC**, con instrucciones claras sobre las configuraciones necesarias, los archivos que debes modificar y ejemplos prácticos que te ayudarán a validar su funcionamiento.

> ✅ **Ideal si eres estudiante, profesional, técnico o integrador y quieres aprovechar el Kontrolog Mini dentro del ecosistema OpenPLC.**

---

## 🛠️ Requisitos previos

* [Descargar OpenPLC Editor](https://www.openplcproject.com/).

Una vez instales estos programas, deberás añadir archivos de configuración al entorno de OpenPLC.

---

## 📂 Archivos a agregar

Coloca los siguientes archivos en la ruta:

```
C:\<Users\Personal>\OpenPLC_Editor\editor\arduino\src
```

* [config.h](https://github.com/Omicron-IoT-Solutions/Kontrolog/blob/OpenPLC/Kontrolog%20Mini/Files%20%28Archivos%29/config.h)
* [TLA2528.cpp](https://github.com/Omicron-IoT-Solutions/Kontrolog/blob/OpenPLC/Kontrolog%20Mini/Files%20%28Archivos%29/TLA2528.cpp)
* [tla2528.h](https://github.com/Omicron-IoT-Solutions/Kontrolog/blob/OpenPLC/Kontrolog%20Mini/Files%20%28Archivos%29/tla2528.h)
* [TLA2528\_C.h](https://github.com/Omicron-IoT-Solutions/Kontrolog/blob/OpenPLC/Kontrolog%20Mini/Files%20%28Archivos%29/TLA2528_C.h)

Y reemplaza el siguiente archivo en la ruta:

```
C:\<Users\Personal>\OpenPLC_Editor\editor\arduino\src\hal
```

* [esp32.cpp](https://github.com/Omicron-IoT-Solutions/Kontrolog/blob/OpenPLC/Kontrolog%20Mini/Files%20%28Archivos%29/esp32.cpp)

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

Para que tu Kontrolog Mini funcione correctamente, debes realizar configuraciones directamente en **OpenPLC Editor**.

Abre OpenPLC Editor y crea un proyecto nuevo dentro de una carpeta vacía. Ten en cuenta que cada proyecto en OpenPLC Editor se guarda como una carpeta con todos los archivos necesarios, por lo que no podrás usar una carpeta que ya tenga contenido.

Cuando definas la ruta de tu proyecto, aparecerá un cuadro de ajustes iniciales. Allí debes asignar el nombre del POU (Unidad de Organización de Programas), mantener el tipo de POU como `programa`, y elegir el lenguaje `LD` (Ladder).

<img width="247" height="204" alt="Imagen1(2)" src="https://github.com/user-attachments/assets/8bc6d576-01a3-48e7-8225-a8989f7058fb" />

Un buen punto de partida es inicializar las salidas en estado apagado, para evitar que los LEDs se enciendan de manera inesperada al arrancar.

Una vez que tengas tu programa, podrás simularlo y transferirlo al Kontrolog Mini usando las opciones del editor.

<img width="2216" height="1688" alt="Imagen1(3)" src="https://github.com/user-attachments/assets/b518ad3b-ae6c-440b-a2b4-f03e23558ab6" />

En la sección **I/O Config** de OpenPLC Editor:

* Selecciona como **Board Type** la opción `ESP32 WROOM [3.3.0]`.
* Define el puerto de comunicación serial con el que conectas tu Kontrolog Mini al ordenador.
* Ingresa como **Digital Outputs** los pines en este orden: `32, 15, 13, 02`.
* Deja vacíos los campos de **Digital Inputs**, **Analog Inputs** y **Analog Outputs** a menos que vayas a utilizarlos.

<img width="985" height="623" alt="Imagen1(4)" src="https://github.com/user-attachments/assets/b025ca25-2e39-4a76-9f81-14c6b8d3b91a" />

En la sección **Transferir**, selecciona la opción `Transfer to PLC` y el programa se instalará en tu Kontrolog Mini.

<img width="985" height="623" alt="Imagen1(5)" src="https://github.com/user-attachments/assets/f6a2954e-7edb-44c8-adda-2951360e4b0a" />

> ⚠️ Esta configuración es esencial para asegurar que la integración de OpenPLC con tu Kontrolog Mini funcione de manera correcta y estable desde el inicio.

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
