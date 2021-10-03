#include <M5StickC.h> 
#include <WiFi.h> 
TFT_eSprite img = TFT_eSprite(&M5.Lcd);

char ssid[] = "WhiteCat"; 
char pass[] = "whitecat1"; 
WiFiServer server(80); 
byte mac[] = { 0x24, 0xA1, 0x60, 0x53, 0xC5, 0xF4 };
#define IW 320 
#define IH 40
#define WAIT 45
#define XX 5700
#define AX 230
#define IW2 50
#define IH2 50


unsigned int CRT(byte value) { 
// Do random color as byte value
byte red_blue_green = random(0xFFFF);
return red_blue_green * value;  
}

unsigned int RGBVAL(byte value) {
  byte red = 0;  // Do basic color wheel by switch sector
  byte blue = 0;
  byte green = 0;

  byte sector = value >> 5;
  byte amplit = value & 0x1F;

  switch (sector) {
  case 0: 
  red = 0x1F;
  green = amplit;
  blue = 0;
  break;
  case 1:
  red = 0x1F - amplit;
  green = 0x1F;
  blue = 0;
  break;
  case 2:
  red = 0;
  green = 0x1F;
  blue = amplit;
  break;
  case 3: 
  red = 0xFF;
  green = 0x1F - amplit;
  blue = random(0x2F);
  break;   
  case 4:
  red = 0;
  green = 0x1F - amplit;
  blue = 0x1F;
  break;  
  }
  
return red << 11 | green << 6 | blue;
}


void printWifiStatus() {
  M5.Lcd.fillScreen(TFT_BLUE); 
  M5.Lcd.setCursor(1,1); 
  M5.Lcd.setTextSize(1); 
  M5.Lcd.setTextColor(TFT_WHITE, TFT_BLUE); 
  // print the SSID of the network you're attached to:
  M5.Lcd.print("SSID: ");
  M5.Lcd.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  M5.Lcd.print("IP Address: ");
  M5.Lcd.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  M5.Lcd.print("signal strength (RSSI):");
  M5.Lcd.print(rssi);
  M5.Lcd.println(" dBm");
  delay(5000); 
  M5.Lcd.fillScreen(TFT_BLACK); 
  M5.Lcd.setCursor(1,1); 
}

void check_board() {
  WiFiClient client = server.available(); 
  if (client) {
    while (client.connected()) {
      if (client.available()) {
      M5.Lcd.setCursor(1,1); 
      M5.Lcd.setTextColor(random(0xFFFF));
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; text-color:white; background-color: #000000;}");
            client.println("h1 { background-color:black; border: none; color: red; padding: 16px 40px;");
            client.println("p { text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer; color:white;}");
            client.println("ol { list-style-type:square;}");
            client.println("</style></head>");
            client.println("<body><h1>WhiteCat Proxy network</h1><br> <h2><font color='lightblue'>ESP32 Web Server Active</h2></font>");
            client.println("<br><p><font color='white'> ");
            client.println("My network Essid is: WhiteCat <br> My network password is: whitecat1<br>");
            client.println("At this time I am configured to act as A proxy network.<br>");
            client.println("</font></p><br>"); 
            client.println("<font color='yellow' size=20>");
            int numSsid = WiFi.scanNetworks();
            
            if (numSsid == -1) { client.println("No WiFi networks Found?<br>"); }
            if (numSsid == 0) { client.println("No WiFi networks Found Searching..<br>"); }            
            client.println("WiFi networks found!<br> ");
            client.println(".<br><ol type='I'><font color='green' size=6px>");
            for (int i = 0; i <= numSsid; i++) {
            for (int thisNet = 0; thisNet < numSsid; thisNet++) {
              client.print("<li>");
              client.print(WiFi.SSID(thisNet));
              client.print("  Signal: ");
              client.print(WiFi.RSSI(thisNet));
              client.print(" dBm");
              client.print("    Encryption:"+(WiFi.encryptionType(thisNet) == WIFI_AUTH_OPEN)?" ":"OPEN");            
              client.print("</li><br>");
            }
            }
            client.println("</font><ol><p>Scanning finished.</p>");
            client.println("</body></html>");     
       client.stop(); 
      }
    }
  }
}
