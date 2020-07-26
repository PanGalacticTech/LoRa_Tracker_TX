#include <SPI.h>
#include <LoRa.h>
#include "globals.h"
#include <autoDelay.h>


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







//-------------------------------------------------VVVVVV----------GPS VARIABLEs and SETTINGS------------------------



//-------------------------------------------^^^^^^^^^^^^-----------GPS VARIABLEs and SETTINGS------------------------













autoDelay autodelay;    // set up autodelay instance. Used for time between transmissions


char callSign[] = {"SKY1"};


long txDelay = 5000;      // time in mS between Tx Packets


int counter = 0;                      // Variable to number transmissions



void setup() {
  Serial.begin(115200);
  while (!Serial);

  loraSetup();

  GPSsetup();

}








void loop() {

  Serial.print("Sending packet: ");
  Serial.println(counter);

  if (autodelay.delayScript(txDelay)) {
    loraSendPacket();
    counter++;
  }

  // delay(5000);    // Delay now handled by autodelay script
}
