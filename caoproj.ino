#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <LiquidCrystal.h>

const char* ssid = "PTCL-BB";
const char* password = "hussain12";

int count;

const int rs = 13, en = 12, d4 = 14, d5 = 27, d6 = 26, d7 = 25;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int trig = 33;
const int echo = 32;
//const int pump = 19;

#define sound_speed 0.034 //speed of sound in cm/microsec
long duration;
float distancecm; 

const char* url = "https://services1.arcgis.com/0MSEUqKaxRlEPj5g/arcgis/rest/services/ncov_cases/FeatureServer/1/query?f=json&where=(Country_Region=%27Pakistan%27)&returnGeometry=false&outFields=Country_Region,Confirmed,Recovered";

void setup() {

  Serial.begin(115200);
  delay(2000);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  //pinMode(pump, OUTPUT);
  //digitalWrite(pump, LOW); 
  
  ///////////////////////////////////////////LCD setup///////////////////////////////////////////////
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Covid19 Tracker");
  lcd.setCursor(0,1);
  lcd.print("Hand Sanitizer");

  ///////////////////////////////////////////wifi setup///////////////////////////////////////////////
  
 Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");              // print ... till not connected
  }
  Serial.println("WiFi connected");
}

void sensor(){
  
  digitalWrite(trig, LOW); //clears trig pin
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);    // Sets the trig Pin on HIGH state for 10 micro seconds
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distancecm = duration * sound_speed  / 2; //distance of obstacle from sensor

  if (distancecm <= 15){
    Serial.print("Distance (cm): ");
    Serial.println(distancecm);
    Serial.print("Opening Pump");
    //digitalWrite(pump, HIGH);
    //delay(2000);
    //digitalWrite(pump, LOW);
    //ESP.restart();
    }
}

void loop() {

  sensor();
  HTTPClient https;
  String data;
  https.begin(url); //establishes connection with the url
  int httpCode = https.GET();
  if (httpCode > 0) { //Check for the returning code //success
    String payload = https.getString(); 
    Serial.println(payload);
    DynamicJsonDocument doc(2048);
    deserializeJson(doc, payload);
    JsonArray fields = doc["fields"];
    JsonObject features_0_attributes = doc["features"][0]["attributes"];
    long features_0_attributes_Last_Update = features_0_attributes["Last_Update"];
    int features_0_attributes_Confirmed = features_0_attributes["Confirmed"];
    int features_0_attributes_Deaths = features_0_attributes["Deaths"];
    int features_0_attributes_Recovered = features_0_attributes["Recovered"];
    if (count < 3){

      lcd.setCursor(0, 0);
      lcd.print("Confirmed:");
      lcd.print(features_0_attributes_Confirmed); 
      lcd.setCursor(0, 1);  
      lcd.print("Recovered:");
      lcd.print(features_0_attributes_Recovered);
    }
    if (count > 3){

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Deaths:");
      lcd.print(features_0_attributes_Deaths); 
      lcd.setCursor(0, 1);
      lcd.print("Last Update:");
      lcd.print(features_0_attributes_Last_Update); 
    }

    if (count > 6){
      count = 0; 
    }
 } 
  else {
    Serial.println("Error on HTTP request");
 }

  https.end();
  count++; 
}
