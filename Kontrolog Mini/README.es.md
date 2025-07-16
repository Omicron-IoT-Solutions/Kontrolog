![LogoOmicron](https://github.com/user-attachments/assets/731e45b1-c19b-441d-91a9-a7186d3ecd1f)

# 🧩 Kontrolog Max en modo No-Code.

![Imagen1](https://github.com/user-attachments/assets/2fcfb911-ca10-46cc-97dd-0984f5d213d9)

📄 **Disponible también en inglés**: [English version](./README.md).

---

## 📘 Descripción general:

Esta rama contiene el firmware predeterminado para el **Kontrolog Max**, permitiendo su programación sin escribir código, mediante tres métodos principales:

* Interfaz gráfica HMI local.
* Portal cautivo vía WiFi.
* Plataforma web IoT (si está habilitada).

Además, incluye ejemplos y tutoriales que te guiarán paso a paso en la instalación y uso en modo No-Code.

> ✅ **Ideal para técnicos, profesionales, estudiantes e integradores.**

---

## ⚙️ ¿Cómo cargar el firmware al Kontrolog Max?:

El [firmware del Kontrolog Max](https://github.com/Omicron-IoT-Solutions/Kontrolog/tree/No-Code/Kontrolog%20Max/Firmware) es el software de fábrica que ya viene instalado al recibir tu dispositivo. Sin embargo, puedes reinstalarlo o actualizarlo manualmente si es necesario.

### Pasos:

1. Descarga e instala el programa **[Flash Download Tool](https://www.espressif.com/en/support/download/other-tools)**.

![Imagen2](https://github.com/user-attachments/assets/e8c1f4cb-4268-45e2-8d13-c6c952a47ac9)

2. Descarga el archivo `.bin` del firmware desde el repositorio.
3. Conecta el Kontrolog Max a tu PC mediante el cable USB-C.
4. Abre Flash Download Tool y selecciona:

   * **Chip**: ESP32.
   * **Mode**: Development.

![Imagen3](https://github.com/user-attachments/assets/8a66cb22-fcc2-408f-a22f-b2307f626297)

5. Carga el archivo `.bin` y configúralo con:

   * Dirección de memoria: `0x10000`.
   * SPI Speed: `40MHz`.
   * SPI Mode: `DIO`.
   * Activa “DoNotChgBin”.
6. Selecciona el puerto COM correcto y velocidad: `460800 Baud`.
7. Haz clic en Start para programar tu dispositivo.

![Imagen4](https://github.com/user-attachments/assets/98c00ce6-3f8f-4906-858b-13938cf082f4)

---

## 🖥️ Simulación de la pantalla HMI:

Puedes simular el comportamiento de la pantalla táctil del Kontrolog Max con el software **[Nextion Editor](https://nextion.tech/nextion-editor/)**.

### Pasos:

1. Descarga e instala Nextion Editor.

![Imagen5](https://github.com/user-attachments/assets/e10485ff-d315-4530-b43c-6ad407b2ba32)

2. Descarga el archivo [.HMI](https://github.com/Omicron-IoT-Solutions/Kontrolog/tree/No-Code/Kontrolog%20Max/Display).
3. Ábrelo desde Nextion Editor.
4. Inicia el modo de depuración (Debug).

![Imagen6](https://github.com/user-attachments/assets/784b0914-5c54-48a8-a983-1875fd930104)

5. Configura:

   * **Send command to**: “Current Simulator”.
   * **User MCU input**: habilitado.
   * **Baudrate**: `115200`.
   * **Puerto**: el mismo al que está conectado tu Kontrolog Max.

![Imagen7](https://github.com/user-attachments/assets/ae30ae74-f5f2-47ec-bbaf-f83d3b6ad956)

Así podrás simular la experiencia real de la pantalla HMI y configurar parámetros básicos.

---

## 🌐 Configuración desde el portal cautivo:

Por defecto, al encenderse, el Kontrolog Max crea una red WiFi llamada:

```
Kontrolog_xxxxxxxxxxx
```

(Ejemplo: `Kontrolog_bcddc212345`).

### Pasos:

1. Conéctate a la red WiFi desde tu celular o PC (contraseña: `OmicronIoT12345678`).
2. Abre un navegador e ingresa la dirección: `192.168.4.1`.

Desde esta interfaz web podrás:

* Conectar el dispositivo a Internet.
* Configurar tu cuenta en la nube (Ubidots).
* Monitorear entradas/salidas.
* Consultar MAC y versión del firmware.

![Imagen8](https://github.com/user-attachments/assets/fb6af919-496a-426e-8732-e19eafbbf1db)

Esto permite configurar el Kontrolog Max sin código, desde una interfaz amigable y visual.

---

## 📞 Contacto:

¿Tienes preguntas o necesitas ayuda?

* 📧 Correo electrónico: [solutions@omicroniot.com](mailto:solutions@omicroniot.com).
* 📱 WhatsApp / Teléfono: [+57 317 4365062](https://api.whatsapp.com/send?phone=573176478281).

---

**Omicron IoT Solutions**
