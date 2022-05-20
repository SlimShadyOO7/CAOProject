#include <LiquidCrystal.h>
#include <WiFi.h>        // Include the Wi-Fi library

const char* ssid     = "PTCL-BB";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "hussain12";     // The password of the Wi-Fi network
// Create An LCD Object. Signals: [ RS, EN, D4, D5, D6, D7 ]
LiquidCrystal lcd(13, 12, 14, 27, 26, 25);
void setup()
{
 Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(500);
    Serial.print('.');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
  
    // Initialize The LCD. Parameters: [ Columns, Rows ]
  lcd.begin(16, 2);

  lcd.clear();  // Clears The LCD Display

  lcd.setCursor(0,0);  // Display The First Message In Home Position (0, 0)

  lcd.print("Covid19 Tracker");

  lcd.setCursor(0,1);

  lcd.print("Hand Sanitizer");
 }
void loop(){}
