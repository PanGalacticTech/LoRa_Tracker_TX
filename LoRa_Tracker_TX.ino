// Test code for Adafruit GPS modules using MTK3329/MTK3339 driver
//
// This code shows how to listen to the GPS module in an interrupt
// which allows the program to have more 'freedom' - just parse
// when a new NMEA sentence is available! Then access data when
// desired.
//
// Tested and works great with the Adafruit Ultimate GPS module
// using MTK33x9 chipset
//    ------> http://www.adafruit.com/products/746
// Pick one up today at the Adafruit electronics shop
// and help support open source hardware & software! -ada

#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <autoDelay.h>
#include "globals.h"
#include <SparkFunBME280.h>
#include <SPI.h>
#include <LoRa.h>


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// GPS Wiring & Constructors
// Connect the GPS Power pin to 5V
// Connect the GPS Ground pin to ground
// Connect the GPS TX (transmit) pin to Digital 8
// Connect the GPS RX (receive) pin to Digital 7


// you can change the pin numbers to match your wiring:
SoftwareSerial mySerial(8, 7);
Adafruit_GPS GPS(&mySerial);


// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO false
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


/////////////////////////////////////////////////////////////////////////////////////////////
//Sensor Wiring and Constructors:
///////////////////////////////////////////////////////////////
//                          BME280                           //
///////////////////////////////////////////////////////////////
/* define the BME280 address.
   Use if address jumper is closed (SDO - GND) : 0x76.*/
#define I2CADDR 0x76

/* Define reading in Fahrenheit or Celsius
    1 = Celsius
    0 = Fahrenheit */
#define TEMP_TYPE 1

/* define whether hight Meters or Foot
    1 = Meters
    0 = Foot */
#define BME_HIGHT 1

//#define SEALEVELPRESSURE_HPA (1013.25)   // standard
#define SEALEVELPRESSURE_HPA (1030)   // lydd airport 3m
//#define SEALEVELPRESSURE_HPA (1029)   // heathrow airport 25m

// BME280 Sensor Wiring:
// Connect BME280 SCL to A5  (10k to +v)
// Connect BME280 SDA to A4  (10k to +v)

BME280 bme280; //Global sensor object

////////////////////////////////////////////////////////////////////////////////////////////////

//####################### AutoDelay Constructors #########################################

autoDelay autodelayGPS;                 /// sets up delay for GPS printouts

long GPSdelay = 2000;

autoDelay autodelayAtmos;           // Sets up delay for Atmospheric Readings

long atmosDelay = 10000;


autoDelay autodelayLoRa;                  // Sets up Delay for LoRa transmissions

long LoRaDelay = 5000;



// status
bool detected_BME280 = false;





void setup() {


  Serial.begin(115200);                   // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  while (!Serial);
  delay (1000);                                           // also spit it out

  loraSetup();                                // LoRa Setup Scripts
  GPSsetup();                                 // GPS Setup Scripts
  BME280setup();                               // Atmospheric Setup Scripts

}











void loop()  {                  // run over and over again


  GPSread_andParse();                // Checks for incoming GPS messages, can directly print messages, or parse them using GPS library for later recall (prefered)



  if (autodelayGPS.delayScript(GPSdelay)) {                      // approximately every 2 seconds or so, print out the current stats
    //  GPSserialPrint();                               //Serial Print Data
    //  GPSdataPackage();

    if (detected_BME280) {                            // This now wrapped up in the GPS delay function so BME packets are delivered with GPS time stamps

      if (autodelayAtmos.delayScript(atmosDelay)) {
        readBME280();
        //   BME280serialPrint();

      }
    }

    if (autodelayLoRa.delayScript(LoRaDelay)) {
      sortGPSData();
      loraBuildPacket();

      loraSendPacket();



    }

  }

}
