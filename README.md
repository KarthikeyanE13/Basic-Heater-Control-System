# Temperature-Based Heater Control System

## 🔧 Overview
This project implements a temperature-controlled heater system using an ESP32 and a DS18B20 sensor. The system monitors temperature in real-time and switches the heater ON or OFF based on defined thresholds, transitioning through different states such as IDLE, HEATING, STABILIZING, TARGET REACHED, and OVERHEAT. An LED indicates the heater's status.

## 🚀 Features
- Real-time temperature monitoring
- Heater control using relay
- LED indicator for heater state
- Overheat protection logic
- Wokwi simulation support

## 📁 Project Structure
- `sketch.ino` – Main C++ code with state management
- `diagram.json` – Circuit wiring for Wokwi simulation
- `libraries.txt` – Required Arduino libraries
- `wokwi-project.txt` – Simulation reference link
- `README.md` – This file

## 🧪 Simulation
▶️ [Try it on Wokwi](https://wokwi.com/projects/436920312189691905)

## 💻 How to Use
1. Connect DS18B20 to ESP32 as per the provided circuit.
2. Upload the code using the Arduino IDE.
3. Monitor temperature via the Serial Monitor.
4. Observe heater and LED behavior based on the current temperature.

## 📚 Requirements
- ESP32 DevKit
- DS18B20 Temperature Sensor
- LED
- Arduino IDE with DallasTemperature & OneWire libraries

## ✍️ Author
Karthikeyan E
