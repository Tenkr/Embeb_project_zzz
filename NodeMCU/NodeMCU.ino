#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#define BLYNK_TEMPLATE_ID "TMPL6mYm1npdl"
#define BLYNK_TEMPLATE_NAME "Jubb Ta Do"
#define BLYNK_AUTH_TOKEN "mKapLcsKEDBPh707XsrjeXf9nA4ZArwb"

char auth[] = "mKapLcsKEDBPh707XsrjeXf9nA4ZArwb";
char ssid[] = "sombobby";
char pass[] = "0969549900";

SoftwareSerial testSerial(D7, D8);

void setup() {
  Serial.begin(9600);
  testSerial.begin(115200);

  //Connect to WiFi network
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();

   while (testSerial.available() > 0) {
    
    String receivedData = testSerial.readStringUntil('\n');  
    delay(1000);
    // Extract parameters using string manipulation and parsing
    int startIndex1 = receivedData.indexOf("soi : ") + strlen("soi : ");
    int endIndex1 = receivedData.indexOf(" ", startIndex1);
    String value1 = receivedData.substring(startIndex1, endIndex1);
    int soi = value1.toInt();
    
    int startIndex2 = receivedData.indexOf("temp : ") + strlen("temp : ");
    int endIndex2 = receivedData.indexOf(" ", startIndex2);
    String value2 = receivedData.substring(startIndex2, endIndex2);
    int temp = value2.toInt();

    int startIndex3 = receivedData.indexOf("humid : ") + strlen("humid : ");
    int endIndex3 = receivedData.indexOf(" ", startIndex3);
    String value3 = receivedData.substring(startIndex3, endIndex3);
    int humid = value3.toInt();

    int startIndex4 = receivedData.indexOf("light : ") + strlen("light : ");
    int endIndex4 = receivedData.indexOf(" ", startIndex4);
    String value4 = receivedData.substring(startIndex4, endIndex4);
    int light = value4.toInt();

    Serial.print("soi: ");
    Serial.println(soi);
    Serial.print("temp: ");
    Serial.println(temp);
    Serial.print("humid: ");
    Serial.println(humid);
    Serial.print("light: ");
    Serial.println(light);

    Blynk.virtualWrite(V2, soi);    // Send individual parameters to Blynk app
    Blynk.virtualWrite(V0, temp);
    Blynk.virtualWrite(V1, humid);
    Blynk.virtualWrite(V3, light);
  }
} 


