#include<ESP8266WiFi.h>

#define ssid "HUNTER🦊"
#define password "Black12045"

void setup() {
  // put your setup code here, to run once:
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);

  Serial.begin(115200);
  Serial.setTimeout(1);

  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  
  // pinMode(13, OUTPUT);
  // pinMode(12, OUTPUT);
  // pinMode(11, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  char controlSignal;
  while (!Serial.available());

  controlSignal = Serial.read();
  if(controlSignal == '0') digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  if(controlSignal == '1') digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  if(controlSignal == '2') digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  if(controlSignal == '3') digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  if(controlSignal == '4') digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

}
