#include <MPU6050_tockn.h>
#include <Wire.h>
#include <WiFi.h>

const char* ssid = "IZAN";
const char* password = "LUASIKBANG";

MPU6050 mpu6050(Wire);
int BUZZER_PIN = 5;
int LED_PIN = 4;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets();

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Menghubungkan ke WiFi...");
  }

  Serial.println("Terhubung ke WiFi!");
}

void loop() {mpu6050.update();
  Serial.print("angleX: ");
  Serial.print(mpu6050.getAngleX());
  Serial.print(" angleY: ");
  Serial.print(mpu6050.getAngleY());
  Serial.print(" angleZ: ");
  Serial.print(mpu6050.getAngleZ());
  Serial.println();

  float angleX = mpu6050.getAngleX();
  float angleY = mpu6050.getAngleY();
  float angleZ = mpu6050.getAngleZ();

  if (angleX > 10) {
    // Sudut miring ke depan
    tone(BUZZER_PIN, 2500); // Bunyi dengan frekuensi 3000 Hz
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Sudut miring depan");
  } else if (angleX < -5) {
    // Sudut miring ke belakang
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 2000); // Bunyi dengan frekuensi 2000 Hz
    Serial.println("Sudut miring belakang");
  } else if (angleY > 5) {
    // Sudut miring ke kanan
    tone(BUZZER_PIN, 1500); // Bunyi dengan frekuensi 1500 Hz
    Serial.println("Sudut miring kanan");
  } else if (angleY < -5) {
    // Sudut miring ke kiri
    tone(BUZZER_PIN, 1000); // Bunyi dengan frekuensi 1000 Hz
    Serial.println("Sudut miring kiri");
  } else {
    noTone(BUZZER_PIN); // Matikan buzzer jika tidak ada perubahan sudut signifikan
  }

  delay(100); // Interval pembacaan sensor
}
