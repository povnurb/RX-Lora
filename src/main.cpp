#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//configuracion del modulo LORA
//pendiente salvar en github
String lora_band = "915000000"; //Banda de frecuencia 
String lora_networkid = "18";   //Identificación de la red Lora
String lora_address = "2";      //Dirección de esta Lora
String lora_RX_address = "1";   //Dirección del modulo receptor

// Oled display size
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

SoftwareSerial serial2;

#define LEDPin 13
String incomingstring;

 
String inString;

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200,SERIAL_8N1, 16,17);
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
  display.setTextSize(1);           
  display.fillRect(0, 0, 128, 15, SSD1306_INVERSE);
  display.setTextColor(SSD1306_BLACK);  
  display.setCursor(4,4); 
  display.println("RECEIVING: ");
  display.println("");
  display.setTextColor(SSD1306_WHITE);
  display.display();
  pinMode(LEDPin,OUTPUT);
  digitalWrite(LEDPin,LOW);

  delay(1000);
  Serial2.println("AT+BAND?");
  if(Serial2.available()){ 
    incomingstring= Serial2.readString();
    display.print(incomingstring);
    display.display();
    Serial.println(incomingstring);
  }
  delay(1000);
  Serial2.println("AT+NETWORKID?");
  if(Serial2.available()){ 
    incomingstring= Serial2.readString();
    display.print(incomingstring);
    display.display();
    Serial.println(incomingstring);
  }
  //delay(1500);
  //Serial2.println("AT+ADDRESS=" + lora_address); //configurar la direccion 
  delay(1000);
  Serial2.println("AT+ADDRESS?");
  if(Serial2.available()){ 
    incomingstring= Serial2.readString();
    display.print(incomingstring);
    display.display();
    Serial.println(incomingstring);
  }
  delay(1000);
}
int Received;

void loop() {
  if(Serial2.available()){ 
    display.clearDisplay();
    display.setTextSize(1);           
    display.fillRect(0, 0, 128, 15, SSD1306_INVERSE);
    display.setTextColor(SSD1306_BLACK);  
    display.setCursor(4,4); 
    display.println("RECEIVING: ");
    display.println("");
    display.setTextColor(SSD1306_WHITE);
    incomingstring= Serial2.readString();
    display.print(incomingstring);
    display.display();
    Serial.println(incomingstring);
    if (incomingstring.indexOf("H") >0) { 
      digitalWrite(LEDPin, HIGH);
    }
    else if (incomingstring.indexOf("L") >0) { 
      digitalWrite(LEDPin, LOW);
    }
  }
}
/*
//https://github.com/labuhardilladelloco/RYLR998/blob/main/RYLR998_RX/receptor.png
//https://github.com/labuhardilladelloco/RYLR998/blob/main/RYLR998_RX/RYLR998_RX.ino
//https://www.youtube.com/watch?v=UH346_44M_Y
//https://i.pinimg.com/originals/b4/47/02/b447026b22d6609aee17fddb097b0a46.png
*/