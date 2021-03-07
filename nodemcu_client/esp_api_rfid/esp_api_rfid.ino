#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SPI.h>
#include <MFRC522.h>


// Enter Your WiFi name
const char* ssid = "***********";
// Enter the WiFi Password
const char* password = "************";

// Enter The checkpoint Number as string
const String checkpoint_no = "1";


//Your Domain name with URL path or IP address with path
String serverName = "http://192.168.0.100:5000/api/";


#define RST_PIN         0          // Configurable, see typical pin layout above
#define SS_PIN          2         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(115200); 

  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
   
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme

}



void loop() {
  
  
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      if ( ! mfrc522.PICC_IsNewCardPresent()) {
      return;
      }

     // Select one of the cards
     if ( ! mfrc522.PICC_ReadCardSerial()) {
        return;
     }
      char str[32] = "";
      array_to_string(mfrc522.uid.uidByte, 4, str); //Insert (byte array, length, char array for output)
      send_update(str);
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  
}


void send_update(char baggage_id[]){
      HTTPClient http;

      String serverPath = serverName + baggage_id +"/" +checkpoint_no;

      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());

      Serial.println(serverPath.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
}


void array_to_string(byte array[], unsigned int len, char buffer[])
{
   for (unsigned int i = 0; i < len; i++)
   {
      byte nib1 = (array[i] >> 4) & 0x0F;
      byte nib2 = (array[i] >> 0) & 0x0F;
      buffer[i*2+0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
      buffer[i*2+1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
   }
   buffer[len*2] = '\0';
}
