#include <LiquidCrystal.h>
#include <WiFi.h>        // Include the Wi-Fi library
const char* ssid     = "PTCL-BB";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "hussain12";     // The password of the Wi-Fi network

// Create An LCD Object. Signals: [ RS, EN, D4, D5, D6, D7 ]
LiquidCrystal My_LCD(13, 12, 14, 27, 26, 25);
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
  My_LCD.begin(16, 2);
  // Clears The LCD Display
  My_LCD.clear();

  // Display The First Message In Home Position (0, 0)
  My_LCD.print("Hello World!");
  // Set The Cursor Position To: [ Col 5, Row 1]
  My_LCD.setCursor(5, 1);
  // Display The Second Message In Position (5, 1)
  My_LCD.print("Setting up...");
 }
void loop(){}
