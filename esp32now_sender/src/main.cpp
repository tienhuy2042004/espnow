#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

// Định nghĩa cấu trúc bản tin (Phải giống hệt bên nhận)
typedef struct struct_message {
    char hoTen[50];
    char msv[20];
    float giaTriFake;
} struct_message;

struct_message myData;
esp_now_peer_info_t peerInfo;

// Địa chỉ FF...FF giúp tự động tìm thấy mọi Receiver trong tầm sóng
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); 

  if (esp_now_init() != ESP_OK) {
    Serial.println("Loi khoi tao ESP-NOW");
    return;
  }

  // Đăng ký thiết bị nhận (Peer)
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Khong the add Peer");
    return;
  }
}

void loop() {
  // Chuẩn bị dữ liệu fake
  strcpy(myData.hoTen, "Hoang Trung Kien");
  strcpy(myData.msv, "B22DCDT156");
  myData.giaTriFake = random(250, 400) / 10.0; // Random nhiệt độ từ 25.0 - 40.0

  // Gửi dữ liệu đi
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.printf("Da gui: %s - %s - Value: %.2f\n", myData.hoTen, myData.msv, myData.giaTriFake);
  }
  
  delay(2000); 
}