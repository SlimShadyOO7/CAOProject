#include <LiquidCrystal.h>
#include <WiFi.h> // Include the Wi-Fi library

const char* ssid = "PTCL-BB"; // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "hussain12"; // The password of the Wi-Fi network

// Create An LCD Object. Signals: [ RS, EN, D4, D5, D6, D7 ]
LiquidCrystal lcd(13, 12, 14, 27, 26, 25);

//defining pins for US sensor
const int trig = 33;
const int echo = 32;

//defining url to get data
const char* url="https://services1.arcgis.com/0MSEUqKaxRlEPj5g/arcgis/rest/services/ncov_cases/FeatureServer/1/query?f=json&where=(Country_Region=%27Pakistan%27)&returnGeometry=false&outFields=Country_Region,Confirmed,Recovered";

#define sound_speed 0.034 //speed of sound in cm/microsec
long duration;//time taken by pulse to travel
float distancecm;//distance of obstacle fro, sensor

void setup()
{
  Serial.begin(115200); // Start the Serial communication to send messages to the computer
  delay(1000);
  Serial.println('\n');
  pinMode(trig, OUTPUT); // Sets the trig Pin as an Output
  pinMode(echo, INPUT); // Sets the echo Pin as an Input
  
  ///////////////////////////////////////////LCD setup///////////////////////////////////////////////
  // Initialize The LCD. Parameters: [ Columns, Rows ]
  lcd.begin(16, 2);
  lcd.clear(); // Clears The LCD Display
  lcd.setCursor(0,0); // Display The First Message In Home Position (0, 0)
  lcd.print("LCD works again!");
  lcd.setCursor(0,1);
  lcd.print("Hand Sanitizer");
  
  ///////////////////////////////////////////wifi setup///////////////////////////////////////////////
  WiFi.begin(ssid, password); // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid);
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
  delay(500);
  Serial.print('.');
  }
  Serial.println('\n');
  Serial.println("Wifi connected!");
}

void sensor(){
  digitalWrite(trig,LOW);//clears pin
  delayMicroseconds(2);
  
  // Sets the trig Pin on HIGH state for 10 micro seconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration=pulseIn(echo, HIGH);
  distancecm= duration * sound_speed / 2; //distance of obstacle from sensor
  
  // Prints the distance in the Serial Monitor
  if(distancecm <= 15){
    Serial.print("Distance (cm): ");
    Serial.println(distancecm);
    Serial.println('\n');
    Serial.print("Opening Pump");
//    digitalWrite(pump, HIGH);
//    delay(2000);
//    digitalWrite(pump, LOW);
//    ESP.restart();
  }
  delay(1000); //1 second delay
}
void loop(){
  sensor();
  
}
