# cg2271-esp32

## Overview
This project demonstrates how to use an ESP32 as a web server to control LEDs via button presses on a web page. The project is programmed using PlatformIO in Visual Studio Code.

## Prerequisites
- Visual Studio Code
- PlatformIO extension for Visual Studio Code
- ESP32 development board

## Setting Up PlatformIO on VSCode
1. **Install Visual Studio Code**:
   - Download and install Visual Studio Code from [here](https://code.visualstudio.com/).

2. **Install PlatformIO Extension**:
   - Open Visual Studio Code.
   - Go to the Extensions view by clicking on the Extensions icon in the Activity Bar on the side of the window or by pressing `Ctrl+Shift+X`.
   - Search for "PlatformIO IDE" and click "Install".

3. **Create a New PlatformIO Project**:
   - Open the Command Palette (`Ctrl+Shift+P`) and select `PlatformIO: New Project`.
   - Enter a name for your project, select your board (e.g., `Espressif ESP32 Dev Module`), and choose `Arduino` as the framework.
   - Click "Finish" to create the project.

## Flashing `index.html` to ESP32
1. **Create a `data` Folder**:
   - In your PlatformIO project directory, create a folder named `data`.

2. **Add `index.html`**:
   - Place your `index.html` file inside the `data` folder.

3. **Upload Filesystem Image**:
   - Open the PlatformIO Terminal in Visual Studio Code.
   - Run the following command to build and upload the filesystem image to the ESP32:
     ```sh
     pio run --target uploadfs
     ```

## How the ESP32 Works as a Web Server
1. **WiFi Setup**:
   - The ESP32 is configured to create a WiFi access point with the SSID and password defined in [wifi_credentials.h](http://_vscodecontentref_/0).

2. **SPIFFS Initialization**:
   - The SPIFFS (SPI Flash File System) is initialized to serve the [index.html](http://_vscodecontentref_/1) file.

3. **Web Server Setup**:
   - An [AsyncWebServer](http://_vscodecontentref_/2) is created to handle HTTP GET requests.
   - The root route (`"/"`) serves the [index.html](http://_vscodecontentref_/3) file from SPIFFS.
   - Additional routes (`"/redOn"`, `"/redOff"`, `"/greenOn"`, `"/greenOff"`, `"/blueOn"`, `"/blueOff"`) handle LED control via HTTP GET requests.

4. **Handling Button Presses**:
   - When a button on the web page is pressed, an HTTP GET request is sent to the ESP32.
   - The ESP32 handles the request by turning the corresponding LED on or off and sending a response back to the client.
   - The status of the LEDs is updated on the web page using JavaScript.
