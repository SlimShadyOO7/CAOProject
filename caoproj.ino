#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <LiquidCrystal.h>

const char* ssid = "PTCL-BB";
const char* password = "hussain12";

int count;

const int rs = 13, en = 12, d4 = 14, d5 = 27, d6 = 26, d7 = 25;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const char* url = "https://services1.arcgis.com/0MSEUqKaxRlEPj5g/arcgis/rest/services/ncov_cases/FeatureServer/1/query?f=json&where=(Country_Region=%27Pakistan%27)&returnGeometry=false&outFields=Country_Region,Confirmed,Recovered";

#define relay 19
#define echo 18
#define trig 5

long duration;
int distance;

void setup() {
  Serial.begin(9600);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);

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

void loop() {
  calc_distance();
  if(distance<10){
    digitalWrite(relay, LOW);
  }
  else{
    digitalWrite(relay, HIGH);
  }

  //////////////////LCD///////////////////////
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

void calc_distance(){
  digitalWrite(trig, LOW); //clear trigger pin from previous loop
  delayMicroseconds(2); //using Microseconds as the delay needs to be very very short - delay uses millisecond
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);  //trigger pin high for 10 microsecond - sound wave sent
  digitalWrite(trig, LOW); //reset trigger pin

  duration = pulseIn(echo, HIGH);  //reading and storing time it takes for echo
  //duration contains sound travel time in microseconds
 
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
  //distance contains distance in centimeter
  Serial.println("Distance: ");
  Serial.println(distance);
}
