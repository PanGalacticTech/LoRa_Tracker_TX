#include <SPI.h>
#include <LoRa.h>


/*

  LoRa SX1278 Module Arduino Nano Board:

  3.3V            -
  Gnd            Gnd
  En/Nss         D10
  G0/DIO0        D2
  SCK            D13
  MISO           D12
  MOSI           D11
  RST            D9




  LoRa SX1278 Module ESP32  Board:

  GPIO 6 - 11 used for integrated SPI

  3.3V            -
  Gnd            Gnd
  En/Nss         D10
  G0/DIO0        D2
  SCK            D13
  MISO           D12
  MOSI           D11
  RST            D9



  Here’s the connections between the RFM95 LoRa transceiver module and the ESP32:


  ANA:          Antenna
  GND:          GND
  DIO3:         don’t connect
  DIO4:         don’t connect
  3.3V:         3.3V
  DIO0:         GPIO 2
  DIO1:         don’t connect
  DIO2:         don’t connect
  GND:          don’t connect
  DIO5:         don’t connect
  RESET:        GPIO 14
  NSS:          GPIO 5
  SCK:          GPIO 18
  MOSI:         GPIO 23
  MISO:         GPIO 19
  GND:          don’t connect




*/


char callSign[] = {"SKY1"};

int counter = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Transmit");

  if (!LoRa.begin(434.5E6)) {                             // sets TX frequency 434.500    E6 = translate to MHz
    Serial.println("Starting LoRa failed!");
    delay(500);
    ESP.restart();
    while (1);
  }
}





void loop() {

  Serial.print("Sending packet: ");
  Serial.println(counter);


  loraSendPacket();

  counter++;

  delay(5000);
}







void loraSendPacket() {


  // send packet
  LoRa.beginPacket();

  LoRa.print(callSign);
  LoRa.print(" ");
  LoRa.print(counter);
  LoRa.print(" ");

  LoRa.print("GPS Data");

  LoRa.endPacket();


}
