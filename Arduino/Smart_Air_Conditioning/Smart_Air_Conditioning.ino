#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

#include "addons/TokenHelper.h"

#include "addons/RTDBHelper.h"

#define WIFI_SSID "YourWifiSSID"
#define WIFI_PASSWORD "YourWifiPassword"

#define API_KEY "AIzaSyDzU0Ndmefis6IOULmc43RPubieEAdgQ9U"

#define DATABASE_URL "https://nodemcu-9a843-default-rtdb.europe-west1.firebasedatabase.app/" 

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int nivosvjetlosti;
bool signupOK = false;
int senzor = 0;
bool automatski = true;
int granica = 0;

void setup() {
  pinMode(D1, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;

  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback; 

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
  if (Firebase.RTDB.getBool(&fbdo, "/rasvjeta/automatski")) {   
      if (fbdo.dataType() == "boolean") {
        automatski = fbdo.boolData();
        Serial.println("automatski:");
        Serial.println(automatski);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
  if (automatski == true) {
    senzor = analogRead(A0);
    if (Firebase.RTDB.setInt(&fbdo, "rasvjeta/senzor", senzor)){
      Serial.println("PASSED");
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    if (Firebase.RTDB.getInt(&fbdo, "/rasvjeta/granica")) {
      if (fbdo.dataType() == "int") {
        granica = fbdo.intData();
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
    if (senzor < granica) {
      analogWrite(D1, 255);
    }
    else {
      analogWrite(D1, 0);
    }
  }
  else {
     if (Firebase.RTDB.getInt(&fbdo, "/rasvjeta/nivosvjetlosti")) {
      if (fbdo.dataType() == "int") {
        nivosvjetlosti = fbdo.intData();
        analogWrite(D1, nivosvjetlosti);
    }
    else {
      Serial.println(fbdo.errorReason());
    }
  }
}
}
}