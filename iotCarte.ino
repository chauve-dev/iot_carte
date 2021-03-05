#include <Arduino.h>

#include <SPI.h>
#include <LoRa.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <WiFi.h>   // Utilisation de la librairie WiFi.h

//define the pins used by the LoRa transceiver module
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

//433E6 for Asia
//866E6 for Europe
//915E6 for North America
#define BAND 866E6

//OLED pins
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RST 16
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels



//const char* ssid = "HUAWEI P20 Pro";  // Mettre votre SSID Wifi
//const char* password = "tuturu26";  // Mettre votre mot de passe Wifi
const char* ssid = "projet-info";
const char* password = "projetinfort";

//const uint16_t port = 15555;
//const char * host = "192.168.1.236";
const uint16_t port = 8080;
const char * host = "172.26.123.12";

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

WiFiClient client;

void setup() {
  //reset OLED display via software
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);

  //initialize OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
 
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("LORA SENDER ");
  display.display();
 
  //initialize Serial Monitor
  Serial.begin(921600);
 
  Serial.println("LoRa Sender Test");

  //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);
 
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");
  display.setCursor(0,10);
  display.print("LoRa Initializing OK!");
  display.display();
  delay(2000);




 
  Serial.begin(115200);   // Initialisation du moniteur série à 115200
  delay(1000);

  Serial.println("\n");
  WiFi.begin(ssid,password);  // Initialisation avec WiFi.begin / ssid et password
  display.setCursor(0, 20);
  display.print("Attente de connexion ...");  // Message d'attente de connexion
  display.display();
  while(WiFi.status() != WL_CONNECTED)  // Test connexion

  {

    Serial.print(".");  // Affiche des points .... tant que connexion n'est pas OK

    delay(100);
  }

  Serial.println("\n");
  Serial.println("Connexion etablie !");  // Affiche connexion établie
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.localIP());  // Affiche l'adresse IP de l'ESP32 avec WiFi.localIP

 
  display.setCursor(0, 30);
  display.print("Connexion etablie ! Adresse IP : ");
  display.print(WiFi.localIP());
  display.display();
  client.connect(host, port);
}

void loop() {  
    display.clearDisplay();
    display.setCursor(0,0);
    display.print(client.connected());
    display.setCursor(0,10);
    if (!client.connected()) {

        display.print("Connection to host failed");
        display.display();

        delay(1000);
        return;
    }
   
    display.print("Connected to server successful!");
//    display.setCursor(0,20);
//    client.print("Hello from ESP32!");

    delay(10000);
}
