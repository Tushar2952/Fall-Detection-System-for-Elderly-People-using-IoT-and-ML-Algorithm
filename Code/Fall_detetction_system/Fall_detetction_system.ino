#include <Wire.h>
#include <MPU6050.h>
#include <Adafruit_BMP280.h>  

MPU6050 mpu;
Adafruit_BMP280 bmp; // Not used, just declared

// Ultrasonic Sensor Pins
const int trigPin = 9;
const int echoPin = 10;

float accX, accY, accZ;
float gX, gY, gZ;
float accMagnitude;
float gyroMagnitude;
float distance = 0;
float pressure = 101325.0;  // Imaginary pressure (Pa)
float altitude = 50.0;      // Imaginary altitude (m)

const float FALL_THRESHOLD = 0.8;
const float GYRO_THRESHOLD = 3.0;
const int ledPin = 8;

bool fallDetected = false;
float prevAccMagnitude = 1.0;
unsigned long fallTime = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }

  Serial.println("accX(g),accY(g),accZ(g),gX(°/s),gY(°/s),gZ(°/s),accMag(g),gyroMag(g),distance(cm),pressure(Pa),altitude(m),Fall Status");
}

void loop() {
  accX = mpu.getAccelerationX() / 16384.0;
  accY = mpu.getAccelerationY() / 16384.0;
  accZ = mpu.getAccelerationZ() / 16384.0;

  gX = mpu.getRotationX() / 131.0;
  gY = mpu.getRotationY() / 131.0;
  gZ = mpu.getRotationZ() / 131.0;

  accMagnitude = sqrt(accX * accX + accY * accY + accZ * accZ);
  gyroMagnitude = sqrt(gX * gX + gY * gY + gZ * gZ);
  distance = readUltrasonicDistance();

  // Simulate sensor readings
  pressure = 101250.0 + random(-200, 200);
  altitude = 50.0 + random(-5, 5);

  float accDrop = prevAccMagnitude - accMagnitude;

  // Fall detection
  if ((accMagnitude < FALL_THRESHOLD || accDrop > 0.5) && gyroMagnitude > GYRO_THRESHOLD && !fallDetected) {
    fallDetected = true;
    fallTime = millis();
    digitalWrite(ledPin, HIGH);
  }

  // Reset fall detection after 2s
  if (fallDetected && millis() - fallTime > 2000) {
    digitalWrite(ledPin, LOW);
    fallDetected = false; // ✅ Reset here
  }

  prevAccMagnitude = accMagnitude;

  Serial.print("AccX:"); Serial.print(accX); Serial.print(",");
  Serial.print("AccY:"); Serial.print(accY); Serial.print(",");
  Serial.print("AccZ:"); Serial.print(accZ); Serial.print(",");
  Serial.print("GyroX:"); Serial.print(gX); Serial.print(",");
  Serial.print("GyroY:"); Serial.print(gY); Serial.print(",");
  Serial.print("GyroZ:"); Serial.print(gZ); Serial.print(",");
  Serial.print("AccMag:"); Serial.print(accMagnitude); Serial.print(",");
  Serial.print("GyroMag:"); Serial.print(gyroMagnitude); Serial.print(",");
  Serial.print("Distance:"); Serial.print(distance); Serial.print(",");
  Serial.print("Pressure:"); Serial.print(pressure); Serial.print(",");
  Serial.print("Altitude:"); Serial.print(altitude); Serial.print(",");
  Serial.print("Status:"); Serial.println(fallDetected ? "Fall Detected" : "Fall Not Detected");

  delay(200);
}

float readUltrasonicDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

