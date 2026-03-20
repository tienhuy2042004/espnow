#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

typedef struct struct_message {
    char hoTen[50];
    char msv[20];
    float giaTriFake;
} struct_message;

struct_message incomingData;

// Callback tự động chạy khi có sóng ESP-NOW đến
void OnDataRecv(const uint8_t * mac, const uint8_t *incoming, int len) {
  memcpy(&incomingData, incoming, sizeof(incomingData));
  
  // Hiển thị dữ liệu nhận được lên Terminal
  Serial.println(">>> NHAN DU LIEU:");
  Serial.print("Ten: "); Serial.println(incomingData.hoTen);
  Serial.print("MSV: "); Serial.println(incomingData.msv);
  Serial.print("Gia tri: "); Serial.println(incomingData.giaTriFake);
  Serial.println("-------------------------");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) return;
  
  // Đăng ký hàm nhận
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}

void loop() {
  // Receiver không cần làm gì trong loop
}