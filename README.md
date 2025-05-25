# 🛡️ Fall Detection System

The **Fall Detection System** is an IoT and machine learning-based solution designed to monitor elderly individuals and detect potential falls in real-time using multiple environmental and motion sensors. The system aims to alert caregivers and reduce the risks associated with undetected falls.

![Fall Detection System Design](Fall%20Detection%20System_Schematic.jpg)

---

## 📦 Features

- Real-time fall detection using motion (MPU6050) and distance (HC-SR04) sensors.
- Environmental data collection using BMP280 (temperature & pressure sensor).
- LED alert system for immediate visual feedback.
- Data logging support for training machine learning models.
- Expandable and modular system for future integrations.

---

## ⚙️ Hardware Components

- Arduino Uno R3
- MPU6050 (Accelerometer + Gyroscope)
- HC-SR04 Ultrasonic Sensor
- BMP280 (Temperature + Pressure sensor)
- LED
- Breadboard & jumper wires

---

## 🧠 Machine Learning Integration

The collected sensor data can be used to:
- Train ML models like Random Forest, XGBoost, or a CNN-LSTM hybrid model.
- Detect fall events using engineered features like jerk, acceleration magnitude, and environment context.

---

## 🛠️ Installation & Setup

### 1. Hardware Setup

Refer to the above schematic image and connect:
- **MPU6050:** Uses I2C (A4 -> SDA, A5 -> SCL)
- **BMP280:** Also uses I2C (shared lines)
- **HC-SR04:** Trig -> D9, Echo -> D10
- **LED:** Anode -> D8 via a 220Ω resistor

### 2. Software Setup

1. Install the Arduino IDE.
2. Install required libraries:
   - `Adafruit_BMP280`
   - `Adafruit_Sensor`
   - `Wire.h`
   - `MPU6050`
3. Upload the `fall_detection.ino` sketch to your Arduino Uno.

---

## 📈 Data Collection

Sensor data logged includes:
- `ax, ay, az` – Accelerometer axes
- `gx, gy, gz` – Gyroscope axes
- `distance` – Ultrasonic sensor
- `pressure`, `altitude` – BMP280
- `acc_magnitude`, `jerk`, `label` – Engineered features

Use the data to train ML models in Python using `scikit-learn`, `xgboost`, or `tensorflow`.

---

## 🧪 Project Structure
